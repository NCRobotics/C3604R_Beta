#ifndef ROBOT_h
#define ROBOT_h

#include <YETI_YUKON.h>
#include <STATE.h>
#include <XBOXRECV.h>

#include <YUKON_CytronMD10.h>

#include "Subsystems\Drive.h"
#include "Subsystems\Lift.h"
#include "Subsystems\Claw.h"
#include "Subsystems\BuddyBot.h"
#include "Subsystems\BALLTHROWER.h"
#include "Subsystems\BALLINTAKE.h"

#include "Autonomous\AUTONOMOUS.h"
#include "Preferences.h"
#include "Preferences.h"
#include "SPIFFS.h"
#include "FS.h"
#include "BluetoothSerial.h"
#include "YUKON_MPU6050.h"

class ROBOT
{
  public:
    ROBOT(YETI_YUKON &rYukon);

    void Setup();
    void GeneralTask();

    void WriteRobot();
    void USBOIGYRO();
    void OLEDLoop();

    YETI_YUKON &Yukon;

    STATE State;

    //Motors
    YUKON_CytronMD10 DriveRight;
    YUKON_CytronMD10 DriveLeft;
    YUKON_CytronMD10 LiftMotor;
    YUKON_CytronMD10 ClawMotor;
    YUKON_CytronMD10 BuddyBotLift;
    YUKON_CytronMD10 BallThrowerMotor;
    YUKON_CytronMD10 BallIntakeMotor;
    //Sensors

    //Subsystems
    DRIVE Drive;
    LIFT Lift;
    CLAW Claw;
    BUDDYBOT BuddyBot;
    BALLTHROWER BallThrower;
    BALLINTAKE BallIntake;
    AUTONOMOUS Auton;

    //USB Items
    USB Usb;
    Preferences preferences;
    XBOXRECV Xbox;
    BluetoothSerial BTserial;
    YUKON_MPU6050 mpu;
    
    //Variables for different modes
    bool PrecisionMode = false;
    bool IsArcadeMode = false;
    bool IsNoLimits = false;
    bool IsDebugMode = false;
    bool BTActive = true;
    bool EmergencyStop = false;
    bool ReadingAuton =false;
    bool CapMode = true;
    bool Parking = true;
    //Vars for speed checks
    float _NextSpeedUpdateMillis = 0;
    //Array Definitions
    volatile int16_t DriveRightSpeeds [750];
    volatile int16_t DriveLeftSpeeds [750];
    volatile int16_t LiftSpeeds [750];
    volatile int16_t ClawSpeeds [750];
    volatile int16_t BuddyBotSpeeds [750];
    //Speed Variable Definitions   
    int16_t CurrentRightSpeed = 0;
    int16_t CurrentLeftSpeed = 0;
    int16_t LiftSpeed = 0;
    int16_t ClawSpeed = 0;
    int16_t BuddyLiftSpeed = 0;
    int16_t BallThrowerSpeed = 0;
    int16_t BallIntakeSpeed = 0;
    //Pointer Definitions
    //Auton Recording
    const char *basepath = "/spiffs";
    const char *rightarraypath ="/spiifs/AutonRecording/DriveRightSpeeds";
    int ArrayPos = 0;
    int ArrayProg = 0;
    bool Recording = false;
    bool FirstTry = true;
    bool RecordMode = false;
    long _NextAutonMillis = 0;
    int _ToBlink = 0;

    void ToggleBt()
    {
      BTActive = !BTActive;
      if(!BTActive)
      {
        BTserial.end();
      }
      if(BTActive)
      {
        BTserial.begin("C3604R");
      }
        }
    
    void BlinkLed3(int NumberofBlinks)
    { _ToBlink = NumberofBlinks;
      while(_ToBlink != 0)
      {
      Xbox.setLedOn(LED3, 1);
      delay(1000);
      Xbox.setLedOff(1);
      _ToBlink--;
      }
    }
    
    ///PIN Declarations
    static const int _DriveRightPWM = 0;
    static const int _DriveRightDir = 17; //14;
    static const bool _DriveRightReversed = true;
        
    static const int _DriveLeftPWM = 1;
    static const int _DriveLeftDir = 14;//17;
    static const bool _DriveLeftReversed = false;
        
    static const int _LiftMotorPWM = 4;//2;
    static const int _LiftMotorDir = 26;//22;
    static const bool _LiftMotorReversed = false;
        
    static const int _ClawMotorPWM = 3;
    static const int _ClawMotorDir = 21;
    static const bool _ClawMotorReversed = false;
        
    static const int _BuddyBotLiftPWM = 3;//4;
    static const int _BuddyBotLiftDir = 22;//26;
    static const bool _BuddyBotLiftReversed = false;

    static const int _BallThrowerPWM = 5;
    static const int _BallThrowerDir = 27;
    static const bool _BallThrowerReversed = false;

    static const int _BallIntakePWM = 6;
    static const int _BallIntakeDir = 32;
    static const bool _BallIntakeReversed = false;
      
    static const uint8_t _Button0 = 0;
    static const uint8_t _LEDBuiltIn = 25;
    static const uint8_t _AutonLightSensor = 0;
    
    static const uint16_t _AutonLightSensorThreshold = 3000; //Value 0 - 1024

  private:
    uint16_t LightSensorVal = 0;
    uint16_t MaxLightSensorVal = 0;
};

#endif