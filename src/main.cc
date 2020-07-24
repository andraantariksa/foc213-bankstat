#include <SFML/System.hpp>

#include "application.h"

int main()
{
	Application app(600, 150, sf::String("Conditional Probability"));
	app.dispatch();
}
