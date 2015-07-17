#include <Servo.h>

int pos=0;
int walkspeed=50;

// define servo center positions (Spider at rest)
int svc[36]={
  2300,2200,2200,     // D27 thigh1, D28 thigh2, D29 thigh3   0,1,2
  1150,1150,950,     // D30 knee 1, D31 knee 2, D32 knee 3   3,4,5,
  1600,1200,1100,     // D33 hip  1, D34 hip  2, D35 hip  3   6,7,8
  1250,1850,2050,     // D36 hip  4, D37 hip  5, D38 hip  6   9,10,11
  1850,1850,2050,     // D39 knee 4, D40 knee 5, D41 knee 6   12,13,14,
  950,950,1000,        // D42 thigh4, D43 thigh5, D44 thigh6   15,16,17

  // define servo center positions (Spider standing)
  1900,1700,1750,     // D27 thigh1, D28 thigh2, D29 thigh3
  1500,1400,1400,     // D30 knee 1, D31 knee 2, D32 knee 3
  1600,1200,1100,     // D33 hip  1, D34 hip  2, D35 hip  3
  1250,1850,2050,     // D36 hip  4, D37 hip  5, D38 hip  6
  1700,1700,1800,     // D39 knee 4, D40 knee 5, D41 knee 6
  1050,1100,1250,     // D42 thigh4, D43 thigh5, D44 thigh6

};

int svt[18];  // storage of temporary servo calculations used to control speed and direction of servos

int svp[18];  // actual servo positions

Servo sv[18];

/**********************Set up Servos******************/ 
void setup()
{
  for(int i=0;i<18;i++)
  {
    svp[i]=svc[i];
  }
  delay (1000);
//  
//   sv[15].attach(27 + 15, 700, 2300);
//  delay(50);
//   sv[12].attach(27+12, 700, 2300);
//  delay(50);
//   sv[9].attach(27+9, 700, 2300);

for(int i=0; i<3;i++)        //intialize left thighs
  {
    sv[i].attach(27+i, 700, 2300);
    sv[i].writeMicroseconds(svc[i]);
    delay(50);
  }
for(int i=15; i<18;i++)      //intialize right thighs
  {
    sv[i].attach(27+i, 700, 2300);
    sv[i].writeMicroseconds(svc[i]);
    delay(50);
  }
for(int i=6; i<12;i++)      // initialzie all hips
  {
    sv[i].attach(27+i, 700, 2300);
    sv[i].writeMicroseconds(svc[i]);
    delay(50);
  }
for(int i=12; i<15;i++)      // initialize right knees
  {
    sv[i].attach(27+i, 700, 2300);
    sv[i].writeMicroseconds(svc[i]);
    delay(50);
  }
for(int i=3; i<6;i++)      // initialize left knees
  {
    sv[i].attach(27+i, 700, 2300);
    sv[i].writeMicroseconds(svc[i]);
    delay(50);
  }
//if (pos>0) SitStand();
//delay (1000);
}
/**********************END SETUP*****************************/ 

void SitStand()
{
  for (int i=0; i<18; i++)
  {
    svt[i]=(svc[i+pos]-svp[i])/20;
    if (svc[i+pos]==0) svt[i]=0;
  }
  for (int j=0; j<20; j++)
  {
    for (int i=0; i<18; i++)
    {
      svp[i]+=svt[i];
      sv[i].writeMicroseconds(svp[i]);
    }
    delay (walkspeed);
  }
}

void ServoUpdate()
{
  for (int i=0; i<18; i++)
    {
      sv[i].writeMicroseconds(svp[i]);
    }
}

/************************WALKING ROUTINES******************/

void Forward()
{
  for (int i=18; i<18; i++)
  {
    svp[i-18]=svc[i];
  }
  ServoUpdate();
  
  /*****MOVE LEFT FRONT LEG FORWARD******/
  sv[0].writeMicroseconds(svp[0]-500);
  sv[6].writeMicroseconds(svp[6]-300);
  sv[0].writeMicroseconds(svp[0]);
  delay(walkspeed);
  
  /*****MOVE RIGHT FRONT LEG FORWARD*****/
  sv[15].writeMicroseconds(svp[15]+500);
  sv[9].writeMicroseconds(svp[9]+300);
  sv[15].writeMicroseconds(svp[15]);
  delay(walkspeed);
  
}

void loop()
{
  delay(1000);
//
//  sv[15].writeMicroseconds(800);
//  delay(1000);
//
//  sv[12].writeMicroseconds(1850);
//  delay(1000);
//
//  sv[9].writeMicroseconds(1350);
//  delay(10000);
  pos=0;
  SitStand();
  delay(5000);
  pos=18;
  SitStand();
  delay(5000);
//  SitStand();
//  delay(10000);
//  pos=0;
}
