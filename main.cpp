#include <iostream>
#include <string>
#include "BullCowGame\FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
FText GetValidGuessFromUserInput();
void PlayGame();
bool AskToPlayAgain();
void PrintGuessResult(BullCowCount);
void SummariseTheGame();
void PrintReadbleErrorIfAny(EGuessStatus);

// TODO remove global BCGame use dependency injection pattern
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

// TODO remove global BCGame
void PlayGame()
{
	while (BCGame.IsPlaying())
	{
		FText Guess = GetValidGuessFromUserInput();
		BullCowCount  GuessResult = BCGame.SubmitValidGuess( Guess );

		PrintGuessResult(GuessResult);

		SummariseTheGame();
	}
}

// TODO remove global BCGame
void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game. \n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of ?\n";
	return;
}

// TODO remove global BCGame
FText GetValidGuessFromUserInput()
{
	EGuessStatus GuessStatus = EGuessStatus::Invalid;
	FText Guess = "";
	std::cout << "Try " << BCGame.GetCurrentTry() << " Enter your guess: ";
	do {
		getline(std::cin, Guess);
		GuessStatus = BCGame.CheckGuessValidity(Guess);
		PrintReadbleErrorIfAny(GuessStatus);
	} while (GuessStatus != EGuessStatus::OK);

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
	std::cout << std::endl;
}

// TODO remove global BCGame
void SummariseTheGame()
{
	switch ( BCGame.GetGameState() ) {
		case EGameState::Win:
			std::cout << "You win !";
			break;
		case EGameState::Lost:
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
	std::cout << std::endl;
}

// TODO remove global BCGame
void PrintReadbleErrorIfAny(EGuessStatus Status)
{

	switch (Status)
	{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n";
			break;
		case EGuessStatus::Wrong_length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		default:
			break;
	}
	std::cout << std::endl;
}
