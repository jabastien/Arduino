#include <FormatPrint.h>
FormatPrint fmt;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

float cnt = 0.0f;
void loop() {
  // put your main code here, to run repeatedly:
  cnt+= 0.001;
  fmt.printFloat(cnt, 3, 3);

  Serial.println();
}
