//
// Created by nicol on 23/12/2020.
//

#ifndef COVID2019_CONNECTIONSI_H
#define COVID2019_CONNECTIONSI_H

#include <vector>
#include "covid/connection.h"

namespace covid{

    struct nodeParam{
        node* X_;
        double coeff;
        nodeParam(node* X, double coefficient) : X_(X), coeff(coefficient) {};
    };

    class connectionSI : public connection{
        protected:
            std::string nameSI;
            std::vector<nodeParam> dependentNodes_coeff;

        public:
            explicit connectionSI(node* src, node* dest, std::vector<nodeParam> &nodesCoeff, const std::string& name) :
            connection(src, dest, name), dependentNodes_coeff(nodesCoeff) {}

            bool updateCoeffSI(const std::string& nameNode, const double& new_coeff) {
                if (new_coeff < 0.0)
                    return false;

                bool found = false;
                for (int i = 0; i < dependentNodes_coeff.size() && !found; ++i) {
                    if (dependentNodes_coeff[i].X_->getName() == nameNode) //quando trovo il nodo di mio interesse 'esco'
                    {
                        dependentNodes_coeff[i].coeff = new_coeff;
                        found = true;
                    }
                }
                return found;
            }

            double computeFlow(double dt) override;

    };
}

#endif //COVID2019_CONNECTIONSI_H
