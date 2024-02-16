#include "control.h"

void Control::get_user_input()
{
    char buff[length_game_name] = "snake_def";
    //std::cin >> buff;
    model.set_name(buff);
}
