# UnrealWithCPP
Using Unreal Engine with C++ for game development in free time.

Game Overview: 
The game selects a random hidden word (an isogram—a word without repeating letters) from a list, and the player must guess the word within a limited number of attempts.

Gameplay Mechanics:
The game starts by selecting a random isogram word (length 4-8 letters) from a predefined list.

The player is prompted to guess a word of the same length.

After each guess:

If the guess matches the hidden word, the player wins.

If the word is not the same length as the hidden word, the game provides feedback.

If the word is not an isogram (contains repeating letters), the player is warned.

The game calculates Bulls and Cows:

Bulls = Correct letters in the correct position

Cows = Correct letters in the wrong position

The player loses a life if their guess is incorrect.

The game continues until the player runs out of lives or guesses the word correctly.

Game Loop:
Start Game – Set up the game and select a word.

Player Inputs a Guess – The game processes the guess.

Feedback Given:

If correct → Win and restart option

If incorrect → Lose a life and provide feedback

Game Ends:

If lives reach 0, the game reveals the word.

If the player wins, they can restart.

Key Features in the Code:
✔ Random word selection from a list of valid isograms.
✔ Lives system (2x the length of the hidden word).
✔ Input validation (checks if input is an isogram and correct length).
✔ Bulls and Cows scoring system to provide hints.
✔ Restart system once the game is over.

