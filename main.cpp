#include "control.hpp"
#include "game.hpp"
#include "view.hpp"

int main(const int argc, const char** argv)
{
    View* view;
    view = (argc > 1) ? (View::get(argv[1])) : (View::get("text"));

    int num_of_bots = 2;
    int num_of_rabbits = 5;

    if(argc > 2)
        num_of_bots = std::stoi(argv[2]);

    if(argc > 3)
        num_of_rabbits = std::stoi(argv[3]);

    Model model(*view, num_of_bots, num_of_rabbits);

    std::list<Control*> control_list;
    auto current_snake = model.snakes.begin();

    for(int i = 0; i < num_of_bots; i++)
        control_list.push_back(std::move(new Control(model, *(current_snake++))));

    view->mainloop();

    for(auto control_it = control_list.begin(); control_it != control_list.end(); control_it++)
        delete *control_it;

    delete view;
    
    return 0;
}
