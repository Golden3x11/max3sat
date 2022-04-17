//
// Created by Konrad on 05.01.2022.
//

#include <string>
#include "Clause.h"


Clause::Clause() {
    variables= new int[CONSTANT_MAX3SAT];
    isNegated= new bool[CONSTANT_MAX3SAT];
}

Clause::~Clause() {
    delete[] variables;
    delete[] isNegated;
}

bool Clause::isTrue(int* gen) {
    return trueEachVariable(0,gen);
}
bool Clause::trueEachVariable(int which, int* gen){
    if(which < CONSTANT_MAX3SAT) {
        return isNegated[which] == !gen[variables[which]] || trueEachVariable((which + 1), gen);
    }
    return false;
}

int Clause::addNewVariable(int offset, string variable) {
    if (variable[0]=='-')
        isNegated[offset]= true;
    else
        isNegated[offset]= false;

    int x= abs(stoi(variable));
    variables[offset]= x;
    return x;
}

int Clause::getVariable(int offset) {
    return variables[offset];
}

void Clause::print() {
    cout<<"( ";
    for(int i=0;i < CONSTANT_MAX3SAT;i++){
        string x= isNegated[i]?"-":"";
        cout<<x<<variables[i]<<"  ";
    }
    cout<<")\n";
}

