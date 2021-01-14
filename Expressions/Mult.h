//
// Created by ariel on 21/12/18.
//

#ifndef EX3_MULT_H
#define EX3_MULT_H


#include "BinaryExpression.h"

class Mult : public BinaryExpression {

public:
    Mult(Expression *left, Expression *right) : BinaryExpression(left, right) {}

    virtual ~Mult() {}

    virtual float calculate() throw() {
        return m_left->calculate() * m_right->calculate();
    }
};


#endif //EX3_MULT_H
