#ifndef CAM
#define CAM
#include "matrix.h"
#include "Input.h"
#include <Windows.h>
#include <GL/gl.h>

class Cam {
private:
	Vector m_position;
	Vector m_target;
	Vector m_forward;
	Vector m_left;


public:
	Cam(Vector position, Vector target);
	Cam();
	~Cam();
	void Cam::deplace(Input const &input);
	void mouseMove(int a, int b);
	void Cam::keyBoardMove(bool f, bool b, bool l, bool r);
	Vector getTarget(void);
	Vector getPosition(void);
};
#endif
