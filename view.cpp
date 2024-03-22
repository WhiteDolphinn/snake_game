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


    struct termios term = {};
    int a = tcgetattr(0, &term);
    old_term = term;

    term.c_lflag &= ~ECHO;
    term.c_lflag &= ~ICANON;

    a = tcsetattr(0, TCSANOW, &term);

}

View::~View()
{
    int a = tcsetattr(0, TCSANOW, &old_term);
}

void View::mainloop()
{
     
}

void View::set_onkey(keyfn f)
{
    onkeys.push_back(f);
}


