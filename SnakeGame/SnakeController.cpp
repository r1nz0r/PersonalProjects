#include "SnakeController.h"
#include "GameSettings.h"
#include "Snake.h"

void SnakeController::HandleInput(const sf::Keyboard::Scancode& scancode)
{
	switch (scancode)
	{
	case sf::Keyboard::Scancode::W:
		_snake.SetDirection(EDirection::Up);
		break;
	case sf::Keyboard::Scancode::S:
		_snake.SetDirection(EDirection::Down);
		break;
	case sf::Keyboard::Scancode::A:
		_snake.SetDirection(EDirection::Left);
		break;
	case sf::Keyboard::Scancode::D:
		_snake.SetDirection(EDirection::Right);
		break;
		//ONLY FOR DEBUG TESTS!!! DELETE AT RELEASE VERSION!!!
	case sf::Keyboard::Scancode::Space:
		_snake.Grow();
		break;
	default:
		//Остальные клавиши нас не интересуют
		break;
	}
}
