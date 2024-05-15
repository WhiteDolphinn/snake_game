#include "control.hpp"
#include "game.hpp"
#include "view.hpp"

int main(const int argc, const char** argv)
{
    View* view;
    view = (argc > 1) ? (View::get(argv[1])) : (View::get("text"));

    int num_of_bots = 2;
    int num_of_rabbits = 5;
    bool is_human = false;

    if(argc > 2)
        num_of_bots = std::stoi(argv[2]);

    if(argc > 3)
        num_of_rabbits = std::stoi(argv[3]);

    if(argc > 4 && argv[4][0] == 'h')
    {
        is_human = true;
        
    }

    Model model(*view, num_of_bots, num_of_rabbits, is_human);

    std::list<Control*> control_list;
    auto current_snake = model.snakes.begin();

    for(int i = 0; i < num_of_bots; i++)
        control_list.push_back(std::move(new Control(model, *(current_snake++))));

    if(is_human)
        control_list.push_back(std::move(new Control(model, *(current_snake++))));


    view->mainloop();

    for(auto control_it = control_list.begin(); control_it != control_list.end(); control_it++)
        delete *control_it;

    delete view;
    
    return 0;
}
