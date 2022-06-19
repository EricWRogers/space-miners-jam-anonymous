#pragma once
#include <glm/glm.hpp>
#include <string>

#include <Canis/External/entt.hpp>

#include <Canis/ECS/Components/RectTransformComponent.hpp>
#include <Canis/ECS/Components/TextComponent.hpp>

class ScoreSystem
{
private:
    int Score = 0;
    int Multiplier = 1;

    int cash = 200;
public:
    entt::registry *refRegistry;
    entt::entity scoreText;

    void UpdateUI()
    {
        auto [score_rect, score_text] = refRegistry->get<Canis::RectTransformComponent, Canis::TextComponent>(scoreText);
						
		*score_text.text = "Score : " + std::to_string(Score);
    }

    int GetScore()
    {
        return Score;
    }

    int GetMultiplier()
    {
        return Multiplier;
    }

    void ClearScore()
    {
        Score = 0;
        Multiplier = 1;

        UpdateUI();
    }

    void AddPoints(int _amount) //, glm::vec3 _location)
    {
        Score += (_amount * Multiplier);

        UpdateUI();

        //EmitSignal(nameof(ScoreUpdated), Score, (_amount * Multiplier));
    }

};