// SumoBot V2 Mod V1

// Input
const int GO = 12;				//PIN D4 est le bouton GO
const int CNY_LEFT = 2;				//PIN D2 est le CNY_1
const int CNY_RIGHT = 3;				//PIN D3 est le CNY_2
const int SHARP = 0;				//PIN A0 est le SHARP

// Output
const int LED_1 = 13;				//PIN D4 est la LED_1
const int LED_2 = 5;				//PIN D5 est le LED_2

// H Bridge
const int leftWheel = 10;			//PIN D10 est le PWM de la roue GAUCHE
const int rightWheel = 11;			//PIN D11 est le PWM de la roue DROITE
const int leftWheelDirection0 = 6;		//PIN D6 est la direction 0 de la roue GAUCHE
const int leftWheelDirection1 = 7;		//PIN D7 est la direction 1 de la roue GAUCHE
const int rightWheelDirection0 = 8;		//PIN D8 est la direction 0 de la roue DROITE
const int rightWheelDirection1 = 9;		//PIN D9 est la direction 1 de la roue DROITE

// Vars
const int RIGHT = 1;
const int LEFT = 2;
const int BOTH = 3;
const int BACKWARDS = 3;
const int FORWARDS = 4;


void setup(void) {
    Serial.begin(115200);
    Serial.println("Sumo Init...");

	pinMode(GO,INPUT_PULLUP);		//le PIN GO (c'est a dire le 12) est en mode entrée avec resistance de tirage au +5V
	pinMode(LED_2,OUTPUT);			//le PIN LED_2 (5) est en mode sortie
	pinMode(CNY_LEFT,INPUT);		        //le PIN CNY_1 (2) est en mode entrée avec resistance de tirage au +5V
	pinMode(CNY_RIGHT,INPUT);		        //le PIN CNY_2 (3) est en mode entrée avec resistance de tirage au +5V
	pinMode(LED_1,OUTPUT);	        	//le PIN LED_1 (13) est en mode sortie
	pinMode(leftWheel, OUTPUT);		//le PIN leftWheel (10) est en mode sortie
	pinMode(rightWheel, OUTPUT);		//le PIN rightWheel (11) est en mode sortie
	pinMode(leftWheelDirection0, OUTPUT);	//le PIN leftWheelDirection0 (6) est en mode sortie
	pinMode(leftWheelDirection1, OUTPUT);	//le PIN leftWheelDirection1 (7) est en mode sortie
	pinMode(rightWheelDirection0, OUTPUT);	//le PIN rightWheelDirection0(8) est en mode sortie
	pinMode(rightWheelDirection1, OUTPUT);	//le PIN rightWheelDirection1 (9) est en mode sortie

}



void loop(void) {
    
    start();    //appele la fonction start()
    go(255);
    while(1) {

        digitalWrite(LED_1,LOW); 
        digitalWrite(LED_2,LOW);

        int whiteLine = whiteLineDetector();
        if(whiteLine != 0) {
          escape(whiteLine);
        }
    
        if(isSharpDetecting(5)) {
            escape(BACKWARDS);
        }
        else {
            go(255);
        }
        delay(50);
    }
}


void start(void) {
	digitalWrite(LED_1, HIGH);    //On allume la LED_1

    Serial.println("Sumo Ready!");

	while(digitalRead(GO) == HIGH){}	      //Tant que le bouton n'est pas appuyé, on ne fait rien
	
    Serial.println("Launched, starting in 3 seconds...");
	digitalWrite(LED_1,LOW);              //On eteint la LED_1
    delay(3000);			      //On attend 3000 ms
}

bool isSharpDetecting(int distance) {
    return (sharpDistance() < distance);
}

int sharpDistance() {
    return sharpRealDistance(SHARP);
}

int sharpRealDistance(int raw) { /* function distRawToPhys */
  ////IR Distance sensor conversion rule
  float vOut = float(raw) * 0.0048828125; // Conversion analog to voltage
  return (13 * pow(vOut, -1.0)); // Conversion volt to distance
}

int whiteLineDetector() {
    int status = 0;
    
    if (digitalRead(CNY_LEFT) == HIGH) {
        status = LEFT;
    }

    if (digitalRead(CNY_RIGHT) == HIGH) {
        if (status == LEFT) {
            return BOTH;
        }
        status = RIGHT;
    }

    return status;
}


void escape(int direction) {
    Serial.print("Escaping : ");
    Serial.println(direction);

    digitalWrite(LED_1,HIGH);

    back(255);
    delay(1500);

    int leftWheelSpeed = 255;
    int rightWheelSpeed = 255;

    if (direction == BACKWARDS) {
        delay(500);
        int direction = random(1,3);
        leftWheelSpeed = random(256);
        rightWheelSpeed = random(256);
    }
    if(direction == LEFT) {
        turnLeft(leftWheelSpeed,rightWheelSpeed);
    }
    else if (direction == RIGHT) {
        turnRight(leftWheelSpeed,rightWheelSpeed);
    }
    
    digitalWrite(LED_1,LOW);
}


void go(unsigned char wheelSpeed) {

    digitalWrite(leftWheelDirection0, HIGH);
    digitalWrite(leftWheelDirection1, LOW);
    digitalWrite(rightWheelDirection0, HIGH);
    digitalWrite(rightWheelDirection1, LOW);
    analogWrite(leftWheel, wheelSpeed);
    analogWrite(rightWheel, wheelSpeed);
}


void back(unsigned char wheelSpeed) {

    digitalWrite(leftWheelDirection0, LOW);
    digitalWrite(leftWheelDirection1, HIGH);
    digitalWrite(rightWheelDirection0, LOW);
    digitalWrite(rightWheelDirection1, HIGH);
    analogWrite(leftWheel, wheelSpeed);
    analogWrite(rightWheel, wheelSpeed);
}


void turnLeft(unsigned char leftWheelSpeed, unsigned char rightWheelSpeed) {

    digitalWrite(leftWheelDirection0, LOW);
    digitalWrite(leftWheelDirection1, HIGH);
    digitalWrite(rightWheelDirection0, HIGH);
    digitalWrite(rightWheelDirection1, LOW);
    analogWrite(leftWheel, leftWheelSpeed);
    analogWrite(rightWheel, rightWheelSpeed);
}


void turnRight(unsigned char leftWheelSpeed, unsigned char rightWheelSpeed) {

    digitalWrite(leftWheelDirection0, HIGH);
    digitalWrite(leftWheelDirection1, LOW);
    digitalWrite(rightWheelDirection0, LOW);
    digitalWrite(rightWheelDirection1, HIGH);
    analogWrite(leftWheel, leftWheelSpeed);
    analogWrite(rightWheel, rightWheelSpeed);
}
