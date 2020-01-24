/*
 -----------------------------------------------------------------------------------
 Laboratoire : 10
 Fichier     : score.h
 Auteur(s)   : Melvin Merk, David Darmanger, Rébecca Tevaearai
 Date        : 23.01.2020

 But         : Fonctions ayant pour rôle d'afficher le score d'un utilisateur en particulier

 Remarque(s) :

 Compilateur : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
 */

#ifndef SCORE_H
#define SCORE_H

#include <vector>
#include <algorithm>
#include <fstream>

using VecStr = std::vector<std::string>;

const std::string FILE_SEPARATOR=" ";// Le caractère qui permet de séparer le nom d'utilisateur et son score dans le fichier
using VecStr = std::vector<std::string>;

/**
@brief                      Permet la lecture du dictionnaire. Utilisée également pour le tri dans l'ordre croissant
@param[in] fileName         string qui contient le nom du fichier à lire
@return                     retourne le dictionnaire sous la forme d'un vector<string>
*/
VecStr readFromFile(const std::string &fileName);

/**
@brief     Ecrit le nom d'utilisateur et le score dans un fichier txt
@param
*/
void writeFile(const std::string &fileName, VecStr& texte);

/**
@brief                      Permet de récupérer tous les noms d'utilisateurs sans leurs scores
@param[in] listScore        Vecteur de string qui contient le contenu du fichier de scores.
@param[in] listUsername     Vecteur de string qui contient la liste de tous les noms d'utilisateurs
*/
void getAllUsername(VecStr listScore, VecStr& listUsername);

/**
@brief                      Permet de trouver la position d'un utilisateur dans le vecteur qui contient les scores
@param[in] listUsername     Vecteur de string qui contient la liste de tous les noms d'utilisateur
@param[in] username         Le nom d'utilisateur à rechercher
@return                     Retourne l'index de la position de l'utilisateur
*/
int findUser(VecStr listUsername, std::string username);

#endif // SCORE_H


