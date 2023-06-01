class examen{
  public:

    float distancia(int trigPin, int echoPin) {
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      float duracion = pulseIn(echoPin, HIGH);
      float distancia = duracion * 0.034 / 2; 
      Serial.print("Distancia: ");
      Serial.println(distancia);
      Serial.print(" cm");
      delay(300);
      return distancia;
    }
};

class uno: public examen{
  public:
    int led1Pin = 2; // Pines 
    int led2Pin = 3;
    int flag=0;
    int buttonPin = 4;

    int currentState = 0; // Variables para controlar el estado y el tiempo
    unsigned long previousMillis = 0;
    unsigned long interval = 1000;

    void crear1() {
      pinMode(led1Pin, OUTPUT); // Configurar los pines de los LEDs y el botón
      pinMode(led2Pin, OUTPUT);
      pinMode(buttonPin, INPUT);
      
      if (digitalRead(buttonPin)== LOW) { // Cambiar de estado si se detecta un cambio en el botón
        currentState++;
        if (currentState > 2) {
          currentState = 0;
        }
        delay(500); // Retardo para evitar lecturas múltiples rápidas del botón
      }

      switch (currentState) { // Realizar las acciones según el estado actual
        case 0:
          interval = 1000;
          if (millis() - previousMillis >= interval) {
            flag++;
            if(flag%2!=0){
            digitalWrite(led1Pin, HIGH);
            digitalWrite(led2Pin, LOW);
            }else{
            digitalWrite(led1Pin, LOW);
            digitalWrite(led2Pin, HIGH);
            }
            if(flag==100){
              flag=0;
            }
          previousMillis = millis();
          }
          break;
        case 1:
          interval = 2000;
          if (millis() - previousMillis >= interval) {
            flag++;
            if(flag%2!=0){
            digitalWrite(led1Pin, HIGH);
            digitalWrite(led2Pin, HIGH);
            }else{
            digitalWrite(led1Pin, LOW);
            digitalWrite(led2Pin, LOW);
            }
            if(flag==100){
            flag=0;
            }
          previousMillis = millis();
          }
          break;
        case 2:
          digitalWrite(led1Pin, LOW);
          digitalWrite(led2Pin, LOW);
          break;
      }
    }
};

class cinco: public examen{
  public: 
    int trigPin = 6;
    int echoPin = 7;
    int numLeds = 5; 
    int ledPins[5] = {8, 9, 10, 11, 12}; 
    int dist = 0;

    void write(int led, int temp){
      digitalWrite(led, HIGH);
      delay(temp);
      digitalWrite(led, LOW);
    }

    void secuencia(int temp){
      write(ledPins[0], temp);
      write(ledPins[1], temp);
      write(ledPins[2], temp);
      write(ledPins[3], temp);
      write(ledPins[4], temp);
    }

    void crear2(){
      for (int i = 0; i < numLeds; i++) {
        pinMode(ledPins[i], OUTPUT);
      }
      pinMode(trigPin, OUTPUT);
      pinMode(echoPin, INPUT);
      Serial.print(echoPin);
      dist = distancia(trigPin, echoPin);

      if (dist > 200){
        secuencia(1500);
      } else if (dist > 100){
        secuencia(1000);
      } else if (dist <= 100){
        secuencia(500);       
      } else {
        secuencia(1500);
      }
    }

};
void setup() {
Serial.begin (9600);
}

void loop() {
  uno leds;
  cinco secu;
  leds.crear1();
  secu.crear2();
}
