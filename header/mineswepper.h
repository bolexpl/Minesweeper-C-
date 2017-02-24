#ifndef MAIN_SAPPER_H
#define MAIN_SAPPER_H

#include <vector>

using namespace std;

/**
 * Główne menu
 * @param x - szerokość planszy
 * @param y - wysokość planszy
 * @param hardline - ilośc min
 * @param countFields - ilość pól
 * @return true - powrót do menu głównego
 * */
bool saper_menu(int &x, int &y, int &hardline, int &countFields, int &level);

/**
 * Narysowanie planszy
 * @param x - szerokość planszy
 * @param y - wysokość planszy
 * @param board - przechowuje wartości pól
 * @param discovered - przechowuje stan pól(odkryte/zakryte/flaga)
 * @param hardline - ilośc min
 * */
void write(int x, int y, vector<vector<int> > board, vector<vector<int> > discovered, int hardline);

/**
 * Generowanie planszy
 *
 * board to plansza:
 * -1 - mina
 * 0 - puste pole
 * cyfra - liczba min
 *
 * discovered to odkrywanie planszy:
 * 1 - odkryte
 * 0 - zakryte
 * -1 - flaga
 * */

/**
 * Generowanie liczb
 * @param x - szerokość planszy
 * @param y - wysokość planszy
 * @param board - przechowuje wartości pól
 * @param discovered - przechowuje stan pól(odkryte/zakryte/flaga)
 * */
void numbers(int x, int y, vector<vector<int> > &board, vector<vector<int> > &discovered);

/**
 * Generowanie min poza polem które trafił gracz przy pierwszym wyborze
 * @param x - szerokość planszy
 * @param y - wysokość planszy
 * @param hardline - ilośc min
 * @param board - przechowuje wartości pól
 * @param discovered - przechowuje stan pól(odkryte/zakryte/flaga)
 * @param targetx - x pola które wybrał gracz
 * @param targety - y pola które wybrał gracz
 * */
void mines_generate(int x, int y, int hardline, vector<vector<int> > &board, vector<vector<int> > &discovered,
                    int targetx, int targety);

/**
 * Generowanie pustej planszy
 * @param x - szerokość planszy
 * @param y - wysokość planszy
 * @param board - przechowuje wartości pól
 * @param discovered - przechowuje stan pól(odkryte/zakryte/flaga)
 * */
void generate(int x, int y, vector<vector<int> > &board, vector<vector<int> > &discovered);

/**
 * Odsłonięcie pola
 * @param action true - strzał/false - flaga
 * @param fieldx - wybrane pole
 * @param fieldy - wybrane pole
 * @param board - przechowuje wartości pól
 * @param discovered - przechowuje stan pól(odkryte/zakryte/flaga)
 * @param x - szerokość planszy
 * @param y - wysokość planszy
 * @param countFields - ilość pól
 * @param hardline - ilośc min
 * @param prime - czy to pole odsłaniane przez gracza czy rekurencyjnie
 * rekurencyjnie miny nie są odkrywane.
 * @return true - mina i koniec gry
 * */
bool discovery(bool action, int fieldx, int fieldy, vector<vector<int> > &board,
               vector<vector<int> > &discovered, int x, int y, int &countFields, int &emptyFields, int &hardline, bool prime);

/**
 * Główna funkcja gry
 * */
void mines();

#endif //MAIN_SAPPER_H
