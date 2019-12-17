/*
 * population.h
 *
 *  Created on: Dec 17, 2019
 *      Author: Adrian Bowyer
 */

#ifndef POPULATION_H_
#define POPULATION_H_

const int histogramSize = 30;
const int maxHistogram = 50;

class Population
{
public:
	Population();
	void Breed();
	void Cull(double minimumFitness);
	int EngineerCount();
	int PopulationCount();
	void Histogram();

private:
	Genome* FindIndividual(int i);
	Genome* start;
};



#endif /* POPULATION_H_ */
