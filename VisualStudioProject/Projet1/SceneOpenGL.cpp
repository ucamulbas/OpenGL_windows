#include "include\SceneOpenGL.h"

SceneOpenGL::SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre) :
	m_titreFenetre(titreFenetre), m_largeurFenetre(largeurFenetre), m_hauteurFenetre(hauteurFenetre), m_fenetre(0), m_contexteOpenGL(0)
{}

void SceneOpenGL::ajouteObjet(float data[], int nombreSommets, int nbEtageActive, int *nbDonneeEtage, const int taille)
{
	GLuint vao;
	GLuint buff;
		

	Objet objet(data, nombreSommets, nbEtageActive, nbDonneeEtage, taille);

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &buff);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, buff);
	glBufferData(GL_ARRAY_BUFFER, sizeof data * taille, data, GL_STATIC_DRAW);

	int size = 0;
	for (int i = 0; i < nbEtageActive; i++)
	{
		glEnableVertexAttribArray(i);
		if (i == 0)
			glVertexAttribPointer(i, nbDonneeEtage[i], GL_FLOAT, GL_FALSE, 0, 0);
		else
		{
			size += nombreSommets * nbDonneeEtage[i - 1];
			glVertexAttribPointer(i, nbDonneeEtage[i], GL_FLOAT, GL_FALSE, 0, (const void *)(size * sizeof *data));
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	objet.m_vao = vao;
	m_objet.push_back(objet);

}

bool SceneOpenGL::initialiserFenetre()
{
	// Initialisation de la SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
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

	if (m_fenetre == 0)
	{
		std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
		SDL_Quit();

		return false;
	}
	// Création du contexte OpenGL
	m_contexteOpenGL = SDL_GL_CreateContext(m_fenetre);

	if (m_contexteOpenGL == 0)
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
	// On initialise GLEW
	GLenum initialisationGLEW(glewInit());
	// Si l'initialisation a échoué :
	if (initialisationGLEW != GLEW_OK)
	{
		// On affiche l'erreur grâce à la fonction : glewGetErrorString(GLenum code)
		std::cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(initialisationGLEW) << std::endl;

		// On quitte la SDL
		SDL_GL_DeleteContext(m_contexteOpenGL);
		SDL_DestroyWindow(m_fenetre);
		SDL_Quit();

		return false;
	}
	// Tout s'est bien passé, on retourne true
	return true;
}

void SceneOpenGL::bouclePrincipale()
{
	// Variables
	bool terminer(false);

	Shader shaderBasique("Shaders/couleur3D.vert", "Shaders/couleur3D.frag");
	shaderBasique.charger();

	MatrixManager mt;
	Cam cam;

	// Boucle principale
	while (!terminer)
	{
		// Gestion des évènements
		SDL_WaitEvent(&m_evenements);
		if (m_evenements.window.event == SDL_WINDOWEVENT_CLOSE)
			terminer = 1;

		// Nettoyage de l'écran
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shaderBasique.getProgramID());

		Objet obj = m_objet[0];

		Matrix projection = mt.MatrixPerspective(70, m_largeurFenetre / m_hauteurFenetre, .1, 100.0);
		Matrix viewMatrix = mt.MatrixLookAt(cam.getPosition().x, cam.getPosition().y, cam.getPosition().z, cam.getTarget().x, cam.getTarget().y, cam.getTarget().z, 0.0, 1.0, 0.0);
		Matrix modelview = mt.MatrixLoadIdentity();
		Matrix MVP = mt.MatrixMultiply(projection, viewMatrix);
		MVP = mt.MatrixMultiply(MVP, modelview);
		glBindVertexArray(obj.m_vao);
		glUniformMatrix4fv(glGetUniformLocation(shaderBasique.getProgramID(), "modelViewProjectionMatrix"), 1, GL_FALSE, (GLfloat *)&MVP);

		glDrawArrays(GL_TRIANGLES, 0, obj.m_nombreSommets);

		glBindVertexArray(0);
		glUseProgram(0);

		SDL_GL_SwapWindow(m_fenetre);
	}
}

SceneOpenGL::~SceneOpenGL()
{
	SDL_GL_DeleteContext(m_contexteOpenGL);
	SDL_DestroyWindow(m_fenetre);
	SDL_Quit();
}
