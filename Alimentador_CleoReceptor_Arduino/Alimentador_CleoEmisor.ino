//#include <Time.h>

//------------------------------------------- LIBRERIAS ------------------------------------------------
//---- Librerias de Red -----

//#include <EthernetClient.h>
#include <SPI.h>
#include <Ethernet.h>
//#include <EthernetServer.h>

//----- Libreria RF (https://www.minitronica.com/arduino-radiofrecuencia-433mhz-virtualwire/)
#include <VirtualWire.h>



//---- Librerias Servo

//#include <Servo.h>

//--------------------------

//---- Librerias Tarjeta SD

//#include <SD.h>


//------------------------

//------------------------------------------------------------------------------------------------------------


//-----Definiciones Globales
#define PORT 9090
#define LED_COM 2 
#define RF_TX   39 //PIN por el que envia el RF
#define DELAYS 2000
byte mac[] = { 0xFA, 0xBA, 0xDA, 0xFA, 0xBA, 0xDA }; //Mac del adaptador Ethernet.
IPAddress ip(192, 168, 1, 235); //IP asignada al mismo
IPAddress gateway(192,168,1, 1);
IPAddress subnet(255, 255, 255, 0);
EthernetServer server(PORT);


//Servo myservo;
//#define NOMFILE "feedCleo.txt"

void setup() {

  Serial.begin(9600);
  while (!Serial) {; }
  initPins();
  initNet();
  initRF();//Antes de llamar a esta funcion hay que establecer todos los PINS.
  
}

//Funcion para inicializar la informacion de la interfaz de Red.
void initNet() 
{
  Ethernet.begin(mac, ip);
  
  server.begin();
  Serial.println(Ethernet.localIP());
  Serial.println("\n");
}

void initPins(){
  pinMode(LED_COM, OUTPUT);
}

void initRF(){
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);
  vw_set_tx_pin(RF_TX);
  //vw_rx_start();   
}

void loop() {

  //Esperamos a que venga algun cliente  
  
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    boolean currentLineIsBlank = true;
    while (client.connected()) 
    {
      while (client.available()>0){
        char c = client.read();
        Serial.print(c);
      }
      construirRespuestaHTTP(client);
      delay(10);
      client.stop();
      blinkLed(1);
      char chArray[] = {'1', '2'};
      sendRFMessage(chArray);
      delay(DELAYS);
      blinkLed(0);
      //Mostrar Respuesta
      
      break;
      
    }

    Serial.println("Cliente Desconectado.");
    Ethernet.maintain();
    
  }
  
}

void construirRespuestaHTTP(EthernetClient client){
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");  
  client.println();
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("Hecho!");
  
  client.println("</html>");
}
void blinkLed(int estado){
  //Encedemos el Led para saber que hay comunicacion
  digitalWrite(LED_COM, (estado == 1 ? HIGH: LOW));
}

void sendRFMessage(char value[]){
  vw_send((uint8_t *)value, strlen(value)); //Envia el mensaje
  vw_wait_tx(); //Espera hasta que se envien los datos
  delay(200);
  //La siguiente implementacion no la soporta la libreria que tengo
  /*if (vw_tx_active()){
    Serial.write("Enviado!!");
  }
  else{
    Serial.write("NO SE HA ENVIADO!!!!");
  }
  */
  Serial.println("Alimentando a Cleo");
}