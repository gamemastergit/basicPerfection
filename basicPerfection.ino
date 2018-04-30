#define MY_DEBUG 

// Enable and select radio type attached
#define MY_RADIO_NRF24
//#define MY_RADIO_RFM69

#include <SPI.h>
#include <MySensors.h>
#include <Bounce2.h>
#define MY_NODE_ID 1
#define RELAY_PIN 8  // Arduino Digital I/O pin number for first relay (second on pin+1 etc)
#define NUMBER_OF_RELAYS 1 // Total number of attached relays
#define RELAY_ON 1  // GPIO value to write to turn on attached relay
#define RELAY_OFF 0 // GPIO value to write to turn off attached relay

// Change to V_LIGHT if you use S_LIGHT in presentation below
MyMessage msg1(1,V_TRIPPED);
MyMessage msg2(2,V_TRIPPED);
MyMessage msg3(3,V_TRIPPED);
MyMessage msg4(4,V_TRIPPED);
MyMessage msg5(5,V_TRIPPED);
MyMessage msg6(6,V_TRIPPED);
MyMessage msg7(7,V_TRIPPED);
MyMessage msg8(8,V_STATUS);
MyMessage msg9(7,V_TRIPPED);


MyMessage mArray[7]{msg1, msg2, msg3, msg4, msg5, msg6, msg7};

void setup()  
{  


  // Setup the button
  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);
  pinMode(6,INPUT_PULLUP);
  pinMode(7,INPUT_PULLUP);
  pinMode(8,INPUT_PULLUP);
  pinMode(A0,INPUT_PULLUP);
  pinMode(A1,INPUT_PULLUP);
  pinMode(3, OUTPUT);
  digitalWrite(RELAY_PIN, 0); 
  // After setting up the button, setup debouncer


}

void presentation() {
  // Register binary input sensor to gw (they will be created as child devices)
  // You can use S_DOOR, S_MOTION or S_LIGHT here depending on your usage. 
  // If S_LIGHT is used, remember to update variable type you send in. See "msg" above.
  sendSketchInfo("Perfection", "1.0");
  delay(150);
  present(1, S_DOOR, "Col 1");
  delay(150);
  present(2, S_DOOR, "Col 2");
  delay(150);  
  present(3, S_DOOR, "Col 3");
  delay(150);
  present(4, S_DOOR, "Col 4");
  delay(150);
  present(5, S_DOOR, "Col 5"); 
  delay(150);
  present(6, S_DOOR, "Col 6"); 
  delay(150);
  present(7, S_DOOR, "Col 7"); 
  delay(150);
  present(8, S_BINARY, "Relay");
  delay(150);
  present(0, S_DOOR, "Start"); 
  delay(150);

}
uint8_t pins[8]{4,5,6,7,8,A0,A1,A2};
int old[8]{0,0,0,0,0,0,0,0};
//  Check if digital input has changed and send in new value
void loop() 
{
  for(int x = 0; x < 8; x++){
  int val = digitalRead(pins[x]);
  if (val !=old[x]) {
    Serial.print("TRIGGER");
     // Send in the new value
     send(mArray[x].set(!val));
     old[x]=val;
  }
  }
}

void receive(const MyMessage &message)
{
    // We only expect one type of message from controller. But we better check anyway.
    if (message.type==V_STATUS) {
        // Change relay state
        digitalWrite(3, message.getBool()?RELAY_ON:RELAY_OFF);
        // Store state in eeprom
        // Write some debug info
        Serial.print("Incoming change for sensor:");
        Serial.print(message.sensor);
        Serial.print(", New status: ");
        Serial.println(message.getBool());
    }
}
