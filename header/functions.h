#ifndef MAIN_FUNCTIONS_H
#define MAIN_FUNCTIONS_H

using namespace std;

/**
 * Podzielenie ciągu na podciągi według podanego rozdzielnika (np. ',')
 * @param s - ciąg
 * @param delim - rozdzielnik
 * */
vector<string> explode(string const & s, char delim);

/**
 * Użytkownik podaje ciąg znaków w formacie x,y
 * Ta funkcja przerabia to na vector z wartościami int
 * @param s - ciąg
 * */
vector<int> getField(string s);

#ifdef _WIN32
string to_string( int t );
#endif

#endif //MAIN_FUNCTIONS_H
