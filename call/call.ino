#include <LGSM.h>

String command;
String number = "";
char charbuffer[20];

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  while (Serial.available() > 0)
  {
    check();
  }
}

void check()
{
  command = Serial.readString();
  if (command.substring(0, 1).equals("C"))
  {
    number = command.substring(1, command.length());
    call();
  }
}

void call()
{
  if (number.length() < 20)
  {
    number.toCharArray(charbuffer, 20);
    if (LVoiceCall.voiceCall(charbuffer))
    {
      Serial.println("call eshtablished");
      while (Serial.available() <= 0)
      {
      }
      if (Serial.available() > 0)
      {
        if(Serial.readString()=="0"){
        if (LVoiceCall.hangCall())
        {
          Serial.println("call ended");
          return;
        }
        }
      }
    }
  }
}
