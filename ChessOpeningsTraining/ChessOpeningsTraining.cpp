﻿#include <SFML/Graphics.hpp>
#include <iostream>
#include "Chessboard.h"
int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "Chess Openings Training Tool");
	Chessboard chessboard;
	chessboard.initChessboard();

	bool left_button_flag = false; //true if LMB is being hold
	sf::Sprite *selected_piece = nullptr;
	sf::Vector2f original_piece_position;
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
					selected_piece = chessboard.checkIfWasSelected(sf::Mouse::getPosition(window));
					left_button_flag = true;
					if (selected_piece != nullptr)
						original_piece_position = selected_piece->getPosition();
					
				}
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left && left_button_flag)
				{
						left_button_flag = false;
			
				}
			}
		}

		//Update selected piece position (only to display)
		if (left_button_flag && selected_piece != nullptr)
		{
			chessboard.set_piece_position(selected_piece, sf::Mouse::getPosition(window));
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
	
		//display
		window.display();

	}
}


