#include <msp430.h> // libreria de la tarjeta
#include <lcd.h>  // libreria del la pantalla lcd
void Segundero();//funcion para aumentar los segundos
void Minutero();//funcion para aumnetar los minutos
void Horero();//funcio para aumentar las horas
void Tiempo();// funcion para verificar el tiempo del pusado del boton
void Configuracion();// funcion para la configuracion de los segundos, minutos o horas
short int  seg=0, segundos=0, min=0, minutos=0, hor=1, hora=0;//inicializando variable para el reloj
int cont=0,WDT_dcnt=0,conteo=0,seleccion=0;//inicializando varibles para las funciones
const int Debounce=1;// para el el boton
unsigned char columna=0, columna1=1,columna2=0,  columna4=9, columna3=7, columna6=6, columna5=5,fila=0;// para la posion del los mensajes en la pantalla lcd
int main(void)
{
  WDTCTL = WDT_ADLY_1000;                   // SE CONFIGURA EL WDT PARA CONTAR 1000 ms
  IE1 = WDTIE;                              // SE HABILITA LA INTERRUPCION POR WDT
  CCR0 =1;                                 // TIEMPO DE ESTABLECIMIENTO DE REF EXTERNA
  CCTL0 = CCIE;                           // INTERRUPCION EN MODO COMPARADOR
  TACTL = TASSEL_1|ID_0|MC_1;               // TACLK = TACLK, /1, Up mode, IE
  P1OUT &= ~0xFF;                           // LIMPIA P1
  P2OUT &= ~0x3F;                           // LIMPIA P2
  P1DIR = 0x7F;                             // P1.0-P1.6 COMO SALIDA
  P2DIR = 0x3F;                             // P2.0-P1.5 COMO SALIDA
  P1REN |= BIT7;        // Resistencia en P1.7 (pulsador derecho)
  P1OUT |= BIT7;        // Modo pull-up
  P1IE |= BIT7;         // habilita la interrupción de P1.7
  P1IES |= BIT7;        // Interrupción por flanco de bajada
  P1IFG &= ~(BIT7);     // baja flag de interrupción de P1.7
  __bis_SR_register(GIE);
       Conf_LCD1602();//configuracion de la pantalla LCD1602
       LCD1602_Print(" -Hora Acatlima-",&columna,&fila);//manda a mostrar lo que esta entre comillas
       columna2=13;                                    //posicion en la columnas
       columna1=11;
       columna4=10;
       columna3=8;
       columna6=7;
       columna5=6;
       fila=1;                                        //posicion en la fila
       LCD1602_Printf("%i",&columna2,&fila,seg);     //manda los numeros en la posicion indicada para mostrar la hora correcta
       LCD1602_Printf(":%i",&columna1,&fila,segundos);
       LCD1602_Printf("%i",&columna4,&fila,min);
       LCD1602_Printf(":%i",&columna3,&fila,minutos);
       LCD1602_Printf("%i",&columna6,&fila,hor);
       LCD1602_Printf("%i",&columna5,&fila,hora);
  // bucle infinito.
  while (1) {
    cont++;
      if(seleccion==0){                        // para cuando entre en modo configuracion se detenga la hora
       Segundero();
       columna2=13;
       columna1=11;
       columna4=10;
       columna3=8;
       columna6=7;
       columna5=6;
       fila=1;
       LCD1602_Printf("%i",&columna2,&fila,seg);           //manda los numeros en la posicion indicada para mostrar la hora correcta
       LCD1602_Printf(":%i",&columna1,&fila,segundos);
       LCD1602_Printf("%i",&columna4,&fila,min);
       LCD1602_Printf(":%i",&columna3,&fila,minutos);
       LCD1602_Printf("%i",&columna6,&fila,hor);
       LCD1602_Printf("%i",&columna5,&fila,hora);
      }

       __low_power_mode_3(); // entramos en modo LPM3
  }
}
//--------------------------------------------------------------------------------------
void Segundero(){         // funcion de aumento de segundos
    seg++;
    if(seg==10){
         seg=0;
         segundos++;
         if(segundos==6)
         {
             segundos=0;
             if(seleccion==0){//solo entra cuando no esta en modo configuracion
             Minutero(); //manda a llamar a la funcion de aumento de minuto cuando los segundos llegan a 60
             }
         }
       }

}

//--------------------------------------------------------------------------------------
void Minutero(){   // funcion de aumento de minutos
    min++;
    if(min==10){
        min=0;
        minutos++;
        if(minutos==6){
            minutos=0;
            if(seleccion==0){//solo entra cuando no esta en modo configuracion
             Horero();    // manda a llamar a la funcion que aumenta la hora cuando los minutos llegan a 60
            }
         }
    }
}
//--------------------------------------------------------------------------------------
void Horero(){      // funcion de aumento de horas
    hor++;
    if(hora==1){
        if(hor==3){// como el reloj es de 12hrs cuando la hora llega a 13 se reinicia
            hor=1;
            hora=0;
        }
    }
    if(hor==10){
             hor=0;
             hora++;
    }
}
//--------------------------------------------------------------------------------------
void Tiempo(){
    conteo++;               // conteo para cambiar de modo configuacion
    if(conteo==0x055){      // si llega este conteo cambia al siguinte modo configuracion hasta salirse de ella.
        seleccion++;
        if(seleccion==4){     //reinicia cuando ya pasapor todas las opciones
            seleccion=0;
        }
    }
    switch (seleccion)         //Escoge el titulo para la opcion seleccionada
            {
            case 1:
                   columna=0;
                   fila=0;
            LCD1602_Print("Config Segundos:",&columna,&fila);//configuracion segundos si seleccion=1
                    break;
            case 2:
                    columna=0;
                    fila=0;
            LCD1602_Print("Configu Minutos:",&columna,&fila);//configuracion minutos si seleccion=2
                    break;
            case 3:
                    columna=0;
                    fila=0;
            LCD1602_Print("Configura Horas:",&columna,&fila);//configuracion horas si seleccion=3
                    break;
            default:
                columna=0;
                fila=0;
                LCD1602_Print(" -Hora Acatlima-",&columna,&fila);//titulo normal del reloj cuando no esta en modo configuracion
                    break;
        }
}
void Configuracion(){
    WDT_dcnt=0;
    switch (seleccion)//modifica el reloj segun la opcion selecionada
            {
            case 1:conteo=0;
                    columna2=13;
                    columna1=11;
                    fila=1;
                    Segundero();//si seleccion=1 se modifica el segundo a cada pulso del boton
                    LCD1602_Printf("%i",&columna2,&fila,seg);           //Actualiza los segundos
                    LCD1602_Printf(":%i",&columna1,&fila,segundos);
                    break;
            case 2: conteo=0;
                    columna4=10;
                    columna3=8;
                    fila=1;
                    Minutero();//si seleccion=2 se modifica el minutos a cada pulso del boton
                    LCD1602_Printf("%i",&columna4,&fila,min);  //Actualiza los minutos
                    LCD1602_Printf(":%i",&columna3,&fila,minutos);
                    break;
            case 3: conteo=0;
                    columna6=7;
                    columna5=6;
                    fila=1;
                    Horero();//si seleccion=3 se modifica el horas a cada pulso del boton
                    LCD1602_Printf("%i",&columna6,&fila,hor);    //Actualiza las horas
                    LCD1602_Printf("%i",&columna5,&fila,hora);
                    break;
            default: conteo=0;// para cuando el reloj esta en modo normal (fuera del modo onfiguracion)
                   break;
        }
}
#pragma vector=PORT1_VECTOR
__interrupt void P1_ISR(void) {
    P1IFG &= ~BIT7; // puesta a cero del flag de interrupción P1.7
    WDT_dcnt=Debounce;//manda un pulso a al WDT para decirle que se pulso el boton
}
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TA0_ISR(void)
{
    if(WDT_dcnt>0){ // verifica si se a pulsado el boton
            Configuracion();// modifica la hora deacuerdo a la opcion donde se encuentre
        }
        if(P1IN & BIT7){// verifica si el boton sigue pulsado
               Tiempo(); //si, mada a llamar a la funcion tiempo para hacer el conteo del tiempo del pulso
            }
}
#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR(void)
{
    LPM3_EXIT;                            // SALE DE LPM3
}
