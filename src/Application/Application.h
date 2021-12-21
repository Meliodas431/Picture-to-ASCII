#pragma once
#include <SFML/Graphics.hpp>
#include <string_view>
#include "DragAndDrop/DragAndDrop.h"

class Application {
private:
	sf::RenderWindow window;
	sf::Text m_text;

public:
	Application(sf::VideoMode size, std::string_view title);
	void run();
};