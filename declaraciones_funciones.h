#ifndef DECLARACIONES_FUNCIONES_H_INCLUDED
#define DECLARACIONES_FUNCIONES_H_INCLUDED

#include "declaraciones_variables.h"

/*----------------------------------------*/
/// LecturaYCargaDeBases.c
void inicializarEquipo(Equipo *nuevo, char nombre[]);
void crearNuevaBaseGrupo();
///void traerDesdeBaseArrayGrupo (Grupo arrayGrupo[]);
void crearArrayGrupoPartido();
void inicializarPartido(Partido *nuevo);
void insertarNodoPartido (int grupo, GrupoPartido arrayGrupoPartidos[], nodoPartido *insertar);
void traerDesdeBaseArrayPartidos(GrupoPartido arrayGrupoPartidos[], nodoEquipo *listaEquipos);
nodoEquipo *obtenerPunteroANodoEquipo(nodoEquipo *listaEquipos, char nombreBuscado[]);

/*----------------------------------------*/
/// impresionConsola.c
void imprimirCabeceraMenuPrincipal();
void imprimirCabeceraMenuPrincipal();
void imprimirUnSoloGrupo (nodoGrupoEquipo *listaEquiposGrupo);
void imprimirArrayGrupo (Grupo arrayGrupo[]);
void imprimirUnSoloPartido(Partido imprimir, int mostrarResultados);
void imprimirArrayGrupoPartidos (GrupoPartido arrayGrupoPartidos[]);


/*----------------------------------------*/
///procesamientoMenuPrincipal.c
char menuPrincipal (char input, GrupoPartido arrayPartidosGrupos[], fase arrayFase[], Grupo arrayEquiposGrupos[], nodoEquipo *listaEquipos);
void iniciarMenuPrincipal(GrupoPartido arrayPartidosGrupos[], fase arrayFase[], Grupo arrayEquiposGrupos[], nodoEquipo *listaEquipos);
void subMenuBasesDeDatos(GrupoPartido arrayPartidosGrupos[], fase arrayFase[], Grupo arrayEquiposGrupos[], nodoEquipo *listaEquipos);

/*----------------------------------------*/
/// SimuladorPartidos.c
///COMPLETAR

#endif // DECLARACIONES_FUNCIONES_H_INCLUDED
