#include "image.h"

Image::Image(const string& file_path, const float& x_pos, const float& y_pos, 
             const int& width, const int& height) : 
        surface_(nullptr), 
        texture_(nullptr), 
        rectangle_(nullptr), 
        file_path_(file_path), 
        x_pos_(x_pos), y_pos_(y_pos),
        width_(width), height_(height) 
        
{
    is_rendered_ = false;
}

Image::~Image(){

    Unload();

}


void Image::Load(SDL_Renderer* renderer) {

    if (surface_ == nullptr){

        surface_ = IMG_Load(file_path_.c_str());
        
        if (surface_ == nullptr)
            cerr << "Error loading image: " << IMG_GetError() << endl;

    }

    if (texture_ == nullptr){

        texture_ = SDL_CreateTextureFromSurface(renderer, surface_);
        
        if (texture_ == nullptr)
            cerr << "Error Creating Texture: " << SDL_GetError() << endl;

    }

    if (rectangle_ == nullptr){

        InitiateRectangle();

    }

}


void Image::Unload(){

    if(surface_ != nullptr) {

        SDL_FreeSurface(surface_);
        surface_ = nullptr;

    }

    if(texture_ != nullptr){

        SDL_DestroyTexture(texture_);
        texture_ = nullptr;

    }

    if(rectangle_ != nullptr){

        delete rectangle_;
        rectangle_ = nullptr;
        
    }

}

void Image::Render(SDL_Renderer* renderer){

        is_rendered_ = true;
        Load(renderer);
        UpdateRectangleCoordinates();

        if(SDL_RenderCopy(renderer, texture_, nullptr, rectangle_) != 0)
            cerr << "Error rendering Image class: " << SDL_GetError() << endl;

}

void Image::InitiateRectangle(){

    rectangle_ = new SDL_Rect;
    rectangle_->w = width_;
    rectangle_->h = height_;
    rectangle_->x = x_pos_;
    rectangle_->y = y_pos_;

}

void Image::UpdateRectangleCoordinates(){

    rectangle_->x = x_pos_;
    rectangle_->y = y_pos_;

}

float Image::GetXPos() const{

    return x_pos_;

}

float Image::GetYPos() const{

    return y_pos_;

}

Uint16 Image::GetWidth() const{

    return width_;

}

Uint16 Image::GetHeight() const{

    return height_;

}

void Image::SetXPos(const float& x_pos){

    x_pos_ = x_pos;

}

 void Image::SetYPos(const float& y_pos){

    y_pos_ = y_pos;

 }

 void Image::SetWidth(const float& width){

    width_ = width;

}

 void Image::SetHeight(const float& height){

    height_ = height;

 }
 
bool Image::IsRendered() const {

    return is_rendered_;

}

void Image::Derender() {

    is_rendered_ = false;

}