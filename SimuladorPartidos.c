#include "declaraciones_variables.h"
#include "declaraciones_funciones.h"

Equipo* retornarPrimeroDelGrupo(nodoGrupoEquipo* listaEquipo)
{

    nodoGrupoEquipo* seg = listaEquipo->siguiente;
    Equipo* aux = listaEquipo->equipo;

    while(seg != NULL)
    {
        if(seg->equipo->pts > aux->pts)
        {
            aux = seg->equipo;
        }
        if(seg->equipo->pts == aux->pts)
        {
            if(seg->equipo->gf > aux->gf)
            {
                aux = seg->equipo;
            }
            if(seg->equipo->gf == aux->gf)
            {
                if(seg->equipo->ga < aux->ga)
                {
                    aux = seg->equipo;
                }
            }
        }
    }

    return aux;


}



void pasarGanadoresAPlayoffOcatvos(Grupo arrayEquiposGrupos, fase arrayFase)///arraygrupo FASE DE GRUPO  arrayFase PLAYOFFS
{

    int i = 0;
    for(int i; i < 4; i++)
    {


        Equipo* primero = retornarPrimeroDelGrupo(arrayEquiposGrupos.equipos);//estos dos equipos son los primeros del mismo grupo "A" por ejemplo
        Equipo* segundo = retornarSegundoDelGrupo(arrayEquiposGrupos[i].equipos);

        i++;

        Equipo* tercero = retornarPrimeroDelGrupo(arrayEquiposGrupos[i]->equipos);//estos dos equipos son los primeros del mismo grupo pero de otro diferente, el grupo siguiente "B" en este caso el siguiente de A va a ser el B
        Equipo* cuarto = retornarSegundoDelGrupo(arrayEquiposGrupos[i]->equipos);

        Partido uno = crearPartido(primero, cuarto);
        insertarPartidoOctavos(&(arrayFase[0].partidos), uno);
        Partido dos = crearPartido(segundo, tercero);
        insertarPartidoOctavos(&(arrayFase[0].partidos), dos);

    }

}

