#include <SFML/System.hpp>

#include "application.h"

int main()
{
	Application app(500, 200, sf::String("Joint Distribution"));
	app.dispatch();
}
