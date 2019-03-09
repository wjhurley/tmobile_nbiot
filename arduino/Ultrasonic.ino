#include <board.h>
#include <BreakoutSDK.h>
#include <stdio.h>
// Install https://github.com/Seeed-Studio/Grove_Ultrasonic_Ranger
#include <Ultrasonic.h>

/** Change this to your device purpose */
static const char *device_purpose = "Dev-Kit";
/** Change this to your key for the SIM card inserted in this device 
 *  You can find your PSK under the Breakout SDK tab of your Narrowband SIM detail at
 *  https://www.twilio.com/console/wireless/sims
*/
static const char *psk_key = "79994415e0fd87d2a445ab6f3aedd5b4";

/** This is the Breakout SDK top API */
Breakout *breakout = &Breakout::getInstance();

#define ULTRASONIC_PIN  (38)
#define INTERVAL        (2000)

Ultrasonic UltrasonicRanger(ULTRASONIC_PIN);

/**
 * Setting up the Arduino platform. This is executed once, at reset.
 */
void setup() {
  pinMode(38, INPUT);
  
  // Feel free to change the log verbosity. E.g. from most critical to most verbose:
  //   - errors: L_ALERT, L_CRIT, L_ERR, L_ISSUE
  //   - warnings: L_WARN, L_NOTICE
  //   - information & debug: L_INFO, L_DB, L_DBG, L_MEM
  // When logging, the additional L_CLI level ensure that the output will always be visible, no matter the set level.
  owl_log_set_level(L_INFO);
  LOG(L_WARN, "Arduino setup() starting up\r\n");

  // Set the Breakout SDK parameters
  breakout->setPurpose(device_purpose);
  breakout->setPSKKey(psk_key);
  breakout->setPollingInterval(1 * 60);  // Optional, by default set to 10 minutes
  
  // Powering the modem and starting up the SDK
  LOG(L_WARN, "Powering on module and registering...");
  breakout->powerModuleOn();
  
  LOG(L_WARN, "... done powering on and registering.\r\n");
  LOG(L_WARN, "Arduino loop() starting up\r\n");
}


/**
 * This is just a simple example to send a command and write out the status to the console.
 */
 
void sendCommand(const char * command) {
  if (breakout->sendTextCommand(command) == COMMAND_STATUS_OK) {
    LOG(L_INFO, "Tx-Command [%s]\r\n", command);
  } else {
    LOG(L_INFO, "Tx-Command ERROR\r\n");
  }
}

void loop(){
  long distance;
  distance = UltrasonicRanger.MeasureInCentimeters();
  
  char commandText[512];
  snprintf(commandText, 50, "Available space changed to [%d] CM", distance);
  sendCommand(commandText);
  
  LOG(L_INFO, "Object is [%ld] CM from the sensor\r\n", distance );

  breakout->spin();
  
  delay(INTERVAL);
}
