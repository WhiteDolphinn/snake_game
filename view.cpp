#include "view.hpp"
#include "Tview.hpp"
#include "Gview.hpp"
#include <functional>
#include <sys/ioctl.h>
#include <unistd.h>


View* View::view = NULL;
View* View::get(std::string s)
{
    if(view)
        return view;

    if(s == "text")
        view = new TView;
    else
        view = new GView;

    return view;
}

View::View()
{
    struct winsize wins;
    ioctl(0, TIOCGWINSZ, &wins);
    win_size.first = wins.ws_row;
    win_size.second = wins.ws_col;
}

void View::set_onkey(keyfn f)
{
    onkeys.push_back(f);
}

void View::set_ontimes(timefn f)
{
    ontimes.push_back(f);
}

void View::set_draw_without_update(drawfn f)
{
    draw_without_update = f;
}

View::~View()
{
    
}

