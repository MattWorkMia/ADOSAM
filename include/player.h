#ifndef PROJECT_INC_PLAYER_H
#define PROJECT_INC_PLAYER_H

#include "SDL.h"

#include "image.h"
#include "tile.h"

#include <deque>

using namespace std;

/**
 * @brief Classe gérant le joueur.
 */
class Player {
public:

    /**
     * @brief Constructeur de la classe Player.
     * @param display_mode Pointeur vers le mode d'affichage SDL.
     * @param bpm Battements par minute utilisé pour le calcul de la vitesse de 
     *            rotation.
     */
    Player(SDL_DisplayMode* display_mode, 
           const unsigned int& bpm);

    /**
     * @brief Destructeur de la classe Player.
     */
    ~Player();

    /**
     * @brief Affiche le soleil et la lune sur la fenêtre graphique.
     * @param renderer Le renderer SDL sur lequel afficher.
     */
    void Render(SDL_Renderer* renderer);

    /**
     * @brief Met à jour la rotation du soleil ou de la lune, selon celui qui 
     *        est en rotation actuellement.
     */
    void UpdateRotation();

    /**
     * @brief Fait défiler le joueur selon les décalages spécifiés.
     * @param x_diff Décalage horizontal.
     * @param y_diff Décalage vertical.
     */
    void Scroll(const float& x_diff, const float& y_diff);

    /**
     * @brief Fait rotater le soleil autour de la lune.
     */
    void RotateSun();

    /**
     * @brief Fait rotater la lune autour du soleil.
     */
    void RotateMoon();

    /**
     * @brief Change le centre de rotation (lune <-> soleil).
     */
    void ChangeRotation();

    /**
     * @brief Inverse la direction de rotation du joueur.
     */
    void ReverseRotation();

    /**
     * @brief Accélère la vitesse de rotation du joueur.
     */
    void SpeedUp();

    /**
     * @brief Ralentit la vitesse de rotation du joueur.
     */
    void SlowDown();

    bool IsSunRotating() const;

    /**
     * @brief Déplace le joueur vers la tuile suivante.
     * @param next_x_pos Position en x de la prochaine tuile.
     * @param next_y_pos Position en y de la prochaine tuile.
     * @param next_is_vertical Indique si la prochaine tuile est verticale.
     * @param next_is_up_corner Indique si la prochaine tuile est un coin vers 
     *                          le haut.
     */
    void MovePlayerToNextTile(const float& next_x_pos, const float& next_y_pos, 
                              const bool& next_is_vertical,
                              const bool& next_is_up_corner);

    /**
     * @brief Calcule la distance du point donné au centre du soleil.
     * @param x Position en x du point.
     * @param y Position en y du point.
     * @return Distance du point au centre du soleil.
     */
    float GetSunDistanceFromPoint(const float& x, const float& y) const;

    /**
     * @brief Calcule la distance du point donné au centre de la lune.
     * @param x Position en x du point.
     * @param y Position en y du point.
     * @return Distance du point au centre de la lune.
     */
    float GetMoonDistanceFromPoint(const float& x, const float& y) const;

    

private:

    unique_ptr<Image> sun_; ///< Image du soleil.
    unique_ptr<Image> moon_; ///< Image de la lune.

    float rotation_speed_; ///< Vitesse de rotation du joueur.
    bool is_sun_rotating_; ///< Indique si le soleil est en rotation autour de la lune.

};

#endif