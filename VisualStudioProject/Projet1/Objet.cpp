#include "include\Objet.h"

Objet::Objet(float *data, int nombreSommets, int nbEtagesActive, int *nbDonneesEtage, int taille) : 
	m_data(data), m_nombreSommets(nombreSommets), m_nbEtagesActive(nbEtagesActive), m_nbDonneesEtage(nbDonneesEtage), m_taille(taille) {}

Objet::~Objet(){}

GLuint Objet::getVao()
{
	return m_vao;
}

void Objet::dessineObjet()
{
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, m_nombreSommets);
	glBindVertexArray(0);
}