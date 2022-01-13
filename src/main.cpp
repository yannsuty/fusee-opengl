// fusee.cpp : définit le point d'entrée de l'application.
//

#include "main.h"
//#include "error_handling.h"
//#include "error_handler.h"

using namespace std;
using namespace gl;
using namespace std::chrono;

int main() {
    //Store the start time of the program
    auto startTime = system_clock::now();
    //Auto declare an private object
    const auto windowPtr = []() {
        //Try to init glfw
        if (!glfwInit()) { //If glfw not init
            //Print error and exit
            fmt::print("glfw didnt initialize!\n");
            std::exit(EXIT_FAILURE);
        }
        //Define OpenGL Version 4.6
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

        //Use glfw method to to createWindow
        auto windowPtr = glfwCreateWindow(
            1280, 720, "Chapter 1 - Window Creation", nullptr, nullptr);

        //If error in creating window
        if (!windowPtr) {
            //Print error and exit glfw and the program
            fmt::print("window doesn't exist\n");
            glfwTerminate();
            std::exit(EXIT_FAILURE);
        }

        //define window position
        glfwSetWindowPos(windowPtr, 520, 180);
        //Make our window the current context
        glfwMakeContextCurrent(windowPtr);
        //Bind proc addresses easely
        glbinding::initialize(glfwGetProcAddress, false);
        return windowPtr;
    }();

    //Enable basic error checking in compilation of glew
    //glbinding::aux::enableGetErrorCallback();
    {
        //glEnable(GL_DEBUG_OUTPUT);
        //Set the gl method to use for error
        //glDebugMessageCallback(errorHandler::MessageCallback, 0);
        //Enable synchronous output
        //glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        //glDebugMessageControl(GL_DEBUG_SOURCE_API, GL_DEBUG_TYPE_OTHER, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, false);
    }

    //auto program = []() -> GLuint {
        const char* vertexShaderSource = R"(
            #version 460 core
            out vec3 colour;
            //layout (location = 0) in vec2 position;
            const vec4 vertices[] = vec4[]( vec4(-0.5f, -0.7f,    0.0, 1.0), 
                                            vec4( 0.5f, -0.7f,    0.0, 1.0),    
                                            vec4( 0.0f,  0.6888f, 0.0, 1.0));   
            const vec3 colours[] = vec3[](  vec3( 1.0, 0.0, 0.0), 
                                            vec3( 0.0, 1.0, 0.0),    
                                            vec3( 0.0, 0.0, 1.0));   
            void main(){
                colour = colours[gl_VertexID];
                gl_Position = vertices[gl_VertexID];  
            }
        )";

        const char* fragmentShaderSource = R"(
            #version 460 core
            in vec3 colour;
            out vec4 finalColor;
            void main() {
                finalColor = vec4(colour, 1.0);
            }
        )";

        auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);
        //Enable error print for the shader vertex
        //errorHandler::checkShader(vertexShader, "Vertex");

        auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
        glCompileShader(fragmentShader);
        //Enable error print for the shader fragment
        //errorHandler::checkShader(fragmentShader, "Fragment");

        auto program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);

        glLinkProgram(program);
      //  return program;
    //}();

    //gl_Position = vec4(position, 0.0f, 1.0f);
    //const std::array<glm::vec2, 3> vertices{ {{-0.5f, -0.7f}, {0.5f, -0.7f}, {0.0f, 0.6888f}} };
    //Get an ID for the buffer
    //GLuint bufferObject;
    //glCreateBuffers(1, &bufferObject);
    //Allocate the storage and transfer the data
    //Args : BufferID, size in bytes, the pointer to the data from our array, 
    //glNamedBufferStorage(bufferObject, vertices.size() * sizeof(glm::vec2), vertices.data(), GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT);

    //Create ID integer
    GLuint vao;
    glCreateVertexArrays(1, &vao);
    //Enable the attribut location in the shader
    //glEnableVertexArrayAttrib(vao, 0);
    // buffer to index mapping
    //glVertexArrayVertexBuffer(vao, 0, bufferObject, /*offset*/ 0, sizeof(glm::vec2));
    // attribute to index mapping. can query shader for its attributes
    //glVertexArrayAttribBinding(vao, glGetAttribLocation(program, "position"),/*buffer slot index*/ 0);
    // data stride
    //glVertexArrayAttribFormat(vao, /* shader attrobute location */ 0, glm::vec2::length(), GL_FLOAT, GL_FALSE, 0);

    glBindVertexArray(vao);

    //Declare a colour array
    std::array<GLfloat, 4> clearColour;

    glUseProgram(program);

    //While the window in not closed
    while (!glfwWindowShouldClose(windowPtr)) {
        //calcul the duration of the program
        auto currentTime = duration<float>(system_clock::now() - startTime).count();
        //Calcul color with the current time
        clearColour = { std::sin(currentTime) * 0.5f + 0.5f,
                       std::cos(currentTime) * 0.5f + 0.5f, 0.2f, 1.0f };
        //Clear current glfw buffer
        glClearBufferfv(GL_COLOR, 0, clearColour.data());
        //Draw triangles
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //Swap the buffer of glfw and our window
        glfwSwapBuffers(windowPtr);
        //Update window states (can checks if any events are triggered)
        glfwPollEvents();
    }
    //When the window is closed
    //Terminate glfw context
    glfwTerminate();
       
    return 0;
}
