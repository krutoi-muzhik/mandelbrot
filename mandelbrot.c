#include "mandelbrot.h"

enum DEFAULT_SIZE {
	SZX = 960,
	SZY = 540
};

int WIDTH = SZX;
int HEIGHT = SZY;
double zoom = 100.0;
int dragging = 0;
double offsetX = 0.0;
double offsetY = 0.0;

#define C_re re * 2 / WIDTH - 1
#define C_im im * 2 / HEIGHT - 1

void do_render (size_t iterations) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POINTS);
		for (float re = 0; re < WIDTH; re += 1 / scope) {
			for (float im = 0; im < HEIGHT; im += 1 / scope) {
				float x = 0, y = 0;
				float x_tmp = 0, y_tmp = 0;
				size_t iter = 0;
				while (iter < iterations && x * x + y * y < 2) {
					x_tmp = x * x - y * y + C_re;
					y_tmp = 2 * x * y + C_im;
					x = x_tmp;
					y = y_tmp;
					iter++;
				}

				float r = 0.0 + iter / (5 * iterations);
				float g = 0.1 - iter / (3 * iterations);
				float b = 0.3 + iter / (1.5 * iterations);

				glColor3f(r, g, b);
				glVertex2d(re * 2 / WIDTH - 1, im * 2 / HEIGHT - 1);
			}
		}
	glEnd();
	return;
}

void framebuffer_size_callback (GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
	glfwGetWindowSize (window, &WIDTH, &HEIGHT);
	return;
}

GLFWwindow *initialize_window () {
	GLFWwindow *Window;
	if (!glfwInit ())
		exit (EXIT_FAILURE);

	Window = glfwCreateWindow (SZX, SZY, "MANDELBROT", NULL, NULL);
	if (!Window) {
		glfwTerminate ();
		exit (EXIT_FAILURE);
	}
	glfwMakeContextCurrent (Window);

	if (glewInit () != GLEW_OK) {
		glfwTerminate ();
		exit (EXIT_FAILURE);
	}
	glfwSetFramebufferSizeCallback (Window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);
	return Window;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		glfwGetCursorPos(window, &oldX, &oldY);
		dragging = 1;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		dragging = 0;
	return;
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	if (dragging) {
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		offsetX += (xpos - oldX) / zoom;
		offsetY += (oldY - ypos) / zoom;

		oldX = xpos;
		oldY = ypos;
	}
	return;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	if (yoffset != 0) {
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		double dx = (xpos - WIDTH / 2) / zoom - offsetX;
		double dy = (HEIGHT - ypos - HEIGHT / 2) / zoom - offsetY;
		offsetX = -dx;
		offsetY = -dy;
		if (yoffset < 0)
			zoom /= 1.2;
		else
			zoom *= 1.2;

		dx = (xpos - WIDTH / 2) / zoom;
		dy = (HEIGHT - ypos - HEIGHT / 2) / zoom;
		offsetX += dx;
		offsetY += dy;
	}
	return;
}
