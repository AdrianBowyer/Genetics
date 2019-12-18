//============================================================================
// Name        : EvoSim.cpp
// Author      : Adrian Bowyer
// Version     :
// Copyright   : GPL
// Description : Evolutionary simulator
//============================================================================

#include "EvoSim.h"

Genome* environment;

Population* population;

// Remind the user what they can do.

void Prompt()
{
	cout << endl << "Commands:" << endl;
	cout << " b: - increase the population by breeding" << endl;
	cout << " c: - cull low fitness members of the population" << endl;
	cout << " g: - breed and cull many generations" << endl;
	cout << " s: - print statistics" << endl;
	cout << " i: - print genome of a random individual" << endl;
	cout << " h: - print this list" << endl;
	cout << " q: - quit" << endl<< endl;
}

// Decide how to process the results.

void Control()
{
	int populationCount, generations;
	double f;

	cout << "Type h for help." << endl;
	while(1)
	{
		cout << "Command: ";
		char c;
		cin >> c;

		switch(c)
		{
		case 'b':
			cout << "Number of children to breed: ";
			cin >> populationCount;
			for(int i = 0; i < populationCount; i++)
				population->Breed();
			break;

		case 'c':
			cout << "Fitness value below which to cull: ";
			cin >> f;
			population->Cull(f);
			break;

		case 'g':
			cout << "Number of generations: ";
			cin >> generations;
			cout << "Fitness value below which to cull: ";
			cin >> f;
			cout << "Target population: ";
			cin >> populationCount;
			for(int g = 0; g < generations; g++)
			{
				int diff = population->PopulationCount() - populationCount;
				for(int d = 0; d < diff; d++)
					population->Breed();
				population->Cull(f);
			}
			break;

		case 's':
			population->Histogram();
			break;

		case 'i':
			population->RandomIndividual()->PrintGenome();
			break;

		case 'q':
			return;

		default:
			cout << endl << "Unrecognised command - " << c << endl;
		case 'h':
			Prompt();
		}
	}
}



int main()
{

	cout << std::fixed;
	cout << std::setprecision(4);

	cout << "Evolutionary simulation" << endl;

	environment = new Genome(false, NULL);
	population = new Population();

	Prompt();
	Control();

	cout << "Bye!" << endl;

	return 0;
}
