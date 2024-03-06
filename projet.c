#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

#define LONGUEUR_USERNAME 20
#define LONGUEUR_PWD 20

// Structure pour stocker les informations de connexion
typedef struct {
    char login[LONGUEUR_USERNAME];
    char motDePasse[LONGUEUR_PWD];
    time_t derniereconnexion;
} Identifiants;

// Fonction pour vérifier les identifiants de connexion
bool verifierIdentifiants(Identifiants *identifiants, int nombreIdentifiants, char *login, char *password) {
    for (int i = 0; i < nombreIdentifiants; i++) {
        if (strcmp(identifiants[i].login, login) == 0 && strcmp(identifiants[i].motDePasse, password) == 0) {
            return true; // Identifiants valides
        }
    }
    return false; // Identifiants invalides
}

int menuAdmin() {
    int choix;
    do {
        printf("------------ menu de l'administrateur-------------:\n");
        printf("1 ---------- GESTION DES ÉTUDIANTS\n");
        printf("2 ---------- GÉNÉRATION DE FICHIERS\n");
        printf("3 ---------- MARQUER LES PRÉSENCES\n");
        printf("4 ---------- ENVOYER UN MESSAGE\n");
        printf("5 ---------- Quitter\n");
        printf("---------- Entrez votre choix :\n ");
        scanf("%d", &choix);
        if (choix < 1 || choix > 5) {
            printf("Choix invalide. Veuillez entrer un choix entre 1 et 5.\n");
        }
    } while (choix < 1 || choix > 5);
    return choix;
}

int menuEtudiant() {
    int choix;
    do {
        printf("----------- menu de l'apprenant ------------:\n");
        printf("1 ---------- GESTION DES ÉTUDIANTS\n");
        printf("2 ---------- GÉNÉRATION DE FICHIERS\n");
        printf("3 ---------- MARQUER SA PRÉSENCE\n");
        printf("4 ---------- Message (0)\n");
        printf("5 ---------- Déconnexion\n");
        printf("\n---------- Entrez votre choix : ");
        scanf("%d", &choix);
        if (choix < 1 || choix > 5) {
            printf("Choix invalide. Veuillez entrer un choix entre 1 et 5.\n");
        }
    } while (choix < 1 || choix > 5);
    return choix;
}

int main() {
    // Création des fichiers pour stocker les identifiants
    FILE *fichierAdmin = fopen("admin.txt", "r");
    if (fichierAdmin == NULL) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return 1;
    }

    // Lecture des identifiants de l'admin
    Identifiants identifiantsAdmin;
    fscanf(fichierAdmin, "%s %s", identifiantsAdmin.login, identifiantsAdmin.motDePasse);
    fclose(fichierAdmin);

    // Variables pour l'authentification
    char saisieLogin[LONGUEUR_USERNAME];
    char *saisieMotDePasse;

    // Authentification
    do {
        printf("---------------- Connexion ----------------\n\n");
        printf("Login : ");

        // Saisie du login
        scanf("%s", saisieLogin);

        // Saisie du mot de passe
        saisieMotDePasse = getpass("Mot de passe: ");

        // Vérification des identifiants
        if (verifierIdentifiants(&identifiantsAdmin, 1, saisieLogin, saisieMotDePasse)) {
            // Menu pour l'admin
            menuAdmin();
        } else {
            printf("Login ou mot de passe invalides.\n");
        }

    } while (!verifierIdentifiants(&identifiantsAdmin, 1, saisieLogin, saisieMotDePasse));

    return 0;
}
