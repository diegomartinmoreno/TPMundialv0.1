#include "declaraciones_variables.h"
#include "declaraciones_funciones.h"

int main()
{
    nodoEquipo *listaEquipos;
    Grupo arrayGrupoEquipos[TAM_MAX_GRUPOS];
    GrupoPartido arrayGrupoPartidos[TAM_MAX_GRUPOS];
    fase arrayFase[4];
    listaEquipos=cargarListaEquipos(listaEquipos);
    vincularAListaArrayGruposEquipos(arrayGrupoEquipos,listaEquipos);
    inicializarArrayGrupoPartidos(arrayGrupoPartidos);
    traerDesdeBaseArrayPartidos(arrayGrupoPartidos, listaEquipos);
    ///verificacionImprimirListaEquipos(listaEquipos); /// SOLO PARA DEBUG
    ///system("pause");
    /// traerDesdeBaseArrayPartidos(arrayGrupoPartidos);
    iniciarMenuPrincipal(arrayGrupoPartidos, arrayFase, arrayGrupoEquipos, listaEquipos);
    system("pause");
    system("cls");
    return 0;
}




