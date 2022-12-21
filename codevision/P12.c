/*******************************************************
This program was created by the CodeWizardAVR V3.49a 
Automatic Program Generator
© Copyright 1998-2022 Pavel Haiduc, HP InfoTech S.R.L.
http://www.hpinfotech.ro

Project : 
Version : 
Date    : 18/12/2022
Author  : 
Company : 
Comments: 


Chip type               : ATmega8535
Program type            : Application
AVR Core Clock frequency: 1.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 128
*******************************************************/

// I/O Registers definitions
#include <mega8535.h>
#include <delay.h>
/*botones de direcciones*/
#define rev PIND.0
#define izq PIND.2
#define der PIND.4
#define adelante PIND.6
/*botones de control*/
#define go PINB.0
#define pause PINB.3
#define clr PINB.6
/*estados de los botones de direcciones*/
bit reva, revp=1;
bit izqa, izqp=1;
bit dera, derp=1;
bit adea, adep=1;
/*estados de los botones de control*/
bit goa, gop=1;
bit pa, pp=1;
bit ca, cp=1;
/*monitoreo de cambios de estado*/
void checarAdelante();
void checarAtras();
void checarIzq();
void checarDer();

void checarGo();
void checarPause();
void checarClr();
unsigned char checarEspacio();

/*{adelante, atras, izquierda, derecha}*/
const char motor[4]={0x11, 0x22, 0x21, 0x12}; //contiene las direcciones del motor
const char disp7seg[4]={0x23, 0x1c, 0x39, 0x0f}; //contiene despliegue de direcciones
const char tam = 40;
unsigned char memoria[tam]; //arreglo donde se guardan las instrucciones
unsigned char i=0; //contador del arreglo
unsigned char j=0; //recorrido del arreglo

// Declare your global variables here

void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRA=(1<<DDA7) | (1<<DDA6) | (1<<DDA5) | (1<<DDA4) | (1<<DDA3) | (1<<DDA2) | (1<<DDA1) | (1<<DDA0);
// State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0 
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=P Bit6=P Bit5=P Bit4=P Bit3=P Bit2=P Bit1=P Bit0=P 
PORTB=(1<<PORTB7) | (1<<PORTB6) | (1<<PORTB5) | (1<<PORTB4) | (1<<PORTB3) | (1<<PORTB2) | (1<<PORTB1) | (1<<PORTB0);

// Port C initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRC=(1<<DDC7) | (1<<DDC6) | (1<<DDC5) | (1<<DDC4) | (1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
// State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0 
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=P Bit6=P Bit5=P Bit4=P Bit3=P Bit2=P Bit1=P Bit0=P 
PORTD=(1<<PORTD7) | (1<<PORTD6) | (1<<PORTD5) | (1<<PORTD4) | (1<<PORTD3) | (1<<PORTD2) | (1<<PORTD1) | (1<<PORTD0);

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=0xFF
// OC0 output: Disconnected
TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (0<<CS02) | (0<<CS01) | (0<<CS00);
TCNT0=0x00;
OCR0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=0xFFFF
// OC1A output: Disconnected
// OC1B output: Disconnected
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (0<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=0xFF
// OC2 output: Disconnected
ASSR=0<<AS2;
TCCR2=(0<<WGM20) | (0<<COM21) | (0<<COM20) | (0<<WGM21) | (0<<CS22) | (0<<CS21) | (0<<CS20);
TCNT2=0x00;
OCR2=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
MCUCSR=(0<<ISC2);

// USART initialization
// USART disabled
UCSRB=(0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (0<<RXEN) | (0<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);

// Analog Comparator initialization
// Analog Comparator: Off
// The Analog Comparator's positive input is
// connected to the AIN0 pin
// The Analog Comparator's negative input is
// connected to the AIN1 pin
ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);
SFIOR=(0<<ACME);

// ADC initialization
// ADC disabled
ADCSRA=(0<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);

// SPI initialization
// SPI disabled
SPCR=(0<<SPIE) | (0<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);

// TWI initialization
// TWI disabled
TWCR=(0<<TWEA) | (0<<TWSTA) | (0<<TWSTO) | (0<<TWEN) | (0<<TWIE);

while (1)
      {
      // Place your code here
        checarAdelante();
        checarAtras();
        checarIzq();
        checarDer();
        checarGo();
        checarPause();
        checarClr();
      }
}

void checarAdelante(){ //checa si se se presiona el boton incrementar
	if( checarEspacio() ){
        if(adelante==0) adea=0; //si se presiona el btn el estado act es presionado
        else adea=1; //si no, el estado tiene el valor de suleto
    	
        if( adea==0 && adep==1 ) //si estaba suelto y se presiona
        {
            PORTA=disp7seg[0]; //despliegue asociado
            memoria[i]=0; //posicion de la configuracion del motor asociada
            i++; //se mueve el indice de la memoria
            delay_ms(25); //retardo antirebotes
        }
        if( adea==1 && adep==0 ) //si si estaba presionado y se suelta
            delay_ms(25); //retardo antirebotes
        adep=adea; //el estado actual se convierte en el estado pasado para la sig iteracion
    }
    else PORTA = 0x79; //E (error)
}

void checarAtras(){ //checa si se se presiona el boton incrementar
	if( checarEspacio() ){
        if(rev==0) reva=0; //si se presiona el btn el estado act es presionado
        else reva=1; //si no, el estado tiene el valor de suleto
    	
        if( reva==0 && revp==1 ) //si estaba suelto y se presiona
        {
            PORTA=disp7seg[1]; //despliegue asociado
            memoria[i]=1; //posicion de la configuracion del motor asociada
            i++; //se mueve el indice de la memoria
            delay_ms(25); //retardo antirebotes
        }
        if( reva==1 && revp==0 ) //si si estaba presionado y se suelta
            delay_ms(25); //retardo antirebotes
        revp=reva; //el estado actual se convierte en el estado pasado para la sig iteracion
    }
    else PORTA = 0x79; //E (error)
}

void checarIzq(){ //checa si se se presiona el boton incrementar
	if( checarEspacio() ){
        if(izq==0) izqa=0; //si se presiona el btn el estado act es presionado
        else izqa=1; //si no, el estado tiene el valor de suleto
    	
        if( izqa==0 && izqp==1 ) //si estaba suelto y se presiona
        {
            PORTA=disp7seg[2]; //despliegue asociado
            memoria[i]=2; //posicion de la configuracion del motor asociada
            i++; //se mueve el indice de la memoria
            delay_ms(25); //retardo antirebotes
        }
        if( izqa==1 && izqp==0 ) //si si estaba presionado y se suelta
            delay_ms(25); //retardo antirebotes
        izqp=izqa; //el estado actual se convierte en el estado pasado para la sig iteracion
    }
    else PORTA = 0x79; //E (error)
}

void checarDer(){ //checa si se se presiona el boton incrementar
	if( checarEspacio() ){
        if(der==0) dera=0; //si se presiona el btn el estado act es presionado
        else dera=1; //si no, el estado tiene el valor de suleto
    	
        if( dera==0 && derp==1 ) //si estaba suelto y se presiona
        {
            PORTA=disp7seg[3]; //despliegue asociado
            memoria[i]=3; //posicion de la configuracion del motor asociada
            i++; //se mueve el indice de la memoria
            delay_ms(25); //retardo antirebotes
        }
        if( dera==1 && derp==0 ) //si si estaba presionado y se suelta
            delay_ms(25); //retardo antirebotes
        derp=dera; //el estado actual se convierte en el estado pasado para la sig iteracion
    }
    else PORTA = 0x79; //E (error)
}

void checarGo(){ //checa si se se presiona el boton incrementar
    if(go==0) goa=0; //si se presiona el btn el estado act es presionado
    else goa=1; //si no, el estado tiene el valor de suleto
    	
    if( goa==0 && gop==1 ) //si estaba suelto y se presiona
    {
        delay_ms(25); //retardo antirebotes
    }
    if( goa==1 && gop==0 ) //si si estaba presionado y se suelta 
    {   
        for(;j<i;j++) 
        {
            PORTA=disp7seg[memoria[j]]; //despliegue asociado  
            PORTC=motor[memoria[j]];    //movimiento asociado
            delay_ms(1000); //retardo para que se mueva la abejita :3
            PORTC=0x00; //se detiene el motor  
            PORTA=0x00; //se apaga el display
            
            checarPause(); 
            checarClr();
        } 
        if(j==i) PORTA=0x40;
        delay_ms(25); 
    }
    gop=goa; //el estado actual se convierte en el estado pasado para la sig iteracion
}

void checarPause(){
    if (pause == 0){
        pa=0;
    }
    else pa=1;
    
    if( pa==0 && pp==1){
        while(1){
            if(go==0){
                gop=1;
                break;
            }       
            if(clr==0){
                cp=1;
                break;
            }
        }    
        //delay_ms(25);
    }
}

void checarClr(){
    if( clr == 0 ) ca=0;
    else ca=1;
    
    if( ca==0 && cp ==1){
        for(i=0; i<20; i++){
            memoria[i]=0;
        }
        i=0;
        j=0;
        PORTA=0x40;
        delay_ms(25);
    }
    if( ca==1 && cp==0) delay_ms(25);
    cp=ca;
}

unsigned char checarEspacio(){
    if( i>=tam ) return 0;      
    else return 1;
}