/*--------------------------------------------------------------
  Program:       OscopetouchLCDmegaMED

  Description:   Digital Oscilloscope with data  displayed
                 on Color TFT LCD with touch screen
  
  Hardware:      sainsmart mega2560 board with 3.5" myGLCD lcd touch  module display and shield kit      
                 http://www.sainsmart.com/home-page-view/sainsmart-mega2560-board-3-5-myGLCD-lcd-module-display-shield-kit-for-atmel-atmega-avr-16au-atmega8u2.html

  Software:      Developed using Arduino 1.0.3 software
                 This program requires the UmyGLCD library and the
                 UTouch library from Henning Karlsen.
                 web: http://www.henningkarlsen.com/electronics
                 Version 1.1
  Date:          18 May 2014
 
  Author:        johnag    
--------------------------------------------------------------*/

#include <UTFT.h>
//#include <UTouch.h>
// Declare which fonts we will be using 
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
//extern uint8_t SevenSegNumFont[];

// Initialize Screen and touch functions
//UTFT    myGLCD(ITDB32S,38,39,40,41);
UTFT    myGLCD(CTE32HR,38,39,40,41);
//UTouch  myTouch(6,5,4,3,2);
// Declare variables
char buf[12];
char buf2[12];
int x,y;
int Input = 0;
byte Sample[480];
byte OldSample[480];
float StartSample = 0; 
float EndSample = 0;
const int fft_length=16;
byte fft[fft_length][3];
byte read_sample_number_prev=0;
//byte fft[4][8][fft_length][3];
//byte channels_state[4][8][3];

int Max = 0;
int Min = 500;
int mode = 0;
int dTime = 1;
int tmode = 0;
int Trigger = 0;
int SampleSize = 0;
float SampleTime = 0;
int dgvh;
int hpos = 105; //set 0v on horizontal  grid
int vsens = 3; // vertical sensitivity
int port = 0;
// variables for DVM
int sum = 0;                    // sum of samples taken

// Define various ADC prescaler
const unsigned char PS_16 = (1 << ADPS2);
const unsigned char PS_32 = (1 << ADPS2) | (1 << ADPS0);
const unsigned char PS_64 = (1 << ADPS2) | (1 << ADPS1);
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

//------------Start Subrutines------------------------------------

//--------draw buttons sub
void buttons(){
 myGLCD.setColor(0, 0, 255);
   myGLCD.fillRoundRect (410, 1, 470, 50);
   myGLCD.fillRoundRect (410, 55, 470, 105);
   myGLCD.fillRoundRect (410, 110, 470, 160);
   myGLCD.fillRoundRect (410, 165, 470, 215);
}
//-------touchscreen position sub
/*void touch(){
  while (myTouch.dataAvailable())
  {
      myTouch.read();
      x=myTouch.getX();
      y=myTouch.getY();
      delay(500);
     if ((y>=1) && (y<=50))  // Delay row
      {
     if ((x>=250) && (x<=300))  //  Delay Button
         waitForIt(250, 1, 310, 50);
           mode= mode ++ ;
      {
 myGLCD.setColor(255, 0, 0);
 myGLCD.drawRoundRect (250, 1, 310, 50);   
 // Select delay times you can change values to suite your needs
 if (mode == 0) dTime = 1;
 if (mode == 1) dTime = 10;
 if (mode == 2) dTime = 20;
 if (mode == 3) dTime = 50;
 if (mode == 4) dTime = 100;
 if (mode == 5) dTime = 200;
 if (mode == 6) dTime = 300;
 if (mode == 7) dTime = 500;
 if (mode == 8) dTime = 1000;
 if (mode == 9) dTime = 5000;
 if (mode == 10) dTime = 10000;
 if (mode > 10) mode = 0;   
    

}}

 if ((y>=70) && (y<=120))  // Trigger  row
 {
 if ((x>=250) && (x<=300))  // Trigger Button
   waitForIt(250, 55, 310, 105);
   tmode= tmode ++;
   {
 myGLCD.setColor(255, 0, 0);
  // Select Software trigger value
 myGLCD.drawRoundRect (250, 55, 310, 105);      
 if (tmode == 1) Trigger = 0;
 if (tmode == 2) Trigger = 10;
 if (tmode == 3) Trigger = 20;
 if (tmode == 4) Trigger = 30;
 if (tmode == 5) Trigger = 50;
 if (tmode > 5)tmode = 0;
 }}
 if ((y>=130) && (y<=180))  // Port select   row
 {
 if ((x>=250) && (x<=300))  // Port select Button
   waitForIt(250, 110, 310, 160);
   port= port ++;
   
   {
    myGLCD.setColor(255, 0, 0);
    myGLCD.drawRoundRect (250, 110, 310, 160); 
    myGLCD.clrScr();
    buttons();
    if (port > 2)port = 0;
 }}}}
//----------wait for touch sub 
void waitForIt(int x1, int y1, int x2, int y2)
{
  while (myTouch.dataAvailable())
  myTouch.read();
}*/
//----------draw grid sub
void DrawGrid(){

  myGLCD.setColor( 0, 200, 0);
  for(  dgvh = 0; dgvh < 4; dgvh ++){
  myGLCD.drawLine( dgvh * 50, 0, dgvh * 50, 150);
  myGLCD.drawLine(  0, dgvh * 50, 245 ,dgvh * 50);
  }
  myGLCD.drawLine( 200, 0, 200, 150);
  myGLCD.drawLine( 245, 0, 245, 150);
  myGLCD.drawLine( 0, 239, 245, 239);
  myGLCD.setColor(255, 255, 255);
  
  myGLCD.drawRoundRect (250, 1, 310, 50);
  myGLCD.drawRoundRect (250, 55, 310, 105);
  myGLCD.drawRoundRect (250, 110, 310, 160);
  myGLCD.drawRoundRect (250, 165, 310, 215);
 
  }
  // ------ Wait for input to be greater than trigger sub
/*void trigger(){

while (Input < Trigger){ Input = Serial1.read()//analogRead(port)
*5/100;
}}*/

//---------------End Subrutine  ----------------------


 void setup() {
  Serial1.begin(115200);
//  Serial1.begin(921600);
  
   myGLCD.InitLCD();
   myGLCD.clrScr();
//   myTouch.InitTouch();
//   myTouch.setPrecision(PREC_MEDIUM);
//   buttons();
  // pinMode(0, INPUT); 
    // set up the ADC
  ADCSRA &= ~PS_128;  // remove bits set by Arduino library

  // you can choose a prescaler from below.
  // PS_16, PS_32, PS_64 or PS_128
  ADCSRA |= PS_128;    // set our own prescaler 
 }
void loop() {
   
   while(1) {
//   DrawGrid();
//   touch();
 //  trigger();

 // Collect the analog data into an array

  StartSample = micros();
 for( int xpos = 0; xpos < 480/2; xpos ++) 
 { 

  while(!Serial1.available()){}
  byte read_start=Serial1.read();
  while(read_start!=0xA0)
  {
    while(!Serial1.available()){}
    read_start=Serial1.read();
  }
  while(!Serial1.available()){}
  byte read_sample_number=Serial1.read();
  
//  int ad_adc = 0;
//  int ad_chan = 0;
 
  for( int index_fft = 0; index_fft < fft_length; index_fft ++) 
//  for( int ad_adc = 0; ad_adc < 4; ad_adc ++) 
  { 
//    for( int ad_chan = 0; ad_chan < 8; ad_chan ++) 
    { 
      while(!Serial1.available()){}
      fft[index_fft][0]=Serial1.read();
//      channels_state[ad_adc][ad_chan][0]=Serial1.read();
//      while(!Serial1.available()){}
//      fft[index_fft][1]=Serial1.read();
//      channels_state[ad_adc][ad_chan][1]=Serial1.read();
//      while(!Serial1.available()){}
//      fft[index_fft][2]=Serial1.read();
//      channels_state[ad_adc][ad_chan][2]=Serial1.read();
    }
  }
//  for( int addit = 0; addit < 3*2; addit ++) 
//  { 
//    while(!Serial1.available()){}
//    Serial1.read();
//  }
  while(!Serial1.available()){}
  byte read_end=Serial1.read();
  
  myGLCD.setFont( BigFont);
  myGLCD.setColor (255, 255,255);
  myGLCD.setBackColor( 0, 0, 255);
//  myGLCD.print( itoa( 100, buf, 10), 100, 300);
  itoa( read_sample_number, buf, 10);
  if(read_sample_number<10)
  {
    buf[3]=buf[1];
    buf[2]=buf[0];
    buf[1]='0';
    buf[0]='0';
  }
  else
  if(read_sample_number<100)
  {
    buf[3]=buf[2];
    buf[2]=buf[1];
    buf[1]=buf[0];
    buf[0]='0';
  }
  myGLCD.print(buf, 100, 300);
  if(read_end==0xC0)
  {
  myGLCD.setBackColor( 0, 255, 0);
    myGLCD.print( "OKAY", 200, 300);
  }
  else
  {
    myGLCD.setBackColor( 255, 0, 0);
    myGLCD.print( "FAIL", 200, 300);
  }

  byte read_sample_number_dif=read_sample_number-read_sample_number_prev;
  itoa( read_sample_number_dif, buf2, 10);
  if(read_sample_number_dif<10)
  {
    buf2[3]=buf2[1];
    buf2[2]=buf2[0];
    buf2[1]='0';
    buf2[0]='0';
  }
  else
  if(read_sample_number_dif<100)
  {
    buf2[3]=buf2[2];
    buf2[2]=buf2[1];
    buf2[1]=buf2[0];
    buf2[0]='0';
  }
  if(read_sample_number_dif==1)
  {
    myGLCD.setBackColor( 0, 255, 0);
    myGLCD.print( buf2, 300, 300);
  }
  else
  {
    myGLCD.setBackColor( 255, 0, 0);
    myGLCD.print( buf2, 300, 300);
  }
  read_sample_number_prev=read_sample_number;
  
  for( int index_fft = 0; index_fft < fft_length; index_fft ++) 
//  for( int ad_adc = 0; ad_adc < 4; ad_adc ++) 
  { 
//    for( int ad_chan = 0; ad_chan < 8; ad_chan ++) 
    { 
      byte read_r=fft[index_fft][0];
      byte read_g=fft[index_fft][0];
      byte read_b=fft[index_fft][0];
//      byte read_g=fft[index_fft][1];
//      byte read_b=fft[index_fft][2];
//      byte read_r=channels_state[ad_adc][ad_chan][0];
//      byte read_g=channels_state[ad_adc][ad_chan][1];
//      byte read_b=channels_state[ad_adc][ad_chan][2];
//      byte read_r=ad_adc*50;
//      byte read_g=ad_adc*50;
//      byte read_b=ad_adc*50;
      myGLCD.setColor( read_r, read_g, read_b);
      myGLCD.drawLine (xpos*2, (index_fft)*8, xpos*2, (index_fft)*8+7);
      myGLCD.drawLine (xpos*2+1, (index_fft)*8, xpos*2+1, (index_fft)*8+7);
//      myGLCD.drawLine (xpos*2, (ad_adc * 9 + ad_chan)*8, xpos*2, (ad_adc * 9 + ad_chan)*8+6);
//      myGLCD.drawLine (xpos*2+1, (ad_adc * 9 + ad_chan)*8, xpos*2+1, (ad_adc * 9 + ad_chan)*8+6);
    }
  }
 }
  EndSample = micros();
/*  
// Display the collected analog data from array
for( int xpos = 0; xpos < 319;
xpos ++)
{
// Erase previous display
myGLCD.setColor( 0, 0, 0);

myGLCD.drawLine (xpos + 1, 475-OldSample[ xpos + 1]* vsens-hpos, xpos + 2, 475-OldSample[ xpos + 2]* vsens-hpos);
if (xpos == 0) myGLCD.drawLine (xpos + 1, 1, xpos + 1, 319);
 //Draw the new data
myGLCD.setColor( 255, 255, 255);
myGLCD.drawLine (xpos, 475-Sample[ xpos]* vsens-hpos, xpos + 1, 475-Sample[ xpos + 1]* vsens-hpos);
}
// Determine sample voltage peak to peak
Max = Sample[ 100];
Min = Sample[ 100];
for( int xpos = 0;
xpos < 320; xpos ++)
{
OldSample[ xpos] = Sample[ xpos];
if (Sample[ xpos] > Max) Max = Sample[ xpos];
if (Sample[ xpos] < Min) Min = Sample[ xpos];
}*/
// display the sample time, delay time and trigger level
//myGLCD.setBackColor( 0, 0, 255);
/*myGLCD.setFont( SmallFont);
myGLCD.setColor (255, 255,255);
myGLCD.setBackColor( 0, 0,255);
myGLCD.print("Delay", 260, 5);
myGLCD.print("     ", 270, 20);
myGLCD.print(itoa ( dTime, buf, 10), 270, 20);
myGLCD.print("Trig.", 260, 60);
myGLCD.print("   ", 270, 75);
myGLCD.print(itoa( Trigger, buf, 10), 270, 75);
SampleTime =( EndSample/1000-StartSample/1000);
myGLCD.print("mSec.", 260, 170);
myGLCD.print("   ", 270, 190);
myGLCD.printNumF(SampleTime, 2, 260, 190);
if (port == 0)myGLCD.print("Pulse", 260, 120);
if (port == 1)myGLCD.print("Temp", 260, 120);
if (port == 2)myGLCD.print("GSR", 260, 120);
myGLCD.print( itoa( port, buf, 10), 270, 135);

myGLCD.setBackColor( 0, 0, 0);
myGLCD.setFont( BigFont);
myGLCD.print("Pulse", 10, 175);
myGLCD.print("Temp", 100, 175);
myGLCD.print("GSR", 180, 175);
myGLCD.setColor (0, 255, 0);

myGLCD.print(itoa( Sample[ 0]//analogRead(A0)
*4.15/10.23, buf, 10), 10, 200);

myGLCD.print( itoa( Sample[ 1]//analogRead(A1)
*4.15/10.23, buf, 10),100, 200);

myGLCD.print(itoa( Sample[ 2]//analogRead(A2 )
*4.15/10.23, buf, 10),180 ,200);
*/
}}



