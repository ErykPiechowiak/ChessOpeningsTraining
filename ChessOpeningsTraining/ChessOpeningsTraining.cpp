#include <SFML/Graphics.hpp>
#include <iostream>
#include "Chessboard.h"
#include "Options.h"
int main()
{
	sf::RenderWindow window(sf::VideoMode(650, 600), "Chess Openings Training Tool");
	Chessboard chessboard;
	Options options(&chessboard);
	chessboard.initChessboard();

	bool left_button_flag = false; //true if LMB is being hold
	sf::Sprite *selected_piece = nullptr;
	sf::Sprite *selected_option = nullptr;
	sf::Vector2f original_piece_position;
	int piece_row = -1, piece_col = -1; //Indexes of chosen chess piece
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			//close request 
			if (event.type == sf::Event::Closed)
				window.close();
			//check if a chess piece was selected
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left && !left_button_flag)
				{
					//Check if chess piece was selected
					selected_piece = chessboard.checkIfWasSelected(sf::Mouse::getPosition(window),piece_row, piece_col);
					left_button_flag = true;

					if (selected_piece != nullptr)
						original_piece_position = selected_piece->getPosition();

					//Check if any available option was selected
					options.checkIfWasSelected(sf::Mouse::getPosition(window));
					//selected_option = options.checkIfWasSelected(sf::Mouse::getPosition(window));
					//if (selected_option != nullptr)
					//{
					//	chessboard.flipBoard();
					//}
					
				}
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left && left_button_flag)
				{
					left_button_flag = false;
					//If chess piece was selected, reset its position
					if (selected_piece != nullptr && !chessboard.checkIfLegal(sf::Mouse::getPosition(window), piece_row, piece_col,original_piece_position))
					{				
						chessboard.set_piece_position(selected_piece, original_piece_position);

					}
					selected_piece = nullptr;
					piece_row = -1;
					piece_col = -1;

				}
			}
		}

		//Update selected piece position (only to display)
		if (left_button_flag && selected_piece != nullptr)
		{
			chessboard.set_piece_position(selected_piece, sf::Mouse::getPosition(window), 30);
		}

		window.clear();
		//draw chessboard
		window.draw(chessboard.get_chessboard());
		
		//draw pieces
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
			{
				sf::Sprite sprite_to_draw = chessboard.get_square(i, j);
				window.draw(sprite_to_draw);
			}
		//draw options
		window.draw(options.get_options());
		//display
		window.display();
		//selected_option = nullptr;

	}
}


