#include "declaraciones_variables.h"
#include "declaraciones_funciones.h"

char menuPrincipal (char input, GrupoPartido arrayPartidosGrupos[], fase arrayFase[], Grupo arrayEquiposGrupos[]){
    char flag='n';
    switch (input){
    case '1': /// 1) Mostrar Equipos.
        ///verEquiposLista(listaEquipos);
    break;
    case '2': /// 2) Mostrar Grupos.
       imprimirArrayGrupo(arrayEquiposGrupos);
    break;
    case '3': /// 3) Mostrar Partidos fase Grupos.
        imprimirArrayGrupoPartidos(arrayPartidosGrupos);
    break;
    case '4': /// 4) Mostrar Partidos Playoffs.
        /// mostrarPartidosPlayoffs (listaPPlayoffs);
    break;
    case '5': /// 5) Simular Partidos.
        /// simular un partido o un conjunto de partidos (grupo o fase) o todo el mundial.
    break;
    case '6': /// 6) Reiniciar bases de datos de EQUIPOS GRUPOS.
            flag='n';
            printf("\n Seguro que desea reiniciar la base de datos de EQUIPOS? Debera ingresar todos los equipos nuevamente. S/N\n");
            fflush(stdin);
            scanf("%c", &flag);
            flag=tolower(flag);
            if (flag=='s'){
                crearNuevaBaseGrupo(arrayEquiposGrupos);
                traerDesdeBaseArrayGrupo(arrayEquiposGrupos);
                imprimirArrayGrupo(arrayEquiposGrupos);
            }
            flag='n';
    break;
    case '7': /// 7) Reiniciar base de datos de PARTIDOS GRUPOS.
            flag='n';
            printf("\n Seguro que desea reiniciar la base de datos de PARTIDOS? Debera ingresar todos los partidos nuevamente. S/N\n");
            fflush(stdin);
            scanf("%c", &flag);
            flag=tolower(flag);
            if (flag=='s'){
                    crearArrayGrupoPartido();
            }
            flag='n';
    break;
    case '8': /// 8) Salir.
            flag='n';
            printf("\n Al salir se eliminaran los partidos simulados en esta sesion. Desea continuar? S/N\n");
            fflush(stdin);
            scanf("%c", &flag);
            flag=tolower(flag);
    break;
    default: printf ("Volviendo al menu...\n");
    system("pause");
    }
    return flag;
}

void iniciarMenuPrincipal(GrupoPartido arrayPartidosGrupos[], fase arrayFase[], Grupo arrayEquiposGrupos[]){
    char input=0;
    char flag='n';
    do{
        system("@cls||clear");
        imprimirCabeceraMenuPrincipal();
        imprimirMenuPrincipal();
        fflush(stdin);
        input=getc(stdin);
        flag=menuPrincipal(input, arrayPartidosGrupos, arrayFase, arrayEquiposGrupos);
    }while (flag!='s');

}

void persistirVariablesYSalir(){

}
