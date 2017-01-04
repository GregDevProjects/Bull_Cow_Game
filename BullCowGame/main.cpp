/* This is the console executable that makes use of the BullCow class 
This acts as the view in a MVC pattern, and is responible for all user interaction.
For game logic sese the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "fBullCowGame.h"

//make syntax unreal friendly
using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary(bool);

//instantiate a new game - this is reused across plays
FBullCowGame BCGame; 

int main() {
	do {
		PrintIntro();
		PlayGame();
		//TODO add a game summary
	} while (AskToPlayAgain());
	return 0; //exit application
}

void PrintIntro() {
	std::cout << " __________      .__  .__    _________                  \n";
		std::cout << " \\______   \\__ __|  | |  |   \\_   ___ \\  ______  _  __  \n";
		std::cout << "  |    |  _/  |  \\  | |  |   /    \\  \\/ /  _ \\ \\/ \\/ /  \n";
		std::cout << "  |    |   \\  |  /  |_|  |__ \\     \\___(  <_> )     /   \n";
		std::cout << "  |______  /____/|____/____/  \\______  /\\____/ \\/\\_/    \n";
		std::cout << "         \\/                          \\/                 \n";
		std::cout << "   (___)		                            ___		      \n";
		std::cout << "   (o o)_____/                           (o o)_____/    \n";
		std::cout << "    @@ `     \\                            @@ `     \\    \n";
		std::cout << "     \\ ____, /                             \\ ____, /    \n";
		std::cout << "     //    //                              //    //     \n";
		std::cout << "    ^^    ^^                              ^^    ^^      \n\n";
		std::cout << "---------------Welcome to Bulls and Cows-------------\n"; 
		std::cout << "-----Now with " << BCGame.GetMaxLevel() << " levels of word guessing goodness!-----\n";
		std::cout << "-Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?-\n";
}

//loops the game until completion 
void PlayGame(){
	BCGame.Reset();
	//loop for number of turns asking for guessess while guesses remain 
	//and game is NOT won 
	while(!BCGame.GetIsGameWon() && (BCGame.GetCurrentTry() <= BCGame.GetMaxTries())){
		
		FText Guess = GetValidGuess();
		//Submit valid guess to game
		int32 LevelBeforeGuess = BCGame.GetCurrentLevel();
		fBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "You guessed: " << Guess << std::endl;
		std::cout << "Bulls: " << BullCowCount.bull << std::endl;
		std::cout << "Cows: " << BullCowCount.cow << std::endl;
		//show current level after user guesses correct word
		int32 LevelAfterGuess = BCGame.GetCurrentLevel();
		if (LevelBeforeGuess < LevelAfterGuess && LevelBeforeGuess < BCGame.GetMaxLevel()) {
			std::cout << "\n ----------Level" << BCGame.GetCurrentLevel() << "----------- \n";
		}
	}

	PrintGameSummary(BCGame.GetIsGameWon());
}


//keep asking in loop until user gives valid guess
FText GetValidGuess() {
	EGeussStatus Status = EGeussStatus::Invalid_Status;
	FText Guess = "";
	do {	
		std::cout << "\nTry " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() << ". ";
		std::cout << "Please guess a word" << std::endl;
		std::getline(std::cin, Guess);
		Status = BCGame.CheckCurrentGuessIsValid(Guess);
		switch (Status) {
			case EGeussStatus::Wrong_Length:
				std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.";
				break;
			case EGeussStatus::NOT_Isogram:
				std::cout << "Please enter an isogram (a word without a repeating letter)";
				break;
			case EGeussStatus::Not_Lowercase:
				std::cout << "Please type your response in lowercase letters";
				break;
			default:
				//assume user input is valid
				break;
		}
		std::cout << std::endl;
	} while (Status != EGeussStatus::OK); //keep looping 

	return Guess;
}


bool AskToPlayAgain() {
	std::cout << "Do you want to play again? (y/n)";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary(bool bGameIsWon) {
	std::cout << "\n \n";
	if (bGameIsWon) {
		std::cout << " __      _______ _____ _______ ____  _______     __  \n";
		std::cout << " \\ \\    / /_   _/ ____|__   __/ __ \\|  __ \\ \\   / /  \n";
		std::cout << "  \\ \\  / /  | || |       | | | |  | | |__) \\ \\_/ /   \n";
		std::cout << "   \\ \\/ /   | || |       | | | |  | |  _  / \\   /    \n";
		std::cout << "    \\  /   _| || |____   | | | |__| | | \\ \\  | |     \n";
		std::cout << "     \\/   |_____\\_____|  |_|  \\____/|_|  \\_\\ |_|     \n";
	} else {
		std::cout << "  ____ _____ _____     ______      _____ _       \n";
		std::cout << " |  _ \\_   _/ ____|   |  ____/\\   |_   _| |      \n";
		std::cout << " | |_) || || |  __    | |__ /  \\    | | | |      \n";
		std::cout << " |  _ < | || | |_ |   |  __/ /\\ \\   | | | |      \n";
		std::cout << " | |_) || || |__| |   | | / ____ \\ _| |_| |____  \n";
		std::cout << " |____/_____\\_____|   |_|/_/    \\_\\_____|______| \n";
	}
	std::cout << "\n \n";
	return;
}
