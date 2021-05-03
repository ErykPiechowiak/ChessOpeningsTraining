#pragma once
#include <SFML/Graphics.hpp>
#include <array>
class Chessboard
{
public: 
	Chessboard();
	sf::Sprite get_chessboard();
	sf::Sprite get_square(int row, int column) const;

	void set_piece_position(sf::Sprite *square, sf::Vector2f position, int offset = 0);
	void set_piece_position(sf::Sprite *square, sf::Vector2i position, int offset = 0);
	//void set_piece_position(sf::Sprite *square, sf::Vector2i position);

	void initChessboard();
	void resetChessboard();
	sf::Sprite* checkIfWasSelected(sf::Vector2i point, int &row, int &column);
	bool checkIfLegal(sf::Vector2i mouse_position, int &row, int &col, sf::Vector2f original_position);//function to check if a done move is legal
	void set_piece_texture(int row, int col);


private:
	void printPiecePositions();
	void makeMove(int &row, int &col, int i, int j);
	void checkEnPassant(int *&en_passant, bool &en_passant_flag);
	sf::Texture chessboard_texture_;
	sf::Texture chess_pieces_texture_;
	sf::Texture empty_texture_;
	std::array<std::array<sf::Sprite, 8>, 8> s_chess_pieces_;
	bool white_move_ = true;
	int *white_en_passant_ = nullptr;
	bool white_en_passant_flag_ = false;
	int *black_en_passant_ = nullptr;
	bool black_en_passant_flag_ = false;

	//sf::Sprite s_squares_[8][8];
	/*
		6 - pawn
		5 - bishop 
		4 - knight
		3 - rook
		2 - king
		1 - queen

		Numbers with '-' sign are white pieces
	*/
	std::array<std::array<int, 8>,8> chess_pieces_ = 
	{
		{
			{3, 4, 5, 1, 2, 5, 4, 3},
			{ 6,6,6,6,6,6,6,6 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ -6,-6,-6,-6,-6,-6,-6,-6 },
			{ -3,-4,-5,-1,-2,-5,-4,-3 }
		}
	};

	sf::Sprite chessboard_;
};

