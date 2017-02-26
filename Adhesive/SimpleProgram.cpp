#include "SimpleProgram.h"

SimpleProgram::SimpleProgram(IGlslProgram* program)
{
  this->program = program;
}

SimpleProgram::~SimpleProgram()
{

}

void SimpleProgram::initialize() {
  GLenum err = glewInit();
  if (GLEW_OK != err) {
    fprintf(stderr, "Error initiaalizing GLEW: %s\n", glewGetErrorString(err));
  }

  program->compileShader("basic.vert");
  program->compileShader("basic.frag");
  program->link();
  program->validate();
  program->use();

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_CULL_FACE);
  glFrontFace(GL_CW);// clockwise faces are front
}

void SimpleProgram::setProjectionView(mat4 pv) {
  PV = pv;
}

void SimpleProgram::setModelMatrix(mat4 m) {
  PVM = PV*m;
  program->setUniform("PVM", PVM);
  mat3 normalMatrix = mat3(m);
  program->setUniform("NormalMatrix", normalMatrix);
}

void SimpleProgram::setAmbience(vec3 color) {
  program->setUniform("AmbientColor", color);
}

void SimpleProgram::setLight(vec3 lightDirection, vec3 lightColor) {
  program->setUniform("LightDirection", lightDirection);
  program->setUniform("LightColor", lightColor);
}

void SimpleProgram::setMaterialColor(vec3 color) {
  program->setUniform("MaterialColor", color);
}