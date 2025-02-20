#ifndef PROJECT_INC_TEXT_H
#define PROJECT_INC_TEXT_H

#include <iostream>

#include "SDL.h"
#include "SDL_ttf.h"

using namespace std;

/**
 * @brief Classe représentant un texte rendu à l'écran.
 */
class Text {
public:

    /**
     * @brief Constructeur de la classe Text.
     * 
     * @param renderer Le renderer SDL pour créer la texture du texte.
     * @param color La couleur du texte.
     * @param font La police du texte.
     * @param x_pos La position en x du texte.
     * @param y_pos La position en y du texte.
     * @param width La largeur du texte.
     * @param height La hauteur du texte.
     * @param initial_value La valeur initiale du texte.
     */
    Text(SDL_Renderer* renderer, const SDL_Color& color, TTF_Font* font, 
         const float& x_pos, const float& y_pos, 
         const int& width, const int& height, 
         const string& initial_value);

    /**
     * @brief Destructeur de la classe Text.
     */
    ~Text();

    /**
     * @brief Met à jour le texte avec une nouvelle valeur.
     * 
     * @param renderer Le renderer SDL pour mettre à jour la texture du texte.
     * @param value La nouvelle valeur du texte.
     */
    void Update(SDL_Renderer* renderer, const string& value);

    /**
     * @brief Rend le texte sur l'écran.
     * 
     * @param renderer Le renderer SDL pour afficher le texte.
     */
    void Render(SDL_Renderer* renderer);

    /**
     * @brief Change les coordonnées du texte.
     * 
     * @param x_pos La nouvelle position en x du texte.
     * @param y_pos La nouvelle position en y du texte.
     */
    void ChangeCoordinates(const float& x_pos, const float& y_pos);

private:


    SDL_Surface* text_surface_; ///< Surface du texte.
    SDL_Texture* text_texture_; ///< Texture du texte.
    SDL_Rect* text_rectangle_; ///< Rectangle positionnant le texte.

    SDL_Color color_; ///< Couleur du texte.
    TTF_Font* font_; ///< Police du texte.

    float x_pos_; ///< Position en x du texte.
    float y_pos_; ///< Position en y du texte.

    Uint16 width_; ///< Largeur du texte.
    Uint16 height_; ///< Hauteur du texte.

};

#endif