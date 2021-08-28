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
  static char claveCorrecta[6] = {'d', 'u', 'd', 'd', 'u', 'a'};
  static char claveIntroducida[6];
  static int digitosIngresados = 0;
  static int estado = 1;
  static int tiempo = 20;
  static uint32_t previousMillis = 0;
  unsigned long currentMillis = millis();
  const uint32_t interval = 1000;

  switch (estado) {
        //En estado 1 estamos en modo Config
        //U para aumentar el tiempo, no pasa mas de 60 segundos
        //D para disminuir el tiempo, no pasa menos de 10 segundos
        //A para armar la bomba y cambiar al estado 2
    case 1:{
      if (Serial.available() > 0){
        char letra = Serial.read();
        if((char) letra == 'u' && tiempo < 60){
          tiempo++;
          Serial.println(tiempo);
        } else if((char) letra == 'd' && tiempo >10){
          tiempo--;
          Serial.println(tiempo);
        } else if((char) letra == 'a'){
          estado = 2;
          previousMillis = millis();
          digitosIngresados = 0;
        }
      }
      break;
    }

    //Cuando cambia a estado 2 el tiempo empieza la cuenta atras
    case 2: {
      if(Serial.available() > 0){
        //Con esto vamos a poner la clave
        claveIntroducida[digitosIngresados] = Serial.read();
        digitosIngresados++;
        Serial.println("Digito Ingresado");

        if(digitosIngresados == 6){
          //Si la clave que ponemos ta buena la bomba se desactiva
          Serial.println("Revisando clave");
          if(clavesIguales(claveCorrecta, claveIntroducida)){
            Serial.println("Bomba Desactivada SIUUU");
            estado = 1; //se vuelve al estado 1 modo config
            tiempo = 20;//Si se desactiva el timer vuelve a 20segundos
          }
          digitosIngresados = 0;
        }
      }

      if((millis() - previousMillis) >= interval){
        previousMillis = millis();

        if (tiempo > 0){
          tiempo--;
          Serial.println(tiempo);
        } else{
          //Si el timer llega a 0 la bomba explota boom
          Serial.println("BOOOOOOOM *Sonidos de explosion* F");
          estado = 1; //Se vuelve al estado 1 modo config
          tiempo = 20;//Si explota el timepo vuelve a 20segundos
        }
      }
      break;
    }
    default:
      Serial.println("ERROR");
      break;
  }
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
