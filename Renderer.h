#pragma once
#include "glfwInclude.h"
#include "Log.h"
#include "Color.h"

#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <fstream>
#include <sstream>
#include <ostream>
#include <unordered_map>

using namespace std;

#pragma region Buffer Simplifiers

//Helper class for the vertex buffer layout class
struct VertexBufferElement { //Helper struct to create the VertexArray class
	unsigned int type; //Data type
	unsigned int count; //Amount of data
	unsigned char normalized; //If the data is normalized

	//This method returns the size of the inputed data type in bytes, it will return 0 if the data type is unknown
	static unsigned int GetSizeOfType(unsigned int _type) {
		switch (_type) {
		case GL_FLOAT:
			return 4;
		case GL_UNSIGNED_INT:
			return 4;
		case GL_UNSIGNED_BYTE:
			return 1;
		default:
			ASSERT(false);
			return 0;
		}
	}
};

//A class to create a vertex buffer easier.
class VertexBuffer {
private:
	unsigned int m_RendererID = NULL; //Current renderer id

public:
	//A constructor that creates a vertex buffer
	VertexBuffer(const void* data, unsigned int size) {
		GLCall(glGenBuffers(1, &m_RendererID)); //Generate a buffer using the id
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); //Bind the buffer
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW)); //Specify the size of the buffer
	}
	//Destructor to destruct the vertex buffer
	~VertexBuffer() {
		GLCall(glDeleteBuffers(1, &m_RendererID));
	}

	//Methods that bind/unbind the vertex buffer
	void Bind() const {
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); //Bind the buffer
	}
	void Unbind() const {
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); //Bind the buffer
	}
};

//A class that helps creating an index buffer easier
class IndexBuffer
{
private:
	unsigned int m_RendererID = NULL; //Current renderer id
	unsigned int m_Count = NULL; //Amound of current indexes
	bool m_Printed = false; //Bool that indicates if the error in the Draw() method has printed yet
	Debug debug = Debug(); //An instance of the 'Debug' class to display the error

public:
	//Constructor to create an index buffer
	IndexBuffer(const unsigned int* data, unsigned int count) : m_Count(count) {
		GLCall(glGenBuffers(1, &m_RendererID)); //Generate a buffer using the id
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID)); //Bind the buffer
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW)); //Specify the size of the buffer
	}
	//Destructor to destruct the index buffer
	~IndexBuffer() {
		GLCall(glDeleteBuffers(1, &m_RendererID));
	}

	//Methods that bind/unbind the buffer
	void Bind() const {
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID)); //Bind the buffer
	}
	void Unbind() const {
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL)); //Bind the buffer
	}
	//Method that displays the index buffer
	void Draw() {
		//If the count is 0 or NULL we won't draw the index buffer to the screen and create a notification in the console
		bool condition = m_Count == NULL;
		if (condition && !m_Printed) {
			debug.Error("Count is 0");
			m_Printed = true;
			return;
		}
		else if (condition) {
			return;
		}

		GLCall(glDrawElements(GL_TRIANGLES, m_Count, GL_UNSIGNED_INT, nullptr)); //Draw the index buffer
	}

	inline unsigned int GetCount() const { return m_Count; } //Inline function that returns the amount of positions in the buffer
};

//A class that helps creating a vertex buffer layout easier
class VertexBufferLayout {
private:
	vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;

public:
	//Initialize the stride variable with NULL
	VertexBufferLayout()
		:m_Stride(NULL) {}

	template<typename T>
	//Methods that push a datatype on the variable m_Elements
	void Push(unsigned int count) {
		runtime_error(false);
	}
	template<>
	void Push<float>(unsigned int count) {
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}
	template<>
	void Push<unsigned int>(unsigned int count) {
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}
	template<>
	void Push<unsigned char>(unsigned int count) {
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	//Inline methods to return the stride/elements variables
	inline const vector <VertexBufferElement> GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }
};

//A class that helps creating a vertex array easier
class VertexArray {
private:
	unsigned int m_RendererID = NULL; //Current renderer id

public:
	VertexArray() {
		GLCall(glGenVertexArrays(1, &m_RendererID)); //Generate vertex arrays
		GLCall(glBindVertexArray(m_RendererID)); //Bind the arrays
	}

	//This method adds a buffer to the vertex array
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
		GLCall(Bind()); //Bind the vertex array
		GLCall(vb.Bind()); //bind the vertex buffer
		const auto& elements = layout.GetElements();
		unsigned int offset = 0; //Offset in Bytes
		for (unsigned int i = 0; i < elements.size(); i++) {
			const auto& element = elements[i]; //Get the current variable from the elements list
			GLCall(glEnableVertexAttribArray(i)); //Enable the vertex array
			GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const GLvoid*)offset)); //Bind the vertex array with the index buffer
			offset += element.count * VertexBufferElement::GetSizeOfType(element.type); //Increase the offset by the amount of bytes we've just written on
		}
	}

	//Methods to bind/unbind the vertex array
	void Bind() const {
		GLCall(glBindVertexArray(m_RendererID));
	}
	void Unbind() const {
		GLCall(glBindVertexArray(NULL));
	}
};
#pragma endregion

#pragma region Shader Simplifiers
class Shader {
private:
	unsigned int m_RendererID;
	string m_FilePath;
	Debug debug;
	unordered_map<string, int> m_UniformLocationCache;
public:
	Shader(string filepath)
		: m_FilePath(filepath), m_RendererID(0){

		ShaderProgramSource source = ParseShader(filepath);
		m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
	}
	~Shader() {
		GLCall(glDeleteProgram(m_RendererID));
	}

	void SetUniform1i(const string& name, int i){
		GLCall(glUniform1i(GetUniformLocation(name), i));
	}

	void SetUniform4f(const string& name, Color color) {
		GLCall(glUniform4f(GetUniformLocation(name), color.r, color.g, color.b, color.a));
	}

	void Bind() const{
		GLCall(glUseProgram(m_RendererID));
	}
	void Unbind() const{
		GLCall(glUseProgram(0));
	}
	inline unsigned int GetID() { return m_RendererID; }

private:
	int GetUniformLocation(const string name) {
		if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
			return m_UniformLocationCache[name];

		GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));

		if (location == -1)
			debug.Warn("Uniform doesn't exist (= -1)");

		m_UniformLocationCache[name] = location;
		return location;
	}
	struct ShaderProgramSource {
		string VertexSource;
		string FragmentSource;
	};

	ShaderProgramSource ParseShader(const string& filepath) {
		ifstream stream(filepath);

		enum class ShaderType {
			NONE = -1, VERTEX = 0, FRAGMENT = 1
		};

		string line;
		stringstream ss[2];
		ShaderType type = ShaderType::NONE;
		while (getline(stream, line)) {
			if (line.find("#shader") != string::npos) {
				if (line.find("vertex") != string::npos) {
					type = ShaderType::VERTEX;
				}
				else if (line.find("fragment") != string::npos) {
					type = ShaderType::FRAGMENT;
				}
			}
			else {
				ss[(int)type] << line << '\n';
			}
		}
		debug.Log(ss[0].str()); //Print the Vertex Shader
		debug.Log(ss[1].str()); //Print the Fragment Shader
		return { ss[0].str(), ss[1].str() };
	}

	unsigned int CompileShader(const string& source, unsigned int type) {
		Debug debug;
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();

		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE) {
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)_malloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);

			debug.Error("Failed to compile shader");
			debug.Log(message);

			glDeleteShader(id);
			return 0;
		}

		return id;
	}
	unsigned int CreateShader(const string& vertexShader, const string& fragmentShader) {
		unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
		unsigned int fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);
		unsigned int program = glCreateProgram();

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;
	}
};
#pragma endregion

#pragma region Renderer
class Renderer {
public:
	void Draw(const VertexArray& va, const IndexBuffer& ibo, const Shader& shader) {
		shader.Bind();
		va.Bind();
		ibo.Bind();
		glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr);
	}
	void Clear() {
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void Swap(GLFWwindow* window) {
		glfwSwapBuffers(window);
	}
	void PollEvents() {
		glfwPollEvents();
	}
	void Terminate(Shader shader) {
		glDeleteProgram(shader.GetID());
		glfwTerminate();
	}
	void Blend() {
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	}
};
#pragma endregion