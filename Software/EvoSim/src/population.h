/*
 * population.h
 *
 *  Created on: Dec 17, 2019
 *      Author: Adrian Bowyer
 */

#ifndef POPULATION_H_
#define POPULATION_H_

const int histogramSize = 20;
const int maxHistogram = 50;

class Population
{
public:
	Population();
	void Breed();
	void Cull();
	int EngineerCount();
	int PopulationCount();
	Genome* RandomIndividual();
	double AverageFitness();
	double FitnessStandardDeviation();
	void PrintStatistics();

private:
	void Statistics();
	Genome* FindIndividual(int i);
	Genome* start;
	int fitness[histogramSize];
	int histogramMaximum;
	int populationCount;
	int engineerCount;
	double fitnessAverage;
	double fitnessStandardDeviation;
	bool statisticsValid;
};

inline Genome* Population::RandomIndividual() { return FindIndividual((int)((double)PopulationCount()*Uniform())); }


#endif /* POPULATION_H_ */
