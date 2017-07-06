/* This is the console executable that makes use of the BullCow class
This acts as the view in a MVC pattern and is responsible for all user
interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
//FText is for interaction with user
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame;	//instantiate a new game


//the entry point to our app
int main()
{
	bool bPLAY_GAME = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPLAY_GAME = AskToPlayAgain();
	} while (bPLAY_GAME);
	return 0;	//exit
}

void PlayGame()
{
	BCGame.Reset();

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries())
	{
		FText Guess = GetValidGuess();


		//Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls << " | ";
		std::cout << "Cows = " << BullCowCount.Cows << "\n\n";
	}

	//Summarise game
	std::cout << BCGame.PrintGameSummary() << "\n\n";
	return;
}

void PrintIntro()
{
	//introduce the game
	constexpr int32 WORD_LENGTH = 3;
	std::cout << "Welcome to Bulls and Cows\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n\n";
	return;
}

FText GetValidGuess()	//loop continuously until valid guess
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid;
	do
	{
		//get a guess from the player
		std::cout << "Try " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		// check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "That is not an isogram (no repeating letters)\n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Lower_Case:
			std::cout << "Must be lower case\n\n";
			break;
		default:
			return Guess;
		}
	} while (Status != EGuessStatus::OK);
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? ";
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;

	return (Response[0] == 'y' || Response[0] == 'Y');
}
