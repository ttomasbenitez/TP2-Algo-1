#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include "test_de_personalidad.h"
#include "osos_contra_reloj.h" 
#include "utiles.h"

static const int TERMINADO = -1;

static const double TIEMPO_RESTANTE_INICIO = 160;

const char JUGADA_INVALIDA = 'J';

const unsigned int TRES_SEGUNDOS = 3;
const unsigned int CINCO_SEGUNDOS = 5;


void presentar_juego(){
    printf("\nUn día, aburridos de estar encerrados, los Osos y Chloe decidieron salir al bosque y jugar a las escondidas.\n");
    sleep(TRES_SEGUNDOS);
    system("clear");
    
    printf("\nSin embargo, se olvidaron del toque de queda que rige debido a los aumentos de casos de Covid en la ciudad y ya está oscureciendo.\n");
    sleep(TRES_SEGUNDOS);
    system("clear");
    
    printf("\nAdemás tienen otro problema: Chloe sigue escondida y no sabe que ya tienen que volver a casa.\n");
    sleep(TRES_SEGUNDOS);
    system("clear");

    printf("\nAyudá a tu oso a encontrar a su amiga antes de que comience el confinamiento obligatorio.\n");
    sleep(TRES_SEGUNDOS);
    system("clear");

    printf("\n¡Pero hay un problema más! Ya se hizo de noche en el bosque y el personaje no podrá ver nada de lo que hay a su alrededor,\n");
    printf("\ny deberá ayudarse de su linterna, velas y bengalas para poder llegar a encontrarse con su amiga.\n");
    sleep(CINCO_SEGUNDOS);
    system("clear");

    printf("\nPRIMERO DETERMINAREMOS TU PERSONAJE MEDIANTE UN RAPIDO TEST\n");
    sleep(TRES_SEGUNDOS);
    system("clear");
}


//POST: Pide una jugada hasta que se ingrese una jugada valida: W(Arriba), A(Izquierda), S(Abajo), D(derecha), L(linterna), V(vela), E(bengala) o T(tiempo_restante).
// Guarda la jugada ingresada.
void pedir_jugada(char* jugada){
    printf("\nQue queres hacer??\n");
    printf("\nPara moverte: W(arriba), A(izquierda), S(abajo), D(derecha).\n");
    printf("\nPara usar herramienta: L(linterna), V(vela), E(bengala). T para ver el tiempo transcurrido\n");
    scanf(" %c", jugada);

    while(!es_jugada_valida(*jugada)){
        printf("\nEsa no es una jugada valida: \n");
        printf("\nPara moverte: W(arriba), A(izquierda), S(abajo), D(derecha).\n");
        printf("\nPara usar herramienta: L(linterna), V(vela), E(bengala). T para ver el tiempo transcurrido\n");
        scanf(" %c", jugada);
    }
}

//PRE: Recibe un juego en estado TERMINADO.
//POST: Muestra el resultado del juego, si GANASTE(tiempo empleado menor a TIEMPO_RESTANTE_INICIO) o PERDISTE(tiempo empleado mayor a TIEMPO_RESTANTE_INICIO).
void terminar_juego(juego_t juego){
    system("clear");
    
    if(detener_cronometro() + juego.personaje.tiempo_perdido > TIEMPO_RESTANTE_INICIO){
        printf("\n TE AGARRO EL TOQUE DE QUEDA\n");
    printf("\
        (_)(_)(_)(_)_  (_)(_)(_)(_)(_)  (_)(_)(_)(_) _   (_)(_)(_)(_)    (_)(_)(_)  _(_)(_)(_)(_)_  (_)(_)(_)(_)(_) (_)(_)(_)(_)(_)\n \
        (_)        (_) (_)              (_)         (_)   (_)      (_)_     (_)    (_)          (_)       (_)       (_)            \n \
        (_) _  _  _(_) (_) _  _         (_) _  _  _ (_)   (_)        (_)    (_)    (_)_  _  _  _          (_)       (_) _  _       \n \
        (_)(_)(_)(_)   (_)(_)(_)        (_)(_)(_)(_)      (_)        (_)    (_)      (_)(_)(_)(_)_        (_)       (_)(_)(_)      \n \
        (_)            (_)              (_)   (_) _       (_)       _(_)    (_)     _           (_)       (_)       (_)            \n \
        (_)            (_) _  _  _  _   (_)      (_) _    (_)_  _  (_)    _ (_) _  (_)_  _  _  _(_)       (_)       (_) _  _  _  _ \n \
        (_)            (_)(_)(_)(_)(_)  (_)         (_)  (_)(_)(_)(_)    (_)(_)(_)   (_)(_)(_)(_)         (_)       (_)(_)(_)(_)(_)\n ");                                                                                                                                   
    }
    else{   
        printf("   ######       ###      ##    ##      ###      ######  ########  ######## \n");
        printf("  ##    ##     ## ##     ###   ##     ## ##    ##    ##    ##     ##       \n");
        printf("  ##          ##   ##    ####  ##    ##   ##   ##          ##     ##       \n");
        printf("  ##   ####  ##     ##   ## ## ##   ##     ##   ######     ##     ######   \n");
        printf("  ##    ##   #########   ##  ####   #########        ##    ##     ##       \n");
        printf("  ##    ##   ##     ##   ##   ###   ##     ##  ##    ##    ##     ##       \n");
        printf("   ######    ##     ##   ##    ##   ##     ##   ######     ##     ######## \n");
        printf("\n Q grande\n");
    }
}

int main(){
    presentar_juego();

    char personalidad_detectada;
    test_de_personalidad(&personalidad_detectada);

    char tipo_personaje = personalidad_detectada;
    system("clear");

    char jugada = JUGADA_INVALIDA;

    juego_t juego;

    srand ((unsigned)time(NULL));


    inicializar_juego(&juego, tipo_personaje);
    mostrar_juego(juego);
    
    while(estado_juego(juego) != TERMINADO){
        pedir_jugada(&jugada);
        realizar_jugada(&juego, jugada);
        mostrar_juego(juego);       
    }

    terminar_juego(juego);
    

    return 0;
}   