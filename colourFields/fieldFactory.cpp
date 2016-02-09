#include <iostream>
#include <string>
#include <utility>
#include <vector>


#include "../colourFields/linearField.h"
#include "../colourFields/radialField.h"
#include "../colourFields/radialDiamondField.h"
#include "../colourFields/radialSquareField.h"
#include "../colourFields/radialXField.h"
#include "../colourFields/colourField.h"
#include "../colours/colour.h"
#include "../colours/colourConversion.h"

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
	std::string colourStr1;
	std::string colourStr2;
	std::string colourPulse;

	int axis;
	int step;
	int copies;

	double bias;
	int effectOption;
	int effect;
	int effectStep;
	double effectBias;

	// get input to create linear field
	std::cout << "Enter 1 to gradate on x axis, 2 for y: ";
	std::cin >> axis;
	std::cout << "Please enter number of copies: ";
	std::cin >> copies;
	std::cout << "Please enter field step (<= radius): ";
	std::cin >> step;
	std::cout << "Please enter field bias: ";
	std::cin >> bias;
	std::cout << "Please enter first colour (#HEX): ";
	std::cin >> colourStr1;
	std::cout << "Please enter second colour (#HEX): ";
	std::cin >> colourStr2;

	// check if effect is relevant
	std::cout << "Please enter 1 for effect, 2 for no effect: ";
	std::cin >> effectOption;
	// get effect info if relevant
	if (effectOption == 1) {
		std::cout << "Please enter effect mode (1 - strobe, 2 - converge, 3 - pulse): ";
		std::cin >> effect;
		if (effect == 3) {
			std::cout << "Please enter pulse colour (#HEX): ";
			std::cin >> colourPulse;

		}
		std::cout << "Please enter effect step: ";
		std::cin >> effectStep;
		std::cout << "Please enter effect bias: ";
		std::cin >> effectBias;
	}
	

	Colour colour1 = Colour(colourStr1);
	Colour colour2 = Colour(colourStr2);

	std::vector<Colour> colours = std::vector<Colour>();

	colours.push_back(colour1);
	colours.push_back(colour2);

	LinearField* field = new LinearField(colours, x, y, bias);

	// set up effect
	if (effectOption == 1) {
		if (effect == 1) {
			(*field).setStrobe(effectStep, effectBias);
		}
		else if (effect == 2) {
			(*field).setConverge(effectStep, effectBias);
		}
		else if (effect == 3) {
			Colour pulse = Colour(colourPulse);
			(*field).setPulse(pulse, effectStep, effectBias);
		}
	}
	
	// change axis if y was selected
	if (axis == 2) {
		(*field).changeAxis();
	}

	(*field).setStep(step);
	(*field).setCopies(copies);

	return field;
}

// Builds a RadialField object
RadialField* RadialFieldBuilder(int diameter) {
	std::string colourStr1;
	std::string colourStr2;
	std::string colourPulse;

	int step;
	int fieldType;
	int copies;

	double bias;
	int effectOption;
	int effect;
	int effectStep;
	double effectBias;

	// get input to create radial field
	std::cout << "Please enter field type (1 - mapped circle, 2 - square, 3 - X, 4 - diamond): ";
	std::cin >> fieldType;
	std::cout << "Please enter number of copies: ";
	std::cin >> copies;
	std::cout << "Please enter field step (<= radius): ";
	std::cin >> step;
	std::cout << "Please enter field bias: ";
	std::cin >> bias;
	std::cout << "Please enter first colour (#HEX): ";
	std::cin >> colourStr1;
	std::cout << "Please enter second colour (#HEX): ";
	std::cin >> colourStr2;

	// check if effect is relevant
	std::cout << "Please enter 1 for effect, 2 for no effect: ";
	std::cin >> effectOption;
	// get effect info if relevant
	if (effectOption == 1) {
		std::cout << "Please enter effect mode (1 - strobe, 2 - converge, 3 - pulse): ";
		std::cin >> effect;
		if (effect == 3) {
			std::cout << "Please enter pulse colour (#HEX): ";
			std::cin >> colourPulse;

		}
		std::cout << "Please enter effect step: ";
		std::cin >> effectStep;
		std::cout << "Please enter effect bias: ";
		std::cin >> effectBias;
	}


	Colour colour1 = Colour(colourStr1);
	Colour colour2 = Colour(colourStr2);

	std::vector<Colour> colours = std::vector<Colour>();

	colours.push_back(colour1);
	colours.push_back(colour2);

	RadialField* field;

	if (fieldType == 1) {
		field = new RadialField(colours, diameter / 2, bias);
	}
	else if (fieldType == 2) {
		field = new RadialSquareField(colours, diameter / 2, bias);
	}
	else if (fieldType == 3) {
		field = new RadialXField(colours, diameter / 2, bias);
	}
	else if (fieldType == 4) {
		field = new RadialDiamondField(colours, diameter / 2, bias);
	}

	// set up effect
	if (effectOption == 1) {
		if (effect == 1) {
			(*field).setStrobe(effectStep, effectBias);
		}
		else if (effect == 2) {
			(*field).setConverge(effectStep, effectBias);
		}
		else if (effect == 3) {
			Colour pulse = Colour(colourPulse);
			(*field).setPulse(pulse, effectStep, effectBias);
		}
	}

	(*field).setStep(step);
	(*field).setCopies(copies);

	return field;
}

// Builds a ColourField (and any of its derived classes
ColourField* fieldFactory(int x, int y) {
	ColourField* field(NULL);

	int option;

	std::cout << "Please enter the type of field (1 for radial, 2 for linear, 3 for solid): ";
	std::cin >> option;

	if (option == 1) {
		field = RadialFieldBuilder(x);
	}
	else if (option == 2) {
		field = LinearFieldBuilder(x, y);
	}
	else if (option == 3) {
		field = ColourFieldBuilder();
	}

	return field;
}