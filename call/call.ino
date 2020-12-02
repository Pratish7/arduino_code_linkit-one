#include <LGSM.h>

String command;
String number = "";
char charbuffer[20];

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  Serial.println("READY");
  while (Serial.available() <= 0)
  {
  }
  if (Serial.available() > 0)
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
    return;
  }
}

void call()
{
  if (number.length() < 20)
  {
    number.toCharArray(charbuffer, 20);
    if (LVoiceCall.voiceCall(charbuffer))
    {
      Serial.println("called");
      while (Serial.available() <= 0)
      {
      }
      if (Serial.available() > 0)
      {
        if (Serial.readString() == "0")
        {
          if (LVoiceCall.hangCall())
          {
            Serial.println("CALL RUNNING");
            number = "";
            return;
          }
          else
          {
            number = "";
            return;
          }
        }
      }
    }
    else
    {
      Serial.print("CALL FAILED");
      number = "";
      return;
    }
  }
  else
  {
    Serial.print("CALL FAILED");
    number = "";
    return;
  }
}
