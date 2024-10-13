/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       smoot                                                     */
/*    Created:      9/15/2024, 9:35:11 AM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

competition Competition;

brain  Brain;
controller Controller1 = controller(primary);

//for 4610K robot
motor leftFront = motor(PORT7, ratio18_1, false);
motor rightFront = motor(PORT12, ratio18_1, true);
motor leftMiddle = motor(PORT19, ratio18_1, false);
motor rightMiddle = motor(PORT11, ratio18_1, true);
motor leftBack = motor(PORT15, ratio18_1, false);
motor rightBack = motor(PORT8, ratio18_1, true);
digital_out mm1 = digital_out(Brain.ThreeWirePort.A);
digital_out mm2 = digital_out(Brain.ThreeWirePort.B);
motor intake = motor(PORT17, ratio18_1, true);
motor belt = motor(PORT1, ratio18_1, true);

inertial aniNertial = inertial(PORT18);

extern brain Brain;
extern controller Controller1;
extern motor leftFront;
extern motor rightFront;
extern motor leftBack;
extern motor rightBack;
extern motor rightMiddle;
extern motor leftMiddle;
extern digital_out mm1;
extern digital_out mm2;
extern inertial aniNertial;
extern motor intake;
extern motor belt;

//aniGle is the global angle! (named after anika obv)
int aniGle = 0;

void pre_auton(void) {
  aniNertial.calibrate();
  aniNertial.resetRotation();
}

void getDonuts(double time){
  intake.spin(fwd, 50, pct);
  wait(time, msec);
  intake.stop();
}

//tune kp for robot (same for right turns!)
//change minSpeed
void turnL(int target){
  aniGle = target;
  double error;
  double deriviative;
  double kd = .2;

  while(aniNertial.rotation(degrees) > aniGle + .5){
    double prevErr = error;
    error = abs(target - aniNertial.rotation(degrees));
    deriviative = error - prevErr;
    double kp = .3;
    double minSpeed = 5;
    double speed = error * kp + deriviative * kd + minSpeed;

    leftFront.spin(reverse, speed, pct);
    rightFront.spin(fwd, speed, pct);
    rightMiddle.spin(fwd, speed, pct);
    leftBack.spin(reverse, speed, pct);
    rightBack.spin(fwd, speed, pct);
    leftMiddle.spin(reverse, speed, pct);
    wait(10,msec);
  }

  leftFront.setStopping(brake);
  rightFront.setStopping(brake);
  leftBack.setStopping(brake);
  rightBack.setStopping(brake);
  leftMiddle.setStopping(brake);
  rightMiddle.setStopping(brake);

  leftFront.stop();
  leftMiddle.stop();
  rightMiddle.stop();
  rightFront.stop();
  leftBack.stop();
  rightBack.stop();
  wait(200, msec);
}

void turnR(int target){
  aniGle = target;
  double error;
  double deriviative;
  double kd = .2;

  while(aniNertial.rotation(degrees) < aniGle - .5){
    double prevErr = error;
    error = target - aniNertial.rotation(degrees);
    deriviative = error - prevErr;
    double kp = .3;
    double minSpeed = 5;
    double speed = error * kp + deriviative * kd + minSpeed;
    
    leftFront.spin(fwd, speed, pct);
    leftBack.spin(fwd, speed, pct);
    leftMiddle.spin(fwd, speed, pct);
    rightFront.spin(reverse, speed, pct);
    rightBack.spin(reverse, speed, pct);
    rightMiddle.spin(reverse, speed, pct);
    wait(10,msec);
  }

  leftFront.setStopping(brake);
  leftBack.setStopping(brake);
  rightBack.setStopping(brake);
  rightMiddle.setStopping(brake);
  leftMiddle.setStopping(brake);
  rightFront.setStopping(brake);

  leftFront.stop();
  leftBack.stop();
  rightFront.stop();
  leftMiddle.stop();
  rightMiddle.stop();
  rightBack.stop();
  wait(200,msec);
}

//minimum and maximum paramaters for different scenarios
void moveF(double target, int min) { 
  leftFront.resetPosition();
  rightFront.resetPosition();
  double deriviative;
  double error = target - (leftFront.position(degrees)+rightFront.position(degrees))/2; 
  double kd = .2;

  while((leftFront.position(degrees)+rightFront.position(degrees))/2 < target) {
    double prevErr = error;
    error = target - (leftFront.position(degrees)+rightFront.position(degrees))/2; 
    double kp = .3;
    deriviative = error - prevErr;
    double speed = error * kp + deriviative * kd + min; 
    int max = 100;
    if(speed > max){
      speed = max;
    }
    leftFront.spin(fwd, speed, pct);
    rightFront.spin(fwd, speed, pct);
    wait(10, msec);
  }

  leftFront.setStopping(brake);
  rightFront.setStopping(brake);
  leftFront.stop();
  rightFront.stop();

  leftFront.setStopping(coast);
  rightFront.setStopping(coast);
  wait(200, msec);
}

void moveR(double target, int min){
  leftFront.resetPosition();
  rightFront.resetPosition();
  double deriviative;
  double error = target - (leftFront.position(degrees)+rightFront.position(degrees))/2;
  double kd = .2;

  while((leftFront.position(degrees)+rightFront.position(degrees))/2 > -target) {
    double prevErr = error;
    error = target - (leftFront.position(degrees)+rightFront.position(degrees))/2; 
    double kp = .3;
    double speed = error * kp + min; 
    int max = 100;
    if(speed > max){
      speed = max;
    }
    leftFront.spin(fwd, -speed, pct);
    rightFront.spin(fwd, -speed, pct);
    wait(10,msec);
  }

  leftFront.setStopping(brake);
  rightFront.setStopping(brake);
  leftFront.stop();
  rightFront.stop();

  leftFront.setStopping(coast);
  rightFront.setStopping(coast);
  wait(200, msec);
}

/*At least three (3) Scored Rings of the Alliance's color
A minimum of two (2) Stakes on the Alliance's side of the Autonomous Line with at least (1) Ring of the Alliance's color Scored
Neither Robot contacting / breaking the plane of the Starting Line
At least One (1) Robot contacting the Ladder */

void awp(){
  //starting parallel to the mogo on the right side, move forward and grab the mogo
  //knock over piles and get the blue rings
  //touch the ladder
  moveF(1050, 10);
}

void codingChallenge(){
  //24 fwd, right 45, 12 rev, left 90
  moveF(1050, 10);
  turnL(-45);
  moveR(700, 10);
  turnR(45);
}

void twofivezeroninea(){
  //from the finals at highlander summit
  //blue right
  moveF(1500, 10);
  turnR(45);
  moveF(525, 10);
  turnR(90);
  moveR(1500, 10);
  turnR(180);
}

void foursixtenc(){
  //blue left
  //back up 2 squares
  moveR(2100, 10);
  //turn right 45
  turnR(45);
  //reverse 1/2 square
  moveR(500, 10);
  //forward 2 squares
  moveF(2100, 10);
  //reverse a little
  moveR(100, 10);
  //180 left
  turnL(-90);
  //forward 2 squares
  moveF(2100, 10);
  //right 75
  turnR(-15);
  //forward to corner
  moveF(1700, 10);
  //reverse a little
  moveR(200, 10);
  //right 180
  turnR(165);
  //forward across the field
  moveF(5250, 10);
}

void oneonesixeighta(){
  //move forward a little bit
  moveF(200, 10);
  //right 45 
  turnR(45);
  //move back a little bit
  moveR(200, 10);
  //forward a little bit
  moveF(200, 10);
  // left back to 0
  turnL(0);
  //forward 2 squares
  moveF(2000, 10);
  //turn to -90
  turnL(-90);
  //reverse 2 squares
  moveR(2000, 10);
  //turns left to -45
  turnL(-45);
  //forward to the bar
  moveF(2000, 10);

}

void onesixtyninetyninec(){
  //right 15
  turnR(15);
  //reverse 1 square
  moveR(1000, 10);
  //left -15
  turnL(-15);
  //reverse 1 square
  moveR(1000, 10);
  //turn right 90
  turnR(90);
  //forward 2 squares
  moveF(2000, 10);
  //right 180
  turnR(180);
  //forward little
  moveF(200, 10);
  //left 125
  turnL(125);
  //reverse a little
  moveR(200, 10);
  //back to 180
  turnR(180);
  //forward little
  moveF(200, 10);
  //left 125
  turnL(125);
  //reverse all the way back
  moveR(5000, 10);
  //a little forward
  moveF(200, 10);
  //left 15
  turnL(15);
}

void autonomous(void) {
}

bool clamp = false;

void drive(){
  while(true) {
    //drive
    leftFront.spin(fwd, Controller1.Axis3.position() + (Controller1.Axis1.position()/3), pct);
    leftBack.spin(fwd, Controller1.Axis3.position() + (Controller1.Axis1.position()/3), pct);
    rightFront.spin(fwd, Controller1.Axis3.position() - (Controller1.Axis1.position()/3), pct);
    rightBack.spin(fwd, Controller1.Axis3.position() - (Controller1.Axis1.position()/3), pct);   
    leftMiddle.spin(fwd, Controller1.Axis3.position() + (Controller1.Axis1.position()/3), pct);
    rightMiddle.spin(fwd, Controller1.Axis3.position() - (Controller1.Axis1.position()/3), pct);
  }

  if(Controller1.ButtonR1.pressing()){
    intake.spin(fwd, 100, pct);
    belt.spin(fwd, 100, pct);
  } else if(Controller1.ButtonR2.pressing()){
    intake.spin(reverse, 100, pct);
    belt.spin(reverse, 100, pct);
  } else{
    intake.stop();
    belt.stop();
  }
  
  if(Controller1.ButtonL1.pressing() and clamp == false){
    clamp = true;
    mm1.set(true);
    mm2.set(true);
  }

  if(Controller1.ButtonL1.pressing() and clamp == true){
    clamp = false;
    mm1.set(false);
    mm2.set(false);
  }

  wait(50, msec);
}

void usercontrol(void) {
  while (1) {
    aniNertial.calibrate();
    wait(3, sec);
    aniNertial.resetRotation();
    turnR(90);
    turnL(0);
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while (true) {
    wait(100, msec);
  }
}
