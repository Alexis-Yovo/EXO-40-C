#include <stdio.h>
#include <stdlib.h>

// Définition de la structure
typedef struct cellule {
    int iVal;
    struct cellule *suivant;
} cellule;

typedef cellule *liste;

// Fonction 1 : Recherche d'une valeur
int recherche(liste tete, int valeur) {
    if (tete == NULL) return 0; // Liste vide

    cellule *courant = tete;
    do {
        if (courant->iVal == valeur) {
            return 1; // Trouvé
        }
        courant = courant->suivant;
    } while (courant != tete); // Boucle jusqu'au retour à la tête

    return 0; // Non trouvé
}

// Fonction 2 : Ajout en tête
void ajoutEnTete(liste *tete, int valeur) {
    cellule *nouvelle = (cellule*)malloc(sizeof(cellule));
    if (!nouvelle) {
        fprintf(stderr, "Erreur d'allocation\n");
        exit(1);
    }
    nouvelle->iVal = valeur;

    if (*tete == NULL) {
        // Liste vide : la nouvelle cellule pointe sur elle-même
        nouvelle->suivant = nouvelle;
        *tete = nouvelle;
    } else {
        // Insérer avant la tête
        nouvelle->suivant = *tete;

        // Trouver la dernière cellule (celle qui pointe sur la tête)
        cellule *derniere = *tete;
        while (derniere->suivant != *tete) {
            derniere = derniere->suivant;
        }

        // Mettre à jour le dernier pour qu'il pointe sur la nouvelle tête
        derniere->suivant = nouvelle;

        // Mettre à jour la tête
        *tete = nouvelle;
    }
}

// Fonction 3 : Suppression d'une valeur
void suppression(liste *tete, int valeur) {
    if (*tete == NULL) return;

    cellule *courant = *tete;
    cellule *precedent = NULL;

    do {
        if (courant->iVal == valeur) {
            // Cas 1 : liste à un seul élément
            if (courant->suivant == courant) {
                free(courant);
                *tete = NULL;
                return;
            }

            // Si on supprime la tête, on doit mettre à jour *tete
            if (courant == *tete) {
                // Trouver le dernier élément pour mettre à jour son suivant
                cellule *dernier = *tete;
                while (dernier->suivant != *tete) {
                    dernier = dernier->suivant;
                }
                // Le dernier doit maintenant pointer vers la nouvelle tête
                dernier->suivant = courant->suivant;
                *tete = courant->suivant;
            } else {
                // Suppression en milieu ou fin
                precedent->suivant = courant->suivant;
            }

            free(courant);
            return;
        }
        precedent = courant;
        courant = courant->suivant;
    } while (courant != *tete);
}

// Fonction d'affichage (pour débogage)
void afficher(liste tete) {
    if (tete == NULL) {
        printf("Liste vide\n");
        return;
    }

    cellule *courant = tete;
    printf("Liste circulaire : ");
    do {
        printf("%d ", courant->iVal);
        courant = courant->suivant;
    } while (courant != tete);
    printf("(retour à %d)\n", tete->iVal);
}

// Fonction principale de test
int main() {
    liste tete = NULL;

    printf("=== Exercice 40 : Liste circulaire (tête) ===\n\n");

    // Ajout
    ajoutEnTete(&tete, 10);
    ajoutEnTete(&tete, 20);
    ajoutEnTete(&tete, 30);
    afficher(tete); // 30 20 10

    // Recherche
    printf("Recherche 20 : %s\n", recherche(tete, 20) ? "Trouvé" : "Non trouvé");
    printf("Recherche 50 : %s\n", recherche(tete, 50) ? "Trouvé" : "Non trouvé");

    // Suppression
    suppression(&tete, 20);
    afficher(tete); // 30 10

    suppression(&tete, 30);
    afficher(tete); // 10

    suppression(&tete, 10);
    afficher(tete); // Liste vide

    return 0;
}
