#include "declaraciones_variables.h"
#include "declaraciones_funciones.h"

int main()
{
    Grupo arrayGrupoEquipos[TAM_MAX_GRUPOS];
    GrupoPartido arrayGrupoPartidos[100];
    fase arrayFase[4];
    traerDesdeBaseArrayGrupo(arrayGrupoEquipos);
    iniciarMenuPrincipal(arrayGrupoPartidos, arrayFase, arrayGrupoEquipos);
    system("pause");
    system("cls");
    return 0;
}



