#ifndef OBJET
#define OBJET

#include <GL/glew.h>


class Objet
{
	private:
	float *m_data;
	int m_nbEtagesActive;
	int *m_nbDonneesEtage;
	int m_taille;


 	public:
	int m_nombreSommets;
	GLuint m_vao;
 	Objet(float data[], int nombreSommets, int nbEtagesActive, int *nbDonneesEtage, int taille);
 	~Objet();
 	GLuint getVao();
 	void dessineObjet();

};

#endif