//
// Created by Konrad on 04.01.2022.
//

#include "Optimizer.h"



CIndividual::CIndividual(CProblem *pcProblem) {
    problem= pcProblem;
    numberOfVariables= problem->iGetNumberVariables();
    completedClauses=0;
    genotype= new int [numberOfVariables];
}

CIndividual::CIndividual(const CIndividual &other) {
    numberOfVariables=other.numberOfVariables;
    completedClauses=other.completedClauses;
    genotype= new int [numberOfVariables];
    for(int i=0; i < numberOfVariables; i++)
        genotype[i]=other.genotype[i];
}


CIndividual::~CIndividual() {
    delete[] genotype;
}

double CIndividual::randomDouble(int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, max);

    return dis(gen);
}

double CIndividual::fitness(int numberOfClauses) {
    return (double )completedClauses / numberOfClauses;
}

void CIndividual::mutation(double changeProb) {
    for(int i=0; i < numberOfVariables; i++){
        if(randomDouble(1) < PROBABILITY_OF_MUTATION + changeProb)
            genotype[i]= !genotype[i];
    }
}

void CIndividual::crossover(CIndividual *parent1, CIndividual *parent2, CIndividual *child2, double changeProb) {

    if(randomDouble(1) < PROBABILITY_OF_CROSSOVER + changeProb) {
        int pointCrossover = static_cast<int>( randomDouble(numberOfVariables));
//        int pointC2= randomDouble(numberOfVariables);
//        if(pointC2 < pointCrossover) {
//            int pT = pointC2;
//            pointC2=pointCrossover;
//            pointCrossover=pT;
//        }
        for (int i = 0; i < numberOfVariables; i++) {
            //if(i >= pointCrossover && i< pointC2) {
            if(i >= pointCrossover) {
                child2->genotype[i] = parent1->genotype[i];
                this->genotype[i] = parent2->genotype[i];
            } else {
                this->genotype[i] = parent1->genotype[i];
                child2->genotype[i] = parent2->genotype[i];
            }
        }
    }
    else{
        for (int i = 0; i < numberOfVariables; i++) {
            this->genotype[i] = parent1->genotype[i];
            child2->genotype[i] = parent2->genotype[i];
        }
    }
//    this->optimize();
//    child2->optimize();
}

void CIndividual::fillGenotypeRandom() {

    for (int i = 0; i < numberOfVariables; i++) {
        bool x = randomDouble(1) >= 0.5;
        genotype[i] = x;
    }
}

void COptimizer::vInitialize() {
    bestFound= new CIndividual(problem);

    for(int i=0; i< SIZE_OF_POPULATION;i++){
        CIndividual *individual= new CIndividual(problem);
        individual->fillGenotypeRandom();
        population.push_back(individual);
    }

    evaluatePopulation();
}

void COptimizer::vRunIteration() {
    vector<CIndividual *>  newPopulation;
    newPopulation.push_back(new CIndividual(*bestFound));
    CIndividual* randomInd= new CIndividual(problem);
    randomInd->fillGenotypeRandom();
    newPopulation.push_back(randomInd);

    while(newPopulation.size() < population.size()){
        CIndividual* parent1= chooseParent();
        CIndividual* parent2= chooseParent();
        CIndividual* child1= new CIndividual(problem);
        CIndividual* child2= new CIndividual(problem);

        child1->crossover(parent1,parent2,child2,changeProbability);
        child1->mutation(changeProbability);
        child2->mutation(changeProbability);
        newPopulation.push_back(child1);
        newPopulation.push_back(child2);
    }

    deletePopulation();
    population= newPopulation;
    evaluatePopulation();

    if(bestCompletedClauses == bestFound->getCompletedClauses()){
        iterationWithoutChange++;
        if(iterationWithoutChange% ITERATION_WITHOUT_CHANGE == 0) {
            if (changeProbability == 0) {
                changeProbability = CHANGE_PROBABILITY;
                //cout << "change " << changeProbability << endl;
            }
            else {
                changeProbability = 0;
                //cout << "change " << changeProbability << endl;
            }
        }
    }else{
        bestCompletedClauses= bestFound->getCompletedClauses();
        iterationWithoutChange=0;
        changeProbability=0;
        //cout<<"better "<<bestCompletedClauses<<endl;
    }
}

COptimizer::COptimizer(CProblem *pcProblem) {
    changeProbability=0;
    bestCompletedClauses=0;
    iterationWithoutChange=0;
    problem=pcProblem;
    numberOfVariables= problem->iGetNumberVariables();
}

COptimizer::~COptimizer() {
    delete bestFound;
    deletePopulation();
}

void COptimizer::deletePopulation() {
    for(int i=0; i<SIZE_OF_POPULATION;i++)
        delete population[i];
}


void COptimizer::evaluatePopulation() {
    int bestFoundCompletedClauses= bestFound->getCompletedClauses();
    for(int i=0; i<SIZE_OF_POPULATION;i++){
        if(population[i]->getCompletedClauses() == 0){
            population[i]->setCompletedClauses(problem->dEvaluate(population[i]->piGetResultAsTable()));
            if(population[i]->getCompletedClauses() >= bestFoundCompletedClauses){
                delete bestFound;
                bestFound=population[i]->clone();
                bestFoundCompletedClauses=bestFound->getCompletedClauses();
            }
        }
    }

}

CIndividual *COptimizer::chooseParent() {
    CIndividual* parent= population[randomIntSize()];
    for(int i=1; i<SIZE_OF_TOURNAMENT;i++){
        CIndividual* potentialParent= population[randomIntSize()];
        if(potentialParent->getCompletedClauses()> parent->getCompletedClauses())
            parent= potentialParent;
    }
    return parent;
}

int COptimizer::randomIntSize() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, SIZE_OF_POPULATION);
    return int(floor(dis(gen)));
}

void CIndividual::optimize()
{
    int before, after;

    for (int i = 0; i < numberOfVariables; ++i) {
        before = problem->dEvaluate(genotype);
        genotype[i] = (genotype[i] + 1) % 2;
        after = problem->dEvaluate(genotype);

        if (before >= after)
            genotype[i] = (genotype[i] + 1) % 2;
    }
}

