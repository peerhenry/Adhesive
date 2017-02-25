#include "GlfwStandardCallbackProvider.h"
using peg_glfw::GlfwStandardCallbackProvider;

namespace peg_glfw {
  map<int, InputCallback>* localPressCommands;
  map<int, InputCallback>* localReleaseCommands;
  pegcore::CursorCallback localCursorCallback;
  double oldX;
  double oldY;

  void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    if (action == GLFW_PRESS) {
      InputCallback callback = (*localPressCommands)[key];
      if (callback)(*callback)();
    }
    else if (action == GLFW_RELEASE) {
      InputCallback callback = (*localReleaseCommands)[key];
      if (callback)(*callback)();
    }
  }

  void cursorCallback(GLFWwindow* window, double xpos, double ypos)
  {
    double dX = (xpos - oldX);
    double dY = (ypos - oldY);
    if (dX != 0 || dY != 0) {
      localCursorCallback(xpos, ypos, dX, dY);
    }
    oldX = xpos;
    oldY = ypos;
  }
}

GlfwStandardCallbackProvider::GlfwStandardCallbackProvider(map<int, InputCallback>* pressCommands, map<int, InputCallback>* releaseCommands, CursorCallback cursorCallback)
{
  localPressCommands = pressCommands;
  localReleaseCommands = releaseCommands;
  localCursorCallback = cursorCallback;
}

GlfwStandardCallbackProvider::~GlfwStandardCallbackProvider()
{

}

void GlfwStandardCallbackProvider::initCursor(GLFWwindow* window)
{
  glfwGetCursorPos(window, &oldX, &oldY);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

GLFWkeyfun GlfwStandardCallbackProvider::getKeyCallback()
{
  return keyCallback;
}

GLFWcursorposfun GlfwStandardCallbackProvider::getCursorCallback()
{
  return cursorCallback;
}

GLFWmousebuttonfun GlfwStandardCallbackProvider::getMouseButtonCallback()
{
  return [](GLFWwindow* window, int button, int action, int mods) {};
}