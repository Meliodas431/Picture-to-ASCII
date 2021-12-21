#include "Application/Application.h"
#include <iostream>

int main() {
	Application app({1280u, 720u}, "Picture to ASCI");
	
	app.run();
	return 0;
}
