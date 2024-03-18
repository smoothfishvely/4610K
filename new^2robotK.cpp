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
// Controller1          controller                    
// leftFront            motor         14              
// rightFront           motor         17              
// leftBack             motor         19              
// rightBack            motor         5               
// intakeMotor          motor         16              
// puncherLeft          motor         18              
// topFly               motor         15              
// rakeWithK            motor         7               
// gyroK                inertial      10              
// knooMatics1          digital_out   A               
// knooMatics2          digital_out   B               
// puncherRight         motor         12              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

competition Competition;

/*
int flyWheel(){
  int flyControl = 0;
  while(true){
    if(Controller1.ButtonB.pressing()){
      if(flyControl == 0){
        topFly.spin(forward,100,pct);
        bottomFly.spin(reverse,100,pct);
        flyControl++;
      } else{
        topFly.stop();
        bottomFly.stop();
        flyControl--;
      }
    }
  }
}
*/

int intake(){
  while(true){
    if(Controller1.ButtonR2.pressing()){
      intakeMotor.spin(forward,100,pct);
    }
    else if(Controller1.ButtonR1.pressing()){
      intakeMotor.spin(reverse,100,pct);
    }
    else{
    intakeMotor.stop();
    }
    wait(20,msec);
  }
}

int splitDrive(){
  while(true){
    leftFront.spin(forward, Controller1.Axis3.position()+Controller1.Axis1.position(),pct);
    leftBack.spin(forward, Controller1.Axis3.position()+Controller1.Axis1.position(),pct);
    rightFront.spin(forward, Controller1.Axis3.position()-Controller1.Axis1.position(),pct);      
    rightBack.spin(forward,Controller1.Axis3.position()-Controller1.Axis1.position(),pct);
    wait(20,msec);
  }
}

int knooMatics(){
  int knoo = 0;
  while(true){
    if(Controller1.ButtonY.pressing()){
      while(Controller1.ButtonY.pressing()){
        wait(20,msec);
      } 
      knoo++;
      if(knoo > 1){
        knoo = 0;
      }

      if(knoo == 0){
        knooMatics1.set(true);
        knooMatics2.set(true);
      } else{
        knooMatics1.set(false);
        knooMatics2.set(false);
      }
    }
  }
}

int knoo1(){
  int matics = 0;
  while(true){
    if(Controller1.ButtonY.pressing()){
      while(Controller1.ButtonY.pressing()){
        wait(20,msec);
      } 

      matics++;
      if(matics > 1){
        matics = 0;
      }

      if(matics == 0){
        knooMatics1.set(true);
      }
      if(matics == 1){
        knooMatics1.set(false);
      }
    }
  }
}

int knoo2(){
  int k = 0;
  while(true){
    if(Controller1.ButtonX.pressing()){
      while(Controller1.ButtonX.pressing()){
        wait(20,msec);
      } 
      k++;
      if(k > 1){
        k = 0;
      }

      if(k == 0){
        knooMatics2.set(true);
      } else{
        knooMatics2.set(false);
      }
    }
  }
}

int knooMatics3(){
  while(true){
    while(Controller1.ButtonL2.pressing()){
      knooMatics1.set(true);
      knooMatics2.set(true);
    }
    while(Controller1.ButtonL1.pressing()){
      knooMatics1.set(false);
      knooMatics2.set(false);
    }
  }
}

// I'm impressed you figured out this was a viable way to run a drive program, although I'd like to note it is innefficient.
// Running everything in one while loop is much easier on the bot and your computer's memory.
// I'm assuming you were not taught how to include additional controls for a drive program so not knowing to do what I did is not your fault at all. 
// Good luck at the competition, K!


bool punchControl = false;

int kick(){
  while(true){
    if(Controller1.ButtonB.pressing()){
      punchControl = !punchControl;
    }
    if(punchControl == true){
      kickerRight.spin(forward,90,pct);
      kickerLeft.spin(forward, 90, pct);
    }
    if(punchControl == false){
      kickerRight.setStopping(coast);
      kickerLeft.setStopping(coast);
      kickerRight.stop();
      kickerLeft.stop();
    }
    wait(80,msec);
  }
}

bool matics1 = false;
bool matics2 = false;
bool wingButton = false;

//USE THIS DRIVE
void DeviDrive(){
  while(true) {
    thread k (kick);
    //drive
    leftFront.spin(forward, Controller1.Axis3.position() + (Controller1.Axis1.position()/2), pct);
    leftBack.spin(forward, Controller1.Axis3.position() + (Controller1.Axis1.position()/2), pct);
    rightFront.spin(forward, Controller1.Axis3.position() - (Controller1.Axis1.position()/2), pct);
    rightBack.spin(forward, Controller1.Axis3.position() - (Controller1.Axis1.position()/2), pct);   
    leftMiddle.spin(forward, Controller1.Axis3.position() + (Controller1.Axis1.position()/2), pct);
    rightMiddle.spin(forward, Controller1.Axis3.position() - (Controller1.Axis1.position()/2), pct);
  
    

    //later change this to using both back wings
    if(Controller1.ButtonL2.pressing() and wingButton == false){
      wingButton = true;
      knooMatics1.set(true);
      knooMatics2.set(true);
    }

    if(Controller1.ButtonL2.pressing() and wingButton == true){
      wingButton = false;
      knooMatics1.set(false);
      knooMatics2.set(false);
    }

    //later change this to using both front wings
    /*
    if(Controller1.ButtonL1.pressing()){
      while(Controller1.ButtonL1.pressing()){
        wait(10, msec);
      }
      matics2 = !matics2;
    }
    if(matics2 == true){
      knooMatics2.set(true);
    } 
    if(matics2 == false){
      knooMatics2.set(false);
    }
*/
        //intake
    if(Controller1.ButtonR2.pressing()) {
      intakeMotor.spin(forward, 100, pct);
    } else if(Controller1.ButtonR1.pressing()) {
      intakeMotor.spin(reverse, 100, pct);
    } else {
      intakeMotor.stop();
    }

    wait(80, msec); 
  } 
}

//ALL CODE UP HERE IS DRIVE CODE
//-----------------------------------------------------------------------------------------
//ALL CODE DOWN HERE IS FOR AUTON



//USE THIS LEFT
void pidAttemptL(int target){

}

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
    rightMiddle.spin(fwd, speed, pct);
    leftBack.spin(reverse, speed, pct);
    rightBack.spin(fwd, speed, pct);
    leftMiddle.spin(reverse, speed, pct);
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
    leftMiddle.spin(fwd, speed, pct);
    rightFront.spin(reverse, speed, pct);
    rightBack.spin(reverse, speed, pct);
    rightMiddle.spin(reverse, speed, pct);
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
}

int autonNumber = 0;

void awesomeInertial(){
  gyroK.calibrate();
  while(true){
    wait(10,msec);
    if(selectorSensor.pressing()){
      while(selectorSensor.pressing()){
        wait(10,msec);
      }
      autonNumber++;
      Brain.Screen.print("anika");
    }
  }
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

//we don't use this, it is not updated
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

//not updated don't use
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
void driveForward(double dist, int max, int min) {   //inches
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
        rightMiddle.spin(fwd, speed, pct);
        leftMiddle.spin(fwd, speed, pct);
        leftBack.spin(fwd, speed, pct);
        rightBack.spin(fwd, speed, pct);

    }

    //stopping with break may allow kp and/or minspeed to be higher
    leftFront.setStopping(brake);
    rightFront.setStopping(brake);
    leftBack.setStopping(brake);
    rightBack.setStopping(brake);
    leftMiddle.setStopping(brake);
    rightMiddle.setStopping(brake);

    leftMiddle.stop();
    rightMiddle.stop();
    leftFront.stop();
    rightFront.stop();
    leftBack.stop();
    rightBack.stop();

    //put breaking back to coast after hanging out
    wait(25, msec);

    leftFront.setStopping(coast);
    rightFront.setStopping(coast);
    leftMiddle.setStopping(coast);
    rightMiddle.setStopping(coast);
    leftBack.setStopping(coast);
    rightBack.setStopping(coast);
}

//reverse
void driveReverse(double dist, int max, int min) {   //inches
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
        leftMiddle.spin(reverse, speed, pct);
        rightMiddle.spin(reverse, speed, pct);

    }

    //stopping with break may allow kp and/or minspeed to be higher
    leftFront.setStopping(brake);
    rightFront.setStopping(brake);
    leftBack.setStopping(brake);
    rightBack.setStopping(brake);
    rightMiddle.setStopping(brake);
    leftMiddle.setStopping(brake);

    leftFront.stop();
    leftMiddle.stop();
    rightMiddle.stop();
    rightFront.stop();
    leftBack.stop();
    rightBack.stop();

    //put breaking back to coast after hanging out
    wait(25, msec);

    leftFront.setStopping(coast);
    leftMiddle.setStopping(coast);
    rightMiddle.setStopping(coast);
    rightFront.setStopping(coast);
    leftBack.setStopping(coast);
    rightBack.setStopping(coast);
}

/*for auton offensive:
move();
autonIntakeOut();
*/
//int autonSelection = 0;
void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  awesomeInertial();
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

void autonomous(void) {
  // ..........................................................................
  switch (autonNumber){
    case 1:
    //defensive AWP
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(0, 0);
      Brain.Screen.print("defensive auton 1 running");
      break;
    case 2:
    //offensive AWP
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(0, 0);
      Brain.Screen.print("offensive auton 2 running");
      break;   
    case 3:
    //skills
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(0, 0);
      Brain.Screen.print("skills auton 3 running");
      break;    
    case 4:
    //offensive score
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(0, 0);
      Brain.Screen.print("offensive auton 4 running");
      break;    
    case 5:
    //bar touch backup
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(0, 0);
      Brain.Screen.print("bar touch auton 5 running");
      break;    
    case 6:
    //single score backup defensive
      break;
    case 7:
    //single score backup offensive
      break;
  }

/*
autonRakeUp(0.5);

  //adjust position for bar touch
  anika(30, 90, 15);

  //up here works
  turnLeft(-45);
  autonRakeUp(0.5);
  arushi(130, 60, 15);

  //go to bar
  turnLeft(-85);
  arushi(270, 50, 10);
  autonRakeDown();
*/


  /*
  driveReverse(125, 50, 5);
//robot is off bar

  wait(100,msec);
  driveForward(100, 20, 5);
  wait(200, msec);
  
  driveReverse(10, 20, 5);
  turnRight(105);
  wait(200,msec);
//at bar touching triball

  driveReverse(15, 20, 5);
  autonRakeDown(0.38);
  wait(300,msec);
  //collect triball using rake, move to    
  driveForward(60, 30, 5);
  wait(100,msec);
  turnLeft(-100);
  wait(100,msec);*/
  //phase 2
  //back up from goal

  // ..........................................................................
}
void usercontrol(void) {
  // User control code here, inside the loop
  while(1){
    DeviDrive();
  }
}
 //while (1) {
   //auton defensive
  /*awesomeInertial();
  turnRight(45);    
  wait(20,msec);
  driveForward(340);
  turnRight(15);
  driveForward(40);
  autonIntakeOut(1);
  driveReverse(40);*/
  /*
  //shove it in the goal
  turnRight(15); 
  driveForward(120);
  
  driveReverse(60);
  turnRight(135);
  driveForward(65);
    //get matchload
    
  turnLeft(-90);
  driveReverse(45);
  autonRakeDown();
   
  wait(400,msec);
  driveForward(70);
  autonRakeUp(0.5);
  turnLeft(-45);
  driveReverse(110);
  turnLeft(-90); 
  driveReverse(200);
*/
    
    //driving();
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

  // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  //}


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
  while(true){
    wait(100,msec);

  }
} 
