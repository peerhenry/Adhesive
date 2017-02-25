#ifndef GLUTILS_H
#define GLUTILS_H

#include "gl/glew.h"

namespace GLUtils
{
  int checkForOpenGLError(const char *, int);

  void dumpGLInfo(bool dumpExtensions = false);
};

#endif // GLUTILS_H