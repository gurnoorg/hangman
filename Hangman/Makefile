all : play
	
play: hangman.o
	g++ hangman.o -o play

hangman.o: hangman.cpp
	g++ -c hangman.cpp 

clean:
	rm -f play *.o
