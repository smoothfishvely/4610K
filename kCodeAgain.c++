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
// leftFront            motor         14              
// rightFront           motor         17              
// leftBack             motor         19              
// rightBack            motor         20              
// intakeMotor          motor         2               
// bottomFly            motor         11              
// topFly               motor         15              
// rakeWithK            motor         10              
// gyroK                inertial      7               
// knooMatics1          digital_out   A               
// knooMatics2          digital_out   B               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

competition Competition;

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
      } else{
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
    if(Controller1.ButtonL2.pressing()){
      knooMatics1.set(true);
      knooMatics2.set(true);
    }
    if(Controller1.ButtonL1.pressing()){
      knooMatics1.set(false);
      knooMatics2.set(false);
    }
  }
}

int rake(){
  while(true){
    if(Controller1.ButtonA.pressing()){
      rakeWithK.spin(forward, 50, pct);
      wait(0.25, sec);
      rakeWithK.setStopping(coast);
      rakeWithK.stop();
    }
    if(Controller1.ButtonY.pressing()){
      rakeWithK.spin(reverse, 50, pct);
      wait(0.25, sec);
      rakeWithK.setStopping(hold);
      rakeWithK.stop();
    }
  }
}


// hello! this is a sample driver i'm adding in for your team to try and work around a few issues i noticed with your drivetrain.
// -eleri (4610W)

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

void driving(){
  
    thread f (flyWheel);
    thread i (intake);
    thread s (splitDrive);
    thread n (knooMatics3);
    thread k (rake);

}

void anotherDrive(){
    int flyControl = 0;
  
    while(true) {
      // Control flywheel
      if(Controller1.ButtonB.pressing()) {
          if(flyControl == 0) {
            // Start flywheel motors
            topFly.spin(forward, 100, pct);
            bottomFly.spin(reverse, 100, pct);
            flyControl++;
          } else {
            // Stop flywheel motors
            topFly.stop();
            bottomFly.stop();
            flyControl--;
          }
        }

        // Control intake motor
        if(Controller1.ButtonR2.pressing()) {
            intakeMotor.spin(forward, 100, pct);
        } else if(Controller1.ButtonR1.pressing()) {
            intakeMotor.spin(reverse, 100, pct);
        } else {
            intakeMotor.stop();
        }

        // Split drive control
        leftFront.spin(forward, Controller1.Axis3.position() + Controller1.Axis1.position(), pct);
        leftBack.spin(forward, Controller1.Axis3.position() + Controller1.Axis1.position(), pct);
        rightFront.spin(forward, Controller1.Axis3.position() - Controller1.Axis1.position(), pct);
        rightBack.spin(forward, Controller1.Axis3.position() - Controller1.Axis1.position(), pct);

        // Control rake
        if(Controller1.ButtonA.pressing()) {
            rakeWithK.spin(forward, 100, pct);
            wait(0.25, sec);
            rakeWithK.setStopping(coast);
            rakeWithK.stop();
        } else if(Controller1.ButtonY.pressing()) {
            rakeWithK.spin(reverse, 100, pct);
            wait(0.25, sec);
            rakeWithK.setStopping(hold);
            rakeWithK.stop();
        }
        wait(20, msec); 
    } 
}
//ALL CODE UP HERE IS DRIVE CODE
//-----------------------------------------------------------------------------------------
//ALL CODE DOWN HERE IS FOR AUTON

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

void turnLeft(int target){
  gyroK.resetRotation();
  wait(.25, msec);

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

void turnRight(int target){
  gyroK.resetRotation();
  wait(.25, seconds);

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

void anika(double dist) {   //inches
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
        double min_speed = 15;
        double max_speed = 100;
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

void arushi(double dist) {   //inches
    //Drive Forward with Proportional Stop
    leftFront.resetPosition();
  
    double target = dist;

    while(leftFront.position(degrees) > -target) {
        double proportion = target - leftFront.position(degrees); 
        double kp = .6;
        double min_speed = 15;
        double max_speed = 100;
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
int autonSelection = 0;
void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  awesomeInertial();
  while(true){
    if(Controller1.ButtonUp.pressing()){
      autonSelection = 1;
    }
  }
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

void autonomous(void) {
  // ..........................................................................
  //AUTON for offensive
  if(autonSelection == 1){
    turnLeft(-44);
    wait(20,msec);
    anika(285);
    turnLeft(-3);
    anika(45);
    autonIntakeOut(1);
    arushi(30);
    //shove it in the goal
    turnLeft(-10);
    anika(90);
    arushi(65);
    turnLeft(-135);
    anika(80);
    //get matchload
    turnRight(90);
    arushi(55);
    autonRakeDown();
    wait(400,msec);
    anika(70);
    autonRakeUp(0.75);
    //go to bar
    turnLeft(-130);
    anika(50);
    turnRight(95);
    anika(290);
  }
  //Defensive
  /*
  awesomeInertial();
  right(44);
  wait(20,msec);
  anika(285);
  right(3);
  anika(45);
  autonIntakeOut(1);
  anika(15);
  */


  // ..........................................................................
}

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    
    awesomeInertial();
    turnLeft(-44);
    wait(20,msec);
    anika(285);
    turnLeft(-3);
    anika(45);
    autonIntakeOut(1);
    arushi(30);
    //shove it in the goal
    turnLeft(-10);
    anika(90);
    arushi(65);
    turnLeft(-135);
    anika(80);
    //get matchload
    turnRight(90);
    arushi(55);
    autonRakeDown();
    wait(400,msec);
    anika(70);
    autonRakeUp(0.75);
    //go to bar
    turnLeft(-130);
    anika(70);
    turnRight(95);
    anika(290);
    
    //driving();
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
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
