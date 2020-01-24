/*
 -----------------------------------------------------------------------------------
 Laboratoire : Snake
 Fichier     : main.cpp
 Auteur(s)   : Yann Lederrey
 Date        : 20.01.2019
 
 Compilateur : g++ (GCC) 9.2.0

 Brief       : Implémentation d'un jeu de snake en console
 Sources     : https://code.sololearn.com/c8ubSKG6fX73/#cpp
 -----------------------------------------------------------------------------------
 */

#include <string>
#include <cstring>
#include <unistd.h>
#include <stdio.h>
#include <limits>
#include <cstdlib>

#include "sysFunc.h"
#include "display.h"
#include "gameEngine.h"
#include "score.h"

using namespace std;

const int WIDTH = 20;
const int HEIGHT = 20;
const int START_POS_X_SNAKE = WIDTH / 2;
const int START_POS_Y_SNAKE = HEIGHT / 2;
const int SPEED = 500000;
const string FILENAME = "score.txt";
const int NB_OBSTACLE = 8;
const char TXT_SEPAR = ' ';

/**
* @brief Fonction affichant le menu et supprimant l'affichage du terminal.
* @param score score actuel du joueur.
*/
void restart(int score);

/**
* @brief Fonction affichant le menu d'instructions et supprimant l'affichage du terminal.
* Cette fonction permet aussi de quitter le menu d'instructions.
* @param score score actuel du joueur.
*/
void getInstructions(int score);

/**
* @brief Fonction affichant le classement et supprimant l'affichage du terminal.
* Cette fonction permet aussi de quitter le classement.
* @param score score actuel du joueur.
*/
void getRanking(int score);

/**
* @brief Fonction demandant le nom de l'utilisateur
*/
void getUsername(int score);

/**
* @brief Fonction affichant le menu de recherche de score
* @param score score actuel du joueur.
*/
void getUserScore(int score);

/**
* @brief Fonction faisant la traduction entre la direction entrée par l'utilisateur et la direction du serpent.
* @param direction direction proposée par l'utilisateur
* @param oldDirection Direction actuelle du serpent
* @param gameover [out] définis si l'utilisateur arrête la partie.
* @return nouvelle direction du serpent.
*/
eDirection manageDirection(char direction, eDirection oldDirection, bool& gameover);

/**
* @brief Fonction remettant les variables de jeu par défaut.
* @param posSnakeX [out] position X de la tête du serpent.
* @param posSnakeY [out] position Y de la tête du serpent.
* @param direction [out] direction initiale du serpent.
* @param gameover [out] définis si le joueur arrête ou perd la partie.
*/
void reload(int& posSnakeX, int& posSnakeY, int& length, eDirection& direction, bool& gameover);

int main()
 {
    // CONFIGURATIONS VARIABLES
    bool gameover = false;
    bool shutDown = false;
    int tailX[400], tailY[400];
    char actualDirection = KEY_UP;

    int posSnakeX;
    int posSnakeY;
    int snakeSize;
    eDirection dir;
    reload(posSnakeX, posSnakeY, snakeSize, dir, gameover);

    int posFruitX;
    int posFruitY;
    GamePanel gp(HEIGHT, std::vector<eObstacle>(WIDTH, CLEAR));
    obstacleSpawn(WIDTH, HEIGHT, gp, NB_OBSTACLE, posSnakeX, posSnakeY);
    fruitSpawn(posFruitX,posFruitY, WIDTH, HEIGHT, gp);


    // BOUCLE DU MENU.
    do {
        restart(snakeSize);

        string input;
        cin >> input;
        if (input.at(0) == KEY_START)
        {
            reload(posSnakeX, posSnakeY, snakeSize, dir, gameover);

            obstacleSpawn(WIDTH, HEIGHT, gp, NB_OBSTACLE, posSnakeX, posSnakeY);

            // BOUCLE DE JEU
            while (!gameover) {

                clearScreen();

                // dessine le pleateau de jeu
                draw(WIDTH, HEIGHT, posSnakeX, posSnakeY, posFruitX, posFruitY, snakeSize, tailX, tailY, gp);

                // detecte une entrée sur le clavier et récupère le charactère.
                char newDirection;
                if (kbhit()) {
                    newDirection = getch();
                }
                if ((newDirection != actualDirection)) {
                    actualDirection = newDirection;
                }

                // Convertis la direction donnée par l'utilisateur pour le serpent.
                dir = manageDirection(actualDirection, dir, gameover);

                // Ordonne le mouvement au serpent et définis si il meurt.
                logic(WIDTH, HEIGHT, posSnakeX, posSnakeY, posFruitX, posFruitY, snakeSize, tailX, tailY, dir, gameover, gp);

                // met en pause le système définissant la vitesse du serpent.
                mySleep(SPEED);
            }
            getUsername(snakeSize);
        }
        // test si on souhaite afficher le menu
        else if (input.at(0) == KEY_INSTRUCTION)
            getInstructions(snakeSize);
        // test si on souhaite afficher le meilleur score d'un utilisateur
        else if (input.at(0) == KEY_SCORE_USER)
            getUserScore(snakeSize);
        // test si on souhaite arrêter de jouer.
        else if (input.at(0) == KEY_QUIT)
            shutDown = true;
        // test si on souhaite afficher le classement
        else if (input.at(0) == KEY_RANKING)
            getRanking(snakeSize);

    } while (shutDown == false);
    return 0;
}

void restart(int score)
 {
    clearScreen();
    displayMenu(score);
}

void getInstructions(int score)
 {
    clearScreen();
    displayInstructions();

    string input;
    cin >> input;
    if (input.at(0) == KEY_MENU)
        restart(score);
}

void getRanking(int score)
{
    clearScreen();
    displayRanking(FILENAME, TXT_SEPAR);

    string input;
    cin >> input;
    if (input.at(0) == KEY_MENU)
        restart(score);

}

void getUsername(int score) {
    clearScreen();
    string stringScore = to_string(score);
    string username;
    string separation = " ";
    std::cout << ENTER_USER ;
    std::cin >> username ;
    vector<string> userAndScore;
    userAndScore.push_back(username);
    userAndScore.push_back(separation);
    userAndScore.push_back(stringScore);
    writeFile(FILENAME, userAndScore );

}

void getUserScore(int score)
{
    // Lecture du fichier dans le vecteur
    VecStr scores = readFromFile(FILENAME);

    // Si l'ouverture du fichier n'a pas posé de problème
    if(!scores.empty())
    {
        int position;
        string scoreUser;
        string input; // L'entrée de l'utilisateur qui permet de recommencer la recherche ou quitter ce menu (score)
        string nom; // Va contenir le nom de l'utilisateur à rechercher
        VecStr allUsername; // Va contenir la liste de tous les noms d'utilisateurs

        do{
            clearScreen();
            displayUserScore(); // Texte de demande d'entrée à l'utilisateur
            cin >> nom;

            getAllUsername(scores, allUsername);
            // On récupère l'index de l'utilisateur à rechercher
            position = findUser(allUsername,nom);

            // Test pour voir si l'utilisateur a été trouvé
            if(position != -1)
            {
                scoreUser = scores.at(position);
                // On remplace l'espace par un texte plus "parlant"
                scoreUser.replace( scoreUser.find( FILE_SEPARATOR ) , FILE_SEPARATOR.length(), " and his best score is " );

                cout << scoreUser << endl;
            }
            else
            {
                cout << "There is no score for this user." << endl;
            }

            cout << "Press any key to restart or \"m\" to return to the menu." << endl;
            cin >> input;
        }
        while (input.at(0) != KEY_MENU); // Tant que l'utilisateur ne souhaite pas retourner au menu

        restart(score);
    }
    else
    {
        cout << "There are no scores. Press any key to return to the menu." << endl;
        getch(); // Attend une entrée utilisateur
        restart(score);
    }
}

eDirection manageDirection(char direction, eDirection oldDirection, bool& gameover)
 {
    eDirection dir;
    bool error = false;
    switch (direction)
    {
        case KEY_LEFT:
            dir = LEFT;
            break;

        case KEY_UP:
            dir = UP;
            break;

        case KEY_DOWN:
            dir = DOWN;
            break;

        case KEY_RIGHT:
            dir = RIGHT;
            break;

        case KEY_QUIT:
            dir = STOP;
            gameover = true;
            break;
        default:
            dir=oldDirection;
            break;
    }
    return dir;
}

void reload(int& posSnakeX, int& posSnakeY, int& length, eDirection& direction, bool& gameover){
    posSnakeX = START_POS_X_SNAKE;
    posSnakeY = START_POS_Y_SNAKE;
    length = 0;
    direction = UP;
    gameover=false;
}
