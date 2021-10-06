//*****************************************************************************
// Universidad del Valle de Guatemala
// BE3015 - Electrónica Digital 2
// Gunther Dietmar Menzel - 19106
// LAB5
//*****************************************************************************

//*****************************************************************************
// Librerías
//*****************************************************************************
//Librería para la pantalla LCD
#include <Arduino.h>
#include <LiquidCrystal.h>

//*****************************************************************************
// Definición de pines
//*****************************************************************************
//Definición de pines para la pantalla LCD
#define d4 14
#define d5 27
#define d6 26
#define d7 25
#define en 12
#define rs 13
//Definición de pines para los potenciómetros
#define pot1 34
#define pot2 35

#define LEDROJA 18
#define LEDVERDE 19
#define LEDAZUL 5

#define frecuencia 60
#define resolucion 8
#define LEDROJACANAL 1
#define LEDVERDECANAL 2
#define LEDAZULCANAL 0

//*****************************************************************************
// Prototipos de función
//*****************************************************************************
//Varibale para el contador de 8 bits
void Contador(void);
void PWM(void);
void Potenciometros(void);

//*****************************************************************************
// Variables Globales
//*****************************************************************************
int ContadorBoton1 = 0; //Contador Boton en entero

// Create An LCD Object. Signals: [ RS, EN, D4, D5, D6, D7 ]
LiquidCrystal LCD(rs, en, d4, d5, d6, d7);

int Potenciometro1 = 0; 
int Potenciometro2= 0; 

