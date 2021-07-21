// commHandler is a script that takes the serial command from the raspberry pi and sends the correct pulse along the correct pin to the bonsai software.

int leverOutFoodPin = 1;
int leverOutPartnerPin = 2;
int leverOutNovelPin = 3;
int leverPressFoodPin = 4;
int leverPressPartnerPin = 5;
int leverPressNovelPin = 6;
int enterPartnerPin = 7;
int enterNovelPin = 8;

void setup () {
    // Set the right pins for the right commands
    pinMode(leverOutFoodPin, OUTPUT);
    pinMode(leverOutPartnerPin, OUTPUT);
    pinMode(leverOutNovelPin, OUTPUT);
    pinMode(leverPressFoodPin, OUTPUT);
    pinMode(leverPressNovelPin, OUTPUT);
    pinMode(leverPressPartnerPin, OUTPUT);
    pinMode(enterNovelPin, OUTPUT);
    pinMode(enterPartnerPin, OUTPUT);

    // setup the serial
    Serial.begin(9600)
}

void loop () {
    // Read the serial for the command

    // Depending on the command send out the correct signal

}