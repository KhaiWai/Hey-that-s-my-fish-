#ifndef BOARD_H
#define BOARD_H

void printBoard(char board[6][6]);

int updateBoardForInitialMove(int row,int column,char board[6][6]);

int isFirstMoveValid(int row,int column,char board[6][6]);

int charToInt(char c);

void printStats();

int isValidMove(int row, int column,char board[6][6],int newRow, int newColumn);

int isValidDirection(int row, int column,char board[6][6],int newRow, int newColumn);

int isPathValid(int row, int column,char board[6][6],int newRow, int newColumn);

int makePlayerMove(char board[6][6],int newRow, int newColumn);

void printPosition(int row, int col, int newRow, int newCol, char curVal, char newVal);

void makeAIFirstMove(char board[6][6]);

int makeAIMove(char board[6][6]);

int isValidMoveForAI(int row, int column,char board[6][6],int newRow, int newColumn);


#endif