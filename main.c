// main.c

#include "ShogiBoardControl.h"
#include "ShogiPieces.h"

#include <stdio.h>

char empty[JPCH+1] = {' ', ' ', '\0'};
char turn[JPCH+1];

int main(void)
{
    board_init();  // Initialize the chess board
	pieces_in_hand_init();
	set_all_pieces();
	board_print();  // Print out the chess board

	move_t move;
	move_t old_location;
	move_t drop_number;
	int drop_or_move;

	bool check;
	bool color_check;
	bool nifu_check;
	bool promotion_check;
	bool game_end = false;
	bool move_canceled = false;

	strcpy(move.piece_data.color, "先");  // set the color 先 by default
	strcpy(turn, "先");

	while(game_end == false)
	{
        do
        {
        	do    // Ask the user to choose which piece to move
	    	{
	    		printf("\n%s, it's your turn\n", turn);
		    	move = choose_piece();
			    check = is_choice_valid(move);
			    color_check = is_color_valid(turn, move);
		    }
		    while(check != true || color_check != true);

	        drop_or_move = move.column;

        	if(move.column == 0) // if the user chose to drop a piece
	        {
	        	drop_number.column = move.column;
	        	drop_number.row = move.row;  // keep the track of which element of the array was chosen

	        	do
	        	{
	        		move = choose_destination(move.piece_data);
	        		check = is_move_valid(drop_number, move);

	        		move_canceled = is_move_canceled(drop_number, move);
	        		nifu_check = is_two_pawns(move_canceled, move);
				}while(check != true || nifu_check == true);
			}
			else  // if the user chose to move a piece that exists on the board
			{
				old_location.column = move.column;
		        old_location.row = move.row;
		        strcpy(old_location.piece_data.piece, move.piece_data.piece);
		        strcpy(old_location.piece_data.color, move.piece_data.color);
		        strcpy(old_location.piece_data.status, move.piece_data.status);

		        do    // The user moves the piece
			    {
				    move = choose_destination(move.piece_data);
				    check = is_destination_valid(old_location, move);

				    move_canceled = is_move_canceled(old_location, move);

				    if(check == true)
				    {
				    	promotion_check = piece_promotion_check(old_location, move);
					    if(promotion_check == true)
					    {
					    	move = piece_promote(move);
						}
					}
		    	}
			    while(check != true);
			}
		}while(move_canceled == true);

		move_canceled = false;

        if(drop_or_move == 0)
        {
        	strcpy(pieces_in_hand[drop_number.row].color, empty);
			strcpy(pieces_in_hand[drop_number.row].piece, empty);
			strcpy(pieces_in_hand[drop_number.row].status, empty);

        	put_piece(move);
		}
		else
		{
			move_piece(old_location, move);
		}

        show_pieces_in_hand("後");

    	board_print();

    	show_pieces_in_hand("先");

    	game_end = is_king_captured();

    	turn_change(turn);

	}

	return 0;
}




