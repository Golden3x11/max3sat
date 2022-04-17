//
// Created by Konrad on 04.01.2022.
//

#include "Problem.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <random>
#include <stdexcept>


CProblem::CProblem() {
    numberOfClauses= 0;
    numberOfVariables= 0;
}

CProblem::~CProblem() {
    for(int i=0; i< numberOfClauses;i++)
        delete clauses[i];
}

bool CProblem::bLoad(string sourcePath) {
    ifstream file(sourcePath);
    if(!file)
        return false;

    string line;

    while(!file.eof()){
        getline(file, line);
        if (line[0] == '(') {
            Clause *clause= new Clause();
            int i = 0;
            for(;i< CONSTANT_MAX3SAT;) {
                size_t pos = 0;
                line.erase(0, 2);

                while ((pos = line.find("  ")) != string::npos) {
                    int x = clause->addNewVariable(i, line.substr(0, pos));
                    if (x > numberOfVariables)
                        numberOfVariables = x;
                    line.erase(0, pos + 2);
                    i++;
                }
                if(i < CONSTANT_MAX3SAT){
                    getline(file, line);
                    if (line[0] != '(')
                        i=CONSTANT_MAX3SAT;
                }
            }
            numberOfClauses++;

            clause->print();
            clauses.push_back(clause);
        }
    }

    numberOfVariables++;
    file.close();
    return true;
}

double CProblem::dEvaluate(int* genotype) {
    int solution= 0;
    for(int i=0; i< numberOfClauses; i++){
        Clause *clause =clauses[i];
        if(clause->isTrue(genotype)){
            solution++;
        }
    }

    return solution;
}




