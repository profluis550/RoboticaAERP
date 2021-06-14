#include <Ultrasonic.h>
#include <DFPlayerMini_Fast.h>
#include <SoftwareSerial.h>

SoftwareSerial mp3Serial(10, 11); // RX, TX
DFPlayerMini_Fast myMP3;

#define redPin A1
#define greenPin A3
#define bluePin A2

#define motorEsq1 6
#define motorEsq2 7
#define motorEsqVel 5

#define motorDir1 8
#define motorDir2 A0
#define motorDirVel 3
#define TRIGGER_PIN 2
#define ECHO_PIN 4

Ultrasonic ultrasonic (TRIGGER_PIN, ECHO_PIN);

//SoftwareSerial mySerial(A5, A4); // RX, TX

char opcao;
int distancia;
long randNum, tempo;

void setup() {
  // put your setup code here, to run once:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(motorEsq1, OUTPUT);
  pinMode(motorEsq2, OUTPUT);
  pinMode(motorEsqVel, OUTPUT);

  pinMode(motorDir1, OUTPUT);
  pinMode(motorDir2, OUTPUT);
  pinMode(motorDirVel, OUTPUT);

  Serial.begin(9600);
  randomSeed(analogRead(5));

  mp3Serial.begin(9600);
  myMP3.begin(mp3Serial, true);

  //Serial.println("Setting volume to max");
  myMP3.volume(30);
  corOlhos(0, 0, 255);
  moveStop();
}

void loop() {
  // put your main code here, to run repeatedly:
  //corOlhos(0, 0, 255);

  if (Serial.available() > 0) {
    opcao = Serial.read();
    Serial.println(opcao);
    switch (opcao) {
      case 'F':
        corOlhos(0, 0, 255);
        myMP3.stop();
        moveStop();
        setSpeedM(150, 150);
        moveF();
        break;
      case 'S':
        corOlhos(0, 0, 255);
        myMP3.stop();
        moveStop();
        break;
      case 'L':
        corOlhos(0, 0, 255);
        myMP3.stop();
        moveStop();
        setSpeedM(0, 150);
        moveL();
        break;
      case 'R':
        corOlhos(0, 0, 255);
        myMP3.stop();
        moveStop();
        setSpeedM(150, 0);
        moveR();
        break;
      case 'B':
        corOlhos(0, 0, 255);
        myMP3.stop();
        moveStop();
        setSpeedM(150, 150);
        moveB();
        break;
      case '1':
        //nome
        corOlhos(0, 0, 255);
        moveStop();
        myMP3.play(1);
        break;
      case '2':
        //Dançar
        corOlhos(0, 0, 255);
        moveStop();
        dancar();
        break;
      case '3':
        //Brincar
        corOlhos(0, 0, 255);
        moveStop();
        myMP3.play(8);
        break;
      case '4':
        //Andar Sozinho
        corOlhos(0, 0, 255);
        moveStop();
        myMP3.play(3);
        delay(6000);
        do {
          autonomo();
          opcao = Serial.read();
          if (opcao != -1)
            break;
        } while (true);
        break;
      case '5':
        //Musica
        corOlhos(0, 0, 255);
        moveStop();
        musica();
        break;
      case '6':
        //Amigo
        corOlhos(0, 0, 255);
        moveStop();
        myMP3.play(6);
        delay(5000);
        corOlhos(255, 0, 0);
        break;
      case '7':
        //Cor Olhos
        corOlhos(0, 0, 255);
        moveStop();
        myMP3.play(5);
        mudaOlhos();
        break;
      case '8':
        //Sono
        corOlhos(0, 0, 255);
        moveStop();
        myMP3.play(2);
        delay(8000);
        corOlhos(0, 0, 0);
        delay(100);
        do {
          myMP3.loop(11);
          opcao = Serial.read();
        } while (opcao == '8');
        break;
      case '9':
        //Dorminhoco
        corOlhos(0, 0, 255);
        moveStop();
        myMP3.play(4);
        break;
      case '0':
        //Fome
        corOlhos(0, 0, 255);
        moveStop();
        myMP3.play(9);
        break;
      case 'X':
        corOlhos(0, 0, 255);
        myMP3.stop();
        moveStop();
        do {
          autonomo();
          opcao = Serial.read();
        } while (opcao != 'F' && opcao != 'B' && opcao != 'L' && opcao && 'R');
        break;
    }
  }

}

void moveF () {

  digitalWrite(motorEsq1, HIGH);
  digitalWrite(motorEsq2, LOW);
  digitalWrite(motorDir1, HIGH);
  digitalWrite(motorDir2, LOW);

}

void moveB () {

  digitalWrite(motorEsq1, LOW);
  digitalWrite(motorEsq2, HIGH);
  digitalWrite(motorDir1, LOW);
  digitalWrite(motorDir2, HIGH);
}

void moveR () {

  digitalWrite(motorEsq1, HIGH);
  digitalWrite(motorEsq2, LOW);
  digitalWrite(motorDir1, LOW);
  digitalWrite(motorDir2, LOW);

}

void moveL () {

  digitalWrite(motorEsq1, LOW);
  digitalWrite(motorEsq2, LOW);
  digitalWrite(motorDir1, HIGH);
  digitalWrite(motorDir2, LOW);
}

void moveStop() {
  digitalWrite(motorEsq1, LOW);
  digitalWrite(motorEsq2, LOW);
  digitalWrite(motorDir1, LOW);
  digitalWrite(motorDir2, LOW);
}

void autonomo() {

  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  tempo = pulseIn(ECHO_PIN, HIGH);
  // Calculating the distance
  distancia = tempo * 0.034 / 2;
  Serial.println(distancia);

  moveF();
  setSpeedM(150, 120);

  if (distancia < 25) {
    moveStop();
    setSpeedM(0, 0);
    delay(500);
    randNum = random(0, 2);
    if (randNum == 0)
    {
      moveB();
      setSpeedM(150, 150);
      delay(1000);
      moveL();
      setSpeedM(0, 150);
      delay(900);

    } else {
      moveB();
      setSpeedM(150, 150);
      delay(1000);
      moveR();
      setSpeedM(150, 0);
      delay(900);
    }
  }
}

void setSpeedM(int speedl, int speedr) {
  analogWrite(motorEsqVel, speedl);
  analogWrite(motorDirVel, speedr);
}

void mudaOlhos() {
  delay(3000);
  corOlhos(255, 0, 0);
  delay(1500);
  corOlhos(0, 255, 0);
  delay(1500);
  corOlhos(255, 0, 128);
  delay(1500);
  corOlhos(0, 0, 255);
}


void corOlhos(int r, int g, int b) {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}

void dancar() {
  myMP3.play(10);
  delay(4000);
  myMP3.loop(12);
  do {
    setSpeedM(150, 150);
    moveF();
    delay(1000);
    opcao = Serial.read();
    if (opcao != -1)
      break;

    setSpeedM(150, 150);
    moveB();
    delay(1000);
    opcao = Serial.read();
    if (opcao != -1)
      break;

    setSpeedM(0, 150);
    moveL();
    delay(1500);
    opcao = Serial.read();
    if (opcao != -1)
      break;

    setSpeedM(150, 0);
    moveR();
    delay(1500);
    opcao = Serial.read();
    if (opcao != -1)
      break;
  } while (true);

}

void musica() {
  myMP3.play(7);
  delay(8000);
  randNum = random(0, 3);
  Serial.println(randNum);
  switch (randNum) {
    case 0:
      myMP3.play(13);
      break;
    case 1:
      myMP3.play(14);
      break;
    case 2:
      myMP3.play(15);
      break;
  }
}
