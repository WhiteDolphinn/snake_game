#include "control.hpp"
#include <functional>

void Control::get_user_input()
{
    char buff[length_game_name] = "snake_def";
    //std::cin >> buff;

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
    /*switch(key)
    {
        case UP:
        auto first_snake = model.snakes.begin();
        (*first_snake).direction = UP;
        break;

        case DOWN:
        auto first_snake = model.snakes.begin();
        (*first_snake).direction = DOWN;
        break;

        case LEFT:
        auto first_snake = model.snakes.begin();
        (*first_snake).direction = LEFT;
        break;

        case RIGHT:
        auto first_snake = model.snakes.begin();
        (*first_snake).direction = RIGHT;
        break;
    }*/

    //auto first_snake = model.snakes.begin();
    snake.direction = key;
    model.update();
}

void Control::timer()
{
    model.update();
}
