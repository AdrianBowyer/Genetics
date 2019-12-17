/*
 * population.cpp
 *
 *  Created on: Dec 17, 2019
 *      Author: Adrian Bowyer
 */

#include "EvoSim.h"

Population::Population()
{
	start = new Genome(false, NULL);
}

void Population::Breed()
{
	int number = PopulationCount();

	// NB this allows self-fertilisation

	Genome* parent1 = FindIndividual((int)((double)number*Uniform()));
	Genome* parent2 = FindIndividual((int)((double)number*Uniform()));
	Genome* child = parent1->ChildWith(parent2);
}

void Population::Cull(double minimumFitness)
{

}

int Population::EngineerCount()
{
	Genome* g = start;
	int engineerCount = 0;
	while(g)
	{
		if(g->IAmAnEngineer())
			engineerCount++;
		g = g->Next();
	}
	return engineerCount;
}

int Population::PopulationCount()
{
	Genome* g = start;
	int populationCount = 0;
	while(g)
	{
		populationCount++;
		g = g->Next();
	}
	return populationCount;
}

void Population::Histogram()
{
	int fitness[histogramSize];
	for(int f = 0; f < histogramSize; f++)
		fitness[f] = 0;

	Genome* g = start;
	int populationCount = 0;
	int engineerCount = 0;
	int histogramMaximum = 0;
	while(g)
	{
		populationCount++;
		if(g->IAmAnEngineer())
			engineerCount++;
		int fit = round(g->Fitness()*(double)histogramSize);
		fitness[fit]++;
		if(fitness[fit] > histogramMaximum)
			histogramMaximum = fitness[fit];
		g = g->Next();
	}


	cout << endl << "Population: " << populationCount << endl << "Engineers: " << engineerCount << endl << endl;
	for(int f = 0; f < histogramSize; f++)
	{
		cout << (double)f/(double)histogramSize << ' ';
		for(int a = 0; a < maxHistogram*round((double)fitness[f]/(double)histogramMaximum); a++)
			cout << '*';
		cout << endl;
	}
	cout << endl;

}

Genome* Population::FindIndividual(int i)
{
	Genome* g = start;
	while(g && i > 0)
	{
		i--;
		g = g->Next();
	}
	if(!g)
	{
		cout << "FindIndividual " << i << " - ran off the end of the list!" << endl;
		return start;
	}
	return g;
}


