#include <Arduino.h>

#define VRX1 36
#define VRY1 39
#define SW 34

#define LED 2

#define MAXINPUT 4095

float mapf(float x, float in_min, float in_max, float out_min, float out_max){
	return (x - in_min) * (out_max - out_min) / ((in_max - in_min)*1.0) + out_min;
}

void printIfChanged(const char *flag, int previous, int current){
	if (previous!=current){
		Serial.print(flag);
		Serial.print("=");
		Serial.println(current);


	}
	
}


class Joystick{

private:
	int currentX, previousX, currentY, previousY, currentButton, previousButton;
	int xPort, yPort, bPort;
	char *name;

public:
	Joystick(int valXport, int valYport, int valBport);
	void start();
	void read();
	void print();
};

Joystick::Joystick(int valXport, int valYport, int valBport){

	xPort = valXport;
	yPort = valYport;
	bPort = valBport;
	pinMode(xPort, INPUT);
	pinMode(yPort, INPUT);
	pinMode(bPort, INPUT_PULLUP);
}
void Joystick::read(){

	previousX = currentX;
	previousY = currentY;
	previousButton = currentButton;

	currentX = mapf(analogRead(xPort) ,0 , MAXINPUT, -5, 5);
	currentY = mapf(analogRead(yPort),0 , MAXINPUT, -5, 5);
	currentButton = digitalRead(bPort);

	printIfChanged("leftX", previousX, currentX);
	printIfChanged("leftY", previousY, currentY);
	printIfChanged("leftB", previousButton, currentButton);


}
void Joystick::start(){
	pinMode(xPort, INPUT);
	pinMode(yPort, INPUT);
	pinMode(bPort, INPUT_PULLUP);
	Serial.println("STARTED");
};

void Joystick::print(){
	Serial.print(" VRX1: ");
	Serial.print(currentX);
	Serial.print(" VRY1: ");
	Serial.print(currentY);
	Serial.print(" SW: ");
	Serial.print(currentButton);
	Serial.println(" ");
};

Joystick left(VRX1, VRY1, SW);

void setup(){

	Serial.begin(115200);
	left.start();

	pinMode(LED, OUTPUT);
}

void loop(){

	while (1){
		printIfChanged("flag", 2,2);
		left.read();
		// left.print();
		delay(100);
	}
}
