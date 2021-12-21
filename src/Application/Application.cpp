#include "Application.h"
#include "Converter/Converter.h"
#include "Menu/Menu.h"
#include <variant>

Application::Application(sf::VideoMode size, std::string_view title) {
	window.create(size, title.data());
	setHandle(window.getSystemHandle());
}

void Application::run() {
	Converter converter(&window);
	MenuImGui menu(window, converter);

	menu.Init();

	menu.textSize = 8;
	menu.wColor[0] = (float)20 / 255;
	menu.wColor[1] = (float)20 / 255;
	menu.wColor[2] = (float)20 / 255;
	
	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			menu.Event(e);
			switch (e.type) {
			case sf::Event::Closed:
				window.close();
				break;
			}	
		}

		sf::Color color = {
				static_cast<uint8_t>(menu.wColor[0] * 255),
				static_cast<uint8_t>(menu.wColor[1] * 255),
				static_cast<uint8_t>(menu.wColor[2] * 255)
		};

		menu.Update();
		window.clear(color);

		menu.Menu();

		menu.Render();
		window.display();
	}
	menu.ShutDown();
}