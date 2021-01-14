//
// Created by ariel on 21/12/18.
//

#ifndef EX3_PLUS_H
#define EX3_PLUS_H


#include "Expression.h"
#include "BinaryExpression.h"

class Plus : public BinaryExpression {

public:
    Plus(Expression *left, Expression *right) : BinaryExpression(left, right) {}

    virtual ~Plus() {}

    virtual float calculate() throw() {
        return m_left->calculate() + m_right->calculate();
    }
};


#endif //EX3_PLUS_H
