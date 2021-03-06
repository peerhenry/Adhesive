#pragma once
#include "BasicObject.h"
#include "PniBuffer.h"
class Cube : public BasicObject
{
private:
  SimpleProgram* glProgram;
  PniBuffer* buffer;
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