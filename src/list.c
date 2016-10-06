/**************************************************************************
 * L3Informatique						Module SYR1
 * 			TP de programmation en C
 *			Mise en oeuvre de listes chaînées
 *
 * Groupe 	:
 * Nom Prénom 1 :
 * Nom Prénom 2 :
 *
 **************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

int nb_malloc = 0;	// compteur global du nombre d'allocations

/*
 * SYNOPSYS    :
 *   list_elem_t * create_element(int value)
 * DESCRIPTION :
 *   crée un nouveau maillon de liste, dont le champ next a été initialisé à NULL, et
 *   dont le champ value contient l'entier passé en paramètre.
 * PARAMETRES :
 *   value : valeur de l'élément
 * RESULTAT :
 *   NULL en cas d'échec, sinon un pointeur sur une structure de type list_elem_t
 */
static list_elem_t *
create_element (int value)
{
  list_elem_t * newelt = malloc (sizeof (list_elem_t));
  if (newelt != NULL) {
    ++nb_malloc;
    newelt->value = value;
    newelt->next = NULL;
  }
  return newelt;
}

/*
 * SYNOPSYS    :
 *   void free_element(list_elem_t * l)
 * DESCRIPTION :
 *   libère un maillon de liste.
 * PARAMETRES  :
 *   l : pointeur sur le maillon à libérer
 * RESULTAT    :
 *   rien
 */
static void
free_element (list_elem_t * l)
{
  --nb_malloc;
  free (l);
}

/*
 * SYNOPSYS :
 *   int insert_head(list_elem_t * * l, int value)
 * DESCRIPTION :
 *   Ajoute un élément en tête de liste, à l'issue de l'exécution de la fonction,
 *   *l désigne la nouvelle tête de liste.
 * PARAMETRES :
 *   list_elem_t ** l : pointeur sur le  pointeur de tête de liste
 *   int value : valeur de l'élément à ajouter
 * RESULTAT :
 *    0 en cas de succès.
 *   -1 si l'ajout est impossible.
 */
int
insert_head (list_elem_t * * l, int value)
{
  if (l == NULL) { return -1; }
  list_elem_t * new_elt = create_element (value);
  if (new_elt == NULL) { return -1; }

  new_elt->next = *l;
  *l = new_elt;
  return 0;
}

/*
 * SYNOPSYS :
 *   int insert_tail(list_elem_t * * l, int value)
 * DESCRIPTION :
 *   Ajoute un élément en queue de la liste (* l désigne la tête de liste)
 * PARAMETRES :
 *   list_elem_t ** l : pointeur sur le pointeur de tête de liste
 *   int value : valeur de l'élément à ajouter
 * RESULTAT :
 *    0 en cas de succès.
 *   -1 si l'ajout est impossible.
 */
int
insert_tail(list_elem_t * * l, int value) {
  if (l == NULL) { return -1; }

  // Creer le nouvel element
  list_elem_t * new_elt = create_element (value);
  if (new_elt == NULL) { return -1; }

  // Si la liste est vide, le nouvel element est la nouvelle tete
  if (*l == NULL) { *l = new_elt; return 0; }

  // Sinon parcourir la liste jusqu'au dernier element
  while ((*l)->next != NULL) { l = &((*l)->next); }

  // Ajouter le nouvel element
  (*l)->next = new_elt;
  return 0;
}

/*
 * SYNOPSYS :
 *   list_elem_t * find_element(list_elem_t * l, int index)
 * DESCRIPTION :
 *   Retourne un pointeur sur le maillon à la position n°i de la liste
 *   (le 1er élément est situé à la position 0).
 * PARAMETRES :
 *   int index : position de l'élément à retrouver
 *   list_elem_t * l : pointeur sur la tête de liste
 * RESULTAT :
 *   - un pointeur sur le maillon de la liste en cas de succès
 *   - NULL si erreur
 */
list_elem_t *
find_element(list_elem_t * l, int index) {
  if (l == NULL || index < 0) { return NULL; }
  // Cas d'arret
  if (index == 0) { return l; }
  // Recursion
  return find_element(l->next,index-1);
}

/*
 * SYNOPSYS :
 *   int remove_element(list_elem_t * * ppl, int value)
 * DESCRIPTION :
 *   Supprime de la liste (dont la tête a été passée en paramètre) le premier élément de
 *   valeur value, et libère l'espace mémoire utilisé par le maillon
 *   ainsi supprimé.
 *   Attention : à l'issue de la fonction la tête de liste peut avoir été modifiée.
 * PARAMETRES :
 *   list_elem_t ** ppl : pointeur sur le  pointeur de tête de liste
 *   int value  : valeur à supprimer de la liste
 * RESULTAT :
 *    0 en cas de succès.
 *   -1 si erreur
 */
int
remove_element(list_elem_t * * ppl, int value) {
  if (ppl == NULL) { return -1; }
  // Si la liste est vide, impossible de supprimer
  if (*ppl == NULL) { return -1; }

  list_elem_t * element_supprime;
  // Cas de suppression de la tete de la liste
  if ((*ppl)->value == value) {
	element_supprime = *ppl;
	*ppl = (*ppl)->next;
	free_element (element_supprime);
	return 0;
  }

  // Parcourir la liste jusqu'a l'element precedent le maillon a supprimer
  while ((*ppl)->next != NULL && ((*ppl)->next)->value != value) {
	ppl = &((*ppl)->next);
  }

  // S'il n'y a pas de prochain element, la valeur n'est pas dans la liste
  if ((*ppl)->next == NULL) { return -1; }

  // Supprimer le prochain maillon
  element_supprime = (*ppl)->next;
  (*ppl)->next = element_supprime->next;
  free_element (element_supprime);
  return 0;
}

/*
 * SYNOPSYS :
 *   void reverse_list(list_elem_t * * l)
 * DESCRIPTION :
 *   Modifie la liste en renversant l'ordre de ses élements
 *   le 1er élément est placé en dernière position, le 2nd en
 *   avant dernière, etc.)
 * PARAMETRES :
 *   list_elem_t ** l : pointeur sur le pointeur de tête de liste
 * RESULTAT :
 *   aucun
 */
void
reverse_list(list_elem_t * * l) {
  // Cas d'erreur
  if (l != NULL) {
	// Ne pas renverser une liste vide
	if (*l != NULL) {
		list_elem_t * previous = NULL;
		list_elem_t * next;
		while ((*l)->next != NULL) {
			next = (*l)->next;
			(*l)->next = previous;
			previous = *l;
			*l = next;
		}
		(*l)->next = previous;
	}
  }
}
