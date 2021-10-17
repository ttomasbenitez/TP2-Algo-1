#include <stdio.h>
#include <stdbool.h>

const char POLAR = 'I';
const char PANDA = 'P';
const char PARDO = 'G';

const char ANIME = 'A';
const char MUSICA_POP = 'M';
const char LIMPIEZA = 'L';

const char BAMBU = 'B';
const char PESCADO = 'P';
const char FOCAS = 'F';

const int PISO_MINIMO = 1;
const int PISO_MAXIMO = 18;

const int POTENCIA_GRITO_MINIMA = 1;
const int POTENCIA_GRITO_MAXIMA = 18;

const int MULTIPLICADOR_LIMPIEZA = 1;
const int MULTIPLICADOR_ANIME = 2;
const int MULTIPLICADOR_MUSICA_POP = 3;

const int PUNTOS_FOCAS = 3;
const int PUNTOS_BAMBU = 6;
const int PUNTOS_PESCADO = 9;

const int MINIMO_RANGO_POLAR = 5;
const int MAXIMO_RANGO_POLAR = 24;
const int MAXIMO_RANGO_PANDA = 43;

void presentar_test(){
    printf("\n¡¡¡¡BIENVENIDO AL TEST (definitivo) PARA DETERMINAR QUE ESCANDALOSO SOS!!!!\n");
    printf("\nResponde las siguientes preguntas para averiguarlo:\n");
}

/*
 * PRE:Recibe un caracter de un canal.
 * POST:Devuelve "true" si es valido el caracter("A", "M" o "L").
 */
bool es_canal_valido(char canal_elegido){
    return ( (canal_elegido == ANIME) || (canal_elegido == MUSICA_POP) || (canal_elegido == LIMPIEZA) );
}

/*
 * PRE:Recibe un caracter de un alimento.
 * POST:Devuelve "true" si es valido el caracter("B", "P" o "F").
 */
bool es_alimento_valido(char alimento_elegido){
    return( (alimento_elegido == BAMBU) || (alimento_elegido == PESCADO) || (alimento_elegido == FOCAS) );
}

/*
 * PRE:Recibe un numero de piso.
 * POST:Devuelve "true" si es valido el numero (entre 1 y 18, ambos inclusive).
 */
bool es_piso_valido(int piso_elegido){
    return ( (piso_elegido >= PISO_MINIMO) && (piso_elegido <= PISO_MAXIMO) );
}

/*
 * PRE:Recibe un numero de potencia de grito.
 * POST:Devuelve "true" si es valido el numero (entre 1 y 18, ambos inclusive).
 */
bool es_potencia_grito_valida(int potencia_grito){
    return ((potencia_grito >= POTENCIA_GRITO_MINIMA) && (potencia_grito <= POTENCIA_GRITO_MAXIMA));
}

/*
 *POST: Pregunta hasta que se ingrese un canal de TV valido ("A", "L" o "M").
 */
void elegir_canal_tv(char* canal_elegido){
    
    printf("\nSi vas a ver tele un rato, ¿que canal pones?\n");
    printf("Anime -A-, Musica Pop -M- o Limpieza -L-\n");
    scanf(" %c" , canal_elegido);

    while(!es_canal_valido(*canal_elegido)){
        printf("Ese canal no existe, dame otro porfa.\n");
        printf("Anime -A-, Musica Pop -M- o Limpieza -L-\n ");
        scanf(" %c" , canal_elegido);
    }
}

/*
 *POST: Pregunta hasta que se ingrese un alimento valido("B", "P" o "F").
 */
void elegir_alimento_vianda(char* alimento_elegido){
    printf("\nSi solo pudieras guardar un alimento en tu vianda. ¿Cual elegis?\n");
    printf("Bambu -B-, Pescado -P- o Focas -F-\n");
    scanf(" %c" , alimento_elegido);

    while(!es_alimento_valido(*alimento_elegido)){
        printf("Ese no es un alimento valido. Intenta devuelta:\n");
        printf("Bambu -B-, Pescado -P- o Focas -F-\n");
        scanf(" %c" , alimento_elegido);
    }
}

/*
 *POST: Pregunta hasta que se ingrese un piso de torre valido(numero del 1 al 18, ambos inclusive).
 */
void elegir_piso_torre(int* piso_elegido){
    printf("\nSi te comprases una torre de 18 pisos con tus 2 hermanos. ¿Cual piso elegis para vivir?\n");
    printf("Del 1 al 18, ambos inclusive\n");
    scanf("%i" , piso_elegido);

    while(!es_piso_valido(*piso_elegido)){
        printf("Ese no es un piso valido. Intenta devuelta:\n");
        printf("Pisos del 1 al 18, ambos inclusive\n");
        scanf("%i" , piso_elegido);
    }
}

/*
 *POST: Pregunta hasta que se ingrese una potencia de grito valida(numero del 1 al 18, ambos inclusive).
 */
void elegir_potencia_grito(int* potencia_grito){
    printf("\nSi ves una rata. ¿Que tan fuerte gritas? Siendo -1- no gritar y -18- desgarrarse la garganta.\n");
    scanf("%i" , potencia_grito);

    while(!es_potencia_grito_valida(*potencia_grito)){
        printf("Esa no es una opcion valida. Intenta devuelta:\n");
        printf("¿Que tan fuerte gritas? Siendo -1- no gritar y -18- desgarrarse la garganta.\n");
        scanf("%i" , potencia_grito);
    }
}

/*
 *PRE: Recibe un caracter valido de canal_elegido ("A", "L" o "M").
 *POST: Devuelve un valor de multiplicador dependiendo canal_elegido.
 */
int multiplicador_segun_canal(char* canal_elegido){
   
    int multiplicador_por_canal = 0;

    if((*canal_elegido) == LIMPIEZA){
        multiplicador_por_canal = MULTIPLICADOR_LIMPIEZA; 
    }
    else if((*canal_elegido) == ANIME){
        multiplicador_por_canal = MULTIPLICADOR_ANIME;
    }
    else{
        multiplicador_por_canal = MULTIPLICADOR_MUSICA_POP;
    }
    return multiplicador_por_canal;
}

/*
 *PRE: Recibe un caracter valido de alimento_elegido ("B", "P" o "F").
 *POST: Devuelve un valor de puntaje dependiendo alimento_elegido.
 */
int puntaje_segun_alimento(char* alimento_elegido){
    
    int puntaje_por_alimento = 0;

    if((*alimento_elegido) == FOCAS){
        puntaje_por_alimento = PUNTOS_FOCAS;
    }
    else if((*alimento_elegido) == BAMBU){
        puntaje_por_alimento = PUNTOS_BAMBU;
    }
    else{
        puntaje_por_alimento = PUNTOS_PESCADO;
    }
    return puntaje_por_alimento;
}
/*
 *PRE: Recibe numeros validos de piso_elegido y potencia_grito(del 1 al 18, ambos inclusive).
 *POST: Devuelve los puntos_totales del test.
 */
int puntos_totales(int multiplicador_por_canal, int puntos_por_alimento, int* piso_elegido, int* potencia_grito){
    return ( ((puntos_por_alimento) * (multiplicador_por_canal)) + (*piso_elegido) + (*potencia_grito));
}

/*
 *POST: Determina el personaje correspondiente de acuerdo a puntos_totales.
 */
void determinar_personaje(int puntaje_total, char* personalidad_detectada){
    if((puntaje_total >= MINIMO_RANGO_POLAR) && (puntaje_total <= MAXIMO_RANGO_POLAR)){
        (*personalidad_detectada) = POLAR;
    }
    else if((puntaje_total > MAXIMO_RANGO_POLAR) && (puntaje_total <= MAXIMO_RANGO_PANDA)){
        (*personalidad_detectada) = PANDA;
    }
    else{
        (*personalidad_detectada) = PARDO;
    }
}

//REALIZA el test_de_personalidad y guarda la personalidad_detectada segun el test.
void test_de_personalidad(char* personalidad_detectada){

    char canal_elegido;
    char alimento_elegido;
    int piso_elegido;
    int potencia_grito;
    
    presentar_test();
    
    elegir_canal_tv(&canal_elegido);
    elegir_alimento_vianda(&alimento_elegido);
    elegir_piso_torre(&piso_elegido);
    elegir_potencia_grito(&potencia_grito);

    int multiplicador_por_canal = multiplicador_segun_canal(&canal_elegido);
    int puntos_por_alimento = puntaje_segun_alimento(&alimento_elegido);
    
    int puntaje_total = puntos_totales(multiplicador_por_canal, puntos_por_alimento, &piso_elegido, &potencia_grito);

    determinar_personaje(puntaje_total, personalidad_detectada);
}