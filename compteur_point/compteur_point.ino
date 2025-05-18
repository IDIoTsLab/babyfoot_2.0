#include "goalTracker.h"


GoalTracker gt;
void setup() {
  // put your setup code here, to run once:
  gt.Init(4, A0, 40);
  Serial.begin(115200);
}

int points = 0;
void loop() {
  if(gt.checkNewPoint()){
    points++;
    Serial.println(points);
  }
  delay(20);
}
