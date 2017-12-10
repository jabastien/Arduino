#include <avr/pgmspace.h>

class MenuState {
  public:
    MenuState(uint8_t menu_size, PGM_P * menu_labels); 
    void  printMenu();
  private:
    PGM_P * _menu_labels; // Same as const char * _menu_labels;
    uint8_t  _menu_size;
};

MenuState::MenuState(uint8_t menu_size, PGM_P * menu_labels){
  this->_menu_size = menu_size;
  this->_menu_labels = menu_labels;
}
  
void MenuState::printMenu(){ 
  char buf[20]; 
  for ( uint8_t i = 0 ; i < _menu_size; i++ ) {
    // This is the same as the code in setup but substitute _menu_labels for MAIN_MENU_LABELS
    const char * menu_pgm_ptr = (PGM_P)pgm_read_word(&(_menu_labels[i]));
    strcpy_P(buf,menu_pgm_ptr);
    Serial.println(buf);
  }
}

const uint8_t MAIN_MENU_SIZE = 7;
const char main_menu_1[] PROGMEM = "Sampling";
const char main_menu_2[] PROGMEM = "Next Coll.";
const char main_menu_3[] PROGMEM = "Edit Collect.";
const char main_menu_4[] PROGMEM = "File Ops.";
const char main_menu_5[] PROGMEM = "Review Current";
const char main_menu_6[] PROGMEM = "Diagnostics";
const char main_menu_7[] PROGMEM = "Power off";
PGM_P const MAIN_MENU_LABELS[MAIN_MENU_SIZE] PROGMEM = {main_menu_1,main_menu_2,main_menu_3,main_menu_4,main_menu_5,main_menu_6,main_menu_7};
// same as 
//const char * const MAIN_MENU_LABELS[MAIN_MENU_SIZE] PROGMEM = {main_menu_1,main_menu_2,main_menu_3,main_menu_4,main_menu_5,main_menu_6,main_menu_7};

MenuState testMenu(MAIN_MENU_SIZE,(PGM_P *) MAIN_MENU_LABELS);


void setup() {
  char buf[20];
  Serial.begin(115200);
  
  // I can print out a single menu item like this:
  strcpy_P(buf,main_menu_1);
  Serial.println(buf);
  
  // To get the same thing out of MAIN_MENU_LABELS,
  // MAIN_MENU_LABELS[1] should be the pointer to main_menu_2 in PROGMEM
  const char * menu_pgm_ptr = (PGM_P)pgm_read_word(&(MAIN_MENU_LABELS[1]));
  
  // So menu_pgm_ptr is a pointer to a string in program space.
  strcpy_P(buf,menu_pgm_ptr);
  Serial.println(buf); // And that works too!
  Serial.println("Now the hard way");
  testMenu.printMenu();
}

void loop() {}
