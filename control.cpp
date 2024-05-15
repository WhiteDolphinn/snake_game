#include "control.hpp"
#include <functional>
#include <queue>

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
        if(snake.is_stupid_bot == true)
            stupid_bot();
        else
            smart_bot();
    }
}

void Control::draw_without_update()
{
    model.view.draw(model.rabbits, model.snakes);
}

void Control::stupid_bot()
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
}

void Control::smart_bot()
{
    if(snake.head == coord{0, 0})
        return;

    model.set_field();

    std::vector<coord> gen;
    gen.push_back(snake.head);

    coord rabbit(-1, -1);
    rabbit = next_generation(gen);

    if(rabbit != coord{0, 0})
    {
        coord last_coord = {};
        for(coord current_coord = rabbit; current_coord != snake.head && current_coord != coord{0, 0};)
        {
            switch(model.field[current_coord.first][current_coord.second])
            {
                case RIGHT+1:
                    last_coord = current_coord;
                    current_coord.first += 1;
                    break;

                case LEFT+1:
                    last_coord = current_coord;
                    current_coord.first -= 1;
                    break;

                case DOWN+1:
                    last_coord = current_coord;
                    current_coord.second += 1;
                    break;

                case UP+1:
                    last_coord = current_coord;
                    current_coord.second -= 1;
                    break;

                default: 
                snake.direction = (snake.direction + 1) % 4;
                break;
            }
        }
        
        if(last_coord.first - snake.head.first == 1)
            snake.direction = DOWN;

        if(last_coord.first - snake.head.first == -1)
            snake.direction = UP;

        if(last_coord.second - snake.head.second == 1)
            snake.direction = RIGHT;

        if(last_coord.second - snake.head.second == -1)
            snake.direction = LEFT;

    }

}

coord Control::next_generation(std::vector<coord>& generation)
{
    if(generation.empty() || snake.head == coord{0, 0})
        return {0, 0};

    std::vector<coord> generation2;

    for(const auto& entity: generation)
    {
        if(in_bounds(entity.first-1, entity.second) && model.field[entity.first-1][entity.second] == 0)
        {
            model.field[entity.first-1][entity.second] = RIGHT+1;
            generation2.push_back(coord(entity.first-1, entity.second));
        }
        if(in_bounds(entity.first+1, entity.second) && model.field[entity.first+1][entity.second] == 0)
        {
            model.field[entity.first+1][entity.second] = LEFT+1;
            generation2.push_back(coord(entity.first+1, entity.second));
        }
        if(in_bounds(entity.first, entity.second-1) && model.field[entity.first][entity.second-1] == 0)
        {
            model.field[entity.first][entity.second-1] = DOWN+1;
            generation2.push_back(coord(entity.first, entity.second-1));
        }
        if(in_bounds(entity.first, entity.second+1) && model.field[entity.first][entity.second+1] == 0)
        {
            model.field[entity.first][entity.second+1] = UP+1;
            generation2.push_back(coord(entity.first, entity.second+1));
        }

        if(in_bounds(entity.first-1, entity.second) && model.field[entity.first-1][entity.second] == -1)
        {
            model.field[entity.first-1][entity.second] = RIGHT+1;
            return {entity.first-1, entity.second};
        }
        
        if(in_bounds(entity.first+1, entity.second) && model.field[entity.first+1][entity.second] == -1)
        {
            model.field[entity.first+1][entity.second] = LEFT+1;
            return {entity.first+1, entity.second};
        }

        if(in_bounds(entity.first, entity.second-1) && model.field[entity.first][entity.second-1] == -1)
        {
            model.field[entity.first][entity.second-1] = DOWN+1;
            return {entity.first, entity.second-1};
        }

        if(in_bounds(entity.first, entity.second+1) && model.field[entity.first][entity.second+1] == -1)
        {
            model.field[entity.first][entity.second+1] = UP+1;
            return {entity.first, entity.second+1};
        }
    }

    return next_generation(generation2);

}

bool Control::in_bounds(int len1, int len2)
{
    return len1>=0 && len1<=model.view.win_size.first && len2>=0 && len2<=model.view.win_size.second;
}
