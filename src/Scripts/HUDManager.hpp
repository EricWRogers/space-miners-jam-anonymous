#pragma once

#include <glm/glm.hpp>

#include <Canis/External/entt.hpp>

#include <Canis/ECS/Components/TransformComponent.hpp>
#include <Canis/ECS/Components/RectTransformComponent.hpp>
#include <Canis/ECS/Components/ColorComponent.hpp>
#include <Canis/ECS/Components/MeshComponent.hpp>

#include "Wallet.hpp"

class HUDManager
{
private:
    bool showingHUD = false;

public:
    Canis::InputManager *inputManager;
    Canis::Window *window;
    Wallet *wallet;

    entt::entity healthText;
    entt::entity walletText;
    entt::entity scoreText;

    entt::entity right_gun_upgrade_text;
    entt::entity left_gun_upgrade_text;

    void Update(float delta, entt::registry &registry)
    {
        if (showingHUD)
        {

            // grey out what you can not buy
            auto [right_transform, right_color] = registry.get<Canis::RectTransformComponent, Canis::ColorComponent>(right_gun_upgrade_text);
            if (wallet->ICanAfford(100))
                right_color.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
            else
                right_color.color = glm::vec4(0.384f, 0.356f, 0.356f, 1.0f);
            
            auto [color_transform, left_color] = registry.get<Canis::RectTransformComponent, Canis::ColorComponent>(left_gun_upgrade_text);
            if (wallet->ICanAfford(100))
                left_color.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
            else
                left_color.color = glm::vec4(0.384f, 0.356f, 0.356f, 1.0f);

            // right
            if (inputManager->isKeyPressed(SDLK_1) && wallet->ICanAfford(100))
            {
                // give player upgrade
            }

            // left
            if (inputManager->isKeyPressed(SDLK_2) && wallet->ICanAfford(100))
            {
                // give player upgrade
            }
        }
    }

    void Load(entt::registry &registry)
    {
        showingHUD = true;

        scoreText = registry.create();
        registry.emplace<Canis::RectTransformComponent>(scoreText,
            true, // active
            glm::vec2(25.0f, window->GetScreenHeight() - 130.0f), // position
            glm::vec2(0.0f, 0.0f), // rotation
            1.0f // scale
        );
        registry.emplace<Canis::ColorComponent>(scoreText,
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) // #26854c
        );
        registry.emplace<Canis::TextComponent>(scoreText,
            new std::string("Score : 0") // text
        );

        walletText = registry.create();
        registry.emplace<Canis::RectTransformComponent>(walletText,
            true, // active
            glm::vec2(25.0f, window->GetScreenHeight() - 195.0f), // position
            glm::vec2(0.0f, 0.0f), // rotation
            1.0f // scale
        );
        registry.emplace<Canis::ColorComponent>(walletText,
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) // #26854c
        );
        registry.emplace<Canis::TextComponent>(walletText,
            new std::string("Gold : 0") // text
        );

        right_gun_upgrade_text = registry.create();
        registry.emplace<Canis::RectTransformComponent>(right_gun_upgrade_text,
            true, // active
            glm::vec2(25.0f, 120.0f), // position
            glm::vec2(0.0f, 0.0f), // rotation
            0.5f // scale
        );
        registry.emplace<Canis::ColorComponent>(right_gun_upgrade_text,
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) // #26854c
        );
        registry.emplace<Canis::TextComponent>(right_gun_upgrade_text,
            new std::string("[1] $100 increase fire rate") // text
        );

        left_gun_upgrade_text = registry.create();
        registry.emplace<Canis::RectTransformComponent>(left_gun_upgrade_text,
            true, // active
            glm::vec2(25.0f, 90.0f), // position
            glm::vec2(0.0f, 0.0f), // rotation
            0.5f // scale
        );
        registry.emplace<Canis::ColorComponent>(left_gun_upgrade_text,
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) // #26854c
        );
        registry.emplace<Canis::TextComponent>(left_gun_upgrade_text,
            new std::string("[2] $100 increase fire rate") // text
        );
    }
};