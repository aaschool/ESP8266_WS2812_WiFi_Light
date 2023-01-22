DEFINE_GRADIENT_PALETTE( blue_gp ) {
  0,     0,  0,  0,     //black
255,     0,  0,  255 }; //blue

DEFINE_GRADIENT_PALETTE( green_gp ) {
  0,     0,  0,  0,     //black
255,     0,  255,  0 }; //green

DEFINE_GRADIENT_PALETTE( yellow_gp ) {
  0,     0,  0,  0,       //black
255,     255,  255,  0 }; //yellow

DEFINE_GRADIENT_PALETTE( orange_gp ) {
  0,     0,  0,  0,       //black
  10,     10,  5,  0,   
  20,     20,  10,  0,   
  200,     200,  100,  0,
255,     255, 128,  0 };  //orange

DEFINE_GRADIENT_PALETTE( red_gp ) {
  0,     0,  0,  0,     //black
255,     255,  0,  0 }; //red

DEFINE_GRADIENT_PALETTE( pink_gp ) {
  0,     0,  0,  0,       //black
255,     255,  0,  128 }; //pink

DEFINE_GRADIENT_PALETTE( white_gp ) {
  0,     0,  0,  0,         //black
255,     255,  255,  255 }; //white

DEFINE_GRADIENT_PALETTE( black_gp ) {
  0,     0,  0,  0,   //black
255,     0,  0,  0 }; //black

void setColor(int color) {
  int i;
  Serial.println(color);
  CRGB c;
  switch (color) { 
    case WHITE:
      c = CRGB::White;
      palette = white_gp;
      break;
    case RED:
      c = CRGB::Red;
      palette = red_gp;
      break;
    case GREEN:
      c = CRGB::Green;
      palette = green_gp;
      break;
    case BLUE:
      c = CRGB::Blue;
      palette = blue_gp;
      break;
    case YELLOW:
      c = CRGB::Yellow;
      palette = yellow_gp;
      break;
    case ORANGE:
      c = CRGB::Orange;
      palette = orange_gp;
      break;
    case PINK:
      c = CRGB::Pink;
      palette = pink_gp;
      break;
    case BLACK:
      c = CRGB::Black;
      palette = black_gp;
      break;
  }
    delay(DELAY);
}

void testLEDs(){
  int i;
  Serial.println("Testing LEDs");
  for(int i = 0; i < NUM_LEDS; i++) {
    // set our current dot to red
    Serial.println("Red");
    leds[i] = CRGB::Red;
    FastLED.show();
    delay(DELAY);
  }
  for(int i = 0; i < NUM_LEDS; i++) {
    // set our current dot to green
    Serial.println("Green");
    leds[i] = CRGB::Green;
    FastLED.show();
    delay(DELAY);
  }
  for(int i = 0; i < NUM_LEDS; i++) {
    // set our current dot to blue
    Serial.println("Blue");
    leds[i] = CRGB::Blue;
    FastLED.show();
    delay(DELAY);
  }
}

void setBrightness(int newBrightness) 
{
  brightness = newBrightness;
  FastLED.setBrightness(brightness);
  Serial.print("Brightness: ");
  Serial.println(brightness);
}

void brighten()
{
  brightness+=20;
  if (brightness>250) brightness=250;
  FastLED.setBrightness(brightness);
  Serial.print("Brightness: ");
  Serial.println(brightness);
}

void dim()
{
  brightness-=20;
  if (brightness<0) brightness=0;
  FastLED.setBrightness(brightness);
  Serial.print("Brightness: ");
  Serial.println(brightness);
}

void setSpeed(int newSpeed) 
{
  speed = newSpeed;
  FastLED.delay(1000/speed); 
  Serial.print("Speed (frames/second): ");
  Serial.println(speed);
}

void faster()
{
  speed+=10;
  if (speed>3000) speed=3000;
  FastLED.delay(1000/speed); 
  Serial.print("Speed (frames/second): ");
  Serial.println(speed);
}

void slower()
{
  speed-=10;
  if (speed<=10) speed=10;
  FastLED.delay(1000/speed); 
  Serial.print("Speed (frames/second): ");
  Serial.println(speed);
}