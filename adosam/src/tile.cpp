#include "tile.h"

Tile::Tile(const string& file_path, 
           const float& x_pos, const float& y_pos, 
           const int& width, const int& height, 
           const string& tile_type,
           const string& direction) :
        Image(file_path,  x_pos,  y_pos,  width, height)

{

    tile_type_ = GetType(tile_type);

    direction_ = direction;

    if(IsVertical()){

        SetWidth(50);
        SetHeight(100);

    }

    else if(IsCorner()){

        SetWidth(100);
        SetHeight(75);

    }

    else{

        SetWidth(100);
        SetHeight(50);

    }

}

Tile::~Tile(){

}

void Tile::GetCenter(float& x_pos, float& y_pos) const{

    if(IsVertical()){

        x_pos = GetXPos() + GetWidth() / 4 ;
        y_pos = GetYPos() + GetHeight() / 2;

    }

    else{

        x_pos = GetXPos() + GetWidth() / 2;
        y_pos = GetYPos() + GetHeight() / 2;

    }

}

Tile::Types_ Tile::GetType(const std::string& type) const{
    
    if(type == "vertical")
        return VERTICAL;

    else if(type == "horizontal")
        return HORIZONTAL;

    else if(type == "down-left")
        return DOWN_LEFT;

    else if(type == "down-right")
        return DOWN_RIGHT;

    else if(type == "up-left")
        return UP_LEFT;

    else if(type == "up-right")
        return UP_RIGHT;

    else if(type == "speed")
        return SPEED;

    else if(type == "slow")
        return SLOW;

    else if(type == "swirl")
        return SWIRL;

    return END;

}

bool Tile::IsVertical() const{

    if(tile_type_ == VERTICAL)
        return true;
    
    return false;

}

bool Tile::IsHorizontal() const{

    if(tile_type_ == HORIZONTAL)
        return true;
    
    return false;

}

bool Tile::IsCorner() const{

    if(IsSwirl() || IsSlow() ||
       IsSpeed() || IsVertical() ||
       IsHorizontal() || IsEnd())

        return false;
    
    return true;

}

bool Tile::IsUpCorner() const{

    if(tile_type_ == UP_LEFT || tile_type_ == UP_RIGHT)
        return true;
    
    return false;

}

bool Tile::IsDownCorner() const{

    if(tile_type_ == DOWN_LEFT || tile_type_ == DOWN_RIGHT)
        return true;
    
    return false;

}

bool Tile::IsEnd() const{

    if(tile_type_ == END)
        return true;
    
    return false;

}

bool Tile::IsSwirl() const{

    if(tile_type_ == SWIRL)
        return true;
    
    return false;

}

bool Tile::IsSpeed() const{

    if(tile_type_ == SPEED)
        return true;
    
    return false;

}

bool Tile::IsSlow() const{

    if(tile_type_ == SLOW)
        return true;
    
    return false;

}

string Tile::DetermineNextDirection(const std::string& next_tile_type){

    Tile::Types_ next_type = GetType(next_tile_type);

    if(direction_ == "right"){

        switch(next_type){

            case HORIZONTAL : 
                return "right";

            case SLOW : 
                return "right";

            case SPEED : 
                return "right";

            case SWIRL : 
                return "right";
                
            case DOWN_LEFT : 
                return "down";

            case UP_LEFT : 
                return "up";

            case END : 
                return "right";

            default:
                cerr << "Not existing type" << endl;
                return "";

        }
        
    }

    else if(direction_ == "left"){

        switch(next_type){

            case HORIZONTAL : 
                return "left";

            case SLOW : 
                return "left";

            case SPEED : 
                return "left";

            case SWIRL : 
                return "left";
                
            case DOWN_RIGHT : 
                return "down";

            case UP_RIGHT : 
                return "up";

            default:
                cerr << "Not existing type" << endl;
                return "";

        }
        
    }

    else if(direction_ == "up"){

        switch(next_type){

            case VERTICAL: 
                return "up";
                
            case DOWN_LEFT : 
                return "left";

            case DOWN_RIGHT : 
                return "right";

            default:
                cerr << "Not existing type" << endl;
                return "";

        }
        
    }

    else{

        switch(next_type){

            case VERTICAL: 
                return "down";
                
            case UP_LEFT : 
                return "left";

            case UP_RIGHT : 
                return "right";

            default:
                cerr << "Not existing type" << endl;
                return "";

        }

    }

}


void Tile::DetermineNextTileCoordinates(const std::string& next_tile_type,
                                        float& next_tile_x_pos, 
                                        float& next_tile_y_pos) const{

    Tile::Types_ next_type = GetType(next_tile_type);

    if(direction_ == "right"){
        
        next_tile_x_pos = GetXPos() + GetWidth();
        
        if(next_type != UP_LEFT && tile_type_ == UP_RIGHT) 
            next_tile_y_pos = GetYPos() + GetHeight() / 3;
        
        else if(next_type == UP_LEFT && tile_type_ == DOWN_RIGHT)
            next_tile_y_pos = GetYPos() - GetHeight() / 3;

        else if(next_type == UP_LEFT && tile_type_ == HORIZONTAL)
            next_tile_y_pos = GetYPos() - GetHeight() / 2; 

        else 
            next_tile_y_pos = GetYPos();

    }

    else if(direction_ == "left"){

        next_tile_x_pos = GetXPos() - GetWidth();
        
        if(next_type == UP_RIGHT && tile_type_ == DOWN_LEFT) 
            next_tile_y_pos = GetYPos() - GetHeight() / 3;

        else if(next_type == UP_RIGHT && tile_type_ == HORIZONTAL)
            next_tile_y_pos = GetYPos() - GetHeight() / 2; 

        else if(next_type != UP_RIGHT && tile_type_ == UP_LEFT)
            next_tile_y_pos = GetYPos() + GetHeight() / 3; 

        else 
            next_tile_y_pos = GetYPos();

    }

    else if(direction_ == "down"){

        if(next_type == UP_LEFT && tile_type_ == DOWN_RIGHT) 
            next_tile_x_pos = GetXPos() - GetWidth() / 2;
        
        else if(next_type == UP_LEFT && tile_type_ == VERTICAL)
            next_tile_x_pos = GetXPos() - GetWidth();

        else if(next_type != UP_LEFT && tile_type_ == DOWN_LEFT)
            next_tile_x_pos = GetXPos() + GetWidth() / 2; 

        else 
            next_tile_x_pos = GetXPos();

        next_tile_y_pos = GetYPos() + GetHeight();

    }

    else{

        if(next_type != DOWN_LEFT && tile_type_ == UP_LEFT) 
            next_tile_x_pos = GetXPos() + GetWidth() / 2;
        
        else if(next_type == DOWN_LEFT && tile_type_ == VERTICAL)
            next_tile_x_pos = GetXPos() - GetWidth();

        else if(next_type == DOWN_LEFT && tile_type_ == UP_RIGHT)
            next_tile_x_pos = GetXPos() - GetWidth() / 2; 

        else 
            next_tile_x_pos = GetXPos();

        next_tile_y_pos = GetYPos() - GetHeight();

    }

}
