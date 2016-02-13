#include <iostream>

#include "../colours/colour.h"
#include "fieldGeometry.h"

// converts radian value to integer degree
int degToRad(double a) {
	return std::floor(a * (180 / PI));
}


// returns angle of an x, y point on the Cartesian plane around the x axis in radians
int getAngle(int x, int y) {
	double angle;
	
	// origin
	if ( (x == 0) && (y == 0) ) {
		angle = 0;
	}	
	// quadrant 1
	else if ((x >= 0) && (y >= 0)) {
		// if on x-axis
		if (y == 0) {
			angle = 0;
		}
		// if on y-axis
		else if (x == 0) {
			angle = PI / 2.0;
		}
		else {
			angle = std::atan(y / (double) x);
		}
	}
	// quadrant 2
	else if ((x <= 0) && (y >= 0) ){
		// if on x-axis
		if (y == 0) {
			angle = PI;
		}
		// if on y-axis
		else if (x == 0) {
			angle = PI / 2.0;
		}
		else {
			// adjust x
			x = std::abs(x);

			// flip x & y to get angle from positive y axis 
			angle = (PI / 2.0) + std::atan(x / (double) y);
		}
	}
	// quadrant 3
	else if ((x <= 0) && (y <= 0)) {
		// if on x-axis
		if (y == 0) {
			angle = PI;
		}
		// if on y-axis
		else if (x == 0) {
			angle = (3 * PI) / 2;
		}
		else {
			// adjust x and y
			x = std::abs(x);
			y = std::abs(y);

			// since values adjusted, treat as reflection about both axes
			angle = PI + std::atan(y / (double) x);
		}
	}
	// quadrant 4
	else{
		// if on x-axis
		if (y == 0) {
			angle = 2 * PI;
		}
		// if on y-axis
		else if (x == 0) {
			angle = (3 * PI) / 2;
		}
		else {
			// adjust y
			y = std::abs(y);

			// flip x & y to get angle from positive y axis 
			angle = ( (3 * PI) / 2.0 ) + std::atan(x / (double) y);
		}
	}

	return degToRad(angle);
}

/*
// maps a biased distance on a scale of 0 -> maxDistance to a point between between p2 and p1
double interpolateDistance(int maxDistance, int distance, int stepSize, double p2, double p1, double bias) {
	// calculate biased halfway pt and number of steps
	int halfwayOriginal = maxDistance * bias;
	int numSteps = maxDistance / stepSize;

	// calculate differences and biased halfway point
	double dif = p2 - p1;
	double halfwayDif = dif / 2.0;

	double originalSlope;
	double labSlope;
	int curStep;

	// calculate step distance and corresponding step
	if (distance > halfwayOriginal) {
		originalSlope = (maxDistance - halfwayOriginal) / (numSteps / 2.0);
		labSlope = (dif - halfwayDif) / (numSteps / 2.0);
		curStep = (distance - halfwayOriginal) / originalSlope;
	}
	else {
		originalSlope = halfwayOriginal / (numSteps / 2.0);
		labSlope = (halfwayDif) / (numSteps / 2.0);
		curStep = distance / originalSlope;
	}

	double p;

	// calculate position corresponding to current step
	if (bias == 0) {
		p = p1;
	}
	else if (bias == 1) {
		p = p2;
	}
	else if (distance > halfwayOriginal ) {
		p = p1 + halfwayDif + (labSlope * curStep);
	}
	else {
		p = p1 + (labSlope * curStep);
	}

	return p;
}
*/

// returns corresponding step based on distance
int correspondingStep(int maxDistance, int distance, int stepSize, double bias) {
	// calculate biased halfway pt and number of steps
	int halfwayOriginal = maxDistance * bias;
	int numSteps = maxDistance / stepSize;

	double slope;
	int curStep;

	// calculate step distance and corresponding step
	if (bias == 0) {
		curStep = 0;

	}
	else if (bias == 1) {
		curStep = 1;
	}
	else if (distance > halfwayOriginal) {
		slope = (maxDistance - halfwayOriginal) / (numSteps / 2.0);
		curStep = (distance - halfwayOriginal) / slope;
		curStep += (numSteps / 2);

		// Add remainder of odd division onto second half
		if ((numSteps % 2) != 0) {
			curStep += 1;
		}

	}
	else {
		slope = halfwayOriginal / (numSteps / 2.0);
		curStep = distance / slope;
	}



	return curStep;
}

// maps a biased step to a point between between p2 and p1
double interpolateStep(int step, int numSteps, double p2, double p1, double bias) {
	double dif = p2 - p1;
	double halfwayDif = dif * bias;

	double stepDistance;

	// calculates slope by step
	if (step > (numSteps / 2) ) {
		if ((numSteps % 2) != 0) {
			stepDistance = (dif - halfwayDif) / ((numSteps / 2.0) + 1);
		}
		else {
			stepDistance = (dif - halfwayDif) / (numSteps / 2.0);
		}
	}
	else {
		stepDistance = halfwayDif / (numSteps / 2.0);
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

// Interpolates colour between two different ones
// if apply bias is true, then bias is applied
Colour interpolateColour(Colour c1, Colour c2, int curStep, int stepsBetween, double bias, bool applyBias) {
	// get LAB values
	double l1 = c1.getLAB_L();
	double l2 = c2.getLAB_L();
	double a1 = c1.getLAB_A();
	double a2 = c2.getLAB_A();
	double b1 = c1.getLAB_B();
	double b2 = c2.getLAB_B();

	// interpolate new LAB values
	Colour newColour;
	
	if (applyBias) {
		double l = interpolateStep(curStep, stepsBetween, l2, l1, bias);
		double a = interpolateStep(curStep, stepsBetween, a2, a1, bias);
		double b = interpolateStep(curStep, stepsBetween, b2, b1, bias);
		newColour = Colour(l, a, b);
	}
	else {
		double l = interpolateStep(curStep, stepsBetween, l2, l1, 0.5);
		double a = interpolateStep(curStep, stepsBetween, a2, a1, 0.5);
		double b = interpolateStep(curStep, stepsBetween, b2, b1, 0.5);

		newColour = Colour(l, a, b);
	}

	return newColour;

}