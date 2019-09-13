// Pieces.c

#include "ShogiPieces.h"


#include <stdio.h>

char tom[JPCH+1] = {' ', ' ', '\0'};

void put_piece(move_t put)
{
	strcpy(board[put.row-1][put.column-1].piece, put.piece_data.piece);
	strcpy(board[put.row-1][put.column-1].color, put.piece_data.color);
	strcpy(board[put.row-1][put.column-1].status, put.piece_data.status);
}

move_t choose_piece()
{
	move_t move;

    do
    {
    	printf("Choose which piece to move (column, row): ");
	    scanf(" %d %d", &move.column, &move.row);

	    if(move.column >= 10)
	    {
	    	printf("There must be a space between column and row\n");
		}
	}while(move.column >= 10);

	if(move.column == 0)
	{
		strcpy(move.piece_data.piece, pieces_in_hand[move.row].piece);
		strcpy(move.piece_data.color, pieces_in_hand[move.row].color);
		strcpy(move.piece_data.status, pieces_in_hand[move.row].status);
	}
	else
	{
		strcpy(move.piece_data.piece, board[move.row-1][move.column-1].piece);
		strcpy(move.piece_data.color, board[move.row-1][move.column-1].color);
		strcpy(move.piece_data.status, board[move.row-1][move.column-1].status);
	}

	return move;
}

bool is_choice_valid(move_t move)
{
	bool check = true;
	// if it's out of boundary, false
	if(move.column != 0)
	{
		if(move.column < 0 || move.column > COLUMN)
		{
			check = false;
		}
	}

	// if it's out of boundary, false
	if(move.column > 0)
	{
		if(move.row <= 0 || move.row > ROW)
		{
			check = false;
		}

		if(strcmp(board[move.row-1][move.column-1].piece, tom)==0)
		{
			check = false;
		}
	}
	else
	{
		if(move.row > MAXPIECES)
		{
			check = false;
		}
		if(strcmp(pieces_in_hand[move.row].piece, tom) == 0)
		{
			check = false;
			printf("You can't pick a piece that doesn't exist\n");
		}
	}

	if(check == false)
	{
		printf("Invalid choice\n");
	}

	return check;
}



move_t choose_destination(piece_t piece_data)
{
	move_t move;

	printf("Which square to move the piece to?  ");
	scanf(" %d %d", &move.column, &move.row);

	strcpy(move.piece_data.piece, piece_data.piece);
	strcpy(move.piece_data.color, piece_data.color);
	strcpy(move.piece_data.status, piece_data.status);

	return move;
}


void move_piece(move_t old_location, move_t move)
{
	strcpy(board[old_location.row-1][old_location.column-1].piece, tom);
	strcpy(board[old_location.row-1][old_location.column-1].color, tom);
	strcpy(board[old_location.row-1][old_location.column-1].status, tom);
	strcpy(board[move.row-1][move.column-1].piece, move.piece_data.piece);
	strcpy(board[move.row-1][move.column-1].color, move.piece_data.color);
	strcpy(board[move.row-1][move.column-1].status, move.piece_data.status);
}

bool is_destination_valid(move_t old_location, move_t move)
{
	bool check = true;

	if(old_location.row == move.row && old_location.column == move.column)
	{

	}
	else
	{
		// if it's out of boundary, false
		if(move.column <= 0 || move.column > COLUMN)
		{
			check = false;
		}
		// if it's out of boundary, false
		if(move.row <= 0 || move.row > ROW)
		{
			check = false;
		}

		// check if Pawn's movement is valid
		if(strcmp(move.piece_data.piece, "歩") == 0)
	    {
	    	bool result = check_pawn_movement(old_location, move);
			if(result == false)
			{
				check = false;
			}
		}

		// check if Rook's movement is valid
		if(strcmp(move.piece_data.piece, "飛") == 0)
		{
			bool result = check_vertical_horizontal(old_location, move);
			if(result == false)
			{
				check = false;
			}
		}

		// check if King's movement is valid
		if(strcmp(move.piece_data.piece, "玉") == 0)
		{
			bool result = check_king_movement(old_location, move);
			if(result == false)
			{
				check = false;
			}
		}

		// check if Knight's movement is valid
		if(strcmp(move.piece_data.piece, "桂") == 0)
		{
			bool result;
			if(strcmp(move.piece_data.status, "成") == 0)
		    {
		    	result = check_gold_movement(old_location, move);
			}
			else
			{
				result = check_knight_movement(old_location, move);
			}

			if(result == false)
			{
				check = false;
			}
		}

		// check if Knight's movement is valid
		if(strcmp(move.piece_data.piece, "香") == 0)
		{
			bool result;

			if(strcmp(move.piece_data.status, "成") == 0)
		    {
		    	result = check_gold_movement(old_location, move);
			}
			else
			{
				result = check_lance_movement(old_location, move);
			}

			if(result == false)
			{
				check = false;
			}
		}

		// check if Bishop's movement is valid
		if(strcmp(move.piece_data.piece, "角") == 0)
		{
		    bool result = check_diagonal(old_location, move);
			if(result == false)
			{
				check = false;
			}
		}

		// check if Gold General's movement is valid
		if(strcmp(move.piece_data.piece, "金") == 0 || strcmp(move.piece_data.piece, "と")==0)
		{
		    bool result = check_gold_movement(old_location, move);
			if(result == false)
			{
				check = false;
			}
		}

		// check if Silver General's movement is valid
		if(strcmp(move.piece_data.piece, "銀") == 0)
		{
		    bool result;
		    if(strcmp(move.piece_data.status, "成") == 0)
		    {
		    	result = check_gold_movement(old_location, move);
			}
			else
			{
				result = check_silver_movement(old_location, move);
			}

			if(result == false)
			{
				check = false;
			}
		}

		// check if Dragon's movement is valid
		if(strcmp(move.piece_data.piece, "竜") == 0)
		{
			bool resultVH;
			bool resultD;
			resultVH = check_vertical_horizontal(old_location, move);
			resultD = check_silver_movement(old_location, move);

			if(resultVH == false && resultD == false)
			{
				check = false;
			}
		}

		// check if Horse's movement is valid
		if(strcmp(move.piece_data.piece, "馬") == 0)
		{
			bool resultVH;
			bool resultD;
			resultVH = check_gold_movement(old_location, move);
			resultD = check_diagonal(old_location, move);

			if(resultVH == false && resultD == false)
			{
				check = false;
			}
		}

		if(check == false)
		{
			printf("Invalid destination\n");
		}
    }

    if(strcmp(board[move.row-1][move.column-1].color, move.piece_data.color) != 0)
    {
    	if(strcmp(board[move.row-1][move.column-1].color, tom) != 0)
    	{
    		store_piece_in_hand(board[move.row-1][move.column-1]);
		}
	}

	return check;
}



bool check_pawn_movement(move_t old_location, move_t move)
{
	bool check = true;

	if(strcmp(move.piece_data.color, "先") ==0)
	{

		if(old_location.row == move.row+1&& old_location.column == move.column
   		   && strcmp(board[move.row-1][move.column-1].piece, "先") != 0 ){}
        else
        {
	        check = false;
        }
	}

	if(strcmp(move.piece_data.color, "後") ==0)
	{
		if(old_location.row == move.row-1&& old_location.column == move.column
   		   && strcmp(board[move.row-1][move.column-1].piece, "後") != 0 ){}
        else
        {
	        check = false;
        }
	}

	return check;
}

bool piece_promotion_check(move_t old_location, move_t move)
{
	bool result = false;

    if(strcmp(move.piece_data.status, "成") != 0)
    {
    	if(((strcmp(move.piece_data.piece, "歩")) == 0 || (strcmp(move.piece_data.piece, "香")) == 0
		|| (strcmp(move.piece_data.piece, "桂")) == 0 || (strcmp(move.piece_data.piece, "銀")) == 0
		|| (strcmp(move.piece_data.piece, "角")) == 0 || (strcmp(move.piece_data.piece, "飛")) == 0)
		&& strcmp(move.piece_data.color, "先") == 0 && move.row <= 3 )
		{
			result = true;
		}

		if(((strcmp(move.piece_data.piece, "歩")) == 0 || (strcmp(move.piece_data.piece, "香")) == 0
		|| (strcmp(move.piece_data.piece, "桂")) == 0 || (strcmp(move.piece_data.piece, "銀")) == 0
		|| (strcmp(move.piece_data.piece, "角")) == 0 || (strcmp(move.piece_data.piece, "飛")) == 0)
		&& strcmp(move.piece_data.color, "後") == 0 && move.row > ROW-3 )
		{
			result = true;
		}
	}

	if(strcmp(move.piece_data.color, "先") == 0)
	{
		if(old_location.row <= 3 && strcmp(move.piece_data.status, "成") != 0)
		{
			if(strcmp(move.piece_data.piece, "竜") != 0 && strcmp(move.piece_data.piece, "馬") != 0)
			{
				result = true;
			}
		}
	}

	if(strcmp(move.piece_data.color, "後") == 0)
	{
		if(old_location.row > ROW-3 && strcmp(move.piece_data.status, "成") != 0)
		{
			if(strcmp(move.piece_data.piece, "竜") != 0 && strcmp(move.piece_data.piece, "馬") != 0)
			{
				result = true;
			}
		}
	}

	return result;
}

move_t piece_promote(move_t move)
{
	char promotion;
	do
	{
		printf("Promote? (Y/N) ");
		scanf(" %c",&promotion);
		promotion = toupper(promotion);
	}while(promotion != 'Y'&& promotion != 'N');

    if(promotion == 'Y')
    {
    	if(strcmp(move.piece_data.piece, "歩") == 0)
    	{
    		strcpy(move.piece_data.piece,"と");
		}

    	if(strcmp(move.piece_data.piece, "飛") == 0)
    	{
    		strcpy(move.piece_data.piece,"竜");
		}

		if(strcmp(move.piece_data.piece, "角") == 0)
    	{
    		strcpy(move.piece_data.piece,"馬");
		}

		if(strcmp(move.piece_data.piece, "銀") == 0)
    	{
    		strcpy(move.piece_data.status,"成");
		}

		if(strcmp(move.piece_data.piece, "桂") == 0)
    	{
    		strcpy(move.piece_data.status,"成");
		}

		if(strcmp(move.piece_data.piece, "香") == 0)
    	{
    		strcpy(move.piece_data.status,"成");
		}
	}

	return move;
}

bool check_king_movement(move_t old_location, move_t move)
{
	bool check = true;

	if(old_location.row - move.row < 2 && move.row - old_location.row < 2 &&
		old_location.column - move.column < 2 && move.column - old_location.column < 2
	    && strcmp(board[move.row-1][move.column-1].color, move.piece_data.color) != 0){}
	else
	{
		check = false;
	}

	return check;
}

bool check_gold_movement(move_t old_location, move_t move)
{
	bool check = true;

    if(strcmp(move.piece_data.color, "先") ==0)
    {
    	if(strcmp(board[move.row-1][move.column-1].color, move.piece_data.color) != 0
		&&((old_location.row == move.row+1&& old_location.column == move.column)
		||(old_location.row == move.row-1&& old_location.column == move.column)
		||(old_location.row == move.row && old_location.column == move.column+1)
		||(old_location.row == move.row && old_location.column == move.column-1)
		||(old_location.row == move.row+1 && old_location.column == move.column+1)
		||(old_location.row == move.row+1 && old_location.column == move.column-1))){}
		else
		{
			check = false;
		}
	}

	if(strcmp(move.piece_data.color, "後") ==0)
    {
    	if(strcmp(board[move.row-1][move.column-1].color, move.piece_data.color) != 0
		&&((old_location.row == move.row+1&& old_location.column == move.column)
		||(old_location.row == move.row-1&& old_location.column == move.column)
		||(old_location.row == move.row && old_location.column == move.column+1)
		||(old_location.row == move.row && old_location.column == move.column-1)
		||(old_location.row == move.row-1 && old_location.column == move.column+1)
		||(old_location.row == move.row-1 && old_location.column == move.column-1))){}
		else
		{
			check = false;
		}
	}

	return check;
}

bool check_silver_movement(move_t old_location, move_t move)
{
	bool check = true;

    if(strcmp(move.piece_data.color, "先") ==0)
    {
    	if(strcmp(board[move.row-1][move.column-1].color, move.piece_data.color) != 0
		&&((old_location.row == move.row+1&& old_location.column == move.column)
		||(old_location.row == move.row-1 && old_location.column == move.column+1)
		||(old_location.row == move.row-1 && old_location.column == move.column-1)
		||(old_location.row == move.row+1 && old_location.column == move.column+1)
		||(old_location.row == move.row+1 && old_location.column == move.column-1))){}
		else
		{
			check = false;
		}
	}

	if(strcmp(move.piece_data.color, "後") ==0)
    {
    	if(strcmp(board[move.row-1][move.column-1].color, move.piece_data.color) != 0
		&&((old_location.row == move.row-1&& old_location.column == move.column)
		||(old_location.row == move.row-1 && old_location.column == move.column+1)
		||(old_location.row == move.row-1 && old_location.column == move.column-1)
		||(old_location.row == move.row+1 && old_location.column == move.column+1)
		||(old_location.row == move.row+1 && old_location.column == move.column-1))){}
		else
		{
			check = false;
		}
	}

	return check;
}

bool check_knight_movement(move_t old_location, move_t move)
{
	bool check = true;

    if(strcmp(move.piece_data.color, "先") ==0)
    {
    	if((old_location.row - move.row == 2 && move.column - old_location.column == 1
	        && board[move.row-1][move.column-1].color != move.piece_data.color)
		|| (old_location.row - move.row == 2 && old_location.column - move.column == 1
		    && board[move.row-1][move.column-1].color != move.piece_data.color)){}
		else
		{
			check = false;
		}
	}

	if(strcmp(move.piece_data.color, "後") ==0)
    {
	    if((move.row - old_location.row == 2 && move.column - old_location.column == 1
		   && board[move.row-1][move.column-1].color != move.piece_data.color)
		|| (move.row - old_location.row == 2 && old_location.column - move.column == 1
		   && board[move.row-1][move.column-1].color != move.piece_data.color)){}
		else
		{
			check = false;
		}
	}

	return check;
}

bool check_lance_movement(move_t old_location, move_t move)
{
	bool check = true;
    int distance;
	int blocked = 0;

    if(strcmp(move.piece_data.color, "先") ==0)
    {
    	if(old_location.column == move.column && old_location.row > move.row
		&& (strcmp(board[move.row-1][move.column-1].color, move.piece_data.color) != 0)){}
		else
		{
			check = false;
		}

		distance = old_location.row - move.row;
		if(distance >= 2)
		{
			for(int i = 1; i <= distance;i++)
			{
				if(strcmp(board[old_location.row-1-i][move.column-1].color, tom ) != 0)
				{
					blocked = i;
				}

				if(blocked > 0 && blocked < distance)
				{
					check = false;
				}
			}
		}
	}

	if(strcmp(move.piece_data.color, "後") ==0)
    {
	    if(old_location.column == move.column && old_location.row < move.row
		&& (strcmp(board[move.row-1][move.column-1].color, move.piece_data.color) != 0)){}
		else
		{
			check = false;
		}

		distance = move.row - old_location.row;
		if(distance >= 2)
		{
			for(int i = 1; i <= distance;i++)
			{
				if(strcmp(board[old_location.row-1+i][move.column-1].color, tom ) != 0)
				{
					blocked = i;
				}

				if(blocked > 0 && blocked < distance)
				{
					check = false;
				}
			}
		}
	}



	return check;
}

bool check_vertical_horizontal(move_t old_location, move_t move)
{
	bool check = true;

	// check if the movement is horizontal or vertical
	// and destination is not occupied by another piece of the same color
	if((old_location.row == move.row || old_location.column == move.column)
	  && (strcmp(board[move.row-1][move.column-1].color, move.piece_data.color) != 0)){}
	else
	{
		check = false;
	}


	int blocked = 0;
	int column_distance;

	// save the distance of the horizontal movement (to the right)
	column_distance = move.column - old_location.column;
	if(column_distance >= 2)
    {
		for(int i = 1; i <= column_distance;i++)
		{
			// if there is the opponent's piece that blocks the way, return false
			if(strcmp(board[move.row-1][old_location.column-1+i].color, tom) != 0)
			{
				blocked = i;
			}

			if(blocked > 0 && blocked < column_distance)
			{
				check = false;
			}
		}
	}

	blocked = 0;
	column_distance = old_location.column - move.column;
	if(column_distance >= 2)
	{
		for(int i = 1; i <= column_distance;i++)
		{
			if(strcmp(board[move.row-1][old_location.column-1-i].color, tom) != 0)
			{
				blocked = i;
			}

			if(blocked > 0 && blocked < column_distance)
			{
				check = false;
			}
		}
	}

	blocked = 0;
	int row_distance;
	row_distance = move.row - old_location.row;
	if(row_distance >= 2)
	{
		for(int i = 1; i <= row_distance;i++)
		{
			if(strcmp(board[old_location.row-1+i][move.column-1].color, tom ) != 0)
			{
				blocked = i;
			}

			if(blocked > 0 && blocked < row_distance)
			{
				check = false;
			}
		}
	}

	blocked = 0;
	row_distance = old_location.row - move.row;
	if(row_distance >= 2)
	{
		for(int i = 1; i <= row_distance;i++)
		{
			if(strcmp(board[old_location.row-1-i][move.column-1].color, tom) != 0)
			{
				blocked = i;
			}

			if(blocked > 0 && blocked < row_distance)
			{
				check = false;
			}
		}
	}

	return check;
}

bool check_diagonal(move_t old_location, move_t move)
{
	bool check = true;

	if(((move.column - old_location.column == move.row - old_location.row)
	|| ((move.column - old_location.column) + (move.row - old_location.row) == 0))
	&& (strcmp(board[move.row-1][move.column-1].color, move.piece_data.color) != 0)){}
	else
	{
		check = false;
	}

	// check if there is an obstacle on the way (right up)
	int distance;
	int blocked = 0;
	if(old_location.row < move.row && old_location.column < move.column)
	{
	    distance = move.column - old_location.column;
	    if(distance >= 2)
	    {
	    	for(int i = 1; i <= distance; i++)
	    	{
				if(strcmp(board[old_location.row-1+i][old_location.column-1+i].color, tom) != 0)
				{
					blocked = i;
				}

				if(blocked > 0 && blocked < distance)
				{
					check = false;
				}
			}
		}
	}

	// check if there is an obstacle on the way (left down)
	blocked = 0;
	if(move.row < old_location.row && move.column < old_location.column)
	{
		distance = old_location.column - move.column;
		if(distance >= 2)
	    {
	    	for(int i = 1; i <= distance; i++)
	    	{
				if(strcmp(board[old_location.row-1-i][old_location.column-1-i].color,tom) != 0)
				{
					blocked = i;
				}

				if(blocked > 0 && blocked < distance)
				{
					check = false;
				}
			}
		}
	}

	// check if there is an obstacle on the way (right down)
	blocked = 0;
	if(move.row < old_location.row && old_location.column < move.column)
	{
		distance = move.column - old_location.column;
		if(distance >= 2)
	    {
	    	for(int i = 1; i <= distance; i++)
	    	{
				if(strcmp(board[old_location.row-1-i][old_location.column-1+i].color, tom) != 0)
				{
					blocked = i;
				}

				if(blocked > 0 && blocked < distance)
				{
					check = false;
				}
			}
		}
	}

	// check if there is an obstacle on the way (left up)
	blocked = 0;
	if(old_location.row < move.row && move.column < old_location.column)
	{
		distance = old_location.column - move.column;
		if(distance >= 2)
	    {
	    	for(int i = 1; i <= distance; i++)
	    	{
				if(strcmp(board[old_location.row-1+i][old_location.column-1-i].color, tom) != 0)
				{
					blocked = i;
				}

				if(blocked > 0 && blocked < distance)
				{
					check = false;
				}
			}
		}
	}

	return check;
}







