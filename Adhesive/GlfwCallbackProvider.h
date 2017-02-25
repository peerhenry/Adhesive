#pragma once
#include <map>
#include <glfw/glfw3.h>
#include "pegcore/Command.h"
using std::map;
using pegcore::command;

class GlfwCallbackProvider {
public:
  virtual void initCursor(GLFWwindow* window) = 0;
  virtual GLFWkeyfun getKeyCallback() = 0;
  virtual GLFWcursorposfun getCursorCallback() = 0;
  virtual GLFWmousebuttonfun getMouseButtonCallback() = 0;
};