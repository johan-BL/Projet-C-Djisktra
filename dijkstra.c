#include "dijkstra.h"
#include "stdlib.h"
//#include "animation.h"
#include <math.h>

/**
 * cout : calcule le coût pour rejoindre le noeud suivant depuis le noeud
 * courant. Ce coût est égal à la distance euclidienne entre les deux noeuds,
 * plus le dénivelé entre ces deux noeuds s'il est positif.
 * 
 * Pré-conditions :
 *  - dans_les_bornes(grille, courant)
 *  - dans_les_bornes(grille, suivant)
 * Post-conditions :
 *  - cout > 0, potentiellement infini (INFINITIY)
 *
 * @param grille heightmap contenant les hauteurs
 * @param courant noeud duquel on part pour calculer le coût
 * @param suivant noeud auquel on arrive pour calculer le coût
 * @return coût pour passer de courant à suivant
 */
static float cout(grille_t grille, coord_t courant, coord_t suivant) {
    float cout = -1.0;
    if ((dans_les_bornes (grille, courant)) && (dans_les_bornes (grille, suivant))){
        cout = distance_euclidienne (courant, suivant);
        float denivele = get_hauteur (grille, suivant) - get_hauteur (grille, courant);
        if (denivele > 0){
            cout = cout + denivele;}
        else{
            NULL;}
    }
    else {
        NULL;}
    return cout;
        
}

/**
 * construire_chemin_vers - Construit le chemin depuis le noeud de départ donné vers le
 * noeud donné. On passe un chemin en entrée-sortie de la fonction, qui est mis à jour
 * par celle-ci.
 *
 * Ce sous-programme fonctionne récursivement :
 *  1. Si le noeud est égal au noeud de départ, on a fini
 *  2. Sinon, on construit le chemin du départ au noeud précédent (appel récursif)
 *  3. Dans tous les cas, on ajoute le noeud au chemin, avec les caractéristiques associées dans visites
 *
 * @param chemin [in/out] chemin dans lequel enregistrer les étapes depuis le départ vers noeud
 * @param visites [in] liste des noeuds visités créée par l'algorithme de Dijkstra
 * @param source noeud de départ du chemin
 * @param noeud noeud vers lequel on veut construire le chemin depuis le départ
 */
// TODO: construire_chemin_vers
void construire_chemin_vers (liste_noeud_t** chemin, liste_noeud_t* Visites, coord_t source, coord_t noeud) {
    if (memes_coord (source, noeud)) {
        NULL;}
    else{
        construire_chemin_vers (chemin, Visites, source, precedent_noeud_liste (Visites,noeud));}
    inserer_noeud_liste (*chemin, noeud, precedent_noeud_liste (Visites, noeud), cout_noeud_liste (Visites, noeud));}

float dijkstra(
        grille_t grille, 
        coord_t source, coord_t destination, 
        float seuil,
        liste_noeud_t** chemin) {
    float retour = -1.0;
    coord_t* voisins = NULL;
    if ((!dans_les_bornes (grille, source)) || (!dans_les_bornes (grille, destination))){
        NULL;}
    else {
        liste_noeud_t* A_Visiter = creer_liste();
        liste_noeud_t* Visites = creer_liste();
        inserer_noeud_liste (A_Visiter, source, source, 0);
        while (!est_vide_liste(A_Visiter)) {
            coord_t courant = min_noeud_liste (A_Visiter);
            float cout_visite = cout_noeud_liste (A_Visiter, courant);
            coord_t precedent_visite = precedent_noeud_liste (A_Visiter, courant);
            inserer_noeud_liste (Visites, courant, precedent_visite, cout_visite);
            supprimer_noeud_liste (A_Visiter, courant);
            size_t nb_voisins = get_voisins(grille, courant, seuil, &voisins);
            for (size_t i = 0; i < nb_voisins; i++) {
                if (contient_noeud_liste (Visites, voisins[i])) {
                    NULL;}
                else {
                    float delta_prime = cout_noeud_liste (Visites, courant) + cout (grille, courant, voisins[i]);
                    float delta = 0.0;
                    if (contient_noeud_liste (A_Visiter, voisins[i])) {
                        delta = cout_noeud_liste (A_Visiter, voisins[i]);}
                    else {
                        delta = INFINITY;}
                    if (delta_prime < delta) {
                        inserer_noeud_liste (A_Visiter, voisins[i], courant, delta_prime);}
                    else {
                        NULL;
                    }
                }                 
            }            
            free(voisins);
        }
        detruire_liste(&A_Visiter);
        if (memes_coord (source, destination)){
            retour = 0.0;}
        else {
            NULL;}
        if (chemin != NULL) {
            *chemin = creer_liste();
            if (!contient_noeud_liste (Visites, destination)) {
                NULL;}
            else {
                retour = cout_noeud_liste (Visites, destination);
                coord_t noeud_precedent = precedent_noeud_liste (Visites, destination);
                construire_chemin_vers (chemin, Visites, source, noeud_precedent);}
            detruire_liste(&Visites);
        }
        else{
            chemin = NULL;
            detruire_liste(&Visites);}
        
    }
    
    return retour;
}


