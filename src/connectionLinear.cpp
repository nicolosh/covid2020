//
// Created by nicol on 23/12/2020.
//

#include "../include/covid/connectionLinear.h"

double covid::connectionLinear::computeFlow(double dt) {
    flow_ = coefficientLC * src_->getValue() * dt;
    return flow_;
}
