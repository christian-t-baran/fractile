#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "../colours/colour.h"
#include "../colours/colourConversion.h"
#include "angularField.h"
#include "angularSingleReflectionField.h"
#include "angularDoubleReflectionField.h"
#include "linearField.h"
#include "linearDiagonalField.h"
#include "radialField.h"
#include "radialDiamondField.h"
#include "radialSquareField.h"
#include "radialXField.h"
#include "colourField.h"

std::vector<Colour> ColourVectorBuilder() {
	std::string colour;
	std::vector<Colour> colours = std::vector<Colour>();
	
	std::cout << "Please enter first colour (#HEX): ";
	std::cin >> colour;
	
	colours.push_back(Colour(colour));

	std::cout << "Please enter second colour (#HEX): ";
	std::cin >> colour;

	while (colour != "0") {
		colours.push_back(Colour(colour));

		std::cout << "Please enter next colour (#HEX) or 0 to stop entering colours" << std::endl;
		
		std::cin >> colour;
	}

	return colours;
}

void effectBuilder(ColourField& field)
{
	int effectOption;
	int effect;
	int effectStep;
	unsigned int effectDepth = 1;
	bool effectDirection = true;
	double effectBias;
	std::string colourPulse;

	// check if effect is relevant
	std::cout << "Please enter 1 for effect, 2 for no effect: ";
	std::cin >> effectOption;
	// get effect info if relevant
	if (effectOption == 1) {
		std::cout << "Please enter effect mode (1 - strobe, 2 - converge, 3 - pulse, 4 - flow): ";
		std::cin >> effect;
		std::cout << "Please enter effect step: ";
		std::cin >> effectStep;

		if ((effect == 1) || (effect == 3)){
			int effectDir;
			std::cout << "Please enter 1 for inner colour changing, 2 for outer: ";
			std::cin >> effectDir;

			if (effectDir == 2) {
				effectDirection = false;
			}
		}
		else if ((effect == 4)) {
			int effectDir;
			std::cout << "Please enter 1 for colours flowing from start, 2 for colours flowing in reverse: ";
			std::cin >> effectDir;

			if (effectDir == 2) {
				effectDirection = false;
			}
		}
		
		if ((effect == 1) || (effect == 3)) {
			std::cout << "Please enter effect depth: ";
			std::cin >> effectDepth;
		}

		if (effect == 3) {
			std::cout << "Please enter pulse colour (#HEX): ";
			std::cin >> colourPulse;

		}

		if ((effect == 1) || (effect == 2) || (effect == 3) ) {
			std::cout << "Please enter effect bias: ";
			std::cin >> effectBias;
		}
	}

	// set up effect
	if (effectOption == 1) {
		if (effect == 1) {
			field.setStrobe(effectStep, effectDepth, effectBias, effectDirection);
		}
		else if (effect == 2) {
			field.setConverge(effectStep, effectBias);
		}
		else if (effect == 3) {
			Colour pulse = Colour(colourPulse);
			field.setPulse(pulse, effectStep, effectDepth, effectBias, effectDirection);
		}
		else if (effect == 4) {
			field.setFlow(effectStep, effectBias, effectDirection);
		}
	}
}

// Builds a base (flat) ColourField object
ColourField* ColourFieldBuilder() {
	std::string colourStr;

	std::cout << "Please enter colour (#HEX): ";
	std::cin >> colourStr;

	Colour colour = Colour(colourStr);
	std::vector<Colour> colours = std::vector<Colour>();

	colours.push_back(colour);

	ColourField* field = new ColourField(colours);

	return field;
}

// Builds a LinearField object
LinearField* LinearFieldBuilder(int x, int y) {
	std::string colourPulse;

	int fieldType;
	int step;
	int copies;

	double bias;

	// get input to create linear field
	std::cout << "Please enter field type (1 - single axis, 2 - diagonal): ";
	std::cin >> fieldType;
	std::cout << "Please enter number of copies: ";
	std::cin >> copies;
	std::cout << "Please enter field step (<= radius): ";
	std::cin >> step;
	std::cout << "Please enter field bias: ";
	std::cin >> bias;


	std::vector<Colour> colours = ColourVectorBuilder();

	LinearField* field;

	// set up direction
	if (fieldType == 1) {
		int direction;
		
		std::cout << "1 to gradate on x axis, 2 to gradate on y axis: ";
		std::cin >> direction;

		field = new LinearField(colours, x, y, bias);

		if (direction == 2) {
			(*field).changeDirection();
		}

	}
	else if (fieldType == 2) {
		int direction;

		std::cout << "1 to gradate from top-left to bottom-right, 2 for opposite: ";
		std::cin >> direction;

		field = new LinearDiagonalField(colours, x, y, bias);

		if (direction == 2) {
			(*field).changeDirection();
		}
	}

	effectBuilder(*field);

	(*field).setStep(step);
	(*field).setCopies(copies);

	return field;
}

// Builds a RadialField object
RadialField* RadialFieldBuilder(int x, int y) {
	std::string colourPulse;

	int step;
	int fieldType;
	int copies;

	double bias;

	// get input to create radial field
	std::cout << "Please enter field type (1 - mapped circle, 2 - square, 3 - X, 4 - diamond): ";
	std::cin >> fieldType;
	std::cout << "Please enter number of copies: ";
	std::cin >> copies;
	std::cout << "Please enter field step (<= radius): ";
	std::cin >> step;
	std::cout << "Please enter field bias: ";
	std::cin >> bias;

	std::vector<Colour> colours = ColourVectorBuilder();

	RadialField* field;

	if (fieldType == 1) {
		field = new RadialField(colours, x, y, bias);
	}
	else if (fieldType == 2) {
		field = new RadialSquareField(colours, x, y, bias);
	}
	else if (fieldType == 3) {
		field = new RadialXField(colours, x, y, bias);
	}
	else if (fieldType == 4) {
		field = new RadialDiamondField(colours, x, y, bias);
	}

	effectBuilder(*field);


	(*field).setStep(step);
	(*field).setCopies(copies);

	return field;
}

AngularField* AngularFieldBuilder(int x, int y) {
	std::string colourPulse;

	int step;
	int fieldType;
	int copies;

	double bias;

	// get input to create radial field
	std::cout << "Please enter field type (1 - single, 2 - single reflection, 3 - all axis reflection): ";
	std::cin >> fieldType;
	std::cout << "Please enter number of copies: ";
	std::cin >> copies;
	std::cout << "Please enter field step (in whole deg): ";
	std::cin >> step;
	std::cout << "Please enter field bias: ";
	std::cin >> bias;

	std::vector<Colour> colours = ColourVectorBuilder();

	AngularField* field;

	if (fieldType == 1) {
		int direction;

		std::cout << "1 to start on positive x axis, 2 to start on positive y axis: ";
		std::cin >> direction;

		field = new AngularField(colours, x, y, bias);

		if (direction == 2) {
			(*field).changeDirection();
		}
	}
	else if (fieldType == 2) {
		int direction;

		std::cout << "1 to reflect around x axis, 2 to reflect around y axis: ";
		std::cin >> direction;

		field = new AngularSingleReflectionField(colours, x, y, bias);

		if (direction == 2) {
			(*field).changeDirection();
		}
	}
	else if (fieldType == 3) {
		int direction;

		std::cout << "1 to reflect around x axis, 2 to reflect around y axis: ";
		std::cin >> direction;

		field = new AngularDoubleReflectionField(colours, x, y, bias);

		if (direction == 2) {
			(*field).changeDirection();
		}
	}

	effectBuilder(*field);


	(*field).setStep(step);
	(*field).setCopies(copies);

	return field;
}

// Builds a ColourField (and any of its derived classes
ColourField* fieldFactory(int x, int y) {
	ColourField* field(NULL);

	int option;

	std::cout << "Please enter the type of field (1 for radial, 2 for linear, 3 for angular, 4 for solid): ";
	std::cin >> option;

	if (option == 1) {
		field = RadialFieldBuilder(x, y);
	}
	else if (option == 2) {
		field = LinearFieldBuilder(x, y);
	}
	else if (option == 3) {
		field = AngularFieldBuilder(x, y);
	}
	else if (option == 4) {
		field = ColourFieldBuilder();
	}

	return field;
}