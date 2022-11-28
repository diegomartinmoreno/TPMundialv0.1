#ifndef DECLARACIONES_VARIABLES_H_INCLUDED
#define DECLARACIONES_VARIABLES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/// las librerias de abajo son para que el bendito generador de numeros random funcione.
#include <time.h>
#include <conio.h>
#include <stddef.h>
#include <unistd.h>
#include <windows.h>

#define TAM_MAX_GRUPOS 8
#define TAM_MAX_GRUPO 4

/*----------------------------------------*/

///   Explicación de variables:
/// GrupoPartido arrayPartidosGrupos[] = Contiene un arreglo de listas de los PARTIDOS de fase de grupos.
/// fase arrayFase[] = Contiene un arreglo de listas con los PARTIDOS de cada fase PlayOffs. 0=Octavos, 4=Final.
/// Grupo arrayEquiposGrupos[] = Contiene un arreglo de listas de los EQUIPOS de cada grupo y sus estadísticas.
/// Cualquier estructura que contenga un puntero nodoEquipo, apuntara siempre a la misma direccion de memoria para cada respectivo equipo.
/// Cambios en un equipo en una estructura, afetará a todas las demás que incluyan a ese equipo.

/*----------------------------------------*/

typedef struct
{
    float probEquipo1;
    float probEquipo2;
} probabilidad;

typedef struct /// por consigna, solo se guardan partidos de fase de grupos, ya que el resto se simula.
{
    int fecha; /// DDMM
    char grupo;
    char nomEquipo1[40];
    char nomEquipo2[40];
} partidoArchivo;


typedef struct
{
    char nomEquipo[40];
    int mp;   /// partidos jugados
    int gf;   /// goles a favor
    int ga;   /// goles en contra
    int win;  /// partidos ganados
    int loss; /// partidos perdidos
    int pts; /// puntos totales.
} Equipo;

typedef struct
{
    int id;
    int fecha; /// DDMM
    Equipo* equipo1;
    Equipo* equipo2;
    int golesEq1;
    int golesEq2;
    int penales1; /// en la fase de grupos no hay penales
    int penales2; /// 1 si hay penales (playoffs), 0 si no hay penales (grupos).
} Partido;

typedef struct nodoPartido
{
    Partido partido;
    struct nodoPartido* siguiente;
} nodoPartido;

typedef struct
{
    int idFase;
    nodoPartido* partidos;
} fase;

typedef struct
{
    char letra;
    nodoPartido* partidos;
} GrupoPartido;

typedef struct nodoEquipo
{
    Equipo equipo;
    struct nodoEquipo* siguiente;
} nodoEquipo;

typedef struct Grupo
{
    char letra; ///'A','B'....
    struct nodoGrupoEquipo* equipos;
} Grupo;

typedef struct nodoGrupoEquipo
{
    Equipo* equipo;
    struct nodoGrupoEquipo* siguiente;
} nodoGrupoEquipo;


#endif // DECLARACIONES_VARIABLES_H_INCLUDED
