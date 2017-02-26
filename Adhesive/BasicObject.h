#pragma once
#include <vector>
#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "pegcore/SceneObject.hpp"
#include "SimpleProgram.h"
#include "PniBuffer.h"
using std::vector;
using pegcore::SceneObject;
class BasicObject : public SceneObject
{
public:
  virtual void translate(float x, float y, float z) = 0;
  virtual void setColor(float r, float g, float b) = 0;
};