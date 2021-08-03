// commHandler is a script that takes the serial command from the raspberry pi and sends the correct pulse along the correct pin to the bonsai software.

// includes
#include <CSV_Parser.h>

byte pins[] = {1,2,3,4,5,6,7,8};

int leverOutFoodPin      = pins[0];
int leverOutPartnerPin   = pins[1];
int leverOutNovelPin     = pins[2];
int leverPressFoodPin    = pins[3];
int leverPressPartnerPin = pins[4];
int leverPressNovelPin   = pins[5];
int enterPartnerPin      = pins[6];
int enterNovelPin        = pins[7];

String sdata = ""; // Initialize
byte pinCount = sizeof(pins)

void setup () {
    // Set the right pins for the right commands
    for (byte i = 0; i < pinCount; i++) {
        pinMode(pins[i], OUTPUT);
    }

    // setup the serial
    Serial.begin(9600)

    // Test the csv parsing
    CSV_Parser cp('commands.csv', /*format*/, "ss", /*has_header*/ false);
    cp.print();
}

void loop () {
    // Read the serial for the command
    byte ch;
    if (Serial.available()) {
        ch = Serial.read();
        sdata += (char)ch;

        if (ch == '\r') { // End of the command, full line has been recieved and is ready to go
            sdata.trim();

            // Re-initialize the variable
            sdata = "";
        }
    }
}

void commands (String command) {
    switch(command) {
        case "leverOutFood":
            // Food Lever is extended
            digitalWrite(leverOutFoodPin, HIGH);
            break;
        case "leverOutPartner":
            // Partner lever is extended
            digitalWrite(leverOutPartnerPin, HIGH);
            break;
        case "leverOutNovel":
            // Novel lever is extended
            digitalWrite(leverOutNovelPin, HIGH);
            break;
        case "leverPressFood":
            // Food lever is pressed
            digitalWrite(leverPressFoodPin, HIGH);
            break;
        case "leverPressPartner":
            // Partner lever is pressed
            digitalWrite(leverPressPartnerPin, HIGH);
            break;
        case "leverPressNovel":
            // Novel lever is pressed
            digitalWrite(leverPressNovelPin, HIGH);
            break;
        case "enterNovel":
            // Animal entered the novel chamber
            digitalWrite(enterNovelPin, HIGH);
            break;
        case "enterPartner";
            // Animal entered the partner chamber
            digitalWrite(enterPartnerPin, HIGH);
            break;
        default:
            break;
    }

    // Reset all the values to LOW
    for (byte i = 0; i < pinCount; i++) {
        digitalWrite(pins[i], LOW);
    }
}