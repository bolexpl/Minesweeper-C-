#include <iostream>
#include <vector>
#include <chrono>

#ifdef _WIN32
#include <cstdlib>
#include <windows.h>
#define CLEAN "cls"
#define sleep Sleep
#define WAIT 3000
#endif

#ifdef __gnu_linux__
#include <unistd.h>
#define CLEAN "clear"
#define WAIT 3
#include <unistd.h>
#endif

#include "../header/functions.h"
#include "../header/mineswepper.h"

using namespace std;

bool saper_menu(int &x, int &y, int &hardline, int &countFields, int &level) {
    char choose;
    system(CLEAN);
    cout << "Wybierz poziom trudności:" << endl;
    wybor:
    cout << "1. łatwy (9x9)" << endl;
    cout << "2. średni (16x16)" << endl;
    cout << "3. trudny (20x20)" << endl;
    cout << "4. własne ustawienia" << endl;
    cout << "0. wróć" << endl;
    cin >> choose;
#ifdef _WIN32
    cin.clear();
    cin.sync();
#endif
    system(CLEAN);
    level = (int) choose - '0';
    switch (choose) {
        case '1':
            x = 9;
            y = 9;
            hardline = 12;
            break;
        case '2':
            x = 16;
            y = 16;
            hardline = 30;
            break;
        case '3':
            x = 20;
            y = 20;
            hardline = 60;
            break;
        case '4':
        mines:
            cout << "Ile pól poziomo? ";
            cin >> x;
            cout << "Ile pól pionowo? ";
            cin >> y;
            cout << "Ile min? ";
            cin >> hardline;

            // jeśli ilość min jest większa niż ilość pól
            if (hardline >= (x * y)) {
                system(CLEAN);
                cout << "Za dużo min!" << endl;
                goto mines;
            }
            break;
        case '0':
            return true;
        default:
            cout << "Wybierz jedną z opcji!" << endl;
            goto wybor;
    }
    countFields = x * y;
    return false;
}

void write(int x, int y, vector<vector<int> > board, vector<vector<int> > discovered, int hardline) {

    cout << "Pozostałe miny: " << hardline << endl;
#ifdef _WIN32
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

    for (int i = 0; i <= y + 1; i++) {
        if (i < 10 | i == y + 1) {
            cout << " ";
        }
        if (i != 0 && i != y + 1) {
            cout << " " << i << " ";
        } else {
            cout << "   ";
        }
        if (i == 0 || i == y + 1) {
            cout << "   ";
        } else {
            cout << " | ";
        }
        for (int c = 1; c < x + 1; c++) {
            if (i == 0 || i == y + 1) {
                if (c >= 10) {
                    cout << "-" << c << "-";
                } else {
                    cout << "-" << c << "--";
                }
            } else {
                if (i > 0 && c > 0 && c < x + 1) {
                    if (discovered[c - 1][i - 1] == -1) {
#ifdef _WIN32
                        SetConsoleTextAttribute(hconsole,2);
                        cout <<" F  ";
                        SetConsoleTextAttribute(hconsole,15);
#endif
#ifdef __gnu_linux__
                        cout << " \033[0;32mF\033[0m  ";
#endif
                    } else if (discovered[c - 1][i - 1] == 0) {
                        cout << " x  ";
                    } else if (board[c - 1][i - 1] == -1) {
#ifdef _WIN32
                        SetConsoleTextAttribute(hconsole,4);
                        cout <<" #  ";
                        SetConsoleTextAttribute(hconsole,15);
#endif
#ifdef __gnu_linux__
                        cout << " \033[0;31m#\033[0m  ";
#endif
                    } else if (board[c - 1][i - 1] != 0) {
                        cout << " ";
                        switch (board[c - 1][i - 1]) {
                            case 1:
#ifdef _WIN32
                                SetConsoleTextAttribute(hconsole,9);
#endif
#ifdef __gnu_linux__
                                cout << "\033[1;34m";
#endif
                                break;
                            case 2:
#ifdef _WIN32
                                SetConsoleTextAttribute(hconsole,10);
#endif
#ifdef __gnu_linux__
                                cout << "\033[1;32m";
#endif
                                break;
                            case 3:
#ifdef _WIN32
                                SetConsoleTextAttribute(hconsole,12);
#endif
#ifdef __gnu_linux__
                                cout << "\033[1;31m";
#endif
                                break;
                            case 4:
#ifdef _WIN32
                                SetConsoleTextAttribute(hconsole,14);
#endif
#ifdef __gnu_linux__
                                cout << "\033[1;33m";
#endif
                                break;
                            case 5:
#ifdef _WIN32
                                SetConsoleTextAttribute(hconsole,11);
#endif
#ifdef __gnu_linux__
                                cout << "\033[1;36m";
#endif
                                break;
                            case 6:
#ifdef _WIN32
                                SetConsoleTextAttribute(hconsole,13);
#endif
#ifdef __gnu_linux__
                                cout << "\033[1;35m";
#endif
                                break;
                            case 7:
#ifdef _WIN32
                                SetConsoleTextAttribute(hconsole,1);
#endif
#ifdef __gnu_linux__
                                cout << "\033[0;34m";
#endif
                                break;
                            case 8:
#ifdef _WIN32
                                SetConsoleTextAttribute(hconsole,8);
#endif
#ifdef __gnu_linux__
                                cout << "\033[1;30m";
#endif
                                break;
                        }
                        cout << board[c - 1][i - 1];
#ifdef _WIN32
                        SetConsoleTextAttribute(hconsole,15);
#endif
#ifdef __gnu_linux__
                        cout << "\033[0m";
#endif
                        cout << "  ";
                    } else {
                        cout << "    ";
                    }
                }
            }
        }
        if (i == 0 || i == y + 1) {
            cout << "   ";
        } else {
            cout << " | ";
        }
        if (i != 0 && i != y + 1) {
            cout << " " << i;
        }
        cout << endl;
    }
}

void numbers(int x, int y, vector<vector<int> > &board, vector<vector<int> > &discovered) {

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            if (board[i][j] == 0) {
                int countMines = 0;

                int xmin = (i == 0) ? 0 : i - 1;
                int xmax = (i == x - 1) ? x - 1 : i + 1;

                int ymin = (j == 0) ? 0 : j - 1;
                int ymax = (j == y - 1) ? y - 1 : j + 1;

                for (int c = xmin; c <= xmax; c++) {
                    for (int z = ymin; z <= ymax; z++) {
                        if (board[c][z] == -1) {
                            countMines++;
                        }
                    }
                }
                board[i][j] = countMines;
            }
        }
    }
}

void mines_generate(int x, int y, int hardline, vector<vector<int> > &board, vector<vector<int> > &discovered,
                    int targetx, int targety) {
    int tmp, tmp2;
    for (int i = 0; i < hardline; i++) {
        do {
            tmp = rand() % x;
            tmp2 = rand() % y;
        } while (board[tmp][tmp2] == -1
                 || (tmp == targetx
                     && tmp2 == targety)
                 || (tmp == targetx - 1
                     && tmp2 == targety - 1)
                 || (tmp == targetx + 1
                     && tmp2 == targety + 1)
                 || (tmp == targetx - 1
                     && tmp2 == targety)
                 || (tmp == targetx + 1
                     && tmp2 == targety)
                 || (tmp == targetx
                     && tmp2 == targety - 1)
                 || (tmp == targetx
                     && tmp2 == targety + 1)
                 || (tmp == targetx + 1
                     && tmp2 == targety - 1)
                 || (tmp == targetx - 1
                     && tmp2 == targety + 1)
                );
        board[tmp][tmp2] = -1;
    }

    numbers(x, y, board, discovered);
}

void generate(int x, int y, vector<vector<int> > &board, vector<vector<int> > &discovered) {
    for (int i = 0; i < x; i++) {
        vector<int> row;
        vector<int> row2;
        for (int j = 0; j < y; j++) {
            row.push_back(0);
            row2.push_back(0);
        }
        board.push_back(row);
        discovered.push_back(row2);
    }
}

bool discovery(bool action, int fieldx, int fieldy, vector<vector<int> > &board,
               vector<vector<int> > &discovered, int x, int y, int &countFields, int &emptyFields, int &hardline,
               bool prime) {

    if (action) {

        // strzał
        // jeśli nie jest odkryte ani zablokowane
        if (discovered[fieldx][fieldy] == 0) {

            discovered[fieldx][fieldy] = 1;
            countFields--;
            emptyFields--;

            if (board[fieldx][fieldy] == -1) {
                return false;
            }

            // rekurencja dla ośmiu pustych pól dookoła
            if (board[fieldx][fieldy] == 0) {
                for (int i = fieldx - 1; i <= fieldx + 1; i++) {
                    for (int i2 = fieldy - 1; i2 <= fieldy + 1; i2++) {
                        if (i >= 0 && i < x && i2 >= 0 && i2 < y) {
                            discovery(true, i, i2, board, discovered, x, y, countFields, emptyFields, hardline, false);
                        }
                    }
                }
            }
        } else if (discovered[fieldx][fieldy] == 1 && board[fieldx][fieldy] > 0 && prime) {

            // po wybraniu odkrytej liczby która ma odpowiednią ilość flag dookoła
            // odkrywają się pozostałe pola
            int count = 0;
            // liczę flagi dookoła
            for (int i = fieldx - 1; i <= fieldx + 1; i++) {
                for (int i2 = fieldy - 1; i2 <= fieldy + 1; i2++) {
                    if (i >= 0 && i2 >= 0 && i < x && i2 < y) {
                        if (discovered[i][i2] == -1) {
                            count++;
                        }
                    }
                }
            }

            if (count == board[fieldx][fieldy]) {
                bool play;
                for (int i = fieldx - 1; i <= fieldx + 1; i++) {
                    for (int i2 = fieldy - 1; i2 <= fieldy + 1; i2++) {
                        if (i >= 0 && i2 >= 0 && i < x && i2 < y) {
                            if (discovered[i][i2] != -1) {
                                play = discovery(true, i, i2, board, discovered, x, y, countFields, emptyFields,
                                                 hardline, false);
                                if (!play) {
                                    return false;
                                }
                            }
                        }


                    }
                }
            }
        }
    } else {

        // postawienie lub zabranie flagi
        if (discovered[fieldx][fieldy] == 0) {
            discovered[fieldx][fieldy] = -1;
            countFields--;
            hardline--;

            if (board[fieldx][fieldy] != -1) {
                emptyFields--;
            }
        } else if (discovered[fieldx][fieldy] == -1) {
            discovered[fieldx][fieldy] = 0;
            countFields++;
            hardline++;
            if (board[fieldx][fieldy] != -1) {
                emptyFields++;
            }
        }
    }
    return true;
}

void mines() {
    /**
     * emptyFields - pola niezaminowane
     * countFields - ilość wszystkich pól
     * hardline - ilość min
     * x,y - rozmiar planszy
     * level - wybrany poziom
     * emptyFields - ilość pól niezaminowanych
     * */
    int x, y, hardline, countFields, level, emptyFields;

    /**
     * board - zawartość pól (liczba, mina)
     * discovered - stan pól (zakryte, odkryte, oflagowane)
     * field - współrzędne
     * */
    vector<vector<int> > board;
    vector<vector<int> > discovered;
    vector<int> field;

    bool play = true; //zmienna sterująca pętlą
    string input; //ciąg wpisany przez gracza
    int score_time; //czas gry
    chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now(); //czas początku gry

    // wyświetlenie menu i ewentualne wyjście z gry
    if (saper_menu(x, y, hardline, countFields, level)) {
        return;
    }

    // obliczenie liczby niezaminowanych pól
    emptyFields = countFields - hardline;
    // generowanie pustej planszy
    generate(x, y, board, discovered);

    // zmienna oznaczająca, czy to jest pierwszy ruch
    bool begin = true;
#ifdef _WIN32
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif
#ifdef __gnu_linux__
    cin.ignore();
#endif
    do {
        system(CLEAN);

        // wypisanie planszy
        write(x, y, board, discovered, hardline);


        cout << endl << "Numer pola podajemy jako x,y np. 2,3" << endl;
        cout << "Aby postawić flagę to podajemy -x,y" << endl;
        cout << "Aby skończyć należy wpisać 'q'" << endl << endl;
        choose:
        cout << "Wybierz pole:  ";
        getline(cin, input);

        // wyjście z gry
        if (input == "q") {
            play = false;
            break;
        }

        unsigned int i;
        // liczba przecinków
        int countPoint = 0;
        // pozycja przecinka
        int positionPoint = 0;
        // czy dane są poprawne
        bool czy = false;

        // liczenie przecinków
        for (i = 0; i < input.length(); i++) {
            if (input.at(i) == ',') {
                czy = true;
                positionPoint = i;
                countPoint++;
            }
        }
        // jeśli przecinek w złym miejscu
        if (positionPoint == 0 || positionPoint == input.length() - 1 || countPoint > 1) {
            czy = false;
        }
        if (!czy) {
            cout << "Zły wybór!" << endl;
            goto choose;
        }

        // zamiana ciągu znaków na dwie wartości liczbowe
        field = getField(input);

        // czy wybrano pole poza planszą
        if (field[0] < -x || field[1] < 0 || field[0] > x || field[1] > y) {
            cout << "Zły wybór!" << endl;
            continue;
        }

        // jeśli pierwszy ruch to generuje miny poza ośmioma polami dookoła
        if (begin && field[0] > 0) {
            mines_generate(x, y, hardline, board, discovered, field[0] - 1, field[1] - 1);
            begin = false;
        }

        // jeśli x jest ujemny to zmienia znak i wywołuje funkcję do stawiania flagi
        // jeśli funkcja trafi na minę to zwraca false i gra się kończy
        if (field[0] < 0) {
            field[0] = -field[0];
            discovery(false, field[0] - 1, field[1] - 1, board, discovered, x, y, countFields, emptyFields,
                      hardline, true);
        } else {
            play = discovery(true, field[0] - 1, field[1] - 1, board, discovered, x, y, countFields, emptyFields,
                             hardline, true);
        }

        // jeśli zablokowane są wszystkie miny lub odkryte są pozostałe pola to gracz wygrał
        if (emptyFields == 0) {
            system(CLEAN);
            write(x, y, board, discovered, hardline);
#ifdef _WIN32
            SetConsoleTextAttribute(hconsole,2);
            cout << endl << "Wygrana" << endl << endl;
            SetConsoleTextAttribute(hconsole,15);
#endif
#ifdef __gnu_linux__
            cout << endl << "\033[32mWygrana \033[0m" << endl << endl;
#endif
            // zakończenie głównej pętli
            play = false;
            sleep(WAIT);
            continue;
        }

        // komunikat przegranej
        if (!play) {
            system(CLEAN);
            //odkrycie min
            // odsłonięcie min
            for (i = 0; i < x; i++) {
                for (int j = 0; j < y; j++) {
                    if (board[i][j] == -1) {
                        discovered[i][j] = 1;
                    }
                }
            }
            write(x, y, board, discovered, hardline);
#ifdef _WIN32
            SetConsoleTextAttribute(hconsole,12);
            cout << endl << "Przegrana" << endl << endl;
            SetConsoleTextAttribute(hconsole,15);
#endif
#ifdef __gnu_linux__
            cout << endl << "\033[31mPrzegrana \033[0m" << endl << endl;
#endif
            sleep(WAIT);
        }
    } while (play);
}