#include <imgui.h>
#include <imgui-SFML.h>

#include "application.h"

Application::Application(int window_width, int window_height, const sf::String& title) :
	window_main(std::make_unique<sf::RenderWindow>(sf::VideoMode(window_width, window_height), title))
{
	// Should be limited to avoid high computation
	// Without this, the computer will works really hard
	window_main->setFramerateLimit(60);

	ImGui::SFML::Init(*this->window_main);

	// Disable saving the ImGui configuration
	ImGui::GetIO().IniFilename = nullptr;
}

Application::~Application()
{
	ImGui::SFML::Shutdown();
}

void Application::updateInterface()
{
}

void Application::dispatch()
{
	sf::Event event{};
	sf::Clock delta_clock;

	while (window_main->isOpen())
	{
		while (window_main->pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed)
			{
				window_main->close();
			}
		}

		window_main->clear(sf::Color::White);

		ImGui::SFML::Update(*window_main, delta_clock.restart());

		updateInterface();

		ImGui::SFML::Render(*window_main);

		window_main->display();
	}
}
