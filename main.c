#include "athlete.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  while (1) // Boucle infinie pour afficher le menu et traiter les choix de l'utilisateur
  {
    printf("1. Ajouter un athlète\n");
    printf("2. Ajouter une performance en entraînement\n");
    printf("3. Afficher les statistiques (Par date, ordre alphabétique ou évenement)\n");
    printf("4. Lister les athlètes\n");
    printf("5. Sélectionner les trois meilleurs athlètes pour les JO\n");
    printf("6. Afficher la différence de temps pour un athlète entre deux dates\n");
    printf("7. Détails des performances d'un athlète dans un évenement\n");
    printf("8. Quitter\n");
    printf("Choisissez une option : ");

    int choice;
    scanf("%d", &choice); // Lire le choix de l'utilisateur
    getchar(); // Consomme le caractère de nouvelle ligne

    char name[MAX_NAME_LEN];
    char event[MAX_EVENT_LEN];
    char date[MAX_DATE_LEN];
    char date1[MAX_DATE_LEN];

    switch (choice) // Traiter le choix de l'utilisateur
    {
    case 1: // Ajouter un athlète
      printf("Entrez le nom de l'athlète : ");
      fgets(name, sizeof(name), stdin); // Lire le nom de l'athlète
      name[strcspn(name, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne
      addAthlete(name); // Appeler la fonction pour ajouter un athlète
      break;
    case 2: // Ajouter une performance
      printf("Entrez le nom de l'athlète : ");
      fgets(name, sizeof(name), stdin); // Lire le nom de l'athlète
      name[strcspn(name, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne
      if (!athleteExists(name)) // Vérifier si l'athlète existe
      {
        printf("Athlète introuvable.\n");
        break;
      }
      printf("1: 100m - 2: 400m - 3: 5000m - 4: Marathon - 5: 4*100m relais - 6: Créer un événement\n");
      printf("Choisissez un événement: ");
      int eventChoice;
      scanf("%d", &eventChoice); // Lire le choix de l'événement
      getchar();
      if (eventChoice == 6) // Créer un nouvel événement
      {
        printf("Entrez le nom de l'événement : ");
        fgets(event, sizeof(event), stdin); // Lire le nom de l'événement
        event[strcspn(event, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne
      }
      else
      {
        const char *events[] = {"100m", "400m", "5000m", "Marathon", "4x100m relais"};
        if (eventChoice < 1 || eventChoice > 5) // Vérifier si le choix de l'événement est valide
        {
          printf("Choix d'événement invalide.\n");
          break;
        }
        strcpy(event, events[eventChoice - 1]); // Copier le nom de l'événement choisi
      }
      printf("Entrez la date (YYYY-MM-DD) : ");
      fgets(date, sizeof(date), stdin); // Lire la date
      date[strcspn(date, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne
      if (!isValidDate(date)) // Vérifier si la date est valide
      {
        printf("Date invalide.\n");
        break;
      }
      printf("Entrez le temps de performance (secondes) : ");
      float time;
      scanf("%f", &time); // Lire le temps de performance
      if (!isValidPerformanceTime(time)) // Vérifier si le temps de performance est valide
      {
        printf("Temps de performance invalide.\n");
        break;
      }
      int relayPosition = 0;
      if (strcmp(event, "4x100m relais") == 0) // Si l'événement est un relais, demander la position de relais
      {
        printf("Entrez la position de relais (1-4) : ");
        scanf("%d", &relayPosition); // Lire la position de relais
        if (!isValidRelayPosition(relayPosition)) // Vérifier si la position de relais est valide
        {
          printf("Position de relais invalide.\n");
          break;
        }
      }
      Performance p = createPerformance(event, date, time, relayPosition); // Créer une nouvelle performance
      updatePerformance(name, p); // Mettre à jour la performance de l'athlète
      break;
    case 3: // Afficher les statistiques
      printf("1: Par date - 2: Par ordre alphabétique - 3: Par événement\n");
      printf("Choisissez une option : ");
      int displayChoice;
      scanf("%d", &displayChoice); // Lire le choix de l'affichage
      getchar();
      if (displayChoice == 1)
      {
        sortAthletesByDate(); // Trier les athlètes par date
      }
      else if (displayChoice == 2)
      {
        sortAthletesByName(); // Trier les athlètes par ordre alphabétique
      }
      else if (displayChoice == 3)
      {
        printf("Entrez le nom de l'événement : ");
        fgets(event, sizeof(event), stdin); // Lire le nom de l'événement
        event[strcspn(event, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne
        displayEventStatistics(event); // Afficher les statistiques de l'événement
      }
      else
      {
        printf("Choix invalide.\n");
      }
      break;
    case 4: // Lister les athlètes
      listAthletes(); // Appeler la fonction pour lister les athlètes
      break;
    case 5: // Sélectionner les trois meilleurs athlètes pour un événement
      printf("Entrez le nom de l'événement : ");
      fgets(event, sizeof(event), stdin); // Lire le nom de l'événement
      event[strcspn(event, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne
      selectTopThree(event); // Sélectionner les trois meilleurs athlètes
      break;
    case 6: // Afficher la différence de temps pour un athlète entre deux dates
      printf("Entrez le nom de l'athlète : ");
      fgets(name, sizeof(name), stdin); // Lire le nom de l'athlète
      name[strcspn(name, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne
      if (!athleteExists(name)) // Vérifier si l'athlète existe
      {
        printf("Athlète introuvable.\n");
        break;
      }
      printf("Entrez le nom de l'événement : ");
      fgets(event, sizeof(event), stdin); // Lire le nom de l'événement
      event[strcspn(event, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne
      printf("Entrez la première date (YYYY-MM-DD) : ");
      fgets(date, sizeof(date), stdin); // Lire la première date
      date[strcspn(date, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne
      strcpy(date1, date); // Copier la première date
      if (!isValidDate(date)) // Vérifier si la date est valide
      {
        printf("Date invalide.\n");
        break;
      }
      clearInputBuffer(); // Vider le buffer d'entrée
      printf("Entrez la deuxième date (YYYY-MM-DD) : ");
      fgets(date1, sizeof(date1), stdin); // Lire la deuxième date
      date1[strcspn(date1, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne
      if (!isValidDate(date1)) // Vérifier si la deuxième date est valide
      {
        printf("Date invalide.\n");
        break;
      }
      displayTimeDifference(name, event, date1, date); // Afficher la différence de temps
      break;
    case 7: // Détails des performances d'un athlète dans un événement
      printf("Entrez le nom de l'athlète : ");
      fgets(name, sizeof(name), stdin); // Lire le nom de l'athlète
      name[strcspn(name, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne
      if (!athleteExists(name)) // Vérifier si l'athlète existe
      {
        printf("Athlète introuvable.\n");
        break;
      }
      printf("Entrez le nom de l'événement : ");
      fgets(event, sizeof(event), stdin); // Lire le nom de l'événement
      event[strcspn(event, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne
      displayPerformanceSummary(name, event); // Afficher le résumé des performances
      break;
    case 8: // Quitter
      printf("Merci d'avoir utilisé notre application. A bientôt !\n");
      exit(0); // Quitter le programme
    default:
      printf("Choix invalide.\n"); // Gérer un choix invalide
    }
  }

  return 0; // Retourner 0 pour indiquer que le programme s'est terminé correctement
}
