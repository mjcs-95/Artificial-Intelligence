/*******************************************/
/* 		    BUSQUEDA.C                     */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "puzle.h"
#include "nodo.h"
#include "listaia.h"

void dispCamino(tElemento *nodo){
   	if (nodo->padre==NULL){
      
      	printf("\n\nInicio:\n");
      	dispEstado(nodo->estado);
   	}else{
      	dispCamino(nodo->padre);
      	dispOperador(nodo->operador);
      	dispEstado(nodo->estado);
      	printf("\n");
   	}
}

void dispSolucion(tElemento *nodo){
	dispCamino(nodo);
   	printf("Profundidad=%d\n",nodo->profundidad);
   	printf("Coste=%d\n",nodo->costeCamino);
}

/* Crea el nodo raíz. */
tElemento *nodoInicial(){
   	tElemento *inicial=(tElemento *) malloc(sizeof(tElemento));

   	inicial->estado=estadoInicial();
   	inicial->padre=NULL;
   	inicial->costeCamino=0;
   	inicial->profundidad=0;
   	return inicial;
}

/* Expande un nodo. */
Lista expandir(tElemento *nodo ){
   	unsigned op;
	Lista sucesores=CrearLista(MAXI);
  	//printf("\nLista de Sucesores de Actual: \n");
   	for (op=1;op<=NUM_OPERADORES;op++){//Anchura
      	if (esValido(op,nodo->estado)){
         	tElemento *nuevo=(tElemento *) malloc(sizeof(tElemento));
         	tEstado *s=(tEstado *) malloc(sizeof(tEstado));
         	s=aplicaOperador(op,nodo->estado);
			nuevo=(tElemento *) malloc(sizeof(tElemento));
	       	nuevo->estado=s;
    	   	nuevo->padre=nodo;
       	 	nuevo->operador=op;
       		nuevo->costeCamino=nodo->costeCamino + coste(op,nodo->estado);
      	 	nuevo->profundidad=nodo->profundidad+1;
			if (!ListaLlena(sucesores)){
           		InsertarUltimo(nuevo,sucesores);//Anchura
      		    //dispEstado(nuevo->estado);
       		}
      	}
  	}
  	//system("pause");
  	return sucesores;
}

/////////////Profundidad Iterativa///////////////////////////
int busquedaprofundidaditerativa(){
    int l=0;   	
	int objetivo=0;
    do{
        objetivo=busquedaprofundidadlimitada(l);
        l++;
    }while ( !objetivo );
    return l;
}
/////////////Profundidad Limitada////////////////////////////
int busquedaprofundidadlimitada(int l){
   	int objetivo=0;
   	int estadosvisitados=0;
   	int maximoabiertos=0;
   	tElemento *Actual=(tElemento*) malloc(sizeof(tElemento));
   	tElemento *Inicial=nodoInicial();
   	tEstado *Final=estadoObjetivo();
   	Lista Abiertos= (Lista) CrearLista(MAXI);
   	Lista Cerrados= (Lista) CrearLista(MAXI);//Visitados
	Lista Sucesores;
   	InsertarUltimo(Inicial, Abiertos);
	int i;   	
	while (!ListaVacia(Abiertos) && !objetivo){
		Actual=ExtraerPrimero(Abiertos);
	    //printf("\n ACTUAL: \n");
	    //dispEstado(Actual->estado);
	    //system("pause");
    	EliminarPrimero(Abiertos);
      	objetivo=testObjetivo(Actual->estado, Final);
      	if (!objetivo && l>= Actual->profundidad ){
         	int visitado = 0;
         	for( i=0;!visitado && i<Cerrados->Nelem;i++){
         		if( iguales( Actual->estado ,ExtraerElem(Cerrados,i)->estado ) ){
					visitado=1;  //Control de estados repetidos
				}
			}
			if(!visitado){
				Sucesores = expandir(Actual);
    	     	Abiertos=Concatenar(Sucesores, Abiertos);//profundidad
				InsertarUltimo(Actual,Cerrados);// Control de estados repetidos
			}		
		}
		if(Abiertos->Nelem > maximoabiertos ) { 
			maximoabiertos =  Abiertos->Nelem;
		}
		estadosvisitados++;
   	}
	dispSolucion(Actual);
  	if(objetivo){ puts ("SOLUCIÓN ENCONTRADA");}else{puts ("SOLUCIÓN NO ENCONTRADA");}
  	printf("Estados visitados : %d \n",estadosvisitados);
   	printf("Máximo estados Abiertos a la vez : %d \n",maximoabiertos);
	system("pause");
	return objetivo;
}

/////////////Profundidad/////////////////////////////////////
int busquedaprofundidad(){
   	int objetivo=0;
   	int estadosvisitados=0;
   	int maximoabiertos=0;
   	tElemento *Actual=(tElemento*) malloc(sizeof(tElemento));

   	tElemento *Inicial=nodoInicial();
   	tEstado *Final=estadoObjetivo();

   	Lista Abiertos= (Lista) CrearLista(MAXI);
   	Lista Cerrados= (Lista) CrearLista(MAXI);//Visitados
	Lista Sucesores;

   	InsertarUltimo(Inicial, Abiertos);
	int i;   	
	while (!ListaVacia(Abiertos) && !objetivo){
		Actual=ExtraerPrimero(Abiertos);
	    printf("\n ACTUAL: \n");
	    dispEstado(Actual->estado);
	    system("pause");
    	EliminarPrimero(Abiertos);
      	objetivo=testObjetivo(Actual->estado, Final);
      	if (!objetivo){
         	int visitado = 0;
         	for( i=0;!visitado && i<Cerrados->Nelem;i++){
         		if( iguales( Actual->estado ,ExtraerElem(Cerrados,i)->estado ) ){
					visitado=1;  //Control de estados repetidos
				}
			}
			if(!visitado){
				Sucesores = expandir(Actual);
    	     	Abiertos=Concatenar(Sucesores, Abiertos);//profundidad
				InsertarUltimo(Actual,Cerrados);// Control de estados repetidos
			}		
		}
		if(Abiertos->Nelem > maximoabiertos ) { 
			maximoabiertos =  Abiertos->Nelem;
		}
		estadosvisitados++;
   	}
	dispSolucion(Actual);
   	printf("Estados visitados : %d \n",estadosvisitados);
   	printf("Máximo estados Abiertos a la vez : %d \n",maximoabiertos);
	return objetivo;
}

/////////////Anchura/////////////////////////////////////////
int busquedaanchura(){
   	int objetivo=0;
   	int estadosvisitados=0;
   	int maximoabiertos=0;
   	tElemento *Actual=(tElemento*) malloc(sizeof(tElemento));

   	tElemento *Inicial=nodoInicial();
   	tEstado *Final=estadoObjetivo();

   	Lista Abiertos= (Lista) CrearLista(MAXI);
   	Lista Cerrados= (Lista) CrearLista(MAXI);//Visitados
	Lista Sucesores;

   	InsertarUltimo(Inicial, Abiertos);
	int i;   	
	while (!ListaVacia(Abiertos) && !objetivo){
		Actual=ExtraerPrimero(Abiertos);
	    printf("\n ACTUAL: \n");
	    dispEstado(Actual->estado);
	    system("pause");
    	EliminarPrimero(Abiertos);
      	objetivo=testObjetivo(Actual->estado, Final);
      	if (!objetivo){
         	int visitado = 0;
         	for( i=0;!visitado && i<Cerrados->Nelem;i++){
         		if( iguales( Actual->estado ,ExtraerElem(Cerrados,i)->estado ) ){
					visitado=1;  //Control de estados repetidos
				}
			}
			if(!visitado){
				Sucesores = expandir(Actual);
    	     	Abiertos=Concatenar(Abiertos, Sucesores);//anchura
    	     	InsertarUltimo(Actual,Cerrados);// Control de estados repetidos
			}		
		}
		if(Abiertos->Nelem > maximoabiertos ) { 
			maximoabiertos =  Abiertos->Nelem;
		}
		estadosvisitados++;
   	}
	dispSolucion(Actual);
   	printf("Estados visitados : %d \n",estadosvisitados);
   	printf("Máximo estados Abiertos a la vez : %d \n",maximoabiertos);
	return objetivo;
}

//Fin
