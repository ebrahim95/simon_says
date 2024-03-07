#include <Adafruit_CircuitPlayground.h>
 
// sets up variables for regions
// simon says

int region_leds[][3] = { { 0, 1, 2 }, { 2, 3, 4 }, { 5, 6, 7 }, { 7, 8, 9 } };
int region_tone[] = { 252, 209, 310, 415, };
int region_colors[][3] = { { 255, 255, 0 }, { 0, 0, 255 }, { 255, 0, 0}, { 0, 255, 0 } };
int region_touch[] = {3,4,4,1,1,2,2};

int current_time = millis();
int last_time = 0;
int runtime = 5000;

void light_region(int region, int duration = 1000) {
  for (int i = 0; i < 3; ++i) {
    CircuitPlayground.setPixelColor(region_leds[region][i], region_colors[region][0],region_colors[region][1],region_colors[region][2]);
  }
  CircuitPlayground.playTone(region_tone[region], 100);
  delay(duration);
  CircuitPlayground.clearPixels();
  delay(500);

}

int read_region() {
  if (CircuitPlayground.readCap(0) > 1000) { //A6
    light_region(1,1000);
    return 1;
  }  else if (CircuitPlayground.readCap(1) > 1000) { //A7
    light_region(1,1000);
    return 1;
  } else if (CircuitPlayground.readCap(2) > 1000) { //A5
    light_region(0,1000);
    return 0;
  } else if (CircuitPlayground.readCap(3) > 1000) { //A4
    light_region(0,1000);
    return 0;
  } else if (CircuitPlayground.readCap(6) > 1000) { //A1
    light_region(2,1000);
    return 2;
  } else if (CircuitPlayground.readCap(9) > 1000) { //A2
    light_region(3,1000);
    return 3;
  } else if (CircuitPlayground.readCap(10) > 1000) { //A3
    light_region(3,1000);
    return 3;
  } else {
    return 4;
  }
} 

int sequence[] = {0,1,2,3};
int turn = 0;
int read = 0;
void setup() {
  CircuitPlayground.begin();
  for (int i = 0; i < sizeof(sequence) / sizeof(int); i++) {
    light_region(i);
  }
}


void loop() {
  read = read_region();
 // the turn needs to checked
 // if they took the turn 
 // then increase the turn 
 // see if it is right or wrong
 if (turn == 4) {
    Serial.print("You win");
    for (int i = 0; i < 10; i++) {
      int value_1 = rand() % 256;
      int value_2 = rand() % 256;
      int value_3 = rand() % 256;

      CircuitPlayground.setPixelColor(i, value_1, value_2, value_3);
    }
    delay(2000);
    CircuitPlayground.clearPixels();
    turn = 0;
 } else if (sequence[turn] == read) {
    turn += 1;
    read = 0;
 } else if (!sequence[turn] == read) {
    CircuitPlayground.redLED(HIGH);
    CircuitPlayground.playTone(160,500);
    delay(1000);
    CircuitPlayground.redLED(LOW);
    turn = 0;
    read = 0;
 }  

if (current_time - last_time >= runtime) {
  // do something
  // timer 
  Serial.println("hi");
  last_time = current_time;
  delay(3000);
}

 Serial.println(read);
 Serial.println(turn);

 current_time = millis();
  
}
