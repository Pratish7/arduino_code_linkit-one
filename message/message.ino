#include <LGSM.h>

String command;
String number = "";
char charbuffer[20];
String sms_text;

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
  if (command.substring(0, 1).equals("S"))
  {
    msg();
    return;
  }
}

void msg()
{
  for (int i = 0; i < command.length(); i++)
  {
    if (command.substring(i, i + 1).equals("T"))
    {
      sms_text = command.substring(i + 1, command.length());
      number = command.substring(1, i);
    }
    else{
      return;
    }
  }
  if (sms_text.length() > 0)
  {
    number.toCharArray(charbuffer, 20);
    LSMS.beginSMS(charbuffer);
    LSMS.print(sms_text);
    if (LSMS.endSMS())
    {
      Serial.println("MESSAGE SENT");
      return;
    }
    else
    {
      Serial.println("FAILED");
      return;
    }
  }
  else{
    return;
  }
}
