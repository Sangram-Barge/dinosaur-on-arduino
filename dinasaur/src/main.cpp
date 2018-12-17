#include <Arduino.h>
#include <LiquidCrystal.h>

int en = 7, rs = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
int contrast = 6;
int button = 3;
int dinosaur = 0;
int cactus = 1;
int grass = 2;
int cactoPosition = 16;
int score = 0;
int speed = 150;


LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// custom chatacters 
byte dino[8] = { // create dinosaur character
  B01110,
  B01110,
  B00100,
  B01110,
  B10101,
  B00100,
  B01010,
  B11011,
};

byte cacto[8]{ // create cactus character
  B00000,
  B00100,
  B00101,
  B10111,
  B11100,
  B00101,
  B00110,
  B00100,
};

byte gras[8]{ // create grass
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00100,
  B01101,
  B11111,
};

//define all the functions
void gameOver();
void jump();
void stay();
void displayScore();
void moveCacto();
void drawGrass();

void setup() {
  pinMode(button, INPUT); // jump button as input
  analogWrite(contrast, 0);
  lcd.begin(16, 2);
  lcd.createChar(dinosaur, dino); //create
  lcd.createChar(cactus, cacto); //custom
  lcd.createChar(grass, gras);  //characters
}

void loop() {                                                              
  bool jumping = !digitalRead(button); // check if button is pressed

  if(jumping){ // if pressed jump
    jump();
  }
  if(!jumping){ // if not pressed stay 
    stay();
  } 
  if(!jumping && cactoPosition == 3){
    gameOver();
  }
  if(jumping && cactoPosition == 3){
    score++;
  }
  drawGrass();
  displayScore();
  moveCacto();
  delay(speed);
}

void jump(){
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(3, 0);
  lcd.write(dinosaur);
}

void stay(){
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(3, 1);
  lcd.write(dinosaur);
}

void moveCacto(){
  lcd.setCursor(cactoPosition, 1);
  lcd.print("  ");

  lcd.setCursor(cactoPosition--, 1);
  lcd.write(cactus);

  if(cactoPosition < 0){
    cactoPosition = 16;
  }
}

void drawGrass(){
  for(int l=0; l<16; l++){
    if(l != 3){ 
      lcd.setCursor(l, 1);
      lcd.write(grass);
    }
  }
}

void displayScore(){
  lcd.setCursor(6, 0);
  lcd.print("Score:");
  lcd.setCursor(13, 0);
  lcd.print(score);
}

void gameOver(){
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(2, 0);
  lcd.print("Game Over");
  score = 0;
  delay(3000);
  lcd.print("          ");
}