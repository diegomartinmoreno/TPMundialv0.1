#include "declaraciones_variables.h"
#include "declaraciones_funciones.h"

char menuPrincipal (char input, GrupoPartido arrayPartidosGrupos[], fase arrayFase[], Grupo arrayEquiposGrupos[]){ ///nodoEquipo *listaEquipos
    char flag='n';
    switch (input){
    case '1': /// 1) Mostrar Grupos. DIEGO
       imprimirArrayGrupo(arrayEquiposGrupos);
    break;
    case '2': /// 2) Mostrar Partidos fase Grupos. DIEGO
        imprimirArrayGrupoPartidos(arrayPartidosGrupos);
    break;
    case '3': /// 3) Mostrar Partidos Playoffs. DIEGO
        /// mostrarPartidosPlayoffs (arrayFase);
    break;
    case '4': /// 4) Simular Partidos.
        /// FALTA ASIGNAR QUIEN HACE:
        /// FUNCION (S) simularFaseGrupo (arrayPartidosGrupos, arrayEquiposGrupos) /// DEBE PERMITIR SELECCIONAR UN EQUIPO QUE CLASIFIQUE SIN AZAR.
        /// FUNCION simularUnPartido (Partido *partidoASimular); /// DEBE PODER REUTILIZARSE PARA PLAYOFFS Y GRUPOS
        /// FUNCION simular un partido o un conjunto de partidos (grupo o fase) o todo el mundial.
        /// FUNCION que compruebe si se jugaron todos los partidos de fase de grupos. (en arrayEquiposGrupos, todos los MP-matchs played deben ser=3);
        /// FUNCION que tome los primeros dos ganadores de cada grupo del arrayEquiposGrupos y los inserte en arrayFase[0];
        /// FUNCION que simule todos los playoffs.
        /// ----
    break;

    case '5': /// 5) Agregar un partido.
        /// Agregar un solo partido a la estructura de GrupoPartido ya existente. DIEGO
    break;
    case '6': /// 6) Reiniciar bases de datos de EQUIPOS GRUPOS. DIEGO
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
    case '7': /// 7) Reiniciar base de datos de PARTIDOS GRUPOS. DIEGO
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
    case '8': /// 8) Salir. DIEGO
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
