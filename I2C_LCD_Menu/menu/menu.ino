   /* Rebuilt by Doug 07/02/2017 Australia.
 * This is a bare bones menu using buttons to navigate and select, there are no special libraries, 
 * I am using an I2C LCD2004, but any display will work with minor mods. This has been translated from, 
 * I believe Slovakian, that was fun, stripped down and modified for button control, I have found that 
 * buttons are less picky than rotary encoders, even the good ones, just my experience.
 * I believe that I have removed all unnecessary script, but I may have missed some.
 * look at the last 2 --page()-- sections for instruction on extending down even further, I don't think 
 * that there is a limit to how many levels you can have, how many do you really need.
 * The original sketch is from: Stanislav Petrek of Slovakia, you can find sketch on YouTube comments.
 * https://www.youtube.com/watch?v=gIP29m12wjQ&t=41s
 * Have fun with the translation  ;-}
 * The last thing I did before posting was to relaod and test this sketch, so it works.      
 */
#include <LiquidCrystal_I2C.h> //from newliquidcrystal library
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
LiquidCrystal_I2C lcd(0x27, 20, 4);  // Set the LCD I2C address

// menu system
int poz = 0; //  cursor position on actual page
int poz_max = 1;
int poz_min = 0;

int pozOld = 0;
int pozNew = 0;

int page = 0; //  actual page
int page_max = 1;
int page_min = 0;

int press = 0;
int press_max = 1;

int keypad_pin = A0;                      //analoge A0 to sense button values.
int keypad_value = 0;
int keypad_value_old = 0;

//bool menu2 = false;
char btn_push;
//****************************************************************setup*****************************************
void setup() {
Serial.begin(9600);
//lcd.begin(20, 4);
//lcd.clear();
//lcd.home();

  // LCD setup
  lcd.init();
  lcd.backlight();

  delay(2000);  
  lcd.clear();  
  
}
//************************************************************loop************************************************
void loop() {
MainmenuBtn();
if (btn_push == 'S') //enter selected menu
{
press++;
delay(250);
if (press > press_max) {
  press = 0;
}
}
// page select
switch (page) {

case 0:
  page0();
  break;
case 1:
  page1();
  break;
case 2:
  page2();
  break;
case 3:
  page3();
  break;
case 4:
  page4();
  break;
case 5:
  page5();
  break;
}
}
//****************************************************up/down************************************************
void MainmenuBtn()
{
btn_push = ReadKeypad();
WaitBtnRelease();
if (btn_push == 'U')
{
poz++;
if (poz > poz_max) {
  poz = poz_max;
}
}
else if (btn_push == 'D')
{
poz--;
if (poz < poz_min) {
  poz = poz_min;
}
}
pozNew = poz;
if (pozNew != pozOld) { //only update display when page change
pozOld = pozNew;
}
}
//*************************************************************read buttons***********************************
char ReadKeypad()
{
/* Keypad button analog Value
no button pressed 1023
*********************adjust these values to suit your keypad***********************
nul     >400
select  <400
left    <350
down    <290
up      <190
right   <50
*/
keypad_value = analogRead(keypad_pin);
if (keypad_value < 50)
return 'R';
else if (keypad_value < 190)
return 'D';
else if (keypad_value < 290)
return 'U';
else if (keypad_value < 350)
return 'L';
else if (keypad_value < 400)
return 'S';
else if (keypad_value > 400)
return 'N';
}
//********************************************************button release*************************************
void WaitBtnRelease()
{
while ( analogRead(keypad_pin) < 600) {}
}
//*******************************************************Front Page 0*******************************************
void page0() {
poz_min = 0;
poz_max = 3;
press_max = 1;

lcd.setCursor(0, 0);
lcd.print("Pg1 Pg2 Pg3 Pg4     ");
lcd.setCursor(0, 2);
lcd.print("                    ");
lcd.setCursor(0, 3);
lcd.print("                    ");

switch (poz)
{
case 0:
  lcd.setCursor(0, 1);
  lcd.print("---                 ");
  if (press == 1) {
    press = 0;
    poz = 0;
    page = 1;
  }
  break;
case 1:
  lcd.setCursor(0, 1);
  lcd.print("    ---             ");
  if (press == 1) {
    press = 0;
    poz = 0;
    page = 2;
  }
  break;
case 2:
  lcd.setCursor(0, 1);
  lcd.print("        ---         ");
  if (press == 1) {
    press = 0;
    poz = 0;
    page = 3;
  }
  break;
case 3:
  lcd.setCursor(0, 1);
  lcd.print("            ---     ");
  if (press == 1) {
    press = 0;
    poz = 0;
    page = 4;
  }
  break;
}
}
//*************************************************Pages 1*****************************************
void page1() {
poz_min = 0;
poz_max = 2;
press_max = 1;

lcd.setCursor(0, 0);
lcd.print("Page1               ");
lcd.setCursor(0, 1);
switch (poz) {

case 0:
  lcd.print("Page1 Case0         ");
  if (press == 1) {
    press = 0;
  }
  break;
case 1:
  lcd.print("Page1 Case1         ");
  if (press == 1) {
    press = 0;
  }
  break;

case 2:
  lcd.print("Page1 Case2    exit ");
  if (press == 1) {
    press = 0;
    page = 0;
    poz = 0;
  }
  break;
}
}
//*************************************************Pages 2*****************************************
void page2() {
poz_min = 0;
poz_max = 2;
press_max = 1;

lcd.setCursor(0, 0);
lcd.print("Page2               ");
lcd.setCursor(0, 1);
switch (poz) {

case 0:
  lcd.print("Page2 Case0         ");
  if (press == 1) {
    press = 0;
  }
  break;
case 1:
  lcd.print("Page2 Case1         ");
  if (press == 1) {
    press = 0;
  }
  break;

case 2:
  lcd.print("Page2 Case2  exit   ");
  if (press == 1) {
    press = 0;
    page = 0;
    poz = 1;
  }
  break;
}
}
//*************************************************Pages 3*****************************************
void page3() {
poz_min = 0;
poz_max = 2;
press_max = 1;
lcd.setCursor(0, 0);
lcd.print("Page3               ");

switch (poz)
{
case 0:
  lcd.setCursor(0, 1);
  lcd.print("Page3 Case0         ");
  if (press == 1) {
    lcd.setCursor(0, 1);
    lcd.print("                    ");
    //navi();
  }
  break;

case 1:
  lcd.setCursor(0, 1);
  lcd.print("Page3 Case1         ");
  if (press == 1) {
    press = 0;
  }
  break;

case 2:
  lcd.setCursor(0, 1);
  lcd.print("Page3 Case2  exit   ");
  if (press == 1) {
    press = 0;
    page = 0;
    poz = 2;
  }
  break;
}
}
//*************************************************Pages 4*****************************************
void page4() {
poz_min = 0;
poz_max = 1;
press_max = 1;

lcd.setCursor(0, 0);
lcd.print("Page4               ");
lcd.setCursor(0, 1);
switch (poz) {

case 0:
  lcd.print("Page4 Case0  branch ");
  if (press == 1) {
    press = 0;
    page = 5;                                   //branches to page5() menu
    poz = 0;                                    //at position 0 on button 'S' press
    break;

  case 1:
    lcd.setCursor(0, 1);
    lcd.print("Page4 Case1  exit   ");
    if (press == 1) {
      press = 0;
      page = 0;
      poz = 3;
    }
    break;
  }
  }
}
//*************************************************Pages 5*****************************************
void page5() {
poz_min = 0;                      //see void MainmenuBtn()
poz_max = 1;                      //see void MainmenuBtn()
press_max = 1;                    //used when you have multiple selection within a section-increase number
                                  //see  original script for example
lcd.setCursor(0, 0);
lcd.print("Page5               ");
lcd.setCursor(0, 1);
switch (poz) {

case 0:
  lcd.print("Page5 Case0         ");
  break;

case 1:
  lcd.setCursor(0, 1);
  lcd.print("Page5 Case1  exit   ");
  if (press == 1) {                 //variable set to '1' when the 'S' key is pressed
    press = 0;
    page = 4;                         //this is the page() that you return to after the 'S' button is pressed
    poz = 1;                          //this is the 'case' number that you will return to for that page
  }
  break;
}
}
