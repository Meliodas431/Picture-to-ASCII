#include "Converter.h" 
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>
#include "../DragAndDrop/DragAndDrop.h"

Converter::Converter(sf::RenderWindow* window) {
	this->window = window;
}

std::string getName() {
	std::filesystem::path path(getPath().data());
	return path.filename().replace_extension().u8string();
}

void Converter::setChars(char* chars) {
	m_chars = chars;
}

void Converter::toGrey() {
	uint8_t tmp { 0 };
	int count = 0;
	for (int Y { 0 }; Y < m_pSize.y; Y++) {
		for (int X { 0 }; X < m_pSize.x; X++) {
			auto pixel = m_image.getPixel(X, Y);
			uint8_t tmp = (pixel.r + pixel.g + pixel.b)/3;
			m_image.setPixel(X, Y, { tmp ,tmp ,tmp ,255u });
			m_Grey_buffer.emplace_back(tmp);
		}
	}
	m_texture.loadFromImage(m_image);
	m_sprite.setTexture(m_texture);
}

void Converter::toASCII() {
	m_ASCII_buffer.clear();
	for (int Y{ 0 }; Y < m_pSize.y; Y++) {
		for (int X{ 0 }; X < m_pSize.x; X++) {
			uint32_t index{ (255u - m_Grey_buffer.at(Y * m_pSize.x + X)) * m_chars.size() / 256u };
			m_ASCII_buffer += m_chars.data()[index];		
		}			
	}
}

void Converter::toTxT() {
	std::string name = "src/save/" + getName() + ".txt";
	std::ofstream out(name);
	if (out) {
		for (int index{ 0 }; index < m_Grey_buffer.size(); index++) {
			if (index % m_pSize.x == 0)
				out << '\n';
			else
				out << m_ASCII_buffer[index];
		}
	}
	out.close();
}

void Converter::toHTML() {
	std::string start{ "<html>\n"
					"<style>\n"
					"  .word {\n"
					"  background: #000000;\n"
					"  white-space: pre;\n"
					"      }\n"
					"</style>\n"
					"<body>\n"
					"<p class = \"word\"><font face = \"Consolas\">" };
	std::string end{ "</font>\n</p>\n</body>\n</html>" };
	std::string name = "src/save/" + getName() + ".html";
	std::ofstream out(name, std::ios::out);

	bool color = false;
	if (out) {
		out << start;
		for (int index{ 0 }; index < m_Grey_buffer.size(); index++) {
			if (index % m_pSize.x == 0) {
				out << '\n';
			}
			else if (m_ASCII_buffer.at(index) == ' ') {
				out << m_ASCII_buffer.at(index);
			}
			else {
				std::string hex = toHexGrey(m_Grey_buffer.at(index));
				out << "<font color=" << hex << ">";
				out << m_ASCII_buffer.at(index);
				out << "</font>";
			}
		}
		out << end;
	}
	out.close();
}

void Converter::getPicture(std::string_view path) {
	m_image.loadFromFile(path.data());
	m_pSize = m_image.getSize();

	m_Grey_buffer.clear();
	m_ASCII_buffer.clear();
	m_Grey_buffer.reserve(m_pSize.x * m_pSize.y);
	m_ASCII_buffer.reserve(m_pSize.x * m_pSize.y);
}

inline uint8_t Converter::to16(const uint8_t& digit) {
	static const char* hex{ "0123456789ABCDEF" };
	return hex[digit];
}

inline std::string Converter::toHexGrey(const uint8_t& digit) {
	std::string result = "#000000";
	uint8_t First  = digit / 16;;
	uint8_t Second = digit % 16;;

	First = to16(First);
	Second = to16(Second);

	for (int i = 1; i < result.size(); i += 2) {
		result[i] = First;
		result[i + 1] = Second;
	}
	return result;
}

void Converter::toConsole() {
	system("cls");
	for (int index{ 0 }; index < m_ASCII_buffer.size(); index++) {
		if (index % m_pSize.x == 0)
			std::cout << '\n';
		else
			std::cout << m_ASCII_buffer[index];
	}
	std::cout << '\n';
}

void Converter::toWindow() {
	window->draw(m_sprite);
}

void Converter::setScale(const float& scale) {
	m_sprite.setScale(scale, scale);
}