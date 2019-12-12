/*
 * genome.cpp
 *
 *  Created on: Dec 12, 2019
 *      Author: Adrian Bowyer
 */

#include "genome.h"

Genome::Genome(bool editor)
{
	engineer = editor;
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
	return match/(double)geneCount;
}


void Genome::Mutate()
{
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
}


void Genome::Edit()
{
	if(!engineer)
		return;

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
	Genome* child = new Genome(false);

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
	return child;
}


