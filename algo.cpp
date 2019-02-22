#include "algo.h"
#include "ray.h"

#include <cmath>
#include <iostream>       // std::cout
#include <typeinfo>       // operator typeid
#include <fstream>   // Ouverture fichiers

algo::algo(int n, wall *walls[], antena *Transmitter, antena *Receiver)
{
    /*
     * METHODE DU PLUS COURT CHEMIN
     * Prototype : Une seule réflection :
     * Principe :
     * 1) Construction du vecteur unitaire normal au mur
     * 2) Rotation de 90° de ce vecteur
     * 3) Calcul de la distance émetteur/mur (la plus courte) x 2
     * 4) Droite vecteur unitaire de départ Emetteur, de longueur 3) --> point final = position image
     * 5) Droite image-récepteur + intersection avec le mur point de départ
     * 6) Ray = demi-droite jusqu'au mur + demi droite jusqu'au récepteur.
     *
     *
     * METHODE DES ANGLES PAR RAPPORT AUX EXTREMITES
     * L'idée ici est de considérer l'orientation absolue du mur et de la droite tracée en rejoignant l'émetteur et une extrémité du mur, profitant de la conservation
     * angulaire de a symétrie orthogonale. Cette méthode est choisie car elle est plus générale que la précédente, où le vecteur orthogonal de plus court chemin
     * n'existe pas forcément.
     */
    amount_reflect = n;
    wallsL = walls;
    a_wall = *walls[0]->arg();

}

void algo::createRay(){

}


ray algo::returnResults(){

}
