
#include "FBullCowGame.h"
#include <stdexcpt.h>

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 2;
	const FString HIDDEN_WORD = "gael";
	MyCurrentTry = 1;
	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyGameState = Playing;
	return;
}

bool FBullCowGame::CheckGuessValidity(FText)
{
	return false;
}

FBullCowGame::FBullCowGame()
{
	Reset();
}

GameState FBullCowGame::GetGameState() const
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
	return GetGameState() == Playing;
}

bool FBullCowGame::IsGameWon() const
{
	return false;
}
// TODO this function is doing too much
BullCowCount FBullCowGame::SubmitGuess(FText Guess)
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
		MyGameState = Win;
	}
	else if (MyCurrentTry == MyMaxTries) {
		MyGameState = Lost;
	}
	else {
		MyCurrentTry++;
	}
}

BullCowCount FBullCowGame::CompareWord(FText Guess,FText WordToFind)
{
	BullCowCount Count;
	int32 CurrentGuessPosition = 0;
	// loop through all letters in the guess
	for (char& CharacterInGuess : Guess)
	{
		int32 CurrentHiddenWordPosition = 0;
		// compare letters against the hidden word
		for (char& CharacterInHiddenWord : WordToFind)
		{
			if (tolower(CharacterInHiddenWord) == tolower(CharacterInGuess))
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
