#include "declaraciones_variables.h"
#include "declaraciones_funciones.h"

/*----------------------------------------*/

///   Explicación de variables:
/// GrupoPartido arrayPartidosGrupos[] = Contiene un arreglo de listas de los PARTIDOS de fase de grupos.
/// fase arrayFase[] = Contiene un arreglo de listas con los PARTIDOS de cada fase PlayOffs. 0=Octavos, 4=Final.
/// Grupo arrayEquiposGrupos[] = Contiene un arreglo de listas de los EQUIPOS de cada grupo y sus estadísticas.
/// Cualquier estructura que contenga un puntero nodoEquipo, apuntara siempre a la misma direccion de memoria para cada respectivo equipo.
/// Cambios en un equipo en una estructura, afetará a todas las demás que incluyan a ese equipo.

/// GLOSARIO:

/// 1) - Codigo relacionado a estructura Grupo (equipos).
///     1.1) CREAR BaseArrayGrupo.
///     1.2) LEVANTAR BaseArrayGrupo en lista simple de equipos nodoEquipo.
///     1.3) VINCULAR Grupo arrayGrupoEquipos[] a la lista simple de equipos nodoEquipo.

/// 2) - Codigo relacionado a estructura GrupoPartido (partidos)
///     2.1) AGREGAR, REINICIAR Y CARGAR DEFAULT para BaseArrayPartidos.bin
///     2.2) LEVANTAR Y VINCULAR desde BaseArrayPartidos.bin a arrayGrupoPartidos[] (equipos de esta estructura apuntaran a lista simple nodoEquipo.

/*----------------------------------------*/

/// 1) INICIO de codigo relacionado a estructura Grupo (equipos).

/*----------------------------------------*/

///     1.1) INICIO de codigo para < CREAR > BaseArrayGrupo.bin (EQUIPOS), solo para primera ejecución.

void crearNuevaBaseGrupo(){ /// Crear base de datos de grupos A, B ... H. ¡SOLO PARA PRIMERA EJECUCION!

    /// Nota: Teniendo en cuenta que cada grupo SIEMPRE tiene < 4 > equipos, no guardo la letra del grupo.
    /// El formato de la base de datos es de Equipo1, Equipo2.... EquipoN...

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

void cargarDefaultBaseGrupo(){
    FILE *fp_backup=NULL;
    FILE *fp_base=NULL;
    Equipo lectura;
    fp_backup=fopen("./BaseArrayGrupo - BACKUP.bin", "r");
    fp_base=fopen("./BaseArrayGrupo.bin", "w");
    while (fread(&lectura, sizeof(Equipo),1,fp_backup)){
        fwrite(&lectura, sizeof(Equipo), 1, fp_base);
    }
    fclose(fp_backup);
    fclose(fp_base);
}

///     FIN de codigo para < CREAR > BaseArrayGrupo.bin (EQUIPOS), solo para primera ejecución.

/*----------------------------------------*/

///     1.2) INICIO de codigo para < LEVANTAR > BaseArrayGrupos.bin y volcarlo en lista simple de equipos.

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

nodoEquipo *leerListaEquipos (){
    FILE *fp;
    nodoEquipo *inicioLista=NULL;
    nodoEquipo *seguidor=NULL;
    nodoEquipo *anterior=NULL;
    Equipo lectura;
    fp=fopen("./BaseArrayGrupo.bin", "r");
    if (fp){
        inicioLista=inicializarNodoEquipo(inicioLista, "NO");
        seguidor=inicioLista;
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
        puts("Error al abrir base de datos de equipos, se necesita crear una nueva base de datos de equipos o cargar la base por defecto.\n");
    }
    anterior->siguiente=NULL;
    fclose(fp);
    return inicioLista;
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

///     FIN de codigo para < LEVANTAR > BaseArrayGrupos.bin y volcarlo en lista simple de equipos.

/*----------------------------------------*/

///     1.3) INICIO de codigo para < VINCULAR > equipos en el arreglo de grupos con equipos de la lista simple.

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

///     FIN de codigo para < VINCULAR > equipos en el arreglo de grupos con equipos de la lista simple.

/*----------------------------------------*/

///     2) INICIO DE CODIGO RELACIONADO A ESTRUCTURA GrupoPartido (Partidos).

/*----------------------------------------*/

///     2.1) INICIO de codigo para < AGREGAR > a BaseArrayPartidos.bin (PARTIDOS).

void reiniciarBasePartidos (){
    FILE *fp=NULL;
    fp=fopen("./BaseArrayPartidos.bin", "w");
    fclose(fp);
}

void cargarDefaultBasePartido(){
    FILE *fp_backup=NULL;
    FILE *fp_base=NULL;
    partidoArchivo lectura;
    fp_backup=fopen("./BaseArrayPartidos - BACKUP.bin", "r");
    fp_base=fopen("./BaseArrayPartidos.bin", "w");
    while (fread(&lectura, sizeof(partidoArchivo),1,fp_backup)){
        fwrite(&lectura, sizeof(partidoArchivo), 1, fp_base);
    }
    fclose(fp_backup);
    fclose(fp_base);
}

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

void agregarABaseArrayGrupoPartido(nodoEquipo *listaEquipos){ /// Agrega partidos a la base de datos de partidos ya existente.
    FILE *fp=NULL;
    fp=fopen("./BaseArrayPartidos.bin", "a+");
    partidoArchivo guardar;
    char flag='n';
    char confirmar='n';

    /// Nota: La base de datos guarda todos los PARTIDOS en estructuras partidoArchivo.
    /// donde: < int fecha=DDMM >

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

///     FIN de codigo para < AGREGAR, REINICIAR Y CARGAR DEFAULT > a BaseArrayPartidos.bin (PARTIDOS).

/*----------------------------------------*/

///     2.2) INICIO de codigo para < LEVANTAR Y VINCULAR > desde BaseArrayPartidos.bin (PARTIDOS) -
///     - a GrupoPartido arrayGrupoPartidos[] y vincular el arreglo con la lista simple de equipos.

void inicializarPartido(Partido *nuevo){
    /// Nota: Dentro de la estructura Partido, el valor -1 (int) o NULL representa el estado de variable no asignada aun.
    nuevo->equipo1=NULL;
    nuevo->equipo2=NULL;
    nuevo->fecha=0;
    nuevo->golesEq1=0;
    nuevo->golesEq2=0;
    nuevo->id=0;
    nuevo->penales1=0;
    nuevo->penales2=0;
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
    }
    return nodoBuscado;
}

void leerYVincularBaseArrayPartidos(GrupoPartido arrayGrupoPartidos[], nodoEquipo *listaEquipos) {
    FILE *fp=NULL;
    nodoPartido *nuevo=NULL;
    nodoEquipo *aux=NULL;
    partidoArchivo lectura;
    inicializarArrayGrupoPartidos(arrayGrupoPartidos);
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
            }
            aux=obtenerPunteroANodoEquipo(listaEquipos, lectura.nomEquipo2);
            if (aux){
                nuevo->partido.equipo2=&aux->equipo;
            }else{
                puts("Uno de los equipos en la lista de partidos fue mal ingresado. Por favor reiniciar la base de datos de PARTIDOS.");
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
    }
    fclose(fp);
}

///     2.2) FIN de codigo para < LEVANTAR Y VINCULAR > desde BaseArrayPartidos.bin (PARTIDOS) -
///     - a GrupoPartido arrayGrupoPartidos[] y vincular el arreglo con la lista simple de equipos.

/*----------------------------------------*/

