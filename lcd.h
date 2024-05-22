

#ifndef LCD_H_
#define LCD_H_

#include "msp430g2553.h"
#include <stdarg.h>//funcion para detectar argumentos variables
#include <stdlib.h>

void Conf_LCD1602(void);
void LCD1602_Com(char comando);
void LCD1602_Dato(char dato);


void LCD1602_E(void);
void LCD1602_Pos(char columna, char fila);
int LCD1602_Cadena(char* cadena,unsigned char* columna, unsigned char* fila);
void LCD1602_GC (const char* datos,char dir);

void LCD1602_Char(char dato);
unsigned char LCD1602_Print(char* conv,unsigned char* columna, unsigned char* fila);
unsigned char LCD1602_Printf(char* conv,unsigned char* columna, unsigned char* fila,...);


unsigned char Conv_Entero(long long numero,char* conv);


/*DEfinciones de Comando*/

#define GCRAM 0x40 //comando para guardar algun caracter personalizado

#define CLEAR 0x1 //limpia la pantalla

#define HOME  0x2 //manda cursor a Home 0,0

//Combinacion de los siguientes parametros para mandar comando
#define IncAdd  0x6 //Incrementa la direccion en cada escritura
#define DecAdd  0x4 //Decrementa la direccion en cada escritura

#define NSDisp 0x4 //no desplaza la pantalla
#define SDisp 0x5 //desplaza la pantalla 1 posicion

//combinacion de los siguientes parametros para mandar comando
#define ONDisp    0xC //enciende la pantalla
#define OFFDisp   0x8 //apaga la pantalla

#define ONCursor  0xA //prende el cursor visual
#define OFFCursor 0x8 //apaga el cursor visual

#define ONBlink   0x9 //hace que el cursor parpadee
#define OFFBlink  0x8 //El parpadeo se desactiva

//mandar solo una defincion en este comando
#define SRDisp  0x1C //Desplaza la pantalla a la der, la dir no cambia
#define SLDisp  0x18 //Desplaza la pantalla a la izq, la dir no cambia
#define CRDisp  0x14 //mueve el cursor a la der, la dir aumenta en 1
#define CLDisp  0x10 //mueve el cursor a la izq, la dir disminuye en 1

//combinacion de los siguientes parametros para mandar comando
#define M8BIT     0x30 //modo 8bit
#define M4BIT     0x20 //modo 4bit

#define M1LINE    0x20 //modo 1 linea
#define M2LINE    0x28 //modo 2 lineas

#define M5_8_Font 0x20 //fuente 5x8
#define M5_11_Font 0x24 //fuente 5x11 solo para 1 linea

#define PUERTO_E  P1
#define PUERTO_RS P1
#define PUERTO_RW P1
#define PUERTO_D4 P1
#define PUERTO_D5 P1
#define PUERTO_D6 P2
#define PUERTO_D7 P2

#define E  BIT3
#define RS BIT1
#define RW BIT2
#define D4 BIT4
#define D5 BIT5
#define D6 BIT1
#define D7 BIT2

#define E_POS  3
#define RS_POS 1
#define RW_POS 2
#define D4_POS 4
#define D5_POS 5
#define D6_POS 1
#define D7_POS 2


#define OUTp(p)    Out(p)
#define Out(p)    p ## OUT    //abreviacion para seleccionar el puerto indicado (PxOUT)

#define DIRp(p)    Dir(p)
#define Dir(p)    p ## DIR    //abreviacion para seleccionar el puerto indicado (PxDIR)

#define INp(p)     In(p)
#define In(p)     p ## IN     //abreviacion para seleccionar el puerto indicado (PxIN)

#define SELp(p)    Sel(p)
#define Sel(p)    p ## SEL    //abreviacion para seleccionar el puerto indicado (PxSEL)

#define RENp(p)    Ren(p)
#define Ren(p)    p ## REN    //abreviacion para seleccionar el puerto indicado (PxREN)

#define SEL2p(p)   Sel2(p)
#define Sel2(p)   p##SEL2



//------------------ Definiciones Pin E ---------------

#define E_OUT   OUTp( PUERTO_E )
#define E_DIR   DIRp(PUERTO_E)
#define E_REN   RENp( PUERTO_E )
#define E_SEL   SELp(PUERTO_E)
#define E_SEL2  SEL2p(PUERTO_E)
#define E_IN    INp(PUERTO_E)

//------------------ Definiciones Pin RS ---------------

#define RS_OUT   OUTp( PUERTO_RS )
#define RS_DIR   DIRp(PUERTO_RS)
#define RS_REN   RENp( PUERTO_RS )
#define RS_SEL   SELp(PUERTO_RS)
#define RS_SEL2  SEL2p(PUERTO_RS)
#define RS_IN    INp(PUERTO_RS)

//------------------ Definiciones Pin RW ---------------

#define RW_OUT   OUTp( PUERTO_RW )
#define RW_DIR   DIRp(PUERTO_RW)
#define RW_REN   RENp( PUERTO_RW )
#define RW_SEL   SELp(PUERTO_RW)
#define RW_SEL2  SEL2p(PUERTO_RW)
#define RW_IN    INp(PUERTO_RW)

//------------------ Definiciones Pin D4 ---------------

#define D4_OUT   OUTp( PUERTO_D4 )
#define D4_DIR   DIRp(PUERTO_D4)
#define D4_REN   RENp( PUERTO_D4 )
#define D4_SEL   SELp(PUERTO_D4)
#define D4_SEL2  SEL2p(PUERTO_D4)
#define D4_IN    INp(PUERTO_D4)

//------------------ Definiciones Pin D5 ---------------

#define D5_OUT   OUTp( PUERTO_D5 )
#define D5_DIR   DIRp(PUERTO_D5)
#define D5_REN   RENp( PUERTO_D5 )
#define D5_SEL   SELp(PUERTO_D5)
#define D5_SEL2  SEL2p(PUERTO_D5)
#define D5_IN    INp(PUERTO_D5)

//------------------ Definiciones Pin D6 ---------------

#define D6_OUT   OUTp( PUERTO_D6 )
#define D6_DIR   DIRp(PUERTO_D6)
#define D6_REN   RENp( PUERTO_D6 )
#define D6_SEL   SELp(PUERTO_D6)
#define D6_SEL2  SEL2p(PUERTO_D6)
#define D6_IN    INp(PUERTO_D6)
//------------------ Definiciones Pin D7 ---------------

#define D7_OUT   OUTp( PUERTO_D7 )
#define D7_DIR   DIRp(PUERTO_D7)
#define D7_REN   RENp( PUERTO_D7 )
#define D7_SEL   SELp(PUERTO_D7)
#define D7_SEL2  SEL2p(PUERTO_D7)
#define D7_IN    INp(PUERTO_D7)



const char signos[8][8]= //°¬¡?\¨´ñ
{
 {2,5,2,0,0,0,0,0}, // °
 {0,0,0,0,0xF,1,0,0}, // ¬
 {4,0,0,4,4,4,4,0},// ¡
 {4,0,4,8,0x10,0x11,0xE,0}, //¿
 {0,0x10,8,4,2,1,0,0},// diagonal invertida
 {0xA,0,0,0,0,0,0,0}, //¨
 {0,2,4,8,0,0,0,0},//´
 {0xA,0x05,0,0x16,0x19,0x11,0x11,0}//ñ

};


void Conf_LCD1602(void)
{
    long Delay=0;

    E_DIR|=E;
    E_OUT&=~E;
    E_REN&=~E;
    E_SEL&=~E;
    E_SEL2&=~E;

    RS_DIR |=RS;
    RS_OUT &=~RS;
    RS_REN &=~RS;
    RS_SEL &=~RS;
    RS_SEL2&=~RS;

    RW_DIR|=RW;
    RW_OUT&=~RW;
    RW_REN&=~RW;
    RW_SEL&=~RW;
    RW_SEL2&=~RW;


    D4_DIR|=D4;
    D4_OUT&=~D4;
    D4_REN&=~D4;
    D4_SEL&=~D4;
    D4_SEL2&=~D4;

    D5_DIR|=D5;
    D5_OUT&=~D5;
    D5_REN&=~D5;
    D5_SEL&=~D5;
    D5_SEL2&=~D5;

    D6_DIR|=D6;
    D6_OUT&=~D6;
    D6_REN&=~D6;
    D6_SEL&=~D6;
    D6_SEL2&=~D6;

    D7_DIR|=D7;
    D7_OUT&=~D7;
    D7_REN&=~D7;
    D7_SEL&=~D7;
    D7_SEL2&=~D7;

    for(Delay=30000; Delay>0; Delay--);//20 ms aprox a 16MHz
    //manda 0x3 en la parte alta de la LCD
    D4_OUT|=D4;
    D5_OUT|=D5;
    LCD1602_E(); //manda un pulso en el pin E (Enable)
    for(Delay=10000; Delay>0; Delay--);//7 ms aprox a 16MHz

    LCD1602_E(); //manda un pulso en el pin E (Enable)
    for(Delay=500; Delay>0; Delay--);//100 us aprox a 16MHz

    LCD1602_E(); //manda un pulso en el pin E (Enable)
    for(Delay=10000; Delay>0; Delay--);//7 ms aprox a 16MHz

    //primer comando 0x20 configuracion a 4 bits
    D4_OUT&=~D4; //conf para los pines D4-7 = P1.4-7
    LCD1602_E(); //manda un pulso en el pin E (Enable)
    for(Delay=240; Delay>0; Delay--);//40 us aprox a 16MHz

    /*M8BIT o M4BIT,M2LINE o M1LINE, M5_8_Font o M5_11_Font */
    LCD1602_Com(M4BIT|M2LINE|M5_8_Font);

    /*ONDisp o OFFDisp, ONCursor o OFFCursor,ONBlink o OFFBLink*/
    LCD1602_Com(ONDisp|OFFCursor|OFFBlink );

    LCD1602_Com(CLEAR); //limpia la pantalla
    for(Delay=3000; Delay>0; Delay--);//1.60 ms aprox a 16MHz//OJOJO  30

    /*IAdd o DAdd*/
    LCD1602_Com(IncAdd);

    for(Delay=0;Delay<8;Delay++)
    {
        LCD1602_GC(&signos[Delay][0], Delay);
    }


    LCD1602_Com(HOME);//Manda cursor a home
    for(Delay=3000; Delay>0; Delay--);//1.60 ms aprox a 16MHz
}

void Conf_Reloj(void)
{
    DCOCTL=CALDCO_16MHZ;
    BCSCTL1=CALBC1_16MHZ; //conf para DCO=16MHz aprox 15.62 a 15.72MHz

    /*Seleccion de ACLK*/
    BCSCTL3&=~(LFXT1S_3);
    BCSCTL3|=LFXT1S_2;  //ACLK=VLOCLK
    /*Division de ACLK*/
    BCSCTL1&=~DIVA_3; //Division de ACLK/1;

    /*SEleccion de MCLK*/
    BCSCTL2&=~SELM_3; //MCLK=DCOCLK
    /*Division de MCLK*/
    BCSCTL2&=~DIVM_3; //Division de MCLK/1;

    /*Seleccion de SMCLK*/
    BCSCTL2&=~SELS; // 0=DCOCLK 1=ACLK
    /*Division de SMCLK*/
    BCSCTL2&=~DIVS_3; //Division de SMCLK/1;
}

void LCD1602_Com(char comando)
{
    unsigned char Delay=0;
    unsigned char valorD4=0,valorD5=0,valorD6=0,valorD7=0;
    unsigned char valorRW=0, valorRS=0;
    //guarda los valores anterior de los pines, en caso que se compartan con otras cosas
    valorD4=D4_IN & D4;
    valorD5=D5_IN & D5;
    valorD6=D6_IN & D6;
    valorD7=D7_IN & D7;
    valorRW=RW_IN & RW;
    valorRS=RS_IN & RS;

    RW_OUT&=~RW; //RW para escritura 1=lectura 0=escritura
    RS_OUT&=~RS; //RS 1=dato 0=comando


    if(comando&0x80)
        D7_OUT|=D7;
    else
        D7_OUT&=~D7;

    if(comando&0x40)
        D6_OUT|=D6;
    else
        D6_OUT&=~D6;

    if(comando&0x20)
        D5_OUT|=D5;
    else
        D5_OUT&=~D5;

    if(comando&0x10)
        D4_OUT|=D4;
    else
        D4_OUT&=~D4;
    LCD1602_E(); //manda un pulso en el pin E (Enable)



    if(comando&0x8)
        D7_OUT|=D7;
    else
        D7_OUT&=~D7;

    if(comando&0x4)
        D6_OUT|=D6;
    else
        D6_OUT&=~D6;

    if(comando&0x2)
        D5_OUT|=D5;
    else
        D5_OUT&=~D5;

    if(comando&0x1)
        D4_OUT|=D4;
    else
        D4_OUT&=~D4;
    LCD1602_E(); //manda un pulso en el pin E (Enable)
    for(Delay=150; Delay>0; Delay--);//40 us aprox a 16MHz


    D4_OUT&=~D4;//reinicia los bits
    D5_OUT&=~D5;
    D6_OUT&=~D6;
    D7_OUT&=~D7;
    RS_OUT&=~RS;
    RW_OUT&=~RW;
    D4_OUT|=valorD4; //restaura el valor anterior
    D5_OUT|=valorD5;
    D6_OUT|=valorD6;
    D7_OUT|=valorD7;
    RS_OUT|=valorRS;
    RW_OUT|=valorRW;
}
void LCD1602_Dato(char dato)
{
    unsigned char Delay=0;
    unsigned char valorD4=0,valorD5=0,valorD6=0,valorD7=0;
    unsigned char valorRW=0, valorRS=0;
    //guarda los valores anterior de los pines, en caso que se compartan con otras cosas
    valorD4=D4_IN & D4;
    valorD5=D5_IN & D5;
    valorD6=D6_IN & D6;
    valorD7=D7_IN & D7;
    valorRW=RW_IN & RW;
    valorRS=RS_IN & RS;

    RW_OUT&=~RW; //RW para escritura 1=lectura 0=escritura
    RS_OUT|=RS; //RS 1=dato 0=comando


    if(dato&0x80)
        D7_OUT|=D7;
    else
        D7_OUT&=~D7;

    if(dato&0x40)
        D6_OUT|=D6;
    else
        D6_OUT&=~D6;

    if(dato&0x20)
        D5_OUT|=D5;
    else
        D5_OUT&=~D5;

    if(dato&0x10)
        D4_OUT|=D4;
    else
        D4_OUT&=~D4;
    LCD1602_E(); //manda un pulso en el pin E (Enable)


    if(dato&0x8)
        D7_OUT|=D7;
    else
        D7_OUT&=~D7;

    if(dato&0x4)
        D6_OUT|=D6;
    else
        D6_OUT&=~D6;

    if(dato&0x2)
        D5_OUT|=D5;
    else
        D5_OUT&=~D5;

    if(dato&0x1)
        D4_OUT|=D4;
    else
        D4_OUT&=~D4;
    LCD1602_E(); //manda un pulso en el pin E (Enable)
    for(Delay=150; Delay>0; Delay--);//40 us aprox a 16MHz


    D4_OUT&=~D4;//reinicia los bits
    D5_OUT&=~D5;
    D6_OUT&=~D6;
    D7_OUT&=~D7;
    RS_OUT&=~RS;
    RW_OUT&=~RW;
    D4_OUT|=valorD4; //restaura el valor anterior
    D5_OUT|=valorD5;
    D6_OUT|=valorD6;
    D7_OUT|=valorD7;
    RS_OUT|=valorRS;
    RW_OUT|=valorRW;
}

void LCD1602_Char(char dato)
{
    //°¬¡?\¨´ñ
    switch(dato)
    {
    case '°':
        dato=0;
        break;
    case '¬':
        dato=1;
        break;
    case '¡':
        dato=2;
        break;
    case '¿':
        dato=3;
        break;
    case '\\':
        dato=4;
        break;
    case '¨':
        dato=5;
        break;
    case '´':
        dato=6;
        break;
    case 'ñ':
    case 'Ñ':
        dato=7;
        break;
    default:
        break;
    }
    LCD1602_Dato(dato);
}




void LCD1602_E(void)
{
    E_OUT|=E; //manda a 1 logico el bit E (Enable)
    E_OUT&=~E;//manda a 0 logico E, completando el pulso
}

void LCD1602_Pos(char columna, char fila)//funcion para la posicion
{
    register long direccion=0x80;//se carga el valor a direccion
    direccion|=columna&0xF;// los primeros 4 bits son para la columna
    direccion|=((fila&0x1)<<6);// y el bit numero 6 es para la fila
    LCD1602_Com(direccion);// esto se manda atraves de la funcion
}



int LCD1602_Cadena(char* cadena,unsigned char* columna, unsigned char* fila)// esta funcion regresa la cantidad de caracteres que se escribieron, recibe 3 puntero
{                                                                           //la primera es la posicion en donde comienza la cadena
                                                                             //el segundo y tercero la posicion donde se mostrará en la lcd

    register int conteo=0;//variable usada para saber cuentos caracteres se imprimieron, lo cual se retornará

    LCD1602_Pos(*columna,*fila); //indica la posicion inicial del cursor
    while(*cadena)// realiza el ciclo mientras la cadena tenga algun valor de 0 o '\0', esto indica fin de cadena

    {
        LCD1602_Dato(*(cadena)); //envia el caracter correspondiente
        (*columna)++; //se le suma 1 al valor que guarda columna indicando que se ha escrito un valor
        if((*columna&0xF)==0) //si se pasa del numero 15 entonces, columna es 0 indica que empieza una nueva fila
        {
            (*columna)=0;//se le asigna el valor de cero al direccion de columna
            (*fila)++; //invierte el valor de fila para que se reincie, esto para que imprima en la fila
            LCD1602_Pos(*columna,*fila); //pone el cursor en 0,x8
        }

        cadena++; //el puntero apunta al siguiente caracter
        conteo++; //suma 1 al conteo total de caracter enviados a la LCD
    }
    return conteo;
}

unsigned char Conv_Entero(long long numero, char* conv)//funcion para convertir numeros enteros, recibe un numero de 64 bits
{                                                       //un puntero donde se comenzará a convertir y retorna el numero de digitos que se convirtió
    char           convTemp[21]; //longitud maxima de 21 digitos con signo, es decir 19 para digitos, 1 para el signo y otro para el final cadena
    register char *punteroActual;//se coloca un apuntador que direcciona a la linea superior
    register int num=0;//contiene el digito que se convertirá a caracter
    register char i=0;
    register long long  numeroReg = numero;//se pasa el numero a un registro

    punteroActual = &convTemp[21 - 1]; //empezamos apuntando a la ultima posicion, para obtener el digito de mas peso
    *punteroActual = 0; //guarda el fin de cadena en la ultima posicion
    if( numeroReg < 0)//se compara si el numero es negativo
    {
        numeroReg*=-1;//se multiplica por menos 1
    }

    do {
        punteroActual--;//se decrementa la posicion donde se guardará el valor
        num=numeroReg % 10; //se obtiene el digito de mayor peso
        *punteroActual = num  + '0'; //'0' convierte el valor en caracter
    }  while((numeroReg /= 10)); //mientras exista un digito sigue el ciclo

    if ( numero < 0) // se verifica si es negativo
    {
        punteroActual--;//se decrementa la ultima posicion
        *punteroActual = '-';//si el numero es negativo guarda el signo negativo
    }

    numeroReg=convTemp+21-punteroActual;//realiza la resta de cuantos caracteres se utilizaron
    for (i = 0; i< numeroReg; i++) //hace un ciclo
    {
        ((unsigned char *)conv)[i] = ((const unsigned char *)punteroActual)[i];
    }

    return numeroReg - 1;//no se toma en cuenta el fin de cadena
}

void LCD1602_GC(const char* datos, char dir)
{
  register char i=0;
  if( dir>7) //solo tiene espacio para guardar 8 caracteres
    return;
  LCD1602_Com(GCRAM+(dir<<3)); // 01xx xddd x=caracter d=posicion
  while(i<8)
  {
    LCD1602_Dato(datos[i++]);
  }
}

unsigned char LCD1602_Print(char* cadena,unsigned char* columna, unsigned char* fila)
{

    register unsigned char conteo=0;//variable usada para saber cuantos caracteres se mandaron a la LCD
    register char salir=0; //variable que funciona cuando encuentra un ESC
    register int delay; //utilizada para los comandos como clear y home
    (*columna)&=0xF;//delimita el valor inicial de columna de 0 a 15 (4 BITS)
    LCD1602_Pos(*columna,*fila); //indica la posicion inicial del cursor
    while(*cadena)// realiza el ciclo mientras la cadena tenga algun valor
           //el valor 0 o '\0' es fin de cadena
    {
        switch (*cadena) //detecta si existe un caracter especial
        {
        case '\n': //salto de linea
            (*fila)++; //aumenta la fila
            LCD1602_Pos(*columna,*fila); //actualiza la posicion
            break;
        case '\r': //retorno de carro (que se regresa a la columna 0)
            *columna=0; //actualiza el valor de la columna a la primera posicion
            LCD1602_Pos(*columna,*fila); //actualiza la posicion
            break;
        case '\t': //tabulacion
            if(((*columna)&0xF)<13)
                *columna+=3; //aumenta 3 espacios vacios
            else
            {
                *columna=0; // pasa a la siguiente fila si no cabe la tabulacion
                *fila++;
            }
            LCD1602_Pos(*columna,*fila); //actualiza la posicion
            break;
         case '\b': //retroceso (regresa una posicion en columna)
            if(((*columna)!=0) || ((*fila)!=0)) //si la columna y fila es diferente a 0 puede retroceder
            {
                if(((*columna)!=0)) //si la columna encuentra entre 1 y 15 puede disminuir uno
                    (*columna)--;
                else
                    if(((*fila)!=0)) //si la columna es 0 entonces checa si existen filas que disminuir
                    {
                        (*columna)=0xF;
                        (*fila)--;
                    }
            }
            LCD1602_Pos(*columna,*fila); //actualiza la posicion
            break;
        case '\a'://borrado (ascii sonido), borra el caracter anterior
            if(((*columna)!=0) || ((*fila)!=0)) //si la columna es diferente a 0 puede retroceder
            {
                if(((*columna)!=0))
                    (*columna)--;
                else
                    if(((*fila)!=0))
                    {
                        (*columna)=0xF;//se posiciona en la columna 15
                        (*fila)--;
                    }
            }
            LCD1602_Pos(*columna,*fila); //actualiza la posicion
            LCD1602_Char(' ');//borra el caracter que pudiera haber en la posicion
            LCD1602_Pos(*columna,*fila); //actualiza la posicion
            break;
        case '\e': //escape ( termina el proceso y ya no imprime mas)
            salir=1;//indica que se necesita salir de la funcion
            break;

        default :
            LCD1602_Char(*(cadena)); //envia el caracter correspondiente
            (*columna)++; //suma 1 a la columna indicando que se ha escrito un valor
            if((*columna&0xF)==0) //si la columna es 0 indica que empieza una nueva fila
            {
                (*columna)=0;
                (*fila)++; //invierte el valor e fila para que se reinciie
                LCD1602_Pos(*columna,*fila); //pone el cursor en 0,x
            }
            break;
        }
        cadena++; //el puntero apunta al siguiente caracter
        conteo++; //suma 1 al conteo total de caracter enviados a la LCD
        if(salir) //si detecto un \e (escape) sale del ciclo while
            break;
    }
     return conteo; //regresa el conteo de caracteres y caracteres especiales
}




unsigned char LCD1602_Printf(char* cadena,unsigned char* columna, unsigned char* fila,...)// los ... indican que serán argumentos variables
{
    register unsigned char conteo=0;//variable usada para saber cuantos caracteres se mandaron a la LCD
    register char salir=0; //variable que funciona cuando encuentra un ESC
    register int delay; //utilizada para los comandos como clear y home

    va_list ap; //crea puntero de los argumentos su utilidad es apuntar adecuadamente al bufer.
    double valorARGd; //variable donde guardara el valor del argumento
    char* valorARGc; //variable donde guardara el valor del argumento
    long valorARGi; //variable donde guardara el valor del argumento
    char conversion[30];
    va_start(ap, fila);//maneja la memoria de los argumentos empezando desde el ultimo conocido ingresado


    (*columna)&=0xF;//delimita el valor inicial de columna de 0 a 15
    LCD1602_Pos(*columna,*fila); //indica la posicion inicial del cursor
    while(*cadena)// realiza el ciclo mientras la cadena tenga algun valor
           //el valor 0 o '\0' es fin de cadena
    {
        switch (*cadena) //detecta si existe un caracter especial
        {
        case '\n': //salto de linea
            (*fila)++; //aumenta la fila
            LCD1602_Pos(*columna,*fila); //actualiza la posicion
            break;
        case '\r': //retorno
            *columna=0; //actualiza el valor de la columna a la primera posicion
            LCD1602_Pos(*columna,*fila); //actualiza la posicion
            break;
        case '\t': //tabulacion
            if(((*columna)&0xF)<13)
                *columna+=3; //aumenta 3 espacios vacios
            else
            {
                *columna=0; // pasa a la siguiente fila si no cabe la tabulacion
                *fila++;
            }
            LCD1602_Pos(*columna,*fila); //actualiza la posicion
            break;
         case '\b': //retroceso
            if(((*columna)!=0) || ((*fila)!=0)) //si la columna y fila es diferente a 0 puede retroceder
            {
                if(((*columna)!=0)) //si la columna encuentra entre 1 y 15 puede disminuir uno
                    (*columna)--;
                else
                    if(((*fila)!=0)) //si la columna es 0 entonces checa si existen filas que disminuir
                    {
                        (*columna)=0xF;
                        (*fila)--;
                    }
            }
            LCD1602_Pos(*columna,*fila); //actualiza la posicion
            break;
        case '\a'://borrado (ascii sonido)
            if(((*columna)!=0) || ((*fila)!=0)) //si la columna es diferente a 0 puede retroceder
            {
                if(((*columna)!=0))
                    (*columna)--;
                else
                    if(((*fila)!=0))
                    {
                        (*columna)=0xF;
                        (*fila)--;
                    }
            }
            LCD1602_Pos(*columna,*fila); //actualiza la posicion
            LCD1602_Char(' ');//borra el caracter que pudiera haber en la posicion
            LCD1602_Pos(*columna,*fila); //actualiza la posicion
            break;
        case '\e': //escape
            salir=1;//indica que se necesita salir de la funcion
            break;
        case '%':
            cadena++;
            switch(*cadena)
            {
                case 'd': //"%d o %i"//indica si es un entero
                case 'i':
                    valorARGi=(int)va_arg(ap, int);//se coloca el puntero (ap) donde se está apuntando mi argumento anterior al argumento siguiente
                                                    //lo cual va hacer un entero y se va hacer el casteo a un entero.
                    Conv_Entero(valorARGi,conversion);//se manda a llamar la funcion para convertir y se guarda en conversion
                    conteo+=LCD1602_Cadena(conversion,columna,fila)-1;//se envia la conversion en la funcion siguiente y el numero de digitos que
                                                                      //contega la cadena se le suma a conteo
                    break;
                case 'u':// "%u"//indica que se mandará un entero sin signo
                    valorARGi=(unsigned int)va_arg(ap, unsigned int);
                    Conv_Entero(valorARGi,conversion);
                    conteo+=LCD1602_Cadena(conversion,columna,fila)-1;
                    break;

                case 'c': //"%c" se indica que se mandará un char
                    valorARGi=(unsigned char)va_arg(ap, unsigned char);
                    LCD1602_Dato(valorARGi);//manda el caracter a la LCD
                    (*columna)++; //suma 1 a la columna indicando que se ha escrito un valor
                    if(((*columna)&0xF)==0) //si la columna es 0 indica que empieza una nueva fila
                    {
                        (*columna)=0;
                        (*fila)++; //aumenta en uno la fila
                        LCD1602_Pos(*columna,*fila); //pone el cursor en 0,x
                    }
                    break;
                case 's':// "%s"
                    valorARGc=(char*)va_arg(ap,char*);  //el siguiente argumento es un puntero
                    conteo+=LCD1602_Print(valorARGc,columna,fila)-1;//imprime la cadena del puntero
                    break;

                default:// "%p"
                    cadena--;//si no es ningun caso anterior regresa al '%'
                    LCD1602_Dato(*cadena);
                    (*columna)++; //suma 1 a la columna indicando que se ha escrito un valor
                    if(((*columna)&0xF)==0) //si la columna es 0 indica que empieza una nueva fila
                    {
                        (*columna)=0;
                        (*fila)++; //invierte el valor e fila para que se reinciie
                        LCD1602_Pos(*columna,*fila); //pone el cursor en 0,x
                    }
                    break;

           }
            break;



        default :
            LCD1602_Char(*(cadena)); //envia el caracter correspondiente
            (*columna)++; //suma 1 a la columna indicando que se ha escrito un valor
            if((*columna&0xF)==0) //si la columna es 0 indica que empieza una nueva fila
            {
                (*columna)=0;
                (*fila)++; //invierte el valor e fila para que se reinciie
                LCD1602_Pos(*columna,*fila); //pone el cursor en 0,x
            }
            break;
        }
        cadena++; //el puntero apunta al siguiente caracter
        conteo++; //suma 1 al conteo total de caracter enviados a la LCD
        if(salir) //si detecto un \e (escape) sale del ciclo while
            break;
    }
    va_end(ap); //reinicia el puntero

     return conteo; //regresa el conteo de caracteres y caracteres especiales
}
#endif  /*LCD_H_*/
