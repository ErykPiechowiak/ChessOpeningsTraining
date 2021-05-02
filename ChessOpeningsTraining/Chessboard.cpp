#include "Chessboard.h"

Chessboard::Chessboard()
{
	chessboard_texture_.loadFromFile("chessboard.jpg");
	chess_pieces_texture_.loadFromFile("chess_pieces.png");

	//assigning every square its position on the board
	int offset = 42;
	int y = 0;
	for (int i = 0; i < 8; i++)
	{
		s_squares_[i][0].setPosition(offset, offset + y);
		for (int j = 1; j < 8; j++)
		{
			s_squares_[i][j].setPosition(s_squares_[i][j - 1].getPosition().x + 63+1.5, s_squares_[i][j - 1].getPosition().y);
		}
		y += 63+2;
	}
}	

sf::Sprite Chessboard::get_chessboard()
{
	return chessboard_;
}

sf::Sprite Chessboard::get_square(int row, int column) const
{
	return s_squares_[row][column];
}

void Chessboard::set_piece_position(sf::Sprite * square, sf::Vector2i position)
{
	square->setPosition((float)position.x-30, (float)position.y-30);
}

void Chessboard::initChessboard()
{
	chessboard_.setTexture(chessboard_texture_);
	int y;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			
			y = 0;
			if (squares_[i][j] != 0)
			{
				if (squares_[i][j] < 0)
					y = 60;
				s_squares_[i][j].setTexture(chess_pieces_texture_);
				s_squares_[i][j].setTextureRect(sf::IntRect(abs(squares_[i][j]) * 60 - 60, y, 60, 60));
			}
		}
	}

}

void Chessboard::resetChessboard()
{

}

sf::Sprite * Chessboard::checkIfWasSelected(sf::Vector2i point)
{
	sf::FloatRect boundingBox;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			boundingBox = s_squares_[i][j].getGlobalBounds();
			if (boundingBox.contains((float)point.x,(float)point.y))
				return &s_squares_[i][j];
		}
	}
	return nullptr;
}
