#include <iostream>
#include <string>
#include "BullCowGame\FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
FText GetGuess();
void PlayGame();
bool AskToPlayAgain();
void PrintGuessResult(BullCowCount);
void SummariseTheGame();

FBullCowGame BCGame;

int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		BCGame.Reset();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);
	return 0;
}

void PlayGame()
{
	int32 MaxTries = BCGame.GetMaxTries();
	while (BCGame.IsPlaying())
	{
		BullCowCount  GuessResult = BCGame.SubmitGuess( GetGuess() );

		PrintGuessResult(GuessResult);

		SummariseTheGame();
	}
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
	std::cout << "Do you want to play again ? ";
	FText Response = "";

	getline(std::cin, Response);

	return (tolower(Response[0]) == 'y');
}

void PrintGuessResult(BullCowCount GuessResult)
{
	std::cout << "Cows : " << GuessResult.Cows << " Bulls: " << GuessResult.Bulls;
	std::cout << std::endl;
}


void SummariseTheGame()
{
	switch ( BCGame.GetGameState() ) {
		case Win:
			std::cout << "You win !";
			break;
		case Lost:
			std::cout << "You lose ! ";
			break;
		default:
			if (BCGame.GetNumberOfTriesLeft() == 1)
			{
				std::cout << "it's the last attempt !";
			}
			else {
				std::cout << BCGame.GetNumberOfTriesLeft() << " attempts left !";
			}
			
	}
	std::cout << std::endl;
}
