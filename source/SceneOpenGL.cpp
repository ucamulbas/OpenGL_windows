#include "../include/SceneOpenGL.h"

SceneOpenGL::SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre) : 
  	m_titreFenetre(titreFenetre), m_largeurFenetre(largeurFenetre), m_hauteurFenetre(hauteurFenetre), m_fenetre(0), m_contexteOpenGL(0)
{}

void SceneOpenGL::ajouteObjet(float data[], int nombreSommets, int nbEtageActive, int *nbDonneeEtage, int taille)
{
	GLuint vao;
	GLuint buff;

	float vertices[taille];
	for(int i = 0; i < taille; i++)
		vertices[i] = data[i];

	Objet objet(vertices, nombreSommets, nbEtageActive, nbDonneeEtage, taille);

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &buff);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, buff);
	glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);

	int size = 0;
	for(int i = 0; i< nbEtageActive; i++)
	{
		glEnableVertexAttribArray(i);
		if(i==0)
			glVertexAttribPointer(i, nbDonneeEtage[i], GL_FLOAT, GL_FALSE, 0, 0);
		else
		{
      std::cout << "size : " << size << "  ->  " << nombreSommets << " * " << nbDonneeEtage[i-1] << " = " << size + nombreSommets * nbDonneeEtage[i-1] << std::endl;
			size += nombreSommets * nbDonneeEtage[i-1];
			glVertexAttribPointer(i, nbDonneeEtage[i], GL_FLOAT, GL_FALSE, 0, (const void *)(size * sizeof *vertices));
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
  	glBindVertexArray(0);
  	objet.m_vao = vao;
  	m_objet.push_back(objet);

}

SceneOpenGL::~SceneOpenGL()
{
   	SDL_GL_DeleteContext(m_contexteOpenGL);
   	SDL_DestroyWindow(m_fenetre);
   	SDL_Quit();
}

bool SceneOpenGL::initialiserFenetre()
{
    	// Initialisation de la SDL
    	if(SDL_Init(SDL_INIT_VIDEO) < 0)
    	{

        	std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
       		SDL_Quit();

        	return false;
    	}

        // Version d'OpenGL
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	    // Double Buffer
	    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    
    	// Création de la fenêtre
	    m_fenetre = SDL_CreateWindow(m_titreFenetre.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_largeurFenetre, m_hauteurFenetre, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	    if(m_fenetre == 0)
    	{
        	std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
        	SDL_Quit();

        	return false;
    	}
    	// Création du contexte OpenGL
    	m_contexteOpenGL = SDL_GL_CreateContext(m_fenetre);

    	if(m_contexteOpenGL == 0)
    	{
       		std::cout << SDL_GetError() << std::endl;
       		SDL_DestroyWindow(m_fenetre);
       		SDL_Quit();

       		return false;
   		}

    	return true;
} 

bool SceneOpenGL::initGL()
{
    	#ifdef WIN32
        // On initialise GLEW
        GLenum initialisationGLEW(glewInit());
        // Si l'initialisation a échoué :
        if(initialisationGLEW != GLEW_OK)
        {
            // On affiche l'erreur grâce à la fonction : glewGetErrorString(GLenum code)
            std::cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(initialisationGLEW) << std::endl;

            // On quitte la SDL
            SDL_GL_DeleteContext(m_contexteOpenGL);
            SDL_DestroyWindow(m_fenetre);
            SDL_Quit();

            return false;
        }
	    #endif
        // Tout s'est bien passé, on retourne true
	    return true;
}

void SceneOpenGL::bouclePrincipale()
{
	// Variables
    bool terminer(false);
    
    Shader shaderBasique("Shaders/couleur2D.vert", "Shaders/couleur2D.frag");
    shaderBasique.charger();

   	// Boucle principale
   	while(!terminer)
   	{
       	// Gestion des évènements
       	SDL_WaitEvent(&m_evenements);
       	if(m_evenements.window.event == SDL_WINDOWEVENT_CLOSE)
          	terminer = 1;

       	// Nettoyage de l'écran
       	glClear(GL_COLOR_BUFFER_BIT);

       	glUseProgram(shaderBasique.getProgramID());

    	  m_objet[0].dessineObjet();
    	  m_objet[1].dessineObjet();

       	glUseProgram(0);

        SDL_GL_SwapWindow(m_fenetre); 
   	}
}

