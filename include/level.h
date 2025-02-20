#ifndef PROJECT_INC_LEVEL_H
#define PROJECT_INC_LEVEL_H

#include "SDL_ttf.h"

#include "map.h"
#include "tile.h"
#include "player.h"
#include <deque>
#include "chrono"

using namespace std;

const int FRAMERATE = 60;

/**
 * @brief Classe représentant un niveau du jeu.
 * 
 * La classe Level gère le déroulement d'un niveau du jeu. Elle charge les tuiles à partir
 * d'un dossier spécifié, les affiche, contrôle le mouvement du joueur et applique les effets
 * des différentes tuiles sur le joueur.
 */
class Level{
public:

    /**
     * @brief Constructeur de la classe Level.
     * 
     * @param img_tile_path Le chemin vers les images des tuiles.
     * @param img_extension L'extension des images des tuiles.
     * @param level_folder_path Le chemin vers le dossier contenant les données du niveau.
     * @param displaymode Le mode d'affichage de la fenêtre SDL.
     */
    Level(const string& img_tile_path, 
          const string& img_extension, const string& level_folder_path, 
          SDL_DisplayMode* displaymode);

    /**
     * @brief Destructeur de la classe Level.
     */
    ~Level();

    /**
     * @brief Charge les données du niveau à partir du dossier spécifié.
     *        Initialise la carte, le joueur, et la première tuile.
     * 
     * @param level_folder_path Le chemin vers le dossier contenant les données 
     *                          du niveau.
     */
    void Load(const string& level_folder_path);

    /**
     * @brief Charge de nouvelles tuiles pour préparer leur affichage, jusqu'à 
     *        ce qu'il n'y ait plus de tuiles à initialiser.
     */
    void LoadNewTiles();

    /**
     * @brief Décharge les tuiles qui ne sont plus visibles à l'écran.
     */
    void UnloadOutOfScreenTiles();

    /**
     * @brief Affiche le niveau.
     * 
     * @param renderer Le moteur de rendu SDL sur lequel afficher le niveau.
     */
    void Render(SDL_Renderer* renderer);

    /**
     * @brief Démarre le niveau.
     */
    void Start();

    /**
     * @brief Met en pause ou reprend le niveau selon l'état spécifié.
     * 
     * @param is_paused Booléen indiquant si le niveau doit être mis en pause.
     */
    void Pause(const bool& is_paused);

    /**
     * @brief Met à jour le niveau.
     *        Met à jour le joueur, la musique, les tuiles, et l'état du joueur 
     *        (en vie ou non).
     */
    void Update();

    /**
     * @brief Ajoute une tuile à afficher dans la file d'affichage.
     * 
     * @param tile_to_add La tuile à ajouter.
     */
    void AddTileToDisplay(Tile* tile_to_add);

    /**
     * @brief Met à jour la position des tuiles affichées.
     */
    void UpdateTilesPosition();

    /**
     * @brief Vérifie si la tuile suivante est affichable.
     * 
     * @param current_tile La tuile actuelle.
     * @param next_tile_type Le nom de la tuile suivante.
     * @return true si la tuile suivante est affichable, false sinon.
     */
    bool IsNextTileRenderable(const Tile& current_tile, 
                              const string& next_tile_type);

    /**
     * @brief Vérifie si une tuile est en dehors de l'écran.
     * 
     * @param tile La tuile à vérifier.
     * @return true si la tuile est en dehors de l'écran, false sinon.
     */
    bool IsTileOutOfScreen(const Tile& tile) const;

    /**
     * @brief Retourne la tuile la plus ancienne actuellement affichée.
     * 
     * @return Un pointeur vers la tuile la plus ancienne.
     */
    Tile* GetOldestDisplayedTile() const;

    /**
     * @brief Retourne la dernière tuile affichée.
     * 
     * @return Un pointeur vers la dernière tuile affichée.
     */
    Tile* GetCurrentTile() const;

    /**
     * @brief Retire la tuile la plus ancienne de la file d'affichage.
     */
    void PopOldestDisplayedTile();

    /**
     * @brief Déplace le joueur vers la tuile suivante.
     */
    void MoveToNextTile();

    /**
     * @brief Applique l'effet de la tuile actuelle sur le joueur.
     */
    void ApplyTileEffect();

    /**
     * @brief Met à jour le défilement de l'écran.
     * 
     * @param current_tile La tuile actuelle.
     * @param next_tile La tuile suivante.
     */
    void UpdateScrolling(Tile* current_tile, Tile* next_tile);

    /**
     * @brief Vérifie si le joueur est sur la tuile suivante.
     * 
     * @return true si le joueur est sur la tuile suivante, false sinon.
     */
    bool IsPlayerOnNextTile() const;

    /**
     * @brief Calcule la distance entre le joueur et la tuile suivante.
     *        Correspond à la distance entre l'astre en rotation et le centre 
     *        de la tuile suivante.
     * 
     * @return La distance entre le joueur et la tuile suivante.
     */
    float GetDistanceFromNextTile() const;

    /**
     * @brief Vérifie l'exactitude de l'input du joueur par rapport au rythme 
     *        du niveau.
     * 
     * @param rythm_text Le texte indiquant si le joueur est en rythme.
     * @param tile_x La position en x de la tuile actuelle.
     * @param tile_y La position en y de la tuile actuelle.
     */
    void CheckPlayerAccuracy(string& rythm_text, float& tile_x, float& tile_y);

    int GetScore() const;

    int GetLife() const;

    bool IsFinished() const;

    /**
     * @brief Joue l'effet sonore associé au Countdown du début de niveau.
     */
    void PlaySoundEffect();

    float GetMusicSecondsPerBeat() const;

private:

    SDL_DisplayMode* displaymode_; ///< Le mode d'affichage de la fenêtre SDL.

    Map* map_; ///< La carte du niveau.
    Player* player_; ///< Le joueur.

    ///< La file des tuiles affichées.
    deque<Tile*>* displayed_tiles_;
    ///< Itérateur pour la tuile sur laquelle le joueur se trouve actuellement.
    deque<Tile*>::iterator level_position_;

    ///< Point dans le temps pour le délai d'entrée.
    chrono::time_point<chrono::high_resolution_clock> input_delay_;

    string tile_image_path_; ///< Le chemin vers les images de tuiles.
    string image_extension_; ///< L'extension des images de tuiles.

    float scroll_x_diff_; ///< La différence en coordonnée x pour le défilement.
    float scroll_y_diff_; ///< La différence en coordonnée y pour le défilement.
    float scroll_speed_; ///< La vitesse de défilement.

    int score_; ///< Le score du joueur.
    int life_; ///< Les vies restantes du joueur.

    bool has_moved_; ///< Indique si le joueur s'est déplacé.
    bool finished_; ///< Indique si le niveau est terminé.
    
};


#endif