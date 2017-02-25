#include "Cube.h"

Cube::Cube(SimpleProgram* glProgram)
{
  modelMatrix = mat4(1.0f);
  this->glProgram = glProgram;
}

Cube::~Cube()
{
}

float pos[] = {
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

unsigned short indices[] = {
   0, 1, 2, 2, 1, 3, // south
   4, 5, 6, 6, 5, 7, // east
   8, 9,10,10, 9,11, // north
  12,13,14,14,13,15, // west
  16,17,18,18,17,19, // top
  20,21,22,22,21,23  // bottom
};

float normals[] = {
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
   0,  0, -1,
};


void Cube::initialize() {

  // create buffers
  GLuint vboHandles[3];
  glGenBuffers(3, vboHandles);
  GLuint posBufferHandle = vboHandles[0];
  GLuint normalBufferHandle = vboHandles[1];
  indexBufferHandle = vboHandles[2];

  // populate buffers
  glBindBuffer(GL_ARRAY_BUFFER, posBufferHandle);
  glBufferData(GL_ARRAY_BUFFER, 72 * sizeof(float), pos, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, normalBufferHandle);
  glBufferData(GL_ARRAY_BUFFER, 72 * sizeof(float), normals, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, indexBufferHandle);
  glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(unsigned short), indices, GL_STATIC_DRAW);

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

  // set divisor for normals
  //glVertexBindingDivisor(1, 4);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  // set other uniforms
  glProgram->setAmbience(vec3(0.3f));
  glProgram->setLight(
    vec3(2, 0.5f, -1),  // direction
    vec3(0.9f));      // color
}

void Cube::update(double dt) {
  modelMatrix = glm::rotate(modelMatrix, glm::radians((float)(90*dt)), vec3(0, 0, 1));
}

void Cube::render() {
  // upload material color
  glProgram->setMaterialColor(color);
  // upload model matrix
  glProgram->setModelMatrix(modelMatrix);

  glBindVertexArray(vaoHandle);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferHandle);
  glDrawElements(
    GL_TRIANGLES,       // mode
    36,                 // count: 36 indices
    GL_UNSIGNED_SHORT,  // type
    nullptr             // offset
  );
}

void Cube::translate(float x, float y, float z)
{
  modelMatrix = glm::translate(modelMatrix, vec3(x, y, z));
}

void Cube::setColor(float r, float g, float b) {
  color = vec3(r, g, b);
}