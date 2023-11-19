//calibrating in the main
int main(){
  gyroK.calibrate();
  
  while(gyroK.isCalibrating()){
    wait(100,msec);
  }

  hopefullyGoodLeft(-90);
}

//gyroK is the inertial
//turning function for left
//assuming the target for left is a negative number
void hopefullyGoodLeft(int target){
  gyroK.resetRotation();
  wait(.25, msec); 
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