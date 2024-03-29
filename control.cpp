#include "control.hpp"
#include <functional>

void Control::get_user_input()
{
    char buff[length_game_name] = "snake_def";
    model.set_name(buff);
}

Control::Control(Model& model_, Snake& snake_)
                : model(model_), snake(snake_)
{
    auto f = std::bind(&Control::key_pressed, this, std::placeholders::_1);
    model.view.set_onkey(f);
    
    auto f2 = std::bind(&Control::timer, this);
    model.view.set_ontimes(f2);
}

void Control::key_pressed(int key)
{
    snake.direction = key;
    //model.update();
}

void Control::timer()
{
    model.update();
}
