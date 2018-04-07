#ifndef CAM
#define CAM
#include "matrix.h"
#include <Windows.h>
#include <GL/gl.h>

class Cam {
private:
	Vector m_position = { 62.5 * 4,10.0,-40.0 };
	Vector m_target;
	Vector m_forward;
	Vector m_left;


public:
	Cam(Vector position, Vector target);
	Cam();
	~Cam();

	void mouseMove(int a, int b);
	void keyBoardMove(int a, int b, int c, int d);
	Vector getTarget(void);
	Vector getPosition(void);
};
#endif
