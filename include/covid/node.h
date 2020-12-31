//
// Created by nicol on 23/12/2020.
//

#ifndef COVID2019_NODE_H
#define COVID2019_NODE_H

#include <string>

namespace covid {
    class node {
    protected:
        std::string name_;
        double value_;
    public:
        explicit node(const std::string& name, double stateNode) : name_(name), value_(stateNode){}

        bool isEmpty() const { return (value_ == 0); }

        const std::string& getName() const { return name_; }

        double getValue() const { return value_; }

        void transferTo(node* dest, double value)
        {
            value_ -= value;
            dest->value_ += value;
        }

    };
}

#endif //COVID2019_NODE_H
