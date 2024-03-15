#include "game.hpp"
#include <csignal>

void Model::set_name(char* buff)
{
    strcpy(game_name, buff);

    //view.draw();
    //for(int i = 0; i<100000;i++)



    //std::signal(SIGWINCH, view.draw(rabbits));
    //std::signal(SIGINT, view.bye_print());

    for(int i = 0; i < 1000; i++)
    {
        view.draw(rabbits, snakes);
        usleep(1000000/30);
        update();
    }

    //view.print_game_name(game_name);
}

void Model::generate_rabbits()
{
    srand(time(NULL));
    Rabbit rabbit;

    FILE* logfile = fopen("logfile.txt", "w");

    for(int i = 0; i < num_of_rabbits; i++)
    {   
        /*rabbit.xy.first = 10;
        rabbit.xy.second = 10;*/
        rabbit.xy.first = (rand() % (view.win_size.first-2))+2;
        rabbit.xy.second = (rand() % (view.win_size.second-2))+2;
        
        fprintf(logfile, "%d %d %d\n", i, rabbit.xy.first, rabbit.xy.second);
        rabbits.push_back(rabbit);
    }

    fclose(logfile); 
}

void Model::generate_snakes()
{
    Snake snake;
    snake.length = 4;

    snake.head.first = 20;
    snake.head.second = 12;

    coord xy1 = {20, 11};
    snake.body.push_back(xy1);

    xy1 = {20, 10};
    snake.body.push_back(xy1);

    snake.tail.first = 20;
    snake.tail.second = 9;

    snakes.push_back(snake);
}

void Model::update()
{
    for(auto snake = snakes.begin(); snake != snakes.end(); snake++)
    {
        (*snake).head.second++;
        for(auto part = (*snake).body.begin(); part != (*snake).body.end(); part++)
        {
            (*part).second++;
        }

        (*snake).tail.second++;
        
    }
}