#include "StandardCamera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/geometric.hpp"

void StandardCamera::calculateView() {
  vec3 target = location + direction;
  view = glm::lookAt(location, target, vec3(0, 0, 1));
}

void StandardCamera::calculateViewProjection()
{
  projection = glm::perspective(fovy, aspectRatio, near, far);
  calculateViewFromOrientation();
}

void StandardCamera::calculateViewFromOrientation()
{
  double cosphi = cos(phi);
  direction = vec3(cosphi*sin(theta), cosphi*cos(theta), sin(phi));
  calculateView();
}

void StandardCamera::initialize() {
  location = vec3(0);
  theta = 0.0;
  phi = 0.0;
  forward = backward = left = right = up = down = false;
  calculateViewProjection();
  speed = 15.0f;
}

StandardCamera::StandardCamera(PvmProgram* pvmProgram)
{
  this->pvmProgram = pvmProgram;
  fovy = glm::radians(45.0f);
  aspectRatio = 1;
  near = 0.1f;
  far = 100;
  initialize();
}

StandardCamera::StandardCamera(PvmProgram* pvmProgram, float fovy, float aspect, float near, float)
{
  this->pvmProgram = pvmProgram;
  this->fovy = fovy;
  this->aspectRatio = aspect;
  this->near = near;
  this->far = far;
  initialize();
}

StandardCamera::~StandardCamera()
{
}

void StandardCamera::setFovY(float fovy)
{
  this->fovy = fovy;
  projection = glm::perspective(fovy, aspectRatio, near, far);
}

void StandardCamera::setAspectRatio(float aspect)
{
  this->aspectRatio = aspect;
  projection = glm::perspective(fovy, aspect, near, far);
}

void StandardCamera::setFovYAspect(float fovy, float aspect)
{
  this->fovy = fovy;
  this->aspectRatio = aspect;
  projection = glm::perspective(fovy, aspect, near, far);
}

void StandardCamera::setNearFar(float near, float far)
{
  this->near = near;
  this->far = far;
  projection = glm::perspective(fovy, aspectRatio, near, far);
}

void StandardCamera::setLocation(float x, float y, float z)
{
  location = vec3(x, y, z);
  calculateView();
}

void StandardCamera::translate(float dx, float dy, float dz)
{
  location += vec3(dx, dy, dz);
  calculateView();
}

void StandardCamera::translate(vec3 ds)
{
  location += ds;
  calculateView();
}

void StandardCamera::setOrientation(double theta, double phi)
{
  this->theta = theta;
  this->phi = phi;

  double halfPi = glm::half_pi<double>();
  double Pi = glm::pi<double>();
  while (phi > halfPi) phi -= Pi;
  while (phi < -halfPi) phi += Pi;

  double twoPi = glm::two_pi<double>();
  while (theta > twoPi) theta -= twoPi;
  while (theta < 0) theta += twoPi;

  calculateViewFromOrientation();
}

void StandardCamera::rotate(double dTheta, double dPhi)
{
  theta += dTheta;

  double twoPi = glm::two_pi<double>();
  while (theta > twoPi) theta -= twoPi;
  while (theta < 0) theta += twoPi;

  double newPhi = phi + dPhi;
  double halfPi = glm::half_pi<double>();
  if (newPhi < halfPi && newPhi > -halfPi) phi = newPhi;

  calculateViewFromOrientation();
}

void StandardCamera::uploadPV()
{
  mat4 PV = projection*view;
  pvmProgram->setProjectionView(PV);
}

void StandardCamera::moveForward(float ds) {
  vec3 dVec = direction*ds;
  translate(dVec);
}

void StandardCamera::moveBackward(float ds) {
  vec3 dVec = -direction*ds;
  translate(dVec);
}

void StandardCamera::moveUp(float ds) {
  translate(0, 0, ds);
}

void StandardCamera::moveDown(float ds) {
  translate(0, 0, -ds);
}

void StandardCamera::moveLeft(float ds) {
  vec3 dVec = ds*cross(direction, vec3(0, 0, 1));
  translate(dVec);
}

void StandardCamera::moveRight(float ds) {
  vec3 dVec = ds*cross(vec3(0, 0, 1), direction);
  translate(dVec);
}

void StandardCamera::beginMovingForward(){
  forward = true;
}

void StandardCamera::stopMovingForward(){
  forward = false;
}

void StandardCamera::beginMovingBackward(){
  backward = true;
}

void StandardCamera::stopMovingBackward(){
  backward = false;
}

void StandardCamera::beginMovingLeft(){
  left = true;
}

void StandardCamera::stopMovingLeft(){
  left = false;
}

void StandardCamera::beginMovingRight(){
  right = true;
}

void StandardCamera::stopMovingRight(){
  right = false;
}

void StandardCamera::beginMovingUpward() {
  up = true;
}

void StandardCamera::stopMovingUpward() {
  up = false;
}

void StandardCamera::beginMovingDownward() {
  down = true;
}

void StandardCamera::stopMovingDownward() {
  down = false;
}

void StandardCamera::update(double dt) {
  vec3 moveDir = vec3(0);
  bool moving = false;
  if (forward) {
    if (!backward) {
      moveDir += direction;
      moving = true;
    }
  }
  else if (backward) {
    moveDir -= direction;
    moving = true;
  }

  if (left) {
    if (!right) {
      moveDir += cross(vec3(0, 0, 1), direction);
      moving = true;
    }
  }
  else if (right) {
    moveDir += cross(direction, vec3(0, 0, 1));
    moving = true;
  }

  if (up) {
    if (!down) {
      moveDir += vec3(0, 0, 1);
      moving = true;
    }
  }
  else if (down) {
    moveDir += vec3(0, 0, -1);
    moving = true;
  }

  if (moving) {
    moveDir = glm::normalize(moveDir);
    float ds = dt*speed;
    vec3 dVec = moveDir*ds;
    translate(dVec);
  }
}