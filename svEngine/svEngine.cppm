#include "pch.h"
export module sv_engine;
import sv_render;

namespace svEngine {

	 int WIDTH = 800, HEIGHT = 480;

	 std::unique_ptr<svRender::svRenderer> renderer;

	GLFWwindow* window;

	 sveCamera camera;

	bool amogus;


	void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
		renderer->resize();
	}

	void mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{
		static double lastX = WIDTH / 2.0f;
		static double lastY = HEIGHT / 2.0f;
		static bool firstMouse = true;

		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos;

		lastX = xpos;
		lastY = ypos;

		const float sensitivity = 0.1f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		camera.rotateRelative(glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(xoffset));
		camera.rotate(glm::vec3(1.0f, 0.0f, 0.0f), glm::radians(-yoffset));
	}

	void processInput(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camera.translateRelative(glm::vec3(0.0f, 0.0f, 1.0f));
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camera.translateRelative(glm::vec3(0.0f, 0.0f, -1.0f));
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camera.translateRelative(glm::vec3(1.0f, 0.0f, 0.0f));
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camera.translateRelative(glm::vec3(-1.0f, 0.0f, 0.0f));
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			camera.translateRelative(glm::vec3(0.0f, -1.0f, 0.0f));
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			camera.translateRelative(glm::vec3(0.0f, 1.0f, 0.0f));
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	int startRender() {
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
		glfwSetWindowUserPointer(window, renderer.get());
		glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
		glfwSetCursorPosCallback(window, mouse_callback);

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		renderer = std::make_unique<svRender::svRenderer>(window);
		amogus = true;
		try {
			renderer->run();
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
			return EXIT_FAILURE;
		}

		return EXIT_SUCCESS;
	}


	export void start()
	{
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		proj = glm::perspective(glm::radians(34.0f), WIDTH / (float)HEIGHT, 0.001f, 100.0f);
		proj[1][1] *= -1;

		amogus = false;
		std::thread renderThread(startRender);
		while(!amogus)
		{ }
		renderer->setModel(model);
		renderer->setView(view);
		renderer->setProjection(proj);
		while (!glfwWindowShouldClose(window))
		{
			processInput(window);
			view = camera.getViewMatrix();
			renderer->setView(view);
		}
		renderThread.join();
	}
}