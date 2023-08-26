#pragma once
#include "Vector.h"
#include "Log.h"
#include <string>
#include <list>
#include "glfwInclude.h"
#include <iostream>
using namespace std;

class Entity {
public:
	Vector2 position;

private:
	Debug debug;
	int amountOfFloats;
	bool initialized;

public:
	Entity() {
		position.x = 0;
		position.y = 0;
		amountOfFloats = 0;
		initialized = false;
	}

public:
	void Move(float x, float y) {
		position.x = x;
		position.y = y;
	}
	void Move(Vector2 pos) {
		position.x = pos.x;
		position.y = pos.y;
	}
	void DisplayPosition() {
		debug.Log(to_string(position.x) + ", " + to_string(position.y));
	}
	void Init(float vertices[], int sizeOfFloatArray) {
		if (initialized) {
			debug.Error("Can't initialize an Entity 2 or more times");
			return;
		}
		else
			initialized = true;

		amountOfFloats = sizeOfFloatArray;
		unsigned int image;

		glGenBuffers(1, &image); //Generate Buffer
		glBindBuffer(GL_ARRAY_BUFFER, image); //Bind Buffer
		glBufferData(GL_ARRAY_BUFFER, sizeOfFloatArray * sizeof(float), vertices, GL_STATIC_DRAW);//Assign buffer data

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);//Assign more buffer data
		glEnableVertexAttribArray(0);//Enable the buffer
	}
	void Draw() {
		glDrawArrays(GL_TRIANGLES, 0, amountOfFloats/2);//Draw the triangle from the buffer
	}
};