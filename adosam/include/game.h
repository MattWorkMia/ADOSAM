#ifndef PROJECT_INC_GAME_H
#define PROJECT_INC_GAME_H

#include <memory>

#include "SDL.h"

#include "game_renderer.h"

/**
 * @brief Classe gérant le déroulement du jeu.
 */
class Game {
public:
    
    /**
     * @brief Constructeur par défaut de la classe Game.
     */
    Game();

    /**
     * @brief Destructeur de la classe Game.
     */
    ~Game();

    /**
     * @brief Lance le jeu. Contient la boucle principale.
     */
    void Run();

    /**
     * @brief Gère les événements de souris et les traite.
     *        Teste pour chaque bouton s'il a été cliqué. 
     */
    void ProcessMouseButton();

    /**
     * @brief Gère les événements de clavier et les traite.
     *        Arrête le jeu sur appui de la touche ESCAPE, 
     *        Met le jeu en pause sur appui de la touche p, 
     *        Avance le joueur sur appui de toute autre touche.
     */
    void ProcessKeyboard();

    /**
     * @brief Fonction qui appelle la mise à jour du niveau et de son rendu 
     *        quand le joueur est dans un niveau.
     */
    void IfInGame();

private:

    SDL_Event event_; ///< Événement SDL.

    GameRenderer* game_renderer_; ///< Pointeur vers le moteur de rendu du jeu.

    bool is_running_; ///< Indique si le jeu est en cours d'exécution.
    
    bool is_in_game_; ///< Indique si le joueur est dans un niveau.
    
    bool is_paused_; ///< Indique si le jeu est en pause.

    bool is_finished_; ///< Indique si le jeu est fini.

};

#endif