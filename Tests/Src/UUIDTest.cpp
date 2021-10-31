#include "Catch2/catch.hpp"
#include <UUID_Generator.hpp>

TEST_CASE("UUID")
{
	UUID uuid;
	UUID empty = UUID::MakeEmpty();

	SECTION("Create")
	{
		REQUIRE_FALSE(uuid != 0);
		
		

		REQUIRE(empty ==0);
	}

	SECTION("Copy/Assigne")
	{
		UUID t;

		t = uuid;

		REQUIRE_FALSE(t == 0);
		
	}
		
	
}