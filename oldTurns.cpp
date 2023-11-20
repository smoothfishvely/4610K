void turnRight(int target){
  //PID example(?):
  //if abs(error) > 180
        //error-= sgn?(error) * 360
  gyroK.resetRotation();
  wait(.25,seconds);
  float error = target-gyroK.rotation(degrees);
  float kp = 0.3;
  while(fabs(error)>1){
    error = target-gyroK.rotation(degrees);
    leftFront.spin(forward,error*kp,percent);
    leftBack.spin(forward,error*kp,pct);
    rightFront.spin(reverse,error*kp,pct);
    rightBack.spin(reverse,error*kp,pct);
    wait(10,msec);
  }
  leftFront.stop();
  leftBack.stop();
  rightBack.stop();
  rightFront.stop();
}

void turnRightNew(int target){
    gyroK.resetRotation();
    wait(20,msec);
    while(gyroK.rotation(degrees)<target){
      leftFront.spin(fwd,20,percent);
      leftBack.spin(fwd,20,pct);
      rightFront.spin(reverse,20,pct);
      rightBack.spin(reverse,20,pct);
      wait(10,msec);
  }
    leftFront.stop();
    leftBack.stop();
    rightBack.stop();
    rightFront.stop();
}

void turnLeftNew(int target){
  gyroK.resetRotation();
  wait(20,msec);
  while(gyroK.rotation(degrees)>target){
    leftFront.spin(reverse,20,percent);
    leftBack.spin(reverse,20,pct);
    rightFront.spin(fwd,20,pct);
    rightBack.spin(fwd,20,pct);
    wait(10,msec);
  }
  leftFront.stop();
  leftBack.stop();
  rightBack.stop();
  rightFront.stop();
}

void turnLeft(int target){
  float error = target-gyroK.rotation(degrees);
  float kp = 0.5;
  gyroK.resetRotation();
  wait(.25,seconds);
  while(fabs(error)<1){
    error = target-gyroK.rotation(degrees);
    leftFront.spin(reverse,error*kp,percent);
    leftBack.spin(reverse,error*kp,pct);
    rightFront.spin(forward,error*kp,pct);
    rightBack.spin(forward,error*kp,pct);
    wait(10,msec);
  }
  leftFront.stop();
  leftBack.stop();
  rightBack.stop();
  rightFront.stop();
}
