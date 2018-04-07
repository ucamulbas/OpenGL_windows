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
	
	float vertices[] = {
		-0.5, -0.5, 0.0,   
		-0.5, 0.5, 0.0,   
		0.5, -0.5, 0.0,  
		0.5, 0.5, 0.0,
	
		0.0, 0.0,
		0.0, 1.0, 
		1.0, 0.0,
		1.0, 1.0
	};


	int optionVertices[] = { 3, 2 };
	Objet face(vertices, 4, 2, optionVertices, 20);

	face.SetTexture("images/caisse.jpg");
	face.SetShader("Shaders/texture.vs", "Shaders/texture.fs");

	
	scene.ajouteObjet(face);

	// Boucle Principale
	scene.bouclePrincipale();
	// Fin du programme
	return 0;
}

