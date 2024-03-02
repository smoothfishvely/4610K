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


void SPLITDRIVE() {
// run your predrive here.
  while (true) {
  float movement1 = (Controller1.Axis3.position()) + (Controller1.Axis1.position());
  float movement2 = (Controller1.Axis3.position()) - (Controller1.Axis1.position());
  leftFront.spin(forward, movement1,  pct);
  rightFront.spin(forward, movement2, pct);

  leftBack.spin(forward, movement1,  pct);
  rightBack.spin(forward, movement2, pct);
  }
  if (Controller1.ButtonA.pressing()) {
    rakeWithK.spin(forward, 100, pct);
  } else if (Controller1.ButtonB.pressing()) {
//    SECONDARY FUNCTION, WOULD BE USED FOR A HOLD VARIABLE
  } else {
    rakeWithK.stop();
  }

}


// I'm impressed you figured out this was a viable way to run a drive program, although I'd like to note it is innefficient.
// Running everything in one while loop is much easier on the bot and your computer's memory.
// I'm assuming you were not taught how to include additional controls for a drive program so not knowing to do what I did is not your fault at all. 
// Good luck at the competition, K!

bool punchControl = false;

int puncher(){
  while(true){
    if(Controller1.ButtonB.pressing()){
      punchControl = !punchControl;
    }
    if(punchControl == true){
      puncherRight.spin(forward,48,pct);
      puncherLeft.spin(forward, 48, pct);
    }
    if(punchControl == false){
      puncherRight.stop();
      puncherLeft.stop();
    }
    wait(80,msec);
  }
}

bool matics1 = false;
bool matics2 = false;

//USE THIS DRIVE
void DeviDrive(){
  

  while(true) {
    thread p (puncher);
    leftFront.spin(forward, Controller1.Axis3.position() + (Controller1.Axis1.position()/2), pct);
    leftBack.spin(forward, Controller1.Axis3.position() + (Controller1.Axis1.position()/2), pct);
    rightFront.spin(forward, Controller1.Axis3.position() - (Controller1.Axis1.position()/2), pct);
    rightBack.spin(forward, Controller1.Axis3.position() - (Controller1.Axis1.position()/2), pct);   

    if(Controller1.ButtonL2.pressing()){
      while(Controller1.ButtonL2.pressing()){
        wait(10, msec);
      }
      matics1 = !matics1;
    }
    if(matics1 == true){
      knooMatics1.set(true);
    }
    if(matics1 == false){
      knooMatics1.set(false);
    }

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

        //intake
    if(Controller1.ButtonR2.pressing()) {
      intakeMotor.spin(forward, 100, pct);
    } else if(Controller1.ButtonR1.pressing()) {
      intakeMotor.spin(reverse, 100, pct);
    } else {
      intakeMotor.stop();
    }
        // rake
    if(Controller1.ButtonDown.pressing()) {
      rakeWithK.spin(forward, 100, pct);
      wait(0.25, sec);
      rakeWithK.setStopping(hold);
      rakeWithK.stop();
    } else if(Controller1.ButtonUp.pressing()) {
      rakeWithK.spin(reverse, 100, pct);
      wait(0.25, sec);
      rakeWithK.setStopping(coast);
      rakeWithK.stop();
    }
    wait(80, msec); 
  } 
}

//ALL CODE UP HERE IS DRIVE CODE
//-----------------------------------------------------------------------------------------
//ALL CODE DOWN HERE IS FOR AUTON

void autonRakeDown(float seconds){
  rakeWithK.spin(reverse,100,pct);
  rakeWithK.setStopping(coast);
  wait(seconds,sec);
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
  puncherRight.spin(forward,48,pct);
  puncherLeft.spin(forward,48,pct);
  wait(30,sec);

  //done match loading

  //stop puncher
  puncherRight.stop();
  puncherLeft.stop();

  
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
  //reverse to near side goal
  arushi(410, 30, 5);
  tessa(2500,100);
  knooMatics1.set(true);
  knooMatics2.set(true);
  arushi(500, 60, 7);
  tessa(2800,100);
  turnRight(10);

  knooMatics1.set(false);
  knooMatics2.set(false);

  //left front push
  arushi(70, 20, 5);
  turnLeft(-90);
  anika(100, 30, 5);
  turnRight(90);
  knooMatics1.set(true);
  knooMatics2.set(true);
  tessa(800, 80);
  
  knooMatics1.set(false);
  knooMatics2.set(false);
  
  //left side push
  arushi(10, 30, 5);
  turnLeft(-90);
  anika(150, 40, 5);
  turnRight(90);
  anika(100, 40, 5);
  turnRight(90);
  knooMatics1.set(true);
  knooMatics2.set(true);
  tessa(700, 80);

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
  anika(340);
  turnRight(15);
  anika(40);
  autonIntakeOut(1);
  arushi(40);*/
  /*
  //shove it in the goal
  turnRight(15); 
  anika(120);
  
  arushi(60);
  turnRight(135);
  anika(65);
    //get matchload
    
  turnLeft(-90);
  arushi(45);
  autonRakeDown();
   
  wait(400,msec);
  anika(70);
  autonRakeUp(0.5);
  turnLeft(-45);
  arushi(110);
  turnLeft(-90);
  arushi(200);
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
