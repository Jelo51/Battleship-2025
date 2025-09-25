#include "board/board.h"

int main() {
    Board board;
    int missed_shots = 0;
    int max_misses = 50;
    int total_shots = 0;

    // Initialisation du jeu
    init_board(&board);

    printf("Bienvenue dans la Bataille Navale !\n");
    printf("Objectif : Coulez tous les navires ennemis.\n");
    printf("Limite : maximum %d tirs manques autorises.\n", max_misses);

    // Choix du placement des navires
    choose_placement(&board);

    // Boucle de jeu principale
    while (1) {
        print_board(&board);
        printf("\nStatistiques : %d tirs manques / %d autorises, %d tirs total\n",
               missed_shots, max_misses, total_shots);

        Position pos = get_player_input();

        // Verification de l'entree
        if (pos.row == -1 || pos.col == -1) {
            printf("Entree invalide ! Essayez encore (ex: B5).\n");
            continue;
        }

        int result = attack(&board, pos);

        // Gestion du compteur de tirs manques
        if (result == 0) {
            missed_shots++;
            total_shots++;
        } else if (result == 1) {
            total_shots++;
        }
        // Si result == -1 (deja attaque ou erreur), on ne compte pas le tir

        // Verification de la victoire
        if (check_victory(&board)) {
            print_board(&board);
            printf("\nFELICITATIONS !\n");
            printf("Tous les navires sont coules ! Vous avez gagne !\n");
            printf("Statistiques finales : %d tirs manques, %d tirs total\n", missed_shots, total_shots);
            break;
        }

        // Verification de la defaite
        if (missed_shots >= max_misses) {
            print_board(&board);
            printf("\nVOUS AVEZ PERDU !\n");
            printf("Vous avez depasse la limite de %d tirs manques.\n", max_misses);
            printf("Il restait encore des navires sur le plateau.\n");
            break;
        }
    }

    return 0;
}
