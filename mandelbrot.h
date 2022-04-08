#include <windows.h>
#include <GL\glew.h>
#include <GL\glfw3.h>
#include <stdlib.h>
#include <stdio.h>

void do_render ();
void framebuffer_size_callback (GLFWwindow *window, int width, int height);
GLFWwindow *initialize_window ();