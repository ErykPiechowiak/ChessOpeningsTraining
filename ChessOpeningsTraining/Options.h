#pragma once
#include <SFML/Graphics.hpp>
#include "Chessboard.h"
class Options
{
public: 
	Options(Chessboard *chessboard);
	sf::Sprite get_options() const;
	void checkIfWasSelected(sf::Vector2i point);
private:
	Chessboard *chessboard_;
	sf::Texture flip_board_texture_;
	sf::Sprite flip_board_s;
};

