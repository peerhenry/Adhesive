#include <cstdio>
#include <iostream>
#include <map>
using std::map;

#include "GlslProgram.h"
#include "StandardScene.h"
#include "GlfwContext.h"
#include "MyInputHandler.h"
#include "Cube.h"
#include "Rectangle.h"
#include "SimpleProgram.h"

#include "GlfwCallbackGenerator.h"

#include "pegcore/Command.h"
#include "GlfwStandardCallbackProvider.h"
using peg_glfw::GlfwStandardCallbackProvider;



namespace demo{

GLFWwindow* localWindow;
StandardCamera* localCamera;

map<string, command> getCommandMap() {
  map<string, command> commandMap;
  commandMap["quit"] = command([]() { glfwDestroyWindow(localWindow); });
  commandMap["random background"] = command([]() {
    float r = rand() % 256;
    float g = rand() % 256;
    float b = rand() % 256;
    glm::vec4 cc = glm::vec4(r / 256, g / 256, b / 256, 1);
    glClearColor(cc.r, cc.g, cc.b, cc.a);
  });
  commandMap["forward"] = command(
    []() { localCamera->beginMovingForward(); },
    []() { localCamera->stopMovingForward(); }
  );
  commandMap["backward"] = command(
    []() { localCamera->beginMovingBackward(); },
    []() { localCamera->stopMovingBackward(); }
  );
  commandMap["left"] = command(
    []() { localCamera->beginMovingLeft(); },
    []() { localCamera->stopMovingLeft(); }
  );
  commandMap["right"] = command(
    []() { localCamera->beginMovingRight(); },
    []() { localCamera->stopMovingRight(); }
  );
  commandMap["up"] = command(
    []() { localCamera->beginMovingUpward(); },
    []() { localCamera->stopMovingUpward(); }
  );
  commandMap["down"] = command(
    []() { localCamera->beginMovingDownward(); },
    []() { localCamera->stopMovingDownward(); }
  );
  return commandMap;
}

map<string, string> getControlMap() {
  map<string, string> controls;
  controls["escape"] = "quit";
  controls["a"] = "forward";
  controls["z"] = "backward";
  controls["s"] = "left";
  controls["d"] = "right";
  controls["space"] = "up";
  controls["left-control"] = "down";
  controls["q"] = "random background";
  return controls;
}

map<string, command> generateControlCommandMap(map<string, string>* controls, map<string, command>* commands) {
  map<string, command> controlCommandMap; // couples key names to commands
  for (auto control = controls->begin(); control != controls->end(); ++control) {
    string key = control->first;
    string commandName = control->second;
    command nextCommand = commands->at(commandName);
    controlCommandMap[key] = nextCommand;
  }
  return controlCommandMap;
}

int breakPoint(const char* msg = "") {
  printf(msg);
  printf("\n");
  printf("Press any key");
  printf("\n");
  int yo = 0;
  std::cin >> yo;
  return 0;
}

int run(void)
{
  printf("Starting program");
  // create dependency tree
  /*const int width = 1600;
  const int height = 900;//*/
  /*const int width = 1024;
  const int height = 768;//*/
  const int width = 640;
  const int height = 480;//*/
  float aspect = ((float)width) / height;
  const char* name = "Test of cubes";
  IGlslProgram* program = new GLSLProgram();
  SimpleProgram simpleProgram = SimpleProgram(program);
  GlfwContext context = GlfwContext(width, height, name, &simpleProgram);

  // initialize glfw, glew and load shaders
  context.initialize();
  localWindow = context.getWindow();

  StandardCamera camera = StandardCamera(&simpleProgram, glm::radians(45.0f), aspect, 0.1f, 100);
  localCamera = &camera;
  localCamera->setLocation(0, -40, 0);

  CursorCallback cursorCallback = [](double x, double y, double dx, double dy) {
    double dTheta = 0.005 * dx;
    double dPhi = -0.005 * dy;
    localCamera->rotate(dTheta, dPhi);
  };

  map<string, command> commands = getCommandMap(); // couples command names to commands
  map<string, string> controls = getControlMap(); // couples key names to command names
  map<string, command> controlCommandMap = generateControlCommandMap(&controls, &commands); // couples key names to commands

  peg_glfw::pressReleaseMaps maps = peg_glfw::generateInput(&controlCommandMap);
  peg_glfw::glfwCommandMap pressMap = maps.first;
  peg_glfw::glfwCommandMap releaseMap = maps.second;
  GlfwStandardCallbackProvider handler = GlfwStandardCallbackProvider(&pressMap, &releaseMap, cursorCallback);
  context.setInput(&handler);

  StandardScene scene = StandardScene(localCamera);

  Rectangle rec = Rectangle(&simpleProgram);
  scene.addSceneObject(&rec);

  Cube cube1 = Cube(&simpleProgram);
  Cube cube2 = Cube(&simpleProgram);
  Cube cube3 = Cube(&simpleProgram);
  cube1.translate(0, 0, 1);
  cube1.setColor(0, 1, 0);
  cube2.translate(5, 0, 2);
  cube2.setColor(1, 0, 0);
  cube3.translate(-5, 0, 3);
  cube3.setColor(0, 0, 1);
  scene.addSceneObject(&cube1);
  scene.addSceneObject(&cube2);
  scene.addSceneObject(&cube3);

  context.setScene(&scene);

  // run program
  context.run();

  printf("Closing program");

  delete(program);
  return 0;
}

}