//lo primero es incluir la libreria del LCD
#include <LiquidCrystal.h>

//Indicamos cuales seran los pines del LCD a utilizar
LiquidCrystal lcd(8, 13, 9, 4, 5, 6, 7);

int lcd_key     = 0;
int adc_key_in  = 0;

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnNONE   5

int segundo=0;    //variable del segundo
int minuto=0;     //variable del minuto
int hora=0;       //variable de la hora

int pausa=3;  //pausa=0 reloj funicona, pausa =1 reloj pausado

int read_LCD_buttons(){               // read the buttons
  adc_key_in = analogRead(0);       // read the value from the sensor 
  
  if (adc_key_in > 1000) return btnNONE; 
  // For V1.0 comment the other threshold and use the one below: (FUNCIONA)
  if (adc_key_in < 50)   return btnRIGHT;
  if (adc_key_in < 195)  return btnUP;
  if (adc_key_in < 380)  return btnDOWN;    

    return btnNONE;                // when all others fail, return this.
}

void setup() 
{
  lcd.begin(16, 2);  //inicializamos LCD como una de 16x2
  lcd.setCursor(0,0);
}

void loop() 
{
  lcd.setCursor(0,0); //nos posicionamos en la pantalla      
  lcd.print("Tiempo= ");  //imprimimos el texto deseado
  lcd.print(hora);  //imprimimos la variable hora
  lcd.print(":"); //imprimimo lso dos puntos
  lcd.print(minuto);  //imprimimos el valor de la variable
  lcd.print(":"); //imprimimo dos puntos
  lcd.print(segundo); //imprimimos el valor de la variable

  lcd.setCursor(0,1);
  lcd_key = read_LCD_buttons(); // read the buttons
  
  switch (lcd_key){
    case btnUP:{//cuenta
      lcd.print("pausar DOWN             ");  //  push button "UP" and show the word on the screen
      pausa =0;
      break;
      }
    case btnDOWN:{//parar
      lcd.print("Cont UP,rst RIGTH  ");  //  push button "DOWN" and show the word on the screen
      pausa =1;
      break;
      }
    case btnRIGHT:{//reiniciar
      segundo=0;    //variable del segundo
      minuto=0;     //variable del minuto
      hora=0;
      pausa =3;
      lcd.setCursor(0,0);
      lcd.print("                  ");
      lcd.setCursor(0,1);
      lcd.print("                  ");
      }
   }
  if(pausa == 3){
    lcd.print("iniciar UP    ");  //  push button "UP" and show the word on the screen
    }
  if(pausa==0)  //el reloj tiene que contar
  { 
    segundo++;
    delay(1000);
    
    if(segundo>59)
    {
      segundo=0;
      minuto++;
      if(minuto>59)
      {
        minuto=0;
        hora++;
        if(hora>23)
          hora=0;
      }
    }
  }
}
