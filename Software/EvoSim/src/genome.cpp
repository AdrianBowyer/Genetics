/*
 * genome.cpp
 *
 *  Created on: Dec 12, 2019
 *      Author: Adrian Bowyer
 */

#include "EvoSim.h"

// Negative values are recessive

Genome::Genome(bool editor, Genome* n)
{
	engineer = editor;
	for(int g = 0; g < geneCount; g++)
	{
		genes[0][g] = 2.0*Uniform() - 1.0;
		genes[1][g] = 2.0*Uniform() - 1.0;
	}
	next = n;
}


double Genome::DegreeOfMatch(Genome* genome)
{
	double match = 0.0;
	for(int g = 0; g < geneCount; g++)
	{
		match += fabs(genes[0][g] - genome->genes[0][g]);
		match += fabs(genes[1][g] - genome->genes[1][g]);
	}
	return 0.25*match/(double)geneCount;
}

// TODO Fix this so it makes sense.
// If an allele is dominant and it matches either in the environment that's good.
// If it doesn't match either that's bad.

double Genome::Fitness()
{
	double match = 0.0;
	double d0, d1;
	for(int g = 0; g < geneCount; g++)
	{
		if(genes[0][g] > 0)
		{
			d0 = fabs(genes[0][g] - environment->genes[0][g]);
			d1 = fabs(genes[0][g] - environment->genes[1][g]);
			if(d0 > d1)
				match += d0;
			else
				match += d1;
		} else
			match += fabs(genes[0][g] - environment->genes[0][g]);

		if(genes[1][g] > 0)
		{
			d0 = fabs(genes[1][g] - environment->genes[0][g]);
			d1 = fabs(genes[1][g] - environment->genes[1][g]);
			if(d0 > d1)
				match += d0;
			else
				match += d1;
		} else
			match += fabs(genes[1][g] - environment->genes[1][g]);
	}
	return 0.25*match/(double)geneCount;
}


void Genome::Mutate()
{
	for(int g = 0; g < geneCount; g++)
	{
		if(Uniform() < mutateProportion)
		{
			genes[0][g] += Gaussian(mutateThisMuch);
			if(genes[0][g] < -1.0)
				genes[0][g] = -1.0;
			if(genes[0][g] > 1.0)
				genes[0][g] = 1.0;
		}
		if(Uniform() < mutateProportion)
		{
			genes[1][g] += Gaussian(mutateThisMuch);
			if(genes[1][g] < -1.0)
				genes[1][g] = -1.0;
			if(genes[1][g] > 1.0)
				genes[1][g] = 1.0;
		}
	}

	if(Uniform() < mutateProportion)
		engineer = !engineer;
}


void Genome::Edit()
{
	if(control)
		return;

	if(!engineer)
		return;

	for(int g = 0; g < geneCount; g++)
	{
		if(Uniform() < engineerProportion)
		{
			double shift = fabs(Gaussian(engineerThisMuch));
			if(environment->genes[0][g] < genes[0][g])
				genes[0][g] -= shift;
			else
				genes[0][g] += shift;
			if(genes[0][g] < -1.0)
				genes[0][g] = -1.0;
			if(genes[0][g] > 1.0)
				genes[0][g] = 1.0;
		}
		if(Uniform() < engineerProportion)
		{
			double shift = fabs(Gaussian(engineerThisMuch));
			if(environment->genes[1][g] < genes[1][g])
				genes[1][g] -= shift;
			else
				genes[1][g] += shift;
			if(genes[1][g] < -1.0)
				genes[1][g] = -1.0;
			if(genes[1][g] > 1.0)
				genes[1][g] = 1.0;
		}
	}
}


Genome* Genome::ChildWith(Genome* parent2)
{
	Genome* child = new Genome(false, next);

	for(int g = 0; g < geneCount; g++)
	{
		if(Uniform() > 0.5)
			child->genes[0][g] = genes[0][g];
		else
			child->genes[0][g] = parent2->genes[0][g];
		if(Uniform() > 0.5)
			child->genes[1][g] = genes[1][g];
		else
			child->genes[1][g] = parent2->genes[1][g];
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
		cout << '|' << genes[0][g] << ' ' << genes[1][g] << '|';
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


