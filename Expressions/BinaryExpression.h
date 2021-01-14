//
// Created by ariel on 21/12/18.
//

#ifndef EX3_BINARYEXPRESSION_H
#define EX3_BINARYEXPRESSION_H


#include "Expression.h"

class BinaryExpression : public Expression {
protected:
    Expression *m_left;
    Expression *m_right;

public:
    BinaryExpression(Expression *left, Expression *right) {
        // During SYA, the left member was created before the right one but it should be the opposite, so adjust
        m_left = right;
        m_right = left;
    }

    virtual ~BinaryExpression() {}

    virtual float calculate() throw() = 0;
};


#endif //EX3_BINARYEXPRESSION_H
