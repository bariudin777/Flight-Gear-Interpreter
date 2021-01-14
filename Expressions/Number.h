//
// Created by ariel on 21/12/18.
//

#ifndef EX3_NUMBER_H
#define EX3_NUMBER_H


#include "Expression.h"

class Number : public Expression {
    float m_value;
public:
    explicit Number(float num) { m_value = num; }
    virtual ~Number() {}

    virtual float calculate() throw() {
        return m_value;
    }
};

#endif //EX3_NUMBER_H
