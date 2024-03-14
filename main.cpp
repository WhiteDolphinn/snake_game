#include "control.hpp"
#include "game.hpp"
#include "view.hpp"

int main()
{
    View* view = View::get("text");

    Model model(*view);
    Control control(model);
    control.get_user_input();

    return 0;
}
