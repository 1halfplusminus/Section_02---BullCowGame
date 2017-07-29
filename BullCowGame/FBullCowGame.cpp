#pragma once

#include "FBullCowGame.h"
#include <stdexcpt.h>
#include <map>
#include <array>
#include <random>
// to make syntaxe Unreal friendly
#define TMap std::map
#define TArray std::array
using int32 = int;

std::default_random_engine eng;

void FBullCowGame::Reset()
{
	// TODO read hidden word from file or web api
	TArray<FText, 3> ListOfWords = { "planet","pick","top" }; // this must be a isogram
	std::uniform_int_distribution<int> dist(0, ListOfWords.size() - 1);
	
	int RandomIndex = dist(eng);

	MyCurrentTry = 1;
	MyHiddenWord = ListOfWords[RandomIndex];
	MyGameState = EGameState::Playing;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FText Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if(!IsLengthValid(Guess)) 
	{
		return EGuessStatus::Wrong_length;
	}
	else 
	{
		return EGuessStatus::OK;
	}
}

FBullCowGame::FBullCowGame()
{
	Reset();
}

EGameState FBullCowGame::GetGameState() const
{
	return MyGameState;
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,4},{4,7},{5,10},{6,16},{7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

int32 FBullCowGame::GetNumberOfTriesLeft() const
{
	return GetMaxTries() - (GetCurrentTry() - 1);
}

bool FBullCowGame::IsPlaying() const
{
	return GetGameState() == EGameState::Playing;
}

bool FBullCowGame::IsGameWon() const
{
	return GetGameState() == EGameState::Win;
}
// TODO this function is doing too much
BullCowCount FBullCowGame::SubmitValidGuess(FText Guess)
{
	//Compare the guess word to the hidden word
	BullCowCount ComparaisonResult = CompareWord(Guess,MyHiddenWord);
	//Update the game state depending of the result
	UpdateState(ComparaisonResult);

	return ComparaisonResult;
}

void FBullCowGame::UpdateState(BullCowCount BullCowCount)
{
	if (BullCowCount.Bulls == GetHiddenWordLength())
	{
		MyGameState = EGameState::Win;
	}
	else if (MyCurrentTry == GetMaxTries()) {
		MyGameState = EGameState::Lost;
	}
	else {
		MyCurrentTry++;
	}
}

bool FBullCowGame::IsIsogram(FText Word) const
{
	bool IsIsogram = true;
	TMap<char, bool> LetterFound;
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		if (LetterFound[Letter])
		{
			IsIsogram = false;
			break;
		}
		else 
		{
			LetterFound[Letter] = true;
		}

	}
	return IsIsogram;
}

bool FBullCowGame::IsLengthValid(FText Word) const
{
	return Word.length() == MyHiddenWord.length();
}

BullCowCount FBullCowGame::CompareWord(FText Guess,FText WordToFind)
{
	BullCowCount Count;
	int32 CurrentGuessPosition = 0;
	// loop through all letters in the guess
	for (char& LetterInGuess : Guess)
	{
		int32 CurrentHiddenWordPosition = 0;
		// compare letters against the hidden word
		for (char& LetterInHiddenWord : WordToFind)
		{
			if (tolower(LetterInHiddenWord) == tolower(LetterInGuess))
			{
				// incriment bulls if they're in the same place
				if (CurrentGuessPosition == CurrentHiddenWordPosition)
				{
					Count.Bulls++;
				}
				// increment cows if not
				else
				{
					Count.Cows++;
				}
				break;
			}
			CurrentHiddenWordPosition++;
		}
		CurrentGuessPosition++;
	}
	return Count;
}