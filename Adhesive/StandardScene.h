#pragma once
#include <GL/glew.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "pegcore/Scene.hpp"
#include "GlslProgram.h"
#include "pegcore/Camera.hpp"

using std::vector;
using pegcore::Scene;
using pegcore::Initializable;
using pegcore::Updatable;
using pegcore::Renderable;
using pegcore::SceneObject;
using pegcore::Camera;

class StandardScene : public Scene
{
private:
  vector<Updatable*> updatabales;
  vector<Renderable*> renderables;
  Camera* camera;
public:
  StandardScene(Camera* camera);
  ~StandardScene();
  void addUpdatable(Updatable* updatable);
  void addRenderable(Renderable* renderable);
  void addSceneObject(SceneObject* sceneObject);
  void update(double dt);
  void render();
};