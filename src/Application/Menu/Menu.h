#pragma once
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include "../Converter/Converter.h"

class MenuImGui {
public:
	 char charBuffer[11] { " .,~o#!$%&" };
	  int textSize;
	float wColor[3];
	float scale { 1.f };
private:
	sf::RenderWindow& window;
	Converter& converter;
	sf::Clock deltaClock;

public:
	MenuImGui(sf::RenderWindow& window, Converter& converter);
	void Init();
	void Event(sf::Event& event);
	void Update();
	void Menu();
	void Render();
	void ShutDown();
};

