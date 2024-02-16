#include "view.h"
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

void TView::print_game_name(std::string game_name)
{
    std::cout << "Game: " << game_name;
}

void GView::print_game_name(std::string game_name)
{
    std::cout << "(GView)Game: " << game_name << std::endl  ;
}


View::~View()
{

}

void TView::cls()
{
    std::cout << "\e[H\e[J";

}


void TView::setcolor(int brightness, int color)
{
    std::cout << "\e[" << brightness << ";" << color << "m";
}


void TView::gotoxy(int x, int y)
{
    std::cout << "\e[" << x << ";" << y << "H";
}

void TView::draw()
{
    cls();
    setcolor(0, 34);

    struct winsize wins;
    ioctl(0, TIOCGWINSZ, &wins);

    int win_xsize = wins.ws_row;
    int win_ysize = wins.ws_col;

    gotoxy(win_xsize/2, win_ysize/2);

    print_game_name("snake");
    std::cout << std::flush;

    gotoxy(0, 0); //левая вертикальная стена
    for(int i = 0; i < win_ysize; i++)
    {
        std::cout << '#';
        gotoxy(i+1, 0);
    }

    gotoxy(win_xsize, 0);  // правая вертикальная стена
    for(int i = 0; i < win_ysize; i++)
    {
        std::cout << '#';
        gotoxy(i+1, win_ysize);
    }

    gotoxy(0, 0);  // правая вертикальная стена
    for(int i = 0; i < win_xsize; i++)
    {
        std::cout << '#';
        gotoxy(0, i+1);
    }


    gotoxy(win_xsize, win_ysize);
    //std::cout << std::endl;
}

void GView::draw()
{

    print_game_name("grsnake");
}
