# Hey-that-s-my-fish-

A simplied version of "Hey, that's my fish!" board game, written in C. (In class project)

* 6x6 random board containing numbers 1, 2 and 3.
* Player and AI can only start from 1. 
* After each move, there will be a display of the point accorind to the number and the current position of each player.
* Player and AI can go to higher points in all horizontal, vertical and diagonal directions from the next move.
* The position that has been visited will be placed with a '.'.
* If there is a single or more '.' in the way of the direction, player or AI cannot move to the desired direction.
* The game ends when one of the players end up not being able to move to any direction and the one with the highter points will win.

User  input read as an int and put in the parameters of the functions.
There are 14 functions altogether including the main function. 
To check if the player and AI move in a valid direction, I used the slope formula to go only straight. (For Valid Direction)
To check if the new moving point the player chose is valid, I checked in every possible point during the path if they are free of ‘.’, ‘A’ or ‘P’. That is checking the blocks that are not previously or currently occupied.
For AI, I initially located it at the first available 1 on the board. And for the next moves, AI check in the board by traversing one by one and look for the maximum possible number it can get. 
At the end of the game, the program shows who win, lose or draw by showing the total points of both player and AI. 
