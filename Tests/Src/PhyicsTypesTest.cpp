
#include "Catch2/catch.hpp"
#include <PhyicsTypesSystem.hpp>
#include <PhyicsWorld.hpp>




TEST_CASE("LinearVelocity")
{

	LinearVelocity LinVel (1,2,4);

	SECTION("Create")
	{
		REQUIRE(LinVel.Value().x ==Approx(1));
		REQUIRE(LinVel.Value().y ==Approx(2));
		REQUIRE(LinVel.Value().z ==Approx(4));
		
	}

	SECTION("Copy")
	{

		LinearVelocity LinVel2(LinVel);

			REQUIRE(LinVel2.Value().x ==Approx(1));
		REQUIRE(LinVel2.Value().y ==Approx(2));
		REQUIRE(LinVel2.Value().z ==Approx(4));

		
	}
	
	
}


TEST_CASE("Lambdam and Apply")
{

	BodyState s1;
	BodyState s2;

	s1.linear_velocity = LinearVelocity(0,-10,0);
	s1.postion_state.pos = {2,2,3};
	s2.postion_state.pos = {2,2,2};


	Contact c{};
	c.pos = {2,2,2.5};
	c.norm ={0,1.0f,0};

	BodyProps p1;
	BodyProps p2;
	p1.mass = Mass(1);
	p1.tensor = computeTensorBox(p1.mass,glm::fvec3(0.5f/2,0.5f/2,1.0f/2));

	p2.mass = Mass(3);
	p2.tensor =computeTensorBox(p2.mass, glm::fvec3(3.0/2,1/2.0,3/2.0));

	SECTION("MASS1")
	{
		REQUIRE(p1.mass.getInv() == Approx(1));
	}
	
	SECTION("INv TENSOR 1")
	{
		REQUIRE(p1.tensor.getInv().x == Approx(9.6f).epsilon(0.05));
		REQUIRE(p1.tensor.getInv().y == Approx(24.0f).epsilon(0.05));
		REQUIRE(p1.tensor.getInv().z == Approx(9.6f).epsilon(0.05));
	}


	SECTION("Mass2")
	{
		REQUIRE(p2.mass.getInv() == Approx(1/3.0));
	}

	SECTION("Inv Tensor2")
	{
		REQUIRE(p2.tensor.getInv().x == Approx(0.2222f).epsilon(0.05));
		REQUIRE(p2.tensor.getInv().y == Approx(0.4f).epsilon(0.05));
		REQUIRE(p2.tensor.getInv().z == Approx(0.4f).epsilon(0.05));
	}



	SECTION("Compute Lamda")
	{


		float corelation_of_restitution = 0.6;
	float lambda  =  ComputeLamda(s1,p1,s2,p2,c,corelation_of_restitution );

	REQUIRE(lambda == Approx(4.2227).epsilon(0.05));
	}
	


	
	
	


	
	
	//AngularVelocityVec3 W1, W2;
	//Mass inv_m1, inv_m2;
	//InertiaVector3 inv_J1, inv_J2;
	//DirectionalVec3 R1, R2, normal;
	//float corelation_of_restitution = 0.6;

	//s1.linear_velocity =LinearVelocity(0, -10, 0);
	//W1.value = Vector3(0, 0, 0);
	//inv_m1.value = 1;
	//inv_J1.value = Vector3(9.6, 24.0, 9.6);
	//R1.value = Vector3(2, 2, 2.5) - Vector3(2, 2, 3);

	//V2.value = Vector3(0, 0, 0);
	//W2.value = Vector3(0, 0, 0);
	//inv_m2.value = 1/3;
	//inv_J2.value = Vector3(0.2222, 0.4, 0.4);
	//R2.value = Vector3(2, 2, 2.5) - Vector3(2, 2, 2);

	//normal.value = Vector3(0, 1, 0);

	//double lambda = BodyPair398::calculate_collision_impulse_398(inv_J1, inv_J2, normal,
	//	V1, V2, R1, R2, inv_m1, inv_m2, W1, W2, corelation_of_restitution).value;

	//REQUIRE(lambda == Approx(4.2227));


	
}