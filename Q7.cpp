#include <iostream>
#include <vector>
#include <string>
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
                added++;
            }
        }
        else{ //add to next customer
            for (int i=0; i < current_children; i++){
                _customers[current_customer]->add_child(_customers[added + i]);
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

int main(){
    srand(time(0));
    return 0;
}