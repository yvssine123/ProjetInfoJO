Description du projet :

Ce projet est un programme en C permettant de gérer les performances des athlètes. Il permet d'ajouter des athlètes, de mettre à jour leurs performances, d'afficher leurs statistiques et de sélectionner les meilleurs athlètes pour différents événements, notamment les Jeux Olympiques.

Compiler le programme : 

Ecrire « make » dans le terminal.

Lancer le programme :

Ecrire « ./main » dans le terminal.

Instructions d'utilisation

Le programme utilise des entrées utilisateur pour interagir avec les différentes fonctionnalités.

Assurez-vous que les entrées respectent les formats attendus, notamment pour les dates (YYYY-MM-DD).

Structuration des fichiers :

main.c : Le fichier principal contenant la boucle principale du programme et les options du menu.
athlete.c : Contient les définitions des fonctions pour gérer les athlètes et leurs performances.
athlete.h : Contient les déclarations des fonctions et les définitions des structures utilisées dans le programme.

Fonctionnalités du programme :

1.Ajouter un athlète
Demande le nom de l'athlète et l'ajoute à la liste.

2.Mettre à jour la performance
Demande le nom de l'athlète et l'événement, puis met à jour la performance de l'athlète pour cet événement, en créant un fichier texte qui porte le nom de l’athlète. Chaque performance vient s’ajouter dans le fichier texte sur une unique ligne.

3.Afficher les statistiques
Affiche les statistiques des athlètes triées par date, par ordre alphabétique ou par événement.

4.Lister les athlètes
Affiche la liste de tous les athlètes enregistrés.

5.Sélectionner les trois meilleurs athlètes pour un événement
Affiche les trois meilleurs athlètes (meilleure moyenne de temps) pour un événement donné.

6.Afficher la différence de temps pour un athlète entre deux dates
Affiche la différence de temps pour un athlète entre deux performances à des dates différentes.

7.Détails des performances d'un athlète dans un événement
Affiche les détails des performances (pire temps, meilleur temps et moyenne de temps d'un athlète pour un événement donné.

8.Quitter
Quitte le programme.

Contenu des fichiers

Dans le athlete.h :

La structure “performance” :
Évènement, date, temps et position de relais si nécessaire.

Constantes :
#define MAX_ATHLETES 100
#define MAX_NAME_LEN 100
#define MAX_EVENT_LEN 50
#define MAX_DATE_LEN 11

Dans le main.c :

main() : Boucle principale du programme avec le menu interactif.

Dans le athlete.c :

addAthlete(char *name) : Ajoute un nouvel athlète.

updatePerformance(char *name, Performance p) : Met à jour la performance d'un athlète.

displayStatistics(char *name) : Affiche les statistiques d'un athlète.

listAthletes() : Liste tous les athlètes.

selectTopThree(char *event) : Sélectionne les trois meilleurs athlètes pour un événement.

displayTimeDifference(char *name, char *event, char *date1, char *date2) : Affiche la différence de temps pour un athlète entre deux dates.

displayPerformanceSummary(char *name, char *event) : Affiche le résumé des performances d'un athlète pour un événement.

isValidDate(const char *date) : Vérifie si une date est valide.

isValidRelayPosition(int position) : Vérifie si une position de relais est valide.

isValidPerformanceTime(float time) : Vérifie si un temps de performance est valide.

athleteExists(char *name) : Vérifie si un athlète existe.

createPerformance(char *event, char *date, float time, int relayPosition) : Crée une performance.

displayEventStatistics(char *event) : Affiche les statistiques d'un événement.

displayDateStatistics(char *date) : Affiche les statistiques d'une date.

sortAthletesByDate() : Trie les athlètes par date.

sortAthletesByName() : Trie les athlètes par ordre alphabétique.

clearInputBuffer() : Vide le tampon d'entrée.

