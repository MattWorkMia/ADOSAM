#include "player.h"

Player::Player(SDL_DisplayMode* display_mode, 
               const unsigned int& bpm)
        
{

    sun_ = make_unique<Image>("./data/images/sun.png", 
                                   (display_mode->w / 2) - 75, 
                                   (display_mode->h / 2) - 50,
                                   50, 50);

    moon_ = make_unique<Image>("./data/images/moon.png",
                                    (display_mode->w / 2) - 175, 
                                    (display_mode->h / 2) - 50, 
                                    50, 50);

    rotation_speed_ = (M_PI * bpm) / pow(60, 2);
    is_sun_rotating_ = false;

}

Player::~Player(){

}

void Player::Render(SDL_Renderer* renderer){

    sun_->Render(renderer);
    moon_->Render(renderer);

}

void Player::UpdateRotation(){

    if(is_sun_rotating_)
        RotateSun();

    else
        RotateMoon();

}

void Player::Scroll(const float& x_diff, const float& y_diff){

    sun_->SetXPos(sun_->GetXPos() + x_diff);
    sun_->SetYPos(sun_->GetYPos() + y_diff);

    moon_->SetXPos(moon_->GetXPos() + x_diff); 
    moon_->SetYPos(moon_->GetYPos() + y_diff);

}

void Player::RotateMoon() {

    float initial_x = moon_->GetXPos();
    float initial_y = moon_->GetYPos();

    moon_->SetXPos(cos(rotation_speed_) * (initial_x - sun_->GetXPos()) - 
                   sin(rotation_speed_) * (initial_y - sun_->GetYPos()) + 
                   sun_->GetXPos());

    moon_ -> SetYPos(sin(rotation_speed_) * (initial_x - sun_->GetXPos()) + 
                     cos(rotation_speed_) * (initial_y - sun_->GetYPos()) + 
                     sun_->GetYPos());
    
}

void Player::RotateSun() {

    float initial_x = sun_->GetXPos();
    float initial_y = sun_->GetYPos(); 

    sun_ -> SetXPos(cos(rotation_speed_) * (initial_x - moon_->GetXPos()) - 
                    sin(rotation_speed_) * (initial_y - moon_->GetYPos()) + 
                    moon_->GetXPos());

    sun_ -> SetYPos(sin(rotation_speed_) * (initial_x - moon_->GetXPos()) + 
                    cos(rotation_speed_) * (initial_y - moon_->GetYPos()) + 
                    moon_->GetYPos());

}

void Player::ChangeRotation(){

    is_sun_rotating_ = !is_sun_rotating_;

}

void Player::ReverseRotation(){

    rotation_speed_ *= -1;

}

void Player::SpeedUp(){

    rotation_speed_ *= 1.3;

}

void Player::SlowDown(){

    rotation_speed_ *= 0.66;

}

bool Player::IsSunRotating() const{

    return is_sun_rotating_;

}

void Player::MovePlayerToNextTile(const float& next_x_pos, 
                                  const float& next_y_pos, 
                                  const bool& next_is_vertical,
                                  const bool& next_is_up_corner)
{
    
    float x_offset = 0, y_offset = 0;

    if(next_is_vertical) 
        y_offset = 25;
        
    else if(next_is_up_corner) 
        x_offset = 25, y_offset = 25;

    else 
        x_offset = 25;

    if(IsSunRotating()){

        sun_->SetXPos(next_x_pos + x_offset);
        sun_->SetYPos(next_y_pos + y_offset);

    }
        
    else{

        moon_->SetXPos(next_x_pos + x_offset);
        moon_->SetYPos(next_y_pos + y_offset);

    }
        
}

float Player::GetSunDistanceFromPoint(const float& x, const float& y) const{

    float sun_center_x = sun_->GetXPos() + sun_->GetWidth() / 2;
    float sun_center_y = sun_->GetYPos() + sun_->GetHeight() / 2;
    
    return sqrt( pow(x - sun_center_x, 2) + pow(y - sun_center_y, 2) );

}

float Player::GetMoonDistanceFromPoint(const float& x, const float& y) const{

    float moon_center_x = moon_->GetXPos() + moon_->GetWidth() / 2;
    float moon_center_y = moon_->GetYPos() + moon_->GetHeight() / 2;

    return sqrt( pow(x - moon_center_x, 2) + pow(y - moon_center_y, 2) );

}