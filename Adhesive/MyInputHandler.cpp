#include <cstdio>
#include <glm/vec4.hpp>
#include "MyInputHandler.h"
#include <iostream>

StandardCamera* localCam;
double oldX;
double oldY;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (action == GLFW_PRESS) {
    switch (key) {
    case GLFW_KEY_ESCAPE:
      glfwDestroyWindow(window);
      break;
    case GLFW_KEY_A:
      localCam->beginMovingForward();
      break;
    case GLFW_KEY_Z:
      localCam->beginMovingBackward();
      break;
    case GLFW_KEY_S:
      localCam->beginMovingLeft();
      break;
    case GLFW_KEY_D:
      localCam->beginMovingRight();
      break;
    case GLFW_KEY_SPACE:
      localCam->beginMovingUpward();
      break;
    case GLFW_KEY_LEFT_CONTROL:
      localCam->beginMovingDownward();
      break;
    default:
      float r = rand() % 256;
      float g = rand() % 256;
      float b = rand() % 256;
      glm::vec4 cc = glm::vec4(r / 256, g / 256, b / 256, 1);
      glClearColor(cc.r, cc.g, cc.b, cc.a);
    }
  }
  else if (action == GLFW_RELEASE) {
    switch (key) {
    case GLFW_KEY_A:
      localCam->stopMovingForward();
      break;
    case GLFW_KEY_Z:
      localCam->stopMovingBackward();
      break;
    case GLFW_KEY_S:
      localCam->stopMovingLeft();
      break;
    case GLFW_KEY_D:
      localCam->stopMovingRight();
    case GLFW_KEY_SPACE:
      localCam->stopMovingUpward();
      break;
    case GLFW_KEY_LEFT_CONTROL:
      localCam->stopMovingDownward();
      break;
    }
  }
}

void cursorCallback(GLFWwindow* window, double xpos, double ypos)
{
  double dX = (xpos - oldX);
  double dY = (ypos - oldY);
  if (dX != 0 || dY != 0) {
    double dTheta = 0.005 * dX;
    double dPhi = -0.005 * dY;
    localCam->rotate(dTheta, dPhi);
  }
  oldX = xpos;
  oldY = ypos;
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
}

MyInputHandler::MyInputHandler(StandardCamera* camera) {
  localCam = camera;
}

void MyInputHandler::initCursor(GLFWwindow* window) {
  glfwGetCursorPos(window, &oldX, &oldY);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

GLFWkeyfun MyInputHandler::getKeyCallback() {
  return keyCallback;
}

GLFWcursorposfun MyInputHandler::getCursorCallback() {
  return cursorCallback;
}

GLFWmousebuttonfun MyInputHandler::getMouseButtonCallback() {
  return mouseButtonCallback;
}