/*******************************************/
/* 		      PUZLE.C                      */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "puzle.h"



tEstado *crearEstado(int celdas[N][N])
{
   	tEstado *estado = (tEstado *) malloc(sizeof(tEstado));
   	int i, j, ficha;

   	for (i=0;i<N;i++)
		for (j=0;j<N;j++){
        	ficha=celdas[i][j];
        	estado->celdas[i][j]=ficha;
         	estado->fila[ficha]=i;
         	estado->col[ficha]=j;
      	}
   return estado;
}


tEstado *estadoInicial(){
   return crearEstado(puzle_inicial);
}


tEstado *estadoObjetivo(){
   return crearEstado(puzle_final);
}

int coste(unsigned op, tEstado *estado){
   return 1;
}

/* VISUALIZACIÓN DE ESTADOS Y OPERADORES*/


void dispEstado(tEstado *estado){
   	int i,j;
   	for (i=0; i<N; i++){
      	for (j=0; j<N; j++)
         	printf("%d",estado->celdas[i][j]);
      	printf("\n");
   	}
   	printf("\n");
}


void dispOperador(unsigned op){
   	switch(op){
    	case ARRIBA:    printf("Movimiento ARRIBA:\n"); break;
      	case ABAJO:     printf("Movimiento ABAJO:\n"); break;
      	case IZQUIERDA: printf("Movimiento IZQUIERDA:\n"); break;
      	case DERECHA:   printf("Movimiento DERECHA:\n"); break;
   }
}

// FUNCIONES QUE SE HAN DE IMPLEMENTAR EN LA PRACTICA 1

int iguales(tEstado *s, tEstado *t){
    int i;
    int j;
	for(i=0 ; i<N ; i++)
    	for(j=0 ; j<N ;j++)
			if(s->celdas[i][j] != t->celdas[i][j]) return 0;
	return 1;
}


int testObjetivo(tEstado *estado, tEstado *objetivo){
    int i;
    int j;
	for( i=0 ; i<N ; i++)
    	for( j=0 ; j<N ;j++)
			if(estado->celdas[i][j] != objetivo->celdas[i][j]) return 0;
	return 1;
}


int esValido(unsigned op, tEstado *estado){
    switch(op){
    	case ARRIBA 	: return ( estado->fila[0] == 0   ) ? 0 : 1;
		case ABAJO		: return ( estado->fila[0] == N-1 ) ? 0 : 1;
		case IZQUIERDA  : return ( estado->col[0]  == 0   ) ? 0 : 1;
		case DERECHA 	: return ( estado->col[0]  == N-1 ) ? 0 : 1;
	}
}


tEstado *aplicaOperador(unsigned op, tEstado *anterior){
    tEstado * nuevo = crearEstado(anterior->celdas);
	int n;
	switch(op){
    	case ARRIBA 	: 
    		n= nuevo->celdas[ nuevo->fila[0]-1 ][ nuevo->col[0] ];
			nuevo->fila[0]--;
    		nuevo->fila[n]++;
    		break;
		case ABAJO		:
    		n= nuevo->celdas[ nuevo->fila[0]+1 ][ nuevo->col[0] ];
    		nuevo->fila[0]++;
    		nuevo->fila[n]--;			
    		break;
		case IZQUIERDA  :
    		n= nuevo->celdas[ nuevo->fila[0] ][ nuevo->col[0]-1 ];
			nuevo->col[0]--;
    		nuevo->col[n]++;
    		break;
		case DERECHA 	:
    		n= nuevo->celdas[ nuevo->fila[0] ][ nuevo->col[0]+1 ];
			nuevo->col[0]++;
    		nuevo->col[n]--;
	}
	nuevo->celdas[ nuevo->fila[0] ][ nuevo->col[0] ] = 0;
    nuevo->celdas[ nuevo->fila[n] ][ nuevo->col[n] ] = n;
    return nuevo;
}




