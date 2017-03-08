/*
  ESP8266 AWS IoT gateway - Test code

  Simple test code for the gateway. Upload this to Arduino and connect it to the IoT gateway.
  This code will upload test values once every 10 seconds to MyThing1 and MyThing2 through your gateway. 
  
  created   Mar 2017
  by CheapskateProjects

  ---------------------------
  The MIT License (MIT)

  Copyright (c) 2017 CheapskateProjects

  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

void setup()
{
  Serial.begin(115200);
  delay(5000);// Wait for ESP8266 to initialize
}

int tmp = 0;
void loop()
{
  String message1 = "MyThing1;{\"state\":{\"reported\":{\"test_value1\":111, \"test_value2\":";
  message1 += tmp;
  message1 += "}}}";
  Serial.println(message1);

  delay(1000);
  
  String message2 = "MyThing2;{\"state\":{\"reported\":{\"test_value1\":222, \"test_value2\":";
  message2 += tmp;
  message2 += "}}}";
  Serial.println(message2);

  tmp++;
  
  delay(10000);
}

