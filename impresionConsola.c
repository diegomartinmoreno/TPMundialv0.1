#include "declaraciones_variables.h"
#include "declaraciones_funciones.h"

/*----------------------------------------*/
/// INICIO DE IMPRESIONES DE MENU PRINCIPAL.

void imprimirCabeceraMenuPrincipal(){
    printf("             ___\n");
    printf("         _.-'___'-._\n");
    printf("       .'--.`   `.--'. \n");
    printf("      /.'   \\   /   `.\\ \n");
    printf("     | /'-._/```\_.-'\\  | \n");
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
    printf("\n |-| 1) Cargar valores por defecto para base de EQUIPOS, fase de grupos.");
    printf("\n |-| 2) Cargar valores por defecto para base de PARTIDOS, fase de grupos.");
    printf("\n |-| 3) Reiniciar base de datos de EQUIPOS, fase de grupos. //FUNCIONA");
    printf("\n |-| 4) Reiniciar base de datos de PARTIDOS, fase de grupos. //FUNCIONA");
    printf("\n |-| 5) Volver al menu principal.\n");
}

/// FIN DE IMPRESIONES DE MENU PRINCIPAL.

/*----------------------------------------*/

/// INICIO DE IMPRESIONES DE GRUPOS DE EQUIPOS.

void imprimirUnSoloGrupo (nodoGrupoEquipo *listaEquiposGrupo){
    nodoGrupoEquipo *seguidor=NULL;
    seguidor=listaEquiposGrupo;
    while (seguidor){
        printf ("\n |-| >> Seleccion de: %s", seguidor->equipo->nomEquipo);
        printf("\n |-| MP: %i || Win: %i || Loss: %i || GF: %i || GA: %i", seguidor->equipo->mp, seguidor->equipo->win, seguidor->equipo->loss, seguidor->equipo->gf, seguidor->equipo->ga);
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
}
/// FIN DE IMPRESIONES DE GRUPOS DE EQUIPOS.

/*----------------------------------------*/

/// INICIO DE IMPRESIONES DE PARTIDOS.


void imprimirUnSoloPartido(Partido imprimir, int mostrarResultados){ /// mostrarResultados=1 SI muestra resultados. mostrarResultados=0 NO muestra resultados.
    div_t dia=div(imprimir.fecha, 100);
    int mes=imprimir.fecha%100;
    if(mostrarResultados){
        if (imprimir.golesEq1<=imprimir.golesEq2){ /// Gano equipo 1 o empataron.
            printf ("PARTIDO: %i %s Vs. %i %s  ||  Fecha: %i.", imprimir.golesEq1, imprimir.equipo1, imprimir.golesEq2, imprimir.equipo2, imprimir.fecha);
        }
        if (imprimir.golesEq1>imprimir.golesEq2){ /// Gano equipo 2.
            printf ("PARTIDO: %i %s Vs. %i %s  ||  Fecha: %i.", imprimir.golesEq2, imprimir.equipo2, imprimir.golesEq1, imprimir.equipo1, imprimir.fecha);
        }
        if (imprimir.golesEq1==imprimir.golesEq2&&imprimir.penales2){ /// desempate por penales.
            printf ("PARTIDO: %i %s(%i) Vs. %i %s(%i)  ||  Fecha: %i.", imprimir.golesEq1, imprimir.equipo1, imprimir.penales1, imprimir.golesEq2, imprimir.equipo2, imprimir.penales2, imprimir.fecha);
        }
    }else{ /// partido no jugado/simulado aun.
        printf ("PARTIDO: %s Vs. %s || Fecha: %i/%i || INDEFINIDO.\n", imprimir.equipo1, imprimir.equipo2, dia, mes);
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
    }
}
/// FIN DE IMPRESIONES DE PARTIDOS.

/*----------------------------------------*/

