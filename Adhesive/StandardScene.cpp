#include "StandardScene.h"

StandardScene::StandardScene(Camera * camera)
{
  this->camera = camera;
}

StandardScene::~StandardScene()
{
}

void StandardScene::addUpdatable(Updatable* updatable) {
  updatabales.push_back(updatable);
}

void StandardScene::addRenderable(Renderable* renderable) {
  renderables.push_back(renderable);
}

void StandardScene::addSceneObject(SceneObject* sceneObject) {
  updatabales.push_back(sceneObject);
  renderables.push_back(sceneObject);
  sceneObject->initialize();
  // objects should be initialized when they are added to scene because they may be added runtime.
}

/*
void loadShader(GLuint handle, char* fileName) {
  std::ifstream inFile;
  inFile.open(fileName); //open the input file
  std::stringstream strStream;
  strStream << inFile.rdbuf(); //read the file
  inFile.close();
  std::string str = strStream.str(); //str holds the content of the file
  const GLchar* glslCode = str.c_str(); // convert to c string
  const GLchar* glslArray[] = { glslCode };
  glShaderSource(handle, 1, glslArray, NULL);
}
*/

void StandardScene::update(double dt) {
  camera->update(dt);
  for (auto &updater : updatabales) {
    updater->update(dt);
  }
}

void StandardScene::render() {
  camera->uploadPV();
  for (auto &renderer : renderables) {
    renderer->render();
  }
}