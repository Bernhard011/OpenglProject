#include "Entity.h"
#include "Log.h"

#include "Vector.h"
#include "VectorToFloat.h"
#include "Color.h"
#include "Texture.h"

#include "glfwInclude.h"
#include "Renderer.h"

#include <string>

using namespace std;


int main(void) {
    GLFWwindow* window;
    Debug debug;

    
    if (!glfwInit())// Initialize the library
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(602, 249, "Sandbox", NULL, NULL);// Create a windowed mode window and its OpenGL context
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);//Make the window's context current

    glfwSwapInterval(2);

    if (glewInit() != GLEW_OK)
        debug.Error("Error while initializing GLEW");  

    Color color = Color(1.0f, 1.0f, 1.0f, 1.0f);
    Texture texture("OpenglLogo.png");
    texture.Bind(0);
    Renderer renderer;
    Shader shader = Shader("Basic.shader");
    shader.Bind();
    shader.SetUniform4f("u_Color", color);
    shader.SetUniform1i("u_Texture", 0);

    Vector2 positions[8] = {                        //Array for the 4 different vertices of the rectangle
        Vector2(-0.5f, -0.5f), Vector2(0.0f, 0.0f), //To safe data, we don't specify points which aren't different
        Vector2(0.5f, -0.5f), Vector2(1.0f, 0.0f),
        Vector2(0.5f, 0.5f), Vector2(1.0f, 1.0f),
        Vector2(-0.5f, 0.5f), Vector2(0.0f, 1.0f)
    };

    unsigned int indices[] = { //Specifies which points from the positions array are going to be used
        0, 1, 2,
        2, 3, 0
    };

    float* floats = TransformVectorToFloat(positions); //Transform the Vector2 array to a float array

    float incrementR = 0.05f; //Increment of the r value

    VertexArray va;
    VertexBuffer vb(floats, 4 * 4 * sizeof(float));
    VertexBufferLayout layout;
    IndexBuffer ibo(indices, 6);

    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    renderer.Blend();

    ibo.Unbind();
    va.Unbind();
    shader.Unbind();
    vb.Unbind();
    while (!glfwWindowShouldClose(window))// Loop until the user closes the window
    {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        // Render here
        renderer.Clear();


        shader.Bind();
        renderer.Draw(va, ibo, shader);


       renderer.Swap(window); //Swap front and back buffers
       renderer.PollEvents();
    }
    renderer.Terminate(shader);
    return 0;
}
