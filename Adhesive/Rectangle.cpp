#include "Rectangle.h"

namespace recData {
  vector<float> getPos(float size) {
    vector<float> output = {
      -size, -size, 0,
      -size,  size, 0,
       size, -size, 0,
       size,  size, 0
    };
    return output;
  }

  vector<float> normals = {
    0, 0, 1,
    0, 0, 1,
    0, 0, 1,
    0, 0, 1
  };

  vector<unsigned short> indices = {
    0, 1, 2, 2, 1, 3
  };
}

Rectangle::Rectangle(SimpleProgram* glProgram)
{
  color = vec3(1);
  modelMatrix = mat4(1);
  this->glProgram = glProgram;
  vector<float> pos = recData::getPos(100.0f);
  buffer = new PniBuffer(pos, recData::normals, recData::indices);
}

Rectangle::~Rectangle()
{
  delete(buffer);
}

void Rectangle::initialize() {
  buffer->initialize();
}

void Rectangle::update(double dt) {

}

void Rectangle::render() {
  glProgram->setMaterialColor(color);
  glProgram->setModelMatrix(modelMatrix);
  buffer->render();
}

void Rectangle::translate(float x, float y, float z) {

}

void Rectangle::setColor(float r, float g, float b) {
  color = vec3(r, g, b);
}