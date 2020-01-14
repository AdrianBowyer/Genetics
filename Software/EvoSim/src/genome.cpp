/*
 * genome.cpp
 *
 *  Created on: Dec 12, 2019
 *      Author: Adrian Bowyer
 */

#include "EvoSim.h"

Genome::Genome(bool editor, Genome* n)
{
	next = n;
	engineer = editor;
	fitness = -1.0;

	for(int g = 0; g < geneCount; g++)
	{
		genes[g] = Uniform();
	}
}


double Genome::DegreeOfMatch(Genome* genome)
{
	double match = 0.0;
	for(int g = 0; g < geneCount; g++)
		match += fabs(genes[g] - genome->genes[g]);
	return 1.0 - match/(double)geneCount;
}

// Lazy evaluation

double Genome::Fitness()
{
	if(fitness >= 0.0)
		return fitness;
	fitness = DegreeOfMatch(environment);
	return fitness;
}


void Genome::Mutate()
{
	fitness = -1.0;
	for(int g = 0; g < geneCount; g++)
	{
		if(Uniform() < mutateProportion)
		{
			genes[g] += Gaussian(mutateThisMuch);
			if(genes[g] < 0.0)
				genes[g] = 0.0;
			if(genes[g] > 1.0)
				genes[g] = 1.0;
		}
	}

	if(Uniform() < mutateProportion)
		engineer = !engineer;
}


void Genome::Edit()
{
	if(controlExperiment)
		return;

	if(!engineer)
		return;

	fitness = -1.0;

	for(int g = 0; g < geneCount; g++)
	{
		if(Uniform() < engineerProportion)
		{
			double shift = fabs(Gaussian(engineerThisMuch));
			if(environment->genes[g] < genes[g])
				genes[g] -= shift;
			else
				genes[g] += shift;
			if(genes[g] < 0.0)
				genes[g] = 0.0;
			if(genes[g] > 1.0)
				genes[g] = 1.0;
		}
	}
}


Genome* Genome::ChildWith(Genome* parent2)
{
	Genome* child = new Genome(false, next);

	for(int g = 0; g < geneCount; g++)
	{
		if(Uniform() > 0.5)
			child->genes[g] = genes[g];
		else
			child->genes[g] = parent2->genes[g];
	}

	if(engineer && parent2->engineer)
	{
		child->engineer = true;
	} else if (engineer || parent2->engineer)
	{
		child->engineer = (Uniform() > 0.5);
	}
	child->Mutate();
	child->Edit();
	next = child;
	return child;
}


void Genome::PrintGenome()
{
	cout << endl << "Genome of ";
	if(engineer)
		cout << "an engineer" << endl;
	else
		cout << "a non engineer" << endl;
	for(int g = 0; g < geneCount; g++)
	{
		cout << genes[g] << ' ';
		if(!((g+1)%20))
			cout << endl;
	}
	cout << endl << endl;
}


void Genome::Unlink(Genome* previous)
{
	if(previous)
	{
		previous->next = next;
	}

	delete this;
}


