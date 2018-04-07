#ifndef SCENEOPENGL
#define SCENEOPENGL

#include <GL/glew.h>

#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>


#include "Shader.h"
#include "Objet.h"
#include "Cam.h"
#include "Input.h"


class SceneOpenGL
{
    public:

    SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre);
    ~SceneOpenGL();

    bool initialiserFenetre();
    bool initGL();
    void bouclePrincipale();

    //exemple 2 étages, le premier de 3 données et le 2ème de 2 données, nbDonneeEtage sera {3, 2}
    void ajouteObjet(float data[], int nombreSommets, int nbEtageActive, int *nbDonneeEtage, int taille);
	void ajouteObjet(Objet obj);

    std::vector<Objet> m_objet;
    SDL_Window* m_fenetre;
    SDL_Event m_evenements;

    private:

    std::string m_titreFenetre;
    int m_largeurFenetre;
    int m_hauteurFenetre;
	Input m_input;

    SDL_GLContext m_contexteOpenGL; 
};

#endif