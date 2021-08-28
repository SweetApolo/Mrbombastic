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
  
}

void loop(){
  task1();
  task2();
}
