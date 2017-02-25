#pragma once
#include "GlfwCallbackProvider.h"
#include "StandardCamera.h"
class MyInputHandler : public GlfwCallbackProvider
{
private:
  StandardCamera* camera;
public:
  MyInputHandler(StandardCamera* camera);
  void initCursor(GLFWwindow* window);
  GLFWkeyfun getKeyCallback();
  GLFWcursorposfun getCursorCallback();
  GLFWmousebuttonfun getMouseButtonCallback();
};