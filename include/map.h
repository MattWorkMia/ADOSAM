#ifndef PROJECT_INC_MAP_H
#define PROJECT_INC_MAP_H

#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <memory> 

#include "conductor.h"

using namespace std;

/**
 * @brief Classe représentant la carte d'un niveau du jeu. Un niveau contient 
 *        une seule carte.
 */
class Map {
public:

    /**
     * @brief Constructeur de la classe Map.
     * 
     * @param level_folder_path Chemin du dossier contenant les fichiers du niveau.
     */
    Map(const string& level_folder_path);

    /**
     * @brief Destructeur de la classe Map.
     */
    ~Map();

    /**
     * @brief Charge les données de la carte à partir d'un fichier.
     *        Ces données sont le BPM de la musique, et les noms des tuiles 
     *        qui sont mis dans la file map_queue_.
     * 
     * @param map_path Chemin du fichier de la carte.
     * @param level_folder_path Chemin du dossier contenant les fichiers du niveau.
     */
    void FileToMap(const string& map_path, const string& level_folder_path);

    /**
     * @brief Sauvegarde les données de la carte dans un fichier.
     *        La première ligne sera le BPM de la musique du niveau, puis les 
     *        noms des tuiles de la file map_queue_.
     * 
     * @param map_path Chemin du fichier de la carte.
     */
    void MapToFile(const string& map_path) const;

    /**
     * @brief Affiche dans l'ordre les tuiles de la carte sur la sortie standard.
     */
    void Display() const;

    /**
     * @brief Obtient le nom de la prochaine tuile à afficher.
     * 
     * @return Nom de la prochaine tuile à afficher.
     */
    string GetNextTileTypeToDisplay() const;

    /**
     * @brief Retire la première tuile de la file, qui est la prochaine tuile 
     *        à afficher.
     */
    void PopNewTile();

    /**
     * @brief Vérifie s'il n'y a plus de tuiles à afficher, 
     *        c'est à dire si map_queue_ est vide.
     * 
     * @return true s'il n'y a plus de tuiles à afficher, false sinon.
     */
    bool IsEmpty() const;

    float GetMusicBpm() const;

    float GetMusicSecondsPerBeat() const;

    /**
     * @brief Met à jour la position de lecture de la musique de la carte.
     */
    void UpdateMusic();

    /**
     * @brief Joue la musique de la carte.
     */
    void PlayMusic();

    /**
     * @brief Met en pause ou reprend la lecture de la musique de la carte.
     * 
     * @param is_paused Booléen indiquant si la musique doit être mise en pause.
     */
    void PauseMusic(const bool& is_paused);

    /**
     * @brief Joue l'effet sonore du Countdown de la carte.
     */
    void PlaySoundEffect();

private:

    Conductor* map_music_; ///< Pointeur vers le conducteur de la musique de la carte.
    
    deque<string>* map_queue_; ///< File contenant les tuiles de la carte. 

};
 
#endif