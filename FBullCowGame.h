/*
The game logic class
*/
#pragma once
#include <string>
#include <iostream>
#include <map>
#define TMap std::map 

using int32 = int;
constexpr int32 WORD_LENGTH = 5;
using FText = std::string;
using FString = std::string;


enum EGuessStatus 
{
	InvalidStatus,
	OK,
	NotIsogram,
	WrongLength,
	NotLowerCase

};
struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};
class FBullCowGame
{
public:
	FBullCowGame();
	//~FBullCowGame();
	void Reset();// TODO make a more rich return value
	int32 GetMaxTries() const;
	int32 PrintIntro();
	FText GetValidGuess();
	int32 GetMyCurrentTry() const;
	int32 SetMyCurrentTry(int32 n);
	int32 GetHiddenWordlength() const;
	void setUDMaxTries(int32 ntries);
	int32 getUDMaxTries() const;
	int32 RetrieveUDMaxTries();
	bool IsGameWon() const;
	EGuessStatus isGuessValid(FText str);
	FBullCowCount SubmitValidGuess(FText);
private:
	int32 MyCurrentTry;
//	int32 MyMaxTries;
	FString myHiddenWord;
	int32 UDMaxTries;
	bool bGameWon;
	bool isIsogram(FText str) const;
	bool isLowerCase(FText str) const;

};
