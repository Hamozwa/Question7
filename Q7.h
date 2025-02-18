#ifndef Q7_H
#define Q7_H

#include <vector>
#include <string>

class node{
    public:
        node(std::string name, int distance);
        std::string get_name() const;
        int get_distance() const;
        void add_child(node* child);
        void set_parent(node* parent);
        node* get_parent() const;
        std::vector<node*> get_child_nodes() const;
    private:
        std::string _name;
        int _distance;
        std::vector<node*> _child_nodes;
        node* _parent;
};

class neighbourhood{
    public:
        neighbourhood(int customerNum);
        int shortest_path(node* customer);
        void simulate_order(int orderNum);
    private:
        node* _store;
        std::vector<node*> _customers;

};


#endif