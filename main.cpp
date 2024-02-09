#include "view.h"
#include "game.h"
#include "control.h"

int main()
{
    View view;
    Model model(view);
    Control control(model);
    control.get_user_input();

    return 0;
}