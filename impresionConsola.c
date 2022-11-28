#include "declaraciones_variables.h"
#include "declaraciones_funciones.h"

/*----------------------------------------*/
/// INICIO DE IMPRESIONES DE MENU PRINCIPAL.

void imprimirCabeceraMenuPrincipal(){
    printf("             ___\n");
    printf("         _.-'___'-._\n");
    printf("       .'--.`   `.--'. \n");
    printf("      /.'   \\   /   `.\\ \n");
    printf("     | /'-._/```\\_.-'\\  | \n");
    printf("     |/    |     |    \\| \n");
    printf("     | \\ .''-._.-''. / | \n");
    printf("      \\ |     |     | / \n");
    printf("       '.'._.-'-._.'.' \n");
    printf("         '-:_____;-' \n");
    printf("\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\" \n\n");
    printf(" |||  Simulador del Mundial ||| \n");
}

void imprimirMenuPrincipal(){
    printf("\n |-| 1) Mostrar Grupos. //FUNCIONA");
    printf("\n |-| 2) Mostrar Partidos Fase de Grupos. //FUNCIONA");
    printf("\n |-| 3) Mostrar Partidos PlayOffs.");
    printf("\n |-| 4) Simular Partidos.");
    printf("\n |-| 5) Submenu bases de datos //FUNCIONA");
    printf("\n |-| 6) Salir. //FUNCIONA\n");
}

void imprimirSubMenuBases(){
    printf("\n |-| 1) Cargar valores por defecto para base de EQUIPOS, fase de grupos. //FUNCIONA");
    printf("\n |-| 2) Cargar valores por defecto para base de PARTIDOS, fase de grupos. //FUNCIONA");
    printf("\n |-| 3) Reiniciar base de datos de EQUIPOS, fase de grupos. //FUNCIONA");
    printf("\n |-| 4) Reiniciar base de datos de PARTIDOS, fase de grupos. //FUNCIONA");
    printf("\n |-| 5) Agregar partido de fase de grupos. //FUNCIONA");
    printf("\n |-| 6) Volver al menu principal. //FUNCIONA\n");
}

/// FIN DE IMPRESIONES DE MENU PRINCIPAL.

/*----------------------------------------*/

/// INICIO DE IMPRESIONES DE GRUPOS DE EQUIPOS.

void imprimirUnSoloGrupo (nodoGrupoEquipo *listaEquiposGrupo){
    nodoGrupoEquipo *seguidor=NULL;
    seguidor=listaEquiposGrupo;
    while (seguidor){
        printf ("\n |-| >> Seleccion de: %s", seguidor->equipo->nomEquipo);
        printf("\n |-| MP: %i || Win: %i || Loss: %i || GF: %i || GA: %i || Pts: %i", seguidor->equipo->mp, seguidor->equipo->win, seguidor->equipo->loss, seguidor->equipo->gf, seguidor->equipo->ga, seguidor->equipo->pts);
        seguidor=seguidor->siguiente;
    }
}


void imprimirArrayGrupo (Grupo arrayGrupo[]){
    system("@cls||clear");
    printf("\nLISTA DE EQUIPOS FASE DE GRUPOS\n");
    for (int i=0; i<TAM_MAX_GRUPOS; i++){
        printf("\n\n |-| >>>> Lista de equipos del grupo %c", arrayGrupo[i].letra);
        imprimirUnSoloGrupo(arrayGrupo[i].equipos);
    }
    puts("\n\n");
}

/// FIN DE IMPRESIONES DE GRUPOS DE EQUIPOS.

/*----------------------------------------*/

/// INICIO DE IMPRESIONES DE PARTIDOS.


void imprimirUnSoloPartido(Partido imprimir, int mostrarResultados){ /// mostrarResultados=1 SI muestra resultados. mostrarResultados=0 NO muestra resultados.
    div_t dia_t= div(imprimir.fecha, 100);
    int dia=dia_t.quot; /// USANDO COCIENTE
    int mes= imprimir.fecha % 100;
    if(mostrarResultados){
        if (imprimir.golesEq1>=imprimir.golesEq2){ /// Gano equipo 1 o empataron.
            printf ("PARTIDO: %i %s Vs. %i %s  ||  Fecha: %i/%i.\n", imprimir.golesEq1, imprimir.equipo1->nomEquipo, imprimir.golesEq2, imprimir.equipo2->nomEquipo, dia, mes);
        }
        if (imprimir.golesEq1<imprimir.golesEq2){ /// Gano equipo 2.
            printf ("PARTIDO: %i %s Vs. %i %s  ||  Fecha: %i/%i.\n", imprimir.golesEq2, imprimir.equipo2->nomEquipo, imprimir.golesEq1, imprimir.equipo1->nomEquipo, dia, mes);
        }
        if (imprimir.golesEq1==imprimir.golesEq2&&imprimir.penales2){ /// desempate por penales.
            printf ("PARTIDO: %i %s(%i) Vs. %i %s(%i)  ||  Fecha: %i/%i.\n", imprimir.golesEq1, imprimir.equipo1->nomEquipo, imprimir.penales1, imprimir.golesEq2, imprimir.equipo2->nomEquipo, imprimir.penales2, dia, mes);
        }
    }else{ /// partido no jugado/simulado aun.
        printf ("PARTIDO: %s Vs. %s || Fecha: %i/%i || INDEFINIDO.\n", imprimir.equipo1->nomEquipo, imprimir.equipo2->nomEquipo, dia, mes);
    }
}

void imprimirArrayGrupoPartidos (GrupoPartido arrayGrupoPartidos[]){
    nodoPartido *seguidor;
    system("@cls||clear");
    for (int i=0; i<TAM_MAX_GRUPOS; i++){
        printf(">>>> Resultados del grupo %c\n", arrayGrupoPartidos[i].letra);
        seguidor= arrayGrupoPartidos[i].partidos;
        while (seguidor){
            if (seguidor->partido.golesEq1!=-1){ /// partido ya simulado.
                imprimirUnSoloPartido(seguidor->partido, 1);
            } else{ /// partido no simulado aun.
                imprimirUnSoloPartido(seguidor->partido, 0);
            }
            seguidor=seguidor->siguiente;
        }
        puts("\n");
    }
    puts("\n\n");
}
/// FIN DE IMPRESIONES DE PARTIDOS.

/*----------------------------------------*/

/// IMPRIMIR PLAYOFFS

/*
void imprimirPlayoffs (fase arrayFase[])
{
    Partido partidoActual;
    nodoPartido *seguidorOctavos=arrayFase[0].partidos;
    nodoPartido *seguidorCuartos=arrayFase[1].partidos;
    nodoPartido *seguidorSemis=arrayFase[2].partidos;

    printf("OCTAVOS              CUARTOS                 SEMIS                      FINAL                               CAMPEON\n");
    partidoActual=seguidorOctavos->partido;
    printf("%i(%i)%-20s---------\n", partidoActual.golesEq1, partidoActual.penales1, partidoActual.equipo1->nomEquipo); /// 1er partido octavos.
    printf("              |\n");
    partidoActual=seguidorCuartos->partido;
    printf("              |%i(%i)%-20s----------\n", partidoActual.golesEq1, partidoActual.penales1, partidoActual.equipo1->nomEquipo); /// 1er partido cuartos.
    printf("              |               |\n");
    printf("              |               |\n");
    printf("              |               |\n");
    partidoActual=seguidorOctavos->partido;
    seguidorOctavos=seguidorOctavos->siguiente;
    printf("%i(%i)%-20s---------                |\n", partidoActual.golesEq2, partidoActual.penales2, partidoActual.equipo2->nomEquipo); /// 1er partido octavos.
    partidoActual=arrayFase[3]->partidos->partido;
    printf("                              |%i(%i)%-20s---------------------\n",partidoActual.golesEq1, partidoActual.penales1, partidoActual.equipo1->nomEquipo); ///semifinal
    partidoActual=seguidorOctavos->partido;
    printf("%i(%i)%-20s---------                |                          |\n",partidoActual.golesEq1, partidoActual.penales1, partidoActual.equipo1->nomEquipo); /// 2do partido octavos
    printf("              |               |                          |\n");
    printf("              |               |                          |\n");
    partidoActual=seguidorCuartos->partido;
    seguidorCuartos=seguidorCuartos->siguiente;
    printf("              |%i(%i)%-20s----------                           |\n",partidoActual.golesEq2, partidoActual.penales2, partidoActual.equipo2->nomEquipo); /// 1er partido cuartos
    printf("              |                                          |\n");
    printf("              |                                          |\n");
    partidoActual=seguidorOctavos->partido;
    printf("%i(%i)%-20s---------                                           |\n",partidoActual.golesEq2, partidoActual.penales2, partidoActual.equipo2->nomEquipo);
    printf("              |                                          |%i(%i)%-20s------------------------\n");
    printf("              |                                          |                            |\n");
    printf("              |                                          |                            |\n");
    printf("              |%i(%i)%-20s----------                           |                            |\n");
    printf("              |               |                          |                            |\n");
    printf("              |               |                          |                            |\n");
    printf("              |               |                          |                            |\n");
    printf("%i(%i)%-20s---------                |                          |                            |\n");
    printf("                              |%i(%i)%-20s----------------------                            |\n");
    printf("%i(%i)%-20s---------                |                                                       |\n");
    printf("              |               |                                                       |\n");
    printf("              |               |                                                       |\n");
    printf("              |%i(%i)%-20s----------                                                        |\n");
    printf("              |                                                                       |\n");
    printf("              |                                                                       |\n");
    printf("%i(%i)%-20s---------                                                                        |\n");
    printf("                                                                                      |------- %-20s\n");
    printf("%-20s---------                                                                        |\n");
    printf("              |                                                                       |\n");
    printf("              |%-20s----------\                                                       |\n");
    printf("              |               |                                                       |\n");
    printf("              |               |                                                       |\n");
    printf("              |               |                                                       |\n");
    printf("%-20s---------                |                                                       |\n");
    printf("                              |%-20s---------------------                             |\n");
    printf("%-20s---------                |                          |                            |\n");
    printf("              |               |                          |                            |\n");
    printf("              |               |                          |                            |\n");
    printf("              |%-20s----------                           |                            |\n");
    printf("              |                                          |                            |\n");
    printf("              |                                          |                            |\n");
    printf("%-20s---------                                           |                            |\n");
    printf("              |                                          |%-20s------------------------\n");
    printf("              |                                          |  \n");
    printf("              |                                          |  \n");
    printf("              |%-20s----------                           |  \n");
    printf("              |               |                          |  \n");
    printf("              |               |                          |  \n");
    printf("              |               |                          |  \n");
    printf("%-20s---------                |                          |  \n");
    printf("                              |%-20s----------------------  \n");
    printf("%-20s---------                |    \n");
    printf("              |               |    \n");
    printf("              |               |    \n");
    printf("              |%-20s----------     \n");
    printf("              | \n");
    printf("              | \n");
    printf("%-20s---------  \n");
}
*/

void imprimirPlayoffs(fase arrayFase[]){
    Partido partidoActual;
    nodoPartido *seguidorOctavos=arrayFase[0].partidos;
    nodoPartido *seguidorCuartos=arrayFase[1].partidos;
    nodoPartido *seguidorSemis=arrayFase[2].partidos;
    int i=0;

    printf("\nOCTAVOS\n");
    for (i=0; i<8; i++){
        partidoActual=seguidorOctavos->partido;
        printf("%i(%i)%s vs. ", partidoActual.golesEq1, partidoActual.penales1, partidoActual.equipo1->nomEquipo);
        printf("%i(%i)%s", partidoActual.golesEq2, partidoActual.penales2, partidoActual.equipo2->nomEquipo);
        seguidorOctavos=seguidorOctavos->siguiente;
        printf("\n");
    }

    printf("\nCUARTOS\n");
    for ( i=0; i<4; i++){
        partidoActual=seguidorCuartos->partido;
        printf("%i(%i)%s vs. ", partidoActual.golesEq1, partidoActual.penales1, partidoActual.equipo1->nomEquipo);
        printf("%i(%i)%s", partidoActual.golesEq2, partidoActual.penales2, partidoActual.equipo2->nomEquipo);
        seguidorCuartos=seguidorCuartos->siguiente;
        printf("\n");
    }
    printf("\n>>SEMIFINALES\n");

    for ( i=0; i<2; i++){
        partidoActual=seguidorSemis->partido;
        printf("%i(%i)%s vs. ", partidoActual.golesEq1, partidoActual.penales1, partidoActual.equipo1->nomEquipo);
        printf("%i(%i)%s", partidoActual.golesEq2, partidoActual.penales2, partidoActual.equipo2->nomEquipo);
        seguidorSemis=seguidorSemis->siguiente;
        printf("\n");
    }
    printf("\n>>>>TERCER PUESTO\n");
    partidoActual=arrayFase[3].partidos->partido;
    printf("%i(%i)%s vs. ", partidoActual.golesEq1, partidoActual.penales1, partidoActual.equipo1->nomEquipo);
    printf("%i(%i)%s", partidoActual.golesEq2, partidoActual.penales2, partidoActual.equipo2->nomEquipo);

    printf("\n\n>>>>>>FINAL\n");
    partidoActual=arrayFase[4].partidos->partido;
    printf("%i(%i)%s vs. ", partidoActual.golesEq1, partidoActual.penales1, partidoActual.equipo1->nomEquipo);
    printf("%i(%i)%s", partidoActual.golesEq2, partidoActual.penales2, partidoActual.equipo2->nomEquipo);
    printf("\n\n");
    system("Pause");
}
