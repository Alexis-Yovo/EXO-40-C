### Code C : Liste d'entiers (Code à utiliser)

```c
typedef struct cellule {
    int iVal;
    struct cellule *suivant;
} cellule;

typedef cellule *liste; 
