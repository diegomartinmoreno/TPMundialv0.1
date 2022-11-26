#include "declaraciones_variables.h"
#include "declaraciones_funciones.h"

void simularPartido (Partido partidoAsimular)
{

    srand(time(NULL));

    int rand1 = (rand()%6);
    int rand2 = (rand()%6);
    int randPenales = (rand()%100);


    Equipo * ganador;
    Equipo * perdedor;

    partidoAsimular.golesEq1 = rand1; ///goles aleatorios para ambos equipos
    partidoAsimular.golesEq2 = rand2;

    ///paso estadisticas

    ///goles a favor y en contra
    partidoAsimular.equipo1->gf= partidoAsimular.equipo1->gf + partidoAsimular.golesEq1;
    partidoAsimular.equipo1->ga = partidoAsimular.equipo1->ga + partidoAsimular.golesEq2;
    partidoAsimular.equipo2->gf = partidoAsimular.equipo1->gf + partidoAsimular.golesEq2;
    partidoAsimular.equipo2->ga = partidoAsimular.equipo2->ga + partidoAsimular.golesEq1;
    ///sumo partido
    partidoAsimular.equipo1->mp = partidoAsimular.equipo1->mp++;
    partidoAsimular.equipo2->mp = partidoAsimular.equipo2->mp++;
    ///ganar o perder
    if(partidoAsimular.golesEq1 > partidoAsimular.golesEq2)  ///gana equipo 1
    {
        partidoAsimular.equipo1->win++;
        partidoAsimular.equipo2->loss++;

        ganador = partidoAsimular.equipo1;
        perdedor = partidoAsimular.equipo2;
    }
    else if (partidoAsimular.golesEq2 > partidoAsimular.golesEq1) /// gana equipo 2
    {
        partidoAsimular.equipo2->win++;
        partidoAsimular.equipo1->loss++;

        ganador = partidoAsimular.equipo2;
        perdedor = partidoAsimular.equipo1;
    }
    else ///empate
    {
        if(partidoAsimular.fecha >= 0312) /// si la fecha es igual o posterior a playoffs
        {
            if(randPenales >=50)
            {
                partidoAsimular.penales1 = 1;  ///gano el equipo 1
                partidoAsimular.penales2 = 0;

                partidoAsimular.equipo1->win++;
                partidoAsimular.equipo2->loss++;

                ganador = partidoAsimular.equipo1;
                perdedor = partidoAsimular.equipo2;

            }
            else
            {
                partidoAsimular.penales1 = 0;
                partidoAsimular.penales2 = 1;  ///gano el equipo 2

                partidoAsimular.equipo2->win++;
                partidoAsimular.equipo1->loss++;

                ganador = partidoAsimular.equipo2;
                perdedor = partidoAsimular.equipo1;


            }
        }
    }

}

void simularPartidoArreglado (Partido  partidoAsimular, char equipoASimular[], int clasifica) /// para los casos en los que el usuario quiera que un equipo clasifique o no .
{
    srand(time(NULL));
    int rand1 = (rand()%6+1);   ///que gane 5 a 0 como maximo
    int rand2 = 0;
    if(strcmpi(partidoAsimular.equipo1->nomEquipo, equipoASimular)== 0)  ///ganara el primero
    {
        partidoAsimular.golesEq1 = rand1; ///1 a 5
        partidoAsimular.golesEq2 = rand2; /// 0
    }
    else
    {
        if (strcmpi(partidoAsimular.equipo2->nomEquipo, equipoASimular) == 0)  ///ganara el segundo
        {
          partidoAsimular.golesEq1 = rand2; ///0
          partidoAsimular.golesEq2 = rand1;  ///1 a 5
        }
    }

}


void simularFaseDeGrupos (GrupoPartido arrayPartidosGrupos[])  ///simula fase de grupos aleatoriamente
{
    char equipoASimular [20];
    char continuar;
    int clasifica;
    int i ;

    printf("Desea elegir algun equipo? (s/n)");  ///pregunto al usuario si quiere elegir algun equipo para simular
    fflush(stdin);
    gets (&continuar);
    if(continuar == 's' || continuar == 'S')
    {
        printf("ingrese el equipo que desea simular");
        fflush(stdin);
        gets(&equipoASimular);
        printf("Como desea que el equipo se desempeñe? :\n");
        printf("|1| CLASIFICA\n");
        printf("|2| NO CLASIFICA\n");
        scanf("%i", &clasifica);

            for (i = 0 ; i < TAM_MAX_GRUPOS ; i++)  /// aca agarr los grupos
            {
                simulaGrupoArreglado(arrayPartidosGrupos->partidos, equipoASimular, clasifica);  ///simulo los grupos
            }

    }
    else  ///si no quiero que este arreglado, lo simulo aleatoriamente
    {
        for (i = 0 ; i < TAM_MAX_GRUPOS ; i++)
        {
            simulaGrupo (arrayPartidosGrupos->partidos);
        }

    }
}

void simulaGrupo (nodoPartido * partidosGrupo)  ///funcion primaria. Simula grupo aleatoriamente
{
    if(partidosGrupo)
    {
        nodoPartido * seg = partidosGrupo;
        while(seg)
        {
            simularPartido(seg->partido);
            seg = seg->siguiente;
        }
    }
}

void simulaGrupoArreglado (nodoPartido * partidosGrupo, char equipoASimular[], int clasifica) ///simula un grupo con resultado arreglado
{
    if(partidosGrupo)
    {
        nodoPartido * seg = partidosGrupo;
        while(seg)
        {
            if(strcmpi(seg->partido.equipo1, equipoASimular) == 0 || strcmpi(seg->partido.equipo2, equipoASimular) == 0)  ///chequeo que el equipo que quiero simular este entre los dos que juegan partido
            {
                simularPartidoArreglado(seg->partido, equipoASimular, clasifica);   ///simulo el partido con las estadisticas forzadas
            }
            seg = seg->siguiente;
        }
    }
}

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
    Equipo* aux = listaEquipo->equipo;

    if(strcmp(aux->nomEquipo, primero->nomEquipo) == 0)
    {
        seg = seg->siguiente;
        aux = listaEquipo->siguiente;
    }

    while(seg != NULL)
    {
        if(strcmp(aux->nomEquipo, primero->nomEquipo) != 0 && seg->equipo->pts > aux->pts)//si puntos del seg son mayores a los del aux
        {
            aux = seg->equipo;// aux se vuelve seg
        }
        if(strcmp(aux->nomEquipo, primero->nomEquipo) != 0 && seg->equipo->pts == aux->pts)//si son iguales
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


void pasarGanadoresAPlayoffOcatvos(Grupo arrayEquiposGrupos[], fase arrayFase[])///arraygrupo FASE DE GRUPO  arrayFase PLAYOFFS
{

    int i = 0;
    Partido uno;
    for(int i; i < 8; i++)
    {
        Equipo* primero = retornarPrimeroDelGrupo(arrayEquiposGrupos[i].equipos);//estos dos equipos son los primeros del mismo grupo "A" por ejemplo
        Equipo* segundo = retornarSegundoDelGrupo(arrayEquiposGrupos[i].equipos, primero);

        i++;

        Equipo* tercero = retornarPrimeroDelGrupo(arrayEquiposGrupos[i].equipos);//estos dos equipos son los primeros del mismo grupo pero de otro diferente, el grupo siguiente "B" en este caso el siguiente de A va a ser el B
        Equipo* cuarto = retornarSegundoDelGrupo(arrayEquiposGrupos[i].equipos, cuarto);

        nodoPartido* uno = crearNodoPartido(primero, cuarto);///LOS PARTIDOS VIENEN SIN LA FECHA CARGADA
        insertarPartidoOctavos(&(arrayFase[0].partidos), uno);
        nodoPartido* dos = crearNodoPartido(segundo, tercero);///LOS PARTIDOS VIENEN SIN LA FECHA CARGADA
        insertarPartidoOctavos(&(arrayFase[0].partidos), dos);
    }
}



/// CUARTOS
Equipo* vencedor(Partido match)///RETORNA EL EQUIPO GANADOR DEL PARTIDO
{\
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
    simularPartido(lista->partido);
    Equipo* ganador1 = vencedor(lista->partido);///PARTIDO 1A VS 2B
    lista = lista->siguiente;

     simularPartido(lista->partido);
    Equipo* ganador2 = vencedor(lista->partido);///PARTIDO 1B VS 2A
    lista = lista->siguiente;

     simularPartido(lista->partido);
    Equipo* ganador3 = vencedor(lista->partido);///PARTIDO 1C VS 2D
    lista = lista->siguiente;

     simularPartido(lista->partido);
    Equipo* ganador4 = vencedor(lista->partido);///PARTIDO 1D VS 2C
    lista = lista->siguiente;

     simularPartido(lista->partido);
    Equipo* ganador5 = vencedor(lista->partido);///PARTIDO 1E VS 2F
    lista = lista->siguiente;

     simularPartido(lista->partido);
    Equipo* ganador6 = vencedor(lista->partido);///PARTIDO 1F VS 2E
    lista = lista->siguiente;

     simularPartido(lista->partido);
    Equipo* ganador7 = vencedor(lista->partido);///PARTIDO 1G VS 2H
    lista = lista->siguiente;

     simularPartido(lista->partido);
    Equipo* ganador8 = vencedor(lista->partido);///PARTIDO 1H VS 2G



    nodoPartido* match;

    if(*listaCuartos == NULL)///SE CREAN LOS PARTIDOS DE CUARTOS CON SUS RESPECTIVOS EQUIPOS Y SE PONEN EN EL ARREGLO EN LA POSICION 1 YA QUE RECIBIMOS POR PARAMETRO LA LISTA DEL ARREGLO[1]
    {
        match = crearNodoPartido(ganador1, ganador3);
        *listaCuartos = match;
    }

    nodoPartido* seg = (*listaCuartos)->siguiente;

    match = crearNodoPartido(ganador5, ganador7);
    seg = match;
    seg = seg->siguiente;

    match = crearNodoPartido(ganador2, ganador4);
    seg = match;
    seg = seg->siguiente;

    match = crearNodoPartido(ganador6, ganador8);
    seg = match;
    seg = seg->siguiente;
}

void pasarGanadoresACuartos(fase arrayFase[])
{
    pasarEquiposACuartos(arrayFase[0].partidos, &(arrayFase[1].partidos));
}


///SEMIFINAL

void pasarEquiposASemis(nodoPartido* listaCuartos, nodoPartido** listaSemis)
{
     simularPartido(listaCuartos->partido);
    Equipo* semi1 = vencedor(listaCuartos->partido);///PARTIDO entre el ganador1 vs ganador3
    listaCuartos = listaCuartos->siguiente;

     simularPartido(listaCuartos->partido);
    Equipo* semi2 = vencedor(listaCuartos->partido);///PARTIDO entre el ganador5 vs ganador7
    listaCuartos = listaCuartos->siguiente;

     simularPartido(listaCuartos->partido);
    Equipo* semi3 = vencedor(listaCuartos->partido);///PARTIDO entre el ganador2 vs ganador4
    listaCuartos = listaCuartos->siguiente;

     simularPartido(listaCuartos->partido);
    Equipo* semi4 = vencedor(listaCuartos->partido);///PARTIDO entre el ganador6 vs ganador8
    listaCuartos = listaCuartos->siguiente;


    nodoPartido* match;

    if(*listaSemis == NULL)
    {
        match = crearNodoPartido(semi1, semi2);
        *listaSemis = match;
    }

    match = crearNodoPartido(semi3, semi4);
    (*listaSemis)->siguiente = match;
}

void pasarGanadoresASemis(fase arrayFase[])
{
    pasarEquiposASemis(arrayFase[1].partidos, &(arrayFase[2].partidos));
}


///TERCER POSTO

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
     simularPartido(listaSemis->partido);
    Equipo* derrotado1 = perdedor(listaSemis->partido);
    listaSemis = listaSemis->siguiente;

    simularPartido(listaSemis->partido);
    Equipo* derrotado2 = perdedor(listaSemis->partido);

    nodoPartido* match = crearNodoPartido(derrotado1, derrotado2);

    *listaTercerPuesto = match;
}

void pasarGanadoresATercerPuesto(fase arrayFase[])
{
    pasarEquiposATercerPuesto(arrayFase[2].partidos, &(arrayFase[3].partidos));
}


///FINAL

void pasarEquiposAFinal(nodoPartido* listaSemis, nodoPartido** listaFinal)
{
    Equipo* finalista1 = vencedor(listaSemis->partido);
    listaSemis = listaSemis->siguiente;

    Equipo* finalista2 = vencedor(listaSemis->partido);

    nodoPartido* match = crearNodoPartido(finalista1, finalista2);

    *listaFinal = match;
}

void pasarGanadoresAFinal(fase arrayFase[])
{

    pasarEquiposAFinal(arrayFase[2].partidos, &(arrayFase[4].partidos));
}


void jugarFinal (fase arrayFase[])
{
    pasarGanadorYSegundoPuesto (arrayFase[4].partidos);
}

void pasarGanadorYSegundoPuesto (nodoPartido * listaFinal)
{
    Equipo * Campeon = vencedor(listaFinal->partido);
    Equipo * subCampeon = perdedor(listaFinal->partido);
}
