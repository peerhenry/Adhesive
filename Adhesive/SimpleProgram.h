#pragma once
#include "GLSLProgram.h";
#include "pegcore/Initializable.hpp";
#include "pegglsl/PvmProgram.h";
#include <glm/glm.hpp>
using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::mat3;
using peg_glsl::PvmProgram;
class SimpleProgram : public pegcore::Initializable, public PvmProgram
{
private:
  IGlslProgram* program;
  mat4 PV;
  mat4 PVM;
  mat3 NormalMatrix;
public:
  SimpleProgram(IGlslProgram* program);
  ~SimpleProgram();
  void initialize();
  void setProjectionView(mat4 pv);
  void setModelMatrix(mat4 m);
  void setLight(vec3 lightDirection, vec3 lightColor);
  void setMaterialColor(vec3 color);
  void setAmbience(vec3 color);
};