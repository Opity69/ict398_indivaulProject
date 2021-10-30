#include "VissualObject.hpp"


#include "Glew/include/GL/glew.h"
#include "gl/GLU.h"
#include "glm3/glm/gtc/type_ptr.hpp"

IVissualObject::IVissualObject(): drawList(glGenLists(1))
{
}

IVissualObject::IVissualObject(const Transform& transform, const glm::fvec4& color): transform_(transform),
	color_(color), drawList(glGenLists(1))
{
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

Transform IVissualObject::get_transform_()
{
	return transform_;
}

void IVissualObject::SetTransform(const Transform& trans)
{
	transform_ = trans;
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

Shpere::Shpere(const Transform& transform, const glm::fvec4& color, float radius): IVissualObject(transform, color),
	radius(radius), obj_(gluNewQuadric())
{
}


void Shpere::Rebuild()
{
	glNewList(drawList,GL_COMPILE);
	glColor4fv(glm::value_ptr(color_));
	gluSphere(obj_, radius, 16, 8);
	glEndList();
}

void Shpere::DrawSetup()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	Transform t =transform_;
	t.Scale({radius,radius,radius});
	glLoadMatrixf(t.getMatrixPtr());
}

void Shpere::DrawTearDown()
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
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	// Bottom face (y = -1.0f)

	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Front face  (z = 1.0f)

	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);


	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);


	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	
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
}

void Box::DrawTearDown()
{
	glPopMatrix();
}
