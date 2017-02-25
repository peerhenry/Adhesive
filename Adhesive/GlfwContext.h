#pragma once
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include <cstdio>
#include "pegcore/Context.hpp"
#include "pegcore/Scene.hpp"
#include "pegcore/Initializable.hpp"
#include "GlfwCallbackProvider.h"
using pegcore::Scene;
using pegcore::Initializable;

class GlfwContext
{
private:
  GLFWwindow* window;
  Initializable* graphicsProgram;
  Scene* scene;
  int width, height;
  const char* name;
public:
  GlfwContext(int width, int height, const char* name, Initializable* graphicsProgram);
  ~GlfwContext();
  void setInput(GlfwCallbackProvider* handler);
  void initialize();
  GLFWwindow* getWindow();
  void setScene(Scene* scene);
  void run();
};