#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

#include <SFML/Graphics.hpp>

class Application
{
private:
	// Window
	std::unique_ptr<sf::RenderWindow> window_main;
	int num_dates, date_in, date_out;

public:
	Application(int window_width, int window_height, const sf::String& title);
	~Application();

	// Render the layers
	void updateInterface();
	// Main loop
	void dispatch();
};

#endif //_APPLICATION_HPP_
