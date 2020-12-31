//
// Created by nicol on 23/12/2020.
//

#include "../include/covid/connectionSI.h"

double covid::connectionSI::computeFlow(double dt) {
    for (int i = 0; i < dependentNodes_coeff.size(); ++i)
    {
        flow_ += dependentNodes_coeff[i].X_->getValue() * dependentNodes_coeff[i].coeff;
    }
    return (flow_ * src_->getValue() * dt);
}
