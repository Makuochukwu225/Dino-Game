// Chrome Dino Game for Arduino Nano with 16x2 I2C LCD
// Button on D2, Buzzer on D6, LCD on A4(SDA) and A5(SCL)
// Jump over cacti to survive!

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD I2C address (usually 0x27 or 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin definitions
const int BUTTON_PIN = 2;
const int BUZZER_PIN = 6;

// Game variables
int dinoRow = 1;          // Dino position (0 = jumping, 1 = ground)
int dinoCol = 1;          // Dino column (fixed)
bool isJumping = false;
int jumpCounter = 0;
const int JUMP_DURATION = 3; // How long dino stays in air

// Obstacle variables
int obstacle1Pos = 16;    // First obstacle position
int obstacle2Pos = 24;    // Second obstacle position
int obstacle3Pos = 32;    // Third obstacle position
const int OBSTACLE_SPEED = 1;

// Game state
int score = 0;
int gameSpeed = 500;      // Game update interval (gets faster)
bool gameOver = false;
bool gameStarted = false;
unsigned long lastUpdate = 0;
bool buttonPressed = false;
bool lastButtonState = false;

// Custom characters
byte dino[8] = {
  B00000,
  B00111,
  B00101,
  B10111,
  B11100,
  B01100,
  B01010,
  B01010
};

byte dinoJump[8] = {
  B00111,
  B00101,
  B10111,
  B11100,
  B01100,
  B01010,
  B01010,
  B00000
};

byte cactus[8] = {
  B00100,
  B00101,
  B10101,
  B10101,
  B10111,
  B01110,
  B00100,
  B00100
};

byte ground[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B00000
};

void setup() {
  Serial.begin(9600);
  
  // Setup I2C LCD
  lcd.init();
  lcd.backlight();
  
  // Create custom characters
  lcd.createChar(0, dino);      // Running dino
  lcd.createChar(1, dinoJump);  // Jumping dino
  lcd.createChar(2, cactus);    // Cactus obstacle
  lcd.createChar(3, ground);    // Ground line
  
  // Setup pins
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Show start screen
  showStartScreen();
  
  // Initialize random seed
  randomSeed(analogRead(0));
}

void loop() {
  unsigned long currentTime = millis();
  
  // Read button with debouncing
  bool currentButtonState = !digitalRead(BUTTON_PIN);
  if (currentButtonState && !lastButtonState) {
    buttonPressed = true;
  }
  lastButtonState = currentButtonState;
  
  if (!gameStarted) {
    if (buttonPressed) {
      startGame();
      buttonPressed = false;
    }
    return;
  }
  
  if (gameOver) {
    if (buttonPressed) {
      resetGame();
      buttonPressed = false;
    }
    return;
  }
  
  // Update game
  if (currentTime - lastUpdate >= gameSpeed) {
    updateGame();
    drawGame();
    lastUpdate = currentTime;
  }
}

void startGame() {
  gameStarted = true;
  gameOver = false;
  dinoRow = 1;
  isJumping = false;
  jumpCounter = 0;
  obstacle1Pos = 16;
  obstacle2Pos = 24;
  obstacle3Pos = 32;
  score = 0;
  gameSpeed = 500;
}

void resetGame() {
  startGame();
}

void updateGame() {
  // Handle dino jump
  if (buttonPressed && !isJumping) {
    isJumping = true;
    jumpCounter = JUMP_DURATION;
    dinoRow = 0;  // Move to top row
    buttonPressed = false;
  }
  
  // Handle jump physics
  if (isJumping) {
    jumpCounter--;
    if (jumpCounter <= 0) {
      isJumping = false;
      dinoRow = 1;  // Back to ground
    }
  }
  
  // Move obstacles
  obstacle1Pos -= OBSTACLE_SPEED;
  obstacle2Pos -= OBSTACLE_SPEED;
  obstacle3Pos -= OBSTACLE_SPEED;
  
  // Reset obstacles when they go off screen
  if (obstacle1Pos < 0) {
    obstacle1Pos = 16 + random(8, 16);
    score++;
    increaseSpeed();
  }
  
  if (obstacle2Pos < 0) {
    obstacle2Pos = 16 + random(8, 16);
    score++;
    increaseSpeed();
  }
  
  if (obstacle3Pos < 0) {
    obstacle3Pos = 16 + random(8, 16);
    score++;
    increaseSpeed();
  }
  
  // Check collisions
  checkCollisions();
}

void checkCollisions() {
  // Check collision with each obstacle
  if ((obstacle1Pos == dinoCol && dinoRow == 1) ||
      (obstacle2Pos == dinoCol && dinoRow == 1) ||
      (obstacle3Pos == dinoCol && dinoRow == 1)) {
    gameOver = true;
    playTone(200, 1000);  // Game over sound
  }
}

void increaseSpeed() {
  // Increase game speed every few points
  if (score % 3 == 0 && gameSpeed > 150) {
    gameSpeed -= 20;  // Make game faster
  }
}

void drawGame() {
  lcd.clear();
  
  // Draw ground line on bottom row
  for (int i = 0; i < 16; i++) {
    lcd.setCursor(i, 1);
    lcd.write(3);  // Ground character
  }
  
  // Draw dino
  lcd.setCursor(dinoCol, dinoRow);
  if (isJumping) {
    lcd.write(1);  // Jumping dino
  } else {
    lcd.write(0);  // Running dino
  }
  
  // Draw obstacles
  if (obstacle1Pos >= 0 && obstacle1Pos < 16) {
    lcd.setCursor(obstacle1Pos, 1);
    lcd.write(2);  // Cactus
  }
  
  if (obstacle2Pos >= 0 && obstacle2Pos < 16) {
    lcd.setCursor(obstacle2Pos, 1);
    lcd.write(2);  // Cactus
  }
  
  if (obstacle3Pos >= 0 && obstacle3Pos < 16) {
    lcd.setCursor(obstacle3Pos, 1);
    lcd.write(2);  // Cactus
  }
  
  // Draw score
  lcd.setCursor(12, 0);
  lcd.print(score);
  
  // Draw game over message
  if (gameOver) {
    lcd.setCursor(0, 0);
    lcd.print("GAME OVER!      ");
    delay(1000);
    lcd.setCursor(0, 0);
    lcd.print("Score: ");
    lcd.print(score);
    lcd.print("        ");
    lcd.setCursor(0, 1);
    lcd.print("Press to restart");
  }
}

void showStartScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  DINO  RUNNER  ");
  lcd.setCursor(0, 1);
  lcd.print(" Press to start ");
  
  // Animate the dino
  for (int i = 0; i < 3; i++) {
    delay(500);
    lcd.setCursor(6, 1);
    lcd.write(0);  // Show dino
    delay(500);
    lcd.setCursor(6, 1);
    lcd.print(" ");  // Hide dino
  }
}

void playTone(int frequency, int duration) {
  tone(BUZZER_PIN, frequency, duration);
}
