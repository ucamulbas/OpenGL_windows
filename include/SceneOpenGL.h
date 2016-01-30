#ifndef SCENEOPENGL
#define SCENEOPENGL

#ifdef WIN32
#include <GL/glew.h>

#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>

#endif
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>


#include "../include/Shader.h"
#include "../include/Objet.h"

// Classe
class SceneOpenGL
{
    public:

    SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre);
    ~SceneOpenGL();

    bool initialiserFenetre();
    bool initGL();
    void bouclePrincipale();

    //exemple 2 étages, le premier de 3 données et le 2ème de 2 données, nbDonneeEtage sera {3, 2}
    void ajouteObjet(float *data, int nombreSommets, int nbEtageActive, int *nbDonneeEtage, int taille);
    void dessineObjet(int vao);
    //void initData(void);

    private:

    std::string m_titreFenetre;
    int m_largeurFenetre;
    int m_hauteurFenetre;

    std::vector<Objet> m_objet;

    SDL_Window* m_fenetre;
    SDL_GLContext m_contexteOpenGL; 
    SDL_Event m_evenements;
};

#endif