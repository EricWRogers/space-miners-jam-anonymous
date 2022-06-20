#pragma once
#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Canis/Math.hpp>
#include <Canis/Shader.hpp>
#include <Canis/Debug.hpp>
#include <Canis/InputManager.hpp>
#include <Canis/External/entt.hpp>

#include <Canis/ECS/Components/TransformComponent.hpp>
#include <Canis/ECS/Components/SphereColliderComponent.hpp>

#include "../Components/BulletComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Components/PlayerShipComponent.hpp"

class BulletSystem
{
public:
void UpdateComponents(float deltaTime, entt::registry &registry)
    {
        
        auto view = registry.view<Canis::TransformComponent, Canis::SphereColliderComponent, BulletComponent>();

        for (auto [bullet_entity, bullet_transform, bullet_sphere, bullet] : view.each())
        {
            // time
            bullet.life_time -= deltaTime;
            if (bullet.life_time < 0.0f)
            {
                registry.destroy(bullet_entity);
                continue;
            }

            if (bullet.big_miss)
                continue;

            // movement
            Canis::MoveTransformPosition(bullet_transform, (glm::vec3(0.0f,0.0f,1.0f) * bullet.speed) * deltaTime);
            
            // collision
            glm::vec3 bullet_global_position{bullet_transform.modelMatrix * glm::vec4(bullet_sphere.center, 1.0f)}; 
            float bullet_max_radius = bullet_sphere.radius * (std::max(std::max(bullet_transform.scale.x, 
                bullet_transform.scale.y), bullet_transform.scale.z) * 0.5f);

            auto targets_view = registry.view<Canis::TransformComponent, Canis::SphereColliderComponent, HealthComponent>();
            bool bullet_hit = false;
            for (auto [entity, transform, sphere, health] : targets_view.each())
            {
                float distance = glm::distance(transform.position, bullet_global_position);
                // quick check
                if (distance > (bullet_max_radius + sphere.radius) * 2.0f)
                {
                    continue;
                }

                float max_radius = sphere.radius * (std::max(std::max(transform.scale.x, 
                    transform.scale.y), transform.scale.z) * 0.5f);

                glm::vec3 global_position{transform.modelMatrix * glm::vec4(sphere.center, 1.0f)};

                if (distance < bullet_max_radius + max_radius)
                {
                    health.health -= 1;
                    bullet_hit = true;
                    continue;
                }
            }

            if (bullet_hit)
            {
                registry.destroy(bullet_entity);
                continue;
            }
        }        
    }

private:
};