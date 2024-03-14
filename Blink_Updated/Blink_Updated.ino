void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // Initialize the built-in LED pin as an output
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  String inputString = ""; // Variable to store input string
  while (Serial.available()) {
    char c = Serial.read(); // Read serial input character by character
    inputString += c; // Append each character to the input string
  }
  
  if (inputString != "") {
    translateToMorse(inputString); // Translate input string to Morse code
  }
}

void translateToMorse(String input) {
  // Morse code values for letters and numbers
  String morseCode[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."};
  for (int i = 0; i < input.length(); i++) {
    char c = tolower(input[i]); // Convert character to lowercase
    if (c == ' ') {
      delay(4000); // Pause for 7 units between words | In addition with the closing delays this adds up to 7 units
    } else if (isAlphaNumeric(c)) {
      int index = c - (isDigit(c) ? '0' : 'a');
      String morse = morseCode[index]; // Get Morse code for the character
      for (int j = 0; j < morse.length(); j++) {
        if (morse[j] == '.') {
          flashLED(1000); // Short flash for dot | Delay for 1 unit
        } else if (morse[j] == '-') {
          flashLED(3000); // Long flash for dash | Delay for 3 units
        }
        delay(1000); // Pause between dots and dashes | Pause for 1 unit
      }
    }
    delay(2000); // Pause between characters | Pause for 3 units | as the one unit is already listed above only 2 additional units are needed
  }
}

void flashLED(int duration) {
  digitalWrite(LED_BUILTIN, HIGH); // Turn on the LED
  delay(duration); // Wait for the duration
  digitalWrite(LED_BUILTIN, LOW); // Turn off the LED
}