#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grille.h"

#define MAX_COL 100

Cellule* creer_cellule(const char* valeur) {
    Cellule* nouvelle = malloc(sizeof(Cellule));
    if (!nouvelle) {
        perror("Erreur d'allocation");
        exit(EXIT_FAILURE);
    }
    nouvelle->valeur = strdup(valeur);
    nouvelle->droite = NULL;
    nouvelle->bas = NULL;
    return nouvelle;
}

Cellule* creer_grille(int lignes, int colonnes) {
    if (lignes <= 0 || colonnes <= 0) return NULL;

    Cellule* tete = NULL;
    Cellule* ligne_precedente = NULL;

    for (int i = 0; i < lignes; i++) {
        Cellule* debut_ligne = NULL;
        Cellule* cellule_precedente = NULL;

        for (int j = 0; j < colonnes; j++) {
            Cellule* nouvelle = creer_cellule("");
            if (!debut_ligne) debut_ligne = nouvelle;
            if (cellule_precedente) cellule_precedente->droite = nouvelle;
            cellule_precedente = nouvelle;

            if (ligne_precedente) {
                Cellule* haut = ligne_precedente;
                for (int k = 0; k < j; k++) haut = haut->droite;
                haut->bas = nouvelle;
            }
        }

        if (!tete) tete = debut_ligne;
        ligne_precedente = debut_ligne;
    }

    return tete;
}

void set_valeur(Cellule* tete, int i, int j, const char* val) {
    Cellule* courante = tete;
    for (int x = 0; x < i && courante; x++) courante = courante->bas;
    for (int y = 0; y < j && courante; y++) courante = courante->droite;
    if (courante) {
        free(courante->valeur);
        courante->valeur = strdup(val);
    }
}

static void get_largeurs(Cellule* tete, int* largeurs, int max_col) {
    for (int j = 0; j < max_col; j++) largeurs[j] = 0;

    Cellule* ligne = tete;
    while (ligne) {
        Cellule* cellule = ligne;
        int j = 0;
        while (cellule && j < max_col) {
            int len = strlen(cellule->valeur);
            if (len > largeurs[j]) largeurs[j] = len;
            cellule = cellule->droite;
            j++;
        }
        ligne = ligne->bas;
    }
}

static void afficher_separateur(int* largeurs, int colonnes) {
    printf("+");
    for (int j = 0; j < colonnes; j++) {
        for (int k = 0; k < largeurs[j] + 2; k++) printf("-");
        printf("+");
    }
    printf("\n");
}

void afficher_grille(Cellule* tete, int lignes, int colonnes) {
    int largeurs[MAX_COL];
    get_largeurs(tete, largeurs, colonnes);

    Cellule* ligne = tete;
    for (int i = 0; i < lignes && ligne; i++) {
        afficher_separateur(largeurs, colonnes);
        Cellule* cellule = ligne;
        printf("|");
        for (int j = 0; j < colonnes && cellule; j++) {
            printf(" %-*s ", largeurs[j], cellule->valeur);
            printf("|");
            cellule = cellule->droite;
        }
        printf("\n");
        ligne = ligne->bas;
    }
    afficher_separateur(largeurs, colonnes);
}

void liberer_grille(Cellule* tete) {
    Cellule* ligne = tete;
    while (ligne) {
        Cellule* cellule = ligne;
        Cellule* prochaine_ligne = ligne->bas;
        while (cellule) {
            Cellule* suivante = cellule->droite;
            free(cellule->valeur);
            free(cellule);
            cellule = suivante;
        }
        ligne = prochaine_ligne;
    }
}

void exporter_csv(Cellule* tete, int lignes, int colonnes, const char* nom_fichier) {
    FILE* f = fopen(nom_fichier, "w");
    if (!f) {
        perror("Erreur ouverture fichier");
        return;
    }

    Cellule* ligne = tete;
    for (int i = 0; i < lignes && ligne; i++) {
        Cellule* cellule = ligne;
        for (int j = 0; j < colonnes && cellule; j++) {
            // On écrit la valeur
            fprintf(f, "%s", cellule->valeur);

            // Si ce n’est pas la dernière colonne, ajoute une virgule
            if (j < colonnes - 1) {
                fputc(',', f);
            }
            cellule = cellule->droite;
        }
        fputc('\n', f);
        ligne = ligne->bas;
    }

    fclose(f);
}
