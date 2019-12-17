/*
 * random.cpp
 *
 *  Created on: Dec 12, 2019
 *      Author: Adrian Bowyer
 */

#include "EvoSim.h"

random_device rd;
mt19937 e2(rd());
uniform_real_distribution<> dist(0, 1);
normal_distribution<> gaussian(0, 1);

double Uniform()
{
	return dist(e2);
}

double Gaussian(double sd)
{
	return gaussian(e2)*sd;
}



