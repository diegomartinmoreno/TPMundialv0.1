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

///AXEL
void simularPartido (Partido partidoAsimular);
void simularPartidoArreglado (Partido  partidoAsimular, char equipoASimular[], int clasifica); /// para los casos en los que el usuario quiera que un equipo clasifique o no .
void simularFaseDeGrupos (GrupoPartido arrayPartidosGrupos[]);  ///simula fase de grupos aleatoriamente
void simulaGrupo (nodoPartido * partidosGrupo);  ///funcion primaria. Simula grupo aleatoriamente
void simulaGrupoArreglado (nodoPartido * partidosGrupo, char equipoASimular[], int clasifica); ///simula un grupo con resultado arreglado
int ChequearFaseDeGrupo (nodoEquipo * listaEquipos); ///chequea que todos los equipos hayan terminado la fase de grupos


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
