#include "GlfwContext.h"

GlfwContext::GlfwContext(int width, int height, const char* name, Initializable* graphicsProgram)
{
  this->width = width;
  this->height  = height;
  this->name = name;
  this->graphicsProgram = graphicsProgram;
}

void GlfwContext::initialize() {
  if (!glfwInit()) return;

  /* Create a windowed mode window and its OpenGL context */
  //glfwWindowHint(GLFW_DECORATED, false); // hide title bar
  glfwWindowHint(GLFW_SAMPLES, 4); // anti alias
  window = glfwCreateWindow(width, height, name, NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    printf("Error: Could not create window.");
    return;
  }

  glfwMakeContextCurrent(window);
  int xOffset = (1920 - width) / 2;
  int yOffset = (1080- height) / 2;
  glfwSetWindowPos(window, xOffset, yOffset);
  graphicsProgram->initialize();
}

GLFWwindow* GlfwContext::getWindow() {
  return window;
}

void GlfwContext::setInput(GlfwCallbackProvider* handler) {
  handler->initCursor(window);
  glfwSetKeyCallback(window, handler->getKeyCallback());
  glfwSetCursorPosCallback(window, handler->getCursorCallback());
  glfwSetMouseButtonCallback(window, handler->getMouseButtonCallback());
}

void GlfwContext::setScene(Scene* scene) {
  this->scene = scene;
}

void GlfwContext::run() {
  if (!scene) {
    printf("Error: cannot run before a scene is set!");
    return;
  }//*/

  /* Create the loop */
  double oldtime = glfwGetTime();
  while (!glfwWindowShouldClose(window))
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    double newtime = glfwGetTime();
    double dt = newtime - oldtime;
    scene->update(dt);
    scene->render();

    glfwSwapBuffers(window);
    glfwPollEvents();
    oldtime = newtime;
  }

  /* Terminate after the loop is finished */
  glfwTerminate();
}

GlfwContext::~GlfwContext()
{
  glfwTerminate();
}
