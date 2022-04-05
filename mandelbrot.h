#include <windows.h>
#include <GL\glew.h>
#include <GL\glfw3.h>
#include <stdlib.h>

const int SZX = 600;
const int SZY = 600;

void do_render (float *point, size_t n);
void framebuffer_size_callback (GLFWwindow *window, int width, int height);
GLFWwindow *initialize_window ();