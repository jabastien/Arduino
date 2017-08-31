#include <MyLib.h>

void setup() {
  Serial.begin(115200);
  int i = 5;
  int j = 3;
  int result;
  result = MyLib.addem(i, j);
  Serial.print("The result of adding them is ");
  Serial.println(result);
  result = MyLib.subem(i, j);
  Serial.print("The result of subtracting them is ");
  Serial.println(result);
  result = MyLib.multem(i, j);
  Serial.print("The result of multiplying them is ");
  Serial.println(result);
}

void loop() {
}
