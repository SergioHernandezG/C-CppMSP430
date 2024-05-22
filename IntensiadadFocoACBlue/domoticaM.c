#include <msp430.h>///LIBRERIAS
#include <uart.h>/////
#include <lcd.h>  //

#define TXD BIT2
#define RXD BIT1

void Asignacion(int asig);
void Direciones(int dir);
void Modoss(int mod);
void Color();
void Colores(int elegir);
void Rojo();
void Verde();
void Azul();
void Intensidad();
void Estrobo();
void Ascii(int asc);

int maestro=0,dire,modos,inten,bandera=0,bandera1=0,bandera2=0,bandera3=0,bandera4=0,RGB,strob=0,contador=0,ValRojo=0;
int Val1=0,Val2=0,Val3=0,bandera5=0,bandera6=0,ValVerde=0,ValAzul=0;
char enviar;
int const  Abdiel=0x48,Osmar=0x49,Serch=0x50,Jorge=0x51,Jesus=0x52,Eicarld=0x53,Tonii=0x54;
int const TABLABR0=1666;//,pro=0;    // VALORES OBTENIDOS DE DATASHEET 9600 baudios
int const TABLABR1=6,TABLAMCTL=12; // PARA RELOJ DE 16MHZ

int main(void)
{
     WDTCTL = WDTPW | WDTHOLD;  // stop watchdog timer
     // configurando UART
     DCOCTL = 0; // Select lowest DCOx and MODx settings
     BCSCTL1 = CALBC1_16MHZ; // configuramos velocidad de reloj
     DCOCTL = CALDCO_16MHZ;
     P1SEL = BIT1 + BIT2 + BIT6 + BIT7;        // UART: P1.1 = RXD, P1.2=TXD
     P1SEL2 = BIT1 + BIT2 + BIT6 + BIT7;       // UART: P1.1 = RXD, P1.2=TXD
     UCB0CTL1 |= UCSWRST;                      //Activar SW reset
     UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode
     UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
     UCB0BR0 = 12;                             // fSCL = SMCLK/12 = ~100kHz
     UCB0BR1 = 0;
     CONFUART(TABLABR0,TABLABR1,TABLAMCTL);  //configuramos numero de baudios
     activacionRX();           //activamos RX

     __bis_SR_register(CPUOFF + GIE); // modo bajo consumo
     maestro=getRX();            //obtine caracter
     if(maestro>=0){///Entra para la seleccion de esclavos
     while(1){
       __bis_SR_register(CPUOFF + GIE); // modo bajo consumo  para obtener la direccion del esclavo
       dire=getRX();            //obtine caracter
       Asignacion(dire);
      }
     }
}
void Asignacion(int asig){
    bandera=0;
        switch(asig){//-----------Elige la direccion del esclavo y los manda a una funcion de direciones para conectar con el eclavo
                      case 49: Direciones(Abdiel);  //Direccion del esclavo del equipo de Abdiel
                      break;
                      case 50: Direciones(Osmar);  //Direccion del esclavo del equipo de Osmar
                      break;
                      case 51: Direciones(Serch);  //Direccion del esclavo del equipo de Serch
                      break;
                      case 52: Direciones(Jorge);  //Direccion del esclavo del equipo de Jorge
                      break;
                      case 53: Direciones(Jesus);  //Direccion del esclavo del equipo de Jesus
                      break;
                      case 54: Direciones(Eicarld);//Direccion del esclavo del equipo de Eicarld
                      break;
                      case 55: Direciones(Tonii); //Direccion del esclavo del equipo de Tonii
                      break;
                      default: break;  //Direccion del esclavo del equipo de Serch por defecto
                      }
}
void Direciones(int dir){
        contador=0;
        UCB0I2CSA = dir;                         // Slave Address initialization
        UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
       while(bandera < 1){
        __bis_SR_register(CPUOFF + GIE); // modo bajo consumo
        modos=getRX();            //obtine caracter
        if(modos>=49 && modos<=56){
            Asignacion(modos);
            bandera=1;
        }
        else{
          Modoss(modos);
        }
       }
}

void Modoss(mod){
    contador=0;
    switch(mod){//modos del a--d
          case 97: enviar= 'a';          //modo "a" combinaciones de color RGB
          break;
          case 98: enviar= 'b';         //modo "b" intensidad del 0 10 porciento
          break;
          case 99: enviar= 'c';         //modo "c" strobo
          break;
          case 100: enviar= 'd';         //modo "d" Apagado
          break;
          default:  break;;         //modo "c" Strobo y la "d" apagar
          }
    UCB0CTL1 |= UCTR | UCTXSTT; //PARA INICIAR
         while(UCB0CTL1 & UCTXSTT){
             UCB0TXBUF = enviar;//enviar;//0x0001; //01=encendido, 11=apagado
         }
         bandera1=0;
         bandera2=0;
         bandera3=0;
         switch(mod){
         case 97: Color();          //modo "a" combinaciones de color RGB
         break;
         case 98: Intensidad();         //modo "b" intensidad del 0 10 porciento
         break;
         case 99: Estrobo();         //modo "c" strobo
         break;
         default:  break;;         //modo "c" Strobo y la "d" apagar
         }
}

void Color(){
    while(bandera1 < 1){
           __bis_SR_register(CPUOFF + GIE); // modo bajo consumo
           RGB=getRX();            //obtine caracter
           if(RGB>=49 && RGB<=56){
               Asignacion(RGB);
                       bandera1=1;
                   }
          if(RGB>=97 && RGB<=100){
               Modoss(RGB);
               bandera1=1;
           }
           else{
               bandera1=0;
               Colores(RGB);
           }
          }
}
//-----------------------funciones de los modos-------------
void Colores(elegir){
     contador=0;
    switch(elegir){//modos del a--d
          case 114: enviar= 'r';          //modo "a" combinaciones de color RGB
          break;
          case 118:  enviar= 'g';         //modo "b" intensidad del 0 10 porciento
          break;
          case 122: enviar= 'z';         //modo "c" strobo
          break;
          default:  break;         //modo "c" Strobo y la "d" apagar
          }
    setTX(enviar);            //transmite caracter
    UCB0CTL1 |= UCTR | UCTXSTT; //PARA INICIAR
         while(UCB0CTL1 & UCTXSTT){
             UCB0TXBUF = enviar;//0x0001; //01=encendido, 11=apagado
         }
         switch(elegir){//modos del a--d
               case 114: Rojo();          //modo "a" combinaciones de color RGB
               break;
               case 118: Verde();         //modo "b" intensidad del 0 10 porciento
               break;
               case 122: Azul();         //modo "c" strobo
               break;
               default:  break;         //modo "c" Strobo y la "d" apagar
               }
}
void Intensidad(){
    contador=0;
    while(bandera2 < 1){
              __bis_SR_register(CPUOFF + GIE); // modo bajo consumo
              inten=getRX();            //obtine caracter
              if(inten>=49 && inten<=56){
                  Asignacion(inten);
                          bandera2=1;
                      }
              if(inten>=97 && inten<=100){
                  Modoss(inten);
                  bandera2=1;
              }
                Ascii(inten);
             }
}

void Estrobo(){
    contador=0;
    while(bandera3 < 1){
              __bis_SR_register(CPUOFF + GIE); // modo bajo consumo
              strob=getRX();            //obtine caracter
              if(strob>=49 && strob<=56){
                  Asignacion(strob);
                          bandera3=1;
                      }
              if(strob>=97 && strob<=100){
                  Modoss(strob);
                  bandera3=1;
              }
               Ascii(strob);
             }
}

//----------------------------------------enviar el PWM para cada color-------------
void Rojo(){
    while(bandera4 < 1){
              __bis_SR_register(CPUOFF + GIE); // modo bajo consumo
              ValRojo=getRX();            //obtine caracter
              if(ValRojo>=97 && ValRojo<=100){
                  Modoss(ValRojo);
                  bandera4=1;
              }
              if(ValRojo>=114 && ValRojo<=122){
                  Colores(ValRojo);
                  bandera4=1;
              }
             Ascii(ValRojo);
             }
}

void Verde(){
    while(bandera5 < 1){
              __bis_SR_register(CPUOFF + GIE); // modo bajo consumo
              ValVerde=getRX();            //obtine caracter
              if(ValVerde>=97 && ValVerde<=100){
                  Modoss(ValVerde);
                  bandera5=1;
              }
              if(ValVerde>=114 && ValVerde<=122){
                                Colores(ValVerde);
                                bandera5=1;
                            }
                 Ascii(ValVerde);

    }
}

void Azul(){
    while(bandera6 < 1){
              __bis_SR_register(CPUOFF + GIE); // modo bajo consumo
              ValAzul=getRX();            //obtine caracter
              if(ValAzul>=97 && ValAzul<=100){
                  Modoss(ValAzul);
                  bandera6=1;
              }
              if(ValAzul>=114 && ValAzul<=122){
                                Colores(ValAzul);
                                bandera6=1;
                            }
              Ascii(ValAzul);
           }
}
/*--------------------------------converter ascii a decimal-------------------------- */
void Ascii(asc){
    contador+=1;
                 if(contador<=4){
                  if(asc==46){
                    switch(contador){
                     case 2: enviar=Val1;
                       break;
                     case 3: enviar=Val1*10+Val2;
                       break;
                     case 4: enviar=Val1*100+Val2*10+Val3;
                     default: break;

                     }
                    UCB0CTL1 |= UCTR | UCTXSTT; //PARA INICIAR
                         while(UCB0CTL1 & UCTXSTT){
                             UCB0TXBUF = enviar;//0x0001; //01=encendido, 11=apagado
                         }
                  }
                  else{
                      switch(contador){
                      case 1: Val1=asc-48;
                        break;
                      case 2: Val2=asc-48;
                       break;
                      case 3: Val3=asc-48;
                      default: break;
                      }
                  }
                }
                 else{
                     enviar=255;
                     UCB0CTL1 |= UCTR | UCTXSTT; //PARA INICIAR
                          while(UCB0CTL1 & UCTXSTT){
                              UCB0TXBUF = enviar;//0x0001; //01=encendido, 11=apagado
                          }
                 }
}
