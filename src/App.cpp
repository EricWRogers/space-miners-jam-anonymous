#include "App.hpp"

// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

App::App()
{
	
}
App::~App()
{
	
}

void App::Run()
{
	if (appState == AppState::ON)
		Canis::FatalError("App already running.");

	Canis::Init();

	unsigned int windowFlags = 0;

	// windowFlags |= Canis::WindowFlags::FULLSCREEN;

	// windowFlags |= Canis::WindowFlags::BORDERLESS;

	window.Create("Canis", 1280, 720, windowFlags);

	time.init(1000);

	camera.override_camera = false;

	seed = std::time(NULL);
	srand(seed);
	Canis::Log("seed : " + std::to_string(seed));

	Load();

	window.MouseLock(mouseLock);

	appState = AppState::ON;

	Loop();
}
void App::Load()
{
	// configure global opengl state
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	// glEnable(GL_CULL_FACE);
	// build and compile our shader program
	shader.Compile("assets/shaders/lighting.vs", "assets/shaders/lighting.fs");
	shader.AddAttribute("aPos");
	shader.AddAttribute("aNormal");
	shader.AddAttribute("aTexcoords");
	shader.Link();

	// Load color palette
	diffuseColorPaletteTexture = Canis::LoadPNGToGLTexture("assets/textures/palette/diffuse.png", GL_RGBA, GL_RGBA);
	specularColorPaletteTexture = Canis::LoadPNGToGLTexture("assets/textures/palette/specular.png", GL_RGBA, GL_RGBA);

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	std::vector<Canis::Vertex> vecVertex;

	bool res = Canis::LoadOBJ("assets/models/white_block.obj", vertices, uvs, normals);

	for(int i = 0; i < vertices.size(); i++)
	{
		Canis::Vertex v = {};
		v.Position = vertices[i];
		v.Normal = normals[i];
		v.TexCoords = uvs[i];
		vecVertex.push_back(v);
	}

	whiteCubeSize = vecVertex.size();
	Canis::Log("s " + std::to_string(vecVertex.size()));

	glGenVertexArrays(1, &whiteCubeVAO);
	glGenBuffers(1, &whiteCubeVBO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(whiteCubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, whiteCubeVBO);
	glBufferData(GL_ARRAY_BUFFER, vecVertex.size() * sizeof(Canis::Vertex), &vecVertex[0], GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	// asteroid

	vecVertex.clear();
	vertices.clear();
	uvs.clear();
	normals.clear();

	res = Canis::LoadOBJ("assets/models/rock.obj", vertices, uvs, normals);

	for(int i = 0; i < vertices.size(); i++)
	{
		Canis::Vertex v = {};
		v.Position = vertices[i];
		v.Normal = normals[i];
		v.TexCoords = uvs[i];
		vecVertex.push_back(v);
	}

	asteroidSize = vecVertex.size();
	Canis::Log("s " + std::to_string(vecVertex.size()));

	glGenVertexArrays(1, &asteroidVAO);
	glGenBuffers(1, &asteroidVBO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(asteroidVAO);

	glBindBuffer(GL_ARRAY_BUFFER, asteroidVBO);
	glBufferData(GL_ARRAY_BUFFER, vecVertex.size() * sizeof(Canis::Vertex), &vecVertex[0], GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	// asteroid_metal

	vecVertex.clear();
	vertices.clear();
	uvs.clear();
	normals.clear();

	res = Canis::LoadOBJ("assets/models/asteroid_metal.obj", vertices, uvs, normals);

	for(int i = 0; i < vertices.size(); i++)
	{
		Canis::Vertex v = {};
		v.Position = vertices[i];
		v.Normal = normals[i];
		v.TexCoords = uvs[i];
		vecVertex.push_back(v);
	}

	asteroidMetalSize = vecVertex.size();
	Canis::Log("s " + std::to_string(vecVertex.size()));

	glGenVertexArrays(1, &asteroidMetalVAO);
	glGenBuffers(1, &asteroidMetalVBO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(asteroidMetalVAO);

	glBindBuffer(GL_ARRAY_BUFFER, asteroidMetalVBO);
	glBufferData(GL_ARRAY_BUFFER, vecVertex.size() * sizeof(Canis::Vertex), &vecVertex[0], GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	// player

	vecVertex.clear();
	vertices.clear();
	uvs.clear();
	normals.clear();

	res = Canis::LoadOBJ("assets/models/craft_miner.obj", vertices, uvs, normals);

	for(int i = 0; i < vertices.size(); i++)
	{
		Canis::Vertex v = {};
		v.Position = vertices[i];
		v.Normal = normals[i];
		v.TexCoords = uvs[i];
		vecVertex.push_back(v);
	}

	playerSize = vecVertex.size();
	Canis::Log("s " + std::to_string(vecVertex.size()));

	glGenVertexArrays(1, &playerVAO);
	glGenBuffers(1, &playerVBO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(playerVAO);

	glBindBuffer(GL_ARRAY_BUFFER, playerVBO);
	glBufferData(GL_ARRAY_BUFFER, vecVertex.size() * sizeof(Canis::Vertex), &vecVertex[0], GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	// player glass

	vecVertex.clear();
	vertices.clear();
	uvs.clear();
	normals.clear();

	res = Canis::LoadOBJ("assets/models/craft_miner_glass.obj", vertices, uvs, normals);

	for(int i = 0; i < vertices.size(); i++)
	{
		Canis::Vertex v = {};
		v.Position = vertices[i];
		v.Normal = normals[i];
		v.TexCoords = uvs[i];
		vecVertex.push_back(v);
	}

	playerGlassSize = vecVertex.size();
	Canis::Log("s " + std::to_string(vecVertex.size()));

	glGenVertexArrays(1, &playerGlassVAO);
	glGenBuffers(1, &playerGlassVBO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(playerGlassVAO);

	glBindBuffer(GL_ARRAY_BUFFER, playerGlassVBO);
	glBufferData(GL_ARRAY_BUFFER, vecVertex.size() * sizeof(Canis::Vertex), &vecVertex[0], GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	// Draw mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Game Systems
	LoadECS();

	// start timer
	previousTime = high_resolution_clock::now();
}
void App::Loop()
{
	while (appState == AppState::ON)
	{
		deltaTime = time.startFrame();

		Update();
		Draw();
		// Get SDL to swap our buffer
		window.SwapBuffer();
		LateUpdate();
		FixedUpdate(deltaTime);
		InputUpdate();

		float fps = time.endFrame(); 
		
		window.SetWindowName("Canis : Game Name fps : " + std::to_string(fps)
		 + " deltaTime : " + std::to_string(deltaTime)
		 + " Enitity : " + std::to_string(entity_registry.size())
		 + " Rendered : " + std::to_string(renderMeshSystem.entities_rendered));
	}
}
void App::Update()
{
	playerShipSystem.UpdateComponents(deltaTime, entity_registry);
	bulletSystem.UpdateComponents(deltaTime, entity_registry);
	asteroidSystem.UpdateComponents(deltaTime, entity_registry);
	rocketSystem.UpdateComponents(deltaTime, entity_registry);
	hudManager.Update(deltaTime, entity_registry);
}
void App::Draw()
{
	glDepthFunc(GL_LESS);
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

	renderSkyboxSystem.UpdateComponents(deltaTime, entity_registry);

	renderMeshSystem.UpdateComponents(deltaTime, entity_registry);
	
	renderTextSystem.UpdateComponents(deltaTime, entity_registry);
}
void App::LateUpdate() {}
void App::FixedUpdate(float dt)
{
	if (inputManager.isKeyPressed(SDLK_w) && mouseLock)
	{
		camera.ProcessKeyboard(Canis::Camera_Movement::FORWARD, dt);
	}

	if (inputManager.isKeyPressed(SDLK_s) && mouseLock)
	{
		camera.ProcessKeyboard(Canis::Camera_Movement::BACKWARD, dt);
	}

	if (inputManager.isKeyPressed(SDLK_a) && mouseLock)
	{
		camera.ProcessKeyboard(Canis::Camera_Movement::LEFT, dt);
	}

	if (inputManager.isKeyPressed(SDLK_d) && mouseLock)
	{
		camera.ProcessKeyboard(Canis::Camera_Movement::RIGHT, dt);
	}

	if (inputManager.justPressedKey(SDLK_ESCAPE))
    {
		mouseLock = !mouseLock;
		//camera.override_camera = !camera.override_camera;

        window.MouseLock(mouseLock);
    }
}
void App::InputUpdate()
{
	inputManager.swapMaps();

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			appState = AppState::OFF;
			break;
		case SDL_MOUSEMOTION:
			if (mouseLock)
			{
				camera.ProcessMouseMovement(
					event.motion.xrel,
					-event.motion.yrel);
			}
			else
			{
				inputManager.mouse.x = event.motion.x;
				inputManager.mouse.y = event.motion.y;
			}
			break;
		case SDL_KEYUP:
			inputManager.releasedKey(event.key.keysym.sym);
			//Canis::Log("UP" + std::to_string(event.key.keysym.sym));
			break;
		case SDL_KEYDOWN:
			inputManager.pressKey(event.key.keysym.sym);
			//Canis::Log("DOWN");
			break;
		case SDL_MOUSEBUTTONDOWN:
			if(event.button.button == SDL_BUTTON_LEFT)
				inputManager.leftClick = true;
			if(event.button.button == SDL_BUTTON_RIGHT)
				inputManager.rightClick = true;
			break;
		}
	}
}

void App::LoadECS()
{
	// this is a hack need to sort object by distance to camera from render
	entt::entity player_ship_glass = entity_registry.create();
	entity_registry.emplace<Canis::TransformComponent>(player_ship_glass,
		true, // active
		glm::vec3(0.0f, 0.0f, 0.0f), // position
		glm::vec3(0.0f, 0.0f, 0.0f), // rotation
		glm::vec3(1, 1, 1) // scale
	);
	entity_registry.emplace<Canis::ColorComponent>(player_ship_glass,
		glm::vec4(1.0f)
	);
	entity_registry.emplace<Canis::MeshComponent>(player_ship_glass,
		playerGlassVAO,
		playerGlassSize
	);
	entity_registry.emplace<Canis::SphereColliderComponent>(player_ship_glass,
		glm::vec3(0.0f),
		1.5f
	);

	const auto player_ship_body = entity_registry.create();
	entity_registry.emplace<Canis::TransformComponent>(player_ship_body,
		true, // active
		glm::vec3(0.0f, 0.0f, 0.0f), // position
		glm::vec3(0.0f, 0.0f, 0.0f), // rotation
		glm::vec3(1, 1, 1) // scale
	);
	entity_registry.emplace<Canis::ColorComponent>(player_ship_body,
		glm::vec4(1.0f)
	);
	entity_registry.emplace<Canis::MeshComponent>(player_ship_body,
		playerVAO,
		playerSize
	);
	entity_registry.emplace<Canis::SphereColliderComponent>(player_ship_body,
		glm::vec3(0.0f),
		1.5f
	);

	const entt::entity player_ship = entity_registry.create();
	entity_registry.emplace<Canis::TransformComponent>(player_ship,
		true, // active
		glm::vec3(0.0f, 0.0f, 0.0f), // position
		glm::vec3(0.0f, 0.0f, 0.0f), // rotation
		glm::vec3(1, 1, 1) // scale
	);
	entity_registry.emplace<Canis::ColorComponent>(player_ship,
		glm::vec4(1.0f)
	);
	entity_registry.emplace<Canis::SphereColliderComponent>(player_ship,
		glm::vec3(0.0f),
		1.5f
	);
	entity_registry.emplace<PlayerShipComponent>(player_ship,
		player_ship_glass,
		player_ship_body,
		camera.Position,
		glm::vec3(-0.191221f,0.079734f,0.418706f),
		glm::vec3(0.191221f,0.079734f,0.418706f),
		camera.Position - glm::vec3(0.0f,1.0f,0.0f),
		5.0f,
		glm::vec2(1.0f),
		glm::vec2(1.0f),
		8.0f,
		0.5f,
		0.0f,
		0.0f,
		0.0f
	);

	struct PositionAndSize {
		glm::vec3 position;
		glm::vec3 size;
		float radius;
	};

	std::vector<PositionAndSize> positions_and_size;

	PositionAndSize cameraPlacementInfo = {
		camera.Position,
		glm::vec3(1.0f),
		5.0f
	};

	positions_and_size.push_back(cameraPlacementInfo);

	// spawn normal asteroid
	int max_num_of_normal_asteroid = 2000;
	int current_num_of_normal_asteroid = 0;
	glm::vec3 min_position = glm::vec3(-50.0f,-50.0f,-50.0f);
	glm::vec3 max_position = glm::vec3(50.0f,50.0f,50.0f);
	glm::vec3 min_size = glm::vec3(1.0f,1.0f,1.0f);
	glm::vec3 max_size = glm::vec3(3.0f,3.0f,3.0f);
	glm::vec2 radius_range = glm::vec2(1.0f,2.0f);

	while(max_num_of_normal_asteroid != current_num_of_normal_asteroid)
	{
		bool not_found = true;

		PositionAndSize position_info = {};

		while(not_found)
		{
			// pick random position and size
			// this could be better
			position_info.position = glm::vec3(
				min_position.x + rand()%int(max_position.x - min_position.x),
				min_position.y + rand()%int(max_position.y - min_position.y),
				min_position.z + rand()%int(max_position.z - min_position.z)
			);

			position_info.size = glm::vec3(
				min_size.x + rand()%int(max_size.x - min_size.x),
				min_size.y + rand()%int(max_size.y - min_size.y),
				min_size.z + rand()%int(max_size.z - min_size.z)
			);

			position_info.radius = radius_range.x + rand()%int(radius_range.y - radius_range.x);

			// check if position is okay

			not_found = false;

			for(int i = 0; i < positions_and_size.size(); i++)
			{
				float distance = glm::distance(position_info.position, positions_and_size[i].position);
				float entity_spacing_buffer = position_info.radius + positions_and_size[i].radius;

				if (distance < entity_spacing_buffer)
				{
					not_found = true;
					continue;
				}
			}
		}

		// TODO : randomize rotation

		// create entity
		const auto entity = entity_registry.create();
		entity_registry.emplace<Canis::TransformComponent>(entity,
			true, // active
			position_info.position, // position
			glm::vec3(float(rand()%360), float(rand()%360), float(rand()%360)), // rotation
			position_info.size // scale
		);
		entity_registry.emplace<Canis::ColorComponent>(entity,
			glm::vec4(1.0f)
		);
		entity_registry.emplace<Canis::MeshComponent>(entity,
			asteroidVAO,
			asteroidSize
		);
		entity_registry.emplace<Canis::SphereColliderComponent>(entity,
			glm::vec3(0.0f),
			position_info.radius
		);
		entity_registry.emplace<HealthComponent>(entity,
			2,
			2
		);
		entity_registry.emplace<AsteroidComponent>(entity,
			5.0f
		);

		positions_and_size.push_back(position_info);

		current_num_of_normal_asteroid++;
	}

	// spawn metal asteroid
	int max_num_of_metal_asteroid = 500;
	int current_num_of_metal_asteroid = 0;
	while(max_num_of_metal_asteroid != current_num_of_metal_asteroid)
	{
		bool not_found = true;

		PositionAndSize position_info = {};

		while(not_found)
		{
			// pick random position and size
			// this could be better
			position_info.position = glm::vec3(
				min_position.x + rand()%int(max_position.x - min_position.x),
				min_position.y + rand()%int(max_position.y - min_position.y),
				min_position.z + rand()%int(max_position.z - min_position.z)
			);

			position_info.size = glm::vec3(
				min_size.x + rand()%int(max_size.x - min_size.x),
				min_size.y + rand()%int(max_size.y - min_size.y),
				min_size.z + rand()%int(max_size.z - min_size.z)
			);

			position_info.radius = radius_range.x + rand()%int(radius_range.y - radius_range.x);

			// check if position is okay

			not_found = false;

			for(int i = 0; i < positions_and_size.size(); i++)
			{
				float distance = glm::distance(position_info.position, positions_and_size[i].position);
				float entity_spacing_buffer = position_info.radius + positions_and_size[i].radius;

				if (distance < entity_spacing_buffer)
				{
					not_found = true;
					continue;
				}
			}
		}

		// TODO : randomize rotation

		// create entity
		const auto entity = entity_registry.create();
		entity_registry.emplace<Canis::TransformComponent>(entity,
			true, // active
			position_info.position, // position
			glm::vec3(float(rand()%360), float(rand()%360), float(rand()%360)), // rotation
			position_info.size // scale
		);
		entity_registry.emplace<Canis::ColorComponent>(entity,
			glm::vec4(1.0f)
		);
		entity_registry.emplace<Canis::MeshComponent>(entity,
			asteroidMetalVAO,
			asteroidMetalSize
		);
		entity_registry.emplace<Canis::SphereColliderComponent>(entity,
			glm::vec3(0.0f),
			position_info.radius
		);
		entity_registry.emplace<HealthComponent>(entity,
			2,
			2
		);
		entity_registry.emplace<AsteroidComponent>(entity,
			5.0f
		);

		positions_and_size.push_back(position_info);

		current_num_of_metal_asteroid++;
	}

	renderSkyboxSystem.faces = std::vector<std::string>
	{
		"assets/textures/space-nebulas-skybox/skybox_left.png",
		"assets/textures/space-nebulas-skybox/skybox_right.png",
		"assets/textures/space-nebulas-skybox/skybox_up.png",
		"assets/textures/space-nebulas-skybox/skybox_down.png",
		"assets/textures/space-nebulas-skybox/skybox_front.png",
		"assets/textures/space-nebulas-skybox/skybox_back.png"
	};

	asteroidSystem.scoreSystem = &scoreSystem;
	asteroidSystem.wallet = &wallet;

	hudManager.inputManager = &inputManager;
	hudManager.window = &window;
	hudManager.wallet = &wallet;
	hudManager.playerShipSystem = &playerShipSystem;
	hudManager.Load(entity_registry);

	wallet.refRegistry = &entity_registry;
	wallet.walletText = hudManager.walletText;
	wallet.SetCash(50);

	scoreSystem.refRegistry = &entity_registry;
	scoreSystem.scoreText = hudManager.scoreText;
	
	playerShipSystem.camera = &camera;
	playerShipSystem.input_manager = &inputManager;
	playerShipSystem.bulletVAO = whiteCubeVAO;
	playerShipSystem.bulletSize = whiteCubeSize;

	renderSkyboxSystem.window = &window;
	renderSkyboxSystem.camera = &camera;
	renderSkyboxSystem.Init();

	renderTextSystem.camera = &camera;
	renderTextSystem.window = &window;
	renderTextSystem.Init();

	renderMeshSystem.shader = &shader;
	renderMeshSystem.camera = &camera;
	renderMeshSystem.window = &window;
	renderMeshSystem.diffuseColorPaletteTexture = &diffuseColorPaletteTexture;
	renderMeshSystem.specularColorPaletteTexture = &specularColorPaletteTexture;
}