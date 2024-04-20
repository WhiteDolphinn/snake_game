#include "game.hpp"
#include <csignal>

void Model::set_name(char* buff)
{
    strcpy(game_name, buff);
}

void Model::generate_rabbits()
{
    srand(time(NULL));
    Rabbit rabbit;

    //FILE* logfile = fopen("logfile.txt", "w");

    for(int i = 0; i < num_of_rabbits; i++)
    {   
        rabbit.xy.first = (rand() % (view.win_size.first-2))+2;
        rabbit.xy.second = (rand() % (view.win_size.second-2))+2;
        
        //fprintf(logfile, "%d %d %d\n", i, rabbit.xy.first, rabbit.xy.second);
        rabbits.push_back(rabbit);
    }

    //fclose(logfile); 
}

void Model::generate_snakes()
{
    Snake snake;
    snake.length = 2;
    snake.direction = RIGHT;
    snake.is_controlled = true;

    snake.head = {3, 2};
    snake.tail = {3, 1};

    snakes.push_back(snake);

    Snake snake2;
    snake2.length = 2;
    snake2.direction = RIGHT;
    snake2.is_controlled = false;
    
    snake2.head = {5, 5};
    snake2.tail = {4, 5};

    snakes.push_back(snake2);

}

void Model::update()
{
    for(auto snake = snakes.begin(); snake != snakes.end(); snake++)
    {
        for(auto rabbit = rabbits.begin(); rabbit != rabbits.end(); rabbit++)
            if((*snake).head == (*rabbit).xy)
            {
                coord buf_coord = {0, 0};
                (*snake).length++;
                (*snake).body.push_back(buf_coord);

                (*rabbit).xy.first = (rand() % (view.win_size.first-2))+2;
                (*rabbit).xy.second = (rand() % (view.win_size.second-2))+2;
            }

        update_snake(snake);
    }


    view.draw(rabbits, snakes);
}

void Model::update_snake(std::list<Snake>::iterator snake)
{
    
    int prev_x = (*snake).head.first;
    int prev_y = (*snake).head.second;
    int prev_2x = 0;
    int prev_2y = 0;

    switch ((*snake).direction)
    {
    case UP:
        (*snake).head.first--;
        break;
    
    case DOWN:
        (*snake).head.first++;
        break;

    case LEFT:
        (*snake).head.second--;
        break;

    case RIGHT:
        (*snake).head.second++;
        break;
    
    default:
        break;
    }

    for(auto part = (*snake).body.begin(); part != (*snake).body.end(); part++)
    {
        prev_2x = (*part).first;
        prev_2y = (*part).second;

        (*part).first = prev_x;
        (*part).second = prev_y;

        prev_x = prev_2x;
        prev_y = prev_2y;
    }
    
    (*snake).tail.first = prev_x;
    (*snake).tail.second = prev_y;
}