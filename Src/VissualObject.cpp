#include "VissualObject.hpp"


#include "Glew/include/GL/glew.h"
#include "gl/GLU.h"
#include "glm3/glm/gtc/type_ptr.hpp"

IVissualObject::IVissualObject()
{
	drawList = glGenLists(1);
}

IVissualObject::~IVissualObject()
{
	glDeleteLists(drawList,1);
}

IVissualObject::IVissualObject(const Transform& transform, const glm::fvec4& color):TransFormable(transform),
	color_(color)
{
	drawList = glGenLists(1);
}


void IVissualObject::Draw()
{
	if (!Built)
	{
		Rebuild();
		Built = !Built;
	}
	DrawSetup();
	glCallList(drawList);
	DrawTearDown();
}



void IVissualObject::SetColor(const glm::fvec4& color)
{
	this->color_ = color;
	Rebuild();
}

glm::fvec4 IVissualObject::GetColor()
{
	return color_;
}

Sphere::Sphere(const Transform& transform, const glm::fvec4& color, float radius): IVissualObject(transform, color),
	radius(radius), obj_(gluNewQuadric())
{
}


void Sphere::Rebuild()
{
	glNewList(drawList,GL_COMPILE);
	glColor4fv(glm::value_ptr(color_));
	gluSphere(obj_, radius, 24, 32);
	glEndList();
}

void Sphere::DrawSetup()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	Transform t =transform_;
	
	glLoadMatrixf(t.getMatrixPtr());
}

void Sphere::DrawTearDown()
{
	glPopMatrix();
}

Box::Box(const Transform& transform, const glm::fvec4& color, const glm::fvec3& half_exents):
	IVissualObject(transform, color),
	halfExents(half_exents), obj_(gluNewQuadric())
{
}

void Box::Rebuild()
{
	glNewList(drawList,GL_COMPILE);
	
	glBegin(GL_QUADS);
	glColor4fv(glm::value_ptr(color_));
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glm::fvec3 color = color_ * 0.7f;

	// Bottom face (y = -1.0f)
	glColor4fv(glm::value_ptr(color));
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Front face  (z = 1.0f)
	color *= 0.7f;
	glColor4fv(glm::value_ptr(color));
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);


	color *= 0.7f;
	glColor4fv(glm::value_ptr(color));
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);


	color *= 0.7f;
	glColor4fv(glm::value_ptr(color));
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	color *=  0.7f;
	glColor4fv(glm::value_ptr(color_));
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd(); // End of drawing color-cu
	glEndList();
}

void Box::DrawSetup()
{
		glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	Transform t = transform_;
	t.Scale(halfExents);
	glLoadMatrixf(t.getMatrixPtr()); // TODO() setup  transform;

	glBegin(GL_LINES);
		glColor4fv(glm::value_ptr(color_));
		
		glVertex3f(0,0,0);
		
		glVertex3f(1.1,1.1,1.1f);
	glEnd();
}

void Box::DrawTearDown()
{
	glPopMatrix();
}
