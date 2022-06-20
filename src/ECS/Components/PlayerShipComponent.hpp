#pragma once
#include <glm/glm.hpp>

#include <Canis/External/entt.hpp>


struct PlayerShipComponent
{
    entt::entity ship_model;
    entt::entity ship_glass;

    glm::vec3 camera_position_offset;
    glm::vec3 right_gun_position;
    glm::vec3 left_gun_position;
    glm::vec3 center_gun_position;

    float acceleration;
    glm::vec2 velocity;
    glm::vec2 max_velocity;
    float breaking_acceleration;

    float cool_down_time;
    float right_gun_cool_timer;
    float left_gun_cool_timer;
    float center_gun_cool_timer;
};