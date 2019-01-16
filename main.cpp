#include <iostream>
#include <ctime>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cmath>

using namespace std;

string mixLetters(string word){
    string mixed;
    int position(0);

    while (word.size() != 0)
    {
        position = rand() % word.size();
        mixed += word[position];
        word.erase(position, 1);
    }
    return mixed;
}

string pickMot(string dico){
    int position(0), nblines(0);
    string line, word;

    ifstream flux(dico);

    if(flux){
        flux.seekg(0,ios::beg);
        while(getline(flux, line)){
            nblines++;
        }
        position = rand() % nblines;
        flux.clear();
        flux.seekg(0,ios::beg);

        int ind(0);
        do{
            getline(flux,line);
            ind++;
        } while(ind < position);
        flux >> word;
    }
    else{
        cout << "ERROR: Unable to open the file for reading." << endl;
    }
    flux.close();
    return word;
}

int main()
{
    string mysteryWord, mixedWord, userWord;
    srand(time(0));
    string dicoName("dico.txt");

    char reponse;
    int const nbtry(5);
    int index(nbtry);
    do {
	     mysteryWord = pickMot(dicoName);
        mixedWord = mixLetters(mysteryWord);

        do
        {
            cout << endl << "What is this word ? " << mixedWord << endl;
            cin >> userWord;
            for (unsigned int i=0; i<userWord.length(); ++i){
                userWord[i] = ::toupper(userWord[i]);
            }

            if (userWord == mysteryWord)
            {
                cout << "Bravo !" << endl;
            }
            else{
                cout << "This is not the word !" << endl;
                if (index > 0){
                    cout << "You have " << index << " attempts." << endl;
                    index--;
                }
                else{
                    cout << "Lost ! The solution is : " << mysteryWord << "."<< endl;
                    break;
                }
            }
        }
        while (userWord != mysteryWord && index >= 0);

        cout << endl << "Do you want to play again ? (y/N)" << endl;
        cin >> reponse;
        index = nbtry;
    }
    while (reponse == 'y');

    return 0;
}
