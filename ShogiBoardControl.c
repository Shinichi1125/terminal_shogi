// BoardControl.c

#include "ShogiBoardControl.h"
#include "ShogiPieces.h"

#include <stdio.h>

char EMPTY[JPCH+1] = {' ',' ','\0'};
char TURN[JPCH+1];

static const char* dan_list[] = {"一", "二", "三", "四", "五", "六", "七","八", "九"};

void board_init(void)
{
	//printf("\nInitializing the board\n");
	for(int row = 0; row < ROW; row++)
	{
		for(int column = 0; column < COLUMN; column++)
		{
			strcpy(board[row][column].piece, EMPTY);
			strcpy(board[row][column].color, EMPTY);
			strcpy(board[row][column].status, EMPTY);
		}
	}
}

void pieces_in_hand_init(void)
{
	for(int i = 0; i < MAXPIECES; i++)
	{
		strcpy(pieces_in_hand[i].piece, EMPTY);
		strcpy(pieces_in_hand[i].color, EMPTY);
		strcpy(pieces_in_hand[i].status, EMPTY);
	}
}

void store_piece_in_hand(piece_t piece_input)
{
	if(strcmp(piece_input.piece, "竜") == 0)
	{
		strcpy(piece_input.piece, "飛");
	}

	if(strcmp(piece_input.piece, "馬") == 0)
	{
		strcpy(piece_input.piece, "角");
	}

	turn_change(piece_input.color);

	bool store_done = false;
	for(int i = 0; i < MAXPIECES; i++)
	{
		if(strcmp(pieces_in_hand[i].piece, EMPTY) == 0)
		{
			if(store_done == false)
			{
				strcpy(pieces_in_hand[i].piece, piece_input.piece);
				strcpy(pieces_in_hand[i].color, piece_input.color);
				strcpy(pieces_in_hand[i].status, EMPTY);

				store_done = true;
			}
		}
	}
}

void show_pieces_in_hand(char* turn)
{
	printf("\n");
	for(int i = 0; i < MAXPIECES; i++)
	{
		if(strcmp(pieces_in_hand[i].piece, EMPTY) != 0 && strcmp(pieces_in_hand[i].color, turn) == 0)
		{
			printf("[%d]:%s(%s) ",i, pieces_in_hand[i].piece, pieces_in_hand[i].color);
		}
	}
	printf("\n");
}

void set_all_pieces(void)
{
	//printf("\nSetting the pieces in places\n");
	printf("\n");
	for(int row = 0; row < ROW; row++)
	{
		for(int column = 0; column < COLUMN; column++)
		{
			if(row < 3)
			{
				if(row == 0)
    			{
    				strcpy(board[row][column].color, "後");

	    			if(column == 0 || column == COLUMN-1)
    	        	{
	    	        	strcpy(board[row][column].piece, "香");
		            }
    		        if(column == 1 || column == COLUMN-2)
	     	        {
		        	    strcpy(board[row][column].piece, "桂");
			        }
    			    if(column == 2 || column == COLUMN-3)
	    		    {
		    	    	strcpy(board[row][column].piece, "銀");
			    	}
				    if(column == 3 || column == COLUMN-4)
				    {
					    strcpy(board[row][column].piece, "金");
				    }
    				if(column == 4)
	    			{
		    			strcpy(board[row][column].piece, "玉");
			    	}
			    }
			    if(row == 1)
    			{
    				if(column == 1)
    				{
    					strcpy(board[row][column].color, "後");
    					strcpy(board[row][column].piece, "角");
					}
					else if(column == COLUMN-2)
					{
						strcpy(board[row][column].color, "後");
						strcpy(board[row][column].piece, "飛");
					}
	    			else
	    			{
	    				strcpy(board[row][column].color, EMPTY);
	    				strcpy(board[row][column].piece, EMPTY);
					}
		    	}
		    	if(row == 2)
		    	{
		    		strcpy(board[row][column].color, "後");
					strcpy(board[row][column].piece, "歩");
				}
			}

			if(row >= 3 && row <= 5)
			{
				strcpy(board[row][column].color, EMPTY);
	    		strcpy(board[row][column].piece, EMPTY);
			}

			if(row > 5)
			{
				if(row == ROW-1)
    			{
    				strcpy(board[row][column].color, "先");

	    			if(column == 0 || column == COLUMN-1)
    	        	{
	    	        	strcpy(board[row][column].piece, "香");
		            }
    		        if(column == 1 || column == COLUMN-2)
	     	        {
		        	    strcpy(board[row][column].piece, "桂");
			        }
    			    if(column == 2 || column == COLUMN-3)
	    		    {
		    	    	strcpy(board[row][column].piece, "銀");
			    	}
				    if(column == 3 || column == COLUMN-4)
				    {
					    strcpy(board[row][column].piece, "金");
				    }
    				if(column == 4)
	    			{
		    			strcpy(board[row][column].piece, "玉");
			    	}
			    }
			    if(row == ROW-2)
    			{
    				if(column == 1)
    				{
    					strcpy(board[row][column].color, "先");
    					strcpy(board[row][column].piece, "飛");
					}
					else if(column == COLUMN-2)
					{
						strcpy(board[row][column].color, "先");
						strcpy(board[row][column].piece, "角");
					}
	    			else
	    			{
	    				strcpy(board[row][column].color, EMPTY);
	    				strcpy(board[row][column].piece, EMPTY);
					}
		    	}
		    	if(row == ROW-3)
		    	{
		    		strcpy(board[row][column].color, "先");
					strcpy(board[row][column].piece, "歩");
				}
			}

		}
	}
	printf("\n");
}


void board_print(void)
{
	//printf("\nPrinting out the board\n\n");
    printf("\n");
	printf("    ");

	// "suji" is a term used in shogi, and it means "column"
	for(int suji = COLUMN; suji >= 1; suji--)
	{
		printf("   %d   ", suji);
	}

	printf("\n");

	for(int row = 0; row < ROW; row++)
	{
		printf("    ");
		for(int i = 0; i < COLUMN; i++)
		{
			printf("-------");
		}
		printf("-\n");

        char dsp_status[JPCH+1];
		char dsp_color[JPCH+1];
		char dsp_piece[JPCH+1];
		char dan[JPCH+1];

		printf("    ");
		for(int column = COLUMN-1; column >= 0; column--)
		{
			printf("|");
		    strcpy(dsp_status, board[row][column].status);
			printf("   %s ", dsp_status);
		}
		printf("| ");
		printf("\n");

		strcpy(dan, dan_list[row]);

		printf(" %s ", dan); // Print the row number as well
		for(int column = COLUMN-1; column >= 0; column--)
		{
		    strcpy(dsp_color, board[row][column].color);
		    strcpy(dsp_piece, board[row][column].piece);
			printf("| %s%s ", dsp_color, dsp_piece);
		}
		printf("| ");
		printf(" %s ", dan);  // Print the row number as well
		printf("\n");
	}

	printf("    ");
	for(int i = 0; i < COLUMN; i++)
	{
		printf("-------");
	}
	printf("\n");

	printf("    ");

	// "suji" is a term used in shogi, and it means "column"
	for(int suji = COLUMN; suji >= 1; suji--)
	{
		printf("   %d   ", suji);
	}

	printf("\n\n");
}


// for test purpose
void put_kings(void)
{
	strcpy(board[8][4].piece, "玉");
	strcpy(board[8][4].color, "先");

	strcpy(board[0][4].piece, "玉");
	strcpy(board[0][4].color, "後");
}

move_t ask_movement(void)
{
	move_t move;

	scanf(" %d %d %s", &move.column, &move.row, move.piece_data.piece);

	strcpy(move.piece_data.status, EMPTY);

	return move;
}

bool is_move_valid(move_t old_location, move_t move)
{
	bool check = true;

	if(old_location.row == move.row && old_location.column == move.column)
	{

	}
	else
	{
		// if it's out of boundary, false (column)
		if(move.column <= 0 || move.column > COLUMN)
		{
			check = false;
		}
		// if it's out of boundary, false (row)
		if(move.row <= 0 || move.row > ROW)
		{
			check = false;
		}

		if(strcmp(board[move.row-1][move.column-1].color, EMPTY) != 0)
		{
			check = false;
			printf("You can't place a piece in a square where another piece already exists\n");
		}

		if(strcmp(move.piece_data.color, "先") == 0)
		{
			if(strcmp(move.piece_data.piece, "歩") == 0 || strcmp(move.piece_data.piece, "香") == 0)
			{
				if(move.row == 1)
				{
					check = false;
					printf("The piece has nowhere to go\n");
				}
			}
			if(strcmp(move.piece_data.piece, "桂") == 0)
			{
				if(move.row <= 2)
				{
					check = false;
					printf("The piece has nowhere to go\n");
				}
			}
		}

		if(strcmp(move.piece_data.color, "後") == 0)
		{
			if(strcmp(move.piece_data.piece, "歩") == 0 || strcmp(move.piece_data.piece, "香") == 0)
			{
				if(move.row == 9)
				{
					check = false;
					printf("The piece has nowhere to go\n");
				}
			}
			if(strcmp(move.piece_data.piece, "桂") == 0)
			{
				if(move.row >= 8)
				{
					check = false;
					printf("The piece has nowhere to go\n");
				}
			}
		}

		if(check == false)
		{
			printf("Invalid placement\n");
		}
		// for debugging purpose
		//printf("Column:%d Row:%d Piece:%s\n",move.column, move.row, move.piece_data.piece);
	}

	return check;
}

/*
void print_upside_down(void)
{
	printf("\nPrinting out the board (upside down))\n\n");

	// Print out the alphabets (a-h) above and below the board
	printf("  ");
	for(char alphabet = 'h'; alphabet > 'h' - COLUMN; alphabet--)
	{
		printf("   %c ",alphabet);
	}

	printf("\n");

	for(int row = 0; row < ROW; row++)
	{
		printf("  ");
		for(int i = 0; i < COLUMN; i++)
		{
			printf("-----");
		}
		printf("\n");
		printf("%d ", row + 1); // Print the row number as well

		for(int column = COLUMN - 1; column >= 0; column--)
		{
			printf("| %c%c ", board[row][column].color ,board[row][column].piece);
		}
		printf("| ");
		printf("%d", row + 1);  // Print the row number as well
		printf("\n");
	}

	printf("  ");
	for(int i = 0; i < COLUMN; i++)
	{
		printf("-----");
	}
	printf("\n");

	printf("  ");
	for(char alphabet = 'h'; alphabet > 'h' - COLUMN; alphabet--)
	{
		printf("   %c ",alphabet);
	}

	printf("\n");
}

*/


void turn_change(char* turn)
{
	if(strcmp(turn, "先") == 0)
	{
		strcpy(turn, "後");
	}
	else if(strcmp(turn, "後") == 0)
	{
		strcpy(turn, "先");
	}
}




bool is_color_valid(char* turn, move_t move)
{
	bool result;

	if(strcmp(move.piece_data.color, turn) == 0)
	{
		result = true;
	}
	else
	{
		result = false;
	}

	if(result == false)
	{
		printf("You should pick a piece of your own color\n");
	}

	return result;
}

bool is_two_pawns(bool canceled, move_t move)
{
	bool result = false;

	if(canceled == false)
	{
		if(strcmp(move.piece_data.piece, "歩") == 0)
		{
			for(int i = 0; i < ROW; i++)
			{
				if(strcmp(board[i][move.column-1].piece, "歩") == 0)
				{
					if(strcmp(board[i][move.column-1].color, move.piece_data.color) == 0)
					{
						result = true;
					}
				}
			}
		}
	}

	if(result == true)
	{
		printf("Putting 2 pawns on the same column is not allowed\n");
	}

	return result;
}

bool is_move_canceled(move_t old_location, move_t move)
{
	bool result;

	if(old_location.row == move.row && old_location.column == move.column)
	{
		result = true;
	}
	else
	{
		result = false;
	}

	return result;
}


// experimental function

void add_piece(void)
{
	move_t move;
	move_t old_location;
	bool check;
	int choice;
	char color[JPCH+1];

	do
	{
		printf("Do you want to add a piece? (No:0, 先:1, 後:2)  ");
		scanf("%d",&choice);
	}while(choice != 0 && choice != 1 && choice != 2);

	if(choice != 0)
	{
		if(choice == 1)
		{
			strcpy(color, "先");
		}
		else if(choice == 2)
		{
			strcpy(color, "後");
		}

		do    // Ask the user to choose where and which piece to put
    	{
	    	printf("\nMake your move: ");
		    move = ask_movement();
		    check = is_move_valid(old_location, move);
    	}
	    while(check != true);

	    strcpy(move.piece_data.color, color);
	    strcpy(move.piece_data.status, EMPTY);

    	put_piece(move);   // Put the piece onto the designated location

    	board_print();
	}


}


bool is_king_captured(void)
{
	bool result = false;
	int king_count = 0;

	for(int row = 0; row < ROW; row++)
	{
		for(int column = 0; column < COLUMN; column++)
		{
			if(strcmp(board[row][column].piece, "玉") == 0)
			{
				king_count++;
			}
		}
	}

	if(king_count != 2)
	{
		result = true;
		printf("\nThe king has been captured\n");
	}

	return result;
}




