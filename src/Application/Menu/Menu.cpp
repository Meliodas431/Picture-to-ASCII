#include "Menu.h"
#include "../DragAndDrop/DragAndDrop.h"

MenuImGui::MenuImGui(sf::RenderWindow& window, Converter& converter)
	: window(window), converter(converter)
{	

}

void MenuImGui::Init() {
	ImGui::SFML::Init(window);
}

void MenuImGui::Event(sf::Event& e) {
	ImGui::SFML::ProcessEvent(e);
}

void MenuImGui::Update() {
	ImGui::SFML::Update(window, deltaClock.restart());
}

void MenuImGui::Menu() {
	ImGui::Begin("Settings");
	ImGui::InputText("set chars", charBuffer, sizeof(charBuffer));
	ImGui::SliderFloat("Scale", &scale, 0.2f, 5.f);
	if (ImGui::Button("Update", { 50,20 })) {
		converter.getPicture(getPath());
		converter.setChars(charBuffer);
		converter.toGrey();
		converter.toASCII();
	}
	if (ImGui::Button("Draw chars", { 90,20 })) {
		converter.toConsole();
	}
	if (ImGui::Button("Save to TXT", { 90,20 })) {
		converter.toTxT();
	}
	if (ImGui::Button("Save to HTML", { 90,20 })) {
		converter.toHTML();
	}
	ImGui::End();

	converter.setScale(scale);
	converter.toWindow();
}

void MenuImGui::Render() {
	ImGui::SFML::Render(window);
}

void MenuImGui::ShutDown() {
	ImGui::SFML::Shutdown();
}
