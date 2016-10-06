//------------------------------------------------------------------------
// test liste avec google test
//------------------------------------------------------------------------
#include <gtest/gtest.h>

#include <algorithm>
#include <deque>
#include <iterator>
#include <sstream>
#include <cstdlib>
#include <ctime>

extern "C" {
#include "list.h"
}
extern int nb_malloc;

//------------------------------------------------------------------------
// fonctions utilitaires ...
//------------------------------------------------------------------------
// Compter le nombre d'éléments de la liste paramètre
static int
list_size(list_elem_t * p_list)
{
  int nb = 0;
  while (p_list != NULL) {
    nb += 1;
    p_list = p_list->next;
  }
  return nb;
}

// ajouter des élts en tête d'un tableau et d'une liste
void
ajouter_tete(int v_deb, int v_fin,
	     std::deque<int> & tableau,
	     list_elem_t * * pliste)
{
  for (int i = v_deb; i <= v_fin; ++i) {
    tableau.push_front(i);
    insert_head(pliste, i);
  }
}

// ajouter des élts en fin d'un tableau et d'une liste
void
ajouter_fin(int v_deb, int v_fin,
	    std::deque<int> & tableau,
	    list_elem_t * * pliste)
{
  for (int i = v_deb; i <= v_fin; ++i) {
    tableau.push_back(i);
    insert_tail(pliste, i);
  }
}

// ajouter des élts aléatoirement
void
ajout_aleatoire(std::deque<int> & tableau,
		list_elem_t * * pliste)
{
  const int array_size = 100 + rand() % 100;
  for (int i = 0; i < array_size; ++i) {
    int nombre = rand();
    if (rand() % 2 == 0) {
      // ajout en tête
      tableau.push_front(nombre);
      insert_head(pliste, nombre);
    }
    else {
      // ajout en fin
      tableau.push_back(nombre);
      insert_tail(pliste, nombre);
    }
  }
}

// comparer les élts d'une liste et ceux d'un deque
void
list_equals_deque(list_elem_t * list,
		  std::deque<int> tableau)
{
  // std::cout << "\ntaille deque : " << tableau.size() << " taille liste : " << list_size(list) << "";
  EXPECT_EQ(
	    (int) tableau.size(),
	    list_size(list)
	    )
    << "Erreur taille liste";
  // vérifier les allocations
  EXPECT_EQ(
	    list_size(list),
	    nb_malloc)
    << "Erreur nombre d'allocation est " << nb_malloc
    << " au lieu de " << list_size(list);
  // vérifier la valeur des éléments
  int i = 0;
  while (list != NULL) {
    EXPECT_EQ(
	      tableau[i],
	      list->value
	      )
      << "Erreur élément d'indice " << i;
    list = list->next;
    i += 1;
  }
}

//------------------------------------------------------------------------
// test des fonctions d'ajout
//------------------------------------------------------------------------

//-----------------------------
// ajout d'un élt en tête
//-----------------------------
// NB : insert_head est donné et devrait donc être correct :)
TEST(TestList, ajoutEltTete)
{
  nb_malloc = 0; // hé oui :(
  std::deque<int> tableau;
  list_elem_t * la_liste = NULL;
  // ajouter 1 élt en tête d'un tableau et d'une liste
  ajouter_tete(1, 1, tableau, & la_liste);
  // vérifier le résultat
  list_equals_deque(la_liste, tableau);
}

//-----------------------------
// ajouter n élts en tête
//-----------------------------
TEST(TestList, ajoutNEltsTete)
{
  nb_malloc = 0; // hé oui :(
  std::deque<int> tableau;
  list_elem_t * la_liste = NULL;
  // ajouter des élts en tête d'un tableau et d'une liste
  ajouter_tete(1, 50, tableau, & la_liste);
  // vérifier le résultat
  list_equals_deque(la_liste, tableau);
}

// ajout d'un élt en fin
TEST(TestList, ajoutEltFin)
{
  nb_malloc = 0;
  std::deque<int> tableau;
  list_elem_t * la_liste = NULL;
  // ajouter 1 elt en fin d'un tableau et d'une liste
  ajouter_fin (1, 1, tableau, & la_liste);
  // verifier le resultat
  list_equals_deque (la_liste, tableau);
}

// ajouter n élts en fin
TEST(TestList, ajoutNEltsFin)
{
  nb_malloc = 0;
  std::deque<int> tableau;
  list_elem_t *la_liste = NULL;
  // ajouter des elements en fin d'un tableau et d'une liste
  ajouter_fin (1, 50, tableau, & la_liste);
  // verifier le resultat
  list_equals_deque (la_liste, tableau);
}

// ajouter n élts en tête puis n élts en fin
TEST(TestList, ajoutTetePuisFin)
{
  nb_malloc = 0;
  std::deque<int> tableau;
  list_elem_t * la_liste = NULL;
  // ajout
  ajouter_tete (1, 20, tableau, & la_liste);
  ajouter_fin (21, 50, tableau, & la_liste);
  // verification
  list_equals_deque (la_liste, tableau);
}

// ajouter n élts en fin puis n élts en tête
TEST(TestList, ajoutFinPuisTete)
{
  nb_malloc = 0;
  std::deque<int> tableau;
  list_elem_t * la_liste = NULL;
  // ajout
  ajouter_fin (1, 20, tableau, & la_liste);
  ajouter_tete (21, 50, tableau, & la_liste);
  // verification
  list_equals_deque (la_liste, tableau);
}

// ajouter n élts de façon aléatoire
TEST(TestList, ajoutAleatoire)
{
  nb_malloc = 0;
  std::deque<int> tableau;
  list_elem_t * la_liste = NULL;
  // ajout
  ajout_aleatoire (tableau, & la_liste);
  // verification
  list_equals_deque (la_liste, tableau);
}



//------------------------------------------------------------------------
// test des fonctions de recherche
//------------------------------------------------------------------------

TEST(TestList, recherche)
{
  nb_malloc = 0;
  list_elem_t * la_liste = NULL;
  // ajout de 20 valeurs
  for (int i = 0 ; i < 20 ; i++) { insert_tail (&la_liste, i); }
  // recherche d'une valeur presente dans la liste
  list_elem_t * res = find_element (la_liste, 10);
  ASSERT_TRUE (res != NULL);
  EXPECT_EQ (10, res->value);
  // recherche d'une position negative
  res = find_element (la_liste, -3);
  EXPECT_EQ (NULL, res);
  // recherche d'une position depassant la taille de la liste
  res = find_element (la_liste, 25);
  EXPECT_EQ (NULL, res);
}

//------------------------------------------------------------------------
// test des fonctions de retrait
//------------------------------------------------------------------------



//------------------------------------------------------------------------
// tests inversion liste
//------------------------------------------------------------------------

// À COMPLÉTER ...

