#include "fBullCowGame.h"
#include <map>
#define TMap std::map

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3,5},{4,7},{5,16}, {6,21} };
	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

FBullCowGame::FBullCowGame(){ Reset(); }

void FBullCowGame::Reset()
{

	constexpr int32 MAX_LEVEL = 3;
	constexpr int32 STARTING_WORD_LENGTH = 3;

	MaxLevel = MAX_LEVEL;
	MyHiddenWord = GenerateNewWord(STARTING_WORD_LENGTH);
	MyCurrentTry = 1;
	Level = 1;
	bIsGameWon = false;
	return;
}



void FBullCowGame::AdvanceLevel()
{
	//increase level by 1
	Level++;
	//check if game is won
	if (Level > MaxLevel) { 
		bIsGameWon = true; 
	} else { 
		bIsGameWon = false; 
		//set new hidden word that is one character greater then the previous word 
		MyHiddenWord = GenerateNewWord(MyHiddenWord.length() + 1);
		//reset tries
		MyCurrentTry = 1;
	}
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	int32 HiddenWordLength = MyHiddenWord.length();
	return HiddenWordLength;
}
//return level the user is currently on 
int32 FBullCowGame::GetCurrentLevel() const
{

	return Level;
}

bool FBullCowGame::GetIsGameWon() const
{
	return bIsGameWon;
}

EGeussStatus FBullCowGame::CheckCurrentGuessIsValid(FString Guess) const
{
	if (!IsIsogram(Guess)) { //if guess isn't an isogram 
		return EGeussStatus::NOT_Isogram;
	}
	else if (!IsLowercase(Guess)){ //if guess isn't all lowercase 
		return EGeussStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) { //if guess length is wrong 
		return EGeussStatus::Wrong_Length;
	}
	else {
		return EGeussStatus::OK;
	}
}

int32 FBullCowGame::GetMaxLevel() const
{
	return MaxLevel;
}

//recieves a VALID guess, increments turn, and returns count 
fBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	//setup a return variable 
	fBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); //guess must be same length as hidden word
	for (int32 GuessChar = 0; GuessChar < WordLength; GuessChar++) {
		//compare letters agains the hidden word
		for (int32 SolutionChar = 0; SolutionChar < WordLength; SolutionChar++) {
			//if they match
			if (Guess[GuessChar] == MyHiddenWord[SolutionChar]) {
				if (GuessChar == SolutionChar) {
					//increment bulls if in same place 
					BullCowCount.bull++;
				} else {
					//increment cows if not 
					BullCowCount.cow++;
				}
			}
		}
	}
	//advance the level
	if (WordLength == BullCowCount.bull) {
		AdvanceLevel();
	}
		
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	//0 and 1 letter words are isograms 
	if (Guess.length() <= 1) return true;
	TMap<char, bool> LetterSeen; 
	//loop through each of the letters
	for (auto Letter : Guess) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {
			//if one letter has already been added to the map the word is not an isogram 
			return false; 
		} else { 
			//add letter to map if it wansn't already there
			LetterSeen[Letter] = true;
		}
	}
	//if loop ends and no duplicates in has hash table the word is an isogram
	return true;
}

bool FBullCowGame::IsLowercase(FString Guess) const
{
	for (auto Letter : Guess) {
		//if not a lower case letter return false
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}

//return random word for a set wordlength 
FString FBullCowGame::GenerateNewWord(int32 WordLength)
{
	//array of hidden words for the game 
	FString GameWords[3][4];
	GameWords[0][0] = "aim";
	GameWords[0][1] = "ant";
	GameWords[0][2] = "dog";
	GameWords[0][3] = "sag";
	GameWords[1][0] = "corn";
	GameWords[1][1] = "scam";
	GameWords[1][2] = "marc";
	GameWords[1][3] = "said";
	GameWords[2][0] = "amour";
	GameWords[2][1] = "boars";
	GameWords[2][2] = "cigar";
	GameWords[2][3] = "micro";

	//random number from 0 - 3
	int32 random = rand() % 4;
	int32 ArrayindexOffset = 3;
	FString NewWord = GameWords[WordLength - ArrayindexOffset][random];

	return NewWord;
}


