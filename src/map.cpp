#include "map.h"

Map::Map(const string& level_folder_path){

    map_queue_ = new deque<string>;
    FileToMap(level_folder_path + "map.txt", level_folder_path);

}

Map::~Map() {

    delete map_music_;
    delete map_queue_;
    map_music_ = nullptr;
    map_queue_ = nullptr;

}

void Map::FileToMap(const string& map_path, const string& level_folder_path) {

    ifstream map_file(map_path);

    if (!map_file.is_open()) {

        cerr << "Error while opening the file : " 
             << map_path 
             << " - " 
             << strerror(errno) 
             << endl;

    } 

    else {

        string line;
        string music_bpm;

        getline(map_file, music_bpm);

        map_music_ = new Conductor(stof(music_bpm), level_folder_path);

        while (getline(map_file, line)) 
            map_queue_ -> push_back(line);

        map_file.close();

    }

}

void Map::MapToFile(const string& map_path) const {

    ofstream map_file(map_path);

    if (!map_file.is_open()) 
        cerr << "Error while opening the file : " << map_path << endl;

    else {

        map_file << map_music_->GetBpm() << endl;

        for (const string& line : *map_queue_)
            map_file << line << endl;

        map_file.close();

    }

}

void Map::Display() const {

    for (const string& element : *map_queue_)
        cout << element << endl;

}

string Map::GetNextTileTypeToDisplay() const {

    return map_queue_->front();

}

void Map::PopNewTile(){

    map_queue_->pop_front();

}

bool Map::IsEmpty() const{

    return map_queue_->empty();

}

void Map::UpdateMusic(){

    map_music_->Update();

}

void Map::PlayMusic(){

    map_music_->PlayMusic();

}

void Map::PauseMusic(const bool& is_paused){

    map_music_->PauseMusic(is_paused);

}

void Map::PlaySoundEffect(){

    map_music_->PlaySoundEffect();

}

float Map::GetMusicBpm() const{

    return map_music_->GetBpm();

}

float Map::GetMusicSecondsPerBeat() const{

    return map_music_->GetSecondsPerBeat();

}
