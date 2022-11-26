#include "declaraciones_variables.h"
#include "declaraciones_funciones.h"

int main()
{
    nodoEquipo *listaEquipos=NULL;
    Grupo arrayEquiposGrupos[TAM_MAX_GRUPOS];
    GrupoPartido arrayPartidosGrupos[TAM_MAX_GRUPOS];
    fase arrayFase[4];
    puts("Cargando bases de datos...\n");
    listaEquipos=leerListaEquipos();
    inicializarArrayGrupoEquipos(arrayEquiposGrupos);
    vincularAListaArrayGruposEquipos(arrayEquiposGrupos,listaEquipos);
    leerYVincularBaseArrayPartidos(arrayPartidosGrupos, listaEquipos);
    system("pause");

    /// SOLO PARA DEBUG
    /*
    ///verificacionImprimirListaEquipos(listaEquipos);
    ///system("pause");
    /// traerDesdeBaseArrayPartidos(arrayGrupoPartidos);
    */

    iniciarMenuPrincipal(arrayPartidosGrupos, arrayFase, arrayEquiposGrupos, listaEquipos);
    system("pause");
    system("cls");
    return 0;
}




