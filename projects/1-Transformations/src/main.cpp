#include <common/Common.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

namespace Settings
{
    const float SCR_WIDTH{ 800 };
    const float SCR_HEIGHT{ 600 };

    float degreesX{ 0 };
    float degreesY{ 0 };
    float degreesZ{ 0 };

    bool usePerspective{ true };
    bool pPressedLastFrame{ false };
}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window{ glfwCreateWindow(Settings::SCR_WIDTH, Settings::SCR_HEIGHT, "LearnOpenGL", NULL, NULL) };
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
 
    // build and compile our shader program
    // ------------------------------------
    Shader shaderProgram{ "shaders/vertex.vert","shaders/fragment.frag"};

    cy::TriMesh mesh;
    bool success{ mesh.LoadFromFileObj("models/teapot.obj") };
    
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cy::Vec3f)*mesh.NV(), &mesh.V(0), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // as we only have a single shader, we could also just activate our shader once beforehand if we want to 
    shaderProgram.useProgram();

    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        glm::mat4 projection{};
        glm::vec4 color{};
        if (Settings::usePerspective) 
        {
            projection = glm::perspective(
                glm::radians(45.0f),
                Settings::SCR_WIDTH / Settings::SCR_HEIGHT,
                0.1f, 100.0f
            );
            color = { 1,0,0,1 };
        }
        else {
            float distance{ 50.0f };
            float aspect{ Settings::SCR_WIDTH / Settings::SCR_HEIGHT };
            float halfHeight{ distance * tan(glm::radians(45.0f) / 2.0f) };
            float halfWidth{ halfHeight * aspect };

            projection = glm::ortho(
                -halfWidth,   
                halfWidth,   
                -halfHeight,            
                halfHeight,            
                0.1f,                  
                100.0f                 
            );
            color = { 0,1,0,1 };
        }
        shaderProgram.setVec4("color", glm::value_ptr(color));
        shaderProgram.setMatrix4("projection",
            glm::value_ptr(projection));

        glm::mat4 view{ 1.0f };
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -50.0f));
        view = glm::rotate(view, glm::radians(Settings::degreesX), glm::vec3(1.0f, 0.0f, 0.f));
        view = glm::rotate(view, glm::radians(Settings::degreesY), glm::vec3(0.0f, 1.0f, 0.f));
        view = glm::rotate(view, glm::radians(Settings::degreesZ), glm::vec3(0.0f, 0.0f, 1.f));
        shaderProgram.setMatrix4("view", glm::value_ptr(view));

        // render
        // ------
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render the triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS, 0, mesh.NV());

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);


    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        Settings::degreesX += 2.5;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        Settings::degreesY += 2.5;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        Settings::degreesZ += 2.5;
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        Settings::degreesX = 0;
        Settings::degreesY = 0;
        Settings::degreesZ = 0;
    }

    bool pCurrentlyPressed{ (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) };
    if (pCurrentlyPressed && !Settings::pPressedLastFrame) {
        Settings::usePerspective = !Settings::usePerspective;
    }
    Settings::pPressedLastFrame = pCurrentlyPressed;
  
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}