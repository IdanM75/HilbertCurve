#include "pch.h"
#include "ColorsGradient.h"


ColorsGradient::ColorsGradient() {}

ColorsGradient::ColorsGradient(Color firstColor) : currentColor{ firstColor } { addColor(firstColor); }

ColorsGradient::ColorsGradient(const ColorsGradient& cg) : colors{ cg.getColors() }, currentColor{ cg.getColor() } {}

vector<Color> ColorsGradient::getColors() const { return colors; }

Color ColorsGradient::getColor() const { return currentColor; }

Color ColorsGradient::getColor(int index) const { return colors[index]; }

void ColorsGradient::setColors(vector<Color> cs) { colors = cs; }

void ColorsGradient::addColor(Color c) { colors.push_back(c); }

void ColorsGradient::prograde(int ColorAmount) {
	if (colors.size() > 1) {
		int divi = (int)((double)(ColorAmount / (colors.size() - 1)));
		currentStep += 1;
		if (currentStep == ColorAmount) {
			reset();
		}
		else if (currentStep % divi == 0) {
			currentColorIndex += 1;
			if (currentColorIndex == colors.size()) {
				currentColorIndex = 0;
			}
			currentColor = getColor(currentColorIndex);
		}
		else {
			int nextIndex;
			currentColorIndex == colors.size() - 1 ? nextIndex = 0 : nextIndex = currentColorIndex + 1;
			double currentRed = (colors[nextIndex].getRed() - colors[currentColorIndex].getRed());
			currentRed *= ((double)(currentStep % divi) / divi);
			currentRed += colors[currentColorIndex].getRed();
			double currentGreen = (colors[nextIndex].getGreen() - colors[currentColorIndex].getGreen());
			currentGreen *= ((double)(currentStep % divi) / divi);
			currentGreen += colors[currentColorIndex].getGreen();
			double currentBlue = (colors[nextIndex].getBlue() - colors[currentColorIndex].getBlue());
			currentBlue *= ((double)(currentStep % divi) / divi);
			currentBlue += colors[currentColorIndex].getBlue();
			currentColor.setRed((int)currentRed);
			currentColor.setGreen((int)currentGreen);
			currentColor.setBlue((int)currentBlue);
		}
	}
}

void ColorsGradient::reset() {
	currentColorIndex = 0;
	currentColor = getColor(currentColorIndex);
	currentStep = 0;
}

IMPLEMENT_SERIAL(ColorsGradient, CObject, VERSIONABLE_SCHEMA | 1)
void ColorsGradient::Serialize(CArchive& ar) {
	if (ar.IsStoring()) {
		ar << colors.size();
		for (unsigned int i = 0; i < colors.size(); i++) {
			colors[i].Serialize(ar);
		}
		currentColor.Serialize(ar);
		ar << currentStep << currentColorIndex;
	}
	else {
		unsigned int tempColorsSize;
		ar >> tempColorsSize;
		for (unsigned int i = 0; i < tempColorsSize; i++) {
			Color tempColor;
			tempColor.Serialize(ar);
			colors.push_back(tempColor);
		}
		currentColor.Serialize(ar);
		ar >> currentStep >> currentColorIndex;
	}
}