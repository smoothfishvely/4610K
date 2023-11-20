//gyroK is the inertial
//turning function for left
//assuming the target for left is a negative number
void hopefullyGoodLeft(int target){
  gyroK.resetRotation();
  wait(.25, sec); 
  //we can set timeout later, but will be here
  
  while(gyroK.rotation(degrees) > target){
    float error = -target + gyroK.rotation(degrees);
    //please edit the kp and minimumSpeed, the 0.25 is just a placeholder for now
    float kp = 0.25;
    float minimumSpeed = 0.25;
    float speed = error * kp + minimumSpeed;

    leftFront.spin(reverse, speed, pct);
    rightFront.spin(fwd, speed, pct);
    leftBack.spin(reverse, speed, pct);
    rightBack.spin(fwd, speed, pct);
  }

  //i think brake makes the most sense but change if you disagree!
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
  Brain.Screen.print("evelyn is cool");
}

//duplicate for right turning
//target is a positive number
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
  leftBack.setSTopping(brake);
  rightBack.setStopping(brake);
  rightFront.setStopping(brake);
  leftFront.stop();
  leftBack.stop();
  rightFront.stop();
  rightBack.stop();
}

void calibrate(){
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
