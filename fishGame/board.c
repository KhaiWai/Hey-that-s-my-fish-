#include <stdio.h>
#include "board.h"

int playerRow = 0; 
int playerCol = 0;
int playerPoints = 0;
int aiRow = 0;
int aiCol = 0;
int aiPoints = 0;

void printBoard(char board[6][6]){
    printf("    ");
     for(int col=1;col<7;col++){
         printf("%i ",col);
     }
     printf("\n");
    //  for(int row=1;row<7;row++){
    //      printf("%i \n",row);
    //  }
    for(int i=0;i<6;++i){
        printf(" \n");
        printf("%i   ", i+1);
        for(int j=0;j<6;++j){
            
            printf("%c ",board[i][j]);
        
        }
    }
    printf("\n");    
}



void makeAIFirstMove(char board[6][6]){
    int foundOne = 0;
    for(int i=0;i<6;i++){
        for(int j=0;j<6;j++){
            if(board[i][j]== '1'){
                aiPoints += charToInt(board[i][j]);//update ai points
                board[i][j]='A';//update board for ai
                printBoard(board);
                aiRow = i+1;
                aiCol = j+1;
                foundOne = 1;
                printStats();
                break;
            }                
        }
        if(foundOne)
            break;
    }
}

int isFirstMoveValid(int row,int column,char board[6][6]){
    int isValid=0;
    if(row<1 || row >6 || column<1 || column>6) 
        printf("Invalid row/column detected in first move!\n");
    else{
        isValid = (board[row-1][column-1] == '1');
        //printf("isValid= %i", isValid);
    }
    
    return isValid;
}

void printStats(){
    printf("\nplayer points %i, row %i, col %i.  AI points %i, row %i, col %i\n", playerPoints, playerRow, playerCol, aiPoints, aiRow, aiCol);
}

int charToInt(char c){
    return c - '0';
}

int makePlayerMove(char board[6][6],int newRow, int newColumn){
    int isGameOver = 0;
    if(isValidMove(playerRow,playerCol,board,newRow,newColumn)){
        playerPoints += charToInt(board[newRow-1][newColumn-1]);
        board[newRow-1][newColumn-1]='P';
        board[playerRow-1][playerCol-1]='.';
        printBoard(board);
        playerRow = newRow;
        playerCol = newColumn;
        printStats(); 
        isGameOver = makeAIMove(board);
    }
    return isGameOver;
}

int makeAIMove(char board[6][6]){
    int isGameOver=0;
    int currentMax=0;
    int maxRow=0;
    int maxCol=0;
    for(int i=0;i<6;i++){
        for(int j=0;j<6;j++){
            if(charToInt(board[i][j])>currentMax){
                if(isValidMoveForAI(aiRow,aiCol,board,i+1,j+1)){
                    currentMax=charToInt(board[i][j]);
                    maxRow=i+1;
                    maxCol=j+1;
                }
            }
        }
    }
    if(currentMax==0){
        isGameOver=1;
        printStats();
    }
    else{
        aiPoints += charToInt(board[maxRow-1][maxCol-1]);
        board[maxRow-1][maxCol-1]='A';
        board[aiRow-1][aiCol-1]='.';
        printBoard(board);
        //isValid=1;
        aiRow = maxRow;
        aiCol = maxCol;
        printStats(); 
    }
    return isGameOver;
}

int isValidMoveForAI(int row, int column,char board[6][6],int newRow, int newColumn){
    int isValidMove=0;
    if(newRow<1 || newRow >6 || newColumn<1 || newColumn>6 || (row==newRow && column==newColumn)) {
        //printf("Invalid row/column detected!\n");
    }
    else
    {
        if(isValidDirection(row,column,board,newRow,newColumn)){
            if(isPathValid(row,column,board, newRow, newColumn)){
                isValidMove = 1;
            }else{
                //printf("No path to destination from %i,%i to %i,%i.\n", row, column, newRow, newColumn);
            }
        }else
        {
            //printf("Not Valid Direction from current position %i,%i to new position %i,%i.\n",row,column,newRow,newColumn);
        }
        
    }
    
    return isValidMove;
}

int isValidMove(int row, int column,char board[6][6],int newRow, int newColumn){
    int isValidMove=0;
    if(newRow<1 || newRow >6 || newColumn<1 || newColumn>6 || (row==newRow && column==newColumn)) 
        printf("Invalid row/column detected for player!\n");
    else
    {
        if(isValidDirection(row,column,board,newRow,newColumn)){
            if(isPathValid(row,column,board, newRow, newColumn)){
                isValidMove = 1;
            }else{
                printf("No path to destination from %i,%i to %i,%i.\n", row, column, newRow, newColumn);
            }
        }else
        {
            printf("Not Valid Direction from current position %i,%i to new position %i,%i.\n",row,column,newRow,newColumn);
        }
        
    }
    
    return isValidMove;
}

int isValidDirection(int row, int column,char board[6][6],int newRow, int newColumn){
     
    int isValidDirection =0;

    if(newColumn-column == 0)   // slope is 0.
        isValidDirection =1;
    else if(newRow-row == 0)    // slope is infinity.
        isValidDirection =1;
    else if((newColumn-column)%(newRow-row)==0 && ((newColumn-column)/(newRow-row)== 1 ||(newColumn-column)/(newRow-row)== -1)) //slope is 1 or -1.
        isValidDirection =1;

    return isValidDirection;
}

int isPathValid(int row, int column,char board[6][6],int newRow, int newColumn){
    if (row == newRow){//horizontal move
        if(column > newColumn){// to the left
            for(int i=column-1;i>=newColumn;i--){
                //printPosition(row,column,row,i,board[row-1][column-1],board[row-1][i-1]);
                if(board[row-1][i-1]=='.' || board[row-1][i-1]=='A' || board[row-1][i-1]=='P' )
                    return 0;
            }
        }else if (column < newColumn){//to the right
            for(int i=column+1;i<=newColumn;i++){
                //printPosition(row,column,row,i,board[row-1][column-1],board[row-1][i-1]);
                if(board[row-1][i-1] == '.' || board[row-1][i-1]=='A' || board[row-1][i-1]=='P')
                    return 0;
            }
        }
    }else if(row > newRow){
        if (column == newColumn){//vertical move, to up
            for(int i=row-1;i>=newRow;i--){
                //printPosition(row,column,i,column,board[row-1][column-1],board[i-1][column-1]);
                if(board[i-1][column-1]=='.' || board[i-1][column-1]=='A' || board[i-1][column-1]=='P')
                    return 0;
            }
        }else if(column > newColumn){// diagornal, left, up
            int j=column-1;
            for(int i=row-1;i>=newRow;i--){
                //printPosition(row,column,i,j,board[row-1][column-1],board[i-1][j-1]);
                if(board[i-1][j-1]=='.' || board[i-1][j-1]=='A' || board[i-1][j-1]=='P')
                    return 0;
                j--;
            }
        }else if (column < newColumn){//diagornal, right, up
            int j=column+1;
            for(int i=row-1;i>=newRow;i--){
                //printPosition(row,column,i,j,board[row-1][column-1],board[i-1][j-1]);
                if(board[i-1][j-1]=='.' || board[i-1][j-1]=='A' || board[i-1][j-1]=='P')
                    return 0;
                j++;
            }
        }
    }else if (row < newRow){
       if (column == newColumn){//vertical move, to down
            for(int i=row+1;i<=newRow;i++){
                //printPosition(row,column,i,column,board[row-1][column-1],board[i-1][column-1]);
                if(board[i-1][column-1] == '.' || board[i-1][column-1]=='A' || board[i-1][column-1]=='P')
                    return 0;
            }
        }else if(column > newColumn){// diagornal, left, down
            int i=row+1;
            for(int j=column-1;j>=newColumn;j--){
                //printPosition(row,column,i,j,board[row-1][column-1],board[i-1][j-1]);
                if(board[i-1][j-1]=='.' || board[i-1][j-1]=='A' || board[i-1][j-1]=='P')
                    return 0;
                i++;
            }
        }else if (column < newColumn){//diagornal, right, down
            int i=row+1;
            for(int j=column+1;j<=newColumn;j++){
                //printPosition(row,column,i,j,board[row-1][column-1],board[i-1][j-1]);
                if(board[i-1][j-1]=='.' || board[i-1][j-1]=='A' || board[i-1][j-1]=='P')
                    return 0;
                i++;
            }
        }
    }
    return 1;
}

void printPosition(int row, int col, int newRow, int newCol, char curVal, char newVal){
    printf("cur row %i, cur col %i, new row %i, new col %i, cur val %c, new val %c\n", row, col, newRow, newCol, curVal, newVal);
}

int updateBoardForInitialMove(int row,int column,char board[6][6]){
    playerRow = 0;
    int isValid=0;
    if(isFirstMoveValid(row,column,board) == 1){
        playerPoints += charToInt(board[row-1][column-1]);
        board[row-1][column-1]='P';
        printBoard(board);
        isValid=1;
        playerRow = row;
        playerCol = column;
        printStats();
        makeAIFirstMove(board);
    }
    else{
        printf("Invalid first move! Choose Again!\n");
    }
   
    return isValid;
}