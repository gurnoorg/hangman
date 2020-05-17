#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <termios.h>
#include <unistd.h>
#include <cstring>

// Ansii codes implemented from: https://stackoverflow.com/questions/9158150/colored-output-in-c/9158263
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

using namespace std;

// This function is based on info from https://stackoverflow.com/questions/6899025/hide-user-input-on-password-prompt
void inputPassword(string &password)
{
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    getline(cin, password);

    for (int i=0; i< password.length(); i++)
    {
        if (isupper(password[i]))
            //Converting uppercase to lowercase
            password[i] = password[i] + 32;
    }


    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}




void wordDisplayer(char *display, int location, char guess) {
    
    cout<< GREEN;
    display[location] = guess;
    for (int i=0; i<4; i++) {
        cout<<display[i];
    }
    cout<< RESET <<endl;

}

int main () {

    char display[4];

    for(int i=0; i<4; i++) {
        
        display[i] = '*';

    }
	string word;
	string gameOver= "HANGMAN";
	string progress;
	int count = 0;
	int wrongGuesses = 0;
	bool found = 0;
	char guess1;
	cout<< YELLOW << "Welcome to 4-letter hangman!" <<RESET<<endl;
    cout<<"***************************************************************"<<endl;
	cout<<"Player 1: please enter a 4 letter word for Player 2 to guess"<<endl;
    cout<<"NOTE: The input will be invisible, make sure there is no typos!"<<endl;
	inputPassword(word);
	if (word.length()!=4){
		cout<< RED << "The provided word is not 4 letters, please run the game again"<< RESET<<endl;
		return -1;
	}

    cout<<"***************************************************************"<<endl;
    cout<<CYAN<<"All guesses MUST be made in lowercase letters"<< RESET<<endl;
	cout<<"***************************************************************"<<endl;


	while(wrongGuesses<7){
	


		char oldGuess = guess1;
		cout<<"Guess a letter from a-z: "<<endl;
		cin>>guess1;
        cout<<"***************************************************************"<<endl;

		if(guess1 == oldGuess){

			cout<< RED << "You already guessed that letter, try again!"<< RESET <<endl;
			continue;
		}

		
		for(int i = 0; i<4; i++) {

			if (word[i] == guess1) {

				cout<<"CORRECT!"<<endl;
                wordDisplayer(display,i,guess1);
                count+=1;
				found = 1;
		
			}

		}


		if (found == 0) {

			cout<<"This letter is NOT in the word"<<endl;
			wrongGuesses+=1;
            cout<<RED;
            for(int i=0; i<wrongGuesses; i++) {
                cout<<gameOver[i];
            }
            cout<<endl<< RESET;
            cout<<"CURRENT: "<<display<<endl;
		}

		found = 0;

		if (count>=4) {
            
            for(int i=0; i<word.length(); i++) {
			    
                if(word==display) {                
                    cout<< YELLOW <<"Congrats! You have won the game!"<< RESET <<endl;
			        return 0;
                }
                
                else continue;
            }
		}

        cout<<"***************************************************************"<<endl;

	}

	cout<< RED << "YOU LOST :("<< RESET<<endl;
    cout<< YELLOW <<"The word was: "<<word<< RESET<<endl;

	return 0;
}
