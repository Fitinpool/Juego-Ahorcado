/*
    Julio Barra
    Vicente Salas
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "dibujos.h"
//Definimos n con el valor de 20 ya que sera el numero maximo de la mayoria de nuestros arreglos y matrices
#define n 20

char palabra[n][n] = {"arqueozoologia", "correcto", "dialectica", "vomito", "pelota", "hacienda", "corbata", "victoria", "paralelepipedo", "premio",
    "autocorrector", "autonomo", "detenido", "cocina", "mayordomo", "telefono", "cartero", "compositor", "astronauta", "comunismo"};

char letras_del_usuario[n], palabra_temporal_formada[n];
//las letras que usa el usuario se guardan en letras_del_usuario
//las letras que pertenezcan a la palabra que se estan jugando se guardan en palabra_temporal_formada
int palabras_usadas[n];
//palabras_usadas es para guardar la posicion de las palabras usadas
int max_numeros_aleatorios, cuenta_datos_array, errores;
//max_numeros_aleatorios marca el tamaño del arreglo de las palabras que hemos usados

//cuenta los errores del usuario
char letra_ingresada;
//la letra que ingrese el usuario se guarda en esta variable
int i, contador;
// i bandarin que usaremos en todos los for de las funciones

/*
esta funcion es para hacer la imagen inicial cada vez que el juego se reinicia, muestra el tamaño de la palabra y pide una letra
que luego es de vuelta a la funcion main.
*/
char inicio_general(char tamano_palabra_en_juego)
{
    TituloJuego();
    SinAhorcado();

    printf("\nPALABRA SECRETA:");
    for(int i=0; i < tamano_palabra_en_juego; i++)
        printf(" - ");

    printf("\nINGRESE UNA LETRA: ");
    fflush(stdin);
    scanf("%c", &letra_ingresada);
    LimpiaPantalla();
}
/*
esta funcion selecciona al azar una de las 20 palabras que tiene el juego y la almacena en un arreglo para que no se repita ademas de
de volver la posicion de la palabra que se usara en el juego
*/
int selector_palabra()
{
    int numero_aleatorio;

    srand(time(NULL));

    numero_aleatorio = rand()%20;
    //si ya se juegaron las 20 palabras inicia el conteo desde 0
    if(max_numeros_aleatorios == 19 || max_numeros_aleatorios == 0)
    {
        numero_aleatorio = rand()%20;
        palabras_usadas[0] = numero_aleatorio;
        max_numeros_aleatorios = 0;
    }
    //este for es para comprobar que la nueva palabra aleatoria no este repetida
    for(i = 0; i < max_numeros_aleatorios + 1; i++)
    {
        if(numero_aleatorio == palabras_usadas[i])
        {
            numero_aleatorio = rand()%20;
            i = 0;
        }
    }

    max_numeros_aleatorios++;
    //los numeros que son usados se guardan en una lista para que no se vuelvan a usar
    palabras_usadas[max_numeros_aleatorios] = numero_aleatorio;

    return numero_aleatorio;
}
/*
esta funcion muestra por pantalla los errores del jugador
*/
void Errores_jugador()
{
    if(errores == 0)
    {
        TituloJuego();
        SinAhorcado();
    }
    if(errores == 1)
    {
        TituloJuego();
        Cabeza();
    }
    if(errores == 2)
    {
        TituloJuego();
        Tronco();
    }
    if(errores == 3)
    {
        TituloJuego();
        BrazoIzquierdo();
    }
    if(errores == 4)
    {
        TituloJuego();
        BrazoDerecho();
    }
    if(errores == 5)
    {
        TituloJuego();
        PiernaIzquierda();
    }
    if(errores == 6)
    {
        TituloJuego();
        PiernaDerecha();
    }
}
/*
esta funcion analiza si hay una letra con tilde, tanto con mayuscula o minuscula
comparandolo con sus valores en ascii y si la letra lleva tilde la variable letra_ingresada cambia su valor a la misma letra sin tilde
*/
void comprobacion_tildes()
{
    if(letra_ingresada == -96 || letra_ingresada == 65)
        {
            letra_ingresada = 'a';
        }
        if(letra_ingresada == -126 || letra_ingresada == -112)
        {
            letra_ingresada = 'e';
        }
        if(letra_ingresada == -95 || letra_ingresada == 73)
        {
            letra_ingresada = 'i';
        }
        if(letra_ingresada == -94 || letra_ingresada == 79)
        {
            letra_ingresada = 'o';
        }
        if(letra_ingresada == -93 || letra_ingresada == 85)
        {
            letra_ingresada = 'u';
        }
}

int main()
{
    char volver_a_jugar;

    int palabra_en_juego, tamano_palabra_en_juego, tamano_letras_ingresadas, palabra_repetida;

    int contador_para_guardar;
    //contador para guardar sirve para ir guardando las letras que ingresa el usuario dentro del array de letras_del_usuario
    volver_a_jugar = 's';
    //inicialisamos volver a jugar en 's' para que el juego continue hasta que el usuario digite una 'n'
    max_numeros_aleatorios = 0;

    while(volver_a_jugar == 's' || volver_a_jugar == 'S')
    {
        errores = 0; //colocamos errores en 0 para que el juego empiece desde el principio
        palabra_repetida = 0; //si es 1 la palabra esta repetida y si es 0 no esta repetida
        //aqui limpiamos las array de las letras que usa el usuario y la palabra temporal que llevaba
        memset(letras_del_usuario, '\0', 20);
        memset(palabra_temporal_formada, '\0', 20);

        palabra_en_juego = selector_palabra();//elegimos la palabra que usaremos con la funcion selector_palabra

        tamano_palabra_en_juego = strlen(palabra[palabra_en_juego]);//guardamos el tamaño de la palabra que vamos usar para saber los "-" que usaremos

        inicio_general(tamano_palabra_en_juego);// invocamos inicio general para guardar la primera letra ingresada
        //con esto verificamos si la letra que ingreso el usuario es una letra o otro caracter
        if(isdigit(letra_ingresada) != 0 || ( 32 < letra_ingresada && letra_ingresada < 48 ) || ( 90 < letra_ingresada && letra_ingresada < 97 ) || ( 122 < letra_ingresada && letra_ingresada < 129 ) || ( 57 < letra_ingresada && letra_ingresada < 65 ))
            {
                palabra_repetida = 1;
            }

        comprobacion_tildes();

        letras_del_usuario[0] = letra_ingresada; //aqui guardamos la primera letra que ingreso el usuario
        tamano_letras_ingresadas = strlen(letras_del_usuario); //esta variable almacena el tamaño que tiene las letras que guarde el usuario por si vuelve a ingresar la misma letra
        strlwr(letras_del_usuario);//con esto ponermos todas las letras del arreglo en minusculas

        //esto verifica si la palabra que ingresa el usuario esta dentro de la palabra que esta en juego, entra solo si no es una palabra repetida
        if(palabra_repetida == 0)
        {
            contador = 0;
            for(i = 0; i < tamano_palabra_en_juego; i++)
            {
                if(letras_del_usuario[tamano_letras_ingresadas - 1] != palabra[palabra_en_juego][i])
                {
                    contador++;
                    if(contador == tamano_palabra_en_juego)
                    {
                        errores++;
                    }
                }
            }
        }

        contador_para_guardar = 1;//lo ponemos en 1 para que la siguiente letra la guarde en esa posicion

        while(errores != 7)
        {
            //lo primero que hacemos es verificar si la letra ingresada esta en nuestra palabra en juego
            for(i = 0; i < tamano_palabra_en_juego; i++)
            {
                if(letras_del_usuario[tamano_letras_ingresadas - 1] == palabra[palabra_en_juego][i])
                {
                    palabra_temporal_formada[i] = letras_del_usuario[tamano_letras_ingresadas-1];
                }
            }

            Errores_jugador();

            /* PARA VER LA PALABRA CON LA QUE SE ESTA JUGANDO PONER PRINT DEBAJO DE ESTE COMENTARIO
            printf("\n%s", palabra[palabra_en_juego]);
            */
            printf("\nPALABRA SECRETA:");
            //con esto vamos imprimiendo las palabras que lleva el usuario correctas
            for(i = 0; i < tamano_palabra_en_juego; i++)
            {
                if(palabra_temporal_formada[i] == palabra[palabra_en_juego][i])
                    printf(" %c ", palabra_temporal_formada[i]);
                else
                    printf(" - ");
            }
            //le pedimos una letra al usuario
            printf("\nINGRESE UNA LETRA: ");
            fflush(stdin);
            scanf("%c", &letra_ingresada);

            comprobacion_tildes();
            //aqui verificamos si la palabra ingresada esta repetida o no, comparando la letra ya sea mayuscula o minuscula
            palabra_repetida = 0;
            for(i = 0; i < tamano_letras_ingresadas; i++) //revisa si hay una palabra repetida
            {
                if(letra_ingresada == toupper(letras_del_usuario[i]) || letra_ingresada == tolower(letras_del_usuario[i]))
                {
                    palabra_repetida = 1;
                    i = tamano_letras_ingresadas;
                }
            }

            //con esto verificamos si la letra que ingreso el usuario es una letra o otro caracter
            if(isdigit(letra_ingresada) != 0 || ( 32 < letra_ingresada && letra_ingresada < 48 ) || ( 90 < letra_ingresada && letra_ingresada < 97 ) || ( 122 < letra_ingresada && letra_ingresada < 129 ) || ( 57 < letra_ingresada && letra_ingresada < 65 ))
            {
                palabra_repetida = 1;
            }

            if(palabra_repetida == 0)// verificqa errores y guarda letras si no hay palabras repetidas
            {
                letras_del_usuario[contador_para_guardar] = letra_ingresada;//guardamos la letra del usuario en su array si no esta repetida
                contador_para_guardar++;

                tamano_letras_ingresadas = strlen(letras_del_usuario);

                strlwr(letras_del_usuario);//ponemos toda la array en minuscula

                contador = 0;
                //comprueba si hay un error
                for(i = 0; i < tamano_palabra_en_juego; i++)
                {
                    if(letras_del_usuario[tamano_letras_ingresadas - 1] != palabra[palabra_en_juego][i])
                    {
                        contador++;
                        if(contador == tamano_palabra_en_juego)
                        {
                            errores++;
                        }
                    }
                }
            }

            LimpiaPantalla();

            if(errores == 7)
            {
                while(1)
                {
                    TituloJuego();
                    MensajePerdiste();
                    printf("\n\n           LA PALABRA SECRETA ERA: %s", palabra[palabra_en_juego]);
                    printf("\n\n\n           QUIERES VOLVER A JUGAR <s/n>? ");
                    fflush(stdin);
                    scanf("%c", &volver_a_jugar);
                    LimpiaPantalla();
                    if(volver_a_jugar == 's' || volver_a_jugar == 'n' || volver_a_jugar == 'S' || volver_a_jugar == 'N')
                        break;
                }
            }
            //esto verifica si las letras de la palabra temporal son las mismas que la palabra en juego y si es asi el usuario gana
            contador = 1;
            for(i = 0; i < tamano_palabra_en_juego; i++ )
            {
                    if(palabra[palabra_en_juego][i] == palabra_temporal_formada[i])
                    {
                        contador++;
                    }
            }
            if(contador == tamano_palabra_en_juego)
            {
                while(1)
                {
                    TituloJuego();
                    MensajeGanaste();
                    printf("\n\n              LA PALABRA SECRETA ERA: %s", palabra[palabra_en_juego]);
                    printf("\n\n\n              QUIERES VOLVER A JUGAR <s/n>? ");
                    fflush(stdin);
                    scanf("%c", &volver_a_jugar);
                    LimpiaPantalla();
                    if(volver_a_jugar == 's' || volver_a_jugar == 'n' || volver_a_jugar == 'S' || volver_a_jugar == 'N')
                        break;
                }
                errores = 7;
            }
        }
    }
    return 0;
}
