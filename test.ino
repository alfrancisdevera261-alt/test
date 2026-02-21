#include <Servo.h>

#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_C5 523

// Added missing note definitions used by bgMelody
#define NOTE_B4 494
#define NOTE_B5 988
#define NOTE_C6 1046
#define NOTE_E5 659
#define NOTE_E6 1318
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_G6 1568
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_DS5 622

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

// Buzzer pins (keep existing BUZZER1/2/3 for other sounds)
// Added Pac‑Man death sound on pin 11
const int buzzerPin = 11;

// Legacy buzzer outputs used elsewhere in the sketch
#define BUZZER1 10
#define BUZZER2 12
#define BUZZER3 13

// Pac‑Man death sound (replaces previous winner tone)
const int pacman_melody[] = {
  1500, 1400, 1300, 1220, 1150, 1080, 1010, 960,
  900, 850, 800, 760, 720, 680, 640, 600
};
const int pacman_durations[] = {
  120, 110, 110, 100, 90, 90, 80, 80,
   70, 70, 60, 60, 50, 50, 50, 120
};
const int pac_notes = sizeof(pacman_melody) / sizeof(pacman_melody[0]);

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

Servo myservo;

void setup()
{
  myservo.attach(14);

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
  pinMode(BUZZER2, OUTPUT);
  pinMode(BUZZER3, OUTPUT);

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
  myservo.write(90);  
}

void loop()
{
  attractMode(); // Blink lights while waiting for user to press a button

  // Indicate the start of game play
  setLEDs(CHOICE_RED | CHOICE_GREEN | CHOICE_BLUE | CHOICE_YELLOW); 
  myservo.write(90);
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
    toner(gameBoard[currentMove], 150);
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
    buzz_sound(buzz_length_ms, 1136); 
    break;
  case CHOICE_GREEN:
    buzz_sound(buzz_length_ms, 568); 
    break;
  case CHOICE_BLUE:
    buzz_sound(buzz_length_ms, 851); 
    break;
  case CHOICE_YELLOW:
    buzz_sound(buzz_length_ms, 638); 
    break;
  }
  setLEDs(CHOICE_OFF); 
}

void buzz_sound(int buzz_length_ms, int buzz_delay_us)
{
  long buzz_length_us = buzz_length_ms * (long)1000;

  while (buzz_length_us > (buzz_delay_us * 2))
  {
    buzz_length_us -= buzz_delay_us * 2; 

    digitalWrite(BUZZER1, LOW);
    digitalWrite(BUZZER2, HIGH);
    delayMicroseconds(buzz_delay_us);

    digitalWrite(BUZZER1, HIGH);
    digitalWrite(BUZZER2, LOW);
    delayMicroseconds(buzz_delay_us);
  }
}

// Replace the original play_winner implementation with Pac‑Man death tone
void play_winner(void)
{
  pinMode(buzzerPin, OUTPUT);

  for (int i = 0; i < pac_notes; ++i) {
    tone(buzzerPin, pacman_melody[i]);
    delay(pacman_durations[i]);
    noTone(buzzerPin);
    delay(20);
  }

  int finalFreq = pacman_melody[pac_notes - 1];
  for (int i = 0; i < 10; ++i) {
    tone(buzzerPin, finalFreq + (i % 2 ? 25 : -25));
    delay(30);
  }
  noTone(buzzerPin);
}

void winner_sound(void)
{
  for (byte x = 250 ; x > 70 ; x--)
  {
    for (byte y = 0 ; y < 3 ; y++)
    {
      digitalWrite(BUZZER2, HIGH);
      digitalWrite(BUZZER1, LOW);
      delayMicroseconds(x);

      digitalWrite(BUZZER2, LOW);
      digitalWrite(BUZZER1, HIGH);
      delayMicroseconds(x);
    }
  }
}

void play_loser(void)
{
  myservo.write(0);
   
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

  while(checkButton() == CHOICE_NONE) 
  {
    for (int thisNote = 0; thisNote < 32; thisNote++) {
      changeLED();
      tone(BUZZER2, melody[thisNote],noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(BUZZER2);
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

void play_background_buzzer(void)
{
  int size = sizeof(bgDurations) / sizeof(int);

  for (int note = 0; note < size; note++) {
    int duration = 1000 / bgDurations[note];
    long endTime = millis() + duration;
    
    if (bgMelody[note] > 0) {
      // don't shadow the built-in delayMicroseconds() function name
      int halfPeriodUs = 500000 / bgMelody[note];
      
      while (millis() < endTime) {
        digitalWrite(BUZZER3, HIGH);
        delayMicroseconds(halfPeriodUs);
        digitalWrite(BUZZER3, LOW);
        delayMicroseconds(halfPeriodUs);
      }
    } else {
      delay(duration);
    }

    int pauseBetweenNotes = (int)(duration * 1.30);
    delay(pauseBetweenNotes);
  }
}