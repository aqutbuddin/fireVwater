/*-------------------------------------------
Program 1: Fire vs Water
Course: Professor Koehler CS 211, Spring 2024, UIC
System: Advanced zyLab
Author: Aima Qutbuddin
In this project, I used the advanced zylabs enviorment to spread fire annd water across a grid by enforcing a set of rules through a series of simulatiuons. 
IN the simulaitons, the grid is updated then outputted a set of statistics relaying the state of the board.
I utilized for loops and if-else statements to implememt the spread. When fire meets grass or water, it turns into either another fire cell or into an empty cell, respectivley.
When water meets empty or fire, it turns into either another water cell or into an empty cell, respectivley.
------------------------------------------- */
// Copyright Notice
// This document is protected by U.S. copyright law. Reproduction and 
// distribution of this work, including posting or sharing through any medium, 
// is explicitly prohibited by law, and also violates UIC's Student 
// Disciplinary Policy (A2-c. Unauthorized Collaboration; and A2-e3. 
// Participation in Academically Dishonest Activities: Material Distribution).

// Given includes - DO NOT include anything else
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "project_utils.h"

// Prototypes for given functions (given as stubs)
void displayGrid(int r, int c, int g[][c]);
void spread(int r, int c, int g[][c], int spreadWhat);
// Additional Function Decomposition Prototypes
void printStats(int r, int c, int g[][c], int simulations);

int main()
{
    // set up random number generator based on project settings
    srand(RAND_SEED);
    
    // Acquire the simulation count from input
    int simCount = 0;

    // Acquire the simulation count from input
    scanf("%d", &simCount);
    
    // grid setup
    int cols = -1;
    int rows = -1;

    // initialize grid size based on input values
    scanf("%d %d", &rows, &cols);
    int grid[rows][cols];

    // Initialize the 2D grid
    for(int gridRow = 0; gridRow < rows; gridRow++){
        for(int gridColumn = 0; gridColumn < cols; gridColumn++){
            scanf("%d", &grid[gridRow][gridColumn]);
        }
    }

    // Output initial program details
    printf("Fire vs Water - %d Simulations!\n", simCount);

    // output the initial grid
    displayGrid(rows, cols, grid);
    
    // execute however many simulations were requested
    for(int simNum = 1; simNum <= simCount; simNum++){
        //calling functions to implement the spread of fire or water and diplay the updated boards in between simulations
        spread(rows,cols,grid,FIRE); 
        spread(rows,cols,grid,WATER);
        // redraw the updated grid to the screen
        displayGrid(rows, cols, grid);
        // pause for animation
        animate();
    }
    //print the stats after all simulations are complete
    printStats(rows, cols, grid, simCount);
    
    return 0;
}
//Function to display the board
void displayGrid(int r, int c, int g[][c]){
    clearScreen();
    //implement and use the given project utility printCell function
    for(int displayRow = 0; displayRow < r; displayRow++){
       for(int displayColumn = 0; displayColumn < c; displayColumn++){
           printCell(g[displayRow][displayColumn]);
       }
       printf("\n");
    }
}
void printStats(int r, int c, int g[][c], int simulations){
    //print the stats after all simulations are complete]
    //counters to keep track of all states conditions 
    int allCells = 0;
    int empty = 0;
    int fire = 0;
    int grass = 0; 
    int water = 0; 
    //looping through grid and updating the counters based on each cell state
    for(int i = 0; i < r; i++ ){
        for( int j = 0; j < c; j++){
            if(g[i][j] == EMPTY){
                empty++;
            }
            else if(g[i][j] == FIRE){
                fire++;
            }
            else if(g[i][j] == GRASS){
                grass++;
            }
            else if(g[i][j] == WATER){
                water++;
            }
            allCells++; 
        }
    }
    //outputting state stats after all simualtions are completed 
    printf("\nFire vs Water - Stats After %d Simulations!\n", simulations);
    printf("Total Cells: %d\n", allCells);
    printf("Cells Containing Nothing: %d\n", empty);
    printf("Cells Containing Grass: %d\n", grass);
    printf("Cells Containing Water: %d\n", water);
    printf("Cells Containing Fire: %d\n", fire);
    printf("\n");

}                                      
void spread(int r, int c, int g[][c], int spreadWhat){
    const int tempEmptyCell = 5; //place holder for a water or fire cell that has been applied fire or water respectivley, EMPTY
    const int tempFireCell = 6; //place holder for a grass cell that has been applied fire, FIRE
    const int tempWaterCell = 6;//place holder for a fire cell that has been applied water, FIRE
    bool checkRand = false; // checking if random is successful in spreading, true or false

    // iterating through grid to implement spread     
    for(int row = 0; row < r; row++){
        for(int column = 0; column < c; column++){
            if(g[row][column] == spreadWhat){ 
                int randomDirection = rand() % 4; // randomly assigning a direction
                checkRand = false; 
                if(spreadWhat == FIRE){//FIRE spread rules
                    //each if-else if block checks conditions on the direction and if spread is possible depending on the state of the cell 
                    // if checks are met then grid is updated to a temporary placeholder and the boolean is set to true 
                    // NORTH RANDOM 
                    if(randomDirection == NORTH  && row > 0 && g[row-1][column] == GRASS){ 
                        g[row-1][column] = tempFireCell;
                        checkRand = true; 
                    }
                    else if(randomDirection == NORTH && row > 0 && g[row-1][column] == WATER){
                        g[row-1][column] = tempEmptyCell; 
                        checkRand = true;
                    }
                    // SOUTH RANDOM 
                    else if(randomDirection == SOUTH  && row < r-1 && g[row+1][column] == GRASS){
                        g[row+1][column] = tempFireCell;
                        checkRand = true;
                    }
                    else if(randomDirection == SOUTH && row < r-1 && g[row+1][column] == WATER){
                        g[row+1][column] = tempEmptyCell; 
                        checkRand = true;
                    }
                    //EAST RANDOM
                    else if(randomDirection == EAST  && column < c-1 && g[row][column+1] == GRASS){
                        g[row][column+1] = tempFireCell;
                        checkRand = true;
                    }
                    else if(randomDirection == EAST &&  column  < c-1  && g[row][ column+1] == WATER){
                        g[row][column+1] = tempEmptyCell; 
                        checkRand = true;
                    }
                    //WEST RANDOM 
                    else if(randomDirection == WEST && column > 0 && g[row][column-1] == GRASS){
                        g[row][column-1] = tempFireCell;
                        checkRand = true;
                    }
                    else if(randomDirection == WEST && column > 0 && g[row][column-1] == WATER){
                       g[row][column-1] = tempEmptyCell;
                        checkRand = true; 
                    }
                    if(!checkRand){ // when random spread fails, the spread checks grid in N,S,E,W order
                        //NORTH
                        if( row > 0 && g[row-1][column] == GRASS){
                            g[row-1][column] = tempFireCell;
                        }
                        else if(row > 0 && g[row-1][column] == WATER){
                            g[row-1][column] = tempEmptyCell;
                        }
                        //SOUTH
                        else if(row < r-1 && g[row+1][column] == GRASS){
                            g[row+1][column] = tempFireCell;
                        }
                        else if(row < r-1 && g[row+1][column] == WATER){
                            g[row+1][column] = tempEmptyCell;
                        }
                        //EAST
                        else if(column < c-1 && g[row][column+1] == GRASS){
                            g[row][column+1] = tempFireCell;
                        }
                        else if(column < c-1 && g[row][column+1] == WATER){
                            g[row][column+1] = tempEmptyCell;
                        }
                        //WEST
                        else if(column > 0 && g[row][column-1] == GRASS){
                            g[row][column-1] = tempFireCell;
                        }
                        else if(column > 0 && g[row][column-1] == WATER){
                            g[row][column-1] = tempEmptyCell;
                        }
                    }
                }
                //each if-else if block checks conditions on the direction and if spread is possible depending on the state of the cell 
                // if checks are met then grid is updated to a temporary placeholder and the boolean is set to true 
                else if(spreadWhat == WATER){ // WATER spread rules
                    // NORTH RANDOM 
                    if(randomDirection == NORTH  && row > 0 && g[row-1][column] == FIRE){ 
                        g[row-1][column] = tempEmptyCell;
                        checkRand = true; 
                    }
                    else if(randomDirection == NORTH && row > 0 && g[row-1][column] == EMPTY){
                        g[row-1][column] = tempWaterCell; 
                        checkRand = true;
                    }
                    // SOUTH RANDOM 
                    else if(randomDirection == SOUTH  && row < r-1 && g[row+1][column] == FIRE){
                        g[row+1][column] = tempEmptyCell;
                        checkRand = true;
                    }
                    else if(randomDirection == SOUTH && row < r-1 && g[row+1][column] == EMPTY){
                        g[row+1][column] = tempWaterCell; 
                        checkRand = true;
                    }
                    //EAST RANDOM
                    else if(randomDirection == EAST  && column < c-1 && g[row][column+1] == FIRE){
                        g[row][column+1] = tempEmptyCell;
                        checkRand = true;
                    }
                    else if(randomDirection == EAST &&  column  < c-1  && g[row][column+1] == EMPTY){
                        g[row][column+1] = tempWaterCell; 
                        checkRand = true;
                    }
                    //WEST RANDOM 
                    else if(randomDirection == WEST && column > 0 && g[row][column-1] == FIRE){
                        g[row][column-1] = tempEmptyCell;
                        checkRand = true;
                    }
                    else if(randomDirection == WEST && column > 0 && g[row][column-1] == EMPTY){
                    g[row][column-1] = tempWaterCell;
                        checkRand = true; 
                    }
                    if(!checkRand){// when random spread fails, the spread checks grid in N,S,E,W order
                        //NORTH
                        if( row > 0 && g[row-1][column] == FIRE){
                            g[row-1][column] = tempEmptyCell;
                        }
                        else if( row > 0 && g[row-1][column] == EMPTY){
                            g[row-1][column] = tempWaterCell;
                        }
                        //SOUTH
                        else if(row < r-1 && g[row+1][column] == FIRE){
                            g[row+1][column] = tempEmptyCell;
                        }
                        else if( row < r-1 && g[row+1][column] == EMPTY){
                            g[row+1][column] = tempWaterCell;
                        }
                        //EAST
                        else if(column < c-1 && g[row][column+1] == FIRE){
                            g[row][column+1] = tempEmptyCell;
                        }
                        else if(column < c-1 && g[row][column+1] == EMPTY){
                            g[row][column+1] = tempWaterCell;
                        }
                        //WEST
                        else if(column > 0 && g[row][column-1] == FIRE){
                            g[row][column-1] = tempEmptyCell;
                        }
                        else if(column > 0 && g[row][column-1] == EMPTY){
                            g[row][column-1] = tempWaterCell;
                        }
                    }
                }
            }
        }
    }
    //iterating over the bpard again to update the temporary values to reflect the true state of each cell 
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            if (g[i][j] == tempEmptyCell){
                g[i][j] = EMPTY;
            }
            else if(g[i][j] == tempFireCell){
                g[i][j] = spreadWhat;
            } 
            else if (g[i][j] == tempWaterCell){
                g[i][j] = spreadWhat;
            }
        }
    }
}