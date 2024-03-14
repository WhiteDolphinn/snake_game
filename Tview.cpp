#include "Tview.hpp"
#include <termios.h>
#include <sys/ioctl.h>

void TView::cls()
{
    std::cout << "\e[H\e[J";

}

void TView::draw()
{
    cls();
    setcolor(0, 34);

    struct winsize wins;
    ioctl(0, TIOCGWINSZ, &wins);

    int win_xsize = wins.ws_row;
    int win_ysize = wins.ws_col;

    draw_wall('#', 0, 0, win_xsize, 0);
    draw_wall('#', 0, win_ysize, win_xsize, win_ysize);
    draw_wall('#', 0, 0, 0, win_ysize);
    draw_wall('#', win_xsize, 0, win_xsize, win_ysize);

    gotoxy(0, win_ysize/2);
    print_game_name("snake");
    std::cout << std::flush;

    gotoxy(win_xsize, win_ysize);
    std::cout << std::flush;
}

void TView::draw(std::list<Rabbit>& rabbits)
{
    draw();

    for(const auto& rabbit: rabbits)
        draw_rabbit(rabbit);

    struct winsize wins;
    ioctl(0, TIOCGWINSZ, &wins);
    
    int win_xsize = wins.ws_row;
    int win_ysize = wins.ws_col;


    gotoxy(win_xsize, win_ysize);
    std::cout << std::flush;

    /*for(auto it = rabbits.begin(); it != rabbits.end(); ++it)
    {
        std::cout << (*it)->xy.first << (*it)->xy.second;
        draw_rabbit(*it);
    }*/
        
}

void TView::draw_wall(char symbol, int start_x, int start_y, int end_x, int end_y)
{
    gotoxy(0, 0);

    if(start_x == end_x) // horizontal wall
    {
        for(int i = start_y; i < end_y; i++)
        {
            std::cout << symbol;
            gotoxy(start_x, i+1);
        }
    }

    if(start_y == end_y) //vertical wall
    {
        for(int i = start_x; i < end_x; i++)
        {
            std::cout << symbol;
            gotoxy(i+1, start_y);
        }
    }
}

void TView::setcolor(int brightness, int color)
{
    std::cout << "\e[" << brightness << ";" << color << "m";
}


void TView::gotoxy(int x, int y)
{
    std::cout << "\e[" << x << ";" << y << "H";
}

void TView::print_game_name(std::string game_name)
{
    std::cout << "Game: " << game_name;
}

void TView::draw_rabbit(const Rabbit& rabbit)
{
    gotoxy(rabbit.xy.first, rabbit.xy.second);
    std::cout << "r";
    //gotoxy(20, 20);
    //std::cout << rabbit.xy.first << " , " << rabbit.xy.second;
}

void TView::draw_snake(const Snake& snake)
{
    return;
}
