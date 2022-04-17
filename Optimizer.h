//
// Created by Konrad on 04.01.2022.
//

#ifndef MAX3SAT_OPTIMIZER_H
#define MAX3SAT_OPTIMIZER_H
#pragma once

#include "Problem.h"

#include <random>
#include <vector>

using namespace std;
const int SIZE_OF_POPULATION = 12;
const int SIZE_OF_TOURNAMENT= 4;
const double PROBABILITY_OF_CROSSOVER = 0.65;
const double PROBABILITY_OF_MUTATION = 0.01;
const double CHANGE_PROBABILITY = 0.09;
const int ITERATION_WITHOUT_CHANGE= 2500;


class  CIndividual;

class COptimizer
{
public:
    COptimizer(CProblem *pcProblem);
    ~COptimizer();

    void vInitialize();
    void vRunIteration();

    CIndividual  *pcGetBestFound() { return bestFound; }


private:
    double changeProbability;
    int iterationWithoutChange;
    int bestCompletedClauses;
    int numberOfVariables;
    CProblem *problem;
    CIndividual  *bestFound;
    vector<CIndividual *>  population;

    int randomIntSize();
    CIndividual* chooseParent();
    void evaluatePopulation();
    void deletePopulation();
};//class COptimizer

class  CIndividual
{
public:
    CIndividual(CProblem *pcProblem);
    CIndividual(const CIndividual &other);
    ~CIndividual();

    void crossover(CIndividual* parent1, CIndividual* parent2,CIndividual* child2,double change);
    void mutation(double change);
    double fitness(int numberOfClauses);

    CIndividual *clone(){ return new CIndividual(*this);};
    void fillGenotypeRandom();
    void setCompletedClauses(int completed){completedClauses=completed;}
    int getCompletedClauses(){return completedClauses;}

    int* piGetResultAsTable(){return genotype;}


private:
    CProblem *problem;
    void optimize();
    int numberOfVariables;
    double randomDouble(int max);
    int* genotype;
    int completedClauses;

};//class  CIndividual


#endif //MAX3SAT_OPTIMIZER_H
