#include <LiquidCrystal.h>
LiquidCrystal lcd(A4, A5, A3, A2, A1, A0);                          // Variable donde se almacena la letra
boolean prendido = false;           // Estado LED la primera vez, apagado
String password = "1234";
int redPin = 10;
int greenPin = 11;
int buzzer = 12;
int position = 0;
int total = 0;
int wrong = 0;
int val;
char s;
char br;
float mv;
float temp;
boolean bandera = true;
//char pressed;
//String key;

void setup() {
  // put your setup code here, to run once:
  //Inicializamos la comunicacion serial a 9600bps
  pinMode(A6, INPUT);                              //Asignamos el pin A1 como entrada (Sensor de Temperatura)
  pinMode(6, OUTPUT);                              //Asignamos el pin 6 como salida (Led Verde)
  pinMode(7, OUTPUT);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin (9600);


}

void loop() {
  // put your main code here, to run repeatedly:
  s = Serial.read();
  switch (s) {

    case 'a':
eti0:
      br = Serial.read();
      if (br == 's')break;

      val = analogRead (A6);                           //Realiza la lectura del pin A1 (Sensor) y el valor lo guarda en la variable val
      mv = (val / 1024.0) * 5000;                //Declaramos variable de tipo float y operamos para obtener el resultado en celsius (grados centigrados)
      temp = mv / 10;                            //Declaramos variable de tipo float y operamos para obtener el resultado en celsius (grados centigrados)



      if (temp > 37.6) {                               //Si temp es mayor que 37.6
        Serial.print ("TEMPERATURA CORPORAL ALTA = ");                 //Imprimimos en pantalla TEMPERATURE =
        Serial.print (temp);                             //Imprimimos el valor de la variable temp
        Serial.print ("*C");                             //Imprimimos en pantalla *C
        Serial.println ();                               //Salto de linea
        digitalWrite(6, LOW);                        //Apaga el Led Verde
        digitalWrite(7, HIGH);                       //Prende el Led Rojo
      }
      else {
        Serial.print ("TEMPERATURA CORPORAL BAJA = ");                 //Imprimimos en pantalla TEMPERATURE =
        Serial.print (temp);                             //Imprimimos el valor de la variable temp
        Serial.print ("*C");                             //Imprimimos en pantalla *C
        Serial.println ();                               //Salto de linea//Si temp NO es mayor que 37.6
        digitalWrite(6, HIGH);                         //Prende el Led Verde
        digitalWrite(7, LOW);                          //Apaga el Led Rojo
      }

      delay(1000);


      goto eti0;
      break;

    case 'b':

      br = Serial.read();
      if (br == 's')break;
      
      lcd.begin(16, 2);
      lcd.setCursor(0, 0);
      lcd.println("*BIENVENIDO!!*");
      delay(3000);
      lcd.setCursor(0, 0);
      lcd.println("*INTRODUCE*");
      lcd.setCursor(0, 1);
      lcd.println("*EL CODIGO*");
      delay(3000);
      lcd.setCursor(0, 0);
      lcd.println("*PARA ABRIR*");
      lcd.setCursor(0, 1);
      lcd.println("*LA PUERTA!!*");
      delay(3000);
      lcd.clear();
      lcd.clear();
      lcd.print(" Password: ");
      delay(100);


eti1:
      char pressed = Serial.read();
      String key[3];

      if (pressed)
      {
        lcd.clear();
        lcd.print(" Password: ");
        lcd.setCursor(position, 2);
        lcd.print(pressed);
        delay(500);

        if (pressed == '*' || pressed == '#')
        {
          position = 0;
          setLocked(true);
          lcd.clear();
        }

        else if (pressed == password[position])
        {
          key[position] = pressed;
          position++;
        }

        else if (pressed != password[position] )
        {
          wrong++;
          position ++;
        }

        if (position == 3) {
          if ( wrong > 0)
          {
            total++;
            wrong = 0;
            position = 0;
            lcd.clear();
            lcd.setCursor(0, 2);
            lcd.print("    Acceso Denegado!     ");
            delay(1000);
            setLocked(true);
          }

          else if (position == 3 && wrong == 0)
          {
            position = 0;
            wrong = 0;
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("      Bienvenido!     ");
            lcd.setCursor(0, 1);
            lcd.print(" Puerta Abierta");
            delay(2000);
            setLocked(false);
          }

          if (total == 3)
          {
            total = 0;
            buzzer_beep();
            delay(500);
          }

        }

      }
      goto eti1;
        break;
      default:
      break;

          
  }
}

void setLocked(int locked)
{
  if (locked)
  {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    delay(1000);
  }
  else
  {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    delay(2000);
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
  }
}
void buzzer_beep()
{
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("    PELIGRO  !!!!   ");
  lcd.setCursor(0, 2);
  lcd.print("   ACCESO DENEGADO");
  for (int i = 0; i < 10; i++) {
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
    delay(1000);
  }
}
