#pragma once
#include <gl/glew.h>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>

#include <vector>
#include <string>

#include <stdexcept>

// MSVC Will Spit Out All Sorts Of Useless Warnings If
// You Create Vectors Of Strings, This Pragma Gets Rid Of Them.
#pragma warning(disable: 4786)

namespace freetype {
  using std::vector;
  using std::string;

  struct font_data {
    float height; // font height
    GLuint * textures; // texture handles
    GLuint list_base;

    void init(const char* fontName, unsigned int height);

    void clean();
  };

  void print(const font_data &ft_font, float x, float y, const char* fmt, ...);
}