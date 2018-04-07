#ifndef OBJET
#define OBJET

#include <GL/glew.h>
#include "Matrix.h"
#include "Shader.h"
#include "SDL_image.h"

class Objet
{
	private:

		float *m_data;
		int m_nbEtagesActive;
		int *m_nbDonneesEtage;
		int m_taille;
		Shader m_shader;
		GLuint m_texId;
		GLuint m_vao;
		int m_nombreSommets;

 	public:

 		Objet(float * data, int nombreSommets, int nbEtagesActive, int *nbDonneesEtage, int taille);

		void Draw();
		void Draw(Matrix projection);
		
		void SetTexture(char * const texture);
		void SetShader(std::string const vertex, std::string const fragment);
		void SetVao(GLuint vao);

 		GLuint GetVao();
		GLuint GetTexId();
		int GetNbSommet();
		float *GetData();
		int GetShaderID();
		int GetEtages();
		int *GetDonneeEtage();
		int GetTaille();

 		~Objet();
};

#endif