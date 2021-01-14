//
// Created by ariel on 21/12/18.
//

#ifndef EX3_MINUS_H
#define EX3_MINUS_H


#include "BinaryExpression.h"

class Minus : public BinaryExpression {

public:
    Minus(Expression *left, Expression *right) : BinaryExpression(left, right) {}
    ~Minus() {}
    virtual float calculate() throw() {
        return m_left->calculate() - m_right->calculate();
    }
};


#endif //EX3_MINUS_H
