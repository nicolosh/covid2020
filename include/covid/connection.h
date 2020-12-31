//
// Created by nicol on 23/12/2020.
//

#ifndef COVID2019_CONNECTION_H
#define COVID2019_CONNECTION_H

#include "covid/node.h"

namespace covid {

    class connection { // calcola i flussi di persone da spostare nei vari nodes
    protected:
        node* src_;
        node* dest_;
        double flow_;
        std::string nameConnection;

    public:
        explicit connection(node* src, node* dest, const std::string& name) : src_(src), dest_(dest), nameConnection(name),
        flow_(0.0){}

        virtual double computeFlow(double dt = 1.0) = 0;

        double getFlow() const { return flow_; }

        node* getNodeSource() const { return src_; }

        node* getNodeDestination() const { return dest_; }

        const std::string& getNameConnection() const { return nameConnection; }

    };
}

#endif //COVID2019_CONNECTION_H
