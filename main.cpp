#include "control.hpp"
#include "game.hpp"
#include "view.hpp"
#include <stdio.h>

int main(const int argc, const char** argv)
{
    View* view;
    (argc > 1) ? (view = View::get(argv[1])) : (view = View::get("text"));

    Model model(*view);

    auto current_snake = model.snakes.begin();
    Control control(model, *current_snake);
    control.get_user_input();  
    current_snake++;

    Control control_bot(model, *(current_snake));
    control_bot.get_user_input();

    view->mainloop();
    
    delete view;
    return 0;
}
