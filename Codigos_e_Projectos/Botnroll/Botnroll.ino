#include <SoftwareSerial.h>
#include <Ultrasonic.h>
#include <BnrOneA.h>   // Bot'n Roll ONE A library
#include <EEPROM.h>    // EEPROM reading and writing
#include <SPI.h>       // SPI communication library required by BnrOne.cpp
BnrOneA one;           // declaration of object variable to control the Bot'n Roll ONE A

//constants definition
#define SSPIN  2       // Slave Select (SS) pin for SPI communication

#define LEFT_TRIG A4
#define LEFT_ECHO A5
#define CENTER_TRIG A2
#define CENTER_ECHO A3
#define RIGHT_TRIG A0
#define RIGHT_ECHO A1

Ultrasonic leftUltra (LEFT_TRIG, LEFT_ECHO);
Ultrasonic centerUltra (CENTER_TRIG, CENTER_ECHO);
Ultrasonic rightUltra (RIGHT_TRIG, RIGHT_ECHO);

SoftwareSerial mySerial(6, 7); // RX, TX

char opcao;
float leftDistance, centerDistance, rightDistance;
long randNum;


void setup()
{
  Serial.begin(9600);     // set baud rate to 57600bps for printing values at serial monitor.
  mySerial.begin(9600);
  one.spiConnect(SSPIN);   // start SPI communication module
  one.stop();              // stop motors
  randomSeed(analogRead(6));
}

void loop()
{
  if (mySerial.available() > 0) {
    opcao = mySerial.read();
    Serial.println(opcao);
    switch (opcao) {
      case 'F':
        one.lcd2("    Forward ");
        one.move(50, 50);
        break;
      case 'S':
        one.lcd2("     Stop   ");
        one.stop();               // Stop Motors
        break;
      case 'L':
        one.lcd2("  Rotate Left ");
        one.move(-50, 50);        //Rotate Left
        break;
      case 'R':
        one.lcd2("  Rotate Right ");
        one.move(50, -50);        // Rotate Right
        break;
      case 'B':
        one.lcd2("   Backwards ");
        one.move(-50, -50);     // Backwards
        break;
      case 'X':
        do {
          autonomo();
          opcao = mySerial.read();
        } while (opcao != 'F' && opcao != 'B' && opcao != 'L' && opcao && 'R');
        break;
    }
  }
}


void autonomo() {

  leftDistance = leftUltra.convert(leftUltra.timing(), Ultrasonic::CM);
  centerDistance = centerUltra.convert(centerUltra.timing(), Ultrasonic::CM);
  rightDistance = rightUltra.convert(rightUltra.timing(), Ultrasonic::CM);
  //  Serial.print(leftDistance);
  //  Serial.print("\t");
  //  Serial.print(centerDistance);
  //  Serial.print("\t");
  //  Serial.println(rightDistance);
  one.lcd2("    Forward ");
  one.move(50, 50);

  if (leftDistance < 25 || centerDistance < 25 || rightDistance < 25) {
    one.lcd2("     Stop   ");
    one.stop();               // Stop Motors

    delay(500);
    randNum = random(0, 2);
    if (randNum == 0)
    {
      one.lcd2("   Backwards ");
      one.move(-50, -50);     // Backwards
      delay(500);
      one.lcd2("  Rotate Left ");
      one.move(-50, 50);        //Rotate Left
      delay(300);

    } else {
      one.lcd2("   Backwards ");
      one.move(-50, -50);     // Backwards
      delay(500);
      one.lcd2("  Rotate Right ");
      one.move(50, -50);        // Rotate Right
      delay(300);
    }
  }
}
