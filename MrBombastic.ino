void setup(){
  
  Serial.begin(115200);
  
}

bool clavesIguales(char *claveRecibida,char *claveCorrecta){
  int ok = 0;

  for (int i = 0; i < 6; i++){
    if (claveRecibida[i] == claveCorrecta[i]){
      ok++;
    }
  }
  if (ok == 6){
    return true; //la clave recibida es igual a la clave almacenada
  }
  else{
    return false; //las claves no tan iguales
  }
}

//Tarea 1 que va a controlar toda la bomba, modo config y modo activada
void task1(){
  
}

//Codigo clasico para tecnica no bloqueante
void task2(){
  static const uint8_t ledPin = 3;
  static uint8_t ledState = LOW;
  static uint32_t interval = 500;
  static uint32_t previousMillis = 0;
  static bool taskInit = false;

  if (taskInit == false){
    pinMode(ledPin, OUTPUT);
    taskInit = true;
  }

  uint32_t currentMillis = millis();

  if ((currentMillis - previousMillis) >= interval) {
    previousMillis = currentMillis;

    if (ledState == LOW){
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    digitalWrite(ledPin, ledState);
  }
}

void loop(){
  task1();
  task2();
}
