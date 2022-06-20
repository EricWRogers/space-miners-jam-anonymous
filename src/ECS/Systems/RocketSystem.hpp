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

#include "../Components/AsteroidComponent.hpp"
#include "../Components/RocketComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Components/PlayerShipComponent.hpp"

class RocketSystem
{
public:
void UpdateComponents(float deltaTime, entt::registry &registry)
    {
        
        auto view = registry.view<Canis::TransformComponent, Canis::SphereColliderComponent, RocketComponent>();

        for (auto [rocket_entity, rocket_transform, bullet_sphere, rocket] : view.each())
        {
            // time
            rocket.life_time -= deltaTime;
            if (rocket.life_time < 0.0f)
            {
                registry.destroy(rocket_entity);
                continue;
            }            

            // movement
            Canis::MoveTransformPosition(rocket_transform, (glm::vec3(0.0f,0.0f,1.0f) * rocket.speed) * deltaTime);

            if (rocket.big_miss)
                continue;
            
            // find target
            entt::entity target_entity;
            float closet_distance = 1000.0f;

            glm::vec3 min_search_position = glm::vec3(
                glm::translate(
                    rocket_transform.modelMatrix,
                    glm::vec3(-5.0f,-5.0f,1.0f)
                    )[3]);

            glm::vec3 max_search_position = glm::vec3(
                glm::translate(
                    rocket_transform.modelMatrix,
                    glm::vec3(5.0f,5.0f,30.0f)
                    )[3]);
            
            rocket.big_miss = true;
            
            auto targets_view = registry.view<Canis::TransformComponent, Canis::SphereColliderComponent, HealthComponent, AsteroidComponent>();
            for (auto [entity, transform, sphere, health, asteroid] : targets_view.each())
            {
                // bounds check 
                // TODO : make this faster
                /*if (
                    ((min_search_position.x < transform.position.x) && (transform.position.x < max_search_position.x))
                    || ((min_search_position.x > transform.position.x) && (transform.position.x > max_search_position.x)))
                {
                    //Canis::Log("Passed X");
                    if (
                        ((min_search_position.y < transform.position.y) && (transform.position.y < max_search_position.y))
                        || ((min_search_position.y > transform.position.y) && (transform.position.y > max_search_position.y)))
                    {
                        //Canis::Log("Passed Y");
                        if (
                            ((min_search_position.z < transform.position.z) && (transform.position.z < max_search_position.z))
                            || ((min_search_position.z > transform.position.z) && (transform.position.z > max_search_position.z)))
                        {
                            //Canis::Log("Passed Z");
                        }
                        else
                            continue;
                    }
                    else
                        continue;
                }
                else
                    continue;*/
                
                //Canis::Log("Passed");
                
                // atleast one target found
                rocket.big_miss = false;

                // closest target
                float distance = glm::distance(transform.position, rocket_transform.position);

                if (distance < closet_distance)
                {
                    closet_distance = distance;
                    target_entity = entity;
                }
            }

            if (rocket.big_miss == true)
                continue;
            
            //Canis::Log("Target found : " + std::to_string(closet_distance));
            

            auto [target_transform, target_sphere, target_health] = registry.get<Canis::TransformComponent, Canis::SphereColliderComponent, HealthComponent>(target_entity);

            // look at
            glm::quat quat_look_at = Canis::RotationBetweenVectors(
                glm::vec3(0.0f, 0.0f, 1.0f),
                glm::normalize(target_transform.position - rocket_transform.position)
            );
            glm::vec3 rot = glm::eulerAngles(quat_look_at);

            //Canis::SetTransformRotation(rocket_transform, rot);

            rocket_transform.rotation = rot;

            glm::mat4 transform = glm::mat4(1);
            transform = glm::translate(transform, rocket_transform.position);
            transform = glm::rotate(transform, rot.x, glm::vec3(1, 0, 0));
            transform = glm::rotate(transform, rot.y, glm::vec3(0, 1, 0));
            transform = glm::rotate(transform, rot.z, glm::vec3(0, 0, 1));
            rocket_transform.modelMatrix = glm::scale(transform, rocket_transform.scale);

            //Canis::Log("pos: " + glm::to_string(rocket_transform.position) + " target pos: " + glm::to_string(target_transform.position) + " rot: " + glm::to_string(rot));
            
            // collision
            glm::vec3 rocket_global_position{rocket_transform.modelMatrix * glm::vec4(bullet_sphere.center, 1.0f)}; 
            float rocket_max_radius = bullet_sphere.radius * (std::max(std::max(rocket_transform.scale.x, 
                rocket_transform.scale.y), rocket_transform.scale.z) * 0.5f);
            
            glm::vec3 global_position{target_transform.modelMatrix * glm::vec4(target_sphere.center, 1.0f)};

            float max_radius = target_sphere.radius * (std::max(std::max(target_transform.scale.x, 
                    target_transform.scale.y), target_transform.scale.z) * 0.5f);

            float distance = glm::distance(global_position, rocket_global_position);

            if (distance < rocket_max_radius + max_radius)
            {
                target_health.health -= rocket.damage;
                registry.destroy(rocket_entity);
            }
        }        
    }

private:
};