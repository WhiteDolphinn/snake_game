#include "control.hpp"
#include "game.hpp"
#include "view.hpp"
//#include <string>

#define CONTROL(NUMBER)\
    Control control_bot#NUMBER (model, *(current_snake++))

int main(const int argc, const char** argv)
{
    View* view;
    (argc > 1) ? (view = View::get(argv[1])) : (view = View::get("text"));

    int num_of_bots = 2;
    int num_of_rabbits = 5;

    if(argc > 2)
        num_of_bots = std::stoi(argv[2]);

    if(argc > 3)
        num_of_rabbits = std::stoi(argv[3]);

    Model model(*view, num_of_bots, num_of_rabbits);

    std::list<Control*> control_list;
   // auto current_control = control_list.begin();
    auto current_snake = model.snakes.begin();

    /*Control control(model, *(current_snake++));
    Control control2(model, *(current_snake++));
    Control control3(model, *(current_snake++));*/

    for(int i = 0; i < num_of_bots; i++)
    {
        //CONTROL(i);
        control_list.push_back(std::move(new Control(model, *(current_snake++))));
        /*Control control(model, *(current_snake++));
        control_list.push_back(control);
        (*current_control)();

        current_control++;*/

    }

    /*auto current_snake = model.snakes.begin();
    Control control(model, *(current_snake++));

    Control control_bot(model, *(current_snake++));
    
    Control control_bot2(model, *(current_snake++));*/


    view->mainloop();

    for(auto control_it = control_list.begin(); control_it != control_list.end(); control_it++)
        delete *(control_it);

    delete view;
    
    return 0;
}
