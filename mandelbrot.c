#include "mandelbrot.h"

enum DEFAULT_VALS {
	SZX = 960,
	SZY = 540,
	ITERS = 200,
	ZOOM = 1000
};

int WIDTH = SZX;
int HEIGHT = SZY;
double zoom = ZOOM;
int dragging = 0;
double offsetX = -480.0, offsetY = 270.0;
double posX = 0.0, posY = 0;
size_t iterations = ITERS;

#define C_re re * 100 / zoom
#define C_im im * 100 / zoom

void do_render () {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POINTS);
		for (float re = offsetX; re < offsetX + WIDTH; re ++) {
			for (float im = offsetY; im > offsetY - HEIGHT; im --) {
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

				// printf ("offsetX = %lf, offsetY = %lf\n", offsetX, offsetY);

				// printf ("C_re = %lf, C_im = %lf\n", C_re, C_im);

				// printf ("x = %lf, y = %lf, iter = %d\n", re, im, iter);

				float r = 0.0 + iter / (5 * iterations);
				float g = 0.1 - iter / (3 * iterations);
				float b = 0.3 + iter / (1.5 * iterations);

				glColor3f(r, g, b);

				// printf ("x = %lf y = %lf\n", (re - offsetX) * 2 / WIDTH - 1, (offsetY - im) * 2 / HEIGHT - 1);
				glVertex2d((re - offsetX) * 2 / WIDTH - 1, (offsetY - im) * 2 / HEIGHT - 1);
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
	glfwSetKeyCallback(Window, key_callback);
	glfwSetCursorPosCallback(Window, cursor_position_callback);
	glfwSetMouseButtonCallback(Window, mouse_button_callback);
	glfwSetScrollCallback(Window, scroll_callback);
	return Window;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		glfwGetCursorPos(window, &posX, &posY);
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

		offsetX -= (xpos - posX);
		offsetY -= (ypos - posY);

		posX = xpos;
		posY = ypos;
	}
	return;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	if (yoffset != 0) {
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		double dx = (xpos - WIDTH / 2) - offsetX;
		double dy = (ypos - HEIGHT / 2) - offsetY;
		offsetX = -dx;
		offsetY = -dy;

		if (yoffset < 0)
			zoom /= 1.2;
		else
			zoom *= 1.2;

		dx = (xpos - WIDTH / 2) / zoom;
		dy = (ypos - HEIGHT / 2) / zoom;
		offsetX -= dx;
		offsetY -= dy;
	}
	return;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, 1);
	}

	if (key == GLFW_KEY_KP_0 && action == GLFW_PRESS) {
		iterations = ITERS;
		zoom = ZOOM;
		offsetX = 0.0;
		offsetY = 0.0;
	}

	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		offsetX -= WIDTH / 5;
	else if (key == GLFW_KEY_D && action == GLFW_PRESS)
		offsetX += WIDTH / 5;
	else if (key == GLFW_KEY_W && action == GLFW_PRESS)
		offsetY -= HEIGHT / 5;
	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
		offsetY += HEIGHT / 5;

	if (key == GLFW_KEY_KP_ADD && action == GLFW_PRESS)
		zoom *= 2;
	else if (key == GLFW_KEY_KP_SUBTRACT && action == GLFW_PRESS)
		zoom /= 2;

	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
		iterations += 50;
	else if (key == GLFW_KEY_E && action == GLFW_PRESS && iterations >= 100)
		iterations -= 50;
}
