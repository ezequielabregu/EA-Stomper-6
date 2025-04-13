# EA Stomper 6

EA Stomper 6 is a MIDI controller project built using an Arduino Uno. It features six buttons and six LEDs, allowing users to send MIDI Control Change (CC) messages and toggle LED states. The project is designed for musicians and hobbyists who want to create a customizable MIDI controller.

![Stomper6](/media/stomper6.jpeg)

## Features

- **6 Buttons**: Each button sends a MIDI CC message when pressed.
- **6 LEDs**: LEDs indicate the state of each button and provide visual feedback.
- **MIDI Channel Switching**: Hold a button for more than 1 second to switch the MIDI channel.
- **Debouncing**: Ensures reliable button presses using software debouncing.
- **Customizable MIDI CC Values**: Default CC values can be modified in the code.

## Requirements

### Hardware
- Arduino Uno
- 6 LEDs
- 6 Push Buttons
- Resistors (as needed for LEDs and buttons)

### Software
- [PlatformIO](https://platformio.org/) (for building and uploading the code)
- Arduino IDE (optional)

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/your-repo/EA_Stomper_6.git
   cd EA_Stomper_6

### Install PlatformIO:

Follow the PlatformIO installation guide.

Install dependencies: PlatformIO will automatically install the required libraries specified in platformio.ini:

`MIDI Library`

Connect your Arduino Uno to your computer.

Build and upload the code:

### Usage

Connect the buttons and LEDs to the Arduino Uno as specified in the src/main.cpp file:

LED Pins: 13, 12, 11, 10, 9, 8

Button Pins: 2, 3, 4, 5, 6, 7

Power on the Arduino Uno.

Press the buttons to send MIDI CC messages:

Button press toggles the corresponding LED and sends a MIDI CC message.

Hold a button for more than 1 second to switch the MIDI channel.

Use a MIDI-compatible software or hardware to test the MIDI messages.


### Troubleshooting

Ensure the correct COM port is selected in PlatformIO.

Verify the wiring of buttons and LEDs.

Check the MIDI software for proper configuration.

