#include "game.hpp"

void Model::set_name(char* buff)
{
    strcpy(game_name, buff);

    //view.draw();
    view.draw(rabbits);
    //view.print_game_name(game_name);
}
