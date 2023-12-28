#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VOITURES 100
#define MAX_LOCATIONS 1000

typedef struct {
    int id;
    char marque[50];
    char modele[50];
    char etat[20];
} Voiture;

typedef struct {
    int idVoiture;
    char date[20];
    char etatVoiture[50];
} Location;

Voiture voituresDisponibles[MAX_VOITURES];
Location historiqueLocations[MAX_LOCATIONS];

int nbVoitures = 0;
int nbLocations = 0;

void louerVoiture(int idVoiture, char date[20], char etatVoiture[50]) {
    for (int i = 0; i < nbVoitures; i++) {
        if (voituresDisponibles[i].id == idVoiture) {
            strcpy(voituresDisponibles[i].etat, etatVoiture);

            // Ajout de la location à l'historique
            historiqueLocations[nbLocations].idVoiture = idVoiture;
            strcpy(historiqueLocations[nbLocations].date, date);
            strcpy(historiqueLocations[nbLocations].etatVoiture, etatVoiture);
            nbLocations++;

            printf("La voiture avec l'ID %d a été louée avec succès.\n", idVoiture);
            return;
        }
    }
    printf("La voiture avec l'ID %d n'a pas été trouvée.\n", idVoiture);
}

void afficherDescription(int idVoiture) {
    for (int i = 0; i < nbVoitures; i++) {
        if (voituresDisponibles[i].id == idVoiture) {
            printf("ID : %d\nMarque : %s\nModele : %s\nEtat : %s\n",
                   voituresDisponibles[i].id, voituresDisponibles[i].marque,
                   voituresDisponibles[i].modele, voituresDisponibles[i].etat);
            return;
        }
    }
    printf("La voiture avec l'ID %d n'a pas été trouvée.\n", idVoiture);
}

void supprimerVoiturePanne(int idVoiture) {
    for (int i = 0; i < nbVoitures; i++) {
        if (voituresDisponibles[i].id == idVoiture) {
            // Suppression de la voiture en panne
            for (int j = i; j < nbVoitures - 1; j++) {
                voituresDisponibles[j] = voituresDisponibles[j + 1];
            }
            nbVoitures--;
            printf("La voiture avec l'ID %d a été supprimée.\n", idVoiture);
            return;
        }
    }
    printf("La voiture avec l'ID %d n'a pas été trouvée.\n", idVoiture);
}

void modifierDescription(int idVoiture, char nouvelleMarque[50], char nouvelEtat[20]) {
    for (int i = 0; i < nbVoitures; i++) {
        if (voituresDisponibles[i].id == idVoiture) {
            strcpy(voituresDisponibles[i].marque, nouvelleMarque);
            strcpy(voituresDisponibles[i].etat, nouvelEtat);
            printf("La description de la voiture avec l'ID %d a été modifiée.\n", idVoiture);
            return;
        }
    }
    printf("La voiture avec l'ID %d n'a pas été trouvée.\n", idVoiture);
}

void afficherHistoriqueLocations() {
    printf("Historique des locations :\n");
    for (int i = 0; i < nbLocations; i++) {
        printf("Location %d - ID Voiture : %d, Date : %s, Etat : %s\n",
               i + 1, historiqueLocations[i].idVoiture,
               historiqueLocations[i].date, historiqueLocations[i].etatVoiture);
    }
}

void retourVoitureReclamation(int idVoiture, char date[20], char nouvelEtat[50]) {
    for (int i = 0; i < nbLocations; i++) {
        if (historiqueLocations[i].idVoiture == idVoiture) {
            strcpy(historiqueLocations[i].etatVoiture, nouvelEtat);
            strcpy(historiqueLocations[i].date, date); // Mise à jour de la date de retour
            printf("La voiture avec l'ID %d a été retournée avec succès.\n", idVoiture);
            return;
        }
    }
    printf("La voiture avec l'ID %d n'a pas été trouvée dans l'historique des locations.\n", idVoiture);
}

int main() {
    // Simulation d'ajout de voitures
    Voiture voiture1 = {1, "Toyota", "Corolla", "Disponible"};
    Voiture voiture2 = {2, "Honda", "Civic", "En réparation"};

    voituresDisponibles[0] = voiture1;
    voituresDisponibles[1] = voiture2;

    nbVoitures = 2;

    // Test des fonctionnalités
    louerVoiture(1, "28/12/2023", "En location");
    afficherDescription(1);
    supprimerVoiturePanne(2);
    modifierDescription(1, "Tesla", "Disponible");
    afficherHistoriqueLocations();
    retourVoitureReclamation(1, "01/01/2024", "En réparation");

    return 0;
}
