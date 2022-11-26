#include "declaraciones_variables.h"
#include "declaraciones_funciones.h"

void subMenuBasesDeDatos(GrupoPartido arrayPartidosGrupos[], fase arrayFase[], Grupo arrayEquiposGrupos[], nodoEquipo *listaEquipos){
    char input;
    char flag='n';
    do {
            system("@cls||clear");
            imprimirCabeceraMenuPrincipal();
            imprimirSubMenuBases();
            fflush(stdin);
            input=getc(stdin);
            switch (input){
            case '1': /// CARGAR DEFAULT EQUIPOS
                flag='n';
            break;
            case '2': /// CARGAR DEFAULT PARTIDOS
                flag='n';
            break;
            case '3': /// 3) Reiniciar bases de datos de EQUIPOS GRUPOS.
                flag='n';
                printf("\n Seguro que desea reiniciar la base de datos de EQUIPOS? Debera ingresar todos los equipos nuevamente. S/N\n");
                fflush(stdin);
                scanf("%c", &flag);
                flag=tolower(flag);
                if (flag=='s'){
                    crearNuevaBaseGrupo(arrayEquiposGrupos);
                    cargarListaEquipos(listaEquipos);
                    vincularAListaArrayGruposEquipos(arrayEquiposGrupos,listaEquipos);
                    imprimirArrayGrupo(arrayEquiposGrupos);
                    system("Pause");
                }
                flag='n';
            break;
            case '4': /// 4) Reiniciar bases de datos de PARTIDOS GRUPOS.
                flag='n';
                printf("\n Seguro que desea reiniciar la base de datos de PARTIDOS? Debera ingresar todos los partidos nuevamente. S/N\n");
                fflush(stdin);
                scanf("%c", &flag);
                flag=tolower(flag);
                cargarListaEquipos(listaEquipos);
                if (flag=='s'){
                        crearArrayGrupoPartido(listaEquipos);
                }
                traerDesdeBaseArrayPartidos(arrayPartidosGrupos,listaEquipos);
                system("@cls||clear");
                puts("La base de datos de Partidos contiene ahora lo siguiente:\n");
                imprimirArrayGrupoPartidos(arrayPartidosGrupos);
                system("Pause");
                flag='n';
            break;
            case '5': /// CARGAR DEFAULT PARTIDOS
                flag='n';
                printf("\n Volver al menu principal? S/N\n");
                fflush(stdin);
                scanf("%c", &flag);
                flag=tolower(flag);
            break;
            default:
                puts("\nOpcion ingresada no valida.\n");
            }
    }while (flag!='s');

}

char menuPrincipal (char input, GrupoPartido arrayPartidosGrupos[], fase arrayFase[], Grupo arrayEquiposGrupos[], nodoEquipo *listaEquipos){ ///nodoEquipo *listaEquipos
    char flag='n';
    switch (input){
    case '1': /// 1) Mostrar Grupos.
       imprimirArrayGrupo(arrayEquiposGrupos);
       system("Pause");
    break;
    case '2': /// 2) Mostrar Partidos fase Grupos.
        imprimirArrayGrupoPartidos(arrayPartidosGrupos);
        system("Pause");
    break;
    case '3': /// 3) Mostrar Partidos Playoffs.
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
    case '5': /// 5) Ingresar al submenu de bases de datos.
        subMenuBasesDeDatos(arrayPartidosGrupos, arrayEquiposGrupos, arrayFase, listaEquipos);
    break;
    case '6': /// 6) Salir.
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

void iniciarMenuPrincipal(GrupoPartido arrayPartidosGrupos[], fase arrayFase[], Grupo arrayEquiposGrupos[], nodoEquipo *listaEquipos){
    char input=0;
    char flag='n';
    do{
        system("@cls||clear");
        imprimirCabeceraMenuPrincipal();
        imprimirMenuPrincipal();
        fflush(stdin);
        input=getc(stdin);
        flag=menuPrincipal(input, arrayPartidosGrupos, arrayFase, arrayEquiposGrupos, listaEquipos);
    }while (flag!='s');

}
