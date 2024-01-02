#include "Internal.h"


AppData app;

void initialize() {
  assert(glfwInit());

  // configuring glfw

  glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  app.win = glfwCreateWindow(800, 480, "Qub3d", NULL, NULL);
  assert(app.win);

  glfwSetFramebufferSizeCallback(app.win, framebuffer_size_callback);
  glfwSetKeyCallback(app.win, key_callback);
  glfwSetMouseButtonCallback(app.win, mouse_button_callback);
  glfwSetCursorPosCallback(app.win, cursor_position_callback);
  glfwSetCursorEnterCallback(app.win, cursor_enter_callback);

  // opengl context creation
  glfwMakeContextCurrent(app.win);
  assert(gladLoadGL(glfwGetProcAddress));

  // shader setup
  app.shader.build_from_files("../../../assets/shaders/vert.glsl", "../../../assets/shaders/frag.glsl");
  glUseProgram(app.shader.ID);

  glfwSetInputMode(app.win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // TODO: integrate me with glm!
  // camera setup
  app.cam.rotate(-180, 0);
  mat4x4_perspective(app.proj, 45, 800 / 480.f, 1, 100);
  app.shader.set_mat4(app.cam.view_mat(), "view");
  app.shader.set_mat4(app.proj, "proj");
  glEnable(GL_DEPTH_TEST);

  load_and_pack_textures();
}

#include "opengl/Vertex.h"

void update();
void render();
void run() {
  // quad to render
  Vertex vertices[] = {
    { {  0.5f,  0.5f, 0.5f },  { 1, 1 } },
    { { -0.5f,  0.5f, 0.5f },  { 0, 1 } },
    { { -0.5f, -0.5f, 0.5f },  { 1, 1 } },
    { {  0.5f, -0.5f, 0.5f },  { 0, 1 } }
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
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
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
}

void terminatei() {
  glfwDestroyWindow(app.win);
  glfwTerminate();
}

void update() {
  if (app.keyboard.is_key_pressed(GLFW_KEY_W)) {
    app.cam.move(0.2f, 0, 0);
  }

  if (app.keyboard.is_key_pressed(GLFW_KEY_S)) {
    app.cam.move(-0.2f, 0, 0);
  }

  if (app.keyboard.is_key_pressed(GLFW_KEY_D)) {
    app.cam.move(0, 0, 0.2f);
  }

  if (app.keyboard.is_key_pressed(GLFW_KEY_A)) {
    app.cam.move(0, 0, -0.2f);
  }

  if (app.keyboard.is_key_pressed(GLFW_KEY_SPACE)) {
    app.cam.move(0, 0.2f, 0);
  }

  if (app.keyboard.is_key_pressed(GLFW_KEY_LEFT_SHIFT)) {
    app.cam.move(0, -0.2f, 0);
  }

  if (app.mouse.is_moving()) {
    int dx, dy;
  app.mouse.get_offset(&dx, &dy);
  app.cam.rotate(2*dx, 2*dy);
  }
  
  

  app.shader.set_mat4(app.cam.view_mat(), "view");
  app.mouse.refresh();
}

void render() {
  
}
