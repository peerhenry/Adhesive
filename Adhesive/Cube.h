#pragma once
#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "pegcore/SceneObject.hpp"
#include "SimpleProgram.h"
using pegcore::SceneObject;
class Cube : public SceneObject
{
private:
  SimpleProgram* glProgram;
  GLuint vaoHandle;
  GLuint indexBufferHandle;
  mat4 modelMatrix;
  vec3 color;
public:
  Cube(SimpleProgram* glProgram);
  ~Cube();
  void initialize();
  void update(double dt);
  void render();
  void translate(float x, float y, float z);
  void setColor(float r, float g, float b);
};