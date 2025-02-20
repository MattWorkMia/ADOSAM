#include "game.h"

Game::Game() : 
        is_running_(true), is_in_game_(false), is_paused_(false)

{

    game_renderer_ = new GameRenderer;

}

Game::~Game() {

    delete game_renderer_;
    game_renderer_ = nullptr;

}

void Game::Run() {

    while (is_running_) {

        while (SDL_PollEvent(&event_) != 0) {

            if(event_.type == SDL_QUIT)
                is_running_ = false;

            if (event_.type == SDL_MOUSEBUTTONDOWN) 
                ProcessMouseButton();

            if(event_.type == SDL_KEYDOWN)
                ProcessKeyboard();

        }

        if(is_in_game_)
            IfInGame();

        else
            game_renderer_->RenderMenu();
    
    }

    SDL_Delay(16);
    
}



void Game::ProcessMouseButton(){

    if(game_renderer_->IfMouseButtonDown("quit", event_))
        is_running_ = false;

    else if(game_renderer_->IfMouseButtonDown("play1", event_)){

        game_renderer_->InitLevel("1");
        game_renderer_->SetCurrentLevel("1");
        game_renderer_->StartLevel();
        is_in_game_ = true;
        game_renderer_->DerenderMenu();

    }

    else if(game_renderer_->IfMouseButtonDown("play2", event_)){

        game_renderer_->InitLevel("2");
        game_renderer_->SetCurrentLevel("2");
        game_renderer_->StartLevel();
        is_in_game_ = true;
        game_renderer_->DerenderMenu();

    }

    else if(game_renderer_->IfMouseButtonDown("restart", event_)){

        game_renderer_->RestartLevel();
        is_finished_ = false;
        is_in_game_ = true;
        is_paused_ = false;

    }

    else if(game_renderer_->IfMouseButtonDown("go-back", event_)){

        game_renderer_->SetCurrentLevel("");
        is_in_game_ = false;
        is_paused_ = false;
        is_finished_ = false;

    }

}

void Game::ProcessKeyboard(){

    if(event_.key.keysym.sym == SDLK_ESCAPE)
        is_running_ = false;

    else if(is_in_game_){

        if (event_.key.keysym.sym == SDLK_p && !is_finished_){
            is_paused_ = !is_paused_;

            if(!is_paused_)
                game_renderer_->Countdown();

        }

        else if(!is_paused_ && !is_finished_)
            game_renderer_->IfKeyDown();
            
        game_renderer_->PauseLevel(is_paused_);
        

    }

}

void Game::IfInGame(){

    if(is_in_game_){

        game_renderer_->CheckIfLevelFinished(is_finished_);

        if(is_finished_)
            game_renderer_->PauseLevel(!is_paused_);

        else if(!is_paused_ && !is_finished_)
            game_renderer_->UpdateLevel();

        game_renderer_->RenderLevel(is_paused_);

    }

}