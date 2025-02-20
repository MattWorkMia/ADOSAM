#include "level.h"

Level::Level(const string& tile_image_path, 
             const string& img_extension, 
             const string& level_folder_path, 
             SDL_DisplayMode* displaymode) : 
        displaymode_(displaymode), 
        tile_image_path_(tile_image_path), image_extension_(img_extension)
        
{

    Load(level_folder_path);
    finished_ = false;
    scroll_speed_ = FRAMERATE * map_->GetMusicSecondsPerBeat();
    life_ = 3;

}

Level::~Level(){

    delete map_;
    
    for (Tile* tile : *displayed_tiles_)
        delete tile;

    map_ = nullptr;
    displayed_tiles_ = nullptr;

}

void Level::Load(const string& level_folder_path){

    map_ = new Map(level_folder_path);

    displayed_tiles_ = new deque<Tile*>;

    string first_tile_type = map_->GetNextTileTypeToDisplay();

    string first_tile_image_path = tile_image_path_ + 
                                   first_tile_type + 
                                   image_extension_;

    Tile* first_tile = new Tile(first_tile_image_path, 
                                (displaymode_->w/2) - 100, 
                                (displaymode_->h/2) - 50, 
                                100, 
                                100, 
                                first_tile_type,
                                "right");


    AddTileToDisplay(first_tile);

    level_position_ = displayed_tiles_->begin();

    player_ = new Player(displaymode_, map_->GetMusicBpm());

}

void Level::LoadNewTiles(){

    float new_tile_x_pos = 0, new_tile_y_pos = 0;

    Tile* current_tile;
    Tile* new_tile;

    string new_tile_type = map_->GetNextTileTypeToDisplay();


    bool is_next_tile_renderable = IsNextTileRenderable(*GetCurrentTile(), 
                                                        new_tile_type);
    
    while(!map_->IsEmpty() && is_next_tile_renderable){ 

        current_tile = GetCurrentTile();

        new_tile_type = map_->GetNextTileTypeToDisplay();

        current_tile->DetermineNextTileCoordinates(new_tile_type, 
                                                   new_tile_x_pos, 
                                                   new_tile_y_pos);

        string new_tile_image_path = tile_image_path_ 
                                   + new_tile_type 
                                   + image_extension_;

        string new_direction = current_tile->DetermineNextDirection(new_tile_type);

        new_tile = new Tile(new_tile_image_path, 
                            new_tile_x_pos, 
                            new_tile_y_pos, 
                            100,
                            100, 
                            new_tile_type,
                            new_direction);

        AddTileToDisplay(new_tile);

    }

}

void Level::UnloadOutOfScreenTiles(){

    do {

        Tile* oldest_displayed_tile = GetOldestDisplayedTile();

        if (IsTileOutOfScreen(*oldest_displayed_tile)) {
            delete oldest_displayed_tile;
            oldest_displayed_tile = nullptr;
            PopOldestDisplayedTile();
        } 
        
        else 
            break;
    }   
    
    while (!displayed_tiles_->empty());

}

void Level::Render(SDL_Renderer* renderer) {
     
    for (Tile* tile : *displayed_tiles_)
        tile->Render(renderer);

    player_->Render(renderer);

}

void Level::Start(){

    map_->PlayMusic();
    score_ = 0;

}

void Level::Pause(const bool& is_paused){

    map_->PauseMusic(is_paused);

}

void Level::Update(){

    if(life_ == 0)
        finished_ = true;

    if(IsPlayerOnNextTile()){

        MoveToNextTile();
        has_moved_ = true;
        input_delay_ = chrono::high_resolution_clock::now();

    }
    
    player_->UpdateRotation();
    player_->Scroll(scroll_x_diff_, scroll_y_diff_);

    UpdateTilesPosition();

    map_->UpdateMusic();

    LoadNewTiles();
    UnloadOutOfScreenTiles();

}

void Level::AddTileToDisplay(Tile* tile_to_add){

    map_->PopNewTile();
    displayed_tiles_->push_back(tile_to_add);

}

void Level::UpdateTilesPosition(){

    for (Tile* tile : *displayed_tiles_) {

        tile -> SetXPos(tile->GetXPos() + scroll_x_diff_);
        tile -> SetYPos(tile->GetYPos() + scroll_y_diff_);

    }

}

bool Level::IsNextTileRenderable(const Tile& current_tile, 
                             const string& next_tyle_type) 
{

    float x_pos = 0, y_pos = 0;

    current_tile.DetermineNextTileCoordinates(next_tyle_type, x_pos, y_pos);

    if (x_pos >= -displaymode_->w && 
        x_pos <= 2*displaymode_->w && 
        y_pos >= -displaymode_->h && 
        y_pos <= 2*displaymode_->h) 

        return true;


    return false;

}

bool Level::IsTileOutOfScreen(const Tile& tile) const{

    if (tile.GetXPos() >= -300 && 
        tile.GetXPos() <= displaymode_->w && 
        tile.GetYPos() >= -300 && 
        tile.GetYPos() <= displaymode_ ->h) 

        return false;

    return true;

}

Tile* Level::GetOldestDisplayedTile() const{

    return displayed_tiles_->front();

}

Tile* Level::GetCurrentTile() const{

    return displayed_tiles_->back();

}

void Level::PopOldestDisplayedTile(){

    displayed_tiles_->pop_front();

}

void Level::MoveToNextTile(){

    Tile* current_tile = *level_position_;

    ++level_position_;

    Tile* next_tile = *level_position_;

    UpdateScrolling(current_tile, next_tile);

    bool is_next_tile_vertical = next_tile->IsVertical();
    bool is_next_tile_up_corner = next_tile->IsUpCorner();

    player_->MovePlayerToNextTile(next_tile->GetXPos(), 
                                  next_tile->GetYPos(), 
                                  is_next_tile_vertical,
                                  is_next_tile_up_corner);

    ApplyTileEffect();

    player_->ChangeRotation();

}

void Level::ApplyTileEffect(){

    bool is_next_tile_swirl = (*level_position_)->IsSwirl();
    bool is_next_tile_speed = (*level_position_)->IsSpeed();
    bool is_next_tile_slow = (*level_position_)->IsSlow();
    bool is_next_tile_end = (*level_position_)->IsEnd();

    if(is_next_tile_swirl)
        player_->ReverseRotation();

    else if(is_next_tile_speed)
        player_->SpeedUp();

    else if(is_next_tile_slow)
        player_->SlowDown();

    else if(is_next_tile_end)
        finished_ = true;

}

void Level::UpdateScrolling(Tile* current_tile, Tile* next_tile){

    bool is_next_tile_corner = (*level_position_)->IsCorner();

    if(is_next_tile_corner){

        scroll_x_diff_ = (current_tile->GetXPos() - next_tile->GetXPos()) 
                         / scroll_speed_;
        scroll_y_diff_ = (current_tile->GetYPos() - next_tile->GetYPos()) 
                         / scroll_speed_ * 1.3;

    }

    else{

        scroll_x_diff_ = (current_tile->GetXPos() - next_tile->GetXPos()) 
                         / scroll_speed_;
        scroll_y_diff_ = (current_tile->GetYPos() - next_tile->GetYPos()) 
                         / scroll_speed_;
    
    }

}

bool Level::IsPlayerOnNextTile() const{

    Tile* current_tile = *level_position_;

    bool is_tile_corner = current_tile->IsCorner();
    bool is_tile_vertical = current_tile->IsVertical();

    if (level_position_ == displayed_tiles_->end() || 
        level_position_ + 1 == displayed_tiles_->end())

        return false;

    float distance = GetDistanceFromNextTile();

    if(distance < 6)
        return true;

    else if(is_tile_corner && distance < 15) 
        return true;

    else if(is_tile_vertical && distance < 10)
        return true;

    else
        return false;

}

float Level::GetDistanceFromNextTile() const{

    float next_tile_center_x, next_tile_center_y;

    Tile* next_tile = *(level_position_ + 1);

    next_tile->GetCenter(next_tile_center_x, next_tile_center_y);

    float distance_to_point;

    if(player_->IsSunRotating())
        distance_to_point = player_->GetSunDistanceFromPoint(next_tile_center_x, 
                                                             next_tile_center_y);

    else
        distance_to_point = player_->GetMoonDistanceFromPoint(next_tile_center_x, 
                                                              next_tile_center_y);

    return distance_to_point;

}

void Level::CheckPlayerAccuracy(string& rythm_text, float& tile_x, float& tile_y){
    
    auto player_input = chrono::high_resolution_clock::now();
    auto duration = chrono::milliseconds(0);

    if(has_moved_)
        duration = chrono::duration_cast<chrono::milliseconds>(player_input - 
                                                               input_delay_);
    
    else
        duration = chrono::duration_cast<chrono::milliseconds>(input_delay_ - 
                                                               player_input);
    

    float delay = duration.count();

    tile_x = (*level_position_)->GetXPos();
    tile_y = (*level_position_)->GetYPos();

    int bpm = map_->GetMusicBpm();

    if(delay < -bpm * 1.25){

        life_ -= 1;
        rythm_text = "early";

    }

    else if(delay < bpm * 2) {

        score_ += (int) (bpm - delay);
        rythm_text = "good";

    }

    else {
        
        life_ -= 1;
        rythm_text = "late";

    }

    has_moved_ = false;

}

int Level::GetScore() const{

    return score_;

}

int Level::GetLife() const{

    return life_;

}

bool Level::IsFinished() const {

    return finished_;

}

void Level::PlaySoundEffect() {

    map_->PlaySoundEffect();

}

float Level::GetMusicSecondsPerBeat() const{

    return map_->GetMusicSecondsPerBeat();

}