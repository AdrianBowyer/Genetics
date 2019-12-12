/*
 * genome.h
 *
 *  Created on: Dec 12, 2019
 *      Author: Adrian Bowyer
 */

#ifndef GENOME_H_
#define GENOME_H_

#include <random>

using namespace std;

const int geneCount = 100;
const double engineerProportion = 0.04;
const double mutateProportion = 0.04;
const double engineerThisMuch = 0.1;
const double mutateThisMuch = 0.1;

double Uniform();
double Gaussian(double sd);

class Genome
{
public:
	Genome(bool editor);
	double DegreeOfMatch(Genome* genome);
	double Fitness();
	void Mutate();
	void Edit();
	Genome* ChildWith(Genome* parent2);

private:
	double genes[geneCount];
	bool engineer;

};

extern Genome* environment;

inline double Genome::Fitness() { return DegreeOfMatch(environment); }



#endif /* GENOME_H_ */
