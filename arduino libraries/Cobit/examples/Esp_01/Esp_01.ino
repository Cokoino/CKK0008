#include <cobit.h>
#include <SoftwareSerial.h>
#define RX      12
#define TX      13
/*
Basic AT Commands
AT: Test AT startup.
AT+RST: Restart a module.
AT+GMR: Check version information.
AT+CMD: List all AT commands and types supported in current firmware.
AT+GSLP: Enter Deep-sleep mode.
ATE: Configure AT commands echoing.
AT+RESTORE: Restore factory default settings of the module.
AT+UART_CUR: Current UART configuration, not saved in flash.
AT+UART_DEF: Default UART configuration, saved in flash.
AT+SLEEP: Set the sleep mode.
AT+SYSRAM: Query current remaining heap size and minimum heap size.
AT+SYSMSG: Query/Set System Prompt Information.
AT+USERRAM: Operate user’s free RAM.
AT+SYSFLASH: Query/Set User Partitions in Flash.
AT+RFPOWER: Query/Set RF TX Power.
AT+SYSROLLBACK: Roll back to the previous firmware.
AT+SYSTIMESTAMP: Query/Set local time stamp.
AT+SYSLOG: Enable or disable the AT error code prompt.
AT+SLEEPWKCFG: Query/Set the light-sleep wakeup source and awake GPIO.
AT+SYSSTORE: Query/Set parameter store mode.
AT+SYSREG: Read/write the register.

Wi-Fi AT Commands
AT+CWMODE: Set the Wi-Fi mode (Station/SoftAP/Station+SoftAP).
AT+CWSTATE: Query the Wi-Fi state and Wi-Fi information.
AT+CWJAP: Connect to an AP.
AT+CWRECONNCFG: Query/Set the Wi-Fi reconnecting configuration.
AT+CWLAPOPT: Set the configuration for the command AT+CWLAP.
AT+CWLAP: List available APs.
AT+CWQAP: Disconnect from an AP.
AT+CWSAP: Query/Set the configuration of an ESP SoftAP.
AT+CWLIF: Obtain IP address of the station that connects to an ESP SoftAP.
AT+CWQIF: Disconnect stations from an ESP SoftAP.
AT+CWDHCP: Enable/disable DHCP.
AT+CWDHCPS: Query/Set the IP addresses allocated by an ESP SoftAP DHCP server.
AT+CWAUTOCONN: Connect to an AP automatically when powered on.
AT+CWAPPROTO: Query/Set the 802.11 b/g/n protocol standard of SoftAP mode.
AT+CWSTAPROTO: Query/Set the 802.11 b/g/n protocol standard of station mode.
AT+CIPSTAMAC: Query/Set the MAC address of an ESP station.
AT+CIPAPMAC: Query/Set the MAC address of an ESP SoftAP.
AT+CIPSTA: Query/Set the IP address of an ESP station.
AT+CIPAP: Query/Set the IP address of an ESP SoftAP.
AT+CWSTARTSMART: Start SmartConfig.
AT+CWSTOPSMART: Stop SmartConfig.
AT+WPS: Enable the WPS function.
AT+MDNS: Configure the mDNS function.
AT+CWHOSTNAME: Query/Set the host name of an ESP station.
AT+CWCOUNTRY: Query/Set the Wi-Fi Country Code.
*/

//Arduino SoftwareSerial: https://www.arduino.cc/en/Reference/SoftwareSerial
SoftwareSerial EspSerial(RX, TX);

#define DEBUG true 
#define IP "184.106.153.149"                                // ThingSpeak.com ip,the default is fixed.
String Api_key = "GET /update?key=Your thingspeak Api Key"; //change it with your api key like "GET /update?key=Your Api Key"

cobit Car;
int error;
float dat; 
long int old_t;
////////////////////////////////////////////////////////////
String send_command(String command, const int timeout, boolean debug)
{
  String response = "";
  EspSerial.print(command);
  long int time = millis();
  while ( (time + timeout) > millis()){
    while (EspSerial.available()){
      char c = EspSerial.read();
      response += c;
    }
  }
  if (debug){
    Serial.print(response);
  }
  return response;
}

////////////////////////////////////////////////////////////
void updatedata(){
  String command = "AT+CIPSTART=\"TCP\",\"";
  command += IP;
  command += "\",80";
  Serial.println(command);
  EspSerial.println(command);
  delay(2000);
  if(EspSerial.find("Error")){
    return;
  }
  command = Api_key ;
  command += "&field1=";   
  command += dat;
  command += "\r\n";
  Serial.print("AT+CIPSEND=");
  EspSerial.print("AT+CIPSEND=");
  Serial.println(command.length());
  EspSerial.println(command.length());
  if(EspSerial.find(">")){
    Serial.print(command);
    EspSerial.print(command);
  }
  else{
   Serial.println("AT+CIPCLOSE");
   EspSerial.println("AT+CIPCLOSE");
    //Resend...
    error=1;
  }
}
  
////////////////////////////////////////////////////////////
void setup(){  
  Serial.begin(9600);
  EspSerial.begin(115200);
  
  Car.Reset_chip();                                                        //Reset N76E003. This function must be used once within the setup function.
  delay(100);						

  send_command("AT+RST\r\n", 2000, DEBUG);                                 //reset module
  send_command("AT+CWMODE=1\r\n", 1000, DEBUG);                            //set station mode
  send_command("AT+CWJAP=\"Your wifi name\",\"Your wifi password\"\r\n", 0, DEBUG);   //connect wifi network
  while(!EspSerial.find("OK")) {                                           //wait for connection
  Serial.println("Connecting ...");
  }
  Serial.println("connect success");
}

////////////////////////////////////////////////////////////
void loop() {
  if(millis() > old_t+10000){  //Refresh every 10second
    old_t = millis();
    dat = Car.Right_PR();     //Data that you want to send to Thingspeak.
    start:                    //label 
    error=0;
    updatedata();             //Upload data to thinkspeak
    if (error==1){
      goto start;             //go to label "start"
    }
  }
  delay(100);
}




