//============================================================================
// Name        : EvoSim.cpp
// Author      : Adrian Bowyer
// Version     :
// Copyright   : GPL
// Description : Evolutionary simulator
//============================================================================

#include <iostream>
#include "genome.h"

Genome* environment;

int main()
{
	cout << "Evolutionary simulation" << endl;

	environment = new Genome(false);

	return 0;
}
