//
// Created by nicol on 23/12/2020.
//

#ifndef COVID2019_CONNECTIONLINEAR_H
#define COVID2019_CONNECTIONLINEAR_H


#include "covid/connection.h"

namespace covid {

    class connectionLinear : public connection{
    protected:
        std::string connectionName;
        double coefficientLC; //LC = linear connection

    public:
        explicit connectionLinear(node* src, node* dest, const std::string& name, double coeff) :
        connection(src, dest, name), coefficientLC(coeff){}

        double computeFlow(double dt) override;
        const std::string& getConnectionName() const { return connectionName; }

        bool updateCoeffLC(const double& new_coeff){
            if(new_coeff < 0.0)
                return false;

            coefficientLC = new_coeff;
            return true;
        }

    };
}

#endif //COVID2019_CONNECTIONLINEAR_H
