#ifndef GRILLE_H
#define GRILLE_H

typedef struct Cellule {
    char* valeur;
    struct Cellule* droite;
    struct Cellule* bas;
} Cellule;

Cellule* creer_cellule(const char* valeur);
Cellule* creer_grille(int lignes, int colonnes);
void set_valeur(Cellule* tete, int i, int j, const char* val);
void afficher_grille(Cellule* tete, int lignes, int colonnes);
void liberer_grille(Cellule* tete);
void exporter_csv(Cellule* tete, int lignes, int colonnes, const char* nom_fichier);

#endif