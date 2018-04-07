#ifndef MATRIX_HEAD
#define MATRIX_HEAD
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#define CARRE(X) ((X)*(X))
#define M_PI 3.14

class Vector
{
public:
  float x,y,z,w;
};

class Matrix
{
public:
  Vector r[4];
};

class MatrixManager {

private:
	Matrix *pile;
	int H;
	int Taille;

public:
	MatrixManager();
	MatrixManager(int taille);
	~MatrixManager();

	void initPile();
	void PushMatrix(Matrix mat);
	Matrix PopMatrix();

	Matrix MatrixLoadIdentity();
	Matrix MatrixMultiply(Matrix m1, Matrix m2);
	Matrix MatrixPerspective(float fovy, float aspect, float zNear, float zFar);
	Matrix MatrixTranslatef(float x, float y, float z);
	Matrix MatrixRotatef(float fovy, float x, float y, float z);
	Matrix MatrixScalef(float x, float y, float z);
	Matrix MatrixLookAt(float ex, float ey, float ez, float cx, float cy, float cz, float upx, float upy, float upz);
	Vector NormalizeV3(Vector vec);
	Vector MultVector(Vector v1, Vector v2);
	Vector CrossProductV3(Vector v1, Vector v2);
	void MatrixPrint(Matrix mat);
	Matrix MatrixOrthonormal(float left, float right, float bottom, float top, float near, float far);
};

#endif
