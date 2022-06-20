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

#include "../Components/BulletComponent.hpp"
#include "../Components/PlayerShipComponent.hpp"
#include "../Components/RocketComponent.hpp"

class PlayerShipSystem
{
public:
    Canis::Camera *camera;
    Canis::InputManager *input_manager;

    unsigned int bulletVAO;
    int bulletSize;

    unsigned int gun_level = 0;
    unsigned int center_gun_level = 0;

    PlayerShipSystem()
    {
    }

    void Init()
    {
    }

    void Fire(Canis::TransformComponent transform, entt::registry &registry, unsigned int level)
    {
        float fire_speed = 150.0f;

        if (level == 3)
        {
            fire_speed = 250.0f;
        }

        entt::entity bullet_entity = registry.create();
        registry.emplace<Canis::TransformComponent>(bullet_entity,
                                                    transform);
        registry.emplace<Canis::ColorComponent>(bullet_entity,
                                                glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
        registry.emplace<Canis::MeshComponent>(bullet_entity,
                                               bulletVAO,
                                               bulletSize);
        registry.emplace<Canis::SphereColliderComponent>(bullet_entity,
                                                         glm::vec3(0.0f),
                                                         1.5f);
        registry.emplace<BulletComponent>(bullet_entity,
                                          fire_speed,
                                          1.0f,
                                          false);
    }

    void FireRocket(Canis::TransformComponent transform, entt::registry &registry, unsigned int level)
    {
        float fire_speed = 50.0f;

        if (level > 1)
            fire_speed = 150.0f;

        entt::entity rocket_entity = registry.create();
        registry.emplace<Canis::TransformComponent>(rocket_entity,
                                                    transform);
        registry.emplace<Canis::ColorComponent>(rocket_entity,
                                                glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        registry.emplace<Canis::MeshComponent>(rocket_entity,
                                               bulletVAO,
                                               bulletSize);
        registry.emplace<Canis::SphereColliderComponent>(rocket_entity,
                                                         glm::vec3(0.0f),
                                                         1.5f);
        registry.emplace<RocketComponent>(rocket_entity,
                                          5,
                                          fire_speed,
                                          5.0f,
                                          false);
    }

    void UpdateComponents(float deltaTime, entt::registry &registry)
    {
        glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);

        const Uint8 *keystate = SDL_GetKeyboardState(NULL);

        if (keystate[SDL_SCANCODE_SPACE])
            direction.z = 1;
        if (keystate[SDL_SCANCODE_W])
            direction.x = 1;
        if (keystate[SDL_SCANCODE_S])
            direction.x = -1;
        if (keystate[SDL_SCANCODE_A])
            direction.y = -1;
        if (keystate[SDL_SCANCODE_D])
            direction.y = 1;

        // movement offset
        auto view = registry.view<Canis::TransformComponent, PlayerShipComponent>();

        for (auto [entity, transform, ship] : view.each())
        {
            glm::vec3 what_dir = glm::vec3(0.0f, 0.0f, direction.z);
            glm::vec3 movement_offset = (what_dir * ship.acceleration) * deltaTime;

            // add the movement offset to the ship
            float rotation_x = transform.rotation.x + (-direction.x * 20.0f * deltaTime);
            float rotation_y = transform.rotation.y + (-direction.y * 20.0f * deltaTime);
            if (rotation_x > 88.0f)
                rotation_x = 88.0f;
            if (rotation_x < -88.0f)
                rotation_x = -88.0f;
            Canis::SetTransformRotation(transform, glm::vec3(rotation_x, rotation_y, 0.0f));
            Canis::MoveTransformPosition(transform, movement_offset);

            // add the movement offset to the ship body
            Canis::TransformComponent &ship_body_transform = registry.get<Canis::TransformComponent>(ship.ship_model);
            SetTransformPosition(ship_body_transform, transform.position);
            SetTransformRotation(ship_body_transform, transform.rotation);

            // add the movement offset to the ship glass
            Canis::TransformComponent &ship_glass_transform = registry.get<Canis::TransformComponent>(ship.ship_glass);
            SetTransformPosition(ship_glass_transform, transform.position);
            SetTransformRotation(ship_glass_transform, transform.rotation);

            // add the movement offset to the camera
            // camera->Position = ship.camera_position_offset + transform.position;
            camera->Position = glm::vec3(glm::translate(transform.modelMatrix, ship.camera_position_offset)[3]);
            camera->Rotate(-transform.rotation.y + 90.0f, -transform.rotation.x);

            // shoot
            ship.right_gun_cool_timer -= deltaTime;
            ship.left_gun_cool_timer -= deltaTime;
            ship.center_gun_cool_timer -= deltaTime;
            if (ship.right_gun_cool_timer < 0.0f)
                ship.right_gun_cool_timer = 0.0f;
            if (ship.left_gun_cool_timer < 0.0f)
                ship.left_gun_cool_timer = 0.0f;
            if (ship.center_gun_cool_timer < 0.0f)
                ship.center_gun_cool_timer = 0.0f;

            if (keystate[SDL_SCANCODE_RETURN])
            {
                if (ship.left_gun_cool_timer == 0.0f)
                {
                    ship.left_gun_cool_timer = ship.cool_down_time;
                    if (gun_level > 1)
                        ship.left_gun_cool_timer /= 2.0f;

                    // fire left
                    if (gun_level > 0)
                    {
                        Canis::TransformComponent left_gun_transform = transform;
                        left_gun_transform.modelMatrix = glm::translate(
                            left_gun_transform.modelMatrix,
                            ship.left_gun_position);
                        left_gun_transform.scale = glm::vec3(0.05f, 0.05f, 0.1f);
                        left_gun_transform.modelMatrix = glm::scale(left_gun_transform.modelMatrix, glm::vec3(0.1f));
                        left_gun_transform.isDirty = true;
                        Fire(left_gun_transform, registry, gun_level);
                    }
                }

                if (ship.right_gun_cool_timer == 0.0f)
                {
                    ship.right_gun_cool_timer = ship.cool_down_time;

                    if (gun_level > 1)
                        ship.right_gun_cool_timer /= 2.0f;

                    // fire right
                    if (true)
                    {
                        Canis::TransformComponent right_gun_transform = transform;
                        right_gun_transform.modelMatrix = glm::translate(
                            right_gun_transform.modelMatrix,
                            ship.right_gun_position);
                        right_gun_transform.scale = glm::vec3(0.05f, 0.05f, 0.1f);
                        right_gun_transform.modelMatrix = glm::scale(right_gun_transform.modelMatrix, glm::vec3(0.1f));
                        right_gun_transform.isDirty = true;
                        Fire(right_gun_transform, registry, gun_level);
                    }
                }

                if (ship.center_gun_cool_timer == 0.0f)
                {
                    ship.center_gun_cool_timer = ship.cool_down_time;

                    if (center_gun_level > 1)
                        ship.center_gun_cool_timer /= 2.0f;

                    // fire right
                    if (center_gun_level > 0)
                    {
                        Canis::TransformComponent center_gun_transform = transform;
                        center_gun_transform.modelMatrix = glm::translate(
                            center_gun_transform.modelMatrix,
                            ship.center_gun_position);
                        center_gun_transform.scale = glm::vec3(0.05f, 0.05f, 0.2f);
                        center_gun_transform.modelMatrix = glm::scale(center_gun_transform.modelMatrix, glm::vec3(0.1f));
                        center_gun_transform.isDirty = true;
                        FireRocket(center_gun_transform, registry, center_gun_level);
                    }
                }
            }
        }
    }

private:
};