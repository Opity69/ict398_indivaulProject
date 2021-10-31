#include "UUID_Generator.hpp"


  std::random_device        UUID_Generator::rd;
  std::mt19937           UUID_Generator::twister_(rd());
  std::uniform_int_distribution<uint64_t>  UUID_Generator::distribution_ (1,std::numeric_limits<uint64_t>::max());


UUID::UUID()
{
	*this = UUID_Generator::MakeUUID();
}

UUID UUID_Generator::MakeUUID()
{
	return  UUID{distribution_(twister_)};
}

