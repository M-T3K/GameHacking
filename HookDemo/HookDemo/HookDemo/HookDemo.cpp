// HookDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <Windows.h> // Too Lazy to avoid using this
#include <iostream>

int health = 150;

auto sub(int x, int y) -> int {
	printf("Sub\n");
	x = x - y;
	return x;
}

auto sum(int x, int y) -> int {
	printf("Sum\n");
	x = x + y;
	return x;
}

// Very Shitty Code, Don't Judge
auto main() -> int {

	std::cout << "Welcome to DumbHeroes, a very deep and complex game." << std::endl;
	std::cout << "These mechanics consistin pressing SPACE to drink a potion..." << std::endl;
	std::cout << "Try not to die!" << std::endl;
	bool pause = false;

	while( !GetAsyncKeyState(VK_DELETE)) {
		if ( GetAsyncKeyState(VK_SPACE)) {
			std::cout << "You drank a potion and recovered 2 hp..." << std::endl;
			health = sum(health, 2);
			std::cout << health << std::endl;
		}
		if (GetAsyncKeyState(VK_INSERT)) {
			pause = !pause;
		}
		if (!pause) health = sub(health, 1);
		std::cout << "Current Health = " << health << std::endl;
		if (health <= 0) {
			std::cout << "You die..." << std::endl;
			std::cin.get();
			return -1;
		}
		Sleep(1000);
	}
}


