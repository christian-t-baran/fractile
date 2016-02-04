#include <iostream>

#include "fieldGeometry.h"

// maps a biased distance on the circle to a point between between p2 and p1
double interpolateDistance(int radius, int distance, int stepSize, double p2, double p1, double bias) {
	// calculate biased halfway pt and number of steps
	int halfwayRad = radius * bias;
	int numSteps = radius / stepSize;

	double stepDistance;
	int curStep;

	// calculate differences and biased halfway point
	double dif = p2 - p1;
	double halfwayDif = dif * bias;

	// std::cout << "Difference between points " << dif << std::endl;

	// calculate step distance and corresponding step
	if (distance > halfwayRad) {
		stepSize = (radius - halfwayRad) / (numSteps / 2);
		stepDistance = (p2 - halfwayDif) / (numSteps / 2);
		distance = distance - halfwayRad;
		curStep = distance / stepSize;
	}
	else {
		stepSize = halfwayRad / (numSteps / 2);
		stepDistance = halfwayDif / (numSteps / 2);
		curStep = distance / stepSize;
	}

	// std::cout << "Step distance is " << stepDistance << std::endl;
	// std::cout << "Current step is " << curStep << std::endl;

	double p;

	// calculate position corresponding to current step
	if (bias == 0) {
		p = p1;
	}
	else if (bias == 1) {
		p = p2;
	}
	else if (distance > halfwayRad ) {
		p = halfwayDif + (stepDistance * curStep);
	}
	else {
		p = p1 + (stepDistance * curStep);
	}

	// std::cout << "Interpolated point is " << p << std::endl;

	return p;
}

// maps a biased distance on the circle to a point between between p2 and p1
double interpolateSingle(int radius, int step, int stepSize, double p2, double p1, double bias) {

	int halfwayRad = radius * bias;

	int numSteps = radius / stepSize;
	std::cout << "Number of steps: " << numSteps << std::endl;

	double dif = p2 - p1;
	double halfwayDif = dif * bias;

	double stepDistance;

	if (step > (numSteps / 2)) {
		stepDistance = (p2 - halfwayDif) / (numSteps / 2);
	}
	else {
		stepDistance = (halfwayDif - p1) / (numSteps / 2);
	}

	double p;
	if (bias == 0) {
		p = p1;
	}
	else if (bias == 1) {
		p = p2;
	}
	else if (step > (numSteps / 2)) {
		p = halfwayDif + (stepDistance * (step - (numSteps / 2)));
	}
	else {
		p = p1 + (stepDistance * step);
	}

	return p;
}


