#include "text.h"

Text::Text(SDL_Renderer* renderer, const SDL_Color& color, TTF_Font* font, 
           const float& x_pos, const float& y_pos, 
           const int& width, const int& height, 
           const string& initial_value) :
        color_(color), 
        font_(font), 
        x_pos_(x_pos), 
        y_pos_(y_pos), 
        width_(width),
        height_(height)
           
{

    text_surface_ = TTF_RenderText_Solid(font_, "0", color_);

    if (text_surface_ == nullptr)
        cerr << "Error loading text: " << TTF_GetError() << endl;

    text_texture_ = SDL_CreateTextureFromSurface(renderer, text_surface_);

    if (text_texture_ == nullptr) 
        cerr << "Error Creating text Texture: " << SDL_GetError() << endl;

    text_rectangle_ = new SDL_Rect;
    text_rectangle_->x = x_pos_;
    text_rectangle_->y = y_pos_;
    text_rectangle_->w = width_;
    text_rectangle_->h = height_;

}

Text::~Text(){

    delete text_rectangle_;
    text_rectangle_ = nullptr;

    SDL_FreeSurface(text_surface_);
    text_surface_ = nullptr;

    SDL_DestroyTexture(text_texture_);
    text_texture_ = nullptr;

}

void Text::Update(SDL_Renderer* renderer, const string& value){

    text_surface_ = TTF_RenderText_Solid(font_, value.c_str(), color_);

    if (text_surface_ == nullptr) 
        cerr << "Error loading text: " << TTF_GetError() << endl;

    text_texture_ = SDL_CreateTextureFromSurface(renderer, text_surface_);

    if (text_texture_ == nullptr)
        cerr << "Error Creating text Texture: " << SDL_GetError() << endl;

}

void Text::Render(SDL_Renderer* renderer){

    if(SDL_RenderCopy(renderer, text_texture_, nullptr, text_rectangle_) != 0)
        cerr << "Error rendering text: " << SDL_GetError() << endl;

}

void Text::ChangeCoordinates(const float& x_pos, const float& y_pos){

    text_rectangle_->x = x_pos;
    text_rectangle_->y = y_pos;

}