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

#include "../Components/PlayerShipComponent.hpp"

class PlayerShipSystem
{
public:
    Canis::Camera *camera;
    Canis::InputManager *input_manager;

    PlayerShipSystem()
    {
    }

    void Init()
    {
        
    }

    void UpdateComponents(float deltaTime, entt::registry &registry)
    {
        glm::vec3 direction = glm::vec3(0.0f,0.0f,0.0f);

        const Uint8* keystate = SDL_GetKeyboardState(NULL);

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
            glm::vec3 what_dir = glm::vec3(0.0f,0.0f,direction.z);
            glm::vec3 movement_offset = (what_dir * ship.acceleration) * deltaTime;

            // add the movement offset to the ship
            float rotation_x = transform.rotation.x + (-direction.x*20.0f*deltaTime);
            float rotation_y = transform.rotation.y + (-direction.y*20.0f*deltaTime);
            if (rotation_x > 88.0f)
                rotation_x = 88.0f;
            if (rotation_x < -88.0f)
                rotation_x = -88.0f;
            Canis::SetTransformRotation(transform, glm::vec3(rotation_x,rotation_y,0.0f));
            Canis::MoveTransformPosition(transform, movement_offset);

            // add the movement offset to the ship body
            Canis::TransformComponent& ship_body_transform = registry.get<Canis::TransformComponent>(ship.ship_model);
            SetTransformPosition(ship_body_transform, transform.position);
            SetTransformRotation(ship_body_transform, transform.rotation);

            // add the movement offset to the ship glass
            Canis::TransformComponent& ship_glass_transform = registry.get<Canis::TransformComponent>(ship.ship_glass);
            SetTransformPosition(ship_glass_transform, transform.position);
            SetTransformRotation(ship_glass_transform, transform.rotation);

            // add the movement offset to the camera
            //camera->Position = ship.camera_position_offset + transform.position;
            camera->Position = glm::vec3(glm::translate(transform.modelMatrix, ship.camera_position_offset)[3]);
            camera->Rotate(-transform.rotation.y+90.0f,-transform.rotation.x);

            //camera->modelMatrix = glm::inverse(glm::rotate(glm::translate(transform.modelMatrix, ship.camera_position_offset),glm::radians(-180.0f),glm::vec3(0.0f,1.0f,0.0f)));
        }
    }

private:
};