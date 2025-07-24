#include "src/grille.h"

int main() {
    int lignes = 4, colonnes = 3;
    Cellule* grille = creer_grille(lignes, colonnes);

    set_valeur(grille, 0, 0, "ID");
    set_valeur(grille, 0, 1, "Nom");
    set_valeur(grille, 0, 2, "Age");

    set_valeur(grille, 1, 0, "1");
    set_valeur(grille, 1, 1, "prenom A");
    set_valeur(grille, 1, 2, "30");

    set_valeur(grille, 2, 0, "2");
    set_valeur(grille, 2, 1, "Prenom B");
    set_valeur(grille, 2, 2, "25");

    set_valeur(grille, 3, 0, "3");
    set_valeur(grille, 3, 1, "Prenom C");
    set_valeur(grille, 3, 2, "28");

    afficher_grille(grille, lignes, colonnes);

    exporter_csv(grille, lignes, colonnes, "save/tableau.csv");

    liberer_grille(grille);
    return 0;
}
