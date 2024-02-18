#include "view.hpp"
#include "game.hpp"
#include "control.hpp"

int main()
{
    View* view = View::get("text");

    Model model(*view);
    Control control(model);
    control.get_user_input();

    return 0;
}
