#include "Cube.h"

namespace cubeData {

  vector<float> pos = {
    -1, -1, -1, // south
    -1, -1,  1,
    1, -1, -1,
    1, -1,  1,

    1, -1, -1, // east
    1, -1,  1,
    1,  1, -1,
    1,  1,  1,

    1,  1, -1, // north
    1,  1,  1,
    -1,  1, -1,
    -1,  1,  1,

    -1,  1, -1, // west
    -1,  1,  1,
    -1, -1, -1,
    -1, -1,  1,

    -1, -1,  1, // top
    -1,  1,  1,
    1, -1,  1,
    1,  1,  1,

    -1,  1, -1, // bottom
    -1, -1, -1,
    1,  1, -1,
    1, -1, -1
  };

  vector<unsigned short> indices = {
    0, 1, 2, 2, 1, 3, // south
    4, 5, 6, 6, 5, 7, // east
    8, 9,10,10, 9,11, // north
    12,13,14,14,13,15, // west
    16,17,18,18,17,19, // top
    20,21,22,22,21,23  // bottom
  };

  vector<float> normals = {
    0, -1,  0,  // south normal -y
    0, -1,  0,
    0, -1,  0,
    0, -1,  0,
    1,  0,  0,  // east normal +x
    1,  0,  0,
    1,  0,  0,
    1,  0,  0,
    0,  1,  0,  // north normal +y
    0,  1,  0,
    0,  1,  0,
    0,  1,  0,
    -1,  0,  0,  // west normal -x
    -1,  0,  0,
    -1,  0,  0,
    -1,  0,  0,
    0,  0,  1,  // top normal +z
    0,  0,  1,
    0,  0,  1,
    0,  0,  1,
    0,  0, -1,   // bottom normal -z
    0,  0, -1,
    0,  0, -1,
    0,  0, -1
  };
}

Cube::Cube(SimpleProgram* glProgram)
{
  modelMatrix = mat4(1.0f);
  this->glProgram = glProgram;
  buffer = new PniBuffer(cubeData::pos, cubeData::normals, cubeData::indices);
}

Cube::~Cube()
{
  delete(buffer);
}

void Cube::initialize() {

  buffer->initialize();

  // set other uniforms
  glProgram->setAmbience(vec3(0.3f));
  glProgram->setLight(
    vec3(2, 0.5f, -1),  // direction
    vec3(0.9f));        // color
}

void Cube::update(double dt) {
  modelMatrix = glm::rotate(modelMatrix, glm::radians((float)(90*dt)), vec3(0, 0, 1));
}

void Cube::render() {
  glProgram->setMaterialColor(color);
  glProgram->setModelMatrix(modelMatrix);
  buffer->render();
}

void Cube::translate(float x, float y, float z)
{
  modelMatrix = glm::translate(modelMatrix, vec3(x, y, z));
}

void Cube::setColor(float r, float g, float b) {
  color = vec3(r, g, b);
}