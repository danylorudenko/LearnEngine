#ifndef __INPUT_H__
#define __INPUT_H__

#include <GLFW\glfw3.h>
#include <glm\vec2.hpp>
#include "..\Util\Singletone.h"
#include <set>
#include <vector>

class InputSystem : public Singletone<InputSystem>
{
    //                               key, action
    //using KeyboardEvent = std::tuple<int, int>;
    using CommandsContainer = std::set<int>;
public:
    InputSystem                                 (GLFWwindow* window);

    InputSystem                                 (const InputSystem& rhs) = delete;
    InputSystem                                 (InputSystem&& rhs) = delete;
    InputSystem&            operator=           (const InputSystem& rhs) = delete;
    InputSystem&            operator=           (InputSystem&& rhs) = delete;

    bool                    GetKeyDown          (int glfw_code) const;
    bool                    GetKeyUp            (int glfw_code) const;
    bool                    GetKey              (int glfw_code) const;

    const glm::vec2&        GetMousePos         () const;
protected:
    // Called by GLFW to handle user input
    static void key_callback(GLFWwindow* window, int key, int scan_code, int action, int mods);

    // Called by GLFW to handle mouse position relatively to context window.
    static void mouse_pos_callback(GLFWwindow* window, double x_pos, double y_pos);

    // Called by GLFW to hadle user presses on mouse buttons.
    static void mouse_button_callback(GLFWwindow* window, int key, int action, int mods);


    GLFWwindow*             context_window_;

    CommandsContainer       holded_keys_;
    CommandsContainer       down_keys_;
    CommandsContainer       up_keys_;

    glm::vec2               mouse_position_;
};



#endif