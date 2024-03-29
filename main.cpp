#include "control.hpp"
#include "game.hpp"
#include "view.hpp"

int main()
{
    View* view = View::get("text");

    Model model(*view);
    Control control(model, *(model.snakes.begin()));
    control.get_user_input();
    view->mainloop();

    return 0;
}
