#include"../pemain/pemain.h"

#define Top(S) (S).TOP
#define InfoTop(S) (S).T[(S).TOP]
#define StateP1(Q) (Q).X
#define StateP2(Q) (Q).Y 
#define StateNetral(Q) (Q).Netral
#define StateBangunan(Q) (Q).Tab
typedef struct{
    Pemain X,Y;/*Pemain 1 dan Pemain 2*/
    List Netral;
    TabBangunan Tab;
} states;

typedef struct {
    states T[101];
    int TOP;
} StackUndo;

boolean IsEmptyStack(StackUndo S);
void CreateEmptyStackUndo(StackUndo *S);
void SaveState(StackUndo *S,Pemain P1,Pemain P2,List Netral,TabBangunan Bangunan);
void PushStack(StackUndo *S,states s);
void PopStack(StackUndo *S,states *q);
void LoadState(StackUndo *S,Pemain *P1,Pemain *P2,List *Netral,TabBangunan *Bangunan);






