#ifndef PROJECT_INC_CONDUCTOR_H
#define PROJECT_INC_CONDUCTOR_H

#include <iostream>
#include <string>

#include "SDL.h"
#include "SDL_mixer.h"

using namespace std;


/**
 * @brief Classe gérant la musique et les effets sonores du jeu.
 */
class Conductor {
public:

    /**
     * @brief Constructeur de la classe Conductor.
     * 
     * @param music_bpm Le tempo de la musique en battements par minute.
     * @param level_folder_path Le chemin du dossier contenant les fichiers audio.
     */
    Conductor(const float& music_bpm, 
              const string& music_path);

    ~Conductor();

    /**
     * @brief Charge les fichiers audio et initialise les canaux audio.
     */
    void Load();

    /**
     * @brief Libère les ressources audio et arrête tous les sons en cours de lecture.
     */
    void Unload();

    /**
     * @brief Joue la musique du niveau.
     */
    void PlayMusic();

    /**
     * @brief Met en pause ou reprend la lecture de la musique.
     * 
     * @param is_paused Booléen indiquant si la musique doit être mise en pause 
     *                  (true) ou reprise (false).
     */
    void PauseMusic(const bool& is_paused);

    /**
     * @brief Joue l'effet sonore utilisé dans le Countdown du début du niveau.
     */
    void PlaySoundEffect();

    /**
     * @brief Met à jour la position de lecture de la musique.
     */
    void Update();

    float GetBpm() const;

    float GetSecondsPerBeat() const;

private:

    Mix_Chunk* music_; ///< Pointeur vers le fichier audio de la musique.
    Mix_Chunk* sound_effect_; ///< Pointeur vers le fichier audio de l'effet sonore.

    string level_folder_path_; ///< Chemin du dossier contenant les fichiers audio du niveau.

    Uint32 start_time_; ///< Temps de départ de la lecture de la musique.

    float bpm_; ///< Tempo de la musique en battements par minute.
    float seconds_per_beat_; ///< Durée en secondes d'un battement musical.
    double music_position_; ///< Position de lecture actuelle de la musique en secondes.

};

#endif