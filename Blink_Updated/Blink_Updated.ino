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
  // Morse code mappings for letters and numbers
  String morseCode[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."};
  for (int i = 0; i < input.length(); i++) {
    char c = tolower(input[i]); // Convert character to lowercase
    if (c == ' ') {
      // Pause between words
      delay(4000); // Pause for 7 units | In addition with the closing delays this adds up to 7 units
    } else if (isAlphaNumeric(c)) {
      int index = c - (isDigit(c) ? '0' : 'a');
      String morse = morseCode[index]; // Get Morse code for the character
      for (int j = 0; j < morse.length(); j++) {
        if (morse[j] == '.') {
          // Short flash for dot
          flashLED(1000); // Delay for 1 unit
        } else if (morse[j] == '-') {
          // Long flash for dash
          flashLED(3000); // Delay for 3 units
        }
        // Pause between dots and dashes
        delay(1000); // Pause for 1 unit
      }
    }
    // Pause between characters
    delay(2000); // Pause for 3 units | as the one unit is already listed above only 2 additional units are needed
  }
}

void flashLED(int duration) {
  digitalWrite(LED_BUILTIN, HIGH); // Turn on the LED
  delay(duration); // Wait for the duration
  digitalWrite(LED_BUILTIN, LOW); // Turn off the LED
}