#include <windows.h>
#include <GL\glew.h>
#include <GL\glfw3.h>
#include <stdlib.h>
#include <stdio.h>

void do_render (size_t iterations);
void framebuffer_size_callback (GLFWwindow *window, int width, int height);
GLFWwindow *initialize_window ();