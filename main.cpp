/*
A multi-line comment
*/
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"
#include "main.h"
using int32 = int;
using FText = std::string;

FBullCowGame TheGame;


int32 PrintBack(FText str) 
{
	// repeat guess back to them

	std::cout << "User's guess: " << str << "\n";
	return 0;

}
void PrintGameSummary()
{
	if (TheGame.IsGameWon())
		std::cout << "\nCONGRATULATIONS - YOU WON!\n\n";
	else
		std::cout << "\nBetter luck next time!\n\n";
}
bool isSetTries()
{
	std::cout << "Do you want to set thenumber of tries? (y/n):";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}
void PlayGame()
{
//	int32 NumberofTries = TheGame.GetMaxTries();
	FText Guess;
	TheGame.Reset();

	if (isSetTries()) {
		TheGame.setUDMaxTries(TheGame.RetrieveUDMaxTries());
	}
	while(!TheGame.IsGameWon() && TheGame.GetMyCurrentTry() <= TheGame.GetMaxTries())
	{
		Guess = TheGame.GetValidGuess();//TODO make loop checking for valid guesses

		FBullCowCount BullCowCount = TheGame.SubmitValidGuess(Guess);
		std::cout << "Bulls: " << BullCowCount.Bulls << "\n" << "Cows: " << BullCowCount.Cows<<"\n";

		if (Guess != "")
			PrintBack(Guess);
	}
	// TODO to add
	PrintGameSummary();
	return;
}



bool isPlayAgain() 
{
	std::cout << "Do you want to play again? (y/n):";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}

int main(void) 
{

	FText Guess="";
	TheGame.PrintIntro();
	do
	{
		PlayGame();
	} while (isPlayAgain());
	
	return 0;
}