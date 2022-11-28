#include "declaraciones_variables.h"
#include "declaraciones_funciones.h"
#include "declaraciones_variables.h"
#include "declaraciones_funciones.h"
#include "declaraciones_variables.h"
#include "declaraciones_funciones.h"



void simularPartido (Partido *partidoAsimular)
{
    clock_t seed;
    Sleep(10); /// milisegundos
    seed=clock();
    int intSeed= 0;
    intSeed= (int)seed;
    srand(intSeed);
    int rand1 = (rand()%5);

    //Sleep(15); /// milisegundos
    //seed=clock();
    //intSeed= (int)seed;
    //srand(intSeed);
    int rand2 = (rand()%5);

    Sleep(20); /// milisegundos
    seed=clock();
    intSeed= (int)seed;
    srand(intSeed);
    int randPenales = (rand()%100);

    partidoAsimular->golesEq1 = rand1; ///goles aleatorios para ambos equipos
    partidoAsimular->golesEq2 = rand2;

    ///paso estadisticas

    ///goles a favor y en contra
    partidoAsimular->equipo1->gf += partidoAsimular->golesEq1;
    partidoAsimular->equipo1->ga += partidoAsimular->golesEq2;
    partidoAsimular->equipo2->gf += partidoAsimular->golesEq2;
    partidoAsimular->equipo2->ga += partidoAsimular->golesEq1;
    ///sumo partido
    partidoAsimular->equipo1->mp++;
    partidoAsimular->equipo2->mp++;
    ///ganar o perder
    if(partidoAsimular->golesEq1 > partidoAsimular->golesEq2)  ///gana equipo 1 /// verificar si entra en EMPATES
    {
        partidoAsimular->equipo1->pts+=3;
        partidoAsimular->equipo1->win++;
        partidoAsimular->equipo2->loss++;
    }
    else if (partidoAsimular->golesEq2 > partidoAsimular->golesEq1) /// gana equipo 2
    {
        partidoAsimular->equipo2->pts+=3;
        partidoAsimular->equipo2->win++;
        partidoAsimular->equipo1->loss++;
    }
    else ///empate
    {
        partidoAsimular->equipo2->pts++;
        partidoAsimular->equipo1->pts++;
        div_t dia_t= div(partidoAsimular->fecha, 100);
        int dia=dia_t.quot; /// USANDO COCIENTE
        int mes= partidoAsimular->fecha % 100;
        if (mes==12){
            if(dia>3) /// si la fecha es igual o posterior a playoffs  ///PROBLEMA CON LA LECTURA DE FECHA.
            {
                if(randPenales >=50)///gano el equipo 1
                {
                    partidoAsimular->penales1 = 1;
                    partidoAsimular->penales2 = 0;

                    partidoAsimular->equipo1->win++;
                    partidoAsimular->equipo2->loss++;
                }
                else ///gano el equipo 2
                {
                    partidoAsimular->penales1 = 0;
                    partidoAsimular->penales2 = 1;

                    partidoAsimular->equipo2->win++;
                    partidoAsimular->equipo1->loss++;
                }
            }
        }
    }
}

void simularPartidoArreglado (Partido  *partidoAsimular, char equipoASimular1[], char equipoASimular2[], int clasifica1, int clasifica2) /// para los casos en los que el usuario quiera que un o dos equipo clasifiquen o no .
/// clasifica1=2 ARREGLADO PARA QUE equipoASimular1 NO CLASIFIQUE.
/// clasifica1=1 ARREGLADO PARA QUE equipoASimular1 CLASIFIQUE.
/// igual para clasifica2
/// clasifica2=0 Si esta arreglado para un solo equipo.

/// EJEMPLO
/// equipoASimular1= Argentina;
/// equipoASimular2= Qatar;

{
    clock_t seed;
    int intSeed= 0;

    Sleep(10); /// milisegundos
    seed=clock();
    intSeed= (int)seed;
    srand(intSeed);
    int rand1 = ((rand()%5)+1);   ///que gane 1 a 0 como minimo, 5 a 0 como maximo

    int rand2 = 0; /// No es random porque tiene que perder. Siempre 0.

    /// CUANDO ESTA ARREGLADO PARA UN SOLO EQUIPO.
    if(clasifica1==1){
        if(strcmpi(partidoAsimular->equipo1->nomEquipo, equipoASimular1)== 0)  ///Arreglado para que gane equipoASimular1. En ejemplo: gana Argentina.
        {
            partidoAsimular->golesEq1 = rand1; ///1 a 5
            partidoAsimular->golesEq2 = rand2; /// 0
        }
        else
        {
            if (strcmpi(partidoAsimular->equipo2->nomEquipo, equipoASimular1) == 0)  ///Arreglado para que gane equipoASimular1. En ejemplo: gana Argentina.
            {
                partidoAsimular->golesEq1 = rand2; ///0
                partidoAsimular->golesEq2 = rand1;  ///1 a 5
            }
        }
    }
    if (clasifica1==2){
        if(strcmpi(partidoAsimular->equipo1->nomEquipo, equipoASimular1)== 0)  ///Arreglado para que pierda equipoASimular1. En ejemplo: gana Qatar.
        {
            partidoAsimular->golesEq1 = rand2; /// 0
            partidoAsimular->golesEq2 = rand1; ///1 a 5
        }
        else
        {
            if (strcmpi(partidoAsimular->equipo2->nomEquipo, equipoASimular1) == 0)  ///Arreglado para que pierda equipoASimular1. En ejemplo: gana Qatar.
            {
                partidoAsimular->golesEq1 = rand1; ///1 a 5
                partidoAsimular->golesEq2 = rand2;  ///0
            }
        }
    }
    /// CUANDO ESTA ARREGLADO PARA DOS EQUIPOS.
    if(clasifica2==1){
        if(strcmpi(partidoAsimular->equipo2->nomEquipo, equipoASimular2)== 0)  ///Arreglado para que gane equipoASimular2. En ejemplo: gana Qatar.
        {
            partidoAsimular->golesEq2 = rand1; ///1 a 5
            partidoAsimular->golesEq1 = rand2; /// 0
        }
        else
        {
            if (strcmpi(partidoAsimular->equipo2->nomEquipo, equipoASimular2) == 0)  ///Arreglado para que gane equipoASimular2. En ejemplo: gana Qatar.
            {
                partidoAsimular->golesEq2 = rand2; ///0
                partidoAsimular->golesEq1 = rand1;  ///1 a 5
            }
        }
    }
    if (clasifica2==2){
        if(strcmpi(partidoAsimular->equipo1->nomEquipo, equipoASimular2)== 0)  ///Arreglado para que pierda equipoASimular2. En ejemplo: gana Qatar.
        {
            partidoAsimular->golesEq2 = rand2; /// 0
            partidoAsimular->golesEq1 = rand1; ///1 a 5
        }
        else
        {
            if (strcmpi(partidoAsimular->equipo1->nomEquipo, equipoASimular2) == 0)  ///Arreglado para que pierda equipoASimular2. En ejemplo: gana Qatar.
            {
                partidoAsimular->golesEq2 = rand1; ///1 a 5
                partidoAsimular->golesEq1 = rand2;  ///0
            }
        }
    }

    /// Se sobreescriben valores cuando se enfrentan los dos equipos cuyos resultados fueron arreglados.
    /// Esto no es un problema ya que ganarán o perderán (segun lo que se haya arreglado) el resto de sus partidos de fase de grupos.

    ///paso estadisticas

    ///goles a favor y en contra
    partidoAsimular->equipo1->gf += partidoAsimular->golesEq1;
    partidoAsimular->equipo1->ga += partidoAsimular->golesEq2;
    partidoAsimular->equipo2->gf += partidoAsimular->golesEq2;
    partidoAsimular->equipo2->ga += partidoAsimular->golesEq1;
    ///sumo partido
    partidoAsimular->equipo1->mp++;
    partidoAsimular->equipo2->mp++;
    ///ganar o perder
    if(partidoAsimular->golesEq1 > partidoAsimular->golesEq2)  ///gana equipo 1 /// verificar si entra en EMPATES
    {
        partidoAsimular->equipo1->pts+=3;
        partidoAsimular->equipo1->win++;
        partidoAsimular->equipo2->loss++;

    }
    else if (partidoAsimular->golesEq2 > partidoAsimular->golesEq1) /// gana equipo 2
    {
        partidoAsimular->equipo2->pts+=3;
        partidoAsimular->equipo2->win++;
        partidoAsimular->equipo1->loss++;
    }
    if (partidoAsimular->golesEq2 == partidoAsimular->golesEq1){ /// empate
        partidoAsimular->equipo2->pts++;
        partidoAsimular->equipo1->pts++;
    }
    /// Esta funcion no se utiliza en playoffs asi que los empates son sin penales.
}

int verificarSiEstaEquipoEnGrupo (nodoGrupoEquipo *listaEquiposGrupo, char equipoBuscado[]){
    nodoGrupoEquipo *seguidor=NULL;
    seguidor=listaEquiposGrupo;
    int encontrado=0;
    while (seguidor){
        if (strcmp(seguidor->equipo->nomEquipo, equipoBuscado)==0){
            encontrado=1;
        }
        seguidor=seguidor->siguiente;
    }
    return encontrado;
}

void simularFaseDeGrupos (GrupoPartido arrayPartidosGrupos[], Grupo arrayEquiposGrupos[], nodoEquipo *listaEquipos)  ///simula fase de grupos aleatoriamente
{
    char equipoASimular1 [20]="NO";
    char equipoASimular2 [20]="NO";
    char continuar='n';
    int clasifica1;
    int clasifica2;
    char idGrupos[TAM_MAX_GRUPOS]= {'A', 'B', 'C', 'D', 'E', 'F','G', 'H'};

    for (int i=0; i<TAM_MAX_GRUPOS; i++){ /// REPITO TODO EL MENU PARA CADA GRUPO.

        printf("\nDesea elegir un resultado para la clasificacion de algun equipo del grupo %c? Puede elegir hasta 2 equipos. (s/n)\n", idGrupos[i]);
        fflush(stdin);
        gets (&continuar);
        if(continuar == 's' || continuar == 'S') /// Si arreglo al menos un equipo...
        {
            int flag=0;
            do{
                printf("Ingrese el equipo cuyo resultado desea predefinir:\n"); /// PRIMER EQUIPO ARREGLADO.
                fflush(stdin);
                gets(&equipoASimular1);
                flag=verificarSiEstaEquipoEnGrupo (arrayEquiposGrupos[i].equipos, equipoASimular1);
                if (flag==0){
                    puts("El equipo ingresado no es valido");
                }
            } while (flag==0);
            printf("Cuales seran los resultados del equipo %s? :\n", equipoASimular1);
            printf("|1| CLASIFICA\n");
            printf("|2| NO CLASIFICA\n");
            do {
                fflush(stdin);
                scanf("%i", &clasifica1);
            } while ( clasifica1 > 2 );

            printf("Desea elegir un resultado para la clasificacion de otro equipo del grupo %c? Puede elegir hasta 2 equipos. (s/n)\n", idGrupos[i]);
            fflush(stdin);
            gets (&continuar);
            if(continuar == 's' || continuar == 'S'){ /// SEGUNDO EQUIPO ARREGLADO.
                flag=0;
                do{
                    printf("Ingrese el equipo cuyo resultado desea predefinir:\n");
                    fflush(stdin);
                    gets(&equipoASimular2);
                    flag=verificarSiEstaEquipoEnGrupo (arrayEquiposGrupos[i].equipos, equipoASimular2);
                    if (strcmp(equipoASimular1, equipoASimular2)==0){
                        flag=0;
                    }
                    if (flag==0){
                        puts("El equipo ingresado no es valido");
                    }
                } while (flag==0);
                printf("Cuales seran los resultados del equipo %s? :\n", equipoASimular2);
                printf("|1| CLASIFICA\n");
                printf("|2| NO CLASIFICA\n");
                do {
                    fflush(stdin);
                    scanf("%i", &clasifica2);
                } while ( clasifica1 > 2 );
            }
                simulaGrupoArreglado(arrayPartidosGrupos[i].partidos, equipoASimular1, equipoASimular2, clasifica1, clasifica2);  /// simulo el grupo [i]
        }
        else  /// Si no quiero ningun equipo del grupo [i] este arreglado. Lo simulo aleatoriamente.
        {
            simulaGrupo (arrayPartidosGrupos[i].partidos);
        }

    } /// fin del for (i)

}

void simulaGrupo (nodoPartido * partidosGrupo)  ///funcion primaria. Simula grupo aleatoriamente
{
    if(partidosGrupo)
    {
        nodoPartido * seg = partidosGrupo;
        while(seg)
        {
            simularPartido(&seg->partido);
            seg = seg->siguiente;
        }
    }
}

void simulaGrupoArreglado (nodoPartido *partidosGrupo, char equipoASimular1[], char equipoASimular2[], int clasifica1, int clasifica2) ///simula un grupo con resultado arreglado
{
    if(partidosGrupo)
    {
        nodoPartido * seg = partidosGrupo;
        while(seg)
        {
            int arreglado=0;
            /// chequeo que el equipoASimular1 este entre los dos que juegan el partido.
            /// chequeo que el equipoASimular2 este entre los dos que juegan el partido.
            if(strcmpi(seg->partido.equipo1, equipoASimular1) == 0 || strcmpi(seg->partido.equipo2, equipoASimular1) == 0)
            {
                arreglado=1;

            }
            if(strcmpi(seg->partido.equipo1, equipoASimular2) == 0 || strcmpi(seg->partido.equipo2, equipoASimular2) == 0)
            {
                arreglado=1;

            }
            if (arreglado){
                simularPartidoArreglado(&seg->partido, equipoASimular1, equipoASimular2, clasifica1, clasifica2);   ///simulo el partido con las estadisticas forzadas
            }else{
                simularPartido(&seg->partido);
            }
            seg = seg->siguiente;
        }
    }
}

/*------------------------------------------*/

/// INICIO DE CODIGO PARA PlayOffs

/*------------------------------------------*/

int ChequearFaseDeGrupo (nodoEquipo * listaEquipos) ///chequea que todos los equipos hayan terminado la fase de grupos
{

    if(listaEquipos)  ///chequeamos desde la lista de equipos que es mas facil
    {
        nodoEquipo* seg = listaEquipos;
        while (seg)
        {
            if(seg->equipo.mp < 3)
            {
                return 0;  ///retorna 0 si no se termino la fase de grupos
            }
            else
            {
                seg = seg->siguiente;
            }
        }
        if(!seg) /// si llego al final de la lista
        {
            return 1;   ///termino la fase de grupos, retorna 1
        }
    }
}


Equipo* retornarPrimeroDelGrupo(nodoGrupoEquipo* listaEquipo)
{

    nodoGrupoEquipo* seg = listaEquipo->siguiente;
    Equipo* aux = listaEquipo->equipo;

    while(seg != NULL)
    {
        if(seg->equipo->pts > aux->pts)//si puntos del seg son mayores a los del aux
        {
            aux = seg->equipo;// aux se vuelve seg
        }
        if(seg->equipo->pts == aux->pts)//si son iguales
        {
            if(seg->equipo->gf > aux->gf)//se comparan los goles metidos
            {
                aux = seg->equipo;
            }
            if(seg->equipo->gf == aux->gf)//si son iguales los goles metidos
            {
                if(seg->equipo->ga < aux->ga)//se comparan los goles en contra
                {
                    aux = seg->equipo;
                }
            }
        }
        seg = seg->siguiente;
    }

    return aux;
}



Equipo* retornarSegundoDelGrupo(nodoGrupoEquipo* listaEquipo, Equipo* primero)
{

    nodoGrupoEquipo* seg = listaEquipo->siguiente;
    Equipo* ganadorActual = listaEquipo->equipo;

    if(strcmp(ganadorActual->nomEquipo, primero->nomEquipo) == 0)
    {
        seg = seg->siguiente;
        ganadorActual = listaEquipo->siguiente->equipo;
    }

    while(seg != NULL)
    {
        if(strcmp(ganadorActual->nomEquipo, primero->nomEquipo) != 0 && strcmp(seg->equipo->nomEquipo, primero->nomEquipo) != 0 && seg->equipo->pts > ganadorActual->pts)//si puntos del seg son mayores a los del ganadorActual
        {
            ganadorActual = seg->equipo;// ganadorActual se vuelve seg
        }
        if(strcmp(ganadorActual->nomEquipo, primero->nomEquipo) != 0 && strcmp(seg->equipo->nomEquipo, primero->nomEquipo) != 0 && seg->equipo->pts == ganadorActual->pts)//si son iguales
        {
            if(seg->equipo->gf > ganadorActual->gf)//se comparan los goles metidos
            {
                ganadorActual = seg->equipo;
            }
            if(seg->equipo->gf == ganadorActual->gf)//si son iguales los goles metidos
            {
                if(seg->equipo->ga < ganadorActual->ga)//se comparan los goles en contra
                {
                    ganadorActual = seg->equipo;
                }
            }
        }
        seg = seg->siguiente;
    }

    return ganadorActual;

}


nodoPartido* crearNodoPartido(Equipo* uno, Equipo* dos)
{
    nodoPartido* partidon = (nodoPartido*)malloc(sizeof(nodoPartido));
    partidon->partido.equipo1 = uno;
    partidon->partido.equipo2 = dos;
    partidon->partido.golesEq1 = 0;
    partidon->partido.golesEq2 = 0;
    partidon->partido.penales1 = 0;
    partidon->partido.penales2 = 0;
    partidon->siguiente = NULL;

    return partidon;
}

///SIMULACION COMPLETA DE PLAYOFFS


void simularPlayoffs(GrupoPartido arrayPartidosGrupos [], nodoEquipo * listaEquipos, Grupo arrayEquiposGrupos[], fase arrayFase[]) /// SIMULACION COMPLETA DE PLAYOFFS
{
    int faseDeGruposTerminada = ChequearFaseDeGrupo(listaEquipos);
    if(faseDeGruposTerminada == 0)
    {
        printf("Todavia no se termino de jugar la fase de grupos.\n\n");
        system("pause");
    }
    else
    {
        pasarGanadoresAPlayoffOcatvos(arrayEquiposGrupos, arrayFase);
        pasarGanadoresACuartos(arrayFase);
        pasarGanadoresASemis(arrayFase);
        pasarGanadoresATercerPuesto(arrayFase);
        pasarGanadoresAFinal(arrayFase);
        jugarFinal(arrayFase);
        imprimirPlayoffs(arrayFase);
    }
}


void insertarPartidoOctavos(nodoPartido** listaPartidos, nodoPartido* partidin)  ///octavos
{

    nodoPartido* seg;

    if(*listaPartidos == NULL)
    {
        *listaPartidos = partidin;
    }
    else
    {
        seg = *listaPartidos;
        while(seg->siguiente != NULL)
        {
            seg = seg->siguiente;
        }
        seg->siguiente = partidin;
    }
}

void inicializarArrayFase(fase arrayFase[]){
    for (int i=0; i<5 ; i++){
        arrayFase[i].partidos=NULL;
        arrayFase[i].idFase=i;
    }
}

void pasarGanadoresAPlayoffOcatvos(Grupo arrayEquiposGrupos[], fase arrayFase[])///arraygrupo FASE DE GRUPO  arrayFase PLAYOFFS
{
    inicializarArrayFase (arrayFase);
    for(int i=0; i < 8; i++)
    {
        Equipo* primeroPrimerGrupo = retornarPrimeroDelGrupo(arrayEquiposGrupos[i].equipos);//Clasificados del grupo, por ejemplo "A".
        Equipo* segundoPrimerGrupo = retornarSegundoDelGrupo(arrayEquiposGrupos[i].equipos, primeroPrimerGrupo);

        i++;

        Equipo* primeroSegundoGrupo = retornarPrimeroDelGrupo(arrayEquiposGrupos[i].equipos);//Clasificados del grupo siguiente, "B" en el ejemplo.
        Equipo* segundoSegundoGrupo = retornarSegundoDelGrupo(arrayEquiposGrupos[i].equipos, primeroSegundoGrupo);
        nodoPartido* uno = crearNodoPartido(primeroPrimerGrupo, segundoSegundoGrupo); ///LOS PARTIDOS VIENEN SIN LA FECHA CARGADA
        insertarPartidoOctavos(&(arrayFase[0].partidos), uno);
        nodoPartido* dos = crearNodoPartido(segundoPrimerGrupo, primeroSegundoGrupo); ///LOS PARTIDOS VIENEN SIN LA FECHA CARGADA
        insertarPartidoOctavos(&(arrayFase[0].partidos), dos);
    }
}



/// CUARTOS
Equipo* vencedor(Partido match)///RETORNA EL EQUIPO GANADOR DEL PARTIDO
{
    if(match.golesEq1 > match.golesEq2)
    {
        return match.equipo1;
    }
    else if(match.golesEq1 < match.golesEq2)
    {
        return match.equipo2;
    }
    else if(match.golesEq1 == match.golesEq2)
    {
        if(match.penales1 != 0)
        {
            return match.equipo1;
        }
        else
        {
            return match.equipo2;
        }
    }
}

void pasarEquiposACuartos(nodoPartido* lista, nodoPartido** listaCuartos)///la "lista" es de octavos
{
    lista->partido.fecha=312;
    simularPartido(&lista->partido);
    Equipo* ganador1 = vencedor(lista->partido);///PARTIDO 1A VS 2B
    lista = lista->siguiente;

    lista->partido.fecha=312;
    simularPartido(&lista->partido);
    Equipo* ganador2 = vencedor(lista->partido);///PARTIDO 1B VS 2A
    lista = lista->siguiente;

    lista->partido.fecha=412;
    simularPartido(&lista->partido);
    Equipo* ganador3 = vencedor(lista->partido);///PARTIDO 1C VS 2D
    lista = lista->siguiente;

    lista->partido.fecha=412;
    simularPartido(&lista->partido);
    Equipo* ganador4 = vencedor(lista->partido);///PARTIDO 1D VS 2C
    lista = lista->siguiente;

    lista->partido.fecha=512;
    simularPartido(&lista->partido);
    Equipo* ganador5 = vencedor(lista->partido);///PARTIDO 1E VS 2F
    lista = lista->siguiente;

    lista->partido.fecha=512;
    simularPartido(&lista->partido);
    Equipo* ganador6 = vencedor(lista->partido);///PARTIDO 1F VS 2E
    lista = lista->siguiente;

    lista->partido.fecha=612;
    simularPartido(&lista->partido);
    Equipo* ganador7 = vencedor(lista->partido);///PARTIDO 1G VS 2H
    lista = lista->siguiente;

    lista->partido.fecha=612;
    simularPartido(&lista->partido);
    Equipo* ganador8 = vencedor(lista->partido);///PARTIDO 1H VS 2G


    nodoPartido* match;

    if(*listaCuartos == NULL)///SE CREAN LOS PARTIDOS DE CUARTOS CON SUS RESPECTIVOS EQUIPOS Y SE PONEN EN EL ARREGLO EN LA POSICION 1 YA QUE RECIBIMOS POR PARAMETRO LA LISTA DEL ARREGLO[1]
    {
        *listaCuartos = crearNodoPartido(ganador1, ganador3);
        match=*listaCuartos;
    }

    nodoPartido *nuevo=NULL;
    nuevo = crearNodoPartido(ganador5, ganador7);
    match->siguiente=nuevo;
    match=match->siguiente;

    nuevo = crearNodoPartido(ganador2, ganador4);
    match->siguiente=nuevo;
    match=match->siguiente;

    nuevo = crearNodoPartido(ganador6, ganador8);
    match->siguiente=nuevo;
    match=match->siguiente;
}

void pasarGanadoresACuartos(fase arrayFase[])
{
    pasarEquiposACuartos(arrayFase[0].partidos, &(arrayFase[1].partidos));
}


///SEMIFINAL

void pasarEquiposASemis(nodoPartido* listaCuartos, nodoPartido** listaSemis)
{
    listaCuartos->partido.fecha=912;
    simularPartido(&listaCuartos->partido);
    Equipo* semi1 = vencedor(listaCuartos->partido);///PARTIDO entre el ganador1 vs ganador3¿
    listaCuartos = listaCuartos->siguiente;

    listaCuartos->partido.fecha=912;
    simularPartido(&listaCuartos->partido);
    Equipo* semi2 = vencedor(listaCuartos->partido);///PARTIDO entre el ganador5 vs ganador7
    listaCuartos = listaCuartos->siguiente;

    listaCuartos->partido.fecha=1012;
    simularPartido(&listaCuartos->partido);
    Equipo* semi3 = vencedor(listaCuartos->partido);///PARTIDO entre el ganador2 vs ganador4
    listaCuartos = listaCuartos->siguiente;

    listaCuartos->partido.fecha=1012;
    simularPartido(&listaCuartos->partido);
    Equipo* semi4 = vencedor(listaCuartos->partido);///PARTIDO entre el ganador6 vs ganador8
    listaCuartos = listaCuartos->siguiente;

    if(*listaSemis == NULL)
    {
        nodoPartido *aux;
        *listaSemis = crearNodoPartido(semi1, semi2);
        aux=*listaSemis;
        aux->siguiente=crearNodoPartido(semi3, semi4);
    }
}

void pasarGanadoresASemis(fase arrayFase[])
{
    pasarEquiposASemis(arrayFase[1].partidos, &(arrayFase[2].partidos));
}


///TERCER PUESTO

Equipo* perdedor(Partido match)///RETORNA EL EQUIPO PERDEDOR DEL PARTIDO
{
    if(match.golesEq1 < match.golesEq2)
    {
        return match.equipo1;
    }
    else if(match.golesEq1 > match.golesEq2)
    {
        return match.equipo2;
    }
    else if(match.golesEq1 == match.golesEq2)
    {
        if(match.penales1 == 0)
        {
            return match.equipo1;
        }
        else
        {
            return match.equipo2;
        }
    }
}

void pasarEquiposATercerPuesto(nodoPartido* listaSemis, nodoPartido** listaTercerPuesto)
{

    listaSemis->partido.fecha=1312;
    simularPartido(&listaSemis->partido);
    Equipo* derrotado1 = perdedor(listaSemis->partido);

    listaSemis = listaSemis->siguiente;

    listaSemis->partido.fecha=1412;
    simularPartido(&listaSemis->partido);

    Equipo* derrotado2 = perdedor(listaSemis->partido);

    nodoPartido* match = crearNodoPartido(derrotado1, derrotado2);

    *listaTercerPuesto = match;
}

void pasarGanadoresATercerPuesto(fase arrayFase[])
{
    pasarEquiposATercerPuesto(arrayFase[2].partidos, &(arrayFase[3].partidos));
}


///FINAL

void pasarEquiposAFinal(nodoPartido* listaSemis, nodoPartido** listaTercerPuesto,  nodoPartido** listaFinal)
{
    ///SEMIFINALES
    Equipo* finalista1 = vencedor(listaSemis->partido);
    Equipo* eq1TercerPuesto= perdedor(listaSemis->partido);

    listaSemis = listaSemis->siguiente;

    Equipo* finalista2 = vencedor(listaSemis->partido);
    Equipo* eq2TercerPuesto= perdedor(listaSemis->partido);

    /// TERCER PUESTO

    *listaTercerPuesto=crearNodoPartido(eq2TercerPuesto,eq1TercerPuesto);
    nodoPartido *auxTercerPuesto=*listaTercerPuesto;
    auxTercerPuesto->partido.fecha=1712;
    simularPartido(&auxTercerPuesto->partido);


    /// FINALES

    nodoPartido* match = crearNodoPartido(finalista1, finalista2);

    *listaFinal = match;
}

void pasarGanadoresAFinal(fase arrayFase[])
{
    pasarEquiposAFinal(arrayFase[2].partidos, &(arrayFase[3].partidos), &(arrayFase[4].partidos));
}


void jugarFinal (fase arrayFase[])
{
    pasarGanadorYSegundoPuesto (arrayFase[4].partidos);
}

void pasarGanadorYSegundoPuesto (nodoPartido * listaFinal)
{
    listaFinal->partido.fecha=1812;
    simularPartido(&listaFinal->partido);
    Equipo * Campeon = vencedor(listaFinal->partido);
    Equipo * subCampeon = perdedor(listaFinal->partido);
}
