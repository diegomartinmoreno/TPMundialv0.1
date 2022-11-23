#include "declaraciones_variables.h"
#include "declaraciones_funciones.h"

int main()
{
    Grupo arrayGrupoEquipos[TAM_MAX_GRUPOS];
    GrupoPartido arrayGrupoPartidos[TAM_MAX_GRUPOS];
    fase arrayFase[4];
    traerDesdeBaseArrayGrupo(arrayGrupoEquipos);
   /// traerDesdeBaseArrayPartidos(arrayGrupoPartidos);
    iniciarMenuPrincipal(arrayGrupoPartidos, arrayFase, arrayGrupoEquipos);
    system("pause");
    system("cls");
    return 0;
}




