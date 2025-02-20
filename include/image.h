#ifndef PROJECT_INC_IMAGE_H
#define PROJECT_INC_IMAGE_H

#include "SDL.h"
#include "SDL_image.h"

#include <iostream>
#include <memory>
#include <string>

using namespace std;

/**
 * @brief Classe représentant une image chargée depuis un fichier.
 */
class Image {
public:

    /**
     * @brief Constructeur de la classe Image.
     * 
     * @param file_path Chemin vers le fichier image.
     * @param x_pos Position x de l'image.
     * @param y_pos Position y de l'image.
     * @param width Largeur de l'image.
     * @param height Hauteur de l'image.
     */
    Image(const string& file_path, const float& x_pos, const float& y_pos,
          const int& width, const int& height);

    /**
     * @brief Destructeur de la classe Image.
     */
    ~Image();

    /**
     * @brief Charge l'image, en gérant les potentielles erreurs.
     * 
     * @param renderer Le renderer SDL utilisé pour créer la texture.
     */
    void Load(SDL_Renderer* renderer);

    /**
     * @brief Décharge l'image de la mémoire.
     */
    void Unload();

    /**
     * @brief Affiche l'image sur l'écran, en gérant les potentielles erreurs.
     * 
     * @param renderer Le renderer SDL utilisé pour le rendu.
     */
    void Render(SDL_Renderer* renderer);

    /**
     * @brief Initialise le rectangle utilisé pour le rendu avec 
     *        les données membres de la classe.
     */
    void InitiateRectangle();

    /**
     * @brief Met à jour les coordonnées du rectangle utilisé pour le rendu.
     */
    void UpdateRectangleCoordinates();

    float GetXPos() const;

    float GetYPos() const;

    Uint16 GetWidth() const;

    Uint16 GetHeight() const;

    void SetXPos(const float& x_pos);

    void SetYPos(const float& y_pos);

    void SetWidth(const float& width);

    void SetHeight(const float& height);

    bool IsRendered() const;

    void Derender();

private:

    SDL_Surface* surface_; ///< Le surface SDL utilisé pour charger l'image.
    SDL_Texture* texture_; ///< Le texture SDL utilisé pour le rendu de l'image.
    SDL_Rect* rectangle_; ///< Le rectangle SDL utilisé pour le rendu de l'image.

    string file_path_; ///< Le chemin vers le fichier image.

    float x_pos_; ///< La position en x de l'image.
    float y_pos_; ///< La position en y de l'image.

    bool is_rendered_;

    Uint16 width_; ///< La largeur de l'image.
    Uint16 height_; ///< La hauteur de l'image.
    
};

#endif