#ifndef DECLARACIONES_FUNCIONES_H_INCLUDED
#define DECLARACIONES_FUNCIONES_H_INCLUDED

#include "declaraciones_variables.h"

/*----------------------------------------*/
/// LecturaYCargaDeBases.c
void inicializarEquipo(Equipo *nuevo);
void crearNuevaBaseGrupo();
void traerDesdeBaseArrayGrupo (Grupo arrayGrupo[]);
void crearArrayGrupoPartido();
void inicializarPartido(Partido *nuevo);
void insertarNodoPartido (int grupo, GrupoPartido arrayGrupoPartidos[], nodoPartido *insertar);
void traerDesdeBaseArrayPartidos(GrupoPartido arrayGrupoPartidos[]);

/*----------------------------------------*/
/// impresionConsola.c
void imprimirCabeceraMenuPrincipal();
void imprimirCabeceraMenuPrincipal();
void imprimirUnSoloGrupo (nodoEquipo *listaEquiposGrupo);
void imprimirArrayGrupo (Grupo arrayGrupo[]);
void imprimirUnSoloPartido(Partido imprimir, int mostrarResultados);
void imprimirArrayGrupoPartidos (GrupoPartido arrayGrupoPartidos[]);


/*----------------------------------------*/
///procesamientoMenuPrincipal.c
char menuPrincipal (char input, GrupoPartido arrayPartidosGrupos[], fase arrayFase[], Grupo arrayEquiposGrupos[]);
void iniciarMenuPrincipal(GrupoPartido arrayPartidosGrupos[], fase arrayFase[], Grupo arrayEquiposGrupos[]);

/*----------------------------------------*/
///simulacionPartidos.c
///COMPLETAR

#endif // DECLARACIONES_FUNCIONES_H_INCLUDED
