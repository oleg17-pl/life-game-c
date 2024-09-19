#ifndef LIFEGAME_H
#define LIFEGAME_H

#include <stdlib.h>

typedef char cell_t;
typedef char bool_t;
typedef size_t coord_t;

typedef struct game_field {
	size_t SIZEX, SIZEY;
	cell_t **value;
} game_field_t;

typedef game_field_t *p_game_field_t;
typedef p_game_field_t *pp_game_field_t;

p_game_field_t create_field(const size_t x, const size_t y);
void init_byrandom(p_game_field_t const field);
bool_t is_alive_cell(const p_game_field_t const field, const coord_t x, const coord_t y);
void clear(p_game_field_t field);
int count_alive_cells(const p_game_field_t const field);
void step(pp_game_field_t field);
void draw(const p_game_field_t const field, coord_t xpos, coord_t ypos);

#endif // !LIFEGAME_H