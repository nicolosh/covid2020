//
// Created by nicol on 23/12/2020.
//

#include "../include/covid/connectionSI.h"

double covid::connectionSI::computeFlow(double dt) {
    flow_ = 0.0;
    for (int i = 0; i < dependentNodes_coeff.size(); ++i)
    {
        flow_ += dependentNodes_coeff[i].X_->getValue() * dependentNodes_coeff[i].coeff;
    }
    flow_ = flow_ * src_->getValue() * dt;
    return flow_;
}
