#include <Arduino.h>
#include <MIDI.h> // MIDI library

MIDI_CREATE_DEFAULT_INSTANCE();

const int ledPins[] = {13, 12, 11, 10, 9, 8}; // 6 LEDs
const int buttonPins[] = {2, 3, 4, 5, 6, 7};  // 6 Buttons
int ctrlDefaults[] = {10, 11, 12, 13, 14, 15};
int ctrl[6];

int midiChannel = 1;

// Debounce variables
int buttonState[6] = {0};          // Current state of the buttons
int buttonPState[6] = {1};         // Previous state of the buttons (initialized to HIGH because of INPUT_PULLUP)
unsigned long lastDebounceTime[6] = {0}; // Last time the button state changed
unsigned long debounceDelay = 10;  // Debounce delay in milliseconds

// LED and toggle state
bool ledState[6] = {false}; // Tracks the current state of each LED

// Button hold detection
unsigned long buttonPressTime[6] = {0}; // Stores the time when a button is pressed
bool buttonHeld[6] = {false};           // Tracks if a button is held

void blinkLED(int i) {
    for (int j = 0; j < 2; j++) { // Blink twice (1 second total)
        digitalWrite(ledPins[i], LOW);
        delay(125);
        digitalWrite(ledPins[i], HIGH);
        delay(125);
        digitalWrite(ledPins[i], LOW);
        delay(125);
        digitalWrite(ledPins[i], HIGH);
    }
    digitalWrite(ledPins[i], LOW); // Ensure the LED is off after blinking
}

void resetAllButtons() {
    for (int i = 0; i < 6; i++) {
        digitalWrite(ledPins[i], LOW); // Turn all LEDs off
        MIDI.sendControlChange(ctrl[i], 0, midiChannel); // Send MIDI CC 0 for all buttons
        ledState[i] = false; // Reset LED state
    }
}

void setup() {
    Serial.begin(31250);
    MIDI.begin(1);

    for (int i = 0; i < 6; i++) {
        pinMode(ledPins[i], OUTPUT);
        pinMode(buttonPins[i], INPUT_PULLUP);
        ctrl[i] = ctrlDefaults[i];

        // Initialize LEDs as off
        digitalWrite(ledPins[i], LOW);
    }
}

void loop() {
    for (int i = 0; i < 6; i++) {
        // Read the button state
        int reading = digitalRead(buttonPins[i]);

        // Check if the button state has changed
        if (reading != buttonPState[i]) {
            lastDebounceTime[i] = millis(); // Reset the debounce timer
        }

        // If the debounce time has passed, update the button state
        if ((millis() - lastDebounceTime[i]) > debounceDelay) {
            if (reading != buttonState[i]) {
                buttonState[i] = reading;

                if (buttonState[i] == LOW) { // Button pressed
                    buttonPressTime[i] = millis(); // Record the time the button was pressed
                    buttonHeld[i] = false;         // Reset the held state

                    // Toggle LED and send MIDI control change
                    ledState[i] = !ledState[i];
                    if (ledState[i]) {
                        digitalWrite(ledPins[i], HIGH); // Turn LED on
                        MIDI.sendControlChange(ctrl[i], 127, midiChannel); // Send MIDI CC 127
                    } else {
                        digitalWrite(ledPins[i], LOW); // Turn LED off
                        MIDI.sendControlChange(ctrl[i], 0, midiChannel); // Send MIDI CC 0
                    }
                }
            }
        }

        // Update the previous button state
        buttonPState[i] = reading;

        // Check if the button is held for more than 1 seconds
        if (buttonState[i] == LOW && (millis() - buttonPressTime[i] > 1000) && !buttonHeld[i]) {
            buttonHeld[i] = true; // Mark the button as held

            // Reset all buttons and LEDs before changing the MIDI channel
            resetAllButtons();

            // Change the MIDI channel based on the button index
            midiChannel = i + 1;

            // Blink the LED to indicate the channel change
            blinkLED(i);
        }
    }
}