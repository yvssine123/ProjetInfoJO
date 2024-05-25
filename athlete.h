#ifndef ATHLETE_H
#define ATHLETE_H

#include <stdbool.h>

#define MAX_ATHLETES 100
#define MAX_NAME_LEN 100
#define MAX_EVENT_LEN 50
#define MAX_DATE_LEN 11

typedef struct
{
  char event[MAX_EVENT_LEN];
  char date[MAX_DATE_LEN];
  float time;
  int relayPosition;
} Performance;

extern char athletes[MAX_ATHLETES][MAX_NAME_LEN];
extern int athleteCount;

void addAthlete(char *name);
void updatePerformance(char *name, Performance p);
void displayStatistics(char *name);
void listAthletes();
void selectTopThree(char *event);
void displayTimeDifference(char *name, char *event, char *date1, char *date2);
void displayPerformanceSummary(char *name, char *event);
void calculateLinearRegression(char *name, char *event);
bool isValidDate(const char *date);
bool isValidRelayPosition(int position);
bool isValidPerformanceTime(float time);
bool athleteExists(char *name);
Performance createPerformance(char *event, char *date, float time, int relayPosition);
void displayEventStatistics(char *event);
void displayDateStatistics(char *date);
void sortAthletesByDate();
void sortAthletesByName();
void clearInputBuffer();

#endif // ATHLETE_H
