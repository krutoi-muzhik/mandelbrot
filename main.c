#include "mandelbrot.h"

int main () {

	GLFWwindow *window = initialize_window();

	// unsigned int bufID;
	// glGenBuffers (1, &bufID);
	// glBindBuffer (GL_ARRAY_BUFFER, bufID);
	// glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (float), point, GL_STATIC_DRAW);

	// glEnableVertexAttribArray (0);
	// glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	double lastTime = glfwGetTime ();
	size_t nFrames = 0;
	double currentTime;

	while (!glfwWindowShouldClose (window)) {
		do_render ();
    	glfwSwapBuffers (window);
    	glfwPollEvents ();
    	nFrames ++;
    	currentTime = glfwGetTime ();
    	if (currentTime - lastTime > 1.0) {
    		lastTime ++;
    		printf ("fps = %ld\n", nFrames);
    		nFrames = 0;
    	}
	}

	glfwTerminate ();
	exit (EXIT_SUCCESS);
}
