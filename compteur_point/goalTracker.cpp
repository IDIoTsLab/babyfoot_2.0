#ifndef GOAL_TRACKER_H
#define GOAL_TRACKER_H
#include "goalTracker.h"
#include <Arduino.h>

void GoalTracker::Init(int ledPin, int resistorPin, int goalThreshold){
	m_ledPin = ledPin;
	m_resistorPin = resistorPin;
	m_goalThreshold = goalThreshold;

	pinMode(m_ledPin, OUTPUT);
	digitalWrite(m_ledPin, HIGH);
}

bool GoalTracker::checkNewPoint(){
	bool isNewPoint = false;
	valueList[count] = analogRead(m_resistorPin);
	int sensorValue = getSensorValue();
	

	if(! isBallPresent && sensorValue < m_goalThreshold){
		isBallPresent = true;
	}

	if(isBallPresent && sensorValue > m_goalThreshold){
		isBallPresent = false;
		isNewPoint = true;
	}
	// put your main code here, to run repeatedly:
	count = (count + 1) % LIST_SIZE;
	return isNewPoint;
}





#endif
