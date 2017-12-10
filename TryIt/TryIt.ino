
class foo {

  public:

    char doInt8_t_0 (int8_t v){ return '0' + v / 100;  } // - (v/1000) * 10;
    char doInt8_t_1 (int8_t v){ return '0' + v / 10         - (v/100)  * 10; }
    char doInt8_t_2 (int8_t v){ return '0' + v / 1          - (v/10)   * 10; }


   // typedef for class function
   typedef char (foo::*int8_t_Function) (int8_t);

   // array of function pointers
    int8_t_Function doInt8_t_sArray [3] =
    {
      &foo::doInt8_t_0, 
      &foo::doInt8_t_1, 
      &foo::doInt8_t_2, 
    };

};  // end of class foo



  /////////////////////////////////////////////////////////////
  static char line   [10];  
  // test instance of foo
  foo bar;
  /////////////////////////////////////////////////////////////
  template <typename T> T setSign (T number){ // Return value of 'T'
    if (number < 0){ // Can't be negative.
      number = -number;
      line[0] = '-';
    }
    else{
      line[0]=' ';
    }
    
    return number;
    }  // end of setSign

  /////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////
  char * editor(int8_t number, char pattern[]){

  strcpy(line, pattern );

  number = setSign(number);

  int digit = 0;

  for (int pos = 0; pattern[pos] != '\0'; pos++)
    {
      if (pattern[pos] == '_'){
        // get member function pointer from array
        foo::int8_t_Function f = bar.foo::doInt8_t_sArray [digit];
        // call the function
        line[pos]=( (bar.*f) (number));
        digit++;   
      }
    }  // end of for loop
  return line;  
}


void setup ()
{
  Serial.begin (115200);
  Serial.println ();
  Serial.println (F("Starting"));

  int8_t number =  98;
  char pattern[  ] = "*__._V";

  Serial.println(editor(number, pattern));  
  Serial.println(pattern);
}  // end of setup

void loop () { }

