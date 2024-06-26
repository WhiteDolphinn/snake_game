#include "Tview.hpp"
#include <termios.h>
#include <sys/ioctl.h>
#include <poll.h>
#include <unistd.h>
#include <chrono>

const int BUFSIZE = 10;

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

    win_size.first = wins.ws_row;
    win_size.second = wins.ws_col;

    draw_wall('#', 0, 0, win_size.first, 0);
    draw_wall('#', 0, win_size.second, win_size.first, win_size.second);
    draw_wall('#', 0, 0, 0, win_size.second);
    draw_wall('#', win_size.first, 0, win_size.first, win_size.second);


    gotoxy(1, win_size.second/2);
    print_game_name("snake");
    std::cout << std::flush;

    gotoxy(win_size.first, win_size.second);
    std::cout << std::flush;
}

void TView::draw(std::list<Rabbit>& rabbits, std::list<Snake>& snakes)
{
    draw();

    for(const auto& rabbit: rabbits)
        draw_rabbit(rabbit);

    for(const auto& snake: snakes)
        draw_snake(snake);

    int snake_number = 0;
    gotoxy(win_size.first, 1);
    for(const auto& snake: snakes)
    {
        if(snake.is_controlled == true)
            std::cout << "snake(human)" << std::to_string(snake_number) << ":" << std::to_string(snake.length) << "##";
        else
            std::cout << "snake(bot)" <<  std::to_string(snake_number) <<  ":" << std::to_string(snake.length) << "##";
        snake_number++;
    }

    gotoxy(win_size.first, win_size.second);
    std::cout << std::flush;
        
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
}

void TView::draw_snake(const Snake& snake)
{
    if(snake.length != 0)
    {
        gotoxy(snake.head.first, snake.head.second);
        std::cout << "O";

        for(const auto& part: snake.body)
        {
            gotoxy(part.first, part.second);
            std::cout << "o";
        }
        
        gotoxy(snake.tail.first, snake.tail.second);
        std::cout << "*";
    }

    return;
}

void TView::bye_print()
{
    printf("\033[H\033[J");
    printf("\033[%d;%dH Good bye!\n", win_size.first/2, win_size.second/2);
    gotoxy(win_size.first, win_size.second);
    //exit(0);
}

void TView::mainloop()
{
    struct pollfd input = {0, POLLIN, 0};
    char buf[BUFSIZE] = "";
    
    int timeout = 1000/UPS;
    for(int i = 0; i < 10000000; i++)
    {
        if(is_game_goes == false)
            break;

        auto first_time = std::chrono::system_clock::now();
        int n = poll(&input, 1, timeout);
        auto second_time = std::chrono::system_clock::now();
        int time = std::chrono::duration_cast<std::chrono::milliseconds>(second_time - first_time).count();
        timeout -= time;

        if(n == 0 || timeout <= 0)
        {
            for(const auto& ontime: ontimes)
                {
                    static auto third_time1 = std::chrono::system_clock::now();
                    static auto third_time2 = std::chrono::system_clock::now();

                    ontime();
                    timeout = 1000/UPS;

                    third_time2 = third_time1;
                    third_time1 = std::chrono::system_clock::now();
                    int time2 = std::chrono::duration_cast<std::chrono::milliseconds>(third_time2 - third_time1).count();
                    gotoxy(0, 3*win_size.first/4);
                    std::cout << "FPS:" << 1000.0/time2 << std::endl;
                }
        }

        if(n == 1)
        {  
            int a = read(0, buf, sizeof(buf));
            static int direction = 0;
                
            for(int i = 0; i < a; i++)
            {
                switch (buf[i])
                {
                    case 'w': case 'W':
                    if(direction != DOWN)
                    {
                        direction = UP;
                    }
                        break;
                    
                    case 's': case 'S':
                    if(direction != UP)
                    {
                        direction = DOWN;
                    }
                        break;

                    case 'a': case 'A':
                    if(direction != RIGHT)
                    {
                        direction = LEFT;
                    }
                        break;

                    case 'd': case 'D':
                    if(direction != LEFT)
                    {
                        direction = RIGHT;
                    }
                        break;

                    default:
                        break;
                }

                for(const auto& onkey: onkeys)
                {
                    onkey(direction);
                }
            }
            buf[0] = '\0';   
        }
        
    }

    bye_print();
}

TView::TView()
{
    struct winsize wins;
    ioctl(0, TIOCGWINSZ, &wins);
    win_size.first = wins.ws_row;
    win_size.second = wins.ws_col;

    struct termios term = {};
    tcgetattr(0, &term);
    old_term = term;

    term.c_lflag &= ~ECHO;
    term.c_lflag &= ~ICANON;

    tcsetattr(0, TCSANOW, &term);
}

TView::~TView()
{
    tcsetattr(0, TCSANOW, &old_term);
    
}
