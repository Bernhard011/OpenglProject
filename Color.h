#pragma once
#include "Log.h"

struct Color {
public:
	float r;
	float g;
	float b;
	float a;

	enum ColorPresets : char{
		RED, GREEN, BLUE, YELLOW, ORANGE, WHITE, BLACK, PURPLE
	};

public:
	Color(float rValue, float gValue, float bValue, float aValue) {
		if (rValue >= 1.0f)
			rValue = 1.0f;
		if (gValue >= 1.0f)
			gValue = 1.0f;
		if (bValue >= 1.0f)
			bValue = 1.0f;
		if (aValue >= 1.0f)
			aValue = 1.0f;

		r = rValue;
		g = gValue;
		b = bValue;
		a = aValue;
	}
	Color(float rValue, float gValue, float bValue) {
		if (rValue >= 1.0f)
			rValue = 1.0f;
		if (gValue >= 1.0f)
			gValue = 1.0f;
		if (bValue >= 1.0f)
			bValue = 1.0f;

		r = rValue;
		g = gValue;
		b = bValue;
		a = 1.0;
	}
	Color(float rValue, float gValue) {
		if (rValue >= 1.0f)
			rValue = 1.0f;
		if (gValue >= 1.0f)
			gValue = 1.0f;

		r = rValue;
		g = gValue;
		b = 0;
		a = 1.0;
	}
	Color(float rValue) {
		if (rValue >= 1.0f)
			rValue = 1.0f;

		r = rValue;
		g = 0;
		b = 0;
		a = 1.0;
	}
	Color() {
		r = 0;
		g = 0;
		b = 0;
		a = 1.0f;
	}

	Color(Vector4 color) {
		if (color.x >= 1.0f)
			color.x = 1.0f;
		if (color.y >= 1.0f)
			color.y = 1.0f;
		if (color.z >= 1.0f)
			color.z = 1.0f;
		if (color.w >= 1.0f)
			color.w = 1.0f;

		r = color.x;
		g = color.y;
		b = color.z;
		a = color.w;
	}
	Color(ColorPresets colorPreset) {
		Vector4 color;

		switch (colorPreset) {
		case RED:
			color = Vector4(1.0f, 0, 0, 1.0f);
			break;
		case GREEN:
			color = Vector4(0, 1.0f, 0, 1.0f);
			break;
		case BLUE:
			color = Vector4(0, 0, 1.0f, 1.0f);
			break;
		case YELLOW:
			color = Vector4(1.0f, 1.0f, 0, 1.0f);
			break;
		case ORANGE:
			color = Vector4(1.0f, 0.647f, 0, 1.0f);
			break;
		case WHITE:
			color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		case BLACK:
			color = Vector4(0, 0, 0, 1.0f);
			break;
		case PURPLE:
			color = Vector4(0.5, 0, 0.5, 1.0f);
			break;
		}

		r = color.x;
		g = color.y;
		b = color.z;
		a = color.w;
	}

	Vector4 ToVec4() {
		Vector4 vec4 = Vector4(r, g, b, a);
		return vec4;
	}
};
