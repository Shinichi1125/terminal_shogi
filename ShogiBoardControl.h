// BoardControl.h

#ifndef __SHOGIBOARDCONTROL_H__
#define __SHOGIBOARDCONTROL_H__

#define ROW 9
#define COLUMN 9
#define JPCH 2
#define MAXPIECES 40

#include <ctype.h>
#include <stdbool.h>

typedef struct piece_data
{
	char piece[JPCH+1];
	char color[JPCH+1];
	char status[JPCH+1];
}piece_t;

piece_t board[ROW][COLUMN];
piece_t pieces_in_hand[MAXPIECES];

typedef struct movement
{
    int column;
	int row;
	piece_t piece_data;
}move_t;

void board_init(void);

void pieces_in_hand_init(void);

void store_piece_in_hand(piece_t piece_input);

void show_pieces_in_hand(char* turn);

void set_all_pieces(void);

void board_print(void);

void put_kings(void);

move_t ask_movement(void);

bool is_move_valid(move_t old_location, move_t move);

//void print_upside_down(void);

void turn_change(char* turn);

bool is_color_valid(char* turn, move_t move);

bool is_two_pawns(bool canceled, move_t move);

bool is_move_canceled(move_t old_location, move_t move);

void add_piece(void);

bool is_king_captured(void);


#endif



