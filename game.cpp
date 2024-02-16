#include "game.h"

void Model::set_name(char* buff)
{
    strcpy(game_name, buff);
    view.draw();
    //view.print_game_name(game_name);
}
