#pragma once
//#include <GL/glu.h>
#include <glm3/glm/glm.hpp>
#include "Transform.hpp"


class GLUquadric;

class IVissualObject
{
public:


protected:

	Transform transform_;
	glm::fvec4 color_;
	mutable unsigned drawList = 0;
	mutable  bool Built= false;

	virtual void Rebuild() = 0;
	virtual void DrawSetup() = 0;
	virtual void DrawTearDown() =0;

	IVissualObject(const Transform& transform, const glm::fvec4& color);

	IVissualObject();


public:
	void Draw();
	Transform get_transform_();

	void SetTransform(const Transform& trans);
	

	void SetColor(const glm::fvec4& color);
	glm::fvec4 GetColor();
};


class Shpere : public IVissualObject
{
public:
	Shpere(const Transform& transform, const glm::fvec4& color, float radius);


private:
	float radius = 0;
	GLUquadric* obj_ = nullptr;
protected:
	void Rebuild() override;
	
	void DrawSetup() override;
	void DrawTearDown() override;
};

class Box : public IVissualObject
{
public:
	Box(const Transform& transform, const glm::fvec4& color, const glm::fvec3& half_exents);

protected:
	void Rebuild() override;
	void DrawSetup() override;
	void DrawTearDown() override;
private:
	glm::fvec3 halfExents = {};
	GLUquadric* obj_ = nullptr;
public:
	
};
