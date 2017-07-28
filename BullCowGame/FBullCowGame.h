#pragma once

#include <string>

using FText = std::string;
using int32 = int;
using FString = std::string;

enum GameState 
{
	Playing,
	Win,
	Lost
};
struct BullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

class FBullCowGame {
public:

	FBullCowGame();

	GameState GetGameState() const;
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	int32 GetNumberOfTriesLeft() const;
	bool  IsPlaying() const;
	bool  IsGameWon() const;
	void Reset(); // TODO make a more rich return value
	bool CheckGuessValidity(FText); // TODO make a more rich return value.
	// provide a methode for counting bulls & cows, and increasing try # assuming the guess is valid
	BullCowCount SubmitGuess(FText);
private:
	// See constructor for init
	int32 MyMaxTries;
	int32 MyCurrentTry;
	FString MyHiddenWord;
	GameState MyGameState;

	// Update the game state according to the number of Bulls and Cows find and the Number of max tries
	void UpdateState(BullCowCount);
	BullCowCount CompareWord(FText,FText);
}; 