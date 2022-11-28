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
                printf("\n Seguro que cargar los valores por defecto a la base de datos de Equipos? Eliminara los datos actuales. Reiniciara simulacion. S/N\n");
                fflush(stdin);
                scanf("%c", &flag);
                flag=tolower(flag);
                if (flag=='s'){
                    cargarDefaultBaseGrupo();
                    listaEquipos=leerListaEquipos();
                    inicializarArrayGrupoEquipos(arrayEquiposGrupos);
                    vincularAListaArrayGruposEquipos(arrayEquiposGrupos, listaEquipos);
                    leerYVincularBaseArrayPartidos(arrayPartidosGrupos, listaEquipos);
                    imprimirArrayGrupo(arrayEquiposGrupos);
                    system("Pause");
                }
                flag='n';
            break;
            case '2': /// CARGAR DEFAULT PARTIDOS
                flag='n';
                printf("\n Seguro que cargar los valores por defecto a la base de datos de Partidos? Eliminara los datos actuales. Reiniciara simulacion. S/N\n");
                fflush(stdin);
                scanf("%c", &flag);
                flag=tolower(flag);
                if (flag=='s'){
                    cargarDefaultBasePartido();
                    listaEquipos=leerListaEquipos();
                    inicializarArrayGrupoEquipos(arrayEquiposGrupos);
                    vincularAListaArrayGruposEquipos(arrayEquiposGrupos,listaEquipos);
                    leerYVincularBaseArrayPartidos(arrayPartidosGrupos, listaEquipos);
                    puts("Base de Partidos cargada con valores por defecto.\n");
                    imprimirArrayGrupoPartidos(arrayPartidosGrupos);
                    system("Pause");
                }
                flag='n';
            break;
            case '3': /// 3) Reiniciar bases de datos de EQUIPOS GRUPOS.
                flag='n';
                printf("\n Seguro que desea reiniciar la base de datos de EQUIPOS? Debera ingresar todos los equipos nuevamente. Reiniciara simulacion. S/N\n");
                fflush(stdin);
                scanf("%c", &flag);
                flag=tolower(flag);
                if (flag=='s'){
                    crearNuevaBaseGrupo(arrayEquiposGrupos);
                    listaEquipos=leerListaEquipos();
                    inicializarArrayGrupoEquipos(arrayEquiposGrupos);
                    vincularAListaArrayGruposEquipos(arrayEquiposGrupos,listaEquipos);
                    leerYVincularBaseArrayPartidos(arrayPartidosGrupos, listaEquipos);
                    imprimirArrayGrupo(arrayEquiposGrupos);
                    system("Pause");
                }
                flag='n';
            break;
            case '4': /// 4) Reiniciar bases de datos de PARTIDOS GRUPOS.
                reiniciarBasePartidos();
                listaEquipos=leerListaEquipos();
                inicializarArrayGrupoEquipos(arrayEquiposGrupos);
                vincularAListaArrayGruposEquipos(arrayEquiposGrupos,listaEquipos);
                leerYVincularBaseArrayPartidos(arrayPartidosGrupos, listaEquipos);
                puts("La base de datos de partidos fue reiniciada, necesita cargar todos los partidos nuevamente. Reiniciara simulacion.\n");
                system("Pause");
            break;
            case '5': /// 5) Agregar a bases de datos de PARTIDOS GRUPOS.
                flag='n';
                printf("\n Agregar partidos? Reiniciara simulacion. S/N\n");
                fflush(stdin);
                scanf("%c", &flag);
                flag=tolower(flag);
                if (flag=='s'){
                        listaEquipos=leerListaEquipos();
                        inicializarArrayGrupoEquipos(arrayEquiposGrupos);
                        vincularAListaArrayGruposEquipos(arrayEquiposGrupos,listaEquipos);
                        leerYVincularBaseArrayPartidos(arrayPartidosGrupos, listaEquipos);

                        agregarABaseArrayGrupoPartido(listaEquipos);

                        listaEquipos=leerListaEquipos();
                        inicializarArrayGrupoEquipos(arrayEquiposGrupos);
                        vincularAListaArrayGruposEquipos(arrayEquiposGrupos,listaEquipos);
                        leerYVincularBaseArrayPartidos(arrayPartidosGrupos, listaEquipos);

                        system("@cls||clear");
                        puts("La base de datos de Partidos contiene ahora lo siguiente:\n");
                        imprimirArrayGrupoPartidos(arrayPartidosGrupos);
                        system("Pause");
                }
                flag='n';
            break;
            case '6': /// 6) VOLVER AL MENU PRINCIPAL
                flag='s';
            break;
            break;
            default:
                puts("\nOpcion ingresada no valida.\n");
            }
    }while (flag!='s');
}

char menuPrincipal (int *faseGruposYaSimulada, char input, GrupoPartido arrayPartidosGrupos[], fase arrayFase[], Grupo arrayEquiposGrupos[], nodoEquipo *listaEquipos){ ///nodoEquipo *listaEquipos
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
        if (*faseGruposYaSimulada==1){
            simularPlayoffs(arrayPartidosGrupos, listaEquipos, arrayEquiposGrupos, arrayFase);
        }else{
            printf("Debe simular la fase de grupos antes de iniciar los Playoffs.\n");
            system("Pause");
        }

    break;
    case '4': /// 4) Simular Partidos.

        flag='n';
        if (*faseGruposYaSimulada==0){
            printf("\n Iniciar simulacion de fase de grupos?S/N\n");
            fflush(stdin);
            scanf("%c", &flag);
            flag=tolower(flag);
            if (flag=='s'){
                system("@cls||clear");
                printf("\n>>>> INICIO DE SIMULACION DE PARTIDOS, FASE DE GRUPOS:\n\n");
                /// simulo con los arreglos inicializados, eliminando simulacion previa.
                simularFaseDeGrupos(arrayPartidosGrupos, arrayEquiposGrupos, listaEquipos);
                *faseGruposYaSimulada=1;
            }
            flag='n';
        }else{
            printf("\n\nLa fase de grupos ya fue simulada. Si desea volver a simularla, reinicie las bases de datos.\n\n");
            system("Pause");
        }
    break;
    case '5': /// 5) Ingresar al submenu de bases de datos.
        subMenuBasesDeDatos(arrayPartidosGrupos,arrayFase,arrayEquiposGrupos,listaEquipos); /// MODIFICO LAS BASES DE DATOS.
        /// LEVANTO LAS MODIFICACIONES HECHAS.
        listaEquipos=leerListaEquipos();
        inicializarArrayGrupoEquipos(arrayEquiposGrupos);
        vincularAListaArrayGruposEquipos(arrayEquiposGrupos,listaEquipos);
        leerYVincularBaseArrayPartidos(arrayPartidosGrupos, listaEquipos);
        *faseGruposYaSimulada=0;
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
    int faseGruposYaSimulada=0;
    do{
        system("@cls||clear");
        imprimirCabeceraMenuPrincipal();
        imprimirMenuPrincipal();
        fflush(stdin);
        input=getc(stdin);
        flag=menuPrincipal(&faseGruposYaSimulada, input, arrayPartidosGrupos, arrayFase, arrayEquiposGrupos, listaEquipos);
    }while (flag!='s');

}
