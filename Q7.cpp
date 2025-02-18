#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include "Q7.h"

//implement node class
node::node(std::string name, int distance){
    _name = name;
    _distance = distance;
};
std::string node::get_name() const {
    return _name;
};
int node::get_distance() const{
    return node::_distance;
};
void node::add_child(node* child){
    _child_nodes.push_back(child);
};
void node::set_parent(node* parent){
    _parent = parent;
};
node* node::get_parent() const {
    return _parent;
};
std::vector<node*> node::get_child_nodes() const {
    return _child_nodes;
};

//implement neighbourhood class
neighbourhood::neighbourhood(int customerNum){
    //randomly create tree of nodes
    _store = new node("store", 0);

    //create customers and randomly create tree of nodes
    _customers.resize(customerNum);
    for (int i = 0; i < customerNum; i++){
        _customers[i] = new node("customer" + std::to_string(i+1), rand() % 1001);
    }
    
    int added = 0;
    for (int current_customer = -1; added < customerNum; current_customer++){
        int current_children = (rand() % (customerNum - added)) + 1;
        if (current_customer == -1){ //add to store
            for (int i=0; i < current_children; i++){
                _store->add_child(_customers[added + i]);
                _customers[added + i]->set_parent(_store);
                added++;
            }
        }
        else{ //add to next customer
            for (int i=0; i < current_children; i++){
                _customers[current_customer]->add_child(_customers[added + i]);
                _customers[added + i]->set_parent(_customers[current_customer]);
                added++;
            
            }
        }
    }

    //print neighhborhood
    std::cout << "Store: " << _store->get_name() << std::endl;
    std::cout << "Customers: ";
    for(int i = 0; i < _customers.size(); i++){
        std::cout << _customers[i]->get_name() << " ";
    }
    
};

std::pair<std::vector<node*>, int> neighbourhood::shortest_path(node* customer){
    node* current = customer;
    std::vector<node*> path;
    int distance = 0;
    
    while (current != _store){
        path.insert(path.begin(), current);
        current = current->get_parent();
        distance += current->get_distance();
    }

    return make_pair(path, distance);
};

void neighbourhood::simulate_order(int orderNum){
    //create random orders
    std::vector<std::pair<node*, int>> orders;
    for (int i=0; i<orderNum; i++){
        std::pair<node*, int> order = std::make_pair(_customers[rand() % _customers.size()], (rand() % 2) + 1);
        orders.push_back(order);
    }

    //deliver orders
    std::vector<bool> delivered(orderNum, false);

    for (int i=0; i<orderNum; i++){
        if (delivered[i] == false){
            delivered[i] = true;
            int items = orders[i].second;
            std::cout << "Delivering " << items << " items to " << orders[i].first->get_name() << std::endl;
            std::pair<std::vector<node*>, int> shortest = shortest_path(orders[i].first);
            std::vector<node*> path = shortest.first;
            int distance = shortest.second;

            //check if another item can be delivered on the way
            bool filled_basket = false;
            for (int j=0; j<path.size(); j++){
                for (int k=0; k<orderNum; k++){
                    if (delivered[k] == false && orders[k].first == path[j] && items + orders[k].second <= 3){
                        delivered[k] = true;
                        items += orders[k].second;
                        std::cout << "Delivering " << orders[k].second << "items to " << orders[k].first->get_name() << " on the way." << std::endl;
                        if (items == 3){
                            filled_basket = true;
                            break;
                        }
                    }
                }
                if (filled_basket){
                    break;
                }

            }
            std::cout << "Total distance for trip: " << distance << std::endl;
        }
    }

}

int main(){
    srand(time(0));

    neighbourhood n(10);
    n.simulate_order(10);
    return 0;
}