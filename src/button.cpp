#include "button.h"

Button::Button(const string& file_path, 
               const float& x_pos, const float& y_pos, 
               const int& width, const int& height) : 
        Image(file_path, x_pos, y_pos, width, height)
        
{
    
}

Button::~Button(){
    
}

bool Button::CheckIfClicked(const SDL_Event& event){

    int mouse_x = event.button.x;
    int mouse_y = event.button.y;

    int x_max, x_min, y_max, y_min;

    x_min = GetXPos();
    x_max = x_min + GetWidth();

    y_min = GetYPos();
    y_max = y_min + GetHeight();

    if (mouse_x >= x_min && mouse_x <= x_max &&
        mouse_y >= y_min && mouse_y <= y_max &&
        IsRendered()) 
        
        return true;
    
    return false;

}