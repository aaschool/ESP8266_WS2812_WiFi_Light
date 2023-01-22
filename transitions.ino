void t_sinelon()
{
  // a coloured dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 2);
  int pos = beatsin16(13,0,NUM_LEDS);
  leds[pos] = ColorFromPalette(palette, idx, 255);
}


void t_bpm()
{
  // colored stripes pulsing at a defined beats-per-minute (BPM)
  uint8_t BeatsPerMinute = int(speed/2);
  uint8_t beat = beatsin8( BeatsPerMinute, 32, 255);
  for( int i = 0; i < NUM_LEDS; i++) { 
    leds[i] = ColorFromPalette(palette, idx+(i*2), beat-idx+(i*10));
  }
}

void t_random() 
{
  // random colored dots that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] = ColorFromPalette(palette, idx + random8(64), 255);
}

void t_gradient()
{
    // all the LEDs smoothly fade up and down
    for( int i = 0; i < NUM_LEDS; i++) {
      leds[i] = ColorFromPalette( palette, idx, brightness, LINEARBLEND);
    }
}

void t_constant()
{
    // constant coloured light for all the LEDs in the strip
    for( int i = 0; i < NUM_LEDS; i++) {
      leds[i] = ColorFromPalette( palette, idx, brightness);
    }
}
