#pragma once
#include <map>
#include <glfw/glfw3.h>
#include "pegcore/Command.h"
#include "GlfwCallbackProvider.h"
using std::map;
using pegcore::command;
using pegcore::InputCallback;
using pegcore::CursorCallback;

namespace peg_glfw {
  class GlfwStandardCallbackProvider : public GlfwCallbackProvider
  {
  public:
    GlfwStandardCallbackProvider(map<int, InputCallback>* pressCommands, map<int, InputCallback>* releaseCommands, CursorCallback cursorCallback);
    ~GlfwStandardCallbackProvider();
    void initCursor(GLFWwindow* window);
    GLFWkeyfun getKeyCallback();
    GLFWcursorposfun getCursorCallback();
    GLFWmousebuttonfun getMouseButtonCallback();
  };
}