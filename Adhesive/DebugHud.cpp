#include "DebugHud.h"
#include <iostream>
#include <sstream> // stringstream
#include "freetype.h"

DebugHud::DebugHud()
{
}

DebugHud::~DebugHud()
{

}

freetype::font_data font;

void DebugHud::initialize() {
  /*glShadeModel(GL_SMOOTH);                // Enable Smooth Shading
  glClearDepth(1.0f);                 // Depth Buffer Setup
  glEnable(GL_DEPTH_TEST);                // Enables Depth Testing
  glDepthFunc(GL_LEQUAL);                 // The Type Of Depth Testing To Do
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Really Nice Perspective Calculations */
  font.init("arial.ttf", 16);
  fpsString = "";
}

double accumulate = 0;
int frames = 0;

void DebugHud::updateFps() {
  std::stringstream stream;
  stream << "FPS: " << frames << "\n";
  fpsString = stream.str();
}

void DebugHud::update(double dt) {
  accumulate += dt;
  if (accumulate > 1) {
    accumulate -= 1;
    updateFps();
    frames = 0;
  }
}

void DebugHud::render() {
  frames++;
  GLint id;
  glGetIntegerv(GL_CURRENT_PROGRAM, &id);
  glUseProgram(0);

  // std::cout << "rendering debughud" << std::endl; // passed!

  // go wild!
  glClear(GL_DEPTH_BUFFER_BIT);
  //freetype::print(font, 0, 16, "abcdefghijklmnopqrstuvwxyz\nABCDEFGHIJKLMNOPQRSTUVWXYZ\n1234567890\n`-=[]\;',./~!@#$%^&*()_+{}|:\"<>?"); // character test
  freetype::print(font, 20, 36, fpsString.c_str());

  // draw point
  /*float crossHair[3] = { 0,0,0 };
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, crossHair);
  
  glDrawArrays(GL_POINTS, 0, 1);
  glDisableVertexAttribArray(0);*/

  glPointSize(5);
  glBegin(GL_POINTS);
  glVertex2f(0, 0);
  glEnd();

  glUseProgram(id);
}