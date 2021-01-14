//
// Created by ariel on 21/12/18.
//

#ifndef EX3_EXPRESSION_H
#define EX3_EXPRESSION_H


class Expression {

public:
    virtual ~Expression() {}

    virtual float calculate() throw() =0;
};


#endif //EX3_EXPRESSION_H
