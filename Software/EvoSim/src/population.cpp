/*
 * population.cpp
 *
 *  Created on: Dec 17, 2019
 *      Author: Adrian Bowyer
 */

#include "EvoSim.h"

Population::Population()
{
	// Adam & Eve

	start = new Genome(false, NULL);
	start = new Genome(false, start);

	histogramMaximum = 0;
	populationCount = 0;
	engineerCount = 0;
	fitnessAverage = 0.0;
	fitnessStandardDeviation = 0.0;
	statisticsValid = false;
}

void Population::Breed()
{
	Genome* parent1 = RandomIndividual();
	Genome* parent2 = parent1;
	int count = 0;
	while(parent2 == parent1 && count < 10)
	{
		parent2 = RandomIndividual();
		count++;
	}
	if(count >= 10)
		cout << "Breed: can't find breeding pair!" << endl;
	parent1->ChildWith(parent2);
	statisticsValid = false;
}

void Population::Cull()
{
	Genome* weakest = NULL;
	double fitness = 1.0;
	Genome* g = start;
	Genome* previous = NULL;
	Genome* p = NULL;;
	while(g)
	{
		double f = g->Fitness();
		if(f < fitness)
		{
			weakest = g;
			fitness = f;
			previous = p;
		}
		p = g;
		g = g->Next();
	}

	if(weakest == start)
		start = weakest->Next();;
	weakest->Unlink(previous);

	statisticsValid = false;
}

int Population::EngineerCount()
{
	if(statisticsValid)
		return engineerCount;
	Statistics();
	return engineerCount;
}

int Population::PopulationCount()
{
	if(statisticsValid)
		return populationCount;
	Statistics();
	return populationCount;
}

double Population::AverageFitness()
{
	if(statisticsValid)
		return fitnessAverage;
	Statistics();
	return fitnessAverage;
}

double Population::FitnessStandardDeviation()
{
	if(statisticsValid)
		return fitnessStandardDeviation;
	Statistics();
	return fitnessStandardDeviation;
}

void Population::PrintStatistics()
{
	if(!statisticsValid)
		Statistics();

	cout << endl << "Population: " << PopulationCount() << endl << "Engineers: " << engineerCount << endl;
	cout << endl << "Average fitness: " << fitnessAverage << endl << "Fitness standard deviation: " << fitnessStandardDeviation << endl << endl;
	for(int f = 0; f < histogramSize; f++)
	{
		cout << (double)f/(double)histogramSize << ' ';
		for(int a = 0; a < maxHistogram*round((double)fitness[f]/(double)histogramMaximum); a++)
			cout << '*';
		cout << endl;
	}
	cout << endl;
}


void Population::Statistics()
{
//	if(statisticsValid)  // Should be OK. But better safe than sorry...
//		return;

	for(int f = 0; f < histogramSize; f++)
		fitness[f] = 0;

	Genome* g = start;

	populationCount = 0;
	engineerCount = 0;
	fitnessAverage = 0.0;
	fitnessStandardDeviation = 0.0;

	while(g)
	{
		populationCount++;
		if(g->IAmAnEngineer())
			engineerCount++;
		double f = g->Fitness();
		fitnessAverage += f;
		fitnessStandardDeviation += f*f;
		int fit = round(f*(double)histogramSize);
		fitness[fit]++;
		if(fitness[fit] > histogramMaximum)
			histogramMaximum = fitness[fit];
		g = g->Next();
	}

	fitnessAverage = fitnessAverage/(double)populationCount;
	fitnessStandardDeviation = sqrt(fitnessStandardDeviation/(double)populationCount - fitnessAverage*fitnessAverage);

	statisticsValid = true;
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



