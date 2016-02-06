#include <iostream>

#include "fieldGeometry.h"

// maps an unbiased distance on the circle to a point between p2 and p1
double interpolateDistanceNoBias(int radius, int distance, int stepSize, double p2, double p1) {
	// calculate biased halfway pt and number of steps
	int numSteps = radius / stepSize;

	// calculate differences and biased halfway point
	double dif = p2 - p1;

	double circleSlope;
	double labSlope;
	int curStep;

	circleSlope = radius / (double)numSteps;
	labSlope = dif / (double)numSteps;
	curStep = distance / circleSlope;

	double p = p1 + (labSlope * curStep);

	return p;
}

// maps a biased distance on the circle to a point between between p2 and p1
double interpolateDistance(int radius, int distance, int stepSize, double p2, double p1, double bias) {
	// calculate biased halfway pt and number of steps
	int halfwayRad = radius * bias;
	int numSteps = radius / stepSize;

	// calculate differences and biased halfway point
	double dif = p2 - p1;
	double halfwayDif = dif / 2.0;

	double circleSlope;
	double labSlope;
	int curStep;

	// calculate step distance and corresponding step
	if (distance > halfwayRad) {
		circleSlope = (radius - halfwayRad) / (numSteps / 2.0);
		labSlope = (dif - halfwayDif) / (numSteps / 2.0);
		curStep = (distance - halfwayRad) / circleSlope;
	}
	else {
		circleSlope = halfwayRad / (numSteps / 2.0);
		labSlope = (halfwayDif) / (numSteps / 2.0);
		curStep = distance / circleSlope;
	}

	double p;

	// calculate position corresponding to current step
	if (bias == 0) {
		p = p1;
	}
	else if (bias == 1) {
		p = p2;
	}
	else if (distance > halfwayRad ) {
		p = p1 + halfwayDif + (labSlope * curStep);
	}
	else {
		p = p1 + (labSlope * curStep);
	}

	return p;
}

// maps a biased distance on the circle to a point between between p2 and p1
double interpolateStep(int radius, int step, int numSteps, double p2, double p1, double bias) {
	int halfwayRad = radius * bias;

	double dif = p2 - p1;
	double halfwayDif = dif * bias;

	double stepDistance;

	// calculates slope by step
	if (step > (numSteps / 2) ) {
		stepDistance = (dif - halfwayDif) / (numSteps / 2);
	}
	else {
		stepDistance = halfwayDif / (numSteps / 2);
	}

	double p;

	// calculate position according to current step
	if (step > (numSteps / 2)) {
		p = p1 + halfwayDif + (stepDistance * (step - (numSteps / 2)));
	}
	else {
		p = p1 + (stepDistance * step);
	}

	return p;
}


