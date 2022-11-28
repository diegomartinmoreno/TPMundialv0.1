#ifndef DECLARACIONES_FUNCIONES_H_INCLUDED
#define DECLARACIONES_FUNCIONES_H_INCLUDED

#include "declaraciones_variables.h"

/*----------------------------------------*/
/// Declaraciones para LecturaYCargaDeBases.c

/// >>> 1) INICIO de funciones relacionadas a estructura Grupo (equipos).

///     1.1) Funciones para < CREAR O CARGAR DEFAULT > BaseArrayGrupo.bin (EQUIPOS), solo para primera ejecución.
void crearNuevaBaseGrupo();
void cargarDefaultBaseGrupo();
///     1.2) Funciones para < LEVANTAR > BaseArrayGrupos.bin y volcarlo en lista simple de equipos.
void inicializarEquipo(Equipo *nuevo, char nombre[]);
nodoEquipo *inicializarNodoEquipo (nodoEquipo *nuevo, char nombre[]);
nodoEquipo *leerListaEquipos ();
///     1.3) Funciones para < VINCULAR > equipos en el arreglo de grupos con equipos de la lista simple.
void inicializarArrayGrupoEquipos (Grupo arrayGrupoEquipos[]);
nodoGrupoEquipo *inicializarNodoGrupoEquipo(nodoGrupoEquipo *nuevo);
nodoGrupoEquipo *agregarNodoGrupoEquipo(nodoGrupoEquipo *listaGrupoEquipo, nodoGrupoEquipo *nuevo);
void vincularAListaArrayGruposEquipos (Grupo arrayGrupoEquipos[], nodoEquipo *listaEquipos);

/// >>> 2) INICIO de funciones relacionadas a estructura GrupoPartido (Partidos).

///     2.1) Funciones para < AGREGAR, REINICIAR O CARGAR DEFAULT > a BaseArrayPartidos.bin (PARTIDOS).
void reiniciarBasePartidos ();
void cargarDefaultBasePartido();
int verificarSiEstaEquipo (nodoEquipo *listaEquipos, char nombre[]);
int verificarGrupo (char grupo);
void agregarABaseArrayGrupoPartido(nodoEquipo *listaEquipos);
///     2.2) Funciones para < LEVANTAR Y VINCULAR > desde BaseArrayPartidos.bin (PARTIDOS) a GrupoPartido.
void inicializarPartido(Partido *nuevo);
void inicializarArrayGrupoPartidos(GrupoPartido arrayGrupoPartidos[]);
void insertarNodoPartido (int grupo, GrupoPartido arrayGrupoPartidos[], nodoPartido *insertar);
nodoEquipo *obtenerPunteroANodoEquipo(nodoEquipo *listaEquipos, char nombreBuscado[]);
void leerYVincularBaseArrayPartidos(GrupoPartido arrayGrupoPartidos[], nodoEquipo *listaEquipos);


/*----------------------------------------*/
/// impresionConsola.c
void imprimirCabeceraMenuPrincipal();
void imprimirMenuPrincipal();
void imprimirSubMenuBases();
void imprimirUnSoloGrupo (nodoGrupoEquipo *listaEquiposGrupo);
void imprimirArrayGrupo (Grupo arrayGrupo[]);
void imprimirUnSoloPartido(Partido imprimir, int mostrarResultados);
void imprimirArrayGrupoPartidos (GrupoPartido arrayGrupoPartidos[]);


/*----------------------------------------*/
///procesamientoMenuPrincipal.c
char menuPrincipal (int *faseGruposYaSimulada, char input, GrupoPartido arrayPartidosGrupos[], fase arrayFase[], Grupo arrayEquiposGrupos[], nodoEquipo *listaEquipos);
void iniciarMenuPrincipal(GrupoPartido arrayPartidosGrupos[], fase arrayFase[], Grupo arrayEquiposGrupos[], nodoEquipo *listaEquipos);
void subMenuBasesDeDatos(GrupoPartido arrayPartidosGrupos[], fase arrayFase[], Grupo arrayEquiposGrupos[], nodoEquipo *listaEquipos);


/*----------------------------------------*/
/// SimuladorPartidos.c

///AXEL
void simularPartido (Partido *partidoAsimular);
void simularPartidoArreglado (Partido  *partidoAsimular, char equipoASimular1[], char equipoASimular2[], int clasifica1, int clasifica2); /// para los casos en los que el usuario quiera que un equipo clasifique o no .
void simularFaseDeGrupos (GrupoPartido arrayPartidosGrupos[], Grupo arrayEquiposGrupos[], nodoEquipo *listaEquipos);  ///simula fase de grupos aleatoriamente
void simulaGrupo (nodoPartido *partidosGrupo);  ///funcion primaria. Simula grupo aleatoriamente
void simulaGrupoArreglado (nodoPartido *partidosGrupo, char equipoASimular1[], char equipoASimular2[], int clasifica1, int clasifica2); ///simula un grupo con resultado arreglado
int ChequearFaseDeGrupo (nodoEquipo *listaEquipos); ///chequea que todos los equipos hayan terminado la fase de grupos
int verificarSiEstaEquipoEnGrupo (nodoGrupoEquipo *listaEquiposGrupo, char equipoBuscado[]);

///mati
Equipo* retornarPrimeroDelGrupo(nodoGrupoEquipo* listaEquipo);
Equipo* retornarSegundoDelGrupo(nodoGrupoEquipo* listaEquipo, Equipo* primero);
nodoPartido* crearNodoPartido(Equipo* uno, Equipo* dos);
void insertarPartidoOctavos(nodoPartido** listaPartidos, nodoPartido* partidin);  ///octavos
void pasarGanadoresAPlayoffOcatvos(Grupo arrayEquiposGrupos[], fase arrayFase[]);///arraygrupo FASE DE GRUPO  arrayFase PLAYOFFS
Equipo* vencedor(Partido match);///RETORNA EL EQUIPO GANADOR DEL PARTIDO
void pasarEquiposACuartos(nodoPartido* lista, nodoPartido** listaCuartos);///la "lista" es de octavos
void pasarGanadoresACuartos(fase arrayFase[]);
void pasarEquiposASemis(nodoPartido* listaCuartos, nodoPartido** listaSemis);
Equipo* perdedor(Partido match);///RETORNA EL EQUIPO PERDEDOR DEL PARTIDO
void pasarEquiposATercerPuesto(nodoPartido* listaSemis, nodoPartido** listaTercerPuesto);
void pasarEquiposAFinal(nodoPartido* listaSemis, nodoPartido** listaFinal);
void pasarGanadoresAFinal(fase arrayFase[]);
void jugarFinal (fase arrayFase[]);
void pasarGanadorYSegundoPuesto (nodoPartido * listaFinal);

#endif // DECLARACIONES_FUNCIONES_H_INCLUDED
