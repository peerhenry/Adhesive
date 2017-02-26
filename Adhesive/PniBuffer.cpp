#include "PniBuffer.h"

PniBuffer::PniBuffer(vector<float> pos, vector<float> normals, vector<unsigned short> indices)
{
  this->pos = pos;
  this->normals = normals;
  this->indices = indices;
  indexCount = indices.size();
}

PniBuffer::~PniBuffer()
{
}

void PniBuffer::initialize() {
  // create buffers
  GLuint vboHandles[3];
  glGenBuffers(3, vboHandles);
  GLuint posBufferHandle = vboHandles[0];
  GLuint normalBufferHandle = vboHandles[1];
  indexBufferHandle = vboHandles[2];

  // upload buffers
  int posByteSize = sizeof(float) * pos.size();
  int normalsByteSize = sizeof(float) * normals.size();
  int indicesByteSize = sizeof(unsigned int) * indices.size();
  glBindBuffer(GL_ARRAY_BUFFER, posBufferHandle);
  glBufferData(GL_ARRAY_BUFFER, posByteSize, &pos.front(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, normalBufferHandle);
  glBufferData(GL_ARRAY_BUFFER, normalsByteSize, &normals.front(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, indexBufferHandle);
  glBufferData(GL_ARRAY_BUFFER, indicesByteSize, &indices.front(), GL_STATIC_DRAW);

  // create VAO
  glGenVertexArrays(1, &vaoHandle);
  glBindVertexArray(vaoHandle);

  // map indices to buffers
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, posBufferHandle);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)nullptr);

  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, normalBufferHandle);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)nullptr);
}

void PniBuffer::render() {
  glBindVertexArray(vaoHandle);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferHandle);
  glDrawElements(
    GL_TRIANGLES,       // mode
    indexCount,         // count
    GL_UNSIGNED_SHORT,  // type
    nullptr             // offset
  );
}