#pragma once
#include "Vector.h"
#include "Log.h"
#include <vector>
using namespace std;

float* TransformVectorToFloat(Vector2 vectors[]) {
    Debug debug;
    int size = sizeof(vectors) / sizeof(vectors[0]);
    debug.Log(size);
    vector<float> floatArray(size);
    for (int i = 0, x = 0; i < size; i+=2, x++) {
        floatArray[i] = vectors[x].ToFloatX();
        floatArray[i + 1] = vectors[x].ToFloatY();
    }
    float* floatPointerArray = new float[size];
    for (int i = 0; i < size; i++) {
        floatPointerArray[i] = floatArray[i];
        debug.Log(floatArray[i]);
    }
    return floatPointerArray;
}