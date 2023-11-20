// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// leftFront            motor         14              
// leftBack             motor         19              
// rightFront           motor         17              
// rightBack            motor         20              
// intakeMotor          motor         2               
// bottomFly            motor         11              
// topFly               motor         15              
// rakeWithK            motor         10              
// gyroK                inertial      7               
// knooMatics1          digital_out   A               
// knooMatics2          digital_out   B               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

competition Competition;

//this is the split drive
//we are using a split drive
int flyControl = 0;
int flyWheel(){
  while(true){
    if(Controller1.ButtonB.pressing()){
      if(flyControl == 0){
        topFly.spin(forward,200,pct);
        bottomFly.spin(forward,200,pct);
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
      knoo ++;
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
    if(Controller1.ButtonY.pressing()){
      while(Controller1.ButtonY.pressing()){
        wait(20,msec);
      } 
      k ++;
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

void driving(){
  
    thread f (flyWheel);
    thread i (intake);
    thread s (splitDrive);
    thread n (knooMatics3);

}

//ALL CODE UP HERE IS DRIVE CODE
//-----------------------------------------------------------------------------------------
//ALL CODE DOWN HERE IS FOR AUTON

//turning funtion for left
//assuming the target for left is a negative number
void hopefullyGoodLeft(int target){
  gyroK.resetRotation();
  wait(.25, msec);
  //we can set timeout later

  while(gyroK.rotation(degrees) > target){
    float error = -target + gyroK.rotation(degrees);
    //edit the kp and minimumSpeed, the 0.25 is just a placeholder for now
    float kp = 0.25;
    float minimumSpeed = 0.25;
    float speed = error * kp + minimumSpeed;

    leftFront.spin(reverse, speed, pct);
    rightFront.spin(fwd, speed, pct);
    leftBack.spin(reverse, speed, pct);
    rightBack.spin(fwd, speed, pct);
  }

  //brake makes the most sense but can change later
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

void hopefullyGoodRight(int target){
  gyroK.resetRotation();
  wait(.25, seconds);
  //where timeout would be

  while(gyroK.rotation(degrees) < target){
    float error = target - gyroK.rotation(degrees);
    //adjust kp and minimum speed to liking
    float kp = .25;
    float minimumSpeed = .25;
    float speed = error * kp + minimumSpeed;
    
    leftFront.spin(reverse, speed, pct);
    leftBack.spin(reverse, speed, pct);
    rightFront.spin(fwd, speed, pct);
    rightBack.spin(fwd, speed, pct);
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

void move(double distance,int velocity,float kp){
  leftFront.setPosition(0,degrees);
  double heading=gyroK.rotation(degrees);
  if(velocity>0){
    while(leftFront.position(degrees)<distance){
      double error=heading-gyroK.rotation(degrees);
      double output=error*kp;
      leftFront.spin(forward,velocity-output,percent);
      leftBack.spin(forward,velocity-output,percent);
      rightFront.spin(forward,velocity+output,percent);
      rightBack.spin(forward,velocity+output,pct);
      wait(10,msec);
    }
  }
  leftFront.stop();
  rightFront.stop();
  rightBack.stop();
  leftBack.stop();
}

void moveBack(double distance,int velocity,int kp){
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

/*for auton offensive:
move();
autonIntakeOut();
*/
void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

void autonomous(void) {
  // ..........................................................................
  //DEFENSIVE AUTONNN
  //step0
  //gyroK.resetRotation();
  //move(750,50,1);
  //backwards?  turnRightNew(45);
  awesomeInertial();
  move(750,50,1);
  hopefullyGoodLeft(-100);
  move(900,50,1);
  move(500,50,1);
  hopefullyGoodRight(45);
  /*autonIntakeOut(1);
  moveBack(40,50,1);
  hopefullyGoodLeft(-15);
  move(45,50,1);*/
  /*hopefullyGoodLeft(-55);
  move(800,50,1);
  turnRight(-90);
  move(100,50,1);
  wait(40,msec);
  autonIntakeOut(1);
  moveBack(200,50,1);*/
  //step1 - turn 180 and then move
  //step2
  //step7
  // ..........................................................................
}

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    driving();
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

  /*// Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);*/
