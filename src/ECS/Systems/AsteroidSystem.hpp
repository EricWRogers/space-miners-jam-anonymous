#pragma once
#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Canis/Math.hpp>
#include <Canis/Shader.hpp>
#include <Canis/Debug.hpp>
#include <Canis/Camera.hpp>
#include <Canis/Window.hpp>
#include <Canis/InputManager.hpp>
#include <Canis/External/entt.hpp>

#include <Canis/ECS/Components/TransformComponent.hpp>
#include <Canis/ECS/Components/SphereColliderComponent.hpp>

#include "../Components/AsteroidComponent.hpp"
#include "../Components/HealthComponent.hpp"

#include "../../Scripts/ScoreSystem.hpp"
#include "../../Scripts/Wallet.hpp"

class AsteroidSystem
{
public:
ScoreSystem *scoreSystem;
Wallet *wallet;

void UpdateComponents(float deltaTime, entt::registry &registry)
    {
        
        auto view = registry.view<Canis::TransformComponent, HealthComponent, AsteroidComponent>();

        for (auto [entity, transform, health, asteroid] : view.each())
        {
            if (health.health <= 0.0f)
            {
                scoreSystem->AddPoints(asteroid.scrap);
                wallet->Earn(asteroid.scrap);
                registry.destroy(entity);
                continue;
            }
        }        
    }

private:
};