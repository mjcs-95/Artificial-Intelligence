/*******************************************/
/* 		    NODO.H                         */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/

#ifndef _tElemento_
#define _tElemento_
   typedef struct NodoBusqueda{
      tEstado *estado;
      struct NodoBusqueda *padre;
      unsigned operador;
      int costeCamino;
      int profundidad;
      int valHeuristica;
   } tNodoBusqueda;

   typedef tNodoBusqueda tElemento;
#endif





