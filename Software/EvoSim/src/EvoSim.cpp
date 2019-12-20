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

bool control = false;

// Remind the user what they can do.

void Prompt()
{
	cout << endl << "Commands:" << endl;
	cout << " b: - increase the population by breeding" << endl;
	cout << " c: - cull low fitness members of the population" << endl;
	cout << " E: - control experiment (no engineering)" << endl;
	cout << " e: - experiment with engineering allowed" << endl;
	cout << " g: - breed and cull many generations" << endl;
	cout << " s: - print statistics" << endl;
	cout << " i: - print genome of a random individual" << endl;
	cout << " h: - print this list" << endl;
	cout << " q: - quit" << endl<< endl;
}

// Decide how to process the results.

void Control()
{
	int populationTarget, generations;

	cout << "Type h for help." << endl;
	while(1)
	{
		cout << "Command: ";
		char c;
		cin >> c;

		switch(c)
		{
		case 'b':
			cout << "The population is " << population->PopulationCount() << " what is the population target? ";
			cin >> populationTarget;
			populationTarget -= population->PopulationCount();
			for(int i = 0; i < populationTarget; i++)
				population->Breed();
			break;

		case 'E':
			control = true;
			cout << "Control experiment - no engineering." << endl;
			break;

		case 'e':
			control = false;
			cout << "Engineering experiment - engineering allowed." << endl;
			break;

		case 'c':
			population->Cull();
			break;

		case 'g':
			cout << "Number of generations: ";
			cin >> generations;
			cout << "Target population: ";
			cin >> populationTarget;
			for(int g = 0; g < generations; g++)
			{
				int diff = population->PopulationCount() - populationTarget;
				for(int d = 0; d < diff; d++)
					population->Breed();
				cout << "Generation " << g << " has average fitness " << population->AverageFitness() << endl;
				population->Cull();
			}
			break;

		case 's':
			population->PrintStatistics();
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
