#include "helloWorld.h"
#include <iostream>
#include <string>

void sayHello() {
	std::cout << makeString() << '\n';
}

std::string makeString() {
	return std::string("Hello, World!");
}

int main() {
	sayHello();
	return 0;
}

