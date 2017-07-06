#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bIsGameWon; }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";

	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bIsGameWon = false;
	return;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))	//if guess is not an isogram return error
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess))	//if guess is not all lower case return error
	{
		return EGuessStatus::Not_Lower_Case;
	}
	else if (Guess.length() != GetHiddenWordLength())	//if guess length is wrong return error
	{
		return EGuessStatus::Wrong_Length;
	}
	else	//otherwise return ok
	{
		return EGuessStatus::OK;
	}	//TODO make actual error
}

// receives a valid guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();	//assuming same length as guess

	for (int32 i = 0; i < WordLength; i++)	//loop through letters in the guess
	{
		for (int32 j = 0; j < WordLength; j++)	//loop through letters against the hidden word
		{
			if (Guess[i] == MyHiddenWord[j])	//if they match increment bulls if they're in the same place
			{
				if (i == j)		//if they're in the same place
					BullCowCount.Bulls++;	//increment bulls
				else
					BullCowCount.Cows++;	//must be a cow
			}
		}
	}
	if (BullCowCount.Bulls == GetHiddenWordLength())
	{
		bIsGameWon = true;
	}
	else
	{
		bIsGameWon = false;
	}
	return BullCowCount;
}

FString FBullCowGame::PrintGameSummary()
{
	if (bIsGameWon)
	{
		return "CONGRATULATIONS YOU WIN!!";
	}
	else
	{
		return "Better luck next time";
	}
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) return true;
	
	TMap<char, bool> LetterSeen;	//set up our map
	for (auto Letter : Word)	//for all letters of the word
	{
		Letter = tolower(Letter);	//handle mixed case
		
			//if the letter is in the map
				//we do NOT have an isogram
			//otherwise
				//add the letter to the map as seen
		if (LetterSeen[Letter])	//if the letter is in the map
		{
			return false;	//we do NOT have an isogram
		}
		else
		{
			LetterSeen[Letter] = true;	//add the letter to the map as seen
		}
	}

	return true;	//for example in cases where \0 is entered
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	if (Word.length() <= 1) return true;

	for (auto Letter : Word)
	{
		if (!islower(Letter))	//if it's not lowercase
		{
			return false;
		}
	}

	return true;
}
