#include "App.h"

#include <glm/gtc/matrix_transform.hpp>

App::App() {
  glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(800, 480, "Qub3d", NULL, NULL);
  assert(window);
  centerWindow();

  // so that i can access app data within the callback
  glfwSetWindowUserPointer(window, this);

  glfwMakeContextCurrent(window);
  assert(gladLoadGL(glfwGetProcAddress));

  glfwSetFramebufferSizeCallback(window, [](GLFWwindow* win, int width, int height) {
    App& a = *((App*)glfwGetWindowUserPointer(win)); // quick alias. I do this in all callbacks

    // correct perspective matrix aspect ratio
    a.proj = glm::perspectiveFov(45.0f, (float)width, (float)height, 1.0f, 100.0f);
    a.shader.uploadMat4("proj", a.proj);

    glViewport(0, 0, width, height);
  });

  keyboard = Keyboard(window);
  mouse = Mouse(window);

  shader.compileFromPaths("../assets/shaders/vert.glsl", "../assets/shaders/frag.glsl");
  shader.use();

  //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  // camera setup
  cam.rotate(0, 0);
  proj = glm::perspectiveFov(45.0f, 800.0f, 450.0f, 1.0f, 100.0f);
  shader.uploadMat4("view", cam.getViewMatrix());
  shader.uploadMat4("proj", proj);
  glEnable(GL_DEPTH_TEST);

  mainLoop();
}

App::~App() {
  glfwDestroyWindow(window);
}

void App::centerWindow() {
  int width, height;
  glfwGetWindowSize(window, &width, &height);

  // Get the resolution of the monitor where window is in
  GLFWmonitor* monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);

  glfwSetWindowPos(window,
    (videoMode->width - width) / 2,
    (videoMode->height - height) / 2
  );
}

void App::fixedUpdate() {

}

void App::update() {
  glfwPollEvents();

  if (keyboard.getKey(GLFW_KEY_ESCAPE)) {
    centerWindow();
  }

  if (keyboard.getKey(GLFW_KEY_W)) {
    cam.move(0.2f, 0, 0);
  }

  if (keyboard.getKey(GLFW_KEY_S)) {
    cam.move(-0.2f, 0, 0);
  }

  if (keyboard.getKey(GLFW_KEY_D)) {
    cam.move(0, 0, 0.2f);
  }

  if (keyboard.getKey(GLFW_KEY_A)) {
    cam.move(0, 0, -0.2f);
  }

  if (keyboard.getKey(GLFW_KEY_SPACE)) {
    cam.move(0, 0.2f, 0);
  }

  if (keyboard.getKey(GLFW_KEY_LEFT_SHIFT)) {
    cam.move(0, -0.2f, 0);
  }

  if (mouse.isMoving()) {
    int dx, dy;
    mouse.getOffset(&dx, &dy);
    cam.rotate(2*dx, 2*dy);
  }

  shader.uploadMat4("view", cam.getViewMatrix());
  mouse.refresh();
}

void App::render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glfwSwapBuffers(window);
}

void App::mainLoop() {
  while (!glfwWindowShouldClose(window)) {
    render();
    update();
  }
}

/*
void run() {
  // quad to render
  Vertex vertices[] = {
    { {  0.5f,  0.5f, 0.5f },  { 0, 1 } },
    { { -0.5f,  0.5f, 0.5f },  { 1, 1 } },
    { { -0.5f, -0.5f, 0.5f },  { 1, 0 } },
    { {  0.5f, -0.5f, 0.5f },  { 0, 0 } }
  };
  GLuint indices[] = {
    0, 1, 2,
    0, 2, 3
  };

  GLuint VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  GLuint VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // dizendo que o array de vertices tem a posicao do vertice no mundo
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));
  glEnableVertexAttribArray(1);

  glClearColor(0, 0, 0, 1);
  glfwSwapInterval(1);

  while (!glfwWindowShouldClose(app.win)) {
    render();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);
    glfwSwapBuffers(app.win);

    glfwPollEvents();
    update();
  }
}*/
