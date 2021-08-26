// commHandler is a script that takes the serial command from the raspberry pi and sends the correct pulse along the correct pin to the bonsai software.

// includes
#include <CSV_Parser.h>
#include <SoftwareSerial.h>

byte pins[] = {13,10,9,4,5,6,7,11};

int leverOutFoodPin      = pins[0];
int leverOutPartnerPin   = pins[1];
int leverOutNovelPin     = pins[2];
int leverPressFoodPin    = pins[3];
int leverPressPartnerPin = pins[4];
int leverPressNovelPin   = pins[5];
int enterPartnerPin      = pins[6];
int enterNovelPin        = pins[7];
int nullPin              = pins[8];

String sdata = ""; // Initialize
byte pinCount = sizeof(pins);

// Software serial pins (rx, Tx)
int softRX = 2;
int softTX = 3;
SoftwareSerial myserial(softRX,softTX);

void setup () {
    // Set the right pins for the right commands
    for (byte i = 0; i < pinCount; i++) {
        pinMode(pins[i], OUTPUT);
    }

    // setup the serial
    Serial.begin(9600);
    Serial.println("Starting Serial Dialogue");

    // Setup the software serial port
    myserial.begin(9600);
    
    
    // Test the csv parsing
    //CSV_Parser cp('commands.csv', /*format*/, "ss", /*has_header*/, false);
    //cp.print();
}

void loop () {
    // Read the serial for the command
    byte ch;
    if (myserial.available()) {
        ch = myserial.read();
        sdata += (char)ch;

        if (ch == '\r') { // End of the command, full line has been recieved and is ready to go
            sdata.trim();

            // Send to the command handler
            commands(sdata);

            // Re-initialize the variable
            sdata = "";
        }
    }
}

void commands (String command) {
    if (command == "leverOutFood") {
      // Food Lever is extended
      digitalWrite(leverOutFoodPin, HIGH);
    }
    else if (command == "leverOutPartner") {
      // Partner lever is extended
      digitalWrite(leverOutPartnerPin, HIGH);
    }
    else if (command == "leverOutNovel") {
      // Novel lever is extended
      digitalWrite(leverOutNovelPin, HIGH);
    }
    else if (command == "leverPressFood") {
      // Food lever is pressed
      digitalWrite(leverPressFoodPin, HIGH);
    }
    else if (command == "leverPressPartner") {
      // Partner lever is pressed
      digitalWrite(leverPressPartnerPin, HIGH);
    }
    else if (command == "leverPressNovel") {
      // Novel lever is pressed
      digitalWrite(leverPressNovelPin, HIGH);
    }
    else if (command == "enterNovel") {
      // Animal entered the novel chamber
      digitalWrite(enterNovelPin, HIGH);
    }
    else if (command == "enterPartner") {
      // Animal entered the partner chamber
      digitalWrite(enterPartnerPin, HIGH);
    }
    else {
      digitalWrite(nullPin, HIGH);
    }

    // Reset all the values to LOW
    delay(500);
    for (byte i = 0; i < pinCount; i++) {
        digitalWrite(pins[i], LOW);
    }
}
