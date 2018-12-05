#include <Adafruit_NeoPixel.h>

#define Count 590
#define Pin 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(Count,Pin,NEO_GRB + NEO_KHZ800);

#define Brightness 67 //Set brightness to 2/10th
#define Full (255/Brightness)
//Create scrolling red and white candy cane stripes.
//Try adjusting the width in pixels for various results.
//Value "sets" should evenly divide into strand length
void CandyCane  (int sets,int width,int wait) {
  int L;
  for(int j=0;j<(sets*width);j++) {
    for(int i=0;i< strip.numPixels();i++) {
      L=strip.numPixels()-i-1;
      if ( ((i+j) % (width*2) )<width)
        strip.setPixelColor(L,238/Brightness,66/Brightness,56/Brightness);
      else
        strip.setPixelColor(L,Full,Full,Full);
    };
    strip.show();
    delay(wait);
  };
};

//Create sets of random white or gray pixels
void RandomWhite (int sets, int wait) {
  int V,i,j;
  for (i=0;i<sets;i++) {
    for(j=0;j<strip.numPixels();j++) {
      V=random(Full);
      strip.setPixelColor(j,V,V,V);
    }
    strip.show();
    delay(wait);
  }
};
//Create sets of random colors
void RandomColor (int sets, int wait) {
  int i,j;
  for (i=0;i<sets;i++) {
    for(j=0;j<strip.numPixels();j++) {
      strip.setPixelColor(j,random(255)/Brightness,random(255)/Brightness,random(255)/Brightness);
    }
    strip.show();
    delay(wait);
  }
};
void RainbowStripe (int sets,int width,int wait) {
  int L;
  for(int j=0;j<(sets*width*6);j++) {
    for(int i=0;i< strip.numPixels();i++) {
      L=strip.numPixels()-i-1;
      switch ( ( (i+j)/width) % 6 ) {
        case 0: strip.setPixelColor(L,238/Brightness,66/Brightness,56/Brightness);break;//ARed
        case 1: strip.setPixelColor(L,247/Brightness,203/Brightness,128/Brightness);break;//AYellow
        case 2: strip.setPixelColor(L,0,Full,0);break;//Green
        case 3: strip.setPixelColor(L,0,Full,Full);break;//Cyan
        case 4: strip.setPixelColor(L,167/Brightness,193/Brightness,210/Brightness);break;//ABlue
        case 5: strip.setPixelColor(L,122/Brightness,31/Brightness,61/Brightness);break;//AMagenta
//        default: strip.setPixelColor(L,0,0,0);//Use for debugging only
      }
    };
    strip.show();
    delay(wait);
  };
};
//These routines were modified from Adafruit strand test sketch
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbowCycle(uint8_t sets, uint8_t wait) {
  uint16_t i, j;
  for(j=0; j<256*sets; j++) { //cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(strip.numPixels()-i-1, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color((WheelPos * 3)/Brightness, (255 - WheelPos * 3)/Brightness, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color((255 - WheelPos * 3)/Brightness, 0, (WheelPos * 3)/Brightness);
  } else {
   WheelPos -= 170;
   return strip.Color(0,(WheelPos * 3)/Brightness, (255 - WheelPos * 3)/Brightness);
  }
}

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  randomSeed(1234);//Set up random number generator
}

void loop() {
  CandyCane(30,8,40);//30 sets, 8 pixels wide, 50us delay
  RainbowStripe(5,4,40);//5 cycles, 4 pixels wide, 75us delay
  RandomWhite(50,200);//50 sets of random grayscale
  RandomColor(50,200);//50 sets of random colors
  colorWipe(strip.Color(238/Brightness, 66/Brightness, 56/Brightness), 40); // ARed
  colorWipe(strip.Color(247/Brightness, 203/Brightness, 128/Brightness), 40); // AYellow
  colorWipe(strip.Color(0, Full, 0), 40); // Green
  colorWipe(strip.Color(0, Full, Full), 40); // Cyan
  colorWipe(strip.Color(167/Brightness, 193/Brightness, 210/Brightness), 40); // ABlue
  colorWipe(strip.Color(122/Brightness, 31/Brightness, 61/Brightness), 40); // AMagenta
  rainbowCycle(10,2);//10 rainbow cycles
  colorWipe(0,5);//Black
}
