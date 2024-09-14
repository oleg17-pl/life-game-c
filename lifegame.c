#include <stdio.h>
#include "lifegame.h"

static void copy_field(const p_game_field_t const from, p_game_field_t const to) {
    const size_t sx = from->SIZEX, sy = from->SIZEY;
    to->SIZEX = sx;
    to->SIZEY = sy;
    for (size_t y = 0; y < sy; y++) {
        for (size_t x = 0; x < sx; x++) {
            to->value[y][x] = from->value[y][x];
        }
    }
}

p_game_field_t create_field(const size_t x, const size_t y) {
    p_game_field_t field = (p_game_field_t)malloc(sizeof(game_field_t));
    field->SIZEX = x;
    field->SIZEY = y;
    field->value = (cell_t **)malloc(sizeof(cell_t *) * y);
    for (size_t row = 0; row < y; row++) {
        field->value[row] = (cell_t *)malloc(sizeof(cell_t) * x);
    }
    return field;
}

void init_byrandom(p_game_field_t const field) {
    const size_t sx = field->SIZEX, sy = field->SIZEY;
    for (size_t y = 0; y < sy; y++) {
        for (size_t x = 0; x < sx; x++) {
            field->value[y][x] = rand() % 2;
        }
    }
}

bool_t is_alive_cell(const p_game_field_t const field, const coord_t x, const coord_t y) {
    const size_t sx = field->SIZEX, sy = field->SIZEY;
    if (x < 0 || y < 0 || x >= sx || y >= sy) {
        return 0;
    }
    return field->value[y][x];
}

void clear(p_game_field_t field) {
    for (size_t row = 0; row < field->SIZEY; row++) {
        free(field->value[row]);
    }
    free(field->value);
    free(field);
}

int count_alive_cells(const p_game_field_t const field) {
    const size_t sx = field->SIZEX, sy = field->SIZEY;
    int count = 0;
    for (size_t y = 0; y < sy; y++) {
        for (size_t x = 0; x < sx; x++) {
            count += field->value[y][x];
        }
    }
    return count;
}

void step(pp_game_field_t pfield) {
    if (count_alive_cells(*pfield) == 0) {
        return;
    }
    const size_t sx = (*pfield)->SIZEX, sy = (*pfield)->SIZEY;
    p_game_field_t new_field = create_field(sx, sy);
    for (size_t y = 0; y < sy; y++) {
        for (size_t x = 0; x < sx; x++) {
            int neighbours = 0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (i != 0 || j != 0) {
                        neighbours += is_alive_cell(*pfield, x + i, y + j);
                    }
                }
            }
            if (neighbours < 2 || neighbours > 3) {
                new_field->value[y][x] = 0;
            }
            else if (neighbours == 3) {
                new_field->value[y][x] = 1;
            }
            else {
                new_field->value[y][x] = (*pfield)->value[y][x];
            }
        }
    }
    clear(*pfield);
    *pfield = new_field;
}

void print(const p_game_field_t const field, coord_t xpos, coord_t ypos) {
    for (size_t i = 0; i < ypos; ++i) {
        printf("\n");
    }
    for (size_t y = 0; y < field->SIZEY; y++) {
        for (size_t i = 0; i < xpos; ++i) {
            printf(" ");
        }
        for (size_t x = 0; x < field->SIZEX; x++) {
            printf(field->value[y][x] ? "#" : ".");
        }
        printf("\n");
    }
}