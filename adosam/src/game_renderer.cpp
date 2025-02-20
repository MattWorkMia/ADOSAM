#include "game_renderer.h"

GameRenderer::GameRenderer() : 
        img_tile_path_("./data/tiles_img/"), img_extension_(".png") 

{
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {

        cerr << "SDL could not initialize Video! SDL_Error: " 
             << SDL_GetError() 
             << endl;

        SDL_Quit();

    }

    if (TTF_Init() < 0) {

        cerr << "SDL could not initialize SDL_ttf! SDL_Error: " 
             << SDL_GetError() 
             << endl;

        SDL_VideoQuit();
        SDL_Quit();

    }

    if (Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)
    {

        cerr << "Could not open SDL_MIXER " << Mix_GetError() << endl;

        SDL_VideoQuit();
        TTF_Quit();
        SDL_Quit();

    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {

        cerr << "SDL_image could not initialize! SDL_image Error: " 
             << IMG_GetError() 
             << endl;

        Mix_CloseAudio();
        SDL_VideoQuit();
        TTF_Quit();
        SDL_Quit();

    }

    displaymode_ = new SDL_DisplayMode;

    if (SDL_GetDesktopDisplayMode(0, displaymode_) != 0) {

        cerr << "SDL could not get display information! SDL_Error: " 
             << SDL_GetError() 
             << endl;
        Mix_CloseAudio();
        SDL_VideoQuit();
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();

    }

    window_ = SDL_CreateWindow("ADOSAM", SDL_WINDOWPOS_UNDEFINED, 
                               SDL_WINDOWPOS_UNDEFINED, 
                               displaymode_->w, displaymode_->h, 
                               SDL_WINDOW_FULLSCREEN);

    if(window_ == nullptr)
    {

        cerr << "SDL could not create the window! SDL_Error: " 
             << SDL_GetError() 
             << endl;

        Mix_CloseAudio();
        SDL_VideoQuit();
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();

    }
    
    renderer_ = SDL_CreateRenderer(window_, -1, 
                                   SDL_RENDERER_ACCELERATED | 
                                   SDL_RENDERER_PRESENTVSYNC | 
                                   SDL_RENDERER_TARGETTEXTURE);

    if(renderer_ == nullptr)
    {

        cerr << "SDL could not create the renderer! SDL_Error: " 
             << SDL_GetError() 
             << endl;

        Mix_CloseAudio();
        SDL_VideoQuit();
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();

    }
    
    font_ = TTF_OpenFont("./data/Roboto-Black.ttf", 100);

    if(font_ == nullptr){

        cerr << "SDL could not open the font! SDL_Error: " 
             << TTF_GetError() 
             << endl;

    }

    InitMenu();

}

GameRenderer::~GameRenderer(){

    delete menu_background_;
    menu_background_ = nullptr;

    delete level_background_;
    level_background_ = nullptr;

    delete quit_button_;
    quit_button_ = nullptr;

    delete level_1_button_;
    level_1_button_ = nullptr;

    delete level_2_button_;
    level_2_button_ = nullptr;

    delete pause_image_;
    pause_image_ = nullptr;

    delete restart_button_;
    restart_button_ = nullptr;

    delete go_back_button_;
    restart_button_ = nullptr;

    delete level_;
    level_ = nullptr;

    delete displaymode_;
    displaymode_ = nullptr;

    delete score_;
    score_ = nullptr;

    delete life_;
    life_ = nullptr;

    delete rythm_;
    life_ = nullptr;

    delete life_image_;
    life_image_ = nullptr;

    TTF_CloseFont(font_);
    font_ = nullptr;

    SDL_DestroyRenderer(renderer_);
    renderer_ = nullptr;

    SDL_DestroyWindow(window_);
    window_ = nullptr;

    Mix_CloseAudio();
    SDL_VideoQuit();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

}


void GameRenderer::IfKeyDown(){

    string text_rythm;
    float tile_x, tile_y;

    level_->CheckPlayerAccuracy(text_rythm, tile_x, tile_y);
    rythm_->Update(renderer_, text_rythm);
    rythm_->ChangeCoordinates(tile_x, tile_y - 25);

}

bool GameRenderer::IfMouseButtonDown(const string& button_name, 
                                     const SDL_Event& event){

    if(button_name == "quit")
        return quit_button_->CheckIfClicked(event);

    else if(button_name == "play1")
        return level_1_button_->CheckIfClicked(event);

    else if(button_name == "play2")
        return level_2_button_->CheckIfClicked(event);

    else if(button_name == "restart")
        return restart_button_->CheckIfClicked(event);

    else if(button_name == "go-back")   
        return go_back_button_->CheckIfClicked(event);

    return false;

}

void GameRenderer::InitMenu(){

    menu_background_= new Image("./data/images/menu.png", 0, 0, 
                                displaymode_->w, displaymode_->h);

    quit_button_ = new Button("./data/images/quit.png", 5, 5, 50, 50);

    level_1_button_ = new Button("./data/images/level1button.png", 
                                400, 600, 250, 200);

    level_2_button_ = new Button("./data/images/level2button.png", 
                                800, 600, 250, 200);

}

void GameRenderer::RenderMenu(){

    SDL_SetRenderDrawColor(renderer_, 255,0,0,255);
    SDL_RenderClear(renderer_);

    menu_background_->Render(renderer_);
    quit_button_->Render(renderer_);
    level_1_button_->Render(renderer_);
    level_2_button_->Render(renderer_);

    SDL_RenderPresent(renderer_);

}

void GameRenderer::DerenderMenu(){

    quit_button_->Derender();
    level_1_button_->Derender();
    level_2_button_->Derender();

}

void GameRenderer::InitLevel(const string& level_number){

    string level_folder_path = "./data/maps/map" + level_number + "/";

    level_background_ = new Image("./data/images/background.png", 0, 0, 
                                  displaymode_->w, displaymode_->h);

    level_ = new Level(img_tile_path_, img_extension_, level_folder_path,
                       displaymode_);

    score_ = new Text(renderer_, {220, 60, 40}, font_, 
                      displaymode_->w - 80, 10, 80, 80, "0");

    life_ = new Text(renderer_, {220, 60, 40}, font_, 0, 0, 80, 80, "3");

    rythm_ = new Text(renderer_, {220, 60, 40}, font_, 
                      2000, 2000, 40, 20, "");

    life_image_ = new Image("./data/images/life.png", 85, 0, 80 , 80);

    pause_image_ = new Image("./data/images/pause.png", 
                             displaymode_->w/2 - 150, 
                             displaymode_->h/2 - 100, 
                             200, 200);

    restart_button_ = new Button("./data/images/restart.png", 
                                 displaymode_->w/2 + 50, 
                                 displaymode_->h/2 - 100, 
                                 200, 200);

    go_back_button_ = new Button("./data/images/quit.png", 
                                 displaymode_->w/2 + - 350, 
                                 displaymode_->h/2 - 100, 
                                 200, 200);

}

void GameRenderer::UpdateLevel(){

    level_->Update();

    string score = to_string(level_->GetScore());

    score_->Update(renderer_, score);

    string life = to_string(level_->GetLife());

    life_->Update(renderer_, life);


}

void GameRenderer::RenderLevel(const bool& is_paused){

    SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 255);
    SDL_RenderClear(renderer_);

    restart_button_->Derender();

    level_background_->Render(renderer_);
    level_ -> Render(renderer_);
    score_->Render(renderer_);
    life_->Render(renderer_);
    life_image_->Render(renderer_);
    rythm_->Render(renderer_);

    if(is_paused){

        pause_image_->Render(renderer_);
        restart_button_->Render(renderer_);
        go_back_button_->Render(renderer_);

    }

    else if(level_->IsFinished()){

        restart_button_->Render(renderer_);
        go_back_button_->Render(renderer_);

    }

    SDL_RenderPresent(renderer_);

}

void GameRenderer::StartLevel(){

    Countdown();
    level_->Start();

}

void GameRenderer::RestartLevel(){

    delete level_;
    level_ = nullptr;
    InitLevel(current_level_);
    StartLevel();

}

void GameRenderer::PauseLevel(const bool & is_paused){

    level_->Pause(is_paused);

}


void GameRenderer::CheckIfLevelFinished(bool& finished) const{

    finished = level_->IsFinished();

}

void GameRenderer::Countdown(){

    Text* countdown = new Text(renderer_, {220, 60, 40}, font_, 
                               displaymode_->w/2 - 50, 
                               displaymode_->h/2 - 50,
                               100, 100, "3");

    UpdateLevel();

    for(unsigned int i = 3; i > 0; i--){

        SDL_RenderClear(renderer_);
        level_background_->Render(renderer_);
        level_->Render(renderer_);

        countdown->Update(renderer_, to_string(i));

        countdown->Render(renderer_);

        SDL_RenderPresent(renderer_);

        int time_between_beats_in_ms = (1000 * level_->GetMusicSecondsPerBeat());

        level_->PlaySoundEffect();

        SDL_Delay(time_between_beats_in_ms);
                                                
    }

    delete countdown;
    
}

void GameRenderer::SetCurrentLevel(const string& current_level){

    current_level_ = current_level;

}


