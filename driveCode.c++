//the flywheel for launching acorns is controlled by button B, it can turn on and off
int flyWheel(){
  int flyControl = 0;
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

//holding down R2 and R1 spin the intake
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

//we use split drive to move
int splitDrive(){
  while(true){
    leftFront.spin(forward, Controller1.Axis3.position()+Controller1.Axis1.position(),pct);
    leftBack.spin(forward, Controller1.Axis3.position()+Controller1.Axis1.position(),pct);
    rightFront.spin(forward, Controller1.Axis3.position()-Controller1.Axis1.position(),pct);      
    rightBack.spin(forward,Controller1.Axis3.position()-Controller1.Axis1.position(),pct);
    wait(20,msec);
  }
}

//first edition of pneumatics which features button Y as a switch
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

//this is if you want pneumatics left and right to be seperated
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

//same as above but for other side
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

//for if you want the pneumatics to be together, but not as a switch
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

//our rake code
//this has not been tested yet
int rake(){
  while(true){
    if(Controller1.ButtonA.pressing()){
      rakeWithK.spin(forward, 50, pct);
      wait(0.5, sec);
      rakeWithK.setStopping(coast);
      rakeWithK.stop();
    }
    if(Controller1.ButtonY.pressing()){
      rakeWithK.spin(reverse, 50, pct);
      wait(0.5, sec);
      rakeWithK.setStopping(hold);
      rakeWithK.stop();
    }
  }
}

//everything combined for driver control period
void driving(){
  
    thread f (flyWheel);
    thread i (intake);
    thread s (splitDrive);
    thread n (knooMatics3);
    thread k (rake);

}
