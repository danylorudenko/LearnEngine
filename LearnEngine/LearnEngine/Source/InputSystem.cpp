#include "..\Include\Input\InputSystem.h"
#include <iostream>
#include <algorithm>

void InputSystem::key_callback(GLFWwindow* window, int key, int scan_code, int action, int mode)
{
    auto& system = Instance();

    system.down_keys_.clear();
    system.up_keys_.clear();

    if (action == GLFW_PRESS) {
        system.holded_keys_.insert(key);
        system.down_keys_.insert(key);
    }

    if (action == GLFW_RELEASE) {
        system.holded_keys_.erase(key);
        system.up_keys_.insert(key);
    }
}

void InputSystem::mouse_pos_callback(GLFWwindow* window, double x_pos, double y_pos)
{
    Instance().mouse_position_ = glm::vec2(x_pos, y_pos);
}

void InputSystem::mouse_button_callback(GLFWwindow* window, int key, int action, int mods)
{
    auto& system = Instance();

    if (action == GLFW_PRESS) {
        system.holded_keys_.insert(key);
        system.down_keys_.insert(key);
    }

    if (action == GLFW_RELEASE) {
        system.holded_keys_.erase(key);
        system.up_keys_.insert(key);
    }
}



InputSystem::InputSystem(GLFWwindow* window)
{
    context_window_ = window;
    glfwSetKeyCallback(window, InputSystem::key_callback);
    glfwSetCursorPosCallback(window, InputSystem::mouse_pos_callback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
}

bool InputSystem::GetKeyDown(int glfw_code) const
{
    return down_keys_.find(glfw_code) != down_keys_.end();
}

bool InputSystem::GetKeyUp(int glfw_code) const
{
    return up_keys_.find(glfw_code) != up_keys_.end();
}

bool InputSystem::GetKey(int glfw_code) const
{
    return holded_keys_.find(glfw_code) != holded_keys_.end();
}

const glm::vec2& InputSystem::GetMousePos() const
{
    return mouse_position_;
}
