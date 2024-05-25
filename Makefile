# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Cible exécutable et fichiers objet
TARGET = main
OBJS = main.o athlete.o

# Cible par défaut pour construire le programme
all: $(TARGET)

# Lier les fichiers objet pour créer l'exécutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compiler main.c
