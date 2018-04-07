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
	objet.SetVao(vao);
	m_objet.push_back(objet);

}

void SceneOpenGL::ajouteObjet(Objet obj)
{
	GLuint vao;
	GLuint buff;

	float *data = obj.GetData();
	int *nbDonneeEtage = obj.GetDonneeEtage();
	int nbSommets = obj.GetNbSommet();

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &buff);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, buff);
	glBufferData(GL_ARRAY_BUFFER, sizeof data * obj.GetTaille(), data, GL_STATIC_DRAW);

	int size = 0;
	for (int i = 0; i < obj.GetEtages(); i++)
	{
		glEnableVertexAttribArray(i);
		if (i == 0)
			glVertexAttribPointer(i, nbDonneeEtage[i], GL_FLOAT, GL_FALSE, 0, 0);
		else
		{
			size += nbSommets * nbDonneeEtage[i - 1];
			glVertexAttribPointer(i, nbDonneeEtage[i], GL_FLOAT, GL_FALSE, 0, (const void *)(size * sizeof *data));
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	obj.SetVao(vao);
	m_objet.push_back(obj);

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


	SDL_SetRelativeMouseMode(SDL_TRUE);
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

	MatrixManager mt;
	Cam cam({ 0.0, 0.0, -3.0 }, { 0.0, 0.0, -1 });
	float rot = 0;

	m_input.afficherPointeur(false);

	// Boucle principale
	while (!m_input.terminer())
	{
		m_input.updateEvenements();
		cam.deplace(m_input);
		// Nettoyage de l'écran
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Objet obj = m_objet[0];

		glUseProgram(obj.GetShaderID());

		Matrix projection = mt.MatrixPerspective(90, m_largeurFenetre / m_hauteurFenetre, .1, 100.0);
		Matrix viewMatrix = mt.MatrixLookAt(cam.getPosition().x, cam.getPosition().y, cam.getPosition().z, cam.getTarget().x, cam.getTarget().y, cam.getTarget().z, 0.0, 1.0, 0.0);
		//Matrix modelview = mt.MatrixMultiply(mt.MatrixLoadIdentity(), mt.MatrixRotatef(rot, 0, 1, 0));
		Matrix modelview = mt.MatrixLoadIdentity();

		Matrix MVP = mt.MatrixMultiply(projection, viewMatrix);
		MVP = mt.MatrixMultiply(MVP, modelview);

		glBindVertexArray(obj.GetVao());

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, obj.GetTexId());

		glUniform1i(glGetUniformLocation(obj.GetShaderID(), "myTexture"), 0);
		glUniformMatrix4fv(glGetUniformLocation(obj.GetShaderID(), "modelViewProjectionMatrix"), 1, GL_FALSE, (GLfloat *)&MVP);
		glUniformMatrix4fv(glGetUniformLocation(obj.GetShaderID(), "modelMatrix"), 1, GL_FALSE, (GLfloat*)&modelview);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, obj.GetNbSommet());
		glBindVertexArray(0);
		glUseProgram(0);

		SDL_GL_SwapWindow(m_fenetre);

		/*rot += 1;
		if (rot == 360)
			rot = 0;*/
	}
}

SceneOpenGL::~SceneOpenGL()
{
	SDL_GL_DeleteContext(m_contexteOpenGL);
	SDL_DestroyWindow(m_fenetre);
	SDL_Quit();
}
