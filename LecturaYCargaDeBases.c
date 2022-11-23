#include "declaraciones_variables.h"
#include "declaraciones_funciones.h"

/*----------------------------------------*/

///   Explicación de variables:
/// GrupoPartido arrayPartidosGrupos[] = Contiene un arreglo de listas de los PARTIDOS de fase de grupos.
/// fase arrayFase[] = Contiene un arreglo de listas con los PARTIDOS de cada fase PlayOffs. 0=Octavos, 4=Final.
/// Grupo arrayEquiposGrupos[] = Contiene un arreglo de listas de los EQUIPOS de cada grupo y sus estadísticas.

/*----------------------------------------*/

/// INICIO de codigo para crear y levantar BaseArrayGrupo.bin (EQUIPOS)

void inicializarEquipo(Equipo *nuevo){
    strcpy(nuevo->nomEquipo, "NO");
    nuevo->mp=0;
    nuevo->ga=0;
    nuevo->gf=0;
    nuevo->loss=0;
    nuevo->win=0;
}


void crearNuevaBaseGrupo(){ /// Crear base de datos de grupos A, B ... H. ¡¡Para primera ejecucion!!

    /// Nota: Teniendo en cuenta que cada grupo SIEMPRE tiene < 4 > equipos. El formato de la base de datos es:
    /// [char grupo1][Equipo Equipo 1.1][Equipo Equipo 1.2]... [char grupo2][Equipo Equipo 2.1]....

    FILE *fp=NULL;
    Grupo auxiliarArrayGrupo[TAM_MAX_GRUPOS];
    nodoEquipo *seguidor=NULL;
    nodoEquipo *anterior=NULL;
    char letraGrupoAux;
    char idGrupos[TAM_MAX_GRUPOS]= {'A', 'B', 'C', 'D', 'E', 'F','G', 'H'};
    fp=fopen("./BaseArrayGrupo.bin", "w");

    for (int i=0; i<TAM_MAX_GRUPOS; i++){      /// para cada grupo de equipos.

        system("@cls||clear");
        printf("\nInicio de carga de equipos grupo %c\n", idGrupos[i]);
        auxiliarArrayGrupo[i].equipos=malloc(sizeof(nodoEquipo));
        seguidor= auxiliarArrayGrupo[i].equipos;
        auxiliarArrayGrupo[i].letra=idGrupos[i];
        letraGrupoAux=idGrupos[i];
        fwrite(&letraGrupoAux, sizeof(char), 1, fp);
        for (int j=0; j<TAM_MAX_GRUPO; j++){            /// para cada equipo individual.
            printf("|--- Ingrese nombre del equipo:\n");
            inicializarEquipo(&seguidor->equipo);
            fflush(stdin);
            //scanf("%s", seguidor->equipo.nomEquipo);
            gets(seguidor->equipo.nomEquipo);
            anterior=seguidor;
            seguidor->siguiente=malloc(sizeof(nodoEquipo));
            seguidor=seguidor->siguiente;
            anterior->siguiente=seguidor;
            Equipo auxEquipo;
            fwrite(&anterior->equipo, sizeof(Equipo), 1, fp); ///verificar
        }

        free (anterior->siguiente);
        anterior->siguiente=NULL;
    }
    fclose(fp);
}


//FUNCION DE ABAJO NO ERA NECESARIA, SEGUN CONSIGNA TODOS LOS PARTIDOS SE SIMULAN.
/*
void persistirBaseGrupo(Grupo arrayGrupo[]){ /// Persiste la estructura de grupos de equipos entre distintas ejecuciones del programa.
    FILE *fp=NULL;
    fp=fopen("./BaseArrayGrupo.bin", "w");
    nodoEquipo *seguidor=NULL;
    nodoEquipo *anterior=NULL;
    for (int i=0; i<TAM_MAX_GRUPOS; i++){
        fwrite(arrayGrupo[i].letra, sizeof(char), 1, fp);
        seguidor=arrayGrupo[i].equipos;
        while (seguidor){
            fwrite(&seguidor->equipo, sizeof(Equipo), 1, fp);
            seguidor=seguidor->siguiente;
        }
    }
}
*/

void traerDesdeBaseArrayGrupo (Grupo arrayGrupo[]){
    FILE *fp=NULL;
    nodoEquipo *seguidor=NULL;
    nodoEquipo *anterior=NULL;
    Grupo auxiliarGrupo;
    char letraGrupoAux;
    fp=fopen("./BaseArrayGrupo.bin", "r");
    if (fp){
        for (int i=0; i<TAM_MAX_GRUPOS; i++){
            arrayGrupo[i].equipos=malloc(sizeof(nodoEquipo));
            seguidor=arrayGrupo[i].equipos;
            fread(&letraGrupoAux, sizeof(char), 1, fp);
            arrayGrupo[i].letra=letraGrupoAux;
            for (int j=0; j<TAM_MAX_GRUPO; j++){
                fread(&seguidor->equipo, sizeof(Equipo), 1, fp);
                anterior=seguidor;
                seguidor->siguiente=malloc(sizeof(nodoEquipo));
                seguidor=seguidor->siguiente;
            }
            free (anterior->siguiente);
            anterior->siguiente=NULL;
        }
    }else{
        puts("No se pudo acceder a la base de datos de grupos de EQUIPOS.");
    }
    fclose(fp);
}

/// FIN de codigo para crear y levantar BaseArrayGrupo.bin

/*----------------------------------------*/

/// INICIO de codigo para crear y levantar BaseArrayPartidos.bin

void crearArrayGrupoPartido(){ /// Crear base de datos de partidos de cada grupo. Para primera ejecucion.
    FILE *fp=NULL;
    fp=fopen("./BaseArrayPartidos.bin", "w");
    partidoArchivo guardar;
    char flag='n';

    /// Nota: La base de datos guarda todos los PARTIDOS en estructuras partidoArchivo.
    /// donde: < int fecha=DDMM > y < int fase=-1 > significa fase de grupos.

    do{
    printf("Ingresar fecha (Solo numeros, formato DDMM):\n");
    fflush(stdin);
    scanf("%i", &guardar.fecha);
    printf("Ingresar letra del grupo:\n");
    fflush(stdin);
    scanf("%c", &guardar.grupo);
    guardar.grupo=toupper(guardar.grupo);
    printf("Ingresar nombre del equipo 1:");
    fflush(stdin);
    gets(&guardar.nomEquipo1);
    printf("VS.");
    printf("Ingresar nombre del equipo 2:");
    fflush(stdin);
    gets(&guardar.nomEquipo2);
    fwrite(&guardar, sizeof(partidoArchivo),1,fp);
    printf("\nDesea cargar otro partido? S/N\n");
    fflush(stdin);
    scanf("%c", &flag);
    flag=tolower(flag);
    }while (flag=='s');

    fclose(fp);
}

void inicializarPartido(Partido *nuevo){
    /// Nota: Dentro de la estructura Partido, el valor -1 (int) o 'NO' (string) representa el estado de variable no asignada aun.
    ///strcpy(nuevo->equipo1->nomEquipo, "NO");
    ///strcpy(&(nuevo->equipo2->nomEquipo), "NO");
    nuevo->fecha=-1;
    nuevo->golesEq1=-1;
    nuevo->golesEq2=-1;
    nuevo->id=-1;
    nuevo->penales1=-1;
    nuevo->penales2=-1;
}

void insertarNodoPartido (int grupo, GrupoPartido arrayGrupoPartidos[], nodoPartido *insertar){ ///Agrego al final de la lista de partidos de ese grupo.
    nodoPartido *seguidor;
    nodoPartido *anterior;
    seguidor=arrayGrupoPartidos[grupo].partidos;
    if (seguidor){
        anterior=seguidor;
        while (seguidor->siguiente){
            anterior=seguidor;
            seguidor=seguidor->siguiente;
        }
        anterior->siguiente=insertar;
    }
}

void traerDesdeBaseArrayPartidos(GrupoPartido arrayGrupoPartidos[]) {
    FILE *fp=NULL;
    nodoPartido *nuevo;
    nodoPartido *anterior;
    partidoArchivo lectura;
    char idGrupos[TAM_MAX_GRUPOS]= {'A', 'B', 'C', 'D', 'E', 'F','G', 'H'};
    fp=fopen("./BaseArrayPartidos.bin", "r"); /// Por consigna, solo contiene partidos de fase de grupos, ya que el resto se simula.
    while (fread(&lectura, sizeof(partidoArchivo),1,fp)){
        nuevo=malloc(sizeof(nodoPartido));
        inicializarPartido(&nuevo->partido);
        strcpy(nuevo->partido.equipo1,lectura.nomEquipo1);
        strcpy(nuevo->partido.equipo2,lectura.nomEquipo2);
        nuevo->partido.fecha=lectura.fecha;
        nuevo->partido.penales2=1;
        nuevo->siguiente=NULL;
            switch (lectura.grupo){ /// Agrega el partido en el grupo correspondiente.
            case 'A':
                insertarNodoPartido (0, arrayGrupoPartidos, nuevo);
            break;
            case 'B':
                insertarNodoPartido (1, arrayGrupoPartidos, nuevo);
            break;
            case 'C':
                insertarNodoPartido (2, arrayGrupoPartidos, nuevo);
            break;
            case 'D':
                insertarNodoPartido (3, arrayGrupoPartidos, nuevo);
            break;
            case 'E':
                insertarNodoPartido (4, arrayGrupoPartidos, nuevo);
            break;
            case 'F':
                insertarNodoPartido (5, arrayGrupoPartidos, nuevo);
            break;
            case 'G':
                insertarNodoPartido (6, arrayGrupoPartidos, nuevo);
            break;
            case 'H':
                insertarNodoPartido (7, arrayGrupoPartidos, nuevo);
            break;
            default:
                printf("Error al leer archivo de partidos.");
        }
    }
    fclose(fp);
}

/// FIN de codigo para crear y levantar BaseArrayPartidos.bin

/*----------------------------------------*/
