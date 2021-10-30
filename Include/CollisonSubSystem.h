#pragma once

#include <vector>
#include  <glm3/glm/glm.hpp>
namespace collierScope
{

	class Trasform
	{
		
	};

	
	class AABB	{
		struct AABB_insectData
		{
			
		};

		
		glm::fvec3 min;
		glm::fvec3  max;



		bool insterects(const AABB other)
		{
			for (int i = 0; i < 3; ++i)
			{

				if(min[i] > other.max[i]  || other.min[i] >max[i])
				{
					return false;				
				}
			}

			return true;
			
		}

		bool contains()
		{
			
		}


		AABB Transform(const Trasform trans)
		{
			
		}

		
	};


	struct Candiates
	{
		std::vector<size_t > candiates;
	};


	class  Broadphase
	{
		



		virtual Candiates getCandiates(const AABB& aabb) = 0;


		
		virtual  ~Broadphase(){};
		

		

		
	};

	

	
	class CollisonSubSystem
{
};


}


