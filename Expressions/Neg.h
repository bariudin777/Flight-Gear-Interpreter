//
// Created by ariel on 24/12/18.
//

#ifndef TESTING_NEG_H
#define TESTING_NEG_H


#include "Expression.h"

class Neg : public Expression {
    Expression *exp;

public:
    Neg(Expression *e) {
        exp = e;
    }

    virtual ~Neg() {}

    virtual float calculate() throw() {
        return exp->calculate() * (-1);
    }
};


#endif //TESTING_NEG_H
