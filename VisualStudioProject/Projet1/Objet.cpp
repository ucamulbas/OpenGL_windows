#include "include\Objet.h"

Objet::Objet(float *data, int nombreSommets, int nbEtagesActive, int *nbDonneesEtage, int taille) : 
	m_data(data), m_nombreSommets(nombreSommets), m_nbEtagesActive(nbEtagesActive), m_nbDonneesEtage(nbDonneesEtage), m_taille(taille) {}

Objet::~Objet(){}

GLuint Objet::GetVao()
{
	return m_vao;
}

GLuint Objet::GetTexId()
{
	return m_texId;
}

void Objet::Draw()
{
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, m_nombreSommets);
	glBindVertexArray(0);
}

void Objet::SetTexture(char* const texturePath)
{
	// Chargement de l'image dans une surface SDL

	SDL_Surface *imageSDL = IMG_Load(texturePath);

	if (imageSDL == 0)
	{
		std::cout << "Erreur : " << SDL_GetError() << std::endl;
		return;
	}

	GLuint m_id;
	// Génération de l'ID
	glGenTextures(1, &m_id);


	// Verrouillage
	glBindTexture(GL_TEXTURE_2D, m_id);


	// Format de l'image
	GLenum formatInterne(0);
	GLenum format(0);

	// Détermination du format et du format interne pour les images à 3 composantes
	if (imageSDL->format->BytesPerPixel == 3)
	{
		// Format interne
		formatInterne = GL_RGB;
		// Format
		if (imageSDL->format->Rmask == 0xff)
			format = GL_RGB;
		else
			format = GL_BGR;
	}

	// Détermination du format et du format interne pour les images à 4 composantes
	else if (imageSDL->format->BytesPerPixel == 4)
	{
		// Format interne
		formatInterne = GL_RGBA;
		// Format
		if (imageSDL->format->Rmask == 0xff)
			format = GL_RGBA;
		else
			format = GL_BGRA;
	}

	// Dans les autres cas, on arrête le chargement
	else
	{
		std::cout << "Erreur, format interne de l'image inconnu" << std::endl;
		SDL_FreeSurface(imageSDL);
		return;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	// Copie des pixels
	glTexImage2D(GL_TEXTURE_2D, 0, formatInterne, imageSDL->w, imageSDL->h, 0, format, GL_UNSIGNED_BYTE, imageSDL->pixels);
	// Déverrouillage
	glBindTexture(GL_TEXTURE_2D, 0);
	m_texId = m_id;
}

void Objet::SetShader(std::string const vertex, std::string const fragment) {
	Shader tmp(vertex, fragment);
	m_shader = tmp;
	m_shader.charger();
}

void Objet::SetVao(GLuint vao)
{
	m_vao = vao;
}

void Objet::Draw(Matrix projection)
{
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, m_nombreSommets);
	glBindVertexArray(0);
}

int Objet::GetNbSommet()
{
	return m_nombreSommets;
}

float * Objet::GetData()
{
	return m_data;
}

int Objet::GetShaderID()
{
	return m_shader.getProgramID();
}

int Objet::GetEtages()
{
	return m_nbEtagesActive;
}

int * Objet::GetDonneeEtage()
{
	return m_nbDonneesEtage;
}

int Objet::GetTaille()
{
	return m_taille;
}
