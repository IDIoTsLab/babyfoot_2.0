#include <FastLED.h>

#define NUM_LEDS_PER_STRIP 10

#define UPDATES_PER_SECOND 100

#define LED_TYPE    WS2811
#define BRIGHTNESS  64
#define COLOR_ORDER GRB

#define LED_PIN_LEFT   6
#define LED_PIN_RIGHT  7

#define LEFT_STRIP true
#define RIGHT_STRIP false

CRGB leds_left[NUM_LEDS_PER_STRIP];
CRGB leds_right[NUM_LEDS_PER_STRIP];

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN_LEFT, COLOR_ORDER>(leds_left, NUM_LEDS_PER_STRIP);
  FastLED.addLeds<LED_TYPE, LED_PIN_RIGHT, COLOR_ORDER>(leds_right, NUM_LEDS_PER_STRIP);
  FastLED.setBrightness(BRIGHTNESS);

  FastLED.clear(true); // Efface tout
}

void loop() {
  // put your main code here, to run repeatedly:
  /*if (detect_goal_left()) {
    score_left++;
    animation_goal(false);  // false = côté gauche
    afficher_score(false, score_left);
  }

  if (detect_goal_right()) {
    score_right++;
    animation_goal(true);   // true = côté droit
    afficher_score(true, score_right);
  }*/
  animation_goal(true);
  
  afficher_score(false, 2);
  afficher_score(true, 5);

  delay(1000);

  animation_goal(false);

  afficher_score(false, 8);
  afficher_score(true, 4);

  

  delay(1000);

  while(1){}
}


void afficher_score(bool is_right, int score) {
  CRGB* strip = is_right ? leds_right : leds_left;

  // Nettoyer le bandeau
  for (int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
    strip[i] = CRGB::Black;
  }

  // Afficher le score en bleu
  int clamped_score = constrain(score, 0, NUM_LEDS_PER_STRIP);
  for (int i = 0; i < clamped_score; i++) {
    strip[i] = CRGB::Blue;
  }

  FastLED.show();
}


void animation_goal(bool is_right) {
  CRGB* scoring_strip = is_right ? leds_right : leds_left;
  CRGB* other_strip   = is_right ? leds_left  : leds_right;

  // Rainbow effect !

  //for(int j = 0; j < 256; j++) {
  for(int j = 0; j < 512; j++) {
		for(int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
			scoring_strip[i] = Scroll((i * 256 / NUM_LEDS_PER_STRIP + j) % 256);   
      other_strip[i] = Scroll((i * 256 / NUM_LEDS_PER_STRIP + j) % 256);
		} 
		FastLED.show();
	} 





  // Blink score
  for (int b = 0; b < 5; b++) {
    for (int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
      scoring_strip[i] = CRGB::Red;
      other_strip[i]   = CRGB::Green;
    }
    FastLED.show();
    delay(200);

    for (int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
      scoring_strip[i] = CRGB::Black;
      other_strip[i]   = CRGB::Black;
    }
    FastLED.show();
    delay(150);
  }
}

// WS2812B LED Strip switches Red and Green
CRGB Scroll(int pos) {
	CRGB color (0,0,0);
	if(pos < 85) {
		color.g = 0;
		color.r = ((float)pos / 85.0f) * 255.0f;
		color.b = 255 - color.r;
	} else if(pos < 170) {
		color.g = ((float)(pos - 85) / 85.0f) * 255.0f;
		color.r = 255 - color.g;
		color.b = 0;
	} else if(pos < 256) {
		color.b = ((float)(pos - 170) / 85.0f) * 255.0f;
		color.g = 255 - color.b;
		color.r = 1;
	}
	return color;
}