#pragma once
#include <random>

class UUID_Generator;

class UUID
{
	uint64_t uuid = 0;

	explicit UUID(uint64_t id): uuid(id)
	{
	};

	friend class UUID_Generator;
public:
	UUID();

	static UUID MakeEmpty()
	{
		return UUID{0};
	}

	operator uint64_t()
	{
		return uuid;
	}

	operator const uint64_t&() const
	{
		return uuid;
	}
};

class UUID_Generator
{
	static std::random_device rd;
	static std::mt19937 twister_;
	static std::uniform_int_distribution<uint64_t> distribution_;
public:
	static UUID MakeUUID();
};
