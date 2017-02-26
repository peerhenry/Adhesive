#pragma once
#include <vector>
#include <GL/glew.h>
#include "pegcore/initializable.hpp"
#include "pegcore/renderable.hpp"
using std::vector;
class PniBuffer : public pegcore::Initializable, pegcore::Renderable
{
private:
  GLuint vaoHandle;
  GLuint indexBufferHandle;
  vector<float> pos;
  vector<float> normals;
  vector<unsigned short> indices;
  int indexCount;
public:
  PniBuffer(vector<float> pos, vector<float> normals, vector<unsigned short> indices);
  ~PniBuffer();
  void initialize();
  void render();
};

