// Pieces.h

#ifndef __SHOGIPIECES_H__
#define __SHOGIPIECES_H__

#include "ShogiBoardControl.h"

#include <stdbool.h>
#include <ctype.h>
#include <string.h>

void put_piece(move_t put);

move_t choose_piece();

bool is_choice_valid(move_t move);

move_t choose_destination(piece_t piece_data);

void move_piece(move_t old_location, move_t move);

bool is_destination_valid(move_t old_location, move_t move);

bool check_pawn_movement(move_t old_location, move_t move);

bool piece_promotion_check(move_t old_location, move_t move);

move_t piece_promote(move_t move);

bool check_king_movement(move_t old_location, move_t move);

bool check_gold_movement(move_t old_location, move_t move);

bool check_silver_movement(move_t old_location, move_t move);

bool check_knight_movement(move_t old_location, move_t move);

bool check_lance_movement(move_t old_location, move_t move);

bool check_vertical_horizontal(move_t old_location, move_t move);


bool check_diagonal(move_t old_location, move_t move);


#endif



