//
// Created by Konrad on 05.01.2022.
//

#ifndef MAX3SAT_CLAUSE_H
#define MAX3SAT_CLAUSE_H

#include <iostream>
using namespace std;
const int CONSTANT_MAX3SAT= 3;

class Clause {
public:
    Clause();
    ~Clause();

    void print();
    int getVariable(int offset);
    int addNewVariable(int offset,string variable);
    bool isTrue(int* gen);


private:
    bool trueEachVariable(int which, int* gen);
    int* variables;
    bool* isNegated;
};


#endif //MAX3SAT_CLAUSE_H
