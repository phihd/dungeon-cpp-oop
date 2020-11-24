#include "World.hpp"
#include <iostream>
int main() 
{
	Battlefield room(10, 10, {}, {}, {Item("B.F Sword", "big fucking sword", Stat(0, 0, 50, 0, 0), 1300), Item("Infinity Edge", "bigger fucking sword", Stat(0, 0, 125, 0, 0), 1300) }, {});
	std::vector<std::string> result = room.ToString();
	for (unsigned int i = 0; i < result.size(); i++) {
		std::cout << result[i] << std::endl;
	}

	std::vector<string> design{"........",
							   "........",
							   "###..###",
							   "#...1..#",
							   "#......#",
							   "###..###",
							   "........",
							   "........"};
	
	bool temp = room.FromString(design);
	std::cout << temp << std::endl;
	result = room.ToString();

	for (unsigned int i = 0; i < result.size(); i++) {
		std::cout << result[i] << std::endl;
	}
	
	return 0;
}