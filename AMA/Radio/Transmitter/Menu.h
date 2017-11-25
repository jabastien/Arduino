//https://arduino.stackexchange.com/questions/21095/how-to-write-array-of-functions-in-arduino-library

/*
class foo {

  public:

   void doAction0 ()
    {
      Serial.println (0);
    }

    void doAction1 ()
    {
      Serial.println (1);
    }

    void doAction2 ()
    {
      Serial.println (2);
    }

    void doAction3 ()
    {
      Serial.println (3);
    }

    void doAction4 ()
    {
      Serial.println (4);
    }

   // typedef for class function
   typedef void (foo::*GeneralFunction) ();

   // array of function pointers
    GeneralFunction doActionsArray [5] =
    {
      &foo::doAction0, 
      &foo::doAction1, 
      &foo::doAction2, 
      &foo::doAction3, 
      &foo::doAction4, 
    };

};  // end of class foo

void setup ()
{
  Serial.begin (115200);
  Serial.println ();
  Serial.println (F("Starting"));

  // test instance of foo
  foo bar;

  for (int i = 0; i < 5; i++)
    {
    // get member function pointer from array
    foo::GeneralFunction f = bar.foo::doActionsArray [i];
    // call the function
    (bar.*f) ();
    }  // end of for loop

}  // end of setup

void loop () { }
*/
