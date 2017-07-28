#include <iostream>
#include <string>
#include "BullCowGame\FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
FText GetGuess();
void PlayGame();
bool AskToPlayAgain();

FBullCowGame BCGame;

int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);
	return 0;
}

void PlayGame()
{
	int32 MaxTries = BCGame.GetMaxTries();
	// Loop for the number of turn asking for guesses
	// TODO Change from FOR to WHILE loop once we are validating tries
	while (BCGame.GetGameState() == Playing)
	{
		FText Guess = "";
		Guess = GetGuess();

		// submit valid guess to the game
		BullCowCount  GuessResult = BCGame.SubmitGuess(Guess);
		// print number of bulls and cows
		std::cout << "Cows : " << GuessResult.Cows << " Bulls: " << GuessResult.Bulls;
		std::cout << std::endl;

		//Print the guess back
		std::cout << "Your guess was: " << Guess;
		std::cout << std::endl;

		if (BCGame.GetGameState() == Win)
		{
			std::cout << "You win. \n";
		}
	}

	// TODO Summarise game
}

void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game. \n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of ?\n";
	return;
}

FText GetGuess()
{
	int32 CurrentTry = BCGame.GetCurrentTry();
	FText Guess = "";
	std::cout << "Try " << CurrentTry << " Enter your guess: ";
	getline(std::cin, Guess);
	return Guess;
}


bool AskToPlayAgain()
{
	BCGame.Reset();

	std::cout << "Do you want to play again ? ";
	FText Response = "";

	getline(std::cin, Response);

	return (tolower(Response[0]) == 'y');
}