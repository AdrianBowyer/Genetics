//============================================================================
// Name        : EvoSim.cpp
// Author      : Adrian Bowyer
// Version     :
// Copyright   : GPL
// Description : Evolutionary simulator
//============================================================================

#include "EvoSim.h"

Genome* environment;

int main()
{

	cout << std::fixed;
	cout << std::setprecision(2);

	cout << "Evolutionary simulation" << endl;

	environment = new Genome(false, NULL);
	Population* pop = new Population();
	for(int i = 0; i < 1000; i++)
		pop->Breed();
	pop->Histogram();

	return 0;
}
