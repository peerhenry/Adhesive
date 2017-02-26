#include "freetype.h"
#include <iostream>

namespace freetype {

  // get the first power of 2 >= a
  inline int next_p2(int a) {
    int rval = 1;
    while (rval < a) rval <<= 1;
    return rval;
  }

  // create a display list for a character
  void makeDisplayList(FT_Face face, unsigned char ch, GLuint list_base, GLuint * tex_base) {
    // 1. FT_Load_Glyph
    if (FT_Load_Glyph(face, FT_Get_Char_Index(face, ch), FT_LOAD_DEFAULT))
      throw std::runtime_error("FT_Load_Glyph failed!");

    // 2. FT_Get_Glyph
    FT_Glyph glyph;
    if( FT_Get_Glyph(face->glyph, &glyph ))
      throw std::runtime_error("FT_Get_Glyph failed!");

    // 3. FT_Glyph_To_Bitmap
    FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
    FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

    // 4. FT_Bitmap creation
    FT_Bitmap& bitmap = bitmap_glyph->bitmap;

    int width = next_p2( bitmap.width );
    int height = next_p2( bitmap.rows );//*/

    // allocate memory
    GLubyte* expanded_data = new GLubyte[2 * width * height];

    // Here We Fill In The Data For The Expanded Bitmap.
    // Notice That We Are Using A Two Channel Bitmap (One For
    // Channel Luminosity And One For Alpha), But We Assign
    // Both Luminosity And Alpha To The Value That We
    // Find In The FreeType Bitmap.
    // We Use The ?: Operator To Say That Value Which We Use
    // Will Be 0 If We Are In The Padding Zone, And Whatever
    // Is The FreeType Bitmap Otherwise.
    /*for (int j = 0; j <height; j++) {
      for (int i = 0; i < width; i++) {
        expanded_data[2 * (i + j*width)] = expanded_data[2 * (i + j*width) + 1] =
          (i >= bitmap.width || j >= bitmap.rows) ?
          0 : bitmap.buffer[i + bitmap.width*j];
      }
    }//*/
    for (int j = 0; j < height; j++) { // produce softer, less jaggy image.
      for (int i = 0; i < width; i++) {
        expanded_data[2 * (i + j * width)] = 255;
        expanded_data[2 * (i + j * width) + 1] =
          (i >= bitmap.width || j >= bitmap.rows) ? 0 : bitmap.buffer[i + bitmap.width * j];
      }
    }//*/

    // 5. opengl textures
    glBindTexture(GL_TEXTURE_2D, tex_base[ch]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, expanded_data);

    // 6. remove data after upload
    delete[] expanded_data;

    // 7. create display list
    glNewList(list_base + ch, GL_COMPILE);

    glBindTexture(GL_TEXTURE_2D, tex_base[ch]);

    glPushMatrix();

    // First We Need To Move Over A Little So That
    // The Character Has The Right Amount Of Space
    // Between It And The One Before It.
    glTranslatef(bitmap_glyph->left, 0, 0);

    // Now We Move Down A Little In The Case That The
    // Bitmap Extends Past The Bottom Of The Line
    // This Is Only True For Characters Like 'g' Or 'y'.
    GLfloat yOffset = bitmap_glyph->top - (int)bitmap.rows;
    glTranslatef(0, yOffset, 0); // THE CULPRIT!

    float x = (float)bitmap.width / (float)width,
      y = (float)bitmap.rows / (float)height;

    glBegin(GL_QUADS);
    glTexCoord2d(x, 0); glVertex2f(bitmap.width, bitmap.rows);
    glTexCoord2d(x, y); glVertex2f(bitmap.width, 0);
    glTexCoord2d(0, y); glVertex2f(0, 0);
    glTexCoord2d(0, 0); glVertex2f(0, bitmap.rows);
    glEnd();
    glPopMatrix();
    glTranslated(face->glyph->advance.x >> 6, 0, 0);

    // Increment The Raster Position As If We Were A Bitmap Font.
    // (Only Needed If You Want To Calculate Text Length)
    // glBitmap(0,0,0,0,face->glyph->advance.x >> 6,0,NULL);

    glEndList();
    FT_Done_Glyph(glyph);
    //std::cout << "display lists succesfully made" << std::endl; // DEBUG
  }

  void font_data::init(const char* fontName, unsigned int height) {
    textures = new GLuint[128];
    this->height = height;

    FT_Library library;
    if (FT_Init_FreeType(&library)) throw std::runtime_error("FT_Init_FreeType failed!");

    FT_Face face;
    if (FT_New_Face(library, fontName, 0, &face)) throw std::runtime_error("FT_New_Face failed!");

    // For Some Twisted Reason, FreeType Measures Font Size
    // In Terms Of 1/64ths Of Pixels.  Thus, To Make A Font
    // h Pixels High, We Need To Request A Size Of h*64.
    FT_Set_Char_Size(face, height << 6, height << 6, 96, 96);

    list_base = glGenLists(128);
    glGenTextures(128, textures);

    // offset 24?
    for (unsigned char i = 33; i < 128+33; i++) { // 0, 128
      makeDisplayList(face, i, list_base, textures);
    }

    // We Don't Need The Face Information or the library Now That The Display
    // Lists Have Been Created, So We Free The Assosiated Resources.
    FT_Done_Face(face);
    FT_Done_FreeType(library);

    std::cout << "font_data succesfully initialized" << std::endl;
  }

  void font_data::clean() {
    glDeleteLists(list_base, 128);
    glDeleteTextures(128, textures);
    delete[] textures;
  }

  // A Fairly Straightforward Function That Pushes
  // A Projection Matrix That Will Make Object World
  // Coordinates Identical To Window Coordinates.
  inline GLdouble pushScreenCoordinateMatrix() {
    glPushAttrib(GL_TRANSFORM_BIT);
    GLint   viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport); // gets x, y, width, height
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(viewport[0], viewport[2], viewport[1], viewport[3], -1, 1);
    glPopAttrib();
    return viewport[3];
  }

  // Pops The Projection Matrix Without Changing The Current
  // MatrixMode.
  inline void pop_projection_matrix() {
    glPushAttrib(GL_TRANSFORM_BIT);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
  }

  void print(const font_data &ft_font, float x, float y, const char* fmt, ...) {
    // We Want A Coordinate System Where Distance Is Measured In Window Pixels.
    GLdouble viewHeight = pushScreenCoordinateMatrix();

    GLuint font = ft_font.list_base;
    // We Make The Height A Little Bigger.  There Will Be Some Space Between Lines.
    float h = ft_font.height / .63f;
    char    text[256];                                  // Holds Our String
    va_list ap;                                     // Pointer To List Of Arguments

    if (fmt == NULL)                                    // If There's No Text
      *text = 0;                                    // Do Nothing
    else {
      va_start(ap, fmt);                              // Parses The String For Variables
      vsprintf(text, fmt, ap);                            // And Converts Symbols To Actual Numbers
      va_end(ap);                                 // Results Are Stored In Text
    }

    // Here Is Some Code To Split The Text That We Have Been
    // Given Into A Set Of Lines. 
    // This Could Be Made Much Neater By Using
    // A Regular Expression Library Such As The One Available From
    // boost.org (I've Only Done It Out By Hand To Avoid Complicating
    // This Tutorial With Unnecessary Library Dependencies).
    const char *start_line = text;
    vector<string> lines;
    for (const char *c = text; *c; c++) {
      if (*c == '\n') {
        string line;
        for (const char *n = start_line; n<c; n++) line.append(1, *n);
        lines.push_back(line);
        start_line = c + 1;
      }
    }
    if (start_line) {
      string line;
      for (const char *n = start_line; *n; n++) line.append(1, *n);
      lines.push_back(line);
    }

    /*//*/

    glPushAttrib(GL_LIST_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT | GL_TRANSFORM_BIT);
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glListBase(font);

    float modelview_matrix[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);

    // This Is Where The Text Display Actually Happens.
    // For Each Line Of Text We Reset The Modelview Matrix
    // So That The Line's Text Will Start In The Correct Position.
    // Notice That We Need To Reset The Matrix, Rather Than Just Translating
    // Down By h. This Is Because When Each Character Is
    // Drawn It Modifies The Current Matrix So That The Next Character
    // Will Be Drawn Immediately After It. 
    for (int i = 0; i<lines.size(); i++) {
      glPushMatrix();
      glLoadIdentity();
      glTranslatef(x, viewHeight  - y - h*i, 0);
      glMultMatrixf(modelview_matrix);
      // std::cout << "there are lines : )" << std::endl; // DEBUG
      // std::cout << lines[i].c_str() << std::endl; // DEBUG
      // The Commented Out Raster Position Stuff Can Be Useful If You Need To
      // Know The Length Of The Text That You Are Creating.
      // If You Decide To Use It Make Sure To Also Uncomment The glBitmap Command
      // In make_dlist().
      //glRasterPos2f(0,0);
      glCallLists(lines[i].length(), GL_UNSIGNED_BYTE, lines[i].c_str());
      // float rpos[4];
      // glGetFloatv(GL_CURRENT_RASTER_POSITION ,rpos);
      // float len=x-rpos[0]; (Assuming No Rotations Have Happend)

      glPopMatrix();
    }

    glPopAttrib();

    pop_projection_matrix();
  }
}