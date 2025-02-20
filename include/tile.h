#ifndef PROJECT_INC_TILES_H
#define PROJECT_INC_TILES_H

#include <string>
#include <iostream>

#include "SDL.h"

#include "image.h"

using namespace std;

/**
 * @brief Classe représentant une tuile.
 */
class Tile : public Image {
public:

    /**
     * @brief Constructeur de la classe Tile.
     * @param file_path Le chemin vers le fichier image représentant la tuile.
     * @param x_pos La position en abscisse de la tuile.
     * @param y_pos La position en ordonnée de la tuile.
     * @param width La largeur de la tuile.
     * @param height La hauteur de la tuile.
     * @param tile_type Le type de la tuile.
     * @param direction La direction de la tuile.
     */
    Tile(const string& file_path, const float& x_pos, const float& y_pos, 
         const int& width, const int& height, const string& tile_type,
         const string& direction);

    /**
     * @brief Destructeur de la classe Tile.
     */
    ~Tile();

    /**
     * @brief Détermine la direction de la tuile suivante.
     * @param next_tile_type Le nom de la tuile suivante.
     * @return La direction de la prochaine tuile.
     */
    string DetermineNextDirection(const string& next_tile_type);

    /**
     * @brief Détermine les coordonnées de la tuile suivante.
     * @param next_tile_type Le nom de la tuile suivante.
     * @param next_tile_x_pos La position en abscisse de la tuile suivante.
     * @param next_tile_y_pos La position en ordonnée de la tuile suivante.
     */
    void DetermineNextTileCoordinates(const string& next_tile_type,
                                      float& next_tile_x_pos, 
                                      float& next_tile_y_pos) const;

    /**
     * @brief Vérifie si la tuile est verticale.
     * @return true si la tuile est verticale, false sinon.
     */
    bool IsVertical() const;

    /**
     * @brief Vérifie si la tuile est horizontale.
     * @return true si la tuile est horizontale, false sinon.
     */
    bool IsHorizontal() const;

    /**
     * @brief Vérifie si la tuile est un coin.
     *        Correspond à une tuile dont la partie gauche a une direction 
     *        différente de la partie droite.
     * @return true si la tuile est un coin, false sinon.
     */
    bool IsCorner() const;

    /**
     * @brief Vérifie si la tuile est un coin vers le haut.
     *        Une tuile est un coin vers le haut si le coin est situé au-dessus 
     *        de la partie horizontale de la tuile.
     * @return true si la tuile est un coin vers le haut, false sinon.
     */
    bool IsUpCorner() const;

    /**
     * @brief Vérifie si la tuile est un coin vers le bas.
     *        Une tuile est un coin vers le bas si le coin est situé en-dessous 
     *        de la partie horizontale de la tuile.
     * @return true si la tuile est un coin vers le bas, false sinon.
     */
    bool IsDownCorner() const;

    /**
     * @brief Vérifie si la tuile est une tuile de fin.
     * @return true si la tuile est une tuile de fin, false sinon.
     */
    bool IsEnd() const;

    /**
     * @brief Vérifie si la tuile est une tuile de changement de sens de rotation.
     * @return true si la tuile est une tuile de changement de sens de rotation, 
     *         false sinon.
     */
    bool IsSwirl() const;

    /**
     * @brief Vérifie si la tuile est une tuile d'accélération.
     * @return true si la tuile est une tuile d'accélération, false sinon.
     */
    bool IsSpeed() const;

    /**
     * @brief Vérifie si la tuile est une tuile de ralentissement.
     * @return true si la tuile est une tuile de ralentissement, false sinon.
     */
    bool IsSlow() const;

    /**
     * @brief Obtient les coordonnées du centre de la tuile.
     * @param x_pos Réel qui devient la coordonnée en abscisse du centre.
     * @param y_pos Réel qui devient la coordonnée en ordonnée du centre.
     */
    void GetCenter(float& x_pos, float& y_pos) const;

private:

    /**
     * @brief Énumération représentant les types de tuiles.
     */
    enum Types_ { HORIZONTAL, DOWN_LEFT, UP_LEFT, DOWN_RIGHT, 
                  UP_RIGHT, VERTICAL, SWIRL, SPEED, SLOW, END
                };

    /**
     * @brief Obtient le type de la tuile.
     * @param type Le nom (sous forme de chaîne) de la tuile.
     * @return Le type de la tuile.
     */
    Types_ GetType(const std::string& type) const;

    Types_ tile_type_; ///< Le type de la tuile.
    std::string direction_; ///< La direction de la tuile.

};

#endif