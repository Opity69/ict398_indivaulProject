#pragma once
#include <iostream>
#include <vector>


enum class BodyMode
{
	RIGID,
	STATIC
	
};
struct Body
{
	
};

struct Contact
{

	
};


#define  MAX_CONTACTS  4
struct BodyPair
{
	Contact contacts[MAX_CONTACTS];
	std::weak_ptr<Body> A;
	std::weak_ptr<Body> B;


	void Solve()
	{
		
	}
	
};


class PhyicsWorld
{
	std::vector<Body> bodies_;



private:
	void SubStep(float TimeStep)
	{
		//1 check collision
		//2 generate pair
		//3 solve pairs(Mnetoum Exchange)
		//4 intergrate Forces
		//5 intergrate Velocityies
		//6 writeBack Postion and Rotation.
		
	}
public:
	PhyicsWorld()
	{
		
	}
	


	void Update(float TimeStep)
	{
		std::cout << "Phyics Tick\n";
	}
	
	
};

