#include <imgui.h>
#include <imgui-SFML.h>

#include "utils.h"
#include "application.h"

Application::Application(int window_width, int window_height, const sf::String& title) :
	window_main(std::make_unique<sf::RenderWindow>(sf::VideoMode(window_width, window_height), title,
		sf::Style::Titlebar |
		sf::Style::Close)),
	num_dates(0),
	date_in(0),
	date_out(0)
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
	ImGui::SetNextWindowSize(sf::Vector2f(600.0, 150.0));
	if (ImGui::Begin("Conditional Probability", nullptr,
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse))
	{
		ImGui::InputInt("Total days of all dating", &this->num_dates, 1, 5);
		ImGui::InputInt("Total days of dating outdoor", &this->date_out, 1, 5);
		ImGui::InputInt("Total days of dating indoor", &this->date_in, 1, 5);
		if (this->num_dates == 0)
		{
			ImGui::Text("Probability dating outdoor when you have dated indoor at the same day NaN%%");
			ImGui::Text("Probability dating indoor when you have dated outdoor at the same day NaN%%");
		}
		else
		{
			if (this->date_in == 0)
			{
				ImGui::Text("Probability dating outdoor when you have dated indoor at the same day NaN%%");
			}
			else
			{
				ImGui::Text("Probability dating outdoor when you have dated indoor at the same day%lf%%", datingProb(this->num_dates, this->date_out, this->date_in).a * 100.0);
			}
			
			if (this->date_in == 0)
			{
				ImGui::Text("Probability dating indoor when you have dated outdoor at the same day NaN%%");
			}
			else
			{
				ImGui::Text("Probability dating indoor when you have dated outdoor at the same day%lf%%", datingProb(this->num_dates, this->date_out, this->date_in).b * 100.0);
			}
		}
		
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

		updateInterface();

		ImGui::SFML::Render(*window_main);

		window_main->display();
	}
}
