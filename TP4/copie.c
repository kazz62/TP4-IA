#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.c"

#define TAILLE 3

int taquin_but[TAILLE*TAILLE] = {0,1,2,3,4,5,6,7,8};

int est_but(int tab[TAILLE]){
    for(int i = 0; i<TAILLE*TAILLE; i++){
        if(tab[i]!= taquin_but[i]){
            return 0;
        }
    }
    return 1;
}

// La fonction vérifie si l'entier a est avant l'entier b dans le taquin but
int est_avant(int a, int b, int but[TAILLE*TAILLE]){
   int pos_a =0;
   int pos_b =0;
   for(int i =0; i< TAILLE*TAILLE;i++){
       if(but[i] == a){
           pos_a = i;
       }
       if(but[i]== b){
           pos_b = i;
       }
   }

   if(pos_a < pos_b){
       return 0;
   }
   else{
       return 1;
   }
}

int est_solvable(int tab[TAILLE*TAILLE],int but[TAILLE*TAILLE]){
    int cpt_inversion = 0;

    for(int i=0; i<TAILLE;i++){
        if(tab[i] != 0){
            for(int j = i+1; j<TAILLE;j++){
                if(tab[j] != 0){
                    if(est_avant(tab[i],tab[j],but)){
                        cpt_inversion++;
                    }
                }
            }
        }
    }
    printf("nb inversions : %d\n",cpt_inversion);
    if(cpt_inversion % 2 == 0){
        return 1;
    }
    else{
        return 0;
    }
}

int trouve_blanc(int tab[TAILLE*TAILLE]){
    for(int i=0;i<TAILLE*TAILLE;i++){
        if(tab[i] == 0){
            return i;
        }
    }
    return 0;
}

void display(int tab[TAILLE*TAILLE]){
    for(int i=0;i<TAILLE;i++){
        for(int j=0; j<TAILLE;j++){
            printf("[ %d ] ",tab[3*i+j]);
        }
        printf("\n"); 
    }
    printf("\n"); 
}

int verif_sequence(int tab[TAILLE*TAILLE], char *ch){;
    int pos_blanc = trouve_blanc(tab);
    for(int i=0;i<strlen(ch);i++){
        if(ch[i]== 'G' || ch[i] == 'g'){
            tab[pos_blanc] = tab[pos_blanc-1];
            tab[pos_blanc-1] = 0;
            pos_blanc = pos_blanc - 1;
        }
        else if(ch[i]== 'D' || ch[i] == 'd'){
            tab[pos_blanc] = tab[pos_blanc+1];
            tab[pos_blanc+1] = 0;
            pos_blanc = pos_blanc + 1;
        }
        else if(ch[i]== 'H' || ch[i] == 'h'){
            tab[pos_blanc] = tab[pos_blanc-3];
            tab[pos_blanc-3] = 0;
            pos_blanc = pos_blanc - 3;
        }
        else{
            tab[pos_blanc] = tab[pos_blanc+3];
            tab[pos_blanc+3] = 0;
            pos_blanc = pos_blanc + 3;
        }
        display(tab);
    }
    if(est_but(tab)){
        return 1;
    }
    return 0;
}

void copy_tab(int tab[TAILLE*TAILLE], int tab2[TAILLE*TAILLE]){
    for(int i =0;i<TAILLE*TAILLE;i++){
        tab2[i] = tab[i];
    }
}

int **successeurs(int tab[TAILLE*TAILLE]){
    int **succ = malloc(sizeof(int)*4);
    succ[0] = malloc(sizeof(int)*TAILLE*TAILLE);
    succ[1] = malloc(sizeof(int)*TAILLE*TAILLE);
    succ[2] = malloc(sizeof(int)*TAILLE*TAILLE);
    succ[3] = malloc(sizeof(int)*TAILLE*TAILLE);
    int tab_g[TAILLE*TAILLE];
    int tab_d[TAILLE*TAILLE];
    int tab_h[TAILLE*TAILLE];
    int tab_b[TAILLE*TAILLE];
    int pos_blanc = trouve_blanc(tab);
    //printf("INITIAL \n");
    //display(tab);
    if((pos_blanc > 0 && pos_blanc <= 3) || (pos_blanc > 4 && pos_blanc <= 6) || (pos_blanc > 7 && pos_blanc <= 8)){
        copy_tab(tab,tab_g);
        tab_g[pos_blanc] = tab_g[pos_blanc-1];
        tab_g[pos_blanc-1] = 0;
        copy_tab(tab_g,succ[0]);
        //printf("GAUCHE\n");
        //display(succ[0]);
    }

    if((pos_blanc >= 0 && pos_blanc < 3) || (pos_blanc >= 4 && pos_blanc < 6) || (pos_blanc >= 7 && pos_blanc < 8)){
        copy_tab(tab,tab_d);
        tab_d[pos_blanc] = tab_d[pos_blanc+1];
        tab_d[pos_blanc+1] = 0;
        copy_tab(tab_d,succ[1]);
        //printf("DROITE\n");
        //display(succ[1]);
    }

    if(pos_blanc+3 <= 9){
        copy_tab(tab,tab_b);
        tab_b[pos_blanc] = tab_b[pos_blanc+3];
        tab_b[pos_blanc+3] = 0;
        copy_tab(tab_b,succ[2]);
        //printf("BAS\n");
        //display(succ[2]);
    }

    if(pos_blanc-3 >= 0){
        copy_tab(tab,tab_h);
        tab_h[pos_blanc] = tab_h[pos_blanc-3];
        tab_h[pos_blanc-3] = 0;
        copy_tab(tab_h,succ[3]);
        //printf("HAUT\n");
        //display(succ[3]);
    }
    return succ;
}

void ajoute_sequence(int courant, char *sequence){
    if(courant == 0){
        strcat(sequence,"g");
    }
    else if(courant ==1) {
        strcat(sequence, "d");
    }
    else if(courant ==2) {
        strcat(sequence, "b");
    }
    else{
        strcat(sequence, "h");
    }
}

char * prof_limite(int tab[TAILLE*TAILLE], int l){
    struct stack *pt = newStack(100);
    int **succ = successeurs(tab);
    int taq[TAILLE*TAILLE];
    int taquin_courant = 0;
    char *sequence;

    push(pt,*succ[0]);

    while(!isEmpty(pt)){
        if(est_but(pt->items)){
            return sequence;
        }
        else{
            if (taquin_courant < l){
                push(pt,*succ[taquin_courant]);
                taquin_courant++;
            }
        }
        pop(pt);
    }

}

int main(){
    // RAPPEL ordre successeur : 0:G 1:D 2:B 3:H

    int taquin_faux[TAILLE*TAILLE] = {1,2,5,3,4,8,6,7,0};
    int taquin_diff[TAILLE*TAILLE] = {0,5,6,8,3,7,4,1,2};
    int taquin_diff2[TAILLE*TAILLE] = {1,0,6,2,3,7,5,8,4};
    //printf("%d\n", est_but(taquin_faux));
    //printf("%d \n",est_solvable(taquin_faux,taquin_but));
    //printf("%d \n",trouve_blanc(taquin_faux));
    //display(taquin_faux);
    //printf("%d \n",verif_sequence(taquin_faux,"HHGG"));
    //printf("%d \n", verif_sequence(taquin_diff2,"bbdhgghdbgbddhhgbdbghgbddhggh"));
    //printf("%d \n", verif_sequence(taquin_diff,"bbdhhgbbdhhdbbghhdbbghhgbbdhhg"));
    int **a = successeurs(taquin_faux);
    char *ch = prof_limite(taquin_diff, 15);
    return 0;
}