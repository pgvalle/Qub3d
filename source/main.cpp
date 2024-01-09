#include "App.h"

int main(int argc, char** argv) {
  assert(glfwInit());
  // this looks weird ik but hey it's kinda funny lol
  delete new App();
  glfwTerminate();
  return 0;
}
