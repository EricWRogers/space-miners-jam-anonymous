#pragma once

#include <glm/glm.hpp>

#include <Canis/External/entt.hpp>

#include <Canis/ECS/Components/TransformComponent.hpp>
#include <Canis/ECS/Components/RectTransformComponent.hpp>
#include <Canis/ECS/Components/ColorComponent.hpp>
#include <Canis/ECS/Components/MeshComponent.hpp>

#include "../ECS/Systems/PlayerShipSystem.hpp"

#include "Wallet.hpp"
#include "ScoreSystem.hpp"

class HUDManager
{
private:
    bool showingHUD = false;

public:
    Canis::InputManager *inputManager;
    Canis::Window *window;
    Wallet *wallet;
    ScoreSystem *scoreSystem;
    PlayerShipSystem *playerShipSystem;

    entt::entity healthText;
    entt::entity walletText;
    entt::entity scoreText;

    entt::entity right_gun_upgrade_text;
    entt::entity left_gun_upgrade_text;

    float starting_seconds = 120.0f;
    float seconds = 0.0f;

    bool game_over = false;

    void Init()
    {
        seconds = starting_seconds;
    }

    void Update(float delta, entt::registry &registry)
    {

        if (game_over)
            return;
        
        if (showingHUD)
        {
            seconds -= delta;

            if (seconds <= 0.0f)
            {
                game_over = true;

                auto [health_transform, health_text] = registry.get<Canis::RectTransformComponent, Canis::TextComponent>(healthText);
                health_transform.active = false;
                auto [wallet_transform, wallet_text] = registry.get<Canis::RectTransformComponent, Canis::TextComponent>(walletText);
                wallet_transform.active = false;
                auto [score_transform, score_text] = registry.get<Canis::RectTransformComponent, Canis::TextComponent>(scoreText);
                (*score_text.text) = "Score : " + std::to_string(scoreSystem->GetScore()) + " there is no restart thanks for playing!";

                auto [right_gun_upgrade_transform, right_gun_upgrade_text_c] = registry.get<Canis::RectTransformComponent, Canis::TextComponent>(right_gun_upgrade_text);
                right_gun_upgrade_transform.active = false;
                auto [left_gun_upgrade_transform, left_gun_upgrade_text_c] = registry.get<Canis::RectTransformComponent, Canis::TextComponent>(left_gun_upgrade_text);
                left_gun_upgrade_transform.active = false;

                return;
            }

            auto [health_transform, health_text] = registry.get<Canis::RectTransformComponent, Canis::TextComponent>(healthText);
            (*health_text.text) = "Timer : " + std::to_string(int(seconds));

            // grey out what you can not buy
            // right
            auto [right_transform, right_color, right_text] = registry.get<Canis::RectTransformComponent, Canis::ColorComponent, Canis::TextComponent>(right_gun_upgrade_text);
            int price = 100;

            switch (playerShipSystem->gun_level)
            {
            case 0: {
                (*right_text.text) = "[1] $100 unlock gun";
                price = 100;
                break;
            }
            case 1: {
                (*right_text.text) = "[1] $150 increase fire rate";
                price = 150;
                break;
            }
            default:
                (*right_text.text) = "";
                break;
            }

            if (wallet->ICanAfford(price) || playerShipSystem->gun_level > 2)
                right_color.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
            else
                right_color.color = glm::vec4(0.384f, 0.356f, 0.356f, 1.0f);
            
            if (inputManager->isKeyPressed(SDLK_1) && wallet->ICanAfford(price))
            {
                // give player upgrade
                wallet->Pay(price);
                playerShipSystem->gun_level++;
            }
            
            // left
            auto [color_transform, left_color, left_text] = registry.get<Canis::RectTransformComponent, Canis::ColorComponent, Canis::TextComponent>(left_gun_upgrade_text);
            
            switch (playerShipSystem->center_gun_level)
            {
            case 0: {
                (*left_text.text) = "[2] $200 unlock rocket launcher";
                price = 100;
                break;
            }
            case 1: {
                (*left_text.text) = "[2] $150 increase fire rate";
                price = 150;
                break;
            }
            default:
                (*left_text.text) = "";
                break;
            }

            if (wallet->ICanAfford(price) || playerShipSystem->center_gun_level > 2)
                left_color.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
            else
                left_color.color = glm::vec4(0.384f, 0.356f, 0.356f, 1.0f);


            if (inputManager->isKeyPressed(SDLK_2) && wallet->ICanAfford(price))
            {
                // give player upgrade
                wallet->Pay(price);
                playerShipSystem->center_gun_level++;
            }
        }
    }

    void Load(entt::registry &registry)
    {
        showingHUD = true;

        healthText = registry.create();
        registry.emplace<Canis::RectTransformComponent>(healthText,
            true, // active
            glm::vec2(25.0f, window->GetScreenHeight() - 65.0f), // position
            glm::vec2(0.0f, 0.0f), // rotation
            1.0f // scale
        );
        registry.emplace<Canis::ColorComponent>(healthText,
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) // #26854c
        );
        registry.emplace<Canis::TextComponent>(healthText,
            new std::string("Timer : " + std::to_string(seconds)) // text
        );

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