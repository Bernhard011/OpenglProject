#pragma once
#include <iostream>
#include <list>
#include <string>
#include "Vector.h"
#include "glfwInclude.h"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

using namespace std;

class Debug{
public:
    unsigned char logLevelWarning = 1;
    unsigned char logLevelInfo = 0;
    unsigned char logLevelError = 2;

private:
    unsigned char m_logLevel;

public:
    Debug() {
        m_logLevel = logLevelInfo;
    }
    Debug(char level) {
        if (level > logLevelError)
            m_logLevel = logLevelError;
        m_logLevel = level;
    }
public:
    void Log(Vector2 data) {
        cout << data.x << data.y << endl;
    }
    template <typename T>
    void Log(T data) {
        cout << data << endl;
    }
    template <typename T>
    void Log(list<T>& data) {
        auto i = data.begin();
        if (i != data.end()) {
            cout << *i;
            ++i;
        }
        for (; i != data.end(); ++i) {
            cout << ", " << *i;
        }
        cout << endl;
    }
    void Log(string data) {
        cout << data << endl;
    }

    template <typename T>
    void Info(T data) {
        if(m_logLevel <= logLevelInfo)
            cout << "[INFO] " << data << endl;
    }
    void Info(string data) {
        if (m_logLevel <= logLevelInfo)
            cout << "[INFO] " << data << endl;
    }
    template <typename T>
    void Warn(T data) {
        if(m_logLevel <= logLevelWarning)
            cout << "[WARNING] " << data << endl;
    }
    void Warn(string data) {
        if (m_logLevel <= logLevelWarning)
            cout << "[WARNING] " << data << endl;
    }
    template <typename T>
    void Error(T data) {
        if(m_logLevel <= logLevelError)
            cout <<"[ERROR] " << data << endl;
    }
    void Error(string data) {
        if (m_logLevel <= logLevelError)
            cout << "[ERROR] " << data << endl;
    }
};

static void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}
static bool GLLogCall(const char* function, const char* file, int line) {
    Debug debug;
    while (GLenum error = glGetError()) {
        debug.Error("Error code: " + to_string(error) + " Function: " + function + " Path: " + file + " line " + to_string(line));
        return false;
    }
    return true;
}