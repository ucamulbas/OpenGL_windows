#include "../include/SceneOpenGL.h"

int main(void)

{
    // Création de la sène
    SceneOpenGL scene("Chapitre 3", 800, 600);

    // Initialisation de la scène
    if(scene.initialiserFenetre() == false)
        return -1;

    if(scene.initGL() == false)
     return -1;

    float vertices[] = {-0.5, -0.5,   0.0, 0.5,   0.5, -0.5};
    float test[] = {-1.5,0.0,   -1.5, 1.5,    0.0,0.0};
    
    scene.ajouteObjet(vertices, 3, 1, new int[1]{2}, 6);
    scene.ajouteObjet(test, 3, 1, new int[1]{2}, 6);

    // Boucle Principale
    scene.bouclePrincipale();
    // Fin du programme
    return 0;
}