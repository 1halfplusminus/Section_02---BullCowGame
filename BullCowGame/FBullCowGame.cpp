
#include "FBullCowGame.h"
#include <stdexcpt.h>
#include <map>
#define TMap std::map

void FBullCowGame::Reset()
{
	// TODO put const in main
	constexpr int32 MAX_TRIES = 5;
	const FString HIDDEN_WORD = "gael";
	MyCurrentTry = 1;
	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
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
	return MyMaxTries;
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
	else if (MyCurrentTry == MyMaxTries) {
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