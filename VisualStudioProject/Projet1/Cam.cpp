#include "include\Cam.h"


Cam::Cam(Vector position, Vector target) : m_position(position), m_target(target) {}
Cam::Cam() {
	m_position = { 0.0, 0.0, 0.0 };
	m_target = { 0.0, 0.0, -1.0 };
}
Cam::~Cam() {}

void Cam::mouseMove(int xrel, int yrel)
{
	static float atheta = 0.0, aphi = 0.0;
	MatrixManager mt;
	GLfloat tmp;
	atheta -= ((GLfloat)xrel * 0.2) * M_PI / 180;
	aphi -= ((GLfloat)yrel * 0.2) * M_PI / 180;

	if (aphi >= M_PI / 2) aphi = 89.0f * M_PI / 180;
	else if (aphi <= -M_PI / 2) aphi = -89.0f * M_PI / 180;

	tmp = cos(aphi);
	m_forward.x = tmp * sin(atheta);
	m_forward.y = sin(aphi);
	m_forward.z = tmp * cos(atheta);

	m_left.x = m_forward.z;
	m_left.y = 0;
	m_left.z = -m_forward.x;
	m_left = mt.NormalizeV3(m_left);


	m_target.x = m_position.x + m_forward.x;
	m_target.y = m_position.y + m_forward.y;
	m_target.z = m_position.z + m_forward.z;


}

void Cam::keyBoardMove(int f, int b, int l, int r)
{
	GLfloat speed = 0.5;
	if (f)
	{
		m_position.x -= m_left.z * speed;
		m_position.z += m_left.x * speed;
	}
	if (b)
	{
		m_position.x += m_left.z * speed;
		m_position.z -= m_left.x * speed;
	}
	if (l)
	{
		m_position.x += m_left.x * speed;
		m_position.z += m_left.z * speed;
	}
	if (r)
	{
		m_position.x -= m_left.x * speed;
		m_position.z -= m_left.z * speed;
	}

	m_target.x = m_position.x + m_forward.x;
	m_target.y = m_position.y + m_forward.y;
	m_target.z = m_position.z + m_forward.z;
}

Vector Cam::getPosition(void)
{
	return m_position;
}

Vector Cam::getTarget(void)
{
	return m_target;
}


