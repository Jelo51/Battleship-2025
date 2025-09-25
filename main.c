#include "board/board.h"

int main() {
    Board board;

    // Initialisation du jeu
    init_board(&board);
    place_ships(&board);

    printf("Bienvenue dans la Bataille Navale !\n");
    printf("Objectif : Coulez tous les navires ennemis.\n");

    // Boucle de jeu principale
    while (1) {
        print_board(&board);

        Position pos = get_player_input();

        // Vérification de l'entrée
        if (pos.row == -1 || pos.col == -1) {
            printf("Entrée invalide ! Essayez encore (ex: B5).\n");
            continue;
        }

        attack(&board, pos);

        // Vérification de la victoire
        if (check_victory(&board)) {
            print_board(&board);
            printf("\nFÉLICITATIONS !\n");
            printf("Tous les navires sont coulés ! Vous avez gagné !\n");
            break;
        }
    }

    return 0;
}
