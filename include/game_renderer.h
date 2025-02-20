#ifndef PROJECT_INC_GAMERENDERER_H
#define PROJECT_INC_GAMERENDERER_H

#include <iostream>
#include <memory>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#include "image.h"
#include "tile.h"
#include "level.h"
#include "button.h"
#include "text.h"

using namespace std;

/**
 * @brief Classe gérant le rendu du jeu.
 */
class GameRenderer{
public:

    /**
     * @brief Constructeur par défaut de la classe GameRenderer.
     */
    GameRenderer();

    /**
     * @brief Destructeur de la classe GameRenderer.
     */
    ~GameRenderer();

    /**
     * @brief Fonction pour traiter l'appui sur une touche.
     *        Regarde si le joueur est en rythme, et met à jour la 
     *        donnée membre rythm_.
     */
    void IfKeyDown();

    /**
     * @brief Fonction pour traiter le clic de la souris sur un bouton.
     * @param button_name Le nom du bouton sur lequel la souris a cliqué.
     * @param event L'événement SDL de la souris.
     * @return true si le bouton a été cliqué, false sinon.
     */
    bool IfMouseButtonDown(const string& button_name, const SDL_Event& event);

    /**
     * @brief Initialise le menu principal.
     */
    void InitMenu();

    /**
     * @brief Affiche le menu principal.
     */
    void RenderMenu();

    /**
     * @brief Retire le menu principal de l'écran.
     */
    void DerenderMenu();

    /**
     * @brief Initialise le niveau.
     * @param level_number Le numéro du niveau à initialiser.
     */
    void InitLevel(const string& level_number);

    /**
     * @brief Met à jour le niveau actuel.
     */
    void UpdateLevel();

    /**
     * @brief Affiche le niveau sur la fenêtre graphique.
     * @param is_paused Indique si le jeu est en pause ou non.
     */
    void RenderLevel(const bool& is_paused);

    /**
     * @brief Démarre le niveau.
     */
    void StartLevel();

    /**
     * @brief Redémarre le niveau actuel.
     */
    void RestartLevel();

    /**
     * @brief Met en pause ou reprend le niveau.
     * @param is_paused true pour mettre en pause, false pour reprendre.
     */
    void PauseLevel(const bool& is_paused);

    /**
     * @brief Vérifie si le niveau est terminé.
     * @param finished Référence booléenne pour indiquer si le niveau est terminé.
     */
    void CheckIfLevelFinished(bool& finished) const;

    /**
     * @brief Lance un compte à rebours avant le début du niveau.
     */
    void Countdown();

    /**
     * @brief Définit le niveau actuel.
     * @param current_level Le numéro du niveau à définir comme actuel.
     */
    void SetCurrentLevel(const string& current_level);

private:

    SDL_Renderer* renderer_; ///< Le moteur de rendu.
    SDL_DisplayMode* displaymode_; ///< Le mode d'affichage.
    SDL_Window* window_; ///< La fenêtre du jeu.

    string current_level_; ///< Le niveau en cours.

    TTF_Font* font_; ///< La police de caractères pour le texte.

    Text* score_; ///< Le texte affichant le score du joueur.
    Text* life_; ///< Le texte affichant le nombre de vies restantes.
    Image* life_image_; ///< L'image représentant une vie.
    Text* rythm_; ///< Le texte affichant si le joueur est en rythme.

    Level* level_; ///< Le niveau en cours.
    Image* level_background_; ///< L'arrière-plan du niveau.

    Image* pause_image_; ///< L'image affichée lorsque le jeu est mis en pause.
    Button* restart_button_; ///< Le bouton pour redémarrer le niveau.
    Button* go_back_button_; ///< Le bouton pour revenir au menu principal.

    Image* menu_background_; ///< L'arrière-plan du menu principal.

    Button* level_1_button_; ///< Le bouton dans le menu pour le niveau 1.
    Button* level_2_button_; ///< Le bouton dans le menu pour le niveau 2.

    Button* quit_button_; ///< Le bouton dans le menu pour quitter le jeu.

    string img_tile_path_; ///< Le chemin vers les images des tuiles.
    string img_extension_; ///< L'extension des fichiers d'images.

    
};

#endif