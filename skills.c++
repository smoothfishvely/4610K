/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Student                                          */
/*    Created:      Mon Nov 20 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// puncherLeft          motor         18              
// puncherRight         motor         12              
// leftFront            motor         14              
// leftBack             motor         19              
// rightFront           motor         17              
// rightBack            motor         5               
// intakeMotor          motor         16              
// rakeWithK            motor         7               
// Controller1          controller                    
// gyroK                inertial      10              
// knooMatics           digital_out   A               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

competition Competition;

// leftFront            motor         14              
// rightFront           motor         17              
// leftBack             motor         19              
// rightBack            motor         20              
// intakeMotor          motor         2               
// puncherRight         motor         12              
// topFly               motor         15              
// rakeWithK            motor         7               
// gyroK                inertial      10              
// knooMatics1          digital_out   A               
// knooMatics2          digital_out   B               
// Controller1          controller                    
// puncherLeft          motor         18            

void autonRakeDown(){
  rakeWithK.spin(reverse,100,pct);
  rakeWithK.setStopping(coast);
  wait(0.5,sec);
  rakeWithK.stop();
}

void autonRakeUp(float seconds){
  rakeWithK.spin(forward,50,pct);
  rakeWithK.setStopping(hold);
  wait(seconds,sec);
  rakeWithK.stop();
}

//USE THIS LEFT
void turnLeft(int target){
  gyroK.resetRotation();
  wait(25, msec);

  while(gyroK.rotation(degrees) > target){
    float error = -target + gyroK.rotation(degrees);
    float kp = 0.28;
    float minimumSpeed = 4;
    float speed = error * kp + minimumSpeed;

    leftFront.spin(reverse, speed, pct);
    rightFront.spin(fwd, speed, pct);
    leftBack.spin(reverse, speed, pct);
    rightBack.spin(fwd, speed, pct);
  }

  leftFront.setStopping(brake);
  rightFront.setStopping(brake);
  leftBack.setStopping(brake);
  rightBack.setStopping(brake);
  leftFront.stop();
  rightFront.stop();
  leftBack.stop();
  rightBack.stop();

  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("tessa is cool");
}
//USE THIS RIGHT
void turnRight(int target){
  gyroK.resetRotation();
  wait(25, msec);

  while(gyroK.rotation(degrees) < target){
    float error = target - gyroK.rotation(degrees);
    float kp = .28;
    float minimumSpeed = 4;
    float speed = error * kp + minimumSpeed;
    
    leftFront.spin(fwd, speed, pct);
    leftBack.spin(fwd, speed, pct);
    rightFront.spin(reverse, speed, pct);
    rightBack.spin(reverse, speed, pct);
  }

  leftFront.setStopping(brake);
  leftBack.setStopping(brake);
  rightBack.setStopping(brake);
  rightFront.setStopping(brake);
  leftFront.stop();
  leftBack.stop();
  rightFront.stop();
  rightBack.stop();
}

void awesomeInertial(){
  gyroK.calibrate();
  while(gyroK.isCalibrating()){
    wait(100,msec);
  }
  rakeWithK.setStopping(hold);
}

void autonIntakeIn(double time){
  intakeMotor.spin(reverse,100,percent);
  wait(time,seconds);
  intakeMotor.stop();
}

void autonIntakeOut(double time){
  intakeMotor.spin(forward,100,percent);
  wait(time,seconds);
  intakeMotor.stop();
}

void move(double distance,int velocity){
  leftFront.setPosition(0,degrees);
  while(leftFront.position(degrees)<distance){
    leftFront.spin(forward,velocity,percent);
    leftBack.spin(forward,velocity,percent);
    rightFront.spin(forward,velocity,percent);      
    rightBack.spin(forward,velocity,pct);
    wait(10,msec);
    }
  leftFront.stop();
  rightFront.stop();
  rightBack.stop();
  leftBack.stop();
}

void moveBack(double distance,int velocity,float kp){
  leftFront.setPosition(0,degrees);
  double heading=gyroK.rotation(degrees);
  if(velocity>0){
    while(fabs(leftFront.position(degrees))<distance){
      double error=heading-gyroK.rotation(degrees);
      double output=error*kp;
      leftFront.spin(reverse,velocity-output,percent);
      leftBack.spin(reverse,velocity-output,percent);
      rightFront.spin(reverse,velocity+output,percent);
      rightBack.spin(reverse,velocity+output,pct);
      wait(10,msec);
    }
  }
  leftFront.stop();
  rightFront.stop();
  rightBack.stop();
  leftBack.stop();
}

//forward
void anika(double dist, int max, int min) {   //inches
    //Drive Forward Proportional
    leftFront.resetPosition();
  /*
    //Convert Inches to Motor Encoder Degrees
    double w_radius = 4.0 / 2.0; //wheel
    double r_conv = 3.14159 / 180.0; //radian conversion
    double gear_ratio = 48.0 / 72.0; //drive train gear ratio*/
    double target = dist; /// (r_conv * w_radius * gear_ratio);

    while(leftFront.position(degrees) < target) {
        double proportion = target - leftFront.position(degrees); 
        double kp = .6;
        double min_speed = min;
        double max_speed = max;
        double speed = proportion * kp + min_speed; //one way to break out of the loop

        if (speed > 100) speed = 100;     // In old IQ Speed over 100 results in no movement (velocity cannot be > 100)
        if (speed > max_speed) speed = max_speed;     // In old IQ Speed over 100 results in no movement (velocity cannot be > 100)

        leftFront.spin(fwd, speed, pct);
        rightFront.spin(fwd, speed, pct);
        leftBack.spin(fwd, speed, pct);
        rightBack.spin(fwd, speed, pct);

    }

    //stopping with break may allow kp and/or minspeed to be higher
    leftFront.setStopping(brake);
    rightFront.setStopping(brake);
    leftBack.setStopping(brake);
    rightBack.setStopping(brake);

    leftFront.stop();
    rightFront.stop();
    leftBack.stop();
    rightBack.stop();

    //put breaking back to coast after hanging out
    wait(25, msec);

    leftFront.setStopping(coast);
    rightFront.setStopping(coast);
    leftBack.setStopping(coast);
    rightBack.setStopping(coast);
}

//reverse
void arushi(double dist, int max, int min) {   //inches
    //Drive Forward with Proportional Stop
    leftFront.resetPosition();
  
    double target = dist;

    while(leftFront.position(degrees) > -target) {
        double proportion = target - leftFront.position(degrees); 
        double kp = .6;
        double min_speed = min;
        double max_speed = max;
        double speed = proportion * kp + min_speed; //one way to break out of the loop

        if (speed > 100) speed = 100;     // In old IQ Speed over 100 results in no movement (velocity cannot be > 100)
        if (speed > max_speed) speed = max_speed;     // In old IQ Speed over 100 results in no movement (velocity cannot be > 100)

        leftFront.spin(reverse, speed, pct);
        rightFront.spin(reverse, speed, pct);
        leftBack.spin(reverse, speed, pct);
        rightBack.spin(reverse, speed, pct);

    }

    //stopping with break may allow kp and/or minspeed to be higher
    leftFront.setStopping(brake);
    rightFront.setStopping(brake);
    leftBack.setStopping(brake);
    rightBack.setStopping(brake);

    leftFront.stop();
    rightFront.stop();
    leftBack.stop();
    rightBack.stop();

    //put breaking back to coast after hanging out
    wait(25, msec);

    leftFront.setStopping(coast);
    rightFront.setStopping(coast);
    leftBack.setStopping(coast);
    rightBack.setStopping(coast);
}

void tessa(float ms, int speed){
  leftFront.spin(fwd, speed, pct);
  rightFront.spin(fwd, speed, pct);
  leftBack.spin(fwd, speed, pct);
  rightBack.spin(fwd, speed, pct);
  wait(ms,msec);
  
  leftFront.stop();
  rightFront.stop();
  leftBack.stop();
  rightBack.stop();
}

void autonomous(void) {
  // ..........................................................................
  autonRakeDown();
  puncherRight.spin(forward,45,pct);
  puncherLeft.spin(forward,45,pct);
  wait(4,sec);
  //done match loading

  //stop puncher, lift rake
  puncherRight.stop();
  puncherLeft.stop();
  autonRakeUp(2);
  
  //adjust position and move forward
  turnLeft(-5);
  anika(500, 80, 20);

  //robot is facing forward 
  turnRight(45);
  //move to bar
  anika(210, 20, 5);
  wait(20, msec);

  //turn to clear
  turnLeft(-90);
  wait(20, msec);
  anika(400, 20, 5);
  autonIntakeOut(0.7);
  //backwards
  arushi(310, 20, 5);
  turnRight(90);
  arushi(410, 30, 5);
  tessa(2500,100);
  knooMatics.set(true);
  arushi(500, 60, 7);
  tessa(2800,100);
  turnRight(10);
  knooMatics.set(false);
  arushi(70, 20, 5);



  /*
  //possible go over
  tessa(1500,100);
  wait(10,msec);
  arushi(300, 80, 15);

  wait(20,msec);
  knooMatics.set(true);'
  */

  /*
  //second go over chance
  tessa(1500, 100);
  turnRight(15);
  wait(20,msec);
  tessa(500, 90);
  knooMatics.set(false);
  arushi(300, 80, 15);
  wait(20,msec);
  knooMatics.set(true);
  tessa(250, 70);
  wait(50,msec);
  knooMatics.set(false);
  arushi(300, 80, 15);
  wait(20,msec);
  knooMatics.set(true);
  anika(400, 80, 20);
  */
  // ..........................................................................
}

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}


void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  awesomeInertial();
  vexcodeInit();
  
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
  while(true){
    wait(100,msec);
  }
}
