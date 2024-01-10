#pragma once

#include <cassert>
#include <cstdio>
#include <string>
#include <map>

#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "input/Input.h"
#include "opengl/OpenGL.h"
#include "world/World.h"

class App {
public:
  // low level

  GLFWwindow* window;
  Mouse mouse;
  Keyboard keyboard;

  // graphics

  glm::mat4 proj;
  Camera cam;
  Shader shader;

  // resources
  
  //TextureAtlas atlas;

  // config ...

  App();
  ~App();

private:
  void centerWindow();

  void fixedUpdate();
  void update();
  void render();

  void mainLoop();
};
