/*
  ESP8266 AWS IoT gateway

  Gateway which takes data from serial and updates it to AWS IoT cloud. 

  Given data should be one line consisting of thing name and JSON shadow content separated by semicolon. 
  e.g. 
  MyThing1;{"state":{"reported":{"test_value1":123, "test_value2":234}}}
  
  created   Mar 2017
  by CheapskateProjects

  ---------------------------
  The MIT License (MIT)

  Copyright (c) 2017 CheapskateProjects

  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <ESP8266WiFi.h>
#include <AmazonIOTClient.h>
#include <ESP8266AWSImplementations.h>

Esp8266HttpClient httpClient;
Esp8266DateTimeProvider dateTimeProvider;

AmazonIOTClient iotClient;
ActionError actionError;

const char* ssid = "XXX";
const char* password = "YYY";

void initWLAN()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
}

void initAWS()
{
  iotClient.setAWSRegion("eu-west-1");
  iotClient.setAWSEndpoint("amazonaws.com");
  iotClient.setAWSDomain("ZZZDOMAINZZZ");
  iotClient.setAWSPath("/things/XXX/shadow");
  iotClient.setAWSKeyID("XXXMYKEYXXX");
  iotClient.setAWSSecretKey("XXXMYSECRETXXX");
  iotClient.setHttpClient(&httpClient);
  iotClient.setDateTimeProvider(&dateTimeProvider);
}

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println("begin");
  initWLAN();
  Serial.println("wlan initialized");
  initAWS();
  Serial.println("iot initialized");
}

String name = "";
char buffer[100];
void readLine()
{
    name = "";
    int i = 0;
    bool nameEnd = false;
    while (Serial.available())
    {
      delay(3);
      if (Serial.available() >0)
      {
        char c = Serial.read();

        if(!nameEnd)
        {
          if(c == ';')
          {
            nameEnd = true;
          }
          else
          {
            name += c;
          }
        }
        else
        {
            buffer[i++] = c;
        }
      }
    }
    
    Serial.println("Got values to upload: ");
    Serial.println(name);
    Serial.print(buffer);
    Serial.println();
}

void sendLine()
{
  
  String path = "/things/";
  path = path + name;
  path = path + "/shadow";
  char pathbuffer[100];
  path.toCharArray(pathbuffer, sizeof(pathbuffer));
  iotClient.setAWSPath(pathbuffer);

  char* result = iotClient.update_shadow(buffer, actionError);
  Serial.print(result);
}

void loop()
{
  if(Serial.available())
  {
    readLine();
    sendLine();
  }
}
