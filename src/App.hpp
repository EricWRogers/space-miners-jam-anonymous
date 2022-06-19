#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <math.h>
#include <chrono>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <Canis/Canis.hpp>
#include <Canis/Debug.hpp>
#include <Canis/Math.hpp>
#include <Canis/Time.hpp>
#include <Canis/Window.hpp>
#include <Canis/Shader.hpp>
#include <Canis/Camera.hpp>
#include <Canis/IOManager.hpp>
#include <Canis/InputManager.hpp>
#include <Canis/Data/GLTexture.hpp>
#include <Canis/Data/Vertex.hpp>
#include <Canis/External/entt.hpp>
#include <Canis/GameHelper/AStar.hpp>

#include <Canis/ECS/Systems/RenderMeshSystem.hpp>
#include <Canis/ECS/Systems/RenderSkyboxSystem.hpp>
#include <Canis/ECS/Systems/RenderTextSystem.hpp>

#include <Canis/ECS/Components/TransformComponent.hpp>
#include <Canis/ECS/Components/ColorComponent.hpp>
#include <Canis/ECS/Components/RectTransformComponent.hpp>
#include <Canis/ECS/Components/TextComponent.hpp>
#include <Canis/ECS/Components/MeshComponent.hpp>
#include <Canis/ECS/Components/SphereColliderComponent.hpp>

#include "ECS/Systems/BulletSystem.hpp"
#include "ECS/Systems/PlayerShipSystem.hpp"

#include "ECS/Components/BulletComponent.hpp"
#include "ECS/Components/HealthComponent.hpp"
#include "ECS/Components/PlayerShipComponent.hpp"

#ifdef __linux__
using namespace std::chrono::_V2;
#elif _WIN32
using namespace std::chrono;
#else

#endif


enum AppState
{
    ON,
    OFF
};

class App
{
public:
    App();
    ~App();

    void Run();

private:
    void Load();
    void Loop();
    void Update();
    void Draw();
    void LateUpdate();
    void FixedUpdate(float dt);
    void InputUpdate();

    void LoadECS();

    AppState appState = AppState::OFF;

    entt::registry entity_registry;

    Canis::Window window;

    Canis::Shader shader;

    Canis::Time time;

    Canis::InputManager inputManager;

    Canis::Camera camera = Canis::Camera(glm::vec3(0.0f, 0.15f, -0.3f),glm::vec3(0.0f, 1.0f, 0.0f),Canis::YAW+90.0f,Canis::PITCH+0.0f);

    Canis::RenderMeshSystem renderMeshSystem;
    Canis::RenderSkyboxSystem renderSkyboxSystem;
    Canis::RenderTextSystem renderTextSystem;

    PlayerShipSystem playerShipSystem;

    // move out to external class
    unsigned int whiteCubeVAO, whiteCubeVBO,
                asteroidVAO, asteroidVBO,
                asteroidMetalVAO, asteroidMetalVBO,
                playerVAO, playerVBO,
                playerGlassVAO, playerGlassVBO;

    int whiteCubeSize, asteroidSize, asteroidMetalSize, playerSize, playerGlassSize;

    Canis::GLTexture texture = {};

    Canis::GLTexture diffuseColorPaletteTexture = {};
    Canis::GLTexture specularColorPaletteTexture = {};

    float lastXMousePos;
    float lastYMousePos;
    
    bool firstMouseMove = true;
    bool mouseLock = false;

    high_resolution_clock::time_point currentTime;
    high_resolution_clock::time_point previousTime;
    double deltaTime;

    Canis::AStar aStar;

    unsigned int seed;
    
};