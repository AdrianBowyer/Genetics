/*
 * genome.h
 *
 *  Created on: Dec 12, 2019
 *      Author: Adrian Bowyer
 */

#ifndef GENOME_H_
#define GENOME_H_

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
	Genome(bool editor, Genome* n);
	double DegreeOfMatch(Genome* genome);
	double Fitness();
	void Mutate();
	void Edit();
	Genome* ChildWith(Genome* parent2);
	Genome* Next();
	Genome* Previous();
	bool IAmAnEngineer();
	void Unlink(Genome* previous);
	void PrintGenome();

private:
	double genes[2][geneCount];
	bool engineer;
	Genome* next;

};

extern Genome* environment;
extern bool control;

// Lazy evaluation

inline Genome* Genome::Next() { return next; }
inline bool Genome::IAmAnEngineer() { return engineer; }

#endif /* GENOME_H_ */
