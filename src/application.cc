#include <imgui.h>
#include <imgui-SFML.h>
#include <iostream>

#include "application.h"
#include "utils.h"

Application::Application(int window_width, int window_height, const sf::String& title) :
        window_main(std::make_unique<sf::RenderWindow>(sf::VideoMode(window_width, window_height), title,
                sf::Style::Titlebar |
                sf::Style::Close)),
        total_dice(1),
        total_eyes(1),
        dice_side_total(6)
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
    ImGui::SetNextWindowPos(sf::Vector2f(0.0, 0.0));
    ImGui::SetNextWindowSize(sf::Vector2f(500.0, 200.0));
    if (ImGui::Begin("Joint Distribution", nullptr,
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoCollapse))
    {
        ImGui::InputInt("Total dice", &this->total_dice, 1, 2);
        ImGui::InputInt("Total dice side", &this->dice_side_total, 1, 2);
        ImGui::InputInt("Expected total eyes", &this->total_eyes, 1, 2);

        ImGui::Text("Probability %lf%%", diceEyesProbability(this->total_dice, this->total_eyes, this->dice_side_total) * 100.0);
    }
    ImGui::End();
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

		this->updateInterface();

		ImGui::SFML::Render(*window_main);

		window_main->display();
	}
}
