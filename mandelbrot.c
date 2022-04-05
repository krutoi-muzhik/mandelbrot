#include "mandelbrot.h"

int main () {

	GLFWwindow *window = initialize_window();

	float point[9] = {
		1.0f, 0.0f, 0.0f, 
		0.0f, -1.0f, 0.0f,
		0.0f, 0.0f, 0.0f};
	size_t npoints = 3;

	unsigned int bufID;
	glGenBuffers (1, &bufID);
	glBindBuffer (GL_ARRAY_BUFFER, bufID);
	glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (float), point, GL_STATIC_DRAW);

	glEnableVertexAttribArray (0);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	while (!glfwWindowShouldClose (window)) {
		do_render (point, npoints);
    	glfwSwapBuffers (window);
    	glfwPollEvents ();
	}

	glfwTerminate ();
	exit (EXIT_SUCCESS);
}


void do_render (float *point, size_t n) {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POINTS);
		glColor3f(1.0, 1.0, 1.0);
		for (size_t i = 0; i < n; i++)
			glVertex3fv(point + 3 * i);
	glEnd();
	return;
}

void framebuffer_size_callback (GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}

GLFWwindow *initialize_window() {
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
	return Window;
}