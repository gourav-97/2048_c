#ifndef C2048_H
#define C2048_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>



// D for Dimension
#define D 4 
#define GAMESIZE 16

int undo_flag=0;
int undo_score=0;
static int Tiles[GAMESIZE];
static int Tiles_copy[GAMESIZE];
int score;
/* we need randomizer */
//int GetRandomNumberWeNeed(int n, int m);
/* we need movement functionality */

/* tiles functionality */
int NotEmpty();
int Empty(void);
int random_index(int x);
int generate_new_index();
void Initialise(void);
void ShiftRight(void);
void ShiftLeft(void);
void ShiftDown(void);
void ShiftUp(void);
void MergeRight(void);
void MergeLeft(void);
void MergeDown(void);
void MergeUp(void);
void PrintBoard();
void instructions();
void restart();
int calculate_max();
void lost();
void ends();
int game_ends();
void wins();
void Start();
#endif

