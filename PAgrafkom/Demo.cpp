#include "Demo.h"



Demo::Demo() {

}


Demo::~Demo() {
}


void Demo::Init() {
	// build and compile our shader program
	// ------------------------------------
	shaderProgram = BuildShader("vertexShader.vert", "fragmentShader.frag", nullptr);

	BuildColoredKasur();

	BuildColoredBantal();

	BuildColoredKulkas();

	BuildColoredLemarii();

	BuildColoredDinding();

	BuildColoredKarpet();

	BuildColoredPintu();

	BuildColoredRak();

	BuildColoredAtap();

	BuildColoredPlane();

	InitCamera();
}

void Demo::DeInit() {
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glDeleteVertexArrays(1, &VAO2);
	glDeleteBuffers(1, &VBO2);
	glDeleteBuffers(1, &EBO2);

	glDeleteVertexArrays(1, &VAO3);
	glDeleteBuffers(1, &VBO3);
	glDeleteBuffers(1, &EBO3);

	glDeleteVertexArrays(1, &VAO5);
	glDeleteBuffers(1, &VBO5);
	glDeleteBuffers(1, &EBO5);

	glDeleteVertexArrays(1, &VAO6);
	glDeleteBuffers(1, &VBO6);
	glDeleteBuffers(1, &EBO6);

	glDeleteVertexArrays(1, &VAO7);
	glDeleteBuffers(1, &VBO7);
	glDeleteBuffers(1, &EBO7);

	glDeleteVertexArrays(1, &VAO8);
	glDeleteBuffers(1, &VBO8);
	glDeleteBuffers(1, &EBO8);

	glDeleteVertexArrays(1, &VAO9);
	glDeleteBuffers(1, &VBO9);
	glDeleteBuffers(1, &EBO9);

	glDeleteVertexArrays(1, &VAO10);
	glDeleteBuffers(1, &VBO10);
	glDeleteBuffers(1, &EBO10);

	glDeleteVertexArrays(1, &VAO11);
	glDeleteBuffers(1, &VBO11);
	glDeleteBuffers(1, &EBO11);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void Demo::ProcessInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	
	// zoom camera
	// -----------
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		if (fovy < 90) {
			fovy += 0.0001f;
		}
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (fovy > 0) {
			fovy -= 0.0001f;
		}
	}

	// update camera movement 
	// -------------
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		MoveCamera(CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		MoveCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		StrafeCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		StrafeCamera(CAMERA_SPEED);
	}

	// update camera rotation
	// ----------------------
	double mouseX, mouseY;
	double midX = screenWidth/2;
	double midY = screenHeight/2;
	float angleY = 0.0f;
	float angleZ = 0.0f;

	// Get mouse position
	glfwGetCursorPos(window, &mouseX, &mouseY);
	if ((mouseX == midX) && (mouseY == midY)) {
		return;
	}

	// Set mouse position
	glfwSetCursorPos(window, midX, midY);

	// Get the direction from the mouse cursor, set a resonable maneuvering speed
	angleY = (float)((midX - mouseX)) / 1000;
	angleZ = (float)((midY - mouseY)) / 1000;

	// The higher the value is the faster the camera looks around.
	viewCamY += angleZ * 2;

	// limit the rotation around the x-axis
	if ((viewCamY - posCamY) > 8) {
		viewCamY = posCamY + 8;
	}
	if ((viewCamY - posCamY) < -8) {
		viewCamY = posCamY - 8;
	}
	RotateCamera(-angleY);

}

void Demo::Update(double deltaTime) {
	
}
//Nisa
void Demo::Render() {
	glViewport(0, 0, this->screenWidth, this->screenHeight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);

	// Pass perspective projection matrix
	glm::mat4 projection = glm::perspective(fovy, (GLfloat)this->screenWidth / (GLfloat)this->screenHeight, 0.1f, 100.0f);
	GLint projLoc = glGetUniformLocation(this->shaderProgram, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// LookAt camera (position, target/direction, up)
	glm::vec3 cameraPos = glm::vec3(0, 3, 3);
	glm::vec3 cameraFront = glm::vec3(0, -1, -1);
	glm::mat4 view = glm::lookAt(glm::vec3(posCamX, posCamY, posCamZ), glm::vec3(viewCamX, viewCamY, viewCamZ), glm::vec3(upCamX, upCamY, upCamZ));
	GLint viewLoc = glGetUniformLocation(this->shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	// set lighting attributes
	GLint viewPosLoc = glGetUniformLocation(this->shaderProgram, "viewPos");
	glUniform3f(viewPosLoc, cameraPos.x, cameraPos.y, cameraPos.z);

	glUniform3f(glGetUniformLocation(this->shaderProgram, "dirLight.direction"), 0.0f, -1.0f, -1.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "dirLight.ambient"), 0.1f, 0.1f, 0.1f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "dirLight.diffuse"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "dirLight.specular"), 0.1f, 0.1f, 0.1f);
	// point light 1
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[0].position"), 0.0f, 3.0f, 0.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[0].ambient"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[0].diffuse"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[0].specular"), 0.0f, 0.0f, 0.0f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "pointLights[0].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "pointLights[0].linear"), 0.09f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "pointLights[0].quadratic"), 0.032f);
	// point light 2
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[1].position"), -2.0f, 3.0f, 0.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[1].ambient"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[1].diffuse"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[1].specular"), 0.0f, 0.0f, 0.0f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "pointLights[1].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "pointLights[1].linear"), 0.09f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "pointLights[1].quadratic"), 0.032f);
	// point light 3
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[2].position"), 2.0f, 3.0f, 0.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[2].ambient"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[2].diffuse"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[2].specular"), 0.0f, 0.0f, 0.0f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "pointLights[2].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "pointLights[2].linear"), 0.09f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "pointLights[2].quadratic"), 0.032f);
	// point light 4
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[3].position"), 0.0f, 3.0f, 2.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[3].ambient"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[3].diffuse"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[3].specular"), 0.0f, 0.0f, 0.0f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "pointLights[3].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "pointLights[3].linear"), 0.09f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "pointLights[3].quadratic"), 0.032f);
	// spotLight
	glUniform3fv(glGetUniformLocation(this->shaderProgram, "spotLight.position"), 1, &cameraPos[0]);
	glUniform3fv(glGetUniformLocation(this->shaderProgram, "spotLight.direction"), 1, &cameraFront[0]);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "spotLight.diffuse"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));
	glUniform1f(glGetUniformLocation(this->shaderProgram, "spotLight.constant"), 1.0f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "spotLight.linear"), 0.09f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "spotLight.quadratic"), 0.032f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));

	DrawColoredKasur();

	DrawColoredBantal();

	DrawColoredKulkas();

	DrawColoredLemarii();

	DrawColoredKarpet();

	DrawColoredPintu();

	DrawColoredRak();

	DrawColoredDinding();

	DrawColoredAtap();

	DrawColoredPlane();

	glDisable(GL_DEPTH_TEST);
}

//Nisa
void Demo::BuildColoredKasur() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("bed3.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
	// front
	-5.0, -1.0, 8.0, 0, 0,  // 0
	5.0, -1.0, 8.0, 1, 0,   // 1
	5.0,  1.0, 8.0, 1, 1,   // 2
	-5.0,  1.0, 8.0, 0, 1,  // 3

	// right
	5.0,  1.0,  8.0, 0, 0,  // 4
	5.0,  1.0, -8.0, 1, 0,  // 5
	5.0, -1.0, -8.0, 1, 1,  // 6
	5.0, -1.0,  8.0, 0, 1,  // 7

	// back
	-5.0, -1.0, -8.0, 0, 0, // 8 
	5.0,  -1.0, -8.0, 1, 0, // 9
	5.0,   1.0, -8.0, 1, 1, // 10
	-5.0,  1.0, -8.0, 0, 1, // 11

	// left
	-5.0, -1.0, -8.0, 0, 0, // 12
	-5.0, -1.0,  8.0, 1, 0, // 13
	-5.0,  1.0,  8.0, 1, 1, // 14
	-5.0,  1.0, -8.0, 0, 1, // 15

	// upper
	5.0, 1.0,  8.0, 0, 0,   // 16
	-5.0, 1.0,  8.0, 1, 0,  // 17
	-5.0, 1.0, -8.0, 1, 1,  // 18
	5.0, 1.0, -8.0, 0, 1,   // 19

	// bottom
	-5.0, -1.0, -8.0, 0, 0, // 20
	5.0, -1.0, -8.0, 1, 0,  // 21
	5.0, -1.0,  8.0, 1, 1,  // 22
	-5.0, -1.0,  8.0, 0, 1, // 23
		
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
//Nisa
void Demo::DrawColoredKasur()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	

	glm::mat4 model;
	//model = glm::translate(model, glm::vec3(4, 0.5, 1));
	model = glm::translate(model, glm::vec3(4, 0.5, 1));
	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}
//Nisa
void Demo::BuildColoredBantal() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture11);
	glBindTexture(GL_TEXTURE_2D, texture11);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("bed.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-3.0, -0.5, 2.0, 0, 0,  // 0
		3.0, -0.5, 2.0, 1, 0,   // 1
		3.0,  0.5, 2.0, 1, 1,   // 2
		-3.0,  0.5, 2.0, 0, 1,  // 3

		// right
		3.0,  0.5,  2.0, 0, 0,  // 4
		3.0,  0.5, -2.0, 1, 0,  // 5
		3.0, -0.5, -2.0, 1, 1,  // 6
		3.0, -0.5,  2.0, 0, 1,  // 7

		// back
		-3.0, -0.5, -2.0, 0, 0, // 8 
		3.0,  -0.5, -2.0, 1, 0, // 9
		3.0,   0.5, -2.0, 1, 1, // 10
		-3.0,  0.5, -2.0, 0, 1, // 11

		// left
		-3.0, -0.5, -2.0, 0, 0, // 12
		-3.0, -0.5,  2.0, 1, 0, // 13
		-3.0,  0.5,  2.0, 1, 1, // 14
		-3.0,  0.5, -2.0, 0, 1, // 15

		// upper
		3.0, 0.5,  2.0, 0, 0,   // 16
		-3.0, 0.5,  2.0, 1, 0,  // 17
		-3.0, 0.5, -2.0, 1, 1,  // 18
		3.0, 0.5, -2.0, 0, 1,   // 19

		// bottom
		-3.0, -0.5, -2.0, 0, 0, // 20
		3.0, -0.5, -2.0, 1, 0,  // 21
		3.0, -0.5,  2.0, 1, 1,  // 22
		-3.0, -0.5,  2.0, 0, 1, // 23

	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO11);
	glGenBuffers(1, &VBO11);
	glGenBuffers(1, &EBO11);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO11);

	glBindBuffer(GL_ARRAY_BUFFER, VBO11);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO11);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
//Nisa
void Demo::DrawColoredBantal()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture11);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO11); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized


	glm::mat4 model;
	model = glm::translate(model, glm::vec3(4, 2, -4));
	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}
//Catur
void Demo::BuildColoredKulkas() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture3);
	glBindTexture(GL_TEXTURE_2D, texture3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("kulkascatur.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-1.5, -2.5, 1.0, 0, 0, // 0
		1.5, -2.5, 1.0, 1, 0, // 1
		1.5,  2.5, 1.0, 1, 1, // 2
		-1.5,  2.5, 1.0, 0, 1, // 3

		// right
		1.5,  2.5,  1.0, 0, 0, // 4
		1.5,  2.5, -1.0, 1, 0, // 5
		1.5, -2.5, -1.0, 1, 1, // 6
		1.5, -2.5,  1.0, 0, 1, // 7

		// back
		-1.5, -2.5, -1.0, 0, 0, // 8 
		1.5, -2.5, -1.0, 1, 0, // 9
		1.5,  2.5, -1.0, 1, 1, // 10
		-1.5,  2.5, -1.0, 0, 1, // 11

		// left
		-1.5, -2.5, -1.0, 0, 0, // 12
		-1.5, -2.5,  1.0, 1, 0, // 13
		-1.5,  2.5,  1.0, 1, 1, // 14
		-1.5,  2.5, -1.0, 0, 1, // 15

		// upper
		1.5, 2.5,  1.0, 0, 0, // 16
		-1.5, 2.5,  1.0, 1, 0, // 17
		-1.5, 2.5, -1.0, 1, 1, // 18
		1.5, 2.5, -1.0, 0, 1, // 19

		// bottom
		-1.5, -2.5, -1.0, 0, 0, // 20
		1.5, -2.5, -1.0, 1, 0, // 21
		1.5, -2.5,  1.0, 1, 1, // 22
		-1.5, -2.5,  1.0, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO3);
	glGenBuffers(1, &VBO3);
	glGenBuffers(1, &EBO3);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO3);

	glBindBuffer(GL_ARRAY_BUFFER, VBO3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
//Catur
void Demo::DrawColoredKulkas()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture3);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO3); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(-5, 2, -6));
	//model = glm::translate(model, glm::vec3(-5, 0.5, -6));
	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}
//Ingke
void Demo::BuildColoredLemarii() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture7);
	glBindTexture(GL_TEXTURE_2D, texture7);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("lemari.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-2.0, -6.0, 1.5, 0, 0,  // 0
		2.0, -6.0, 1.5, 1, 0,   // 1
		2.0,  6.0, 1.5, 1, 1,   // 2
		-2.0,  6.0, 1.5, 0, 1,  // 3

		2.0,  6.0,  1.5, 0, 0,  // 4
		2.0,  6.0, -1.5, 1, 0,  // 5
		2.0, -6.0, -1.5, 1, 1,  // 6
		2.0, -6.0,  1.5, 0, 1,  // 7

		-2.0, -6.0, -1.5, 0, 0, // 8 
		2.0, -6.0, -1.5, 1, 0, // 9
		2.0,  6.0, -1.5, 1, 1, // 10
		-2.0,  6.0, -1.5, 0, 1, // 11

		-2.0, -6.0, -1.5, 0, 0, // 12
		-2.0, -6.0,  1.5, 1, 0, // 13
		-2.0,  6.0,  1.5, 1, 1, // 14
		-2.0,  6.0, -1.5, 0, 1, // 15

		2.0, 6.0,  1.5, 0, 0,   // 16
		-2.0, 6.0,  1.5, 1, 0,  // 17
		-2.0, 6.0, -1.5, 1, 1,  // 18
		2.0, 6.0, -1.5, 0, 1,   // 19

		-2.0, -6.0, -1.5, 0, 0, // 20
		2.0, -6.0, -1.5, 1, 0,  // 21
		2.0, -6.0,  1.5, 1, 1,  // 22
		-2.0, -6.0,  1.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO7);
	glGenBuffers(1, &VBO7);
	glGenBuffers(1, &EBO7);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO7);

	glBindBuffer(GL_ARRAY_BUFFER, VBO7);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO7);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
//Ingke
void Demo::DrawColoredLemarii()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture7);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO7); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized


	glm::mat4 model;
	model = glm::translate(model, glm::vec3(-10, 5, -5.5));
	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}
//Nisa
void Demo::BuildColoredKarpet() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture8);
	glBindTexture(GL_TEXTURE_2D, texture8);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("rug.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-6.0, -0.05, 6.0, 0, 0,  // 0
		6.0, -0.05, 6.0, 1, 0,   // 1
		6.0,  0.05, 6.0, 1, 1,   // 2
		-6.0,  0.05, 6.0, 0, 1,  // 3

		// right
		6.0,  0.05,  6.0, 0, 0,  // 4
		6.0,  0.05, -6.0, 1, 0,  // 5
		6.0, -0.05, -6.0, 1, 1,  // 6
		6.0, -0.05,  6.0, 0, 1,  // 7

		// back
		-6.0, -0.05, -6.0, 0, 0, // 8 
		6.0,  -0.05, -6.0, 1, 0, // 9
		6.0,   0.05, -6.0, 1, 1, // 10
		-6.0,  0.05, -6.0, 0, 1, // 11

		// left
		-6.0, -0.05, -6.0, 0, 0, // 12
		-6.0, -0.05,  6.0, 1, 0, // 13
		-6.0,  0.05,  6.0, 1, 1, // 14
		-6.0,  0.05, -6.0, 0, 1, // 15

		// upper
		6.0, 0.05,  6.0, 0, 0,   // 16
		-6.0, 0.05,  6.0, 1, 0,  // 17
		-6.0, 0.05, -6.0, 1, 1,  // 18
		6.0, 0.05, -6.0, 0, 1,   // 19

		// bottom
		-6.0, -0.05, -6.0, 0, 0, // 20
		6.0, -0.05, -6.0, 1, 0,  // 21
		6.0, -0.05,  6.0, 1, 1,  // 22
		-6.0, -0.05,  6.0, 0, 1, // 23

	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO8);
	glGenBuffers(1, &VBO8);
	glGenBuffers(1, &EBO8);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO8);

	glBindBuffer(GL_ARRAY_BUFFER, VBO8);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO8);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
//Nisa
void Demo::DrawColoredKarpet()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture8);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO8); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized


	glm::mat4 model;
	model = glm::translate(model, glm::vec3(-9, -0.35, 4));
	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}
//Ingke
void Demo::BuildColoredPintu() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture9);
	glBindTexture(GL_TEXTURE_2D, texture9);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("pintu.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-3, -6, 0, 0, 0,  // 0
		3, -6, 0, 1, 0,   // 1
		3,  6, 0, 1, 1,   // 2
		-3,  6, 0, 0, 1,  // 3

		// right
		3,  6,  0, 0, 0,  // 4
		3,  6, -0, 1, 0,  // 5
		3, -6, -0, 1, 1,  // 6
		3, -6,  0, 0, 1,  // 7

		// back
		-3, -6, -0, 0, 0, // 8 
		3,  -6, -0, 1, 0, // 9
		3,   6, -0, 1, 1, // 10
		-3,  6, -0, 0, 1, // 11

		// left
		-3, -6, -0, 0, 0, // 12
		-3, -6,  0, 1, 0, // 13
		-3,  6,  0, 1, 1, // 14
		-3,  6, -0, 0, 1, // 15

		// upper
		3, 6,  0, 0, 0,   // 16
		-3, 6,  0, 1, 0,  // 17
		-3, 6, -0, 1, 1,  // 18
		3, 6, -0, 0, 1,   // 19

		// bottom
		-3, -6, -0, 0, 0, // 20
		3, -6, -0, 1, 0,  // 21
		3, -6,  0, 1, 1,  // 22
		-3, -6,  0, 0, 1, // 23

	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO9);
	glGenBuffers(1, &VBO9);
	glGenBuffers(1, &EBO9);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO9);

	glBindBuffer(GL_ARRAY_BUFFER, VBO9);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO9);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
//Ingke
void Demo::DrawColoredPintu()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture9);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO9); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized


	glm::mat4 model;
	model = glm::translate(model, glm::vec3(-10, 4.9, 22.95));
	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}
//Ingke
void Demo::BuildColoredRak() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture10);
	glBindTexture(GL_TEXTURE_2D, texture10);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("shelf.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-6, -2, 1.5, 0, 0,  // 0
		6, -2, 1.5, 1, 0,   // 1
		6,  2, 1.5, 1, 1,   // 2
		-6,  2, 1.5, 0, 1,  // 3

		// right
		6,  2,  1.5, 0, 0,  // 4
		6,  2, -1.5, 1, 0,  // 5
		6, -2, -1.5, 1, 1,  // 6
		6, -2,  1.5, 0, 1,  // 7

		// back
		-6, -2, -1.5, 0, 0, // 8 
		6,  -2, -1.5, 1, 0, // 9
		6,   2, -1.5, 1, 1, // 10
		-6,  2, -1.5, 0, 1, // 11

		// left
		-6, -2, -1.5, 0, 0, // 12
		-6, -2,  1.5, 1, 0, // 13
		-6,  2,  1.5, 1, 1, // 14
		-6,  2, -1.5, 0, 1, // 15

		// upper
		6, 2,  1.5, 0, 0,   // 16
		-6, 2,  1.5, 1, 0,  // 17
		-6, 2, -1.5, 1, 1,  // 18
		6, 2, -1.5, 0, 1,   // 19

		// bottom
		-6, -2, -1.5, 0, 0, // 20
		6, -2, -1.5, 1, 0,  // 21
		6, -2,  1.5, 1, 1,  // 22
		-6, -2,  1.5, 0, 1, // 23

	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO10);
	glGenBuffers(1, &VBO10);
	glGenBuffers(1, &EBO10);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO10);

	glBindBuffer(GL_ARRAY_BUFFER, VBO10);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO10);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
//Ingke
void Demo::DrawColoredRak()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture10);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO10); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized


	glm::mat4 model;
	model = glm::translate(model, glm::vec3(3, 1.5, 21));
	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}
//Nisa
void Demo::BuildColoredDinding() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture5);
	glBindTexture(GL_TEXTURE_2D, texture5);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("tembok.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		//DINDING DEPAN
		// front
		-20, -1,  -0.3, 0, 0,  // 0
		20, -1, -0.3, 1, 0,   // 1
		20, 15, -0.3, 1, 1,   // 2
		-20, 15, -0.3, 0, 1,   // 3

		// right
		20, 15, -0.3, 0, 0,  // 4 
		20,  15, -0.6, 1, 0,  // 5
		20, -1, -0.6, 1, 1,  // 6
		20, -1, -0.3, 0, 1,  // 7

		// back
		-20, -1,  -0.6, 0, 0,  // 8 
		20, -1, -0.6, 1, 0, // 9
		20,  15, -0.6, 1, 1, // 10
		-20,  15, -0.6, 0, 1,  // 11

		// left
		-20, -1,  -0.6, 0, 0, // 12
		-20, -1,  -0.3, 1, 0, // 13
		-20, 15, -0.3, 1, 1, // 14
		-20, -1,  -0.3, 0, 1, // 15

		// upper
		20, 15, -0.3, 0, 0,   // 16
		-20, 15, -0.3, 1, 0,  // 17
		-20,  15, -0.6,  1, 1,  // 18
		20,  15, -0.6, 0, 1,   // 19

		// bottom
		-20, -1,  -0.6, 0, 0, // 20
		20, -1, -0.6, 1, 0,  // 21
		20, -1, -0.3,1, 1,  // 22
		-20, -1,  -0.3, 0, 1, // 23

		//DINDING KIRI
		// front
		-20.3, -1,  30, 0, 0,  // 24
		-20, -1, 30, 1, 0,   // 25
		-20, 15, 30, 1, 1,   // 26
		-20.3, 15, 30, 0, 1,   // 27

		// right
		-20, 15, 30, 0, 0,  // 28
		-20,  15, -0.6, 1, 0,  // 29
		-20, -1, -0.6, 1, 1,  // 30
		-20, -1, 30, 0, 1,  // 31

		// back
		-20.3, -1,  -0.6, 0, 0,  // 32 
		-20, -1, -0.6, 1, 0, // 33
		-20,  15, -0.6, 1, 1, // 34
		-20.3,  15, -0.6, 0, 1,  // 35

		// left
		-20.3, -1,  -0.6, 0, 0, // 36
		-20.3, -1,  30, 1, 0, // 37
		-20.3, 15, 30, 1, 1, // 38
		-20.3,  15, -0.6, 0, 1, // 40

		// upper
		-20, 15, 30, 0, 0,   // 41
		-20.3, 15, 30, 1, 0,  // 42
		-20.3,  15, -0.6,  1, 1,  // 43
		-20,  15, -0.6, 0, 1,   // 44

		// bottom
		-20.3, -1,  -0.6, 0, 0, // 45
		-20, -1, -0.6, 1, 0,  // 46
		-20, -1, 30, 1, 1,  // 47
		-20.3, -1,  30, 0, 1, // 48

		//DINDING KANAN
		// front
		20, -1,  30, 0, 0,  // 49
		20.3, -1, 30, 1, 0,   // 50
		20.3, 15, 30, 1, 1,   // 51
		20, 15, 30, 0, 1,   // 52

		// right
		20.3, 15, 30, 0, 0,  // 53
		20,  15, -0.6, 1, 0,  // 54
		20, -1, -0.6, 1, 1,  // 55
		20.3, -1, 30, 0, 1,  // 56

		// back
		20.3, -1,  -0.6, 0, 0,  // 57
		20, -1, -0.6, 1, 0, // 58
		20,  15, -0.6, 1, 1, // 59
		20.3,  15, -0.6, 0, 1,  // 60

		// left
		20.3, -1,  -0.6, 0, 0, // 61
		20, -1,  30, 1, 0, // 62
		20, 15, 30, 1, 1, // 63
		20.3,  15, -0.6, 0, 1, // 64

		// upper
		20.3, 15, 30, 0, 0,   // 65
		20, 15, 30, 1, 0,  // 66
		20.3, 15, -0.6, 1, 1,  // 67
		20, 15, -0.6, 0, 1,   // 68

		// bottom
		20.3, -1, -0.6, 0, 0, // 69
		20, -1, -0.6, 1, 0,  // 70
		20.3, -1, 30, 1, 1,  // 71
		20, -1, 30, 0, 1, // 72

		//DINDING BELAKANG
		// front
		20, -1, 30, 0, 0,  // 73
		20, -1, 30, 1, 0,   // 74
		20, 15, 30, 1, 1,   // 75
		20, 15, 30, 0, 1,   // 76

		// right
		20, 15, 30, 0, 0,  // 77
		20, 15, 30.3, 1, 0,  // 78
		20, -1, 30, 1, 1,  // 79
		20, -1, 30.3, 0, 1,  // 80

		// back
		-20, -1, 30, 0, 0,  // 81
		20, -1, 30, 1, 0, // 82
		20, 15, 30, 1, 1, // 83
		-20, 15, 30, 0, 1,  // 84

		// left
		-20, -1, 30, 0, 0, // 85
		-20, -1, 30.3, 1, 0, // 86
		-20, 15, 30.3, 1, 1, // 87
		-20, -1, 30.3, 0, 1, // 88

		// upper
		20, 15, 30.3, 0, 0,   // 89
		-20, 15, 30.3, 1, 0,  // 90
		-20, 15, 30, 1, 1,  // 91
		20, 15, 30, 0, 1,   // 92

		// bottom
		-20, -1, 30, 0, 0, // 93
		20, -1, 30, 1, 0,  // 94
		20, -1, 30.3, 1, 1,  // 95
		-20, -1, 30.3, 0, 1, // 96

	};

	unsigned int indices[] = {
		//DINDING DEPAN
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22,   // bottom

		//DINDING KIRI
		24,  25,  26,  24,  26,  27,   // front
		28,  29,  30,  28,  30,  31,   // right
		32,  33,  34, 32,  34, 35,  // back
		36, 38, 37, 36, 39, 38,  // left
		40, 42, 41, 40, 43, 42,  // upper
		44, 46, 45, 44, 47, 46,   // bottom

		//DINDING KANAN
		48,  49,  50,  48,  50,  51,   // front
		52,  53,  54,  52,  54,  55,   // right
		56,  57,  58, 56,  58, 59,  // back
		60, 62, 61, 60, 63, 62,  // left
		64, 66, 65, 64, 67, 66,  // upper
		68, 70, 69, 68, 71, 70,   // bottom

		//DINDING BELAKANG
		72,  73,  74,  72,  74,  75,   // front
		76,  77,  78,  76,  78,  79,   // right
		80,  81,  82, 80,  82, 83,  // back
		84, 86, 85, 84, 87, 86,  // left
		88, 90, 89, 88, 91, 90,  // upper
		92, 94, 93, 92, 95, 94,   // bottom
	};

	glGenVertexArrays(1, &VAO5);
	glGenBuffers(1, &VBO5);
	glGenBuffers(1, &EBO5);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO5);

	glBindBuffer(GL_ARRAY_BUFFER, VBO5);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO5);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
//Nisa
void Demo::DrawColoredDinding()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture5);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, -7));
	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glBindVertexArray(VAO5); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, 144, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}
//Nisa
void Demo::BuildColoredAtap() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture6);
	glBindTexture(GL_TEXTURE_2D, texture6);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("sky.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		 // front
		-20,  15.01,  30.3, 0, 0,  // 0
		20,  15.01, 30.3, 1, 0,   // 1
		20, 15.2, 30.3, 1, 1,   // 2
		-20.5, 15.2, 30.3, 0, 1,   // 3

		// right
		20, 15.2, 30.8, 0, 0,  // 4
		20,  15.2, -0.3, 1, 0,  // 5
		20, 15.01, -0.3, 1, 1,  // 6
		20,  15.01, 30.8, 0, 1,  // 7

		// back
		-20, 15.01,  -0.7, 0, 0,  // 8 
		20, 15.01, -0.7, 1, 0, // 9
		20,  15.2, -0.7, 1, 1, // 10
		-20,  15.2, -0.7, 0, 1,  // 11

		// left
		-20, 15.01,  -0.3, 0, 0, // 12
		-20,  15.01,  20, 1, 0, // 13
		-20, 15.2, 20, 1, 1, // 14
		-20,  15.2, -0.3, 0, 1, // 15

		// upper
		20, 15.2, 30.8, 0, 0,   // 16
		-20, 15.2, 30.8, 1, 0,  // 17
		-20,  15.2, -0.8, 1, 1,  // 18
		20,  15.2, -0.3, 0, 1,   // 19

		// bottom
		-20, 15.01,  -0.3, 0, 0, // 20 
		20, 15.01, -0.3, 1, 0,  // 21
		20,  15.01, 30.8, 1, 1,  // 22
		-20,  15.01,  30.8, 0, 1, // 23

	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO6);
	glGenBuffers(1, &VBO6);
	glGenBuffers(1, &EBO6);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO6);

	glBindBuffer(GL_ARRAY_BUFFER, VBO6);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO6);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
//Nisa
void Demo::DrawColoredAtap()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture6);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO6); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredPlane()
{
	// Load and create a texture 
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("tile.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Build geometry
	GLfloat vertices[] = {
		// format position, tex coords
		// bottom
		-50.0, -0.5, -50.0,  0,  0,
		 50.0, -0.5, -50.0, 50,  0,
		 50.0, -0.5,  50.0, 50, 50,
		-50.0, -0.5,  50.0,  0, 50,


	};

	GLuint indices[] = { 0,  2,  1,  0,  3,  2 };

	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO2);

	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO
}

void Demo::DrawColoredPlane()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 1);

	glBindVertexArray(VAO2); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::InitCamera()
{
	posCamX = 10.0f;
	posCamY = 10.0f;
	posCamZ = 10.0f;
	viewCamX = 1.0f;
	viewCamY = 0.0f;
	viewCamZ = 0.0f;
	upCamX = 0.0f;
	upCamY = 1.0f;
	upCamZ = 0.0f;
	CAMERA_SPEED = 0.001f;
	fovy = 45.0f;
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}


void Demo::MoveCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	// forward positive cameraspeed and backward negative -cameraspeed.
	posCamX = posCamX + x * speed;
	posCamZ = posCamZ + z * speed;
	viewCamX = viewCamX + x * speed;
	viewCamZ = viewCamZ + z * speed;
}

void Demo::StrafeCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	float orthoX = -z;
	float orthoZ = x;

	// left positive cameraspeed and right negative -cameraspeed.
	posCamX = posCamX + orthoX * speed;
	posCamZ = posCamZ + orthoZ * speed;
	viewCamX = viewCamX + orthoX * speed;
	viewCamZ = viewCamZ + orthoZ * speed;
}

void Demo::RotateCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	viewCamZ = (float)(posCamZ + glm::sin(speed) * x + glm::cos(speed) * z);
	viewCamX = (float)(posCamX + glm::cos(speed) * x - glm::sin(speed) * z);
}


int main(int argc, char** argv) {
	RenderEngine &app = Demo();
	app.Start("Tim Rebahan - Grafkom A - Kos-Kosan 3D", 800, 600, false, false);
}