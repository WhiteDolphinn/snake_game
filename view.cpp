#include "view.hpp"
#include "Tview.hpp"
#include "Gview.hpp"
#include <termios.h>
#include <sys/ioctl.h>


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

View::~View()
{

}
