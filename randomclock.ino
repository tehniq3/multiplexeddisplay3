//https://www.jameco.com/jameco/workshop/techtip/working-with-seven-segment-displays.html
// original sketch was for two digit multiplexed display demo.
// Nicu FLORICA (niq_ro) change for 4 digit multiplexed display

int segPins[] = {0, 1, 2, 3, 4, 5, 6, 7 }; 
int displayPins[] = {8, 9,10, 11};   // pin 8 controls D0, pin 9 controls D1, pin 10 control D2, pin 11 control D3
int displayBuf[4];                 // The display buffer contains the digits to be displayed.
                                      // displayBuf[0] contains the LSD, displayBuf[3] contains the MSD

byte segCode[22][8] = {
// 7 segment code table
//  a  b  c  d  e  f  g  .  
  { 1, 1, 1, 1, 1, 1, 0, 0},  // 0
  { 0, 1, 1, 0, 0, 0, 0, 0},  // 1
  { 1, 1, 0, 1, 1, 0, 1, 0},  // 2
  { 1, 1, 1, 1, 0, 0, 1, 0},  // 3
  { 0, 1, 1, 0, 0, 1, 1, 0},  // 4
  { 1, 0, 1, 1, 0, 1, 1, 0},  // 5
  { 1, 0, 1, 1, 1, 1, 1, 0},  // 6
  { 1, 1, 1, 0, 0, 0, 0, 0},  // 7
  { 1, 1, 1, 1, 1, 1, 1, 0},  // 8  
  { 1, 1, 1, 1, 0, 1, 1, 0},  // 9 
  { 1, 1, 1, 1, 1, 1, 0, 1},  // 0.
  { 0, 1, 1, 0, 0, 0, 0, 1},  // 1.
  { 1, 1, 0, 1, 1, 0, 1, 1},  // 2.
  { 1, 1, 1, 1, 0, 0, 1, 1},  // 3.
  { 0, 1, 1, 0, 0, 1, 1, 1},  // 4.
  { 1, 0, 1, 1, 0, 1, 1, 1},  // 5.
  { 1, 0, 1, 1, 1, 1, 1, 1},  // 6.
  { 1, 1, 1, 0, 0, 0, 0, 1},  // 7.
  { 1, 1, 1, 1, 1, 1, 1, 1},  // 8.  
  { 1, 1, 1, 1, 0, 1, 1, 1},  // 9. 
  { 0, 0, 0, 0, 0, 0, 0, 0},  // space
  { 0, 0, 0, 0, 0, 0, 0, 1}   // DP  
};
   

void refreshDisplay(int digit3, int digit2, int digit1, int digit0)
{
  digitalWrite(displayPins[0], HIGH);  // displays digit 0 (least significant)
  digitalWrite(displayPins[1], HIGH);       
  digitalWrite(displayPins[2], HIGH);       
  digitalWrite(displayPins[3], LOW);       
  setSegments(digit0);                     
  delay(5);
  digitalWrite(displayPins[0], HIGH);  // displays digit 1 
  digitalWrite(displayPins[1], HIGH);       
  digitalWrite(displayPins[2], LOW);       
  digitalWrite(displayPins[3], HIGH);       
  setSegments(digit1);                     
  delay(5);
  digitalWrite(displayPins[0], HIGH);  // displays digit 2 
  digitalWrite(displayPins[1], LOW);       
  digitalWrite(displayPins[2], HIGH);       
  digitalWrite(displayPins[3], HIGH);       
  setSegments(digit2);  
  delay(5);
  digitalWrite(displayPins[0], LOW);  // displays digit 3 (most significant)
  digitalWrite(displayPins[1], HIGH);       
  digitalWrite(displayPins[2], HIGH);       
  digitalWrite(displayPins[3], HIGH);       
  setSegments(digit3);                     
  delay(5);
}

void setSegments(int n)
{
  for (int i=0; i < 8; i++)
  {
    digitalWrite(segPins[i], segCode[n][i]);
  } 
}

//***************************************************************************
//******************************************************************************
void setup()
{
  for (int i=0; i < 8; i++)
  {
    pinMode(segPins[i], OUTPUT);
  }
  pinMode(displayPins[0], OUTPUT);
  pinMode(displayPins[1], OUTPUT);
  pinMode(displayPins[2], OUTPUT);
  pinMode(displayPins[3], OUTPUT);

  displayBuf[0] = 0;    // initializes the display
  displayBuf[1] = 0;
  displayBuf[2] = 0;
  displayBuf[3] = 0;
   }

int i = 0, j = 0, k = 0;
unsigned long startTime = 0;
unsigned long startTime1 = 0;
unsigned endTime, endTime1;;
//******************************************************************************
//******************************************************************************
void loop()
{    
   
   endTime = millis();                  // increments the counter approximately once a second                       
   endTime1 = endTime;
   if ((endTime1 - startTime1) >= 5000)
   {
      i = random(24) * 100 + random(59);
      k = 0;
      startTime1 = endTime1;
   }  
   if ((endTime - startTime) >= 1000)
   {
      k = k+1;   
      j = i; 
      displayBuf[0] = j%10;                // send the updated count to the display buffer
      j = j/10;
      displayBuf[1] = j%10;
      j = j/10;
      if (k%2 == 0) displayBuf[2] = 10+j%10;
      else displayBuf[2] = j%10;
      j = j/10;
      displayBuf[3] = j;  
      startTime = endTime;
   }  
   refreshDisplay(displayBuf[3], displayBuf[2], displayBuf[1], displayBuf[0]);  // Refreshes the display with the contents of displayBuf
                                                     // each iteration of the main loop.
}
