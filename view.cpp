#include "view.hpp"
#include "Tview.hpp"
#include "Gview.hpp"


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

View::~View()
{

}
