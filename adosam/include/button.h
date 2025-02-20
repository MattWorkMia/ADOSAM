#ifndef PROJECT_INC_BUTTON_H
#define PROJECT_INC_BUTTON_H

#include "SDL.h"
#include "image.h"

using namespace std;

/**
 * @brief Classe représentant un bouton, héritant de la classe Image.
 */
class Button : public Image {
public:

    /**
     * @brief Constructeur de la classe Button.
     * 
     * @param file_path Chemin d'accès du fichier image du bouton.
     * @param x_pos Position x du bouton.
     * @param y_pos Position y du bouton.
     * @param width Largeur du bouton.
     * @param height Hauteur du bouton.
     */
    Button(const string& file_path, 
           const float& x_pos, const float& y_pos, 
           const int& width, const int& height);
    
    /**
     * @brief Destructeur de la classe Button.
     */
    ~Button();

    /**
     * @brief Vérifie si le bouton a été cliqué.
     * 
     * @param event Événement SDL.
     * @return true si le bouton a été cliqué.
     * @return false sinon.
     */
    bool CheckIfClicked(const SDL_Event& event);

};

#endif