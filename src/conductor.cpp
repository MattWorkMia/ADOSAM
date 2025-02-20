#include "conductor.h"

Conductor::Conductor(const float& music_bpm, const string& level_folder_path) : 
        music_(nullptr), sound_effect_(nullptr), 
        level_folder_path_(level_folder_path), bpm_(music_bpm)

{

    seconds_per_beat_ = 60 / bpm_;
    music_position_ = 0;
    Load();
    
}

Conductor::~Conductor(){

    Unload();

}

void Conductor::Load(){

    if(music_ == nullptr || sound_effect_ == nullptr){

        Unload();
        Mix_AllocateChannels(2);
        Mix_Volume(0, MIX_MAX_VOLUME);
        Mix_Volume(1, MIX_MAX_VOLUME / 4);
        music_ = Mix_LoadWAV((level_folder_path_ + "music.wav").c_str());
        sound_effect_ = Mix_LoadWAV((level_folder_path_ + "sound_effect.wav").c_str());

    }

}

void Conductor::Unload(){

    Mix_FreeChunk(music_);
    Mix_FreeChunk(sound_effect_);
    Mix_HaltChannel(0);
    Mix_HaltChannel(1);

}

void Conductor::PlayMusic(){

    if(music_position_ == 0)
        start_time_ = SDL_GetTicks();
    
    Mix_PlayChannel(0, music_, 0); 

}

void Conductor::PauseMusic(const bool& is_paused){

    if(is_paused)
        Mix_Pause(0);

    else
        Mix_Resume(0);

}

void Conductor::PlaySoundEffect(){

    Mix_PlayChannel(1, sound_effect_, 0); 

}

void Conductor::Update(){

    music_position_ = (SDL_GetTicks() - start_time_) / 1000;

}

float Conductor::GetBpm() const{

    return bpm_;

}

float Conductor::GetSecondsPerBeat() const{

    return seconds_per_beat_;

}