// Include necessary libraries.
#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

// Define the pins used for the RFID module, LEDs, etc.
#define SS_PIN 21
#define RST_PIN 2
#define LED_rfid 5
#define LED 22

// Create an instance of the MFRC522 object using the defined SS and RST pins.
MFRC522 rfid(SS_PIN, RST_PIN);

// Function to check if the UID of the scanned card is authorized.
bool access() {
	// Define the authorized UID of the card.
	byte authorizedUID[4] = {0x84, 0x16, 0x6C, 0xCB};

	// Check if the scanned card's UID matches the authorized UID.
	if ( 	rfid.uid.uidByte[0] == authorizedUID[0] &&
		rfid.uid.uidByte[1] == authorizedUID[1] &&
		rfid.uid.uidByte[2] == authorizedUID[2] &&
		rfid.uid.uidByte[3] == authorizedUID[3]) {
	return 1;
	}
	else return 0;
}

// Function to read the RFID tag and check for authorization.
void taskRFID(void *arg) {
	unsigned long uid = 0;
	for (;;) {
		// Check if a new RFID card is present.
		if (!rfid.PICC_IsNewCardPresent()) {
		vTaskDelay(1);
		continue;
		}
		// Read the UID of the card if it's present in the MFRC522's range.
		if (!rfid.PICC_ReadCardSerial()) {
		vTaskDelay(1);
		continue;
		}

		// Display the UID of the scanned card.
		Serial.print("UID tag:");
		for (byte i = 0; i < rfid.uid.size; i++) {
		  // Add a space before the hexadecimal value if it's less than 0x10.
		  Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
		  Serial.print(rfid.uid.uidByte[i], HEX);
		}

		Serial.println();

		for (byte i = 0; i < rfid.uid.size; i++) {
			uid <<= 8;
			uid |= rfid.uid.uidByte[i];
		}
		Serial.println(uid);

		// Check if the scanned card is authorized.
		if (access()) {
		  Serial.println("Authorized access");
		  Serial.println();
		  digitalWrite(LED_rfid, HIGH);
		  	vTaskDelay(3000 / portTICK_PERIOD_MS);
		  digitalWrite(LED_rfid, LOW);
		}
		else {
		  Serial.println("Access denied");
		  	vTaskDelay(3000 / portTICK_PERIOD_MS);
		}
	}
}

// Function to blink an LED.
void taskLED(void *arg) {
	for (;;) {
	digitalWrite(LED, HIGH);
	vTaskDelay(100 / portTICK_PERIOD_MS);
	digitalWrite(LED, LOW);
	vTaskDelay(100 / portTICK_PERIOD_MS);
	}
}

// Setup function to initialize the program.
void setup() {
	pinMode(LED_rfid, OUTPUT); // Set the RFID LED on gpio 5;
	pinMode(LED, OUTPUT); // Set the general LED on gpio 22;
	Serial.begin(9600); // Initialize serial communication.
	SPI.begin(); // Initialize the SPI bus.
	rfid.PCD_Init(); // Initialize the MFRC522 RFID module.

	// Create the RFID and LED tasks and assign them to the running core.
	xTaskCreatePinnedToCore(
    taskRFID, 
	"rfid", 
    1024, 
    NULL, 
    2, 
    NULL, 
    tskNO_AFFINITY);

	xTaskCreatePinnedToCore(
    taskLED, 
    "led", 
    1024, 
    NULL, 
    1, 
    NULL, 
    tskNO_AFFINITY);
}

void loop() {
}
