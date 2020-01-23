/*
 -----------------------------------------------------------------------------------
 Laboratoire : 10
 Fichier     : score.cpp
 Auteur(s)   : Melvin Merk, David Darmanger, Rébecca Tevaearai
 Date        : 23.01.2019

 Compilateur : g++ (GCC) 9.2.0

 Brief       : Implémentation des fonctions du fichier score.h
 -----------------------------------------------------------------------------------
 */

#include "score.h"

using namespace std;

VecStr readFromFile(const string &fileName) {
    // Ouverture du fichier
    ifstream file;
    file.open(fileName, ios::in);
    // S'il y a eu un problème
    if(file.fail()){
        // Fermeture du fichier
        file.close();
        return VecStr(); // vector vide
    }

    VecStr scoreList;

    // Parcours ligne par ligne le fichier
    for(string line; getline(file, line);) {
        // On ajoute le mot (ligne actuelle) dans le dictionnaire
        scoreList.push_back(line);
    }

    // Fermeture du fichier
    file.close();

    return scoreList;
}

void getAllUsername(VecStr listScore, VecStr& listUsername)
{
    std::string username;

    for (size_t i = 0; i < listScore.size(); ++i){
        // On récupère la sous-chaîne qui contient uniquement le nom de l'utilisateur sans son score
        username = listScore.at(i).substr(0, listScore.at(i).find(FILE_SEPARATOR));
        // et on l'ajoute dans le vecteur qui contient tous les noms d'utlisateurs
        listUsername.push_back(username);
    }
}

int findUser(VecStr listUsername, std::string username)
{
    // On cherche le pseudo de l'utilisateur
    auto it = find(listUsername.begin(),listUsername.end(),username);
    if (it != listUsername.end())
    {
        // On retourne l'index de la position de l'utilisateur
        return distance(listUsername.begin(), it);
    }
    // On retourne -1 si l'utilisateur n'existe pas
    return -1;
}
