#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "osos_contra_reloj.h" 
#include "test_de_personalidad.h"
#include "utiles.h"

static const int NUMERO_FILAS = 20;
static const int NUMERO_COLUMNAS = 30;

const char CHLOE = 'C';

static const char ARBOL = 'A';
static const char PIEDRA = 'R';
static const char KOALA = 'K';

static const char LINTERNA = 'L';
static const char VELA = 'V';
static const char BENGALA = 'E';
static const char PILA = 'B';

#define POSICION_LINTERNA 0

const int ELEMENTOS_INICIO_POLAR_PANDA = 7;
const int ELEMENTOS_INICIO_PARDO = 5;

const int VELAS_INICIO_POLAR = 6;
const int VELAS_INICIO_PARDO_PANDA = 4;
const int LINTERNA_INICIAL = 1;
const int BENGALAS_INICIO_PANDA = 2;

const int VIDA_LINTERNA_PARDO = 15;
const int VIDA_LINTERNA_POLAR_PANDA = 10;
const int VIDA_UTIL_VELA = 5;
const int VIDA_UTIL_BENGALA = 3;

const int ARBOLES_EN_BOSQUE = 350;
const int PIEDRAS_EN_BOSQUE = 80;
const int KOALA_NOM_NOM = 1;

const int PILAS_RECOLECTABLES = 30;
const int VELAS_RECOLECTABLES = 30;
const int BENGALAS_RECOLECTABLES = 10;

static const int JUGANDO = 0;
static const int TERMINADO = -1;

const int MINIMO_MOVIMIENTO_RESTANTE = 1;

const int FILA_CERO = 0; 
const int ULTIMA_FILA = 19;
const int COLUMNA_CERO = 0;
const int ULTIMA_COLUMNA = 29;

const int DISTANCIA_CERO = 0; 
const int DISTANCIA_DE_UNO = 1; 
const int DISTANCIA_DE_DOS = 2; 
const int DISTANCIA_DE_TRES = 3; 

static const double TIEMPO_RESTANTE_INICIO = 160;

static const char ARRIBA = 'W';
static const char IZQUIERDA = 'A';
static const char ABAJO = 'S';
static const char DERECHA = 'D';
static const char TIEMPO_RESTANTE = 'T';

const int TIEMPO_PERDIDO_PANDA = 30;

const double SEG_PERDIDO_ARBOL_PARDO = 0.5;
const int SEG_PERDIDO_ARBOL_OTRO = 1;
const int SEG_PERDIDO_PIEDRA = 2;

const int MUCHO_TIEMPO_TRANSCURRIDO = 130;

const int MOVIMIENTOS_POR_PILA = 5;

const int NADA_EN_USO = -1;
const int POSICION_INEXISTENTE = -2;

const int SEGUNDO_CERO = 0;

const char VACIO = '.';



//PRE: Recibe un tipo_personaje: Polar(I), Panda(P) o Pardo(G), a partir de detector_de_personajes.h. Y recibe un personaje_t sin todos sus campos inicializados.
//POST: Almacena el tipo_personaje en juego_t.
void detectar_personaje(personaje_t* personaje, char tipo_personaje){

    if(tipo_personaje == POLAR){
        personaje->tipo = POLAR;
    }
    else if(tipo_personaje == PARDO){
        personaje->tipo = PARDO;
    }
    else{
        personaje->tipo = PANDA;
    }
}

//PRE: Recibe un juego_t sin todos sus campos inicializados.
//POST: Inicializa los tipos de obstaculos: Arbol(A), Piedra(R) o Koala(K), en juego_t. Y cuantos seran inicialmente.
void inicializar_obstaculos(juego_t* juego){
    juego->obstaculos->tipo = ARBOL;
    juego->obstaculos->tipo = PIEDRA;
    juego->obstaculos->tipo = KOALA;

    juego->cantidad_obstaculos = ARBOLES_EN_BOSQUE + PIEDRAS_EN_BOSQUE + KOALA_NOM_NOM;
}

//PRE: Recibe un juego_t sin todos sus campos inicializados.
//POST: Inicializa los tipos de herramientas: Vela(V), Bengala(E) o Pila(B), en juego_t. Y cuantas seran inicialmente.
void inicializar_herramientas(juego_t* juego){
    juego->herramientas->tipo = VELA;
    juego->herramientas->tipo = BENGALA;
    juego->herramientas->tipo = PILA;

    juego->cantidad_herramientas = PILAS_RECOLECTABLES + BENGALAS_RECOLECTABLES + VELAS_RECOLECTABLES;
}

//PRE:Recibe un personaje_t sin todos sus campos inicializados.
//POST: Inicializa los elementos de la mochila: Linterna(L), Vela(V) o Bengala(E). Y cuantos habra de cada uno segun que oso sea el personaje.
void inicializar_elementos_mochila(personaje_t* personaje){
    personaje->mochila->tipo = LINTERNA;
    personaje->mochila->tipo = VELA;
    personaje->mochila->tipo = BENGALA;

    if(personaje->tipo == POLAR){
        personaje->cantidad_elementos = VELAS_INICIO_POLAR + LINTERNA_INICIAL;
    }
    else if(personaje->tipo == PARDO){
        personaje->cantidad_elementos = VELAS_INICIO_PARDO_PANDA + LINTERNA_INICIAL;
    }
    else{
        personaje->cantidad_elementos = VELAS_INICIO_PARDO_PANDA + LINTERNA_INICIAL + BENGALAS_INICIO_PANDA;
    }
}

//PRE:Recibe un personaje_t sin todos sus campos inicializados.
//POST: Carga la mochila segun el tipo de personaje obtenido. 
// Inicializa ultimo_movimiento con Derecha(D), elemento_en_uso con NADA_EN_USO (-1) y tiempo_perdido = 0, por convencion.
void inicializar_mochila_segun_oso(personaje_t* personaje){
    for(int i = 0; i < (personaje->cantidad_elementos); i++){
        if(personaje->tipo == POLAR){
            personaje->mochila[POSICION_LINTERNA].tipo = LINTERNA;
            personaje->mochila[i+1].tipo = VELA;
        }
        else if(personaje->tipo == PARDO){
            personaje->mochila[POSICION_LINTERNA].tipo = LINTERNA;
            personaje->mochila[i+1].tipo = VELA;
        }
        else{
            personaje->mochila[POSICION_LINTERNA].tipo = LINTERNA;

            if(i <= VELAS_INICIO_PARDO_PANDA){
                personaje->mochila[i+1].tipo = VELA;
            }
            else{
                personaje->mochila[i].tipo = BENGALA;
            }
        }
    

        if(personaje->mochila[i].tipo == LINTERNA){
            if( (personaje->tipo == POLAR) || (personaje->tipo == PANDA) ){
                personaje->mochila[i].movimientos_restantes = VIDA_LINTERNA_POLAR_PANDA;
            }
            else{
                personaje->mochila[i].movimientos_restantes = VIDA_LINTERNA_PARDO;
            }
        }
        else if(personaje->mochila[i].tipo == VELA){
            personaje->mochila[i].movimientos_restantes = VIDA_UTIL_VELA;
        }
        else if(personaje->mochila[i].tipo == BENGALA){
            personaje->mochila[i].movimientos_restantes = VIDA_UTIL_BENGALA;
        }
    }

    personaje->elemento_en_uso = NADA_EN_USO;
    personaje->tiempo_perdido = 0;
    personaje->ultimo_movimiento = DERECHA;
}


//PRE: Recibe un juego_t sin todos sus campos inicializados.
//POST: Carga todos los obstaculos segun su tipo en obstaculos[MAX_OBSTACULOS] y los inicializa NO visibles.
void inicializar_vector_obstaculos(juego_t* juego){
    for(int i = 0; i < (juego->cantidad_obstaculos); i++){
        if(i < ARBOLES_EN_BOSQUE){
            juego->obstaculos[i].tipo = ARBOL;
            juego->obstaculos[i].visible = false;
        }
        else if(i < (ARBOLES_EN_BOSQUE + PIEDRAS_EN_BOSQUE) ){
            juego->obstaculos[i].tipo = PIEDRA;
            juego->obstaculos[i].visible = false;
        }
        else{
            juego->obstaculos[i].tipo = KOALA;
            juego->obstaculos[i].visible = false;
        }
    }
}

//PRE: Recibe un juego_t sin todos sus campos inicializados.
//POST: Carga todas las herramientas segun su tipo en herramientas[MAX_HERRAMIENTAS].
void inicializar_vector_herramientas(juego_t* juego){
    int pilas_mas_velas = PILAS_RECOLECTABLES + VELAS_RECOLECTABLES;
    
    for(int i = 0; i < (juego->cantidad_herramientas); i++){
        if(i < PILAS_RECOLECTABLES){
            juego->herramientas[i].tipo = PILA;
        }
        else if( (i >= PILAS_RECOLECTABLES) && (i < pilas_mas_velas) ){
            juego->herramientas[i].tipo = VELA;
        }
        else{
            juego->herramientas[i].tipo = BENGALA;
        }
    }
}

//PRE: Recibe una fil_aleatoria y una col_aleatoria.
//POST: Devuelve TRUE si en esa fil_aleatoria y en esa col_aleatoria ya hay algun elemento o personaje.
bool hay_elementos(juego_t juego, int fil_aleatoria, int col_aleatoria){
    int i = 0;

    bool esta_ocupada = false;

    while( (i < juego.cantidad_obstaculos) && (!esta_ocupada) ){
        if( (fil_aleatoria == juego.personaje.posicion.fil) && (col_aleatoria == juego.personaje.posicion.col) ){
            esta_ocupada = true;
        }
        else if( (fil_aleatoria == juego.amiga_chloe.fil) && (col_aleatoria == juego.amiga_chloe.col) ){
            esta_ocupada = true;
        }
        else if( (fil_aleatoria == juego.obstaculos[i].posicion.fil) && (col_aleatoria == juego.obstaculos[i].posicion.col) ){
            esta_ocupada = true;
        }
        else if( (fil_aleatoria == juego.herramientas[i].posicion.fil) && (col_aleatoria == juego.herramientas[i].posicion.col) ){
            esta_ocupada = true;
        }
        i++;
    }
    return esta_ocupada;
}

//PRE: Recibe un juego_t sin todos sus campos inicializados.
//POST: Genera una fil_aleatoria y una col_aleatoria hasta que no sean posiciones ocupadas.
void generar_posicion_aleatoria(juego_t* juego, int* fil_aleatoria, int* col_aleatoria){
    (*fil_aleatoria) = rand() % NUMERO_FILAS;
    (*col_aleatoria) = rand() % NUMERO_COLUMNAS;

    while(hay_elementos(*juego, *fil_aleatoria, *col_aleatoria)){
        (*fil_aleatoria) = rand() % NUMERO_FILAS;
        (*col_aleatoria) = rand() % NUMERO_COLUMNAS; 
    }
}

//PRE: Recibe una fil_aleatoria. Y un personaje_t sin todos sus campos inicializados.
//POST: Inicializa la posicion del oso en fil_aleatoria y la columna cero.
void generar_posicion_oso(personaje_t* personaje, int fil_aleatoria, int col_aleatoria){
    personaje->posicion.fil = fil_aleatoria;
    personaje->posicion.col = COLUMNA_CERO;
}

//PRE: Recibe una fil_aleatoria y una col_aleatoria libres. Y un juego_t sin todos sus campos inicializados.
//POST: Inicializa la posicion de Chloe en fil_aleatoria y col_aleatoria, e inicializa a Chloe NO visible.
void generar_posicion_chloe(juego_t* juego, int fil_aleatoria, int col_aleatoria){
    generar_posicion_aleatoria(juego, &fil_aleatoria, &col_aleatoria);
    
    juego->amiga_chloe.fil = fil_aleatoria;
    juego->amiga_chloe.col = col_aleatoria;

    juego->chloe_visible = false;
}


//PRE: Recibe una fil_aleatoria y una col_aleatoria, libres, para cada obstaculo de obstaculos[MAX_OBSTACULOS]. Y recibe un juego_t sin todos sus campos inicializados.
//POST: Inicializa la posicion de cada obstaculo en cada fil_aleatoria y cada col_aleatoria.
void generar_posicion_obstaculos(juego_t* juego, int fil_aleatoria, int col_aleatoria){
    for(int i = 0; i < (juego->cantidad_obstaculos); i++){
        generar_posicion_aleatoria(juego, &fil_aleatoria, &col_aleatoria);
        if(juego->obstaculos[i].tipo == ARBOL){
            juego->obstaculos[i].posicion.fil = fil_aleatoria;
            juego->obstaculos[i].posicion.col = col_aleatoria; 
        }
        else if(juego->obstaculos[i].tipo == PIEDRA){
            juego->obstaculos[i].posicion.fil = fil_aleatoria;
            juego->obstaculos[i].posicion.col = col_aleatoria; 
        }
        else{
            juego->obstaculos[i].posicion.fil = fil_aleatoria;
            juego->obstaculos[i].posicion.col = col_aleatoria; 
        }
    }
}

//PRE: Recibe una fil_aleatoria y una col_aleatoria, libres, para cada herramienta de herramientas[MAX_HERRAMIENTAS].
//POST: Inicializa la posicion de cada herramienta en cada fil_aleatoria y cada col_aleatoria.
void generar_posicion_herramientas(juego_t* juego, int fil_aleatoria, int col_aleatoria){
    for(int i = 0; i < (juego->cantidad_herramientas); i++){
        generar_posicion_aleatoria(juego, &fil_aleatoria, &col_aleatoria);
        if(juego->herramientas[i].tipo == PILA){
            juego->herramientas[i].posicion.fil = fil_aleatoria;
            juego->herramientas[i].posicion.col = col_aleatoria; 
        }
        else if(juego->herramientas[i].tipo == VELA){
            juego->herramientas[i].posicion.fil = fil_aleatoria;
            juego->herramientas[i].posicion.col = col_aleatoria; 
        }
        else{
            juego->herramientas[i].posicion.fil = fil_aleatoria;
            juego->herramientas[i].posicion.col = col_aleatoria; 
        }
    }
}



/*
 * Inicializará el juego, cargando toda la información inicial
 * y los datos del personaje. 
 */
void inicializar_juego(juego_t* juego, char tipo_personaje){
    int fil_aleatoria = 0;
    int col_aleatoria = 0;

    detectar_personaje(&(juego->personaje), tipo_personaje);
    inicializar_obstaculos(juego);
    inicializar_herramientas(juego);
    inicializar_elementos_mochila(&(juego->personaje));
    inicializar_mochila_segun_oso(&(juego->personaje));
    inicializar_vector_obstaculos(juego);
    inicializar_vector_herramientas(juego);
   
    hay_elementos( (*juego), fil_aleatoria, col_aleatoria);
    generar_posicion_aleatoria(juego, &fil_aleatoria, &col_aleatoria);
    generar_posicion_oso(&(juego->personaje), fil_aleatoria, col_aleatoria);
    generar_posicion_chloe(juego, fil_aleatoria, col_aleatoria);
    generar_posicion_obstaculos(juego, fil_aleatoria, col_aleatoria);
    generar_posicion_herramientas(juego, fil_aleatoria, col_aleatoria);
    
    iniciar_cronometro();
}


/*
 * Recibe un juego con todas sus estructuras válidas.
 *
 * El juego se dará por terminado, si el personaje encontró a Chloe. 
 * Devolverá:
 * -> 0 si el estado es jugando. 
 * -> -1 si el estado es terminado.
 */

int estado_juego(juego_t juego){
    int estado = 0;

    if( (juego.personaje.posicion.fil == juego.amiga_chloe.fil) && (juego.personaje.posicion.col == juego.amiga_chloe.col) ){
        estado = TERMINADO;
    }
    else{
        estado = JUGANDO;
    }

    return estado;
}


/*
 * Devolvera true en caso de ser una jugada valida (W,A,S,D,L,V,E o T)
 * Devolvera false en caso contrario.
 */
bool es_jugada_valida(char jugada){
    return ( (jugada == ARRIBA) || (jugada == IZQUIERDA) || (jugada == ABAJO) || (jugada == DERECHA)|| (jugada == LINTERNA) || (jugada == VELA) || (jugada == BENGALA) || (jugada == TIEMPO_RESTANTE) );
}

//PRE: Recibe una jugada valida y un personaje_t con sus campos validos.
//POST: Devuelve TRUE, si el personaje esta en un borde y la jugada D, A, W o S va en la direccion del borde. 
bool esta_personaje_en_borde(personaje_t personaje, char jugada){
    bool en_borde = false;

    if(jugada == DERECHA){
        if(personaje.posicion.col == ULTIMA_COLUMNA){
            en_borde = true;
        }
    }
    else if(jugada == IZQUIERDA){
        if(personaje.posicion.col == COLUMNA_CERO){
            en_borde = true;
        }
    }
    else if(jugada == ABAJO){
        if(personaje.posicion.fil == ULTIMA_FILA){
            en_borde = true;
        }
    }
    else if(jugada == ARRIBA){
        if(personaje.posicion.fil == FILA_CERO){
            en_borde = true;
        }
    }

    return (en_borde); 
}

//PRE: Recibe un juego con todos sus obstaculos con una fil y una col asignadas.
//POST: Devuelve TRUE si algun obstaculo coincide en fil y col con el personaje, y guarda la posicion en el vector de ese obstaculo.
bool es_posicion_obstaculo(juego_t juego, int* posicion_obstaculo){
    int i = 0;
    bool hay_obstaculo = false;

    while( (i < juego.cantidad_obstaculos) && (!hay_obstaculo) ){
        if( (juego.personaje.posicion.fil == juego.obstaculos[i].posicion.fil) && (juego.personaje.posicion.col == juego.obstaculos[i].posicion.col) ){
            hay_obstaculo = true;
            (*posicion_obstaculo) = i;
        }
        i++;
    }
    return hay_obstaculo;
}

//Recibe una jugada valida.
//Devuelve true si la jugada es A, D, S o W.
bool choca_obstaculo_solo_una_vez(char jugada){
    return ( (jugada == DERECHA) || (jugada == IZQUIERDA) || (jugada == ABAJO) || (jugada == ARRIBA) );
}


//PRE: Recibe una posicion de obstaculo. Y recibe un juego en estado JUGANDO.
//POST: Dependiendo quien sea el personaje y cual sea el tipo de obstaculo, suma tiempo perdido si el personaje esta en la misma fil y col que un obstaculo.
//      Solo sumara segundos a tiempo_perdido una vez por cada obstaculo, mientras que el personaje no cambie su posicion.
void chocar_obstaculo(juego_t* juego, int posicion_obstaculo, char jugada){
    if( es_posicion_obstaculo((*juego), &posicion_obstaculo) && choca_obstaculo_solo_una_vez(jugada) && (!esta_personaje_en_borde((juego->personaje), jugada)) ){
        if(juego->obstaculos[posicion_obstaculo].tipo == ARBOL){
            if(juego->personaje.tipo == PARDO){
                juego->personaje.tiempo_perdido += SEG_PERDIDO_ARBOL_PARDO;
            }
            else{
                juego->personaje.tiempo_perdido += SEG_PERDIDO_ARBOL_OTRO;
            }
        }
        else if(juego->obstaculos[posicion_obstaculo].tipo == PIEDRA){
            if(juego->personaje.tipo != POLAR){
                juego->personaje.tiempo_perdido += SEG_PERDIDO_PIEDRA;
            }
        }
    }
}


//PRE: Recibe el vector herramientas[MAX_HERRAMIENTAS] con todas sus herramientas con una fil y una col asignadas. Y recibe un juego en estado JUGANDO.
//POST: Devuelve TRUE si alguna herramienta coincide en fil y col con el personaje, y guarda la posicion en el vector de esa herramienta.
bool es_posicion_herramienta(juego_t juego, int* posicion_herramienta){
    int i = 0;
    bool hay_herramienta = false;

    while( (i < juego.cantidad_herramientas) && (!hay_herramienta) ){
        if( (juego.personaje.posicion.fil == juego.herramientas[i].posicion.fil) && (juego.personaje.posicion.col == juego.herramientas[i].posicion.col) ){
            hay_herramienta = true;
            (*posicion_herramienta) = i;
        }
        i++;
    }
    return hay_herramienta;
}

//PRE: Recibe una posicion de herramienta que coincida con la posicion del personaje y recibe un juego en estado JUGANDO.
//POST: Elimina la herramienta de el vector herramientas[MAX_HERRAMIENTAS], achicando el tope en 1.
void recoger_herramienta(juego_t* juego, int posicion_herramienta){
    if(es_posicion_herramienta((*juego), &posicion_herramienta)){
        juego->herramientas[posicion_herramienta] = juego->herramientas[(juego->cantidad_herramientas)-1];
        (juego->cantidad_herramientas)--;
    }
}


//PRE: Recibe una posicion de herramienta que coincida con la posicion del personaje y recibe un juego en estado JUGANDO.
//POST: Agrega al vector mochila[] la herramienta de la posicion_herramienta, segun su tipo e inicializa sus movimientos, en el caso que tipo sea VELA(V) o BENGALA(E).
//      Si en posicion_herramienta tipo es PILA(B), suma 5 movimientos a la linterna.
void guardar_herramienta_mochila(juego_t* juego, int posicion_herramienta){
    if(es_posicion_herramienta((*juego), &posicion_herramienta)){
        if( (juego->herramientas[posicion_herramienta].tipo == VELA) || (juego->herramientas[posicion_herramienta].tipo == BENGALA) ){
            (juego->personaje.cantidad_elementos)++;
        }
        
        for(int i = 0; i < (juego->personaje.cantidad_elementos); i++){
            if(juego->herramientas[posicion_herramienta].tipo == VELA){
                juego->personaje.mochila[(juego->personaje.cantidad_elementos)-1].tipo = VELA; 
                juego->personaje.mochila[(juego->personaje.cantidad_elementos)-1].movimientos_restantes = VIDA_UTIL_VELA;  
            }
            else if(juego->herramientas[posicion_herramienta].tipo == BENGALA){
                juego->personaje.mochila[(juego->personaje.cantidad_elementos)-1].tipo = BENGALA;
                juego->personaje.mochila[(juego->personaje.cantidad_elementos)-1].movimientos_restantes = VIDA_UTIL_BENGALA;
            }
            else{
                if(juego->personaje.mochila[i].tipo == LINTERNA){
                    juego->personaje.mochila[i].movimientos_restantes += MOVIMIENTOS_POR_PILA;
                }
            }   
        }
    }
}

//PRE: Recibe un juego en estado JUGANDO.
//POST: Si el tiempo_perdido es mayor a 30 y el tipo personaje es PANDA(P), chloe.visible se actualizara a TRUE.
void ve_panda_a_chloe(juego_t* juego){
    if( (juego->personaje.tipo == PANDA) && (juego->personaje.tiempo_perdido >= TIEMPO_PERDIDO_PANDA) ){
        juego->chloe_visible = true;
    }
}



//PRE: Recibe un juego en estado JUGANDO.
//POST: Si jugada es LINTERNA(L) y elemento_en_uso es POSICION_LINTERNA aumentara en 1 el tope_obstaculos, se agregara un obstaculo de tipo KOALA(K) al vector obstaculos
//      y se le asigara una posicion libre generada aleatoriamente.
void generar_koala(juego_t* juego, char jugada, int fil_aleatoria, int col_aleatoria){
    
    if( (juego->personaje.elemento_en_uso == POSICION_LINTERNA) && (jugada == LINTERNA)){
        (juego->cantidad_obstaculos)++;
        juego->obstaculos[juego->cantidad_obstaculos-1].tipo = KOALA;
        generar_posicion_aleatoria(juego, &fil_aleatoria, &col_aleatoria);

        for(int i = 0; i < (juego->cantidad_obstaculos); i++){
            if(juego->obstaculos[i].tipo == KOALA){
                juego->obstaculos[juego->cantidad_obstaculos-1].posicion.fil = fil_aleatoria;
                juego->obstaculos[juego->cantidad_obstaculos-1].posicion.col = col_aleatoria; 
            }
        }
    }
}

//PRE: Recibe un juego en estado JUGANDO.
//POST: Si el personaje se encuentra en la misma posicion que un KOALA(K), este sera enviado a una posicion libre de columna cero y fila aleatoria.
void chocar_koala(juego_t* juego, int fil_aleatoria, int col_aleatoria){
    generar_posicion_aleatoria(juego, &fil_aleatoria, &col_aleatoria);

    for(int i = 0; i < (juego->cantidad_obstaculos); i++){
        if(juego->obstaculos[i].tipo == KOALA){
            if( (juego->personaje.posicion.fil == juego->obstaculos[i].posicion.fil) && (juego->personaje.posicion.col == juego->obstaculos[i].posicion.col) ){
                juego->personaje.posicion.fil = fil_aleatoria; 
                juego->personaje.posicion.col = COLUMNA_CERO; 
            }
        }
    }
}

//PRE: Recibe un juego en estado JUGANDO.
//POST: Actualiza chloe_visible a TRUE, si chloe esta en la misma, fila o columna que el personaje.
//      Y en la misma direccion que el ultimo_movimiento.
void esta_chloe_en_rango_linterna(juego_t* juego){
    
    if(juego->personaje.ultimo_movimiento == DERECHA){
        if( (juego->personaje.posicion.fil == juego->amiga_chloe.fil) && (juego->personaje.posicion.col < juego->amiga_chloe.col) ){
            juego->chloe_visible = true;
        }
        else{
            juego->chloe_visible = false;
        }
    }
    else if(juego->personaje.ultimo_movimiento == IZQUIERDA){
        if( (juego->personaje.posicion.fil == juego->amiga_chloe.fil) && (juego->personaje.posicion.col > juego->amiga_chloe.col) ){
            juego->chloe_visible = true;
        }
        else{
            juego->chloe_visible = false;
        }
    }
    else if(juego->personaje.ultimo_movimiento == ABAJO){
        if( (juego->amiga_chloe.col == juego->personaje.posicion.col) && (juego->amiga_chloe.fil > juego->personaje.posicion.fil) ){
            juego->chloe_visible = true;
        }
        else{
            juego->chloe_visible = false;
        }
    }
    else if((juego->personaje.ultimo_movimiento == ARRIBA)){
        if( (juego->amiga_chloe.col == juego->personaje.posicion.col) && (juego->amiga_chloe.fil < juego->personaje.posicion.fil) ){
            juego->chloe_visible = true;
        }
        else{
            juego->chloe_visible = false;
        }
    }
}

//PRE: Recibe un juego en estado JUGANDO.
//POST: Actualiza obstaculo[i].visible como TRUE, a cada obstaculo[i] que este en la misma fila o columna que el personaje.
//      Y en la misma direccion que el ultimo_movimiento.
void esta_obstaculo_en_rango_linterna(juego_t* juego){
    for(int i = 0; i < (juego->cantidad_obstaculos); i++){
        if(juego->personaje.ultimo_movimiento == DERECHA){
            if( (juego->obstaculos[i].posicion.fil == juego->personaje.posicion.fil) && (juego->obstaculos[i].posicion.col > juego->personaje.posicion.col) ){
                juego->obstaculos[i].visible = true;
            }
            else{
                juego->obstaculos[i].visible = false;
            }
        }
        else if(juego->personaje.ultimo_movimiento == IZQUIERDA){
            if( (juego->obstaculos[i].posicion.fil == juego->personaje.posicion.fil) && (juego->obstaculos[i].posicion.col < juego->personaje.posicion.col) ){
                juego->obstaculos[i].visible = true;
            }
            else{
                juego->obstaculos[i].visible = false;
            }
        }
        else if(juego->personaje.ultimo_movimiento == ABAJO){
            if( (juego->obstaculos[i].posicion.col == juego->personaje.posicion.col) && (juego->obstaculos[i].posicion.fil > juego->personaje.posicion.fil) ){
                juego->obstaculos[i].visible = true;
            }
            else{
                juego->obstaculos[i].visible = false;
            }
        }
        else{
            if( (juego->obstaculos[i].posicion.col == juego->personaje.posicion.col) && (juego->obstaculos[i].posicion.fil < juego->personaje.posicion.fil) ){
                juego->obstaculos[i].visible = true;
            }
            else{
                juego->obstaculos[i].visible = false;
            }
        }
    }
}

//PRE: Recibe un juego en estado JUGANDO.
//POST: Actualiza herramienta[i].visible como TRUE, a cada herramienta[i] que este en la misma fila o columna que el personaje.
//      Y en la misma direccion que el ultimo_movimiento.
void esta_herramienta_en_rango_linterna(juego_t* juego){
    int i = 0;

    while( i < (juego->cantidad_herramientas)){
        if(juego->personaje.ultimo_movimiento == DERECHA){
            if( (juego->herramientas[i].posicion.fil == juego->personaje.posicion.fil) && (juego->herramientas[i].posicion.col > juego->personaje.posicion.col) ){
                juego->herramientas[i].visible = true;
            }
            else{
                juego->herramientas[i].visible = false;
            }
        }
        else if(juego->personaje.ultimo_movimiento == IZQUIERDA){
            if( (juego->herramientas[i].posicion.fil == juego->personaje.posicion.fil) && (juego->herramientas[i].posicion.col < juego->personaje.posicion.col) ){
                juego->herramientas[i].visible = true;
            }
            else{
                juego->herramientas[i].visible = false;
            }
        }
        else if(juego->personaje.ultimo_movimiento == ABAJO){
            if( (juego->herramientas[i].posicion.col == juego->personaje.posicion.col) && (juego->herramientas[i].posicion.fil > juego->personaje.posicion.fil) ){
                juego->herramientas[i].visible = true;
            }
            else{
                juego->herramientas[i].visible = false;
            }
        }
        else{
            if( (juego->herramientas[i].posicion.col == juego->personaje.posicion.col) && (juego->herramientas[i].posicion.fil < juego->personaje.posicion.fil) ){
                juego->herramientas[i].visible = true;
            }
            else{
                juego->herramientas[i].visible = false;
            }
        }

        i++;
    }
}

//PRE: Recibe un juego en estado JUGANDO.
//POST: Actualiza todas la herramientas, obstaculos y a amiga_chloe como NO visibles.
void invisibilizar_elementos(juego_t* juego){
    
    juego->chloe_visible = false;
   
    for(int i = 0; i < (juego->cantidad_obstaculos); i++){
        juego->obstaculos[i].visible = false;
    }

    for(int i = 0; i < (juego->cantidad_herramientas); i++){
        juego->herramientas[i].visible = false;
    }
}


//PRE: Recibe una jugada y un personaje_t con sus campos validos.
//POST: Si la jugada es VELA(V) busca una en mochila y guarda su posicion en posicion_vela.
//      Si la jugada es BENGALA(E) busca una en mochila y guarda su posicion en posicion_bengala.
void buscar_elemento_mochila(personaje_t* personaje, char jugada, int* posicion_vela, int* posicion_bengala){
    int i = 0; 
    bool es_posicion_elemento = false;

    while( (i < (personaje->cantidad_elementos) && (!es_posicion_elemento) ) ){
            
        if( (personaje->mochila[i].tipo == VELA) && (jugada == VELA) ){
            (*posicion_vela) = i;
            es_posicion_elemento = true;
        }
        else if( (jugada == BENGALA) && (personaje->mochila[i].tipo == BENGALA) ){
            (*posicion_bengala) = i;
            es_posicion_elemento = true;
        }
        i++;
    }
}


//PRE: Recibe un personaje_t con sus campos validos y con POSICION_LINTERNA como elemento_en_uso.
//POST: Resta movimientos_restantes a linterna en cada turno, y actualiza a NADA_EN_USO elemento_en_uso cuando ya no queden movimientos_restantes.
void restar_movimientos_linterna(personaje_t* personaje, char jugada){
    if( (personaje->elemento_en_uso == POSICION_LINTERNA) ){
        if(personaje->mochila[POSICION_LINTERNA].movimientos_restantes >= MINIMO_MOVIMIENTO_RESTANTE){
            (personaje->mochila[POSICION_LINTERNA].movimientos_restantes)--;
        }
        else{
            personaje->elemento_en_uso = NADA_EN_USO;
        }
    }
}

//PRE: Recibe una jugada valida y un juego en estado JUGANDO.
//POST: Si la jugada es LINTERNA(L) o VELA(V) y esta tiene movimientos_restantes y no esta en uso, se actualiza elemento_en_uso a la posicion del elemento en mochila[].
//      Si el elemento ya esta en uso, se actualiza elemento_en_uso a NADA_EN_USO. 
//      Si la jugada es BENGALA(E) y tiene movimientos_restantes, se actualiza elemento_en_uso a posicion_bengala.
void es_elemento_en_uso(juego_t* juego, char jugada, int posicion_vela, int posicion_bengala){

    if(jugada == LINTERNA){
        if( (juego->personaje.elemento_en_uso == NADA_EN_USO) || (juego->personaje.mochila[juego->personaje.elemento_en_uso].tipo == VELA) ){
            if(juego->personaje.mochila[POSICION_LINTERNA].movimientos_restantes >= MINIMO_MOVIMIENTO_RESTANTE){
                juego->personaje.elemento_en_uso = POSICION_LINTERNA;
            }
        }
        else if(juego->personaje.elemento_en_uso == POSICION_LINTERNA){
            juego->personaje.elemento_en_uso = NADA_EN_USO;
        }
    }
    else if(jugada == VELA){
        if(posicion_vela != POSICION_INEXISTENTE){
            if( (juego->personaje.elemento_en_uso == NADA_EN_USO) || (juego->personaje.elemento_en_uso == POSICION_LINTERNA) ){
                if(juego->personaje.mochila[posicion_vela].movimientos_restantes >= MINIMO_MOVIMIENTO_RESTANTE){
                    invisibilizar_elementos(juego);
                    juego->personaje.elemento_en_uso = posicion_vela;
                }
            }
            else if( (juego->personaje.elemento_en_uso == posicion_vela) && (juego->personaje.mochila[posicion_vela].movimientos_restantes >= MINIMO_MOVIMIENTO_RESTANTE) ){
                juego->personaje.elemento_en_uso = NADA_EN_USO;
            }
        }
        else if(posicion_vela == POSICION_INEXISTENTE){
            if(juego->personaje.elemento_en_uso == POSICION_LINTERNA){
                invisibilizar_elementos(juego);
                juego->personaje.elemento_en_uso = NADA_EN_USO;
            }
        }
    }
    else if(jugada == BENGALA){
        if(posicion_bengala != POSICION_INEXISTENTE){
            if( (juego->personaje.elemento_en_uso != posicion_bengala) && (juego->personaje.mochila[posicion_bengala].movimientos_restantes > MINIMO_MOVIMIENTO_RESTANTE) ){
                invisibilizar_elementos(juego);
                juego->personaje.elemento_en_uso = posicion_bengala;
            }
        }
    }
}

//PRE: Recibe una jugada valida y un juego en estado JUGANDO.
//POST: Si la jugada ingresada es D, W, S o A y LINTERNA esta en uso, si el ultimo_movimiento es diferente de la jugada ingresada,
//      todos los elementos que eran visibles, se invisibilizaran.
void borrar_elementos_iluminados_linterna(juego_t* juego, char jugada){
    if( (jugada == DERECHA) || (jugada == IZQUIERDA) || (jugada == ABAJO) || (jugada == ARRIBA) ){    
        if( (juego->personaje.elemento_en_uso == POSICION_LINTERNA) && (juego->personaje.ultimo_movimiento != jugada) ){
            invisibilizar_elementos(juego);
        }
    }
}
     
//PRE: Recibe un personaje_t con sus campos validos y su elemento_en_uso es de tipo VELA o BENGALA. 
//POST: Si elemento_en_uso es de tipo VELA o BENGALA y a este no le quedan movimientos_restantes, elimina el tipo de elemento de mochila[], 
// reduce cantidad_obstaculos en 1 y actualiza elemento_en_uso a NADA_EN_USO.
void eliminar_vela_bengala_gastadas(personaje_t* personaje){
    if( (personaje->mochila[personaje->elemento_en_uso].tipo == BENGALA) && (personaje->mochila[personaje->elemento_en_uso].movimientos_restantes < MINIMO_MOVIMIENTO_RESTANTE) ){
        personaje->mochila[personaje->elemento_en_uso] = personaje->mochila[personaje->cantidad_elementos-1];
        (personaje->cantidad_elementos)--;
        personaje->elemento_en_uso = NADA_EN_USO;
    }
    else if( (personaje->mochila[personaje->elemento_en_uso].tipo == VELA) && (personaje->mochila[personaje->elemento_en_uso].movimientos_restantes < MINIMO_MOVIMIENTO_RESTANTE) ){
        personaje->mochila[personaje->elemento_en_uso] = personaje->mochila[personaje->cantidad_elementos-1];
        (personaje->cantidad_elementos)--;
        personaje->elemento_en_uso = NADA_EN_USO;
    }
}


//PRE: Recibe un juego en estado JUGANDO.
//POST: Actualiza como visible a todo obstaculo, herramienta y Chloe que esten a una distancia de una posicion del personaje.
void esta_en_rango_vela(juego_t* juego){
    int fila_anterior_oso = juego->personaje.posicion.fil - 1;
    int fila_posterior_oso = juego->personaje.posicion.fil + 1;
    int columna_anterior_oso = juego->personaje.posicion.col - 1;
    int columna_posterior_oso = juego->personaje.posicion.col + 1;

    if(fila_anterior_oso == juego->amiga_chloe.fil){
        if( (columna_anterior_oso == juego->amiga_chloe.col) || (juego->personaje.posicion.col == juego->amiga_chloe.col) 
        || (columna_posterior_oso == juego->amiga_chloe.col) ){
            juego->chloe_visible = true;
        }
    }
    else if(juego->personaje.posicion.fil == juego->amiga_chloe.fil){
        if( (columna_anterior_oso == juego->amiga_chloe.col) || (columna_posterior_oso == juego->amiga_chloe.col) ){
            juego->chloe_visible = true;
        }
    }
    else if(fila_posterior_oso == juego->amiga_chloe.fil){
        if( (columna_anterior_oso == juego->amiga_chloe.col) || (juego->personaje.posicion.col == juego->amiga_chloe.col) 
        || (columna_posterior_oso == juego->amiga_chloe.col) ){
            juego->chloe_visible = true;
        }
    }



    for(int i = 0; i < (juego->cantidad_obstaculos); i++){
        if(fila_anterior_oso == juego->obstaculos[i].posicion.fil){
            if( (columna_anterior_oso == juego->obstaculos[i].posicion.col) || (juego->personaje.posicion.col == juego->obstaculos[i].posicion.col) 
            || (columna_posterior_oso == juego->obstaculos[i].posicion.col) ){
                juego->obstaculos[i].visible = true;
            }
        }
        else if(juego->personaje.posicion.fil == juego->obstaculos[i].posicion.fil){
            if( (columna_anterior_oso == juego->obstaculos[i].posicion.col) || (columna_posterior_oso == juego->obstaculos[i].posicion.col) ){
                juego->obstaculos[i].visible = true;
            }
        }
        else if(fila_posterior_oso == juego->obstaculos[i].posicion.fil){
            if( (columna_anterior_oso == juego->obstaculos[i].posicion.col) || (juego->personaje.posicion.col == juego->obstaculos[i].posicion.col) 
            || (columna_posterior_oso == juego->obstaculos[i].posicion.col) ){
                juego->obstaculos[i].visible = true;
            }
        }
    }

    for(int i = 0; i < (juego->cantidad_herramientas); i++){
        if(fila_anterior_oso == juego->herramientas[i].posicion.fil){
            if( (columna_anterior_oso == juego->herramientas[i].posicion.col) || (juego->personaje.posicion.col == juego->herramientas[i].posicion.col) 
            || (columna_posterior_oso == juego->herramientas[i].posicion.col) ){
                juego->herramientas[i].visible = true;
            }
        }
        else if(juego->personaje.posicion.fil == juego->herramientas[i].posicion.fil){
            if( (columna_anterior_oso == juego->herramientas[i].posicion.col) || (columna_posterior_oso == juego->herramientas[i].posicion.col) ){
                juego->herramientas[i].visible = true;
            }
        }
        else if(fila_posterior_oso == juego->herramientas[i].posicion.fil){
            if( (columna_anterior_oso == juego->herramientas[i].posicion.col) || (juego->personaje.posicion.col == juego->herramientas[i].posicion.col) 
            || (columna_posterior_oso == juego->herramientas[i].posicion.col) ){
                juego->herramientas[i].visible = true;
            }
        }
    }
}

//PRE: Recibe una jugada valida y un personaje_t con sus campos validos.
//POST: Devuelve FALSE, si jugada es LINTERNA(L) y esta no tiene movimientos_restantes. O si la jugada es BENGALA(E) y no hay ninguna en mochila[].
//     Caso contrario devuelve TRUE;
bool tiene_movimientos_linterna_bengala(personaje_t personaje, char jugada, int posicion_bengala){
    bool tiene_movimientos = true;
    
    if(jugada == LINTERNA){
        if(personaje.mochila[POSICION_LINTERNA].movimientos_restantes < MINIMO_MOVIMIENTO_RESTANTE){
            tiene_movimientos = false;
        }
    }
    else if(jugada == BENGALA){
        if(posicion_bengala == POSICION_INEXISTENTE){
            tiene_movimientos = false;
        }
    }
    return tiene_movimientos;
}

//PRE: Recibe un personaje_t con sus campos validos y su elemento_en_uso es de tipo VELA, y recibe una jugada valida.
//POST: Le resta un movimiento_restante a la VELA en uso, por cada movimiento hecho. Si no quedan movimientos_restantes se elimina la VELA consumida
//     del vector mochila[] y se resta 1 al tope. Se actualiza elemento_en_uso como NADA_EN_USO.
void restar_movimientos_vela(personaje_t* personaje, char jugada, int posicion_bengala){
    
    if( (personaje->mochila[personaje->elemento_en_uso].tipo == VELA) && tiene_movimientos_linterna_bengala((*personaje), jugada, posicion_bengala) ){
        if(personaje->mochila[personaje->elemento_en_uso].movimientos_restantes >= MINIMO_MOVIMIENTO_RESTANTE){
            (personaje->mochila[personaje->elemento_en_uso].movimientos_restantes)--;
            
        }
        else{
            eliminar_vela_bengala_gastadas(personaje);
        }
    }
}

//PRE: Recibe una jugada valida y un juego en estado JUGANDO.
//POST: Actualiza como NO visible a todo obstaculo, herramienta y amiga_chloe que esten a una distancia de MAS de una posicion respecto del personaje.
void borrar_elementos_iluminados_vela(juego_t* juego, char jugada){
    int col_anterior_oso = juego->personaje.posicion.col - 1;
    int col_posterior_oso = juego->personaje.posicion.col + 1;
    int fil_anterior_oso = juego->personaje.posicion.fil - 1;
    int fil_posterior_oso = juego->personaje.posicion.fil + 1;
    

    if( (jugada == DERECHA) && (juego->amiga_chloe.col == col_anterior_oso) ){
        juego->chloe_visible = false;
    }
    else if( (jugada == IZQUIERDA) && (juego->amiga_chloe.col == col_posterior_oso) ){
        juego->chloe_visible = false;
    }
    else if( (jugada == ABAJO) && (juego->amiga_chloe.fil == fil_anterior_oso) ){
        juego->chloe_visible = false;
    }
    else if( (jugada == ARRIBA) && (juego->amiga_chloe.fil == fil_posterior_oso) ){
        juego->chloe_visible = false;
    }


    for(int i = 0; i < (juego->cantidad_obstaculos); i++){
        if( (jugada == DERECHA) && (juego->obstaculos[i].posicion.col == col_anterior_oso) ){
            juego->obstaculos[i].visible = false;
        }
        else if( (jugada == IZQUIERDA) && (juego->obstaculos[i].posicion.col == col_posterior_oso) ){
            juego->obstaculos[i].visible = false;
        }
        else if( (jugada == ABAJO) && (juego->obstaculos[i].posicion.fil == fil_anterior_oso) ){
            juego->obstaculos[i].visible = false;
        }
        else if( (jugada == ARRIBA) && (juego->obstaculos[i].posicion.fil == fil_posterior_oso) ){
            juego->obstaculos[i].visible = false;
        }
    }


    for(int i = 0; i < (juego->cantidad_herramientas); i++){
        if( (jugada == DERECHA) && (juego->herramientas[i].posicion.col == col_anterior_oso) ){
            juego->herramientas[i].visible = false;
        }
        else if( (jugada == IZQUIERDA) && (juego->herramientas[i].posicion.col == col_posterior_oso) ){
            juego->herramientas[i].visible = false;
        }
        else if( (jugada == ABAJO) && (juego->herramientas[i].posicion.fil == fil_anterior_oso) ){
            juego->herramientas[i].visible = false;
        }
        else if( (jugada == ARRIBA) && (juego->herramientas[i].posicion.fil == fil_posterior_oso) ){
            juego->herramientas[i].visible = false;
        }
    }

    
}

//PRE: Recibe un juego en estado JUGANDO.
//POST:Actualiza como visible a todo obstaculo, herramienta y amiga_chloe que esten a una distancia de valor absoluto 3 de una posicion generada aleatoriamente.
void esta_en_rango_bengala(juego_t* juego){
    int fil_bengala = rand() % NUMERO_FILAS;
    int col_bengala = rand() % NUMERO_COLUMNAS;


    int distancia_manhattan_chloe_fil = abs(fil_bengala - (juego->amiga_chloe.fil) );
    int distancia_manhattan_chloe_col = abs(col_bengala - (juego->amiga_chloe.col) );

    if( (distancia_manhattan_chloe_col == DISTANCIA_CERO) && (distancia_manhattan_chloe_fil <= DISTANCIA_DE_TRES) ){
        juego->chloe_visible = true;
    }
    else if( (distancia_manhattan_chloe_col == DISTANCIA_DE_UNO) && (distancia_manhattan_chloe_fil <= DISTANCIA_DE_DOS) ){
        juego->chloe_visible = true;
    }     
    else if( (distancia_manhattan_chloe_col == DISTANCIA_DE_DOS) && (distancia_manhattan_chloe_fil <= DISTANCIA_DE_UNO) ){
        juego->chloe_visible = true;
    }
    else if( (distancia_manhattan_chloe_col == DISTANCIA_DE_TRES) && (distancia_manhattan_chloe_fil == DISTANCIA_CERO) ){
        juego->chloe_visible = true;
    }

    for(int i = 0; i < (juego->cantidad_obstaculos); i++){
        int distancia_manhattan_obstaculo_fil = abs(fil_bengala - (juego->obstaculos[i].posicion.fil) );
        int distancia_manhattan_obstaculo_col = abs(col_bengala - (juego->obstaculos[i].posicion.col) );

        if( (distancia_manhattan_obstaculo_col == DISTANCIA_CERO) && (distancia_manhattan_obstaculo_fil <= DISTANCIA_DE_TRES) ){
            juego->obstaculos[i].visible = true;
        }
        else if( (distancia_manhattan_obstaculo_col == DISTANCIA_DE_UNO) && (distancia_manhattan_obstaculo_fil <= DISTANCIA_DE_DOS) ){
            juego->obstaculos[i].visible = true;
        }     
        else if( (distancia_manhattan_obstaculo_col == DISTANCIA_DE_DOS) && (distancia_manhattan_obstaculo_fil <= DISTANCIA_DE_UNO) ){
            juego->obstaculos[i].visible = true;
        }
        else if( (distancia_manhattan_obstaculo_col == DISTANCIA_DE_TRES) && (distancia_manhattan_obstaculo_fil == DISTANCIA_CERO) ){
            juego->obstaculos[i].visible = true;
        }
    }

    for(int i = 0; i < (juego->cantidad_herramientas); i++){
        int distancia_manhattan_herramienta_fil = abs(fil_bengala - (juego->herramientas[i].posicion.fil) );
        int distancia_manhattan_herramienta_col = abs(col_bengala - (juego->herramientas[i].posicion.col) );

        if( (distancia_manhattan_herramienta_col == DISTANCIA_CERO) && (distancia_manhattan_herramienta_fil <= DISTANCIA_DE_TRES) ){
            juego->herramientas[i].visible = true;
        }
        else if( (distancia_manhattan_herramienta_col == DISTANCIA_DE_UNO) && (distancia_manhattan_herramienta_fil <= DISTANCIA_DE_DOS) ){
            juego->herramientas[i].visible = true;
        }     
        else if( (distancia_manhattan_herramienta_col == DISTANCIA_DE_DOS) && (distancia_manhattan_herramienta_fil <= DISTANCIA_DE_UNO) ){
            juego->herramientas[i].visible = true;
        }
        else if( (distancia_manhattan_herramienta_col == DISTANCIA_DE_TRES) && (distancia_manhattan_herramienta_fil == DISTANCIA_CERO) ){
            juego->herramientas[i].visible = true;
        }
    }
}

//PRE: Recibe un personaje_t con sus campos validos y su elemento_en_uso es de tipo BENGALA, y recibe una jugada valida.
//POST: Le resta un movimiento_restante a la BENGALA en uso, por cada jugada ingresada. Si no quedan movimientos_restantes 
//    se elimina la BENGALA consumida del vector mochila[] y se resta 1 a cantidad.elementos. Se actualiza elemento_en_uso como NADA_EN_USO.
void restar_movimientos_bengala(personaje_t* personaje, char jugada){
    if(personaje->mochila[personaje->elemento_en_uso].tipo == BENGALA){
        if(personaje->mochila[personaje->elemento_en_uso].movimientos_restantes >= MINIMO_MOVIMIENTO_RESTANTE){
            (personaje->mochila[personaje->elemento_en_uso].movimientos_restantes)--;
        }
        else{
            eliminar_vela_bengala_gastadas(personaje);
        }
    }
}

//PRE: Recibe una jugada valida y un juego en estado JUGANDO.
//POST: Si elemento_en_uso es de tipo BENGALA y se ingresa una jugada valida, se actualizaran todos los elementos_del_mapa y amiga_chloe a NO visibles.
void borrar_elementos_iluminados_bengala(juego_t* juego, char jugada){
    if(juego->personaje.mochila[juego->personaje.elemento_en_uso].tipo == BENGALA){
        invisibilizar_elementos(juego);
    }
}

//PRE: Recibe una jugada y un juego en estado JUGANDO.
//POST: Si elemento_en_uso es de tipo LINTERNA, VELA o BENGALA, se actualizara a visible todo elemento o Chloe que este en su respectivo rango.
//     Si elemento_en_uso es NADA_EN_USO, se actualizara todo elemento y Chloe a NO visible. 
void iluminar(juego_t* juego, char jugada){
    if( (juego->personaje.elemento_en_uso == POSICION_LINTERNA) ){
        esta_chloe_en_rango_linterna(juego);
        esta_obstaculo_en_rango_linterna(juego);
        esta_herramienta_en_rango_linterna(juego);
    }
    else if( (juego->personaje.mochila[juego->personaje.elemento_en_uso].tipo == VELA) ){
        esta_en_rango_vela(juego);
    }
    else if(juego->personaje.mochila[juego->personaje.elemento_en_uso].tipo == BENGALA){
        esta_en_rango_bengala(juego); 
    }
    else if(juego->personaje.elemento_en_uso == NADA_EN_USO){
        invisibilizar_elementos(juego);
    }
}

//PRE: Recibe un tiempo_actual().
//POST: Imprime por pantalla el resultado de TIEMPO_RESTANTE_INICIO - tiempo_actual().
void imprimir_tiempo_restante(){
    double tiempo_transcurrido = tiempo_actual();
    if(tiempo_transcurrido < MUCHO_TIEMPO_TRANSCURRIDO){
        printf("\n TIEMPO RESTANTE PARA EL TOQUE DE QUEDA:\n");
        printf("\n %f segundos \n", (TIEMPO_RESTANTE_INICIO - tiempo_transcurrido) );
    }
    else if( (tiempo_transcurrido >= MUCHO_TIEMPO_TRANSCURRIDO) && (tiempo_transcurrido < TIEMPO_RESTANTE_INICIO) ){
        printf("\n CORRE WACHIN, TIEMPO RESTANTE PARA EL TOQUE DE QUEDA:\n");
        printf("\n %f segundos \n", (TIEMPO_RESTANTE_INICIO - tiempo_transcurrido) );
    }
    else{
        printf("\n FUISTES, EL TOQUE DE QUEDA EMPEZO HACE: \n");
        printf("\n %f segundos \n", (tiempo_transcurrido - TIEMPO_RESTANTE_INICIO) );
    }
}



//PRE: Recibe una jugada valida y un personaje con todos sus campos validos.
//POST: Mueve el personaje una posicion en direccion a la jugada ingresada si jugada es A,D,S o W.
//      Y si la jugada es T, imprime el tiempo_restante por pantalla.
void mover_personaje(personaje_t* personaje, char jugada, int fil_aleatoria, int col_aleatoria){
    
    if(!esta_personaje_en_borde((*personaje), jugada) ){
        if(jugada == ARRIBA){
            if(personaje->posicion.fil != 0){
                personaje->posicion.fil -= 1;
                personaje->ultimo_movimiento = ARRIBA;
            }
        }
        else if(jugada == IZQUIERDA){
            if(personaje->posicion.col != 0){
                personaje->posicion.col -= 1;
                personaje->ultimo_movimiento = IZQUIERDA;
            }
        }
        else if(jugada == ABAJO){
            if(personaje->posicion.fil != NUMERO_FILAS){
                personaje->posicion.fil += 1;
                personaje->ultimo_movimiento = ABAJO;
            }
        }
        else if(jugada == DERECHA){
            if(personaje->posicion.col != NUMERO_COLUMNAS){
                personaje->posicion.col += 1;
                personaje->ultimo_movimiento = DERECHA;
            }
        }
        else if(jugada == TIEMPO_RESTANTE){
            imprimir_tiempo_restante();
        }
    }
}



/*
 * Mueve el personaje en la dirección indicada por el usuario o habilita 
 * cualquiera de las herramientas y actualiza el juego según los elementos 
 * que haya en el camino del personaje.
 * El juego quedará en un estado válido al terminar el movimiento. 
 * El movimiento será:
 * -> W: Si el personaje debe moverse para la arriba. 
 * -> A: Si el personaje debe moverse para la izquierda.
 * -> S: Si el personaje debe moverse para la abajo.
 * -> D: Si el personaje debe moverse para la derecha.
 * -> L: Si el personaje quiere encender una linterna.
 * -> V: Si el personaje quiere encender una vela. 
 * -> E: Si el personaje quiere encender la bengala.
 * -> T: Si el personaje quiere ver el tiempo restante.
 * En caso de que querer activar una herramienta, y no tenga mas movimientos, no deberá 
 * activarse ninguna ventaja. 
 * Si se aprieta una tecla de iluminación y esta ya está siendo usada, se desactivará colocando
 * el int elemento_en_uso en -1.
 */
void realizar_jugada(juego_t* juego, char jugada){
    int posicion_obstaculo = 0;
    int posicion_herramienta = 0;
    int fil_aleatoria = 0;
    int col_aleatoria = 0;
    int posicion_vela = POSICION_INEXISTENTE;
    int posicion_bengala = POSICION_INEXISTENTE;

    es_jugada_valida(jugada);

    buscar_elemento_mochila(&(juego->personaje), jugada, &posicion_vela, &posicion_bengala);

    es_elemento_en_uso(juego, jugada, posicion_vela, posicion_bengala);

    generar_koala(juego, jugada, fil_aleatoria, col_aleatoria);
    
    restar_movimientos_linterna(&(juego->personaje), jugada);
    restar_movimientos_vela(&(juego->personaje), jugada, posicion_bengala);
    restar_movimientos_bengala(&(juego->personaje), jugada);

    borrar_elementos_iluminados_linterna(juego, jugada); 
    borrar_elementos_iluminados_vela(juego, jugada);
    borrar_elementos_iluminados_bengala(juego, jugada);
    
    system("clear");

    mover_personaje(&(juego->personaje), jugada, fil_aleatoria, col_aleatoria);
    
    iluminar(juego, jugada);

    es_posicion_obstaculo((*juego), &posicion_obstaculo);
    chocar_koala(juego, fil_aleatoria, col_aleatoria);
    chocar_obstaculo(juego, posicion_obstaculo, jugada);
    es_posicion_herramienta((*juego), &posicion_herramienta);
    guardar_herramienta_mochila(juego, posicion_herramienta);
    recoger_herramienta(juego, posicion_herramienta);

    ve_panda_a_chloe(juego);
}



//PRE: Recibe un bosque sin inicializar.
//POST: Inicializa todo el bosque con VACIO.
void inicializar_bosque(char bosque[NUMERO_FILAS][NUMERO_COLUMNAS]){
    for(int i = 0; i < NUMERO_FILAS; i++){
        for(int j = 0; j < NUMERO_COLUMNAS; j++){
            bosque[i][j] = VACIO;
        }
    }
}

//PRE: Recibe un bosque y un juego en estado JUGANDO.
//POST: Carga en el bosque al personaje segun su posicion.
void cargar_oso_chloe_bosque(char bosque[NUMERO_FILAS][NUMERO_COLUMNAS], juego_t juego){
    for(int i = 0; i < NUMERO_FILAS; i++){
        for(int j = 0; j < NUMERO_COLUMNAS; j++){
            bosque[juego.personaje.posicion.fil][juego.personaje.posicion.col] = juego.personaje.tipo;

            if(juego.chloe_visible){
                bosque[juego.amiga_chloe.fil][juego.amiga_chloe.col] = CHLOE;
            }
        }
    }
}

//PRE: Recibe un bosque y un juego en estado JUGANDO.
//POST: Carga en el bosque a todo obstaculo que sea visible, segun su posicion.
void cargar_obstaculos_bosque(char bosque[NUMERO_FILAS][NUMERO_COLUMNAS], juego_t juego){
    for(int i = 0; i < NUMERO_FILAS; i++){
        for(int j = 0; j < NUMERO_COLUMNAS; j++){
            for(int k = 0; k < (juego.cantidad_obstaculos); k++){
                if( (i == juego.obstaculos[k].posicion.fil) && (j == juego.obstaculos[k].posicion.col) ){
                    if( (juego.obstaculos[k].visible == true) ){
                        bosque[i][j] = juego.obstaculos[k].tipo;
                    }
                }
            }
        }
    }
}

//PRE: Recibe un bosque y un juego en estado jugando.
//POST: Carga en el bosque a toda herramienta que sea visible, segun su posicion.
void cargar_herramientas_bosque(char bosque[NUMERO_FILAS][NUMERO_COLUMNAS], juego_t juego){
    for(int i = 0; i < NUMERO_FILAS; i++){
        for(int j = 0; j < NUMERO_COLUMNAS; j++){
            for(int k = 0; k < (juego.cantidad_herramientas); k++){
                if( (i == juego.herramientas[k].posicion.fil) && (j == juego.herramientas[k].posicion.col) && (juego.herramientas[k].visible) ){
                    bosque[i][j] = juego.herramientas[k].tipo;
                }
            }
        }
    }
}

//PRE: Recibe un bosque con todos sus elementos cargados.
//POST: Imprime el bosque por pantalla.
void imprimir_bosque(char bosque[NUMERO_FILAS][NUMERO_COLUMNAS]){
    for(int i = 0; i < NUMERO_FILAS; i++){
        for(int j = 0; j < NUMERO_COLUMNAS; j++){
            printf("  %c  ", bosque[i][j]);
        }
        printf("\n");
    }
}

//PRE: Recibe personaje_t con todos sus campos validos y un tiempo_actual().
//POST: Imprime por pantalla el tipo de personaje cuando tiempo_actual() sea cero (antes de ingresar la primer jugada).
void informar_tipo_personaje(personaje_t personaje){
    if(tiempo_actual() == SEGUNDO_CERO){
    
        if(personaje.tipo == POLAR){
            printf("\nSos POLAR(I), tenes la habilidad de saltar las piedras\n");
        }
        else if(personaje.tipo == PANDA){
            printf("\nSos PANDA(P), tenes la habilidad de ubicar a Chloe por GPS una vez hayas perdido 30 segundos\n");
        }
        else if(personaje.tipo == PARDO){
            printf("\nSos PARDO(G), por tu habilidad como guardaparques evadis mas rapido a los arboles\n");
        }
        printf("\n");
        printf("\n");
    }
}


//PRE: Recibe un personaje con todos sus campos validos.
//POST: Imprime la mochila por pantalla.
void imprimir_mochila(personaje_t personaje){
    printf("\nHerramientas en mochila: ");
    
    for(int i = 0; i < (personaje.cantidad_elementos); i++){
        printf("  %c  ", personaje.mochila[i].tipo);
    }
    printf("\n");
}

//PRE: Recibe un personaje con todos sus campos validos.
//POST: Imprime cuantos movimientos le restan a cada elemento de la mochila.
void restan_movimientos(personaje_t personaje){
    int numero_vela = 0;
    int numero_bengala = 0;
    
    printf("\nMOVIMIENTOS RESTANTES:\n");
    printf("\nLINTERNA: %i ", personaje.mochila[POSICION_LINTERNA].movimientos_restantes);
    
    for(int i = 0; i < (personaje.cantidad_elementos); i++){
        if(personaje.mochila[i].tipo == VELA){
            numero_vela++;
            printf("  VELA %i:  %i ", numero_vela, personaje.mochila[i].movimientos_restantes);
        }
        else if(personaje.mochila[i].tipo == BENGALA){
            numero_bengala++;
            printf("  BENGALA %i:  %i ", numero_bengala, personaje.mochila[i].movimientos_restantes);
        }
    }
    printf("\n");
    printf("\n");
}

/*
 * Mostrará el juego por pantalla.
 */
void mostrar_juego(juego_t juego){
    char bosque[NUMERO_FILAS][NUMERO_COLUMNAS];
    
    inicializar_bosque(bosque);
    cargar_herramientas_bosque(bosque, juego);
    cargar_obstaculos_bosque(bosque, juego);
    cargar_oso_chloe_bosque(bosque, juego);

    informar_tipo_personaje(juego.personaje);
    imprimir_bosque(bosque);
    imprimir_mochila(juego.personaje);
    restan_movimientos(juego.personaje);
}
