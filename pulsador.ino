// Declaramos el pin al que estará conectado el pulsador
int pinPulsador = 4;
// Declaramos el pin al que estará conectado el led
int pinLed = 2; // debe ser un pin PWM (3, 5, 6, 9, 10, o 11 en un Arduino Uno)
int brillo = 0; // nivel de brillo actual del LED
unsigned long ultimoIncremento = 0; // momento en que el brillo fue incrementado por última vez

void setup()
{
  // Inicializamos la comunicación serial a 9600 baudios
  Serial.begin(9600);

  // Determinamos que el pin del pulsador será para recibir 
  pinMode(pinPulsador, INPUT);
  // Determinamos que el pin del led será para salir
  pinMode(pinLed, OUTPUT);
}

void loop()
{
  // Si la señal del pulsador es activa incrementamos el brillo del led
  if (digitalRead(pinPulsador) == HIGH) {
    if (millis() - ultimoIncremento > 10000) { // si han pasado 10 segundos o más
      if (brillo > 0) { // si el LED está encendido
        brillo = 0; // apagamos el led
        Serial.println("LED Apagado");
      } else { // si el LED está apagado
        brillo += 85; // incrementamos en 33% (255/3=85)
        if (brillo > 255) {
          brillo = 255; // nos aseguramos de que no supere el máximo
        }
        ultimoIncremento = millis(); // actualizamos el momento del último incremento
        Serial.print("Incrementando brillo a ");
        Serial.println(brillo);
      }
    } else { // si no han pasado 10 segundos
      brillo += 85; // incrementamos en 33% (255/3=85)
      if (brillo > 255) {
        brillo = 255; // nos aseguramos de que no supere el máximo
      }
      ultimoIncremento = millis(); // actualizamos el momento del último incremento
      Serial.print("Incrementando brillo a ");
      Serial.println(brillo);
    }
    analogWrite(pinLed, brillo); // establecemos el nuevo nivel de brillo
    delay(500); // espera para evitar rebotes del interruptor
  }
}
