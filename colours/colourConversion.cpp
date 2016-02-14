#include <cmath>
#include <iostream>
#include <vector>
#include "colourConversion.h"

/*
	Functions for converting colours between RGB and LAB
*/


// Formulas from http://www.easyrgb.com/index.php?X=MATH
// and http://www.brucelindbloom.com/index.html?Equations.html

// Colour test cases from http://www.colorhexa.com

// Converts RGB value to value in 0 -> 1.0 range
double convertRGBtoDec(int c) {
	return c / 255.0;
}

// clamps a vector of RGB values
void clampRGB(std::vector<int>& RGB) {
	for (int i = 0; i < RGB.size(); i++) {
		if (RGB[i] < VALID_RGB_LOWER) {
			RGB[i] = VALID_RGB_LOWER;
		}
		else if (RGB[i] > VALID_RGB_UPPER) {
			RGB[i] = VALID_RGB_UPPER;
		}
	}
}

// Converts RGB to double array of XYZ
std::vector<double> RGBtoXYZ (int r, int g, int b) {
	double R = r / 255.0;
	double G = g / 255.0;
	double B = b / 255.0;

	
	R = RGBtoXYZcompander(R);
	G = RGBtoXYZcompander(G);
	B = RGBtoXYZcompander(B);

	R = R * 100;
	G = G * 100;
	B = B * 100;

	std::vector<double> XYZ(3);

	XYZ[0] = R * 0.4124 + G * 0.3576 + B * 0.1805;
	XYZ[1] = R * 0.2126 + G * 0.7152 + B * 0.0722;
	XYZ[2] = R * 0.0193 + G * 0.1192 + B * 0.9505;

	return XYZ;
}

// Function to handle companding for RGB -> XYZ
double RGBtoXYZcompander(double i) {
	if (i > 0.04045) {
		i = std::pow(((i + 0.055) / 1.055), 2.4);
	}
	else {
		i = i / 12.92;
	}

	return i;
}

// Converts LAB values to array of XYZ values
std::vector<double> LABtoXYZ(double l, double a, double b) {
	double Y = (l + 16) / 116.0;
	double X = (a / 500.0) + Y;
	double Z = Y - (b / 200.0);
	
	// as per the eqn's on Bruce Lindbloom's site
	X = LABtoXYZhelperXZ(X);
	Y = LABtoXYZhelperY(l);
	Z = LABtoXYZhelperXZ(Z);

	std::vector<double> XYZ(3);
	XYZ[0] = X * REF_X;
	XYZ[1] = Y * REF_Y;
	XYZ[2] = Z * REF_Z;

	return XYZ;
};

// Helper for converting LABtoXYZ
double LABtoXYZhelperXZ(double i) {
	if (std::pow(i, 3) > EPSILON) {
		i = std::pow(i, 3);
	}
	else {
		i = ((116 * i) - 16) / KAPPA;
	}
	
	return i;
}

double LABtoXYZhelperY(double l) {
	if (l > (EPSILON * KAPPA)) {
		double temp = ((l + 16) / (double) 116);
		l = std::pow(temp, 3);
	}
	else {
		l = (l / KAPPA);
	}

	return l;
}

// Converts array of XYZ values to array of RGB values
std::vector<int> XYZtoRGB(std::vector<double> XYZ) {
	double X = XYZ[0] / 100.0;    //X from 0 to  95.047      (Observer = 2°, Illuminant = D65)
	double Y = XYZ[1] / 100.0;    //Y from 0 to 100.000
	double Z = XYZ[2] / 100.0;    //Z from 0 to 108.883

	double R = (X * 3.2406) + (Y * -1.5372) + (Z * -0.4986);
	double G = (X * -0.9689) + (Y *  1.8758) + (Z *  0.0415);
	double B = (X *  0.0557) + (Y * -0.2040) + (Z *  1.0570);

	R = XYZtoRGBhelper(R);
	G = XYZtoRGBhelper(G);
	B = XYZtoRGBhelper(B);

	std::vector<int> RGB(3);

	RGB[0] = (int) std::round(R * 255);
	RGB[1] = (int) std::round(G * 255);
	RGB[2] = (int) std::round(B * 255);

	return RGB;
};

// Helper for converting XYZ to RGB
double XYZtoRGBhelper(double i) {
	if (i > 0.0031308) {
		i = (1.055 * (std::pow(i, (1 / 2.4)))) - 0.055;
	}
	else {
		i = i * 12.92;
	}

	return i;
}

// converts array of XYZ values to array of LAB values
std::vector<double> XYZtoLAB(std::vector<double> XYZ) {
	double X = XYZ[0] / REF_X;	// REFERENCE WHITE
	double Y = XYZ[1] / REF_Y;	// Observer= 2°, Illuminant= D65
	double Z = XYZ[2] / REF_Z;
	
	X = XYZtoLABhelper(X);
	Y = XYZtoLABhelper(Y);
	Z = XYZtoLABhelper(Z);

	std::vector<double> LAB(3);

	LAB[0] = (116 * Y) - 16;
	LAB[1] = 500 * (X - Y);
	LAB[2] = 200 * (Y - Z);

	return LAB;
};

// Helper for converting XYZ to LAB
double XYZtoLABhelper(double i) {
	if (i > EPSILON) {
		i = std::pow(i, 1 / 3.0);
	}
	else {
		i = ((903.3 * i) + 16) / 116;
	}

	return i;
}

// Converts set of RGB values to array of LAB values
std::vector<double> RGBtoLAB(int r, int g, int b) {
	std::vector<double> XYZ = RGBtoXYZ(r, g, b);
	
	std::vector<double> LAB = XYZtoLAB(XYZ);

	return LAB;
}

// Converts set of LAB values to array of RGB values
std::vector<int> LABtoRGB(double l, double a, double b) {
	std::vector<double> XYZ = LABtoXYZ(l, a, b);

	std::vector<int> RGB = XYZtoRGB(XYZ);

	// clamp RGB values
	clampRGB(RGB);

	return RGB;
}




// Tests for colourConversion.cpp
void colourConversionTests() {
	// Tests for RGB colours
	std::cout << "Test case RGB(0, 0, 0) - black" << std::endl;		//	black
	std::vector<double> testD = RGBtoLAB(0, 0, 0);
	std::cout << "LAB values are " << testD[0] << ", " << testD[1] << ", " << testD[2] << std::endl;

	std::cout << "Test case RGB(255, 255, 255) - white" << std::endl;	//	white
	testD = RGBtoLAB(255, 255, 255);
	std::cout << "LAB values are " << testD[0] << ", " << testD[1] << ", " << testD[2] << std::endl;

	std::cout << "Test case RGB(165, 42, 42) - brown" << std::endl;		//	brown
	testD = RGBtoLAB(165, 42, 42);
	std::cout << "LAB values are " << testD[0] << ", " << testD[1] << ", " << testD[2] << std::endl;

	std::cout << "Test case RGB(102,51,153) - rebecca purple" << std::endl; // rebecca purple
	testD = RGBtoLAB(102, 51, 153);
	std::cout << "LAB values are " << testD[0] << ", " << testD[1] << ", " << testD[2] << std::endl;

	std::cout << "Test case RGB(143, 188, 143) - dark sea green" << std::endl; // rebecca purple
	testD = RGBtoLAB(143, 188, 143);
	std::cout << "LAB values are " << testD[0] << ", " << testD[1] << ", " << testD[2] << std::endl;

	// Tests for LAB colours
	std::cout << "Test CASE LAB(100, 0, 0.009) - white" << std::endl;	// white
	std::vector<int> testI = LABtoRGB(100, 0, 0.009);
	std::cout << "RGB values are " << testI[0] << ", " << testI[1] << ", " << testI[2] << std::endl;

	std::cout << "Test CASE LAB(0, 0, 0) - black" << std::endl;			// black
	testI = LABtoRGB(0, 0, 0);				
	std::cout << "RGB values are " << testI[0] << ", " << testI[1] << ", " << testI[2] << std::endl;

	std::cout << "Test CASE LAB(37.525, 49.689, 30.54) - brown" << std::endl;		// brown
	testI = LABtoRGB(37.525, 49.689, 30.54);
	std::cout << "RGB values are " << testI[0] << ", " << testI[1] << ", " << testI[2] << std::endl;

	std::cout << "Test CASE LAB(32.903, 42.885, -47.154) - rebecca purple" << std::endl;
	testI = LABtoRGB(32.903, 42.885, -47.154);
	std::cout << "RGB values are " << testI[0] << ", " << testI[1] << ", " << testI[2] << std::endl;

	std::cout << "Test CASE LAB(72.087, -23.82, 18.033) - dark sea green" << std::endl;
	testI = LABtoRGB(72.087, -23.82, 18.033);
	std::cout << "RGB values are " << testI[0] << ", " << testI[1] << ", " << testI[2] << std::endl;

}