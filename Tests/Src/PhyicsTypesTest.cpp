
#include "Catch2/catch.hpp"
#include <PhyicsTypesSystem.hpp>




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