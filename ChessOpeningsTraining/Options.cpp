#include "Options.h"
#include "Chessboard.h"

Options::Options(Chessboard *chessboard) : chessboard_(chessboard)
{
	flip_board_texture_.loadFromFile("swap_icon.png");
	flip_board_s.setPosition(600, 0);
	flip_board_s.setTexture(flip_board_texture_);
	flip_board_s.setTextureRect(sf::IntRect(0, 0, 20, 20));
	
}

sf::Sprite Options::get_options() const
{
	return flip_board_s;
}

void Options::checkIfWasSelected(sf::Vector2i point)
{
	sf::FloatRect boundingBox = flip_board_s.getGlobalBounds();
	if (boundingBox.contains((float)point.x, (float)point.y))
	{
		chessboard_->flipBoard();
		//return &flip_board_s;
	}
	
}
