#include "athlete.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

char athletes[MAX_ATHLETES][MAX_NAME_LEN]; // Tableau pour stocker les noms des athlètes
int athleteCount = 0; // Compteur pour le nombre d'athlètes

// Fonction pour ajouter un athlète
void addAthlete(char *name)
{
  if (athleteCount < MAX_ATHLETES) // Vérifier si le nombre maximum d'athlètes n'est pas atteint
  {
    strcpy(athletes[athleteCount], name); // Copier le nom de l'athlète dans le tableau
    athleteCount++; // Incrémenter le compteur d'athlètes
    printf("Nouvel athlète enregistré !\n");
  }
  else
  {
    printf("Nombre maximum d'athlètes atteint.\n"); // Message d'erreur si le nombre maximum est atteint
  }
}

// Fonction pour vérifier si un athlète existe
bool athleteExists(char *name)
{
  for (int i = 0; i < athleteCount; i++) // Parcourir le tableau des athlètes
  {
    if (strcmp(athletes[i], name) == 0) // Comparer les noms des athlètes
    {
      return true; // Retourner vrai si l'athlète existe
    }
  }
  return false; // Retourner faux si l'athlète n'existe pas
}

// Fonction pour créer une performance
Performance createPerformance(char *event, char *date, float time, int relayPosition)
{
  Performance p;
  strcpy(p.event, event); // Copier le nom de l'événement
  strcpy(p.date, date); // Copier la date
  p.time = time; // Enregistrer le temps de performance
  p.relayPosition = relayPosition; // Enregistrer la position de relais
  return p; // Retourner la performance créée
}

// Fonction pour mettre à jour la performance d'un athlète
void updatePerformance(char *name, Performance p)
{
  char filename[MAX_NAME_LEN + 4];
  snprintf(filename, sizeof(filename), "%s.txt", name); // Créer le nom de fichier pour l'athlète

  // Vérifie s'il n'y a pas 2 valeurs de relais différentes le même jour
  FILE *file = fopen(filename, "r");
  Performance temp;
  while (file && fscanf(file, "%s %s %f %d", temp.date, temp.event, &temp.time, &temp.relayPosition) != EOF)
  {
    if(strcmp(temp.date, p.date) == 0)
    {
      printf("Un seul entraînement de relais est autorisé par jour.\n");
      fclose(file);
      return;
    }
  }

  if (file)
    fclose(file);

  // Ajouter une nouvelle performance
  file = fopen(filename, "a");
  if (file)
  {
    fprintf(file, "%s %s %.2f %d\n", p.date, p.event, p.time, p.relayPosition); // Enregistrer la performance dans le fichier
    fclose(file);
    printf("Nouvelle performance enregistrée !\n");
  }
}

// Fonction pour afficher les statistiques d'un athlète
void displayStatistics(char *name)
{
  char filename[MAX_NAME_LEN + 4];
  snprintf(filename, sizeof(filename), "%s.txt", name); // Créer le nom de fichier pour l'athlète
  FILE *file = fopen(filename, "r");
  if (file == NULL)
  {
    printf("Aucune donnée de performance trouvée pour l'athlète %s.\n", name); // Message d'erreur si le fichier n'existe pas
    return;
  }

  Performance p;
  while (fscanf(file, "%s %s %f %d", p.date, p.event, &p.time, &p.relayPosition) != EOF) // Lire les performances du fichier
  {
    printf("Date: %s, Événement: %s, Temps: %.2f, Position de relais: %d\n", p.date, p.event, p.time, p.relayPosition); // Afficher les performances
  }
  fclose(file); // Fermer le fichier
}

// Fonction pour lister tous les athlètes
void listAthletes()
{
  printf("Liste des athlètes :\n");
  for (int i = 0; i < athleteCount; i++) // Parcourir le tableau des athlètes
  {
    printf("%s\n", athletes[i]); // Afficher le nom de chaque athlète
  }
}

// Fonction pour sélectionner les trois meilleurs athlètes pour un événement
void selectTopThree(char *event)
{
  typedef struct
  {
    char name[MAX_NAME_LEN];
    float averageTime;
  } AthleteAverage;

  AthleteAverage averages[MAX_ATHLETES]; // Tableau pour stocker les temps moyens des athlètes
  int count = 0;

  for (int i = 0; i < athleteCount; i++) // Parcourir le tableau des athlètes
  {
    char filename[MAX_NAME_LEN + 4];
    snprintf(filename, sizeof(filename), "%s.txt", athletes[i]); // Créer le nom de fichier pour l'athlète
    FILE *file = fopen(filename, "r");
    if (file == NULL)
      continue;

    Performance p;
    float totalTime = 0;
    int eventCount = 0;

    while (fscanf(file, "%s %s %f %d", p.date, p.event, &p.time, &p.relayPosition) != EOF) // Lire les performances du fichier
    {
      if (strcmp(p.event, event) == 0) // Vérifier si l'événement correspond
      {
        totalTime += p.time; // Ajouter le temps de performance au total
        eventCount++; // Incrémenter le compteur d'événements
      }
    }
    fclose(file);

    if (eventCount > 0)
    {
      averages[count].averageTime = totalTime / eventCount; // Calculer le temps moyen
      strcpy(averages[count].name, athletes[i]); // Copier le nom de l'athlète
      count++;
    }
  }

  // Trier par temps moyen
  for (int i = 0; i < count - 1; i++)
  {
    for (int j = i + 1; j < count; j++)
    {
      if (averages[i].averageTime > averages[j].averageTime)
      {
        AthleteAverage temp = averages[i];
        averages[i] = averages[j];
        averages[j] = temp;
      }
    }
  }

  printf("Top trois athlètes pour l'événement %s:\n", event);
  for (int i = 0; i < 3 && i < count; i++) // Afficher les trois meilleurs athlètes
  {
    printf("%s avec un temps moyen de %.2f\n", averages[i].name, averages[i].averageTime);
  }
}

// Fonction pour afficher la différence de temps pour un athlète entre deux dates
void displayTimeDifference(char *name, char *event, char *date1, char *date2)
{
  char filename[MAX_NAME_LEN + 4];
  snprintf(filename, sizeof(filename), "%s.txt", name); // Créer le nom de fichier pour l'athlète
  FILE *file = fopen(filename, "r");
  if (file == NULL)
  {
    printf("Aucune donnée de performance trouvée pour l'athlète %s.\n", name); // Message d'erreur si le fichier n'existe pas
    return;
  }

  Performance p;
  float time1 = -1, time2 = -1;

  while (fscanf(file, "%s %s %f %d", p.date, p.event, &p.time, &p.relayPosition) != EOF) // Lire les performances du fichier
  {
    if (strcmp(p.event, event) == 0) // Vérifier si l'événement correspond
    {
      if (strcmp(p.date, date1) == 0) // Vérifier si la date correspond à la première date
      {
        time1 = p.time; // Enregistrer le temps de performance
      }
      else if (strcmp(p.date, date2) == 0) // Vérifier si la date correspond à la deuxième date
      {
        time2 = p.time; // Enregistrer le temps de performance
      }
    }
  }
  fclose(file);

  if (time1 < 0 || time2 < 0) // Vérifier si les deux temps ont été trouvés
  {
    printf("Données de performance insuffisantes pour comparer les dates.\n");
  }
  else
  {
    float diff = time2 - time1; // Calculer la différence de temps
    printf("La différence de temps pour le %s entre le %s et le %s est de %.2f secondes\n", event, date1, date2, diff);
  }
}

// Fonction pour afficher le résumé des performances d'un athlète dans un événement
void displayPerformanceSummary(char *name, char *event)
{
  char filename[MAX_NAME_LEN + 4];
  snprintf(filename, sizeof(filename), "%s.txt", name); // Créer le nom de fichier pour l'athlète
  FILE *file = fopen(filename, "r");
    if (file == NULL)
  {
    printf("Aucune donnée de performance trouvée pour l'athlète %s.\n", name); // Message d'erreur si le fichier n'existe pas
    return;
  }

  Performance p;
  float bestTime = FLT_MAX, worstTime = FLT_MIN, totalTime = 0;
  int count = 0;
  while (fscanf(file, "%s %s %f %d", p.date, p.event, &p.time, &p.relayPosition) != EOF) // Lire les performances du fichier
  {
    if (strcmp(p.event, event) == 0) // Vérifier si l'événement correspond
    {
      if (p.time < bestTime)
        bestTime = p.time; // Mettre à jour le meilleur temps
      if (p.time > worstTime)
        worstTime = p.time; // Mettre à jour le pire temps
      totalTime += p.time; // Ajouter le temps de performance au total
      count++; // Incrémenter le compteur de performances
    }
  }
  fclose(file);

  if (count > 0)
  {
    float averageTime = totalTime / count; // Calculer le temps moyen
    printf("Résumé des performances pour %s dans l'événement %s:\n", name, event);
    printf("Meilleur temps: %.2f, Pire temps: %.2f, Temps moyen: %.2f\n", bestTime, worstTime, averageTime); // Afficher le résumé des performances
  }
  else
  {
    printf("Aucune donnée de performance pour %s dans l'événement %s.\n", name, event);
  }
}

// Fonction pour afficher les statistiques d'un événement
void displayEventStatistics(char *event)
{
  typedef struct
  {
    char name[MAX_NAME_LEN];
    float time;
    char date[MAX_DATE_LEN];
  } EventStats;

  EventStats stats[MAX_ATHLETES * 100];
  int count = 0;

  for (int i = 0; i < athleteCount; i++) // Parcourir le tableau des athlètes
  {
    char filename[MAX_NAME_LEN + 4];
    snprintf(filename, sizeof(filename), "%s.txt", athletes[i]); // Créer le nom de fichier pour l'athlète
    FILE *file = fopen(filename, "r");
    if (file == NULL)
      continue;

    Performance p;
    while (fscanf(file, "%s %s %f %d", p.date, p.event, &p.time, &p.relayPosition) != EOF) // Lire les performances du fichier
    {
      if (strcmp(p.event, event) == 0) // Vérifier si l'événement correspond
      {
        strcpy(stats[count].name, athletes[i]); // Copier le nom de l'athlète
        stats[count].time = p.time; // Copier le temps de performance
        strcpy(stats[count].date, p.date); // Copier la date
        count++;
      }
    }
    fclose(file);
  }

  printf("Statistiques pour l'événement %s:\n", event);
  for (int i = 0; i < count; i++) // Afficher les statistiques pour chaque performance
  {
    printf("Athlète: %s, Temps: %.2f, Date: %s\n", stats[i].name, stats[i].time, stats[i].date);
  }
}

// Fonction pour afficher les statistiques pour une date donnée
void displayDateStatistics(char *date)
{
  typedef struct
  {
    char name[MAX_NAME_LEN];
    float time;
    char event[MAX_EVENT_LEN];
  } DateStats;

  DateStats stats[MAX_ATHLETES * 100];
  int count = 0;

  for (int i = 0; i < athleteCount; i++) // Parcourir le tableau des athlètes
  {
    char filename[MAX_NAME_LEN + 4];
    snprintf(filename, sizeof(filename), "%s.txt", athletes[i]); // Créer le nom de fichier pour l'athlète
    FILE *file = fopen(filename, "r");
    if (file == NULL)
      continue;

    Performance p;
    while (fscanf(file, "%s %s %f %d", p.date, p.event, &p.time, &p.relayPosition) != EOF) // Lire les performances du fichier
    {
      if (strcmp(p.date, date) == 0) // Vérifier si la date correspond
      {
        strcpy(stats[count].name, athletes[i]); // Copier le nom de l'athlète
        stats[count].time = p.time; // Copier le temps de performance
        strcpy(stats[count].event, p.event); // Copier l'événement
        count++;
      }
    }
    fclose(file);
  }

  printf("Statistiques pour la date %s:\n", date);
  for (int i = 0; i < count; i++) // Afficher les statistiques pour chaque performance
  {
    printf("Athlète: %s, Temps: %.2f, Événement: %s\n", stats[i].name, stats[i].time, stats[i].event);
  }
}

// Fonction pour vérifier si une date est valide
bool isValidDate(const char *date)
{
  int year, month, day;
  if (sscanf(date, "%d-%d-%d", &year, &month, &day) != 3)
    return false;
  if (year < 1900 || year > 2024)
    return false;
  if (month < 1 || month > 12)
    return false;
  if (day < 1 || day > 31)
    return false;
  // Vérifier pour les mois de 30 jours
  if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
    return false;
  // Vérifier pour les années bissextiles
  if (month == 2)
  {
    bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (day > 29 || (day == 29 && !isLeap))
      return false;
  }
  return true;
}

// Fonction pour vérifier si la position de relais est valide
bool isValidRelayPosition(int position)
{
  return position >= 1 && position <= 4;
}

// Fonction pour vérifier si le temps de performance est valide
bool isValidPerformanceTime(float time)
{
  return time >= 0;
}

// Fonction pour trier les athlètes par date
void sortAthletesByDate()
{
  typedef struct
  {
    char name[MAX_NAME_LEN];
    char date[MAX_DATE_LEN];
  } AthleteDate;

  AthleteDate athleteDates[MAX_ATHLETES];
  int count = 0;

  for (int i = 0; i < athleteCount; i++) // Parcourir le tableau des athlètes
  {
    char filename[MAX_NAME_LEN + 4];
    snprintf(filename, sizeof(filename), "%s.txt", athletes[i]); // Créer le nom de fichier pour l'athlète
    FILE *file = fopen(filename, "r");
    if (file == NULL)
      continue;

    Performance p;
    while (fscanf(file, "%s %s %f %d", p.date, p.event, &p.time, &p.relayPosition) != EOF) // Lire les performances du fichier
    {
      strcpy(athleteDates[count].name, athletes[i]); // Copier le nom de l'athlète
      strcpy(athleteDates[count].date, p.date); // Copier la date
      count++;
    }
    fclose(file);
  }

  // Trier par date
  for (int i = 0; i < count - 1; i++)
  {
    for (int j = 0; j < count - 1 - i; j++)
    {
      if (strcmp(athleteDates[j].date, athleteDates[j + 1].date) > 0)
      {
        AthleteDate temp = athleteDates[j];
        athleteDates[j] = athleteDates[j + 1];
        athleteDates[j + 1] = temp;
      }
    }
  }

  printf("Athlètes triés par date:\n");
  for (int i = 0; i < count; i++) // Afficher les athlètes triés par date
  {
    printf("Athlète: %s, Date: %s\n", athleteDates[i].name, athleteDates[i].date);
  }
}

// Fonction pour trier les athlètes par ordre alphabétique
void sortAthletesByName()
{
  // Trier par ordre alphabétique
  for (int i = 0; i < athleteCount - 1; i++)
  {
    for (int j = 0; j < athleteCount - 1 - i; j++)
    {
      if (strcmp(athletes[j], athletes[j + 1]) > 0)
      {
        char temp[MAX_NAME_LEN];
        strcpy(temp, athletes[j]);
        strcpy(athletes[j], athletes[j + 1]);
        strcpy(athletes[j + 1], temp);
      }
    }
  }

  printf("Athlètes triés par ordre alphabétique:\n");
  for (int i = 0; i < athleteCount; i++) // Afficher les athlètes triés par ordre alphabétique
  {
    printf("%s\n", athletes[i]);
  }
}

// Fonction pour vider le buffer d'entrée
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
