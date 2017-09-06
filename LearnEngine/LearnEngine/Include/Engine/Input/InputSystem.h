#ifndef __INPUT_H__
#define __INPUT_H__

#include <set>
#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\vec2.hpp>

#include <Engine\Util\ConstructionAttorneyTemplate.h>

// System for interaction with user keyboard/mouse input.
// Independently of user-code request, holds the state of pressed/holded/unpressed keys/mouse_pos/etc.
class InputSystem : public ControlledSingleton<InputSystem>
{
public:
    using ConstructionAttorney                  = SingletonConstructionAttorneyTemplate<InputSystem>;
    friend class ConstructionAttorney;
    
protected:
    //                               key, action
    //using KeyboardEvent = std::tuple<int, int>;
    using CommandsContainer = std::set<int>;
public:
    
    InputSystem                                 (const InputSystem& rhs) = delete;
    InputSystem                                 (InputSystem&& rhs) = delete;
    InputSystem&            operator=           (const InputSystem& rhs) = delete;
    InputSystem&            operator=           (InputSystem&& rhs) = delete;

    void                    ResetFrameData      ();

    // Check if key is was pressed down after the last system iteration (frame).
    bool                    GetKeyDown          (int glfw_code) const;

    // Check if key was released after the last system iteration (frame)
    bool                    GetKeyUp            (int glfw_code) const;

    // Check if key is being pressed after any previous iterations.
    bool                    GetKey              (int glfw_code) const;

    void                    EnableCursor        () const;
    
    void                    DisableCursor       () const;

    // Get mouse position in pixels from the top-left corner of the screen.
    const glm::vec2&        GetMousePos         () const;

    const glm::vec2&        GetMouseDelta       () const;


protected:
    InputSystem                                 (GLFWwindow* window);

    glm::vec2               ComputeMouseDelta   (glm::vec2& new_pos);

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
    glm::vec2               mouse_delta_;
};

#endif