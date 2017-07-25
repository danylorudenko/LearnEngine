#ifndef __INPUT_H__
#define __INPUT_H__

#include <GLFW\glfw3.h>
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
protected:
    // Called by GLFW to handle user input
    static void key_callback(GLFWwindow* window, int key, int scan_code, int action, int move);

    GLFWwindow*             context_window_;
    CommandsContainer       holded_keys_;
    CommandsContainer       down_keys_;
    CommandsContainer       up_keys_;
};



#endif