#ifndef OBJET
#define OBJET

#ifdef WIN32
#include <GL/glew.h>

#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>

#endif

class Objet
{
	private:
	float *m_data;
	int m_nombreSommets;
	int m_nbEtagesActive;
	int *m_nbDonneesEtage;
	int m_taille;


 	public:
	GLuint m_vao;
 	Objet(float data[], int nombreSommets, int nbEtagesActive, int *nbDonneesEtage, int taille);
 	~Objet();
 	GLuint getVao();
 	void dessineObjet();

};

#endif