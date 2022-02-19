// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{    
     Super::BeginPlay();

     Isograms = GetVaildWords(HiddenWords);

     SetupGame();

     PrintLine(TEXT("The number of possible vaild words is: %i"), Isograms.Num());   
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
     if(bGameOver)
     {
          ClearScreen();
          SetupGame();
     }
     else // checking PlayerGuess
     {
          ProcessGuess(PlayerInput);
     }    
}

void UBullCowCartridge::SetupGame()
{

     //Welcome player
     PrintLine(TEXT("Welcome to this game of words."));
     PrintLine(TEXT("Press tab to being.\nHit enter when done."));

     HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
     Lives = HiddenWord.Len() *2;
     bGameOver = false;

     PrintLine(TEXT("Guess a %i letter word.\nYou have %i lives left."), HiddenWord.Len(), Lives);//Prompt player for guess
     PrintLine(TEXT("The HiddenWord is %s."), *HiddenWord); // Debug Line 
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
     if(Guess == HiddenWord) // checks player guess
     {
          ClearScreen();
          PrintLine(TEXT("You have guessed the right word!"));
          EndGame();
          return; // returns if you win game
     }
     if (Guess.Len() != HiddenWord.Len()) // checks if len of guess is len of hiddenword
     {   
          PrintLine(TEXT("You entered a %i letter word.\nHidden word is %i letters.\nYou still have %i lives left."), Guess.Len(), HiddenWord.Len(), Lives);
          return; // returns with hints
     } 
     if(!IsIsogram(Guess))
     {
          PrintLine(TEXT("No repeating letters, guess again!"));
          return;
     }

     // int32 Bulls, Cows; When like initailized and then used right after is OUT PARAMATERS
     FBullCowCount Score = GetBullCows(Guess);

     PrintLine(TEXT("You have %i Bulls, and %i Cows"), Score.Bulls, Score.Cows);

     PrintLine(TEXT("You have lost a life.\nYou have %i lives left."), --Lives); // lose life if wrong guess

     if(Lives <= 0) // checks to see if lives are zero to endgame
     {
          ClearScreen();
          PrintLine(TEXT("You have no lives left!"));
          PrintLine(TEXT("\nThe hidden word was: %s."), *HiddenWord);
          EndGame();
          return;
     }
}

void UBullCowCartridge::EndGame()
{
     bGameOver = true;
     PrintLine(TEXT("Press enter to play again."));
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
     for (int32 Index = 0; Index < Word.Len(); Index++)
     {
          for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
          {
               if (Word[Index] == Word[Comparison])
               {
                    return false;
               }
          }
     }

     return true;
}

TArray<FString> UBullCowCartridge::GetVaildWords(const TArray<FString>& WordList) const
{
     TArray<FString> VaildWords;

     for (FString Word : WordList)
     {
          if (Word.Len() >= 4 && Word.Len() <= 8 
          && IsIsogram(Word))
          {
               VaildWords.Emplace(Word); 
          }    
     }
     return VaildWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
     FBullCowCount Count;

     for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
     {
          if(Guess[GuessIndex] == HiddenWord[GuessIndex])
          {
               Count.Bulls++;
               continue;
          }
          for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
          {
               if(Guess[GuessIndex] == HiddenWord[HiddenIndex])
               {
                    Count.Cows++;
                    break;
               }
          }   
     }
     return Count;
}