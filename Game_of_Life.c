/*
Task allocation:
Josh: menu, binaryToDecimal, Allow the user to select, or create, the first generation,
        saving the output of your program to a text file on disk, 
        

Luke: DecimalToBinary, 
        base code, 
        Allow the user to select different lengths of the first generation, and to select different numbers of generations to produce. 
        other rules than 30

Fergus: 
        Loading saved files, 
        Write your automata out to a text file so that you can look at the results once the program has completed. 
        Wrap the ends of your automata array around so that the right-hand end continues onto the left-hand end and vice-versa.

*/

#define Width  10
#define Height 10

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<string.h>
#include <time.h>
#include <unistd.h>

int checkRules();
int binaryToInteger();
int customParent();
int saveOutput();
void printArray();
void customGen();
void chooseParentSize();

// if the cell is on the right then check the cell on the left
int indexRight(int index, int generationSize){
    if(index == generationSize-1){
        return 0;
    }
     else{
        return index+1;
    }
}

// if the cell is on the left, check the cell all the way on the right 
int indexLeft(int index, int generationSize){
    if(index == 0){
        return generationSize-1;
    }
    else{
        return index-1;
    }
}

// a function to do the game of life
void gameOfLife(){
    int board[Width][Height];
    int ri = (rand() % 100); 
    // make a new board that is populated with 25% red and 75% green randomly
    for (int i = 0; i < Width; i++)             //if i is less than the board width then add to i
    {                                   
        for (int j = 0; j < Height; j++)        //if j is less than the board height then add to j
        {
            if (ri>75){
                board[i][j] = 1;
            }
            else{
                board[i][j] = 0;
            }
            // make a new random number
            ri = (rand() % 100); 
            printf("\033[0;32m"); // make the board green
            printf("%d ", board[i][j] );//? '0':'1'); // print board
            printf("\033[0m");    //remove colour
        }
        printf("\n");                            
    }    
    printf("\n"); 
    printf("\n");    

    // for 100 generations, check each cell and populate it with the required colour
    for(int c = 0; c < 101; c++){
        int nextBoard[Width][Height];
        int cellCount;
        for (int x = 0; x < Width; x++) for (int y = 0; y < Height; y++) 
        {
            // if the cell is in the top left, loop around to check the cells on the other side of the board
            cellCount = 0;
            if(x==0 && y==0){
                if (board[Width-1][0] == 1) cellCount++;
                if (board[x][0]== 1) cellCount++;
                if (board[x+1][0]== 1) cellCount++;
                if (board[x+1][y]== 1) cellCount++;
                if (board[x+1][y+1]== 1) cellCount++;
                if (board[x][y+1]== 1) cellCount++;
                if (board[Width-1][y+1]== 1) cellCount++;
                if (board[Width-1][y]== 1) cellCount++;
            }
            // if the cell is in the top right, loop around to check the cells on the other side of the board
            else if(x==Width-1 && y==0){
                if (board[x-1][0]== 1) cellCount++;
                if (board[x][0]== 1) cellCount++;
                if (board[0][0]== 1) cellCount++;
                if (board[0][y]== 1) cellCount++;
                if (board[0][y+1]== 1) cellCount++;
                if (board[x][y+1]== 1) cellCount++;
                if (board[0][y+1]== 1) cellCount++;
                if (board[0][y]== 1) cellCount++;
            }
            // if the cell is in the bottom left, loop around to check the cells on the other side of the board
            else if(x==0 && y==Height-1){
                if (board[Width-1][y-1]== 1) cellCount++;
                if (board[x][y-1]== 1) cellCount++;
                if (board[x+1][y-1]== 1) cellCount++;
                if (board[x+1][y]== 1) cellCount++;
                if (board[x+1][0]== 1) cellCount++;
                if (board[x][0]== 1) cellCount++;
                if (board[Width-1][0]== 1) cellCount++;
                if (board[Width-1][y]== 1) cellCount++;

            }
            // if the cell is in the bottom right, loop around to check the cells on the other side of the board
            else if(x==Width-1 && y==Height-1){
                if (board[x-1][y-1]== 1) cellCount++;
                if (board[x][y-1]== 1) cellCount++;
                if (board[0][y-1]== 1) cellCount++;
                if (board[0][y]== 1) cellCount++;
                if (board[0][0]== 1) cellCount++;
                if (board[x][0]== 1) cellCount++;
                if (board[x-1][0]== 1) cellCount++;
                if (board[x-1][y]== 1) cellCount++;
            }

            // if the cell is on the left loop around to check the cells on the other side of the board
            else if(x==0){
                
                if (board[Width-1][y-1]== 1) cellCount++;
                if (board[x][y-1]== 1) cellCount++;
                if (board[x+1][y-1]== 1) cellCount++;
                if (board[x+1][y]== 1) cellCount++;
                if (board[x+1][y+1]== 1) cellCount++;
                if (board[x][y+1]== 1) cellCount++;
                if (board[Width-1][y+1]== 1) cellCount++;
                if (board[Width-1][y]== 1) cellCount++;
            }
            // if the cell is on the top loop around to check the cells on the other side of the board
            else if(y==0){
                
                if (board[x-1][Height-1]== 1) cellCount++;
                if (board[x][Height-1]== 1) cellCount++;
                if (board[x+1][Height-1]== 1) cellCount++;
                if (board[x+1][y]== 1) cellCount++;
                if (board[x+1][y+1]== 1) cellCount++;
                if (board[x][y+1]== 1) cellCount++;
                if (board[x-1][y+1]== 1) cellCount++;
                if (board[x-1][y]== 1) cellCount++;
            }

            // if the cell is on the right loop around to check the cells on the other side of the board
            else if(x==Width-1){
                
                if (board[x-1][y-1]== 1) cellCount++;
                if (board[x][y-1]== 1) cellCount++;
                if (board[0][y-1]== 1) cellCount++;
                if (board[0][y]== 1) cellCount++;
                if (board[0][y+1]== 1) cellCount++;
                if (board[x][y+1]== 1) cellCount++;
                if (board[0][y+1]== 1) cellCount++;
                if (board[0][y]== 1) cellCount++;
            }
            // if the cell is on the bottom loop around to check the cells on the other side of the board
            else if(y==Height-1){
                
                if (board[x-1][y-1]== 1) cellCount++;
                if (board[x][y-1]== 1) cellCount++;
                if (board[x+1][y-1]== 1) cellCount++;
                if (board[x+1][y]== 1) cellCount++;
                if (board[x+1][0]== 1) cellCount++;
                if (board[x][0]== 1) cellCount++;
                if (board[x-1][0]== 1) cellCount++;
                if (board[x-1][y]== 1) cellCount++;
            }

            // If it's in the middle, check the cells around i t
            else{
                if (board[x-1][y-1]== 1) cellCount++;
                if (board[x][y-1]== 1) cellCount++;
                if (board[x+1][y-1]== 1) cellCount++;
                if (board[x+1][y]== 1) cellCount++;
                if (board[x+1][y+1]== 1) cellCount++;
                if (board[x][y+1]== 1) cellCount++;
                if (board[x-1][y+1]== 1) cellCount++;
                if (board[x-1][y]== 1) cellCount++;
            }

            // if the cell count is under 2, the cell dies of underpopulation
            if (cellCount < 2)
            {
                nextBoard[x][y] = 0;
            } 
            // if the cell count is over 3, the cell dies of overpopulation
            else if (cellCount > 3)
            {
                nextBoard[x][y] = 0;
            }
            // if the cell count is 2 or 3, the cell lives
            else if (cellCount == 2 || cellCount == 3)
            {
                nextBoard[x][y] = 1;
            }
            else if (board[x][y] == 0 && cellCount == 3)
            {
                nextBoard[x][y] = 1 ;       
            }
        }
        //memcpy(board, nextBoard, sizeof(nextBoard));
        for (int a = 0; a < Width; a++)             //if i is less than the board width then add to i
        {                                   
            for (int b = 0; b < Height; b++)        //if j is less than the board height then add to j
            {
                board[a][b] = nextBoard[a][b];
            }
        }

        for (int a = 0; a < Width; a++)             //if i is less than the board width then add to i
        {                                   
            for (int b = 0; b < Height; b++)        //if j is less than the board height then add to j
            {
                if(nextBoard[a][b] == 1){
                    printf("\033[0;32m");
                    printf("%d ", nextBoard[a][b] );
                    printf("\033[0m");
                }
                else{
                    printf("\033[0;31m"); // make the board green
                    printf("%d ", nextBoard[a][b] );//? '0':'1'); // print board
                    printf("\033[0m");
                }
            }
            printf("\n");   
        }
        printf("\n");   
        printf("\n");   
        sleep(1);  
        system("clear");
    }     
}

// validates the binary input
bool validateBinaryInput(int input){
    // if the input isn't 1 or 0, ask the user for the answer again
    while (input != 1 && input != 0){
        printf("Please enter a valid input\n");
        scanf("%d", &input);
    }
    // Otherwise, return true or false depending on the answer
    if(input == 1){
        return true;
    }
    else{
        return false;
    }
}

// allows the user to add custom rules
void chooseCustomRule(int *ruleArray){
    // for the 8 items in the array, ask for a one or a 0
    for(int i=0; i<8; i++){
        int input;
        printf("[%d] Please enter a '1' or '0' to add your custom rule \n", i+1);
        scanf("%d", &input); 
        if (input==0 || input==1){
            ruleArray[i] = input;
        }
        else{
            printf("Invalid input please wite '1' or '0' \n");
            i--;
        }
    }
}

// allows the user to make the parent generation
void chooseParentSize(int generationSize, int *parent){
    for(int i=0; i<generationSize; i++){
        int customInput;
        // asks the user for a 1 or a 0 for the cell
        printf("[%d] Please enter a '1' or '0' to add into your parent generation: \n", i+1);
        scanf("%d", &customInput); 
        if (customInput==0 || customInput==1)
        {
            parent[i] = customInput;
        }
        else
        {
            printf("Invalid input please wite '1' or '0' \n");
            i--;
        }
    }
    // print the array that the user typed in
    printf("You typed: \n");
    for(int i=0; i<generationSize; i++){
        printf("%d", parent[i]);
    }
    printf("\n");
    printf("\n");
}

// allows the user to write the array to a file
void exportArray(int generationSize, int *parent, FILE* fp){
    // if the parent array is null, report the error 
    if(parent == NULL){
        printf("Current generation is null");
        return;
    }
    else{
        // export the array to the file
        if (fp != NULL){
            for(int p = 0; p < generationSize; p++){
                fprintf(fp, "%d", parent[p]);
            }
            fprintf(fp, "\n");
        }
        else{
            printf("File did not open");
        }
    }
}

// the function to generate the new generation
int generateNewGen (int generationSize, int noOfGenerations, bool customRule){

    //bool parentSize = true;
    int parent[generationSize];
    int ruleArray [8] = {0,0,0,1,1,1,1,0};
    int rule;
    int childGen [generationSize];
    FILE *fp;
    char OutputFile [] = "output.txt";
    fp = fopen(OutputFile,"w");
    // makes the user choose the parent size
    chooseParentSize(generationSize, parent);
    
    // if the user chose to make a custom rule, then asks for the rule
    if (customRule == true){
        chooseCustomRule(ruleArray);
    }
    
    // generates the generations for the rule, for the specified number of times
    for (int c = 0; c < noOfGenerations; c++){
        for(int i = 0; i < generationSize; i++){
            rule = checkRules(parent, i, generationSize);
            childGen[i] = ruleArray[rule];
        }
        // write the array to the file
        exportArray(generationSize, parent, fp);
        // display the array
        printArray(generationSize, parent);
        // take the array and copy it to the parent
        memcpy(parent, childGen, sizeof(parent));
    }
    fclose(fp);
}


// converts an integer to binary
int intToBinary(){
    int number;
    int remainder;
    int binary[8];
    int counter = 0;
    do{
        printf("Please enter an integer less than 256\n");
        scanf("%d", &number);
    }while(number > 256 || number < 0);
    remainder = number;
    for (int i = 128; i>0 ; i=i/2){
        if (remainder >= i){
            printf("1");
            binary[counter] = 1;
            remainder = remainder % i;
        }
        else{
            printf("0");
            binary[counter] = 0;
        }
        counter ++;
    }
    printf("\n");
    return 0;
}


// returns the index for the array depending on what rule is met
int checkRules(int parentGen [], int i, int generationSize){
    if(parentGen == NULL){
        printf("error, null parent generation");
    }
    if(parentGen[indexLeft(i,generationSize)] == 1 && parentGen[i] == 1 && parentGen[indexRight(i,generationSize)] == 1){
        return 0;
    }
    if(parentGen[indexLeft(i,generationSize)] == 1 && parentGen[i] == 1 && parentGen[indexRight(i,generationSize)] == 0){
        return 1;
    }
    if(parentGen[indexLeft(i,generationSize)] == 1 && parentGen[i] == 0 && parentGen[indexRight(i,generationSize)] == 1){
        return 2;
    }
    if(parentGen[indexLeft(i,generationSize)] == 1 && parentGen[i] == 0 && parentGen[indexRight(i,generationSize)] == 0){
        return 3;
    }   
    if(parentGen[indexLeft(i,generationSize)] == 0 && parentGen[i] == 1 && parentGen[indexRight(i,generationSize)] == 1){
        return 4;
    }
    if(parentGen[indexLeft(i,generationSize)] == 0 && parentGen[i] == 1 && parentGen[indexRight(i,generationSize)] == 0){
        return 5;
    }
    if(parentGen[indexLeft(i,generationSize)] == 0 && parentGen[i] == 0 && parentGen[indexRight(i,generationSize)] == 1){
        return 6;
    }
    if(parentGen[indexLeft(i,generationSize)] == 0 && parentGen[i] == 0 && parentGen[indexRight(i,generationSize)] == 0){
        return 7;
    }
}

// prints the array to the screen
void printArray(int generationSize, int currentGen []){
    if(currentGen == NULL){
            printf("Current generation is null");
            return;
        }
    for(int i = 0; i < generationSize; i++){
        printf("%d", currentGen[i]);
    }
    printf("\n");
}

// asks the number of generations the user wants to create 

int askNoOfGenerations(){
    int noOfGenerations;

    do
    {
        printf("Please enter the number of generations you would like to produce (above 0) \n");
        scanf("%d", &noOfGenerations); 
    }while(noOfGenerations<1);
    
    return noOfGenerations;
}

// the menu
int main (void)
{
    /*
    char aBoard [Width][Height];
    char (*board)[Height];
    board = aBoard;
    int Gen = 0;
    */

    int option;
    printf("\n");
    printf("        Welcome to Cellular Automata\n");
    printf("------------------------------------------\n\n");

    do
    {
        printf("Please enter an option from the main menu: \n");
        printf("Main Menu\n");
        printf("1. Convert Binary to Decimal\n");
        printf("2. Convert Deciaml to Binary\n");
        printf("3. Run Automaton\n");
        printf("4. Run game of life\n");
        printf("0. Quit.\n");
        scanf("%d",&option);

        switch(option)
        {
            case 1:
                printf("Converting binary to decimal...\n");
                binaryToInteger();
                break;

            case 2:
                printf("Converting decimal to binary...\n");
                intToBinary();
                break;

            case 3:
                printf("Create the First Generation\n");
                int genSize = customParent();
                int noOfGenerations = askNoOfGenerations();
                printf("Do you want to make a custom rule? ('1' is yes, '0' is no)\n");
                int input;
                scanf("%d", &input);
                bool customRule = validateBinaryInput(input);
                generateNewGen(genSize, noOfGenerations, customRule);
                break;

            case 4:
                
                gameOfLife();

            case 0:
                printf("Goodbye!\n");
                break;

            default:
                printf("Invalid input, please enter a number between \n");
                break;
        }
    }while(option != 0);

}


// converts binary to integer
int binaryToInteger()
{
    long num;
    long binaryNumber;
    long decimalNumber = 0;
    int baseMultiplier = 1;
    int remainder;

    printf("Enter a binary number\n");
    scanf("%ld", &num); 
    binaryNumber = num;

    while (num > 0)
    {
        remainder = num % 10;
        decimalNumber = decimalNumber + remainder * baseMultiplier;
        num = num / 10 ;
        baseMultiplier = baseMultiplier * 2;
    }

    printf("The Binary number is = %ld \n", binaryNumber);
    printf("Its decimal equivalent is = %ld \n", decimalNumber);

}


// asks the user if they want to make a custom parent
int customParent()
{
    int customParentGenSize;

    do
    {
    printf("Please enter the size of the custom parent generation you would like (above 0): \n");
    scanf("%d", &customParentGenSize); 

    }while(customParentGenSize<1);
   
    return customParentGenSize;
}