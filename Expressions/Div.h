//
// Created by ariel on 21/12/18.
//

#ifndef EX3_DIV_H
#define EX3_DIV_H

#include "BinaryExpression.h"

class Div : public BinaryExpression {

public:
    Div(Expression *left, Expression *right) : BinaryExpression(left, right) {};

    virtual float calculate() throw () {
        double denominator = m_right->calculate();
        if (denominator == 0) {
            throw invalid_argument("Cannot divide by 0");
        }
        return m_left->calculate() / denominator;
    }

    virtual ~Div() {}
};


#endif //EX3_DIV_H
