#include "declaraciones_variables.h"
#include "declaraciones_funciones.h"

/*----------------------------------------*/

///   Explicación de variables:
/// GrupoPartido arrayPartidosGrupos[] = Contiene un arreglo de listas de los PARTIDOS de fase de grupos.
/// fase arrayFase[] = Contiene un arreglo de listas con los PARTIDOS de cada fase PlayOffs. 0=Octavos, 4=Final.
/// Grupo arrayEquiposGrupos[] = Contiene un arreglo de listas de los EQUIPOS de cada grupo y sus estadísticas.
/// Cualquier estructura que contenga un puntero nodoEquipo, apuntara siempre a la misma direccion de memoria para cada respectivo equipo.
/// Cambios en un equipo en una estructura, afetará a todas las demás que incluyan a ese equipo.

/*----------------------------------------*/

/// INICIO de codigo para < CREAR > BaseArrayGrupo.bin (EQUIPOS), solo para primera ejecución.


void crearNuevaBaseGrupo(){ /// Crear base de datos de grupos A, B ... H. ¡SOLO PARA PRIMERA EJECUCION!

    /// Nota: Teniendo en cuenta que cada grupo SIEMPRE tiene < 4 > equipos, no guardo la letra del grupo. El formato de la base de datos es de Equipo1, Equipo2.... EquipoN...

    FILE *fp=NULL;
    Equipo auxiliar;
    char idGrupos[TAM_MAX_GRUPOS]= {'A', 'B', 'C', 'D', 'E', 'F','G', 'H'};
    fp=fopen("./BaseArrayGrupo.bin", "w");

    for (int i=0; i<TAM_MAX_GRUPOS; i++){      /// para cada grupo de equipos.
        system("@cls||clear");
        printf("\nInicio de carga de equipos grupo %c\n", idGrupos[i]);
        for (int j=0; j<TAM_MAX_GRUPO; j++){            /// para cada equipo individual.
            printf("|--- Ingrese nombre del equipo:\n");
            inicializarEquipo(&auxiliar, "NO");
            fflush(stdin);
            gets(auxiliar.nomEquipo);
            fwrite(&auxiliar, sizeof(Equipo), 1, fp);
        }
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
*/

/// FIN de codigo para < CREAR > BaseArrayGrupo.bin (EQUIPOS), solo para primera ejecución.

/*----------------------------------------*/

/// INICIO de codigo para < CREAR > BaseArrayPartidos.bin (PARTIDOS), solo para primera ejecución.

int verificarSiEstaEquipo (nodoEquipo *listaEquipos, char nombre[]){
    int encontrado=0;
    nodoEquipo *seguidor=NULL;
    seguidor=listaEquipos;
    while (seguidor){
        if (strcmp(nombre, seguidor->equipo.nomEquipo)==0){
            encontrado=1;
        }
        seguidor=seguidor->siguiente;
    }
    return encontrado;
}

int verificarGrupo (char grupo){
    char idGrupos[TAM_MAX_GRUPOS]= {'A', 'B', 'C', 'D', 'E', 'F','G', 'H'};
    int encontrado=0;
    for (int i=0; i<TAM_MAX_GRUPOS; i++){
        if (idGrupos[i]==grupo){
            encontrado=1;
        }
    }
    return encontrado;
}

void crearArrayGrupoPartido(nodoEquipo *listaEquipos){ /// Crear base de datos de partidos de cada grupo. ¡SOLO PARA PRIMERA EJECUCION!
    FILE *fp=NULL;
    fp=fopen("./BaseArrayPartidos.bin", "w+");
    partidoArchivo guardar;
    char flag='n';
    char confirmar='n';

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
        while(!verificarGrupo(guardar.grupo)){
            printf("Grupo incorrecto, ingrese una letra entre A Y H:\n");
            fflush(stdin);
            scanf("%c", &guardar.grupo);
            guardar.grupo=toupper(guardar.grupo);
        }
        ///////////////
        printf("\nIngresar nombre del equipo 1:");
        fflush(stdin);
        gets(&guardar.nomEquipo1);
        while (!verificarSiEstaEquipo(listaEquipos, guardar.nomEquipo1)){
            puts("El equipo ingresado no es valido, ingrese una seleccion nacional que participe en el mundial.\n");
            printf("Ingresar nombre del equipo 1:");
            fflush(stdin);
            gets(&guardar.nomEquipo1);
        }
        ///////////////
        printf("VS.\n");
        ///////////////
        printf("\nIngresar nombre del equipo 2:");
        fflush(stdin);
        gets(&guardar.nomEquipo2);
        while (!verificarSiEstaEquipo(listaEquipos, guardar.nomEquipo2)){
            puts("El equipo ingresado no es valido, ingrese una seleccion nacional que participe en el mundial.\n");
            printf("\nIngresar nombre del equipo 2:");
            fflush(stdin);
            gets(&guardar.nomEquipo2);
        }
        ///////////////
        printf("\n>>>>>> El %i/%i, Grupo %c, %s vs. %s\n", div(guardar.fecha, 100), guardar.fecha%100, guardar.grupo, guardar.nomEquipo1, guardar.nomEquipo2);
        printf("Desea confirmar la carga? S/N\n");
        fflush(stdin);
        confirmar=getc(stdin);
        confirmar=tolower(confirmar);
        if (confirmar=='s'){
            fwrite(&guardar, sizeof(partidoArchivo),1,fp);
            puts("GUARDADO.\n");
        }
        ///////////////
        printf("\nDesea cargar otro partido? S/N\n");
        fflush(stdin);
        scanf("%c", &flag);
        flag=tolower(flag);
    }while (flag=='s');

    fclose(fp);
}

/// FIN de codigo para < CREAR > BaseArrayPartidos.bin (PARTIDOS), solo para primera ejecución.

/*----------------------------------------*/

/// INICIO de codigo para < LEVANTAR > BaseArrayGrupos.bin y volcarlo en lista simple de equipos.

void inicializarEquipo(Equipo *nuevo, char nombre[]){
    strcpy(nuevo->nomEquipo, nombre);
    nuevo->mp=0;
    nuevo->ga=0;
    nuevo->gf=0;
    nuevo->loss=0;
    nuevo->win=0;
    nuevo->pts=0;
}

nodoEquipo *inicializarNodoEquipo (nodoEquipo *nuevo, char nombre[]){
    nuevo=malloc(sizeof(nodoEquipo));
    inicializarEquipo(&nuevo->equipo, nombre);
    nuevo->siguiente=NULL;
    return nuevo;
}

nodoEquipo *cargarListaEquipos (nodoEquipo *equipos){
    FILE *fp;
    nodoEquipo *seguidor=NULL;
    nodoEquipo *anterior=NULL;
    Equipo lectura;
    fp=fopen("./BaseArrayGrupo.bin", "r");
    if (fp){
        equipos=inicializarNodoEquipo(equipos, "NO");
        seguidor=equipos;
        for (int j=0; j<TAM_MAX_GRUPOS; j++){ /// Cargo los equipos de los 8 grupos.
            for (int i=0; i<TAM_MAX_GRUPO; i++){ /// Cargo los 4 equipos de cada grupo.
                fread(&lectura, sizeof(Equipo), 1, fp);
                strcpy(seguidor->equipo.nomEquipo, lectura.nomEquipo);
                seguidor->siguiente=inicializarNodoEquipo(seguidor->siguiente, "NO");
                anterior=seguidor;
                seguidor=seguidor->siguiente;
            }
        }
    }else{
        puts("Error al abrir base de datos de equipos, proceda a crear una nueva base de datos de equipos:\n");
        crearNuevaBaseGrupo();
        cargarListaEquipos(equipos);
    }
    anterior->siguiente=NULL;
    fclose(fp);
    return equipos;
}

/// PARA VERIFICACION SOLAMENTE.
/*
void verificacionImprimirListaEquipos (nodoEquipo *equipos){
    nodoEquipo *seguidor;
    seguidor=equipos;
    while (seguidor){
        printf ("Nombre del equipo: %s\n", seguidor->equipo.nomEquipo);
        seguidor=seguidor->siguiente;
    }
}
*/

/// FIN de codigo para < LEVANTAR > BaseArrayGrupos.bin y volcarlo en lista simple de equipos.

/*----------------------------------------*/

/// INICIO de codigo para vincular equipos en el arreglo de grupos con equipos de la lista simple.

void inicializarArrayGrupoEquipos (Grupo arrayGrupoEquipos[]){
    char idGrupos[TAM_MAX_GRUPOS]= {'A', 'B', 'C', 'D', 'E', 'F','G', 'H'};
    for (int i=0; i<TAM_MAX_GRUPOS; i++){
        arrayGrupoEquipos[i].letra=idGrupos[i];
        arrayGrupoEquipos[i].equipos=NULL;
    }
}

nodoGrupoEquipo *inicializarNodoGrupoEquipo(nodoGrupoEquipo *nuevo){
    nuevo=malloc(sizeof(nodoGrupoEquipo));
    nuevo->siguiente=NULL;
    nuevo->equipo=NULL;
    return nuevo;
}

nodoGrupoEquipo *agregarNodoGrupoEquipo(nodoGrupoEquipo *listaGrupoEquipo, nodoGrupoEquipo *nuevo){
    nodoGrupoEquipo *anterior;
    nodoGrupoEquipo *seguidor;
    if (listaGrupoEquipo){
            seguidor=listaGrupoEquipo;
        while (seguidor){
            anterior=seguidor;
            seguidor=seguidor->siguiente;
        }
        anterior->siguiente=nuevo;
    }else{
        listaGrupoEquipo=nuevo;
    }
    return listaGrupoEquipo;
}

void vincularAListaArrayGruposEquipos (Grupo arrayGrupoEquipos[], nodoEquipo *listaEquipos){
    nodoEquipo *seguidorListaEquipos;
    nodoGrupoEquipo *nuevo;
    seguidorListaEquipos=listaEquipos;
    inicializarArrayGrupoEquipos(arrayGrupoEquipos);
    if (seguidorListaEquipos){
        for (int i=0; i<TAM_MAX_GRUPOS; i++){
            for (int j=0; j<(TAM_MAX_GRUPO); j++){
                nuevo=inicializarNodoGrupoEquipo(nuevo);
                nuevo->equipo = &(seguidorListaEquipos->equipo);
                arrayGrupoEquipos[i].equipos=agregarNodoGrupoEquipo(arrayGrupoEquipos[i].equipos, nuevo);
                seguidorListaEquipos=seguidorListaEquipos->siguiente; /// lista de equipos.
            }
        }
    }
}

/// FIN de codigo para vincular equipos en el arreglo de grupos con equipos de la lista simple.

/*----------------------------------------*/

/// INICIO de codigo para < LEVANTAR > BaseArrayPartidos.bin (PARTIDOS), para ejecuciones posteriores, cuando la base de datos ya existe.

void inicializarPartido(Partido *nuevo){
    /// Nota: Dentro de la estructura Partido, el valor -1 (int) o NULL representa el estado de variable no asignada aun.
    nuevo->equipo1=NULL;
    nuevo->equipo2=NULL;
    nuevo->fecha=-1;
    nuevo->golesEq1=-1;
    nuevo->golesEq2=-1;
    nuevo->id=-1;
    nuevo->penales1=-1;
    nuevo->penales2=-1;
}

void inicializarArrayGrupoPartidos(GrupoPartido arrayGrupoPartidos[]){
    char idGrupos[TAM_MAX_GRUPOS]= {'A', 'B', 'C', 'D', 'E', 'F','G', 'H'};
    for (int i=0; i<TAM_MAX_GRUPOS; i++){
        arrayGrupoPartidos[i].partidos=NULL;
        arrayGrupoPartidos[i].letra=idGrupos[i];
    }
}

void insertarNodoPartido (int grupo, GrupoPartido arrayGrupoPartidos[], nodoPartido *insertar){ ///Agrego al final de la lista de partidos de ese grupo.
    nodoPartido *seguidor;
    nodoPartido *anterior;
    seguidor=arrayGrupoPartidos[grupo].partidos;
    if (seguidor){
        anterior=seguidor;
        while (seguidor){
            anterior=seguidor;
            seguidor=seguidor->siguiente;
        }
        anterior->siguiente=insertar;
    } else{
    arrayGrupoPartidos[grupo].partidos=insertar;
    }
}

nodoEquipo *obtenerPunteroANodoEquipo(nodoEquipo *listaEquipos, char nombreBuscado[]){
    nodoEquipo *seguidor=NULL;
    nodoEquipo *nodoBuscado=NULL;
    seguidor=listaEquipos;
    int encontrado=0;
    while (seguidor&&!encontrado){
        if (strcmp(seguidor->equipo.nomEquipo, nombreBuscado)==0){
            encontrado=1;
            nodoBuscado=seguidor;
        }
        seguidor=seguidor->siguiente;
    }
    if (!encontrado){
        puts("Se realizo la busqueda de un equipo que no se encuentra en la lista.\n");
        system("pause");
    }
    return nodoBuscado;
}

void traerDesdeBaseArrayPartidos(GrupoPartido arrayGrupoPartidos[], nodoEquipo *listaEquipos) {
    FILE *fp=NULL;
    nodoPartido *nuevo=NULL;
    nodoPartido *anterior=NULL;
    nodoEquipo *aux=NULL;
    partidoArchivo lectura;
    char idGrupos[TAM_MAX_GRUPOS]= {'A', 'B', 'C', 'D', 'E', 'F','G', 'H'};
    fp=fopen("./BaseArrayPartidos.bin", "r"); /// Por consigna, solo contiene partidos de fase de grupos, ya que el resto se simula.
    if (fp){
        while (fread(&lectura, sizeof(partidoArchivo),1,fp)){
            nuevo=malloc(sizeof(nodoPartido));
            inicializarPartido(&nuevo->partido);
            aux=obtenerPunteroANodoEquipo(listaEquipos, lectura.nomEquipo1);
            if (aux){
                nuevo->partido.equipo1=&aux->equipo;
            }else{
                puts("Uno de los equipos en la lista de partidos fue mal ingresado. Por favor reiniciar la base de datos de PARTIDOS.");
                system("pause");
                crearArrayGrupoPartido(listaEquipos);
            }
            aux=obtenerPunteroANodoEquipo(listaEquipos, lectura.nomEquipo2);
            if (aux){
                nuevo->partido.equipo2=&aux->equipo;
            }else{
                puts("Uno de los equipos en la lista de partidos fue mal ingresado. Por favor reiniciar la base de datos de PARTIDOS.");
                system("pause");
                crearArrayGrupoPartido(listaEquipos);
            }
            nuevo->partido.fecha=lectura.fecha;
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
    }else {
        puts("Base de datos de Partidos no encontrada, reiniciarla...");
        system("pause");
        ///cargarDefaultBaseGrupoPartido();
        ///traerDesdeBaseArrayPartidos(arrayGrupoPartidos, listaEquipos);
    }
    fclose(fp);
}

/// FIN de codigo para < LEVANTAR > BaseArrayPartidos.bin (PARTIDOS), para ejecuciones posteriores, cuando la base de datos ya existe.

/*----------------------------------------*/

