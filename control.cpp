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

    auto f3 = std::bind(&Control::draw_without_update, this);
    model.view.set_draw_without_update(f3);

}

void Control::key_pressed(int key)
{
    if(snake.is_controlled)
        snake.direction = key;
}

void Control::timer()
{
    if(snake.is_controlled == false)
    {

        int min_distance = 10000;
        Rabbit min_rabbit;

        int distance = 0;

        for(const auto& rabbit: model.rabbits)
        {
            distance = snake.head.dist(rabbit.xy);

            if(distance < min_distance)
            {
                min_distance = distance;
                min_rabbit = rabbit;
            }
        }

        /*std::cout << snake.head.first << " : " << snake.head.second << "\t";
        std::cout << snake.direction << "\t";
        std::cout << snake.head.first << " : " << snake.head.second << "\t";
        std::cout << snake.direction << "\t";*/

        if(snake.head.first != min_rabbit.xy.first)
        {
            if(snake.head.first < min_rabbit.xy.first)
            {
                if(snake.direction != UP)
                    snake.direction = DOWN;
                else
                    snake.direction = RIGHT;
            }
            else
            {
                if(snake.direction != DOWN)
                    snake.direction = UP;
                else 
                    snake.direction = LEFT;
            }
        }
        else
        {
            if(snake.head.second != min_rabbit.xy.second)
            {
                if(snake.head.second < min_rabbit.xy.second)
                {
                    if(snake.direction != LEFT)
                        snake.direction = RIGHT; 
                    else
                        snake.direction = DOWN;
                }
                else
                {
                    if(snake.direction != RIGHT)
                        snake.direction = LEFT;
                    else
                        snake.direction = UP;
                }
            }
        }

        //snake.direction = (min_distance % 4) + 1;

        //std::cout << snake.direction << std::endl;
    }

    if(snake.is_controlled)  
        model.update();
}

void Control::draw_without_update()
{
    model.view.draw(model.rabbits, model.snakes);
}
