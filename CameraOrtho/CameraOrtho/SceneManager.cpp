#include "SceneManager.h"

//static controllers for mouse and keyboard
static bool keys[1024];
static bool resized;
static bool mousePrimeiraImagem = false;
static bool mouseSegundaImagem = false;
static bool mouseTerceiraImagem = false;
static bool mouseQuartaImagem = false;
static bool mouseQuintaImagem = false;
static bool mouseSextaImagem = false;
static bool flagFirst = true;
static vector <bool> listSticker;

static GLuint width, height;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::initialize(GLuint w, GLuint h)
{
	width = w;
	height = h;

	// GLFW - GLEW - OPENGL general setup -- TODO: config file
	initializeGraphics();

}

void SceneManager::initializeGraphics()
{
	// Init GLFW
	glfwInit();

	// Create a GLFWwindow object that we can use for GLFW's functions
	window = glfwCreateWindow(width, height, "Hello Sprites", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);

	glfwSetMouseButtonCallback(window, mouse_button_callback);

	//Setando a callback de redimensionamento da janela
	glfwSetWindowSizeCallback(window, resize);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	// Build and compile our shader program
	addShader();

	//setup the scene -- LEMBRANDO QUE A DESCRIÇÃO DE UMA CENA PODE VIR DE ARQUIVO(S) DE 
	// CONFIGURAÇÃO
	setupScene();

	resized = true; //para entrar no setup da câmera na 1a vez

}

void SceneManager::addShader()
{
	objShader.push_back(new Shader("../shaders/transformations.vs", "../shaders/transformations.frag"));
	objShader.push_back(new Shader("../shaders/binarizacao.vs", "../shaders/binarizacao.frag"));
	objShader.push_back(new Shader("../shaders/bluerender.vs", "../shaders/bluerender.frag"));
	objShader.push_back(new Shader("../shaders/inversao.vs", "../shaders/inversao.frag"));
	objShader.push_back(new Shader("../shaders/grayscale.vs", "../shaders/grayscale.frag"));
	objShader.push_back(new Shader("../shaders/colorizacao.vs", "../shaders/colorizacao.frag"));
	objShader.push_back(new Shader("../shaders/myfilter.vs", "../shaders/myfilter.frag"));
}


void SceneManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void SceneManager::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		if (ypos >= 500.0f && ypos <= 550) {

			if (xpos >= 280.0f && xpos <= 310.0f)
			{
				mousePrimeiraImagem = !mousePrimeiraImagem;
				mouseSegundaImagem = false;
				mouseTerceiraImagem = false;
				mouseQuartaImagem = false;
				mouseQuintaImagem = false;
				mouseSextaImagem = false;

			}
			else if (xpos >= 320.0f && xpos <= 350.0f) {
				mousePrimeiraImagem = false;
				mouseSegundaImagem = !mouseSegundaImagem;
				mouseTerceiraImagem = false;
				mouseQuartaImagem = false;
				mouseQuintaImagem = false;
				mouseSextaImagem = false;
			}
			else if (xpos >= 360.0f && xpos <= 390.0f) {
				mousePrimeiraImagem = false;
				mouseSegundaImagem = false;
				mouseTerceiraImagem = !mouseTerceiraImagem;
				mouseQuartaImagem = false;
				mouseQuintaImagem = false;
				mouseSextaImagem = false;
			}
			else if (xpos >= 400.0f && xpos <= 430.0f) {
				mousePrimeiraImagem = false;
				mouseSegundaImagem = false;
				mouseTerceiraImagem = false;
				mouseQuartaImagem = !mouseQuartaImagem;
				mouseQuintaImagem = false;
				mouseSextaImagem = false;
			}
			else if (xpos >= 440.0f && xpos <= 470.0f) {
				mousePrimeiraImagem = false;
				mouseSegundaImagem = false;
				mouseTerceiraImagem = false;
				mouseQuartaImagem = false;
				mouseQuintaImagem = !mouseQuintaImagem;
				mouseSextaImagem = false;
			}
			else if (xpos >= 480.0f && xpos <= 510.0f) {
				mousePrimeiraImagem = false;
				mouseSegundaImagem = false;
				mouseTerceiraImagem = false;
				mouseQuartaImagem = false;
				mouseQuintaImagem = false;
				mouseSextaImagem = !mouseSextaImagem;
			}

		}
		else if (ypos >= 30.0f && ypos <= 80) {
			if (xpos >= 280.0f && xpos <= 310.0f) {
				listSticker[0] = !listSticker[0];
			}
			else if (xpos >= 320.0f && xpos <= 350.0f) {
				listSticker[1] = !listSticker[1];
			}
			else if (xpos >= 360.0f && xpos <= 390.0f) {
				listSticker[2] = !listSticker[2];
			}
			else if (xpos >= 400.0f && xpos <= 430.0f) {
				listSticker[3] = !listSticker[3];
			}
			else if (xpos >= 440.0f && xpos <= 470.0f) {
				listSticker[4] = !listSticker[4];
			}
			else if (xpos >= 480.0f && xpos <= 510.0f) {
				listSticker[5] = !listSticker[5];
			}

		}

	}
}

void SceneManager::resize(GLFWwindow* window, int w, int h)
{
	width = w;
	height = h;
	resized = true;

	// Define the viewport dimensions
	glViewport(0, 0, width, height);
}


void SceneManager::update()
{
	if (keys[GLFW_KEY_ESCAPE])
		glfwSetWindowShouldClose(window, GL_TRUE);


	//AQUI aplicaremos as transformações nos sprites

	//altera o angulo do segundo objeto
}

void SceneManager::render()
{
	// Clear the colorbuffer
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if (resized) //se houve redimensionamento na janela, redefine a projection matrix
	{
		setupCamera2D();
		resized = false;
	}

	objInitial[0]->update();
	objInitial[0]->draw();

	for (Sprite* miniSticker : objMiniSticker) {
		miniSticker->update();
		miniSticker->draw();
	}

	for (Sprite* imgInicial : objects) {
		imgInicial->update();
		imgInicial->draw();
	}

	if (mousePrimeiraImagem) {
		objInitial[0]->setShader(objShader[1]);
	}
	else	if (mouseSegundaImagem) {
		objInitial[0]->setShader(objShader[2]);
	}
	else 	if (mouseTerceiraImagem) {
		objInitial[0]->setShader(objShader[3]);
	}
	else 	if (mouseQuartaImagem) {
		objInitial[0]->setShader(objShader[4]);
	}
	else 	if (mouseQuintaImagem) {
		objInitial[0]->setShader(objShader[5]);
	}
	else 	if (mouseSextaImagem) {
		objInitial[0]->setShader(objShader[6]);
	}
	else {
		objInitial[0]->setShader(objShader[0]);
	}

	for (int i = 0; i < 6; i++) {
		if (listSticker[i]) {
			objSticker[i]->update();
			objSticker[i]->draw();
		}
	}

}

void SceneManager::run()
{
	//GAME LOOP
	while (!glfwWindowShouldClose(window))
	{

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		//Update method(s)
		update();

		//Render scene
		render();

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
}

void SceneManager::finish()
{
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
}

void SceneManager::setupScene()
{
	//Criação dos Sprites iniciais -- pode-se fazer métodos de criação posteriormente

	//Mínimo: posicao e escala e ponteiro para o shader
	unsigned int texID = loadTexture("../textures/lena.png");
	Sprite* obj = new Sprite;
	obj->setPosition(glm::vec3(250.0f, 100.0f, 0.0));
	obj->setDimension(glm::vec3(300.0f, 400.0f, 1.0f));
	obj->setShader(objShader[0]);
	objInitial.push_back(obj);
	objInitial[0]->setTexture(texID);

	float xInicial = 280.0f;
	for (int i = 0; i < 6; i++) {
		obj = new Sprite;
		obj->setPosition(glm::vec3(xInicial, 50.0f, 0.0));
		obj->setDimension(glm::vec3(30.0f, 40.0f, 1.0f));
		obj->setShader(objShader[i + 1]);
		objects.push_back(obj);
		objects[i]->setTexture(texID);

		xInicial += 40;
	}

	texID = loadTexture("../textures/sticker.png");
	obj = new Sprite;
	obj->setPosition(glm::vec3(280.0f, 500.0f, 0.0));
	obj->setDimension(glm::vec3(30.0f, 40.0f, 1.0f));
	obj->setShader(objShader[0]);
	objMiniSticker.push_back(obj);
	objMiniSticker[0]->setTexture(texID);

	obj = new Sprite;
	obj->setPosition(glm::vec3(250.0f, 100.0f, 0.0));
	obj->setDimension(glm::vec3(300.0f, 400.0f, 1.0f));
	obj->setShader(objShader[0]);
	objSticker.push_back(obj);
	objSticker[0]->setTexture(texID);

	texID = loadTexture("../textures/estrelas.png");
	obj = new Sprite;
	obj->setPosition(glm::vec3(280.0f, 520.0f, 0.0));
	obj->setDimension(glm::vec3(30.0f, 40.0f, 1.0f));
	obj->setShader(objShader[0]);
	objMiniSticker.push_back(obj);
	objMiniSticker[1]->setTexture(texID);

	obj = new Sprite;
	obj->setPosition(glm::vec3(250.0f, 100.0f, 0.0));
	obj->setDimension(glm::vec3(300.0f, 400.0f, 1.0f));
	obj->setShader(objShader[0]);
	objSticker.push_back(obj);
	objSticker[1]->setTexture(texID);

	texID = loadTexture("../textures/ouro.png");
	obj = new Sprite;
	obj->setPosition(glm::vec3(280.0f, 520.0f, 0.0));
	obj->setDimension(glm::vec3(30.0f, 40.0f, 1.0f));
	obj->setShader(objShader[0]);
	objMiniSticker.push_back(obj);
	objMiniSticker[2]->setTexture(texID);

	obj = new Sprite;
	obj->setPosition(glm::vec3(250.0f, 100.0f, 0.0));
	obj->setDimension(glm::vec3(300.0f, 400.0f, 1.0f));
	obj->setShader(objShader[0]);
	objSticker.push_back(obj);
	objSticker[2]->setTexture(texID);

	texID = loadTexture("../textures/fogos.png");
	obj = new Sprite;
	obj->setPosition(glm::vec3(280.0f, 520.0f, 0.0));
	obj->setDimension(glm::vec3(30.0f, 40.0f, 1.0f));
	obj->setShader(objShader[0]);
	objMiniSticker.push_back(obj);
	objMiniSticker[3]->setTexture(texID);

	obj = new Sprite;
	obj->setPosition(glm::vec3(250.0f, 100.0f, 0.0));
	obj->setDimension(glm::vec3(300.0f, 400.0f, 1.0f));
	obj->setShader(objShader[0]);
	objSticker.push_back(obj);
	objSticker[3]->setTexture(texID);

	texID = loadTexture("../textures/chuva.png");
	obj = new Sprite;
	obj->setPosition(glm::vec3(280.0f, 520.0f, 0.0));
	obj->setDimension(glm::vec3(30.0f, 40.0f, 1.0f));
	obj->setShader(objShader[0]);
	objMiniSticker.push_back(obj);
	objMiniSticker[4]->setTexture(texID);

	obj = new Sprite;
	obj->setPosition(glm::vec3(250.0f, 100.0f, 0.0));
	obj->setDimension(glm::vec3(300.0f, 400.0f, 1.0f));
	obj->setShader(objShader[0]);
	objSticker.push_back(obj);
	objSticker[4]->setTexture(texID);

	texID = loadTexture("../textures/tornado.png");
	obj = new Sprite;
	obj->setPosition(glm::vec3(280.0f, 520.0f, 0.0));
	obj->setDimension(glm::vec3(30.0f, 40.0f, 1.0f));
	obj->setShader(objShader[0]);
	objMiniSticker.push_back(obj);
	objMiniSticker[5]->setTexture(texID);

	obj = new Sprite;
	obj->setPosition(glm::vec3(250.0f, 100.0f, 0.0));
	obj->setDimension(glm::vec3(300.0f, 400.0f, 1.0f));
	obj->setShader(objShader[0]);
	objSticker.push_back(obj);
	objSticker[5]->setTexture(texID);

	float xInicialSticker = 280.0f;
	for (Sprite* miniSticker : objMiniSticker) {
		miniSticker->setPosition(glm::vec3(xInicialSticker, 520.0f, 0.0));
		xInicialSticker += 40;
		listSticker.push_back(false);
	}

	//Definindo a janela do mundo (ortho2D)
	ortho2D[0] = 0.0f; //xMin
	ortho2D[1] = 800.0f; //xMax
	ortho2D[2] = 0.0f; //yMin
	ortho2D[3] = 600.0f; //yMax

	//Habilita transparência
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void SceneManager::setupCamera2D() //TO DO: parametrizar aqui
{
	float zNear = -1.0, zFar = 1.0; //estão fixos porque não precisamos mudar

	projection = glm::ortho(ortho2D[0], ortho2D[1], ortho2D[2], ortho2D[3], zNear, zFar);

	for (Shader* shaders : objShader) {
		shaders->Use();
		//Obtendo o identificador da matriz de projeção para enviar para o shader
		GLint projLoc = glGetUniformLocation(shaders->ID, "projection");

		//Enviando a matriz de projeção para o shader
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	}
}

unsigned int SceneManager::loadTexture(string filename)
{
	unsigned int texture;

	// load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
										   // set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load image, create texture and generate mipmaps
	int width, height, nrChannels;

	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		if (nrChannels == 3) //jpg, bmp
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else //png
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	glActiveTexture(GL_TEXTURE0);

	return texture;
}
