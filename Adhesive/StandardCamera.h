#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include "pegcore/Updatable.hpp"
#include "pegcore/Camera.hpp"
#include "pegglsl/PvmProgram.h"
using pegcore::Updatable;
using pegcore::Camera;
using peg_glsl::PvmProgram;

class StandardCamera : public Updatable, public Camera
{
private:
  PvmProgram* pvmProgram;
  mat4 projection;
  mat4 view;
  float fovy, aspectRatio, near, far;
  vec3 location;
  vec3 direction;
  double theta, phi;
  float speed;
  void calculateView();
  void calculateViewProjection();
  void calculateViewFromOrientation();
  bool forward, backward, left, right, up, down;
  void initialize();
public:
  StandardCamera(PvmProgram* pvmProgram);
  StandardCamera(PvmProgram* pvmProgram, float fovy, float aspect, float near, float far);
  ~StandardCamera();
  void setFovY(float fovy);
  void setAspectRatio(float aspect);
  void setFovYAspect(float fovy, float aspect);
  void setNearFar(float near, float far);
  void setLocation(float x, float y, float z);
  void translate(float dx, float dy, float dz);
  void translate(vec3 ds);
  void setOrientation(double theta, double phi);
  void rotate(double dTheta, double dPhi);
  void uploadPV();
  void moveForward(float ds);
  void moveBackward(float ds);
  void moveUp(float ds);
  void moveDown(float ds);
  void moveLeft(float ds);
  void moveRight(float ds);
  void beginMovingForward();
  void stopMovingForward();
  void beginMovingBackward();
  void stopMovingBackward();
  void beginMovingLeft();
  void stopMovingLeft();
  void beginMovingRight();
  void stopMovingRight();
  void beginMovingUpward();
  void stopMovingUpward();
  void beginMovingDownward();
  void stopMovingDownward();
  void update(double dt);
};