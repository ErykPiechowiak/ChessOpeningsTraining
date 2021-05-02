#pragma once
#include <SFML/Graphics.hpp>
class Chessboard
{
public: 
	Chessboard();
	sf::Sprite get_chessboard();
	sf::Sprite get_square(int row, int column) const;
	void set_piece_position(sf::Sprite *square, sf::Vector2i position);
	void initChessboard();
	void resetChessboard();
	sf::Sprite* checkIfWasSelected(sf::Vector2i point);


private:

	sf::Texture chessboard_texture_;
	sf::Texture chess_pieces_texture_;
	sf::Sprite s_squares_[8][8];
	int squares_[8][8] = 
		{
			{3, 4, 5, 1, 2, 5, 4, 3},
			{ 6,6,6,6,6,6,6,6 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ -6,-6,-6,-6,-6,-6,-6,-6 },
			{ -3,-4,-5,-2,-1,-5,-4,-3 }
		};

	sf::Sprite chessboard_;
};

