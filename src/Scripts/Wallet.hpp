#pragma once
#include <glm/glm.hpp>
#include <string>

#include <Canis/External/entt.hpp>

#include <Canis/ECS/Components/RectTransformComponent.hpp>
#include <Canis/ECS/Components/TextComponent.hpp>

class Wallet
{
private:
    int cash = 0;
public:
    entt::registry *refRegistry;
    entt::entity walletText;

    void Init()
    {

    }

    void UpdateUI()
    {
        auto [wallet_rect, wallet_text] = refRegistry->get<Canis::RectTransformComponent, Canis::TextComponent>(walletText);
						
		*wallet_text.text = "Gold : " + std::to_string(cash);
    }

    int GetCash()
    {
        return cash;
    }

    void SetCash(int _amount)
    {
        cash = _amount;

        UpdateUI();
    }

    bool ICanAfford(int _amount)
    {
        if(0 > (cash - _amount))
        {
            return false;
        }

        return true;
    }

    bool Pay(int _amount)
    {
        if (cash <= 0)
            return false;

        cash -= _amount;

        UpdateUI();
        
        if (cash <= 0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    void Earn(int _amount)
    {
        if (cash < 0)
            return;

        cash += _amount;

        UpdateUI();
    }

};