#include <time.h>
#include <conio.h>
#include <stdio.h>
#include "lifegame.h"

int main(void) {
    srand(time(NULL));
    p_game_field_t field = create_field(25, 15);
    init_byrandom(field);
    char game = 1;
    
    while (game) {
        system("cls");

        printf("Life Game");
        draw(field, 0, 2);
        printf("\n");
        printf("Alive cells: %i\n", count_alive_cells(field));
        printf("Press zero to exit...");

        char input = (char)_getch();
        game = input != '0';
        step(&field);
    }

    clear(field);
    return 0;
}