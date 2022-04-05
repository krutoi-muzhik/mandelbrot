#include "mandelbrot.h"

int main () {

	GLFWwindow *window = initialize_window();

	// unsigned int bufID;
	// glGenBuffers (1, &bufID);
	// glBindBuffer (GL_ARRAY_BUFFER, bufID);
	// glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (float), point, GL_STATIC_DRAW);

	// glEnableVertexAttribArray (0);
	// glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	while (!glfwWindowShouldClose (window)) {
		do_render (500);
    	glfwSwapBuffers (window);
    	glfwPollEvents ();
	}

	glfwTerminate ();
	exit (EXIT_SUCCESS);
}
