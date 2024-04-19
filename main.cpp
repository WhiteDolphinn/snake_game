#include "control.hpp"
#include "game.hpp"
#include "view.hpp"

int main(const int argc, const char** argv)
{
    View* view;
    (argc > 1) ? (view = View::get(argv[1])) : (view = View::get("text"));

    Model model(*view);

    Control control(model, *(model.snakes.begin()));
    control.get_user_input();

    Control control_bot(model, *(model.snakes.end()));
    control_bot.get_user_input();

    view->mainloop();
    
    delete view;
    return 0;
}
