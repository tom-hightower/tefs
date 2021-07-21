void GLFW_Error_Callback(int err, const char* msg) {
	std::cout << err;
	std::cout << msg;
}

void GLFW_FB_Size_Callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void glfwProcessInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}