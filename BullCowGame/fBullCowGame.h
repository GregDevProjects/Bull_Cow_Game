/* Handles game logic for guessing words 
User interaction is handled in main.cpp
*/

#pragma once
#include <iostream>
#include <string>

using FString = std::string;
using int32 = int;

struct fBullCowCount{
	int32 bull = 0;
	int32 cow = 0;
};

enum class EGeussStatus {
	Invalid_Status,
	OK,
	NOT_Isogram,
	Wrong_Length,
	Not_Lowercase
};

enum class EResetStatus {
	No_Hidden_Word,
	OK
};

class FBullCowGame {
public:
	FBullCowGame(); //constructor
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	int32 GetCurrentLevel() const;
	bool GetIsGameWon() const;
	EGeussStatus CheckCurrentGuessIsValid(FString) const; 
	int32 GetMaxLevel() const;

	void Reset(); 
	void AdvanceLevel();
	fBullCowCount SubmitValidGuess(FString); //counts bulls and cows and incresing try number. Assuming valid guess
private:
	int32 MyCurrentTry;
	FString  MyHiddenWord;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	bool bIsGameWon;
	int32 Level;
	int32 MaxLevel; //when current level is  greater than MaxLevel the game is won 
	FString GenerateNewWord(int32);
};