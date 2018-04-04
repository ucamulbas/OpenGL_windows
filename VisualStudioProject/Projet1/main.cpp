#include "include\SceneOpenGL.h"

int SDL_main(int argc, char*argv[])
{
	// Création de la sène
	SceneOpenGL scene("OpenGL", 800, 600);

	// Initialisation de la scène
	if (scene.initialiserFenetre() == false)
		return -1;

	if (scene.initGL() == false)
		return -1;
	
	float vertices[] = { -0.5, 0.0,   0.0, 1.0,   0.5, 0.0,
		240.0 / 255.0, 210.0 / 255.0, 23.0 / 255.0,
		230.0 / 255.0, 0.0, 230.0 / 255.0,
		0.0, 1.0, 0.0 };


	int optionVertices[] = { 2, 3 };
	scene.ajouteObjet(vertices, 3, 2, optionVertices, 15);

	// Boucle Principale
	scene.bouclePrincipale();
	// Fin du programme
	return 0;
}

