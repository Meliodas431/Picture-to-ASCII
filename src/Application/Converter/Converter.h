#pragma once
#include <SFML/Graphics.hpp>
#include <string_view>
#include <string>

class Converter {
private:
	sf::RenderWindow*    window;
	sf::Image            m_image;
	sf::Texture          m_texture;
	sf::Sprite           m_sprite;
	sf::Vector2u         m_pSize;
	std::string_view     m_chars;
	std::string          m_ASCII_buffer;
	std::vector<uint8_t> m_Grey_buffer;
public:
	Converter(sf::RenderWindow* window);
	Converter(const Converter& converter) = delete;

	void setChars(char* chars);
	void toGrey();
	void toASCII();
	void toHTML();
	void getPicture(std::string_view path);
	void toConsole();
	void toWindow();
	void setScale(const float& sacle);
	void toTxT();
	inline uint8_t to16(const uint8_t& digit);
	inline std::string toHexGrey(const uint8_t& digit);
};