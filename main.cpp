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
//Definicón de pines para las LEDs
#define LEDROJA 18
#define LEDVERDE 19
#define LEDAZUL 5
//Definición de la frecuencia, resolución y canal de las LEDs para el PWM
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
//Variable para el PWM
void PWM(void);
//Variable para los potenciómetros
void Potenciometros(void);

//*****************************************************************************
// Variables Globales
//*****************************************************************************
int ContadorBoton1 = 0; //Contador Boton en entero

// Create An LCD Object. Signals: [ RS, EN, D4, D5, D6, D7 ]
LiquidCrystal LCD(rs, en, d4, d5, d6, d7);

int Potenciometro1 = 0; //Potenciómetro 1 en entero
int Potenciometro2= 0;  //Potenciómetro 2 en entero

String t=""; //cadena de caracteres

int DCR = 0; //Entero DCrojo
int DCV = 0; //Entero DCverde
int DCA = 0; //Entero Dazul

long LastTime; 
long LastTime2;
//Tiempo de muestra 
int SampleTime1 = 250;
int SampleTime2 = 1000;

//*****************************************************************************
// Configuración
//*****************************************************************************
void setup() {
  Serial.begin(115200); //Configuración serial
  //LCD_Init(rs, en, d4, d5, d6, d7);
  // Initialize The LCD. Parameters: [ Columns, Rows ]
  LCD.begin(16, 2); //Pantalla LCD 16*2
  // Clears The LCD Display
  
  PWM();
  //Definiendo los LEDs como salidas
  pinMode(LEDROJA, OUTPUT);
  pinMode(LEDVERDE, OUTPUT);
  pinMode(LEDAZUL, OUTPUT);
  //Estados de los LEDs
  digitalWrite(LEDROJA, 0);
  digitalWrite(LEDVERDE, 0);
  digitalWrite(LEDAZUL, 0);
  
  LastTime= millis();
  LastTime2= millis();
  
}

//*****************************************************************************
// Loop Principal
//*****************************************************************************
void loop() {
  //Delay para los potenciómetros
  if (millis()-LastTime2 >= SampleTime2){
    Potenciometros();
    LastTime2 = millis();
  }

  if (millis()-LastTime >= SampleTime1){
    
    //Asignando lo que tiene que decir la pantalla LCD
    LCD.clear();
    LCD.print("Rojo");
    LCD.print(" ");
    LCD.print("Verde");
    LCD.print(" ");
    LCD.print("Azul");
    //Posicion del LCD cursor
    LCD.setCursor(1,1);
    LCD.print(Potenciometro1);
    LCD.print(' '  );
    LCD.print(Potenciometro2);
    LCD.print("     ");
    LCD.print(ContadorBoton1);
    
    
    LastTime=millis();
  }
   //Iniciando contador
   Contador();
  if(t != NULL){
    Serial.print("t dentro del loop ");
    Serial.print(t);
  
      }
      
  if (t=="-"){
    Serial.print("Entro al menos");
    if (ContadorBoton1>0){
      ContadorBoton1 = ContadorBoton1-1;

    }

    else if(ContadorBoton1 <=0){
      ContadorBoton1=255;

    }
    //Contador de 8 bits
    ledcWrite(LEDAZULCANAL,ContadorBoton1);
    Serial.print("Contador: ");
    Serial.print(ContadorBoton1);
    t="";

    }

     
  if (t=="+"){
        Serial.print("Entro al mas");
    if (ContadorBoton1<255){
      ContadorBoton1 = ContadorBoton1+1;

    }

    else if(ContadorBoton1 >=255){
      ContadorBoton1=0;

    }
    //Contador de 8 bits
    ledcWrite(LEDAZULCANAL,ContadorBoton1);
    Serial.print("Contador: ");
    Serial.print(ContadorBoton1);
    t="";

  }  
}
//Iniciando los parámetros en los que tiene que trabajar el contador de 8 bits
void Contador(void){
  if(Serial.available()>0 ){

    t =Serial.readStringUntil('\n');

    Serial.print("El mensaje dice que: ");
    Serial.println(t);

  }

}

//Función PWM
void PWM(void){
  ledcSetup(LEDROJACANAL, frecuencia,resolucion);
  ledcAttachPin(LEDROJA, LEDROJACANAL);

  ledcSetup(LEDVERDECANAL, frecuencia,resolucion);
  ledcAttachPin(LEDVERDE, LEDVERDECANAL);

  ledcSetup(LEDAZULCANAL, frecuencia,resolucion);
  ledcAttachPin(LEDAZUL, LEDAZULCANAL);

}

//Función de los Potenciómetros
void Potenciometros(void ){
  Potenciometro1=analogReadMilliVolts(pot1);
  Potenciometro2=analogReadMilliVolts(pot2);

  Potenciometro1 = map(Potenciometro1, 0, 3300, 0, 255);
  Potenciometro2= map(Potenciometro2, 0, 3300, 0, 255);

  ledcWrite(LEDROJACANAL, Potenciometro1);
  ledcWrite(LEDVERDECANAL, Potenciometro2);
  //Asignando lo que tiene que decir la LCD
  Serial.print("Pot1:");
  Serial.println(Potenciometro1);
  Serial.print("Pot2:");
  Serial.println(Potenciometro2);
  
}
  //FIN DEL CÓDIGO