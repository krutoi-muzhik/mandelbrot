#include <windows.h>
#include <GL\glew.h>
#include <GL\glfw3.h>
#include <stdlib.h>
#include <stdio.h>

void do_render ();
void framebuffer_size_callback (GLFWwindow *window, int width, int height);
GLFWwindow *initialize_window ();
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);