#include <ServoTimer2.h>  // the servo library


#include <VirtualWire.h>



#define RF_RX     3
#define PIN_SERVO 9
#define LED_PIN   4
#define DELAYS    2000
ServoTimer2 servo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  initPins();
  initRF();
  initServo();
  Serial.println("Setup");
}

void initPins(){
  pinMode(LED_PIN, OUTPUT);
}

void initServo(){
  servo.attach(PIN_SERVO);  
}

void initRF(){
  //vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);
  vw_set_rx_pin(RF_RX);
  vw_rx_start();
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t dataLength=VW_MAX_MESSAGE_LEN;

 
  if (vw_get_message(buf,&dataLength))
  {
    Serial.println("Algo ha llegado.");
    if(buf[0]=='1')
    {
      blinkLed(1);
      delay(DELAYS);
      blinkLed(0);
      moveServo();
      
    }
  }
  delay(1);
}
void blinkLed(int estado){
  //Encedemos el Led para saber que hay comunicacion
  digitalWrite(LED_PIN, (estado == 1 ? HIGH: LOW));
}

void moveServo()
{
  Serial.println("Moviendo...");   
  
  servo.write(750);           
  delay(1000);
  
  delay(1000);
  servo.write(3000);             
}

