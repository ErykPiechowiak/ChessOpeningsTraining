#include "Chessboard.h"
#include <iostream>
#include <math.h>

Chessboard::Chessboard()
{
	chessboard_texture_.loadFromFile("chessboard.jpg");
	flipped_chessboard_texture_.loadFromFile("chessboard_flipped2.jpg");
	chess_pieces_texture_.loadFromFile("chess_pieces.png");
	empty_texture_.create(60, 60);
	
	//assigning every square its position on the board
	int offset = 42;
	int y = 0;
	for (int i = 0; i < 8; i++)
	{
		s_chess_pieces_[i][0].setPosition(offset, offset + y);
		for (int j = 1; j < 8; j++)
		{
			s_chess_pieces_[i][j].setPosition(s_chess_pieces_[i][j - 1].getPosition().x + 63+1.5, s_chess_pieces_[i][j - 1].getPosition().y);
		}
		y += 63+2;
	}
	sf::FloatRect boundingBox;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			boundingBox = s_chess_pieces_[i][j].getGlobalBounds();
			
			std::cout << boundingBox.left << " " << boundingBox.top << " " << boundingBox.height << " "<< boundingBox.width << std::endl;
		}
	}
}	

sf::Sprite Chessboard::get_chessboard()
{
	return chessboard_;
}

sf::Sprite Chessboard::get_square(int row, int column) const
{
	return s_chess_pieces_[row][column];
}


void Chessboard::set_piece_position(sf::Sprite * square, sf::Vector2f position, int offset)
{
	square->setPosition(position.x - offset, position.y - offset);
}
void Chessboard::set_piece_position(sf::Sprite * square, sf::Vector2i position, int offset)
{
	square->setPosition(position.x - offset, position.y - offset);
}

void Chessboard::initChessboard()
{
	chessboard_.setTexture(chessboard_texture_);
//	int y;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{

			set_piece_texture(i, j);
		}
	}

}

void Chessboard::resetChessboard()
{

}

sf::Sprite * Chessboard::checkIfWasSelected(sf::Vector2i point, int &row, int &column)
{
	sf::FloatRect boundingBox;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			boundingBox = s_chess_pieces_[i][j].getGlobalBounds();
			if (boundingBox.contains((float)point.x, (float)point.y) && chess_pieces_[i][j] != 0)
			{
				row = i;
				column = j;
				return &s_chess_pieces_[i][j];
			}
		}
	}
	return nullptr;
}

bool Chessboard::checkIfLegal(sf::Vector2i mouse_position, int &row, int &col, sf::Vector2f original_position)
{
	sf::FloatRect boundingBox;
	std::cout << std::endl;
	//change selected piece position to the original one (the position before drawing)
	s_chess_pieces_[row][col].setPosition(original_position);
	int modifier = 1; 
	if (flipped)
		modifier = -1;//if board is flipped - change pawns movement
	
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			boundingBox = s_chess_pieces_[i][j].getGlobalBounds();

			//Check if it's the right square
			if (boundingBox.contains((float)mouse_position.x, (float)mouse_position.y))
			{
				//Check if the move is legal

				//white pawn 
				if (chess_pieces_[row][col] == -6 && white_move_)
				{
					//one square forward
					if ((i == row - (1*modifier) && j == col) && chess_pieces_[i][j] == 0)
					{
						makeMove(row, col, i, j);
						return true;
					}
					//two squares forward
					if ((i == row - (2*modifier) && j == col && (row == 6 || row == 1)) && chess_pieces_[i][j] == 0 && chess_pieces_[i + (1*modifier)][j] == 0)
					{
						chess_pieces_[i + (1*modifier)][j] = -10;
						white_en_passant_ = &chess_pieces_[i + (1*modifier)][j];
						makeMove(row, col, i, j);
						return true;
					}
					//captures
					if (i == row - (1*modifier) && (j == col - 1 || j == col + 1) && chess_pieces_[i][j] > 0 && chess_pieces_[i][j] != 2)
					{
						//check en passant
						if (chess_pieces_[i][j] == 10)
						{
							chess_pieces_[i + (1*modifier)][j] = 0;
							set_piece_texture(i + (1*modifier), j);
						}
						makeMove(row, col, i, j);
						return true;
					}
				}
				//black pawn
				if (chess_pieces_[row][col] == 6 && !white_move_)
				{
					//one squares forward
					if ((i == row + (1*modifier) && j == col) && chess_pieces_[i][j] == 0)
					{
						makeMove(row, col, i, j);
						return true;
					}
					//two squares forward
					if ((i == row + (2*modifier) && j == col && (row == 1 || row == 6)) && chess_pieces_[i][j] == 0 && chess_pieces_[i - (1*modifier)][j] == 0)
					{
						chess_pieces_[i - (1*modifier)][j] = 10;
						black_en_passant_ = &chess_pieces_[i - (1*modifier)][j];
						makeMove(row, col, i, j);
						return true;
					}
					//captures
					if (i == row + (1*modifier) && (j == col - 1 || j == col + 1) && chess_pieces_[i][j] < 0 && chess_pieces_[i][j] != -2)
					{
						//Check en passant
						if (chess_pieces_[i][j] == -10)
						{
							chess_pieces_[i - (1*modifier)][j] = 0;
							set_piece_texture(i - (1*modifier), j);
						}
						makeMove(row, col, i, j);
						return true;
					}
				}
				//white knight
				if ((chess_pieces_[row][col] == -4 && white_move_))
				{
					if ((i == row + 2 || i == row -2 && j == col + 1 || j == col -1) ||
						(i == row + 1 || i == row - 1 && j == col + 2 || j == col -2) && chess_pieces_[i][j] >= 0)
					{
						makeMove(row, col, i, j);
						return true;
					}
				}
				//black knight
				if ((chess_pieces_[row][col] == 4 && !white_move_))
				{
					if ((i == row + 2 || i == row - 2 && j == col + 1 || j == col - 1) ||
						(i == row + 1 || i == row - 1 && j == col + 2 || j == col - 2) && chess_pieces_[i][j] <= 0)
					{
						makeMove(row, col, i, j);
						return true;
					}
				}
				//white bishop
				if (chess_pieces_[row][col] == -5 && white_move_)
				{
					if (abs(row - i) == abs(col - j) && chess_pieces_[i][j] >= 0)
					{
						if (checkBishopMove(i, j, row, col))
						{
							makeMove(row, col, i, j);
							return true;
						}
					}
				}
				//black bishop
				if (chess_pieces_[row][col] == 5 && !white_move_)
				{
					if (abs(row - i) == abs(col - j) && chess_pieces_[i][j] <= 0)
					{
						if (checkBishopMove(i, j, row, col))
						{
							makeMove(row, col, i, j);
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

void Chessboard::flipBoard()
{
	flipped = !flipped;
	if (flipped)
		chessboard_.setTexture(flipped_chessboard_texture_);
	else
		chessboard_.setTexture(chessboard_texture_);

	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			//change game logic 
			std::swap(chess_pieces_[i][j], chess_pieces_[7 - i][7 - j]);
			//change textures
			set_piece_texture(i, j);
			set_piece_texture(7 - i, 7 - j);
		}
	}
}

void Chessboard::set_piece_texture(int row, int col)
{
	int y = 0;
	if (chess_pieces_[row][col] != 0)
	{
		if (chess_pieces_[row][col] < 0)
			y = 60;
		s_chess_pieces_[row][col].setTexture(chess_pieces_texture_);
		s_chess_pieces_[row][col].setTextureRect(sf::IntRect(abs(chess_pieces_[row][col]) * 60 - 60, y, 60, 60));
	}
	else
	{
		s_chess_pieces_[row][col].setTexture(empty_texture_);
		s_chess_pieces_[row][col].setTextureRect(sf::IntRect(abs(chess_pieces_[row][col]) * 60 - 60, y, 60, 60));
	}
}

bool Chessboard::checkBishopMove(int new_row, int new_col, int old_row, int old_col)
{
	int row_step;
	int col_step;
	int temp_i = new_row;
	int temp_j = new_col;
	new_row - old_row > 0 ? row_step = -1 : row_step = 1;
	new_col - old_col > 0 ? col_step = -1 : col_step = 1;
	temp_i += row_step;
	temp_j += col_step;
	while (temp_i != old_row || temp_j != old_col)
	{
		if (chess_pieces_[temp_i][temp_j] != 0)
			return false;

		temp_i += row_step;
		temp_j += col_step;
	}

	return true;
}

void Chessboard::printPiecePositions()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			std::cout << chess_pieces_[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void Chessboard::makeMove(int & row, int & col, int i, int j)
{

	if (white_en_passant_ != nullptr)
		checkEnPassant(white_en_passant_, white_en_passant_flag_);
	if (black_en_passant_ != nullptr)
		checkEnPassant(black_en_passant_, black_en_passant_flag_);

	chess_pieces_[i][j] = chess_pieces_[row][col];
	chess_pieces_[row][col] = 0;
	//std::swap(chess_pieces_[i][j], chess_pieces_[row][col]);
	printPiecePositions();
	set_piece_texture(i, j);
	set_piece_texture(row, col);
	white_move_ = !white_move_;
	row = -1;
	col = -1;

		
}

void Chessboard::checkEnPassant(int *&en_passant, bool &en_passant_flag)
{
	if (en_passant != nullptr && en_passant_flag)
	{
		*en_passant = 0;	
		en_passant = nullptr;
		en_passant_flag = false;
	}
	if (en_passant != nullptr)
		en_passant_flag = true;
}

