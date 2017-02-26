#pragma once
#include <fstream>
#include <sstream>
#include <string>

#include <GL/glew.h>
#include "glm/glm.hpp"

#include "pegcore/SceneObject.hpp"
using std::string;
using pegcore::SceneObject;

class DebugHud : public SceneObject
{
private:
  GLuint fontTexHandle;
  void loadTexture();
  void drawCharacter(char c);
  string fpsString;
  void updateFps();
public:
  DebugHud();
  ~DebugHud();
  void initialize();
  void update(double dt);
  void render();
};

