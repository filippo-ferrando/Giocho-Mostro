#include <stdlib.h>
#include <stdio.h>
#include <time.h>   
#include <string.h>

//betorglio e fenoglio
/*
        betoglio        fenoglio
vita        100             100
armatura   +5-10           +5-10 aggiunge vita
forza       5-10            5-10
arma       +5-10           +5-10 aggiungie forza
*/
//#################################################
/*
menù
 0 esci
 1 crea mostro
 2 gioca
 */

#define vitaIniziale 100
#define vitaMax 110
#define vitaMin 0
#define forza_max 10
#define forza_min 5
#define arma_max 15
#define arma_min 2
#define armatura_max 15
#define armatura_min 2
#define LUNG 100
#define n_mostri 2
 

typedef struct mostro{
    int vita;
    int forza;
    int arma;
    int armatura;
    char nome[LUNG];
}Mostro;

void setArma(Mostro *m){
    srand(time(NULL));
    int arma = rand()%(arma_max-arma_min+1)+arma_min;

    m->arma = arma;
}

void setArmatura(Mostro *m){
    srand(time(NULL));
    int armatura = rand()%(armatura_max-armatura_min+1)+armatura_min;

    m->armatura = armatura;
}

void setVita(int vita, Mostro *m){
    if(vita > vitaMin || vita < vitaMax){
        m->vita = vita;
    }
}

void setForza(Mostro *m){
    srand(time(NULL));
    int forza = rand()%(forza_max-forza_min+1)+forza_min;

    m->forza = forza;
}



int getVita(Mostro *m){
    return m->vita;
}

int getForza(Mostro *m){
    return m->forza;
}

void toString(Mostro m){ //visualizza struttura mostro
    printf("Nome = %s\n", &(m.nome));
    printf("Vita = %d\n", m.vita);
    printf("Forza = %d\n", m.forza);
    printf("Arma = %d\n", m.arma);
    printf("Armatura = %d\n", m.armatura);
}

int menu(){
    int n;
    printf("Premere 0 per uscire\n");
    printf("Premere 1 per creare il personaggio\n");
    printf("Premere 2 per giocare\n");
    fflush(stdin);
    scanf("%d",&n);
    return n;
}


Mostro creaMostro(char nome[LUNG]){
    Mostro m;
    setVita(vitaIniziale, &m);
    setForza(&m);
    setArma(&m);
    setArmatura(&m);
    strcpy(m.nome, nome);
    
    m.forza = m.forza + m.arma;
    m.vita = m.armatura + m.vita;

    return m;
}

void main(){
    Mostro n1, n2;
    int opz;
    char comandoAttacco;
    int numeroMostri = 0;
    char nome[LUNG];

    do{
        opz=menu();
        switch(opz){
            case 0:
                printf("Hai scelto si uscire");
            break;
            case 1:
                   
                if (numeroMostri < 1) {
                    numeroMostri++;
                    fflush(stdin);
                    scanf("%s", &nome);
                    n1 = creaMostro(nome);
                    toString(n1);
                    printf("\n");
                }else{
                    if(numeroMostri < 2){
                        numeroMostri++;
                        fflush(stdin);
                        scanf("%s", &nome);
                        n2 = creaMostro(nome);
                        toString(n2);
                        printf("\n");
                    }else{
                        printf("\nLimite mostri raggiunto\n");
                    }
                }
            break;

            case 2:
                printf("1 giocare preme F per giocare\n2 giocatore preme B per giocare\n");
                do{
                    scanf("%c", &comandoAttacco);
                    if(comandoAttacco == 'f' || comandoAttacco == 'F'){
                        printf("%s ATTACCA %s\n", &(n1.nome), &(n2.nome));
                        n2.vita -= n1.forza;
                        printf("Vita attuale di %s = %d\n", &(n2.nome), n2.vita);
                    } else if(comandoAttacco == 'b' || comandoAttacco == 'B'){
                        printf("%s ATTACCA %s\n", &(n2.nome), &(n1.nome));  
                        n1.vita = n1.vita - n2.forza;
                        printf("Vita rimanente di %s = %d\n", &(n1.nome), n1.vita);
                    }
                } while(n1.vita > 0 && n2.vita > 0);

                printf("\n\n");
                
                if(n1.vita>n2.vita){
                    printf("%s HA VINTO!", n1.nome);
                }else{
                    printf("%s HA VINTO!", n2.nome);
                }

                printf("\n\n");

            break;

        }
    } while(opz!=0);
}
