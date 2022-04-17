//
// Created by Konrad on 04.01.2022.
//

#ifndef MAX3SAT_PROBLEM_H
#define MAX3SAT_PROBLEM_H
#pragma once
#include "Clause.h"
#include <string>
#include <vector>


using namespace std;

class CProblem
{
public:
    CProblem();

    virtual ~CProblem();

    bool  bLoad(string sourcePath);

    double dEvaluate(int* genotype);

    int iGetNumberVariables() { return(numberOfVariables); }
    int iGetNumberClauses() { return(numberOfClauses); }

private:
    vector<Clause*> clauses;
    int numberOfClauses;
    int numberOfVariables;

protected:

};//class CProblem

#endif //MAX3SAT_PROBLEM_H
