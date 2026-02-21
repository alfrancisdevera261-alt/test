#include <Servo.h>
#include <LiquidCrystal_I2C.h>


#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_D5 587
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_DS5 622
#define NOTE_E6 1319
#define NOTE_G6 1568

#define CHOICE_OFF      0 //Used to control LEDs
#define CHOICE_NONE     0 //Used to check buttons
#define CHOICE_RED  (1 << 0)
#define CHOICE_GREEN    (1 << 3)
#define CHOICE_BLUE (1 << 1)
#define CHOICE_YELLOW   (1 << 2)

// LED Pin Definitions
#define LED_RED     3
#define LED_GREEN   9
#define LED_BLUE    5
#define LED_YELLOW  7

// Button Pin Definitions (Wire these to GND)
#define BUTTON_RED    2
#define BUTTON_GREEN  8
#define BUTTON_BLUE   4
#define BUTTON_YELLOW 6

// Buzzer Pin Definitions
#define BUZZER1  10
#define BUZZER3  11

// Game Parameters
#define ROUNDS_TO_WIN      12 
#define ENTRY_TIME_LIMIT   3000 // 3000ms = 3 seconds

#define MODE_MEMORY  0
#define MODE_BATTLE  1
#define MODE_BEEGEES 2

// Game State Variables
byte gameMode = MODE_MEMORY; 
byte gameBoard[32]; 
byte gameRound = 0;
int score = 0;

Servo myservo;

// Tetris Theme Variables
#define BPM_TETRIS (120.0)
#define POLY_DELTA (14400)

float lead_notes[] = {
  523.25, 493.88, 523.25, 587.33, 523.25, 493.88, 440.00, 440.00, 523.25, 587.33, 659.25, 587.33, 523.25, 493.88, 493.88, 523.25, 587.33, 523.25, 440.00, 440.00, 0,
  587.33, 739.99, 880.00, 830.61, 739.99, 659.25, 523.25, 659.25, 587.33, 523.25, 493.88, 493.88, 523.25, 587.33, 523.25, 440.00, 440.00, 0
};

float lead_times[] = {
  1.0, 0.5, 0.5, 1.0, 0.5, 0.5, 1.0, 0.5, 0.5, 1.0, 0.5, 0.5, 1.0, 0.5, 0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
  1.5, 0.5, 1.0, 0.5, 0.5, 1.5, 0.5, 1.0, 0.5, 0.5, 1.0, 0.5, 0.5, 1.0, 1.0, 1.0, 1.0, 1.0
};

// Add these note definitions at the top with your other #defines
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST 0

LiquidCrystal_I2C lcd(0x27, 16, 2); 
bool startupShown = false;

void setup()
{
  //Enable pull ups on inputs
  pinMode(BUTTON_RED, INPUT_PULLUP);
  pinMode(BUTTON_GREEN, INPUT_PULLUP);
  pinMode(BUTTON_BLUE, INPUT_PULLUP);
  pinMode(BUTTON_YELLOW, INPUT_PULLUP);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);

  pinMode(BUZZER1, OUTPUT);
  pinMode(BUZZER3, OUTPUT);

  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0, 0);

   lcd.setCursor(0, 0);
  lcd.print("System Starting");
  delay(1000);
  lcd.clear();
  lcd.print("Repeat After Me");
  startupShown = true;

  Serial.begin(9600);

  //Mode checking
  gameMode = MODE_MEMORY; 

  // Check to see if the lower right button is pressed
  if (checkButton() == CHOICE_YELLOW) play_beegees();

  // Check to see if upper right button is pressed
  if (checkButton() == CHOICE_GREEN)
  {
    gameMode = MODE_BATTLE; 

    //Turn on the upper right (green) LED
    setLEDs(CHOICE_GREEN);
    toner(CHOICE_GREEN, 150);

    setLEDs(CHOICE_RED | CHOICE_BLUE | CHOICE_YELLOW); 

    while(checkButton() != CHOICE_NONE) ; // Wait for release

    //Now do nothing. Battle mode will be serviced in the main routine
  }

  play_winner(); // After setup is complete, say hello to the world
}

void loop()
{
  // Check for button press during Tetris theme
  if (checkButton() != CHOICE_NONE) {
    setLEDs(CHOICE_OFF);
    noTone(BUZZER3);
    // Exit theme and start game
  } else {
    play_tetris_theme_simple();  // Play Tetris theme with LEDs
    return;  // Go back to top of loop to check buttons again
  }
  
  attractMode(); // Blink lights while waiting for user to press a button

  // Indicate the start of game play
  setLEDs(CHOICE_RED | CHOICE_GREEN | CHOICE_BLUE | CHOICE_YELLOW); 
  delay(1000);
  setLEDs(CHOICE_OFF); 
  delay(250);

  if (gameMode == MODE_MEMORY)
  {
    if (play_memory() == true) 
      play_winner(); 
    else 
      play_loser(); 
  }

  if (gameMode == MODE_BATTLE)
  {
    play_battle(); 
    play_loser(); 
  }
  
  play_background_buzzer();
}



//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//The following functions are related to game play only

boolean play_memory(void)
{
  randomSeed(millis()); 
  gameRound = 0; 

  while (gameRound < ROUNDS_TO_WIN) 
  {
    add_to_moves(); 
    playMoves();
    
    // short delay between rounds to let LEDs/LCD settle and sync display
    delay(300); // adjust ms as desired

    // NEW: small pause so player can see last move before round display updates
    delay(400); // <- short delay between game rounds (change value to taste)

    // Display current score during gameplay
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Round:");
    lcd.setCursor(7, 0);
    lcd.print(gameRound);
    
    delay(5);

    for (byte currentMove = 0 ; currentMove < gameRound ; currentMove++)
    {
      byte choice = wait_for_button(); 

      if (choice == 0) return false; // If wait timed out, player loses
      if (choice != gameBoard[currentMove]) return false; // If the choice is incorrect, player loses
    }
    delay(1000); 
  }
  return true; 
}

boolean play_battle(void)
{
  gameRound = 0; 

  while (1) 
  {
    byte newButton = wait_for_button(); 
    gameBoard[gameRound++] = newButton; 

    for (byte currentMove = 0 ; currentMove < gameRound ; currentMove++)
    {
      byte choice = wait_for_button(); 
      if (choice == 0) return false; 
      if (choice != gameBoard[currentMove]) return false; 
    }
    delay(100); 
  }
  return true; 
}

void playMoves(void)
{
  for (byte currentMove = 0 ; currentMove < gameRound ; currentMove++) 
  {
    // Update LCD to show round + current move so it stays visible while LED plays
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Round:");
    lcd.print(gameRound);
    lcd.setCursor(9, 0);
    lcd.print("Move:");
    lcd.print(currentMove + 1);

    // Play LED + sound (toner blocks for the buzz length)
    toner(gameBoard[currentMove], 200); // 200ms buzzer/LED time for visibility

    // small gap after tone so LCD/LED state is readable before next move
    delay(150);
  }
}

void add_to_moves(void)
{
  byte newButton = random(0, 4); 

  if(newButton == 0) newButton = CHOICE_RED;
  else if(newButton == 1) newButton = CHOICE_GREEN;
  else if(newButton == 2) newButton = CHOICE_BLUE;
  else if(newButton == 3) newButton = CHOICE_YELLOW;

  gameBoard[gameRound++] = newButton; 
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//The following functions control the hardware

void setLEDs(byte leds)
{
  if ((leds & CHOICE_RED) != 0) digitalWrite(LED_RED, HIGH);
  else digitalWrite(LED_RED, LOW);

  if ((leds & CHOICE_GREEN) != 0) digitalWrite(LED_GREEN, HIGH);
  else digitalWrite(LED_GREEN, LOW);

  if ((leds & CHOICE_BLUE) != 0) digitalWrite(LED_BLUE, HIGH);
  else digitalWrite(LED_BLUE, LOW);

  if ((leds & CHOICE_YELLOW) != 0) digitalWrite(LED_YELLOW, HIGH);
  else digitalWrite(LED_YELLOW, LOW);
}

byte wait_for_button(void)
{
  long startTime = millis(); 

  while ( (millis() - startTime) < ENTRY_TIME_LIMIT) 
  {
    byte button = checkButton();

    if (button != CHOICE_NONE)
    { 
      toner(button, 150); 
      while(checkButton() != CHOICE_NONE) ;  
      delay(10); 
      return button;
    }
  }
  return CHOICE_NONE; 
}

byte checkButton(void)
{
  if (digitalRead(BUTTON_RED) == 0) return(CHOICE_RED); 
  else if (digitalRead(BUTTON_GREEN) == 0) return(CHOICE_GREEN); 
  else if (digitalRead(BUTTON_BLUE) == 0) return(CHOICE_BLUE); 
  else if (digitalRead(BUTTON_YELLOW) == 0) return(CHOICE_YELLOW);

  return(CHOICE_NONE); 
}

void toner(byte which, int buzz_length_ms)
{
  setLEDs(which); 
  switch(which) 
  {
  case CHOICE_RED:
    buzz_sound(buzz_length_ms, 2272);  // Doubled from 1136
    break;
  case CHOICE_GREEN:
    buzz_sound(buzz_length_ms, 1136);  // Doubled from 568
    break;
  case CHOICE_BLUE:
    buzz_sound(buzz_length_ms, 1702);  // Doubled from 851
    break;
  case CHOICE_YELLOW:
    buzz_sound(buzz_length_ms, 1276);  // Doubled from 638
    break;
  }
  setLEDs(CHOICE_OFF); 
}

void buzz_sound(int buzz_length_ms, int buzz_delay_us)
{
  // Produce a continuous square wave with reduced amplitude
  unsigned long endTime = millis() + buzz_length_ms;
  unsigned int half_period_us = buzz_delay_us / 2;
  unsigned long cycleCount = 0;

  while (millis() < endTime) {
    // Reduce duty cycle to prevent buzzer overheating
    digitalWrite(BUZZER1, HIGH);
    delayMicroseconds(half_period_us);
    digitalWrite(BUZZER1, LOW);
    delayMicroseconds(half_period_us * 2);  // Longer low period reduces power
    
    cycleCount++;
  }
  
  // Ensure buzzer is off
  digitalWrite(BUZZER1, LOW);
}

void winner_sound(void)
{
  for (byte x = 250 ; x > 70 ; x--)
  {
    for (byte y = 0 ; y < 3 ; y++)
    {
      digitalWrite(BUZZER1, HIGH);
      delayMicroseconds(x);

      digitalWrite(BUZZER1, LOW);
      delayMicroseconds(x * 4);  // Increased pause reduces volume
    }
  }
}

void play_loser(void)
{
  setLEDs(CHOICE_RED | CHOICE_GREEN);
  buzz_sound(255, 1500);

  setLEDs(CHOICE_BLUE | CHOICE_YELLOW);
  buzz_sound(255, 1500);

  setLEDs(CHOICE_RED | CHOICE_GREEN);
  buzz_sound(255, 1500);

  setLEDs(CHOICE_BLUE | CHOICE_YELLOW);
  buzz_sound(255, 1500);
}

void attractMode(void)
{
  while(1) 
  {
    setLEDs(CHOICE_RED);
    delay(100);
    if (checkButton() != CHOICE_NONE) return;

    setLEDs(CHOICE_BLUE);
    delay(100);
    if (checkButton() != CHOICE_NONE) return;

    setLEDs(CHOICE_GREEN);
    delay(100);
    if (checkButton() != CHOICE_NONE) return;

    setLEDs(CHOICE_YELLOW);
    delay(100);
    if (checkButton() != CHOICE_NONE) return;
  }
  myservo.write(90);  
}

int melody[] = {
  NOTE_G4, NOTE_A4, 0, NOTE_C5, 0, 0, NOTE_G4, 0, 0, 0,
  NOTE_E4, 0, NOTE_D4, NOTE_E4, NOTE_G4, 0,
  NOTE_D4, NOTE_E4, 0, NOTE_G4, 0, 0,
  NOTE_D4, 0, NOTE_E4, 0, NOTE_G4, 0, NOTE_A4, 0, NOTE_C5, 0};

int noteDuration = 115; 
int LEDnumber = 0; 

void play_beegees()
{
  setLEDs(CHOICE_YELLOW);
  toner(CHOICE_YELLOW, 150);

  setLEDs(CHOICE_RED | CHOICE_GREEN | CHOICE_BLUE); 

  while(checkButton() != CHOICE_NONE) ; 

  setLEDs(CHOICE_NONE); 

  delay(1000); 

  digitalWrite(BUZZER1, LOW);
  noTone(BUZZER3);  // Make sure BUZZER3 is off
  
  while(checkButton() == CHOICE_NONE) 
  {
    for (int thisNote = 0; thisNote < 32; thisNote++) {
      changeLED();
      if (melody[thisNote] > 0) {
        tone(BUZZER3, melody[thisNote], noteDuration * 0.8);  // Longer duration = louder
      } else {
        delay(noteDuration * 0.8);
      }
      int pauseBetweenNotes = noteDuration * 0.5;  // Shorter pause
      delay(pauseBetweenNotes);
      noTone(BUZZER3);
    }
  }
}

void changeLED(void)
{
  setLEDs(1 << LEDnumber); 
  LEDnumber++; 
  if(LEDnumber > 3) LEDnumber = 0; 
}

// Background buzzer melody
int bgMelody[] = {
  NOTE_B4, NOTE_B5, NOTE_FS5, NOTE_DS5,
  NOTE_B5, NOTE_FS5, NOTE_DS5, NOTE_C5,
  NOTE_C6, NOTE_G6, NOTE_E6, NOTE_C6, NOTE_G6, NOTE_E6,
  
  NOTE_B4, NOTE_B5, NOTE_FS5, NOTE_DS5, NOTE_B5,
  NOTE_FS5, NOTE_DS5, NOTE_DS5, NOTE_E5, NOTE_F5,
  NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_B5
};

int bgDurations[] = {
  16, 16, 16, 16,
  32, 16, 8, 16,
  16, 16, 16, 32, 16, 8,
  
  16, 16, 16, 16, 32,
  16, 8, 32, 32, 32,
  32, 32, 32, 32, 32, 16, 8
};


void play_one_note_tetris(float frequency, unsigned long duration) {
  if (frequency == 0) {
    delay(duration / 1000);
    return;
  }
  unsigned long period = 1000000.0 / frequency;
  for (unsigned int cycles = duration / period; cycles > 0; cycles--) {
    digitalWrite(BUZZER3, HIGH);
    delayMicroseconds(period / 2);
    digitalWrite(BUZZER3, LOW);
    delayMicroseconds(period / 2);
  }
  delayMicroseconds(duration % period);
}

void play_tetris_theme() {
  int lead_note_count = sizeof(lead_notes) / sizeof(float);
  
  for (int i = 0; i < lead_note_count; i++) {
    float freq = lead_notes[i];
    float note_duration = lead_times[i];
    unsigned long duration_us = note_duration * 1000000 * (60.0 / BPM_TETRIS);
    
    play_one_note_tetris(freq, duration_us);
  }
}

void play_winner(void)
{
  winner_sound();
  delay(1000);
}

// Pac-Man death sound
const int pacmanMelody[] = {
  1500, 1400, 1300, 1220, 1150, 1080, 1010, 960,
  900, 850, 800, 760, 720, 680, 640, 600
};

const int pacmanDurations[] = {
  120, 110, 110, 100, 90, 90, 80, 80,
  70, 70, 60, 60, 50, 50, 50, 120
};

void play_background_buzzer(void)
{
  int noteCount = sizeof(pacmanMelody) / sizeof(pacmanMelody[0]);
  
  for (int i = 0; i < noteCount; i++) {
    tone(BUZZER3, pacmanMelody[i]);
    delay(pacmanDurations[i]);
    noTone(BUZZER3);
    delay(20);
  }
  
  // Final vibrato effect
  int finalFreq = pacmanMelody[noteCount - 1];
  for (int i = 0; i < 10; i++) {
    tone(BUZZER3, finalFreq + (i % 2 ? 25 : -25));
    delay(30);
  }
  noTone(BUZZER3);
  delay(1000); // Delay after Pac-Man death sound
}

// Tetris Theme - Complete with all verses
int tetris_tempo = 144;
int tetris_melody[] = {
  NOTE_E5, 4,  NOTE_B4, 8,  NOTE_C5, 8,  NOTE_D5, 4,  NOTE_C5, 8,  NOTE_B4, 8,
  NOTE_A4, 4,  NOTE_A4, 8,  NOTE_C5, 8,  NOTE_E5, 4,  NOTE_D5, 8,  NOTE_C5, 8,
  NOTE_B4, -4, NOTE_C5, 8,  NOTE_D5, 4,  NOTE_E5, 4,
  NOTE_C5, 4,  NOTE_A4, 4,  NOTE_A4, 4,  REST, 4,
  
  REST, 8, NOTE_D5, 4,  NOTE_F5, 8,  NOTE_A5, 4,  NOTE_G5, 8,  NOTE_F5, 8,
  NOTE_E5, -4, NOTE_C5, 8,  NOTE_E5, 4,  NOTE_D5, 8,  NOTE_C5, 8,
  NOTE_B4, 4,  NOTE_B4, 8,  NOTE_C5, 8,  NOTE_D5, 4,  NOTE_E5, 4,
  NOTE_C5, 4,  NOTE_A4, 4,  NOTE_A4, 4,  REST, 4,
};

void play_tetris_theme_simple() {
  // Show LCD when Tetris theme plays; "System Starting" only once
  if (!startupShown) {
    lcd.setCursor(0, 0);
    lcd.print("System Starting");
    delay(1000);
    lcd.clear();
    lcd.print("Repeat After Me");
    startupShown = true;
  } else {
    lcd.clear();
    lcd.print("Repeat After Me");
  }

  // ...existing code...
  int notes = sizeof(tetris_melody) / sizeof(tetris_melody[0]) / 2;
  int wholenote = (60000 * 4) / tetris_tempo;
  
  byte led_pattern[] = {CHOICE_RED, CHOICE_GREEN, CHOICE_BLUE, CHOICE_YELLOW};
  byte led_index = 0;
  
  for (int thisNote = 0; thisNote < notes * 2; thisNote += 2) {
    if (checkButton() != CHOICE_NONE) {
      setLEDs(CHOICE_OFF);
      noTone(BUZZER3);
      return;
    }
    
    int divider = tetris_melody[thisNote + 1];
    int noteDuration = (divider > 0) ? (wholenote / divider) : ((wholenote / abs(divider)) * 1.5);
    
    setLEDs(led_pattern[led_index]);
    led_index = (led_index + 1) % 4;
    
    if (tetris_melody[thisNote] > 0) {
      tone(BUZZER3, tetris_melody[thisNote], noteDuration * 0.9);
    }
    
    delay(noteDuration);
    noTone(BUZZER3);
  }
  
  setLEDs(CHOICE_OFF);
}