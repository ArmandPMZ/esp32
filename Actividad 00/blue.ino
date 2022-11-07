/* Con este programa se realiza una conexion bluetooth,
Con la ayuda de la aplicación serial bluetooth terminal
enviamos algunos comandos como por ejemplo: Reset(resetea el bluetooth del esp),
OnLED(enciende led integrado en el esp) y OffLED(apaga ese mismo led).
Intente poner el boton para encender la comunicación pero no lo logre.*/
#include <BluetoothSerial.h>
#define LED1_GPIO 4
#define boton_GPIO 2
#include <WiFi.h>
#include <HTTPClient.h>
#include <time.h>

const char WIFI_SSID[] = "TP-Link_312A";
const char WIFI_PASSWORD[] = "80794141";

//5678744912:AAGLHgtqgtTdiPBsfETNID0pdEWJZ3p6wBw

BluetoothSerial SerialBT;
void ConfigByBluetooth(void);

bool control= true;

void setup() {
  pinMode(LED1_GPIO, OUTPUT);
  Serial.begin(115200);
  Serial.println("Inicio de codigo");
  if(digitalRead(boton_GPIO)==0){
    delay(500); //antirrebotes
    if(digitalRead(boton_GPIO)==0){
      while(digitalRead(boton_GPIO)==0);
      Serial.println("Boton presionado");
      ConfigByBluetooth();
    }
  }
  else{
    Serial.println("Boton no presionado");
  }
  delay(1000);
}

void loop() {
}

void configwifi(void){
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED);{
  delay(500);
  Serial.print(".");
  }
  Serial.println("");
  Serial.print("conectado con la siguiente direccion IP:");
  Serial.println(WiFi.localIP());
}
void ConfigByBluetooth(void){
  //inicializamos bluetooth
  String message = "";
  String message2 = "";
  char incomingChar;
  char incomingChar2;
  bool BTHControl=true;
  SerialBT.begin("ESP32ARMAND");
  while(BTHControl==true){
    Serial.println("Bluetooth disponible");
    if(SerialBT.available()){
      char incomingChar = SerialBT.read();
      if (incomingChar != '\n'){
        message += String(incomingChar);
      }
      else{
        message = "";
      }
      Serial.write(incomingChar);
    }
    if (message == "Reset"){
      BTHControl =false;
      control = false;
    }
    if (message == "OnLED"){
      digitalWrite(LED1_GPIO, HIGH);
    }
    if (message == "OffLED"){
      digitalWrite(LED1_GPIO, LOW);
    }

    
    if (Serial.available()){
      char incomingChar2 = Serial.read();
      if (incomingChar2 != '\n'){
        message2 += String(incomingChar2);
      }
      else{
        message2 = "";
      }
      SerialBT.write(incomingChar2);
    }
  }
  SerialBT.end();
}
