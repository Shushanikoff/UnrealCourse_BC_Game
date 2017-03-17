#pragma once
#include "FBullCowGame.h"
TMap <char, bool> LetterSeen;
FBullCowGame::FBullCowGame(){	Reset();}

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";

	MyCurrentTry = 1;
	UDMaxTries = 0;
	myHiddenWord = HIDDEN_WORD;
	bGameWon = false;
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLength2MaxTries{ {3,4},{4,7},{5,10},{6,15},{7,19} };
	if (getUDMaxTries() > 0)
		return getUDMaxTries();
	else
		return WordLength2MaxTries[myHiddenWord.length()];
}


int32 FBullCowGame::PrintIntro()
{
	// introduce a game
	std::cout << "\n\nWelcome to Bulls and Cows!" << std::endl;
	std::cout << "Can You guess the " << GetHiddenWordlength() << " letter isogram I'm thinking of?\n";

	return 1;
}

FText FBullCowGame::GetValidGuess()// TODO: change to get valid guess
{
FText str;

	EGuessStatus Status = EGuessStatus::InvalidStatus;
	do 
	{

	std::cout << "Try " << MyCurrentTry << " of "<< GetMaxTries() << ". Enter Your guess: ";

	// get user's input
	std::getline(std::cin, str);

	Status = isGuessValid(str);
	switch (Status)
	{
	case EGuessStatus::NotIsogram:
		std::cout << "Please enter an isogram " << GetHiddenWordlength() << "  \n\n";
		break;
	case EGuessStatus::WrongLength:
		std::cout << "Please enter a " << GetHiddenWordlength() << " letter word! \n\n";
		break;
	case EGuessStatus::NotLowerCase:
		std::cout << "Please enter a word in lowercase!\n\n";
		break;
	default:
		// assuming the guess is valid
		break;

	}
	} while (Status != EGuessStatus::OK);// keep looping until we get valid guess

	return str;
}

int32 FBullCowGame::GetMyCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::SetMyCurrentTry(int32 n)
{
	MyCurrentTry = n;
	return 0;
}


int32 FBullCowGame::GetHiddenWordlength() const
{
	return int32(myHiddenWord.length());
}

void FBullCowGame::setUDMaxTries(int32 ntries)
{
	UDMaxTries = ntries;
}

int32 FBullCowGame::getUDMaxTries() const
{
	return UDMaxTries;
}

int32 FBullCowGame::RetrieveUDMaxTries()
{
	FString str;
	int32 ntries;
	do {
		std::cout << "\n Enter the number of tries:";
		std::getline(std::cin, str);
		ntries = atoi(str.c_str());
	} while (ntries <= 0);
	return ntries;
}

bool FBullCowGame::IsGameWon() const
{
	return bGameWon;
}

EGuessStatus FBullCowGame::isGuessValid(FText str)
{

	//if guess isn't an isogram
	if (!isIsogram(str)) {
		return EGuessStatus::NotIsogram;
	}
	else if (str.length() != GetHiddenWordlength())	//if wrong  wordlength
	{
		return EGuessStatus::WrongLength;
	}
	else if (!isLowerCase(str))	//if not lowercase
	{
		return EGuessStatus::NotLowerCase;
	}
	else
	{
		return EGuessStatus::OK; // TODO add actual error

	}

}
// receives a valid guess, increments turns and counts bulls and cows
FBullCowCount FBullCowGame::SubmitValidGuess(FText guess)
{
	MyCurrentTry++;
		//setup a return value
	FBullCowCount bullCowCount;
	// loop through all letters
	int32 HiddenWordLength = myHiddenWord.length();
	int32 GuessLength = guess.length();
	for (int32 i = 0; i < GuessLength; i++)
	{
		for (int32 j = 0; j < HiddenWordLength; j++)
		{
			if (guess[i] == myHiddenWord[j]) {
				if (i == j) bullCowCount.Bulls++;
				else
					bullCowCount.Cows++;
			}
		}
	}
	if (bullCowCount.Bulls == myHiddenWord.length())
		bGameWon = true;
	else
		bGameWon = false;
	return bullCowCount;
}

bool FBullCowGame::isIsogram(FText str) const
{
	if (str.length() < 2) return true;

	LetterSeen.clear();
	char l;
//	for (int i = 0; i < str.length(); i++) 
	for(auto l : str)
	{
	//	l = tolower(str[i]);
		l = tolower(l);
		if (!LetterSeen[l])
			LetterSeen[l] = true;
		else
			return false;
	}

	return true;
}

bool FBullCowGame::isLowerCase(FText str) const
{
	if (str.length() < 1)
		return true;
	for (auto l : str) 
	{
		if (!islower(l)) 
			return false;
	}

	return true;
}
