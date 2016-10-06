# Noms des dossiers
OBJDIR = obj
BINDIR = bin
SRCDIR = src
INCDIR = include

# Nom du programme
PROG = test_list

# Liste des sources
SOURCES = $(wildcard $(SRCDIR)/*.c)
# Liste des modules
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Variables du compilateur
CC = gcc
CFLAGS = -Wall -g
CINCLUDE = -I./$(INCDIR)

#
# Edition de lien
#
$(BINDIR)/$(PROG): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

#
# Modules objets du TP Listes
#
$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(CINCLUDE) -o $@ -c $<

#
# Génération du listing en pdf
#
listing:
	a2ps -o listing.ps $(INCDIR)/*.h $(SOURCES)
	ps2pdf listing.ps
	rm listing.ps

#
# Nettoyage des modules
#
clean :
	rm $(BINDIR)/* $(OBJDIR)/*
