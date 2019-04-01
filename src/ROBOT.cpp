#include "ROBOT.h"

ROBOT::ROBOT(YETI_YUKON &rYukon) : Yukon(rYukon),
    DriveRight(_DriveRightPWM, &Yukon.PWM, _DriveRightDir, _DriveRightReversed), 
    DriveLeft(_DriveLeftPWM, &Yukon.PWM, _DriveLeftDir, _DriveLeftReversed), 
    LiftMotor(_LiftMotorPWM, &Yukon.PWM, _LiftMotorDir, _LiftMotorReversed), 
    ClawMotor(_ClawMotorPWM, &Yukon.PWM, _ClawMotorDir, _ClawMotorReversed), 
    BuddyBotLift(_BuddyBotLiftPWM, &Yukon.PWM, _BuddyBotLiftDir, _BuddyBotLiftReversed),
    BallThrowerMotor(_BallThrowerPWM, &Yukon.PWM, _BallThrowerDir, _BallThrowerReversed), 
    BallIntakeMotor(_BallIntakePWM, &Yukon.PWM, _BallIntakeDir, _BallIntakeReversed),
    Drive(*this),
    Lift(*this),
    Claw(*this),
    BuddyBot(*this),
    BallThrower(*this),
    BallIntake(*this),
    Auton(*this),
    Xbox(&Usb)
    

{
}

void ROBOT::Setup()
{
    Usb.Init();
    DriveLeft.Init();
    DriveRight.Init();
    LiftMotor.Init();
    ClawMotor.Init();
    BuddyBotLift.Init();
    BallThrowerMotor.Init();
    BallIntakeMotor.Init();
    BTserial.begin("C3604R");

    pinMode(_Button0, INPUT_PULLUP);
    pinMode(_LEDBuiltIn, OUTPUT);
}

void ROBOT::GeneralTask()
{
    if (digitalRead(_Button0) == LOW)
    {
        delay(1000);
        if (digitalRead(_Button0) == LOW)
        {
            Yukon.DisableWatchdog();

            Yukon.OLED.clear();
            Yukon.OLED.drawString(0, 0, "GYRO CALIBRATION!");
            Yukon.OLED.display();

            delay(1000);
            Yukon.GYRO.RunCalibration();
        }
        else
        {
            //else toggle wifi
            Yukon.ToggleWIFI();
        }
    }
    //Read The Light Sensor
    uint16_t LightSensorVal = analogRead(33);

    //Keep track of the max light sensor value since power on.
    if (LightSensorVal > MaxLightSensorVal)
        MaxLightSensorVal = LightSensorVal;

    // Make sure the light sensor pin hasn't been detecting light since the robot turned on.
    // This is a sign that the light sensor may be disconnected, or is not shielded enough.
    // Or that the threshold is set too close to zero.
    if (MaxLightSensorVal > _AutonLightSensorThreshold)
    {
        bool tempActive = (LightSensorVal <= _AutonLightSensorThreshold);

        if (State.AutonLightSensorActive != tempActive)
        {
            //Change in light sensor
            if (State.AutonLightSensorState > 0)
                State.AutonLightSensorState++;

            switch (State.AutonLightSensorState)
            {
            case 4:
                Yukon.Disable();
            case 5:
                Yukon.Enable();
            }

            State.AutonLightSensorActive = tempActive;
        }
    }
}

void ROBOT::WriteRobot()
{
    if (Yukon.IsDisabled())
    {
    DriveLeft.SetMotorSpeed(0);
    DriveRight.SetMotorSpeed(0);
    LiftMotor.SetMotorSpeed(0);
    ClawMotor.SetMotorSpeed(0);
    BuddyBotLift.SetMotorSpeed(0);
    BallThrowerMotor.SetMotorSpeed(0);
    BallIntakeMotor.SetMotorSpeed(0);
    }
    else
    {

    DriveLeft.SetMotorSpeed(State.DriveLeftSpeed);
    DriveRight.SetMotorSpeed(State.DriveRightSpeed);
    LiftMotor.SetMotorSpeed(State.LiftMotorSpeed);
    ClawMotor.SetMotorSpeed(State.ClawMotorSpeed);
    BuddyBotLift.SetMotorSpeed(State.BuddyBotLiftSpeed);
    BallThrowerMotor.SetMotorSpeed(State.BallThrowerMotorSpeed);
    BallIntakeMotor.SetMotorSpeed(State.BallIntakeMotorSpeed);
    }
}

void ROBOT::USBOIGYRO()
{
     //Read The Controller
    Usb.Task();
    
        if (Xbox.XboxReceiverConnected)
        {
        for (uint8_t i = 0; i < 4; i++)
        {
        if (Xbox.Xbox360Connected[i])
        {  
        CurrentRightSpeed= (Yukon.XBOXJoystickTo255(Xbox.getAnalogHat(LeftHatY, i), 7500));
        CurrentLeftSpeed = (Yukon.XBOXJoystickTo255(Xbox.getAnalogHat(RightHatY, i), 7500));

        if(CapMode == true)
        {
         LiftSpeed = (Xbox.getButtonPress(R2, i) - Xbox.getButtonPress(L2, i));
         ClawSpeed = (Xbox.getButtonPress(A))*255;
         BuddyLiftSpeed = ((Xbox.getButtonPress(R1, i)*255) - (Xbox.getButtonPress(L1, i)*255));
        }
        if(!CapMode)
        {
         BallThrowerSpeed = ((Xbox.getButtonPress(R1, i)*255) - (Xbox.getButtonPress(L1, i)*255));
         BallIntakeSpeed = (Xbox.getButtonPress(R2, i) - Xbox.getButtonPress(L2, i));
        }
        Drive.OISetSpeed(CurrentLeftSpeed, CurrentRightSpeed);
        Lift.OISetSpeed(LiftSpeed*0.5);
        Claw.OISetSpeed(ClawSpeed);
        BuddyBot.OISetSpeed(BuddyLiftSpeed);
        BallThrower.OISetSpeed(BallThrowerSpeed);
        BallIntake.OISetSpeed(BallIntakeSpeed);

        //This changes the drive mode from 2 joysticks to 1
        if(IsArcadeMode)
        {
            CurrentRightSpeed =  (Yukon.XBOXJoystickTo255(Xbox.getAnalogHat(LeftHatX, i), 7500)) + (Yukon.XBOXJoystickTo255(Xbox.getAnalogHat(LeftHatY, i), 7500));
            CurrentLeftSpeed =   (Yukon.XBOXJoystickTo255(Xbox.getAnalogHat(LeftHatY, i), 7500)) -  (Yukon.XBOXJoystickTo255(Xbox.getAnalogHat(LeftHatX, i), 7500));
        }

        //This cuts all drive inputs by half for more precise movement
        if(PrecisionMode)
        {
            CurrentLeftSpeed = CurrentLeftSpeed * .5;
            CurrentRightSpeed = CurrentRightSpeed  * .5;
        }

        //Controller Mapping
        //Be sure to note the diiference between buttonclick and buttonpress!!!
        if (Xbox.getButtonClick(LEFT))
        Auton.QueuePrev();
        
        if (Xbox.getButtonClick(RIGHT))
        Auton.QueueNext();

        if(Auton.QueuedProgramName() != "")
        {
            BlinkLed3(Auton._QueuedProgramNumber);
        }

        if (Xbox.getButtonClick(DOWN))
        Auton.ToggleArmed();
        
        if (Xbox.getButtonClick(R3))
        EmergencyStop = !EmergencyStop;

        if (Xbox.getButtonClick(Y))
        PrecisionMode = !PrecisionMode;

        if (Xbox.getButtonClick(X))
        {
            if (Auton.IsRunning())
            {
                Yukon.Disable();
            }
            else
            {
                Auton.LaunchQueued();
            }
        }

        if (Xbox.getButtonClick(B))
        IsArcadeMode = !IsArcadeMode;
        
        if (Xbox.getButtonClick(BACK))
        ToggleBt();

        if (Xbox.getButtonClick(START))
        CapMode = !CapMode;
        
        if (Xbox.getButtonClick(L3))
        Parking = !Parking;
        
        if (Xbox.getButtonClick(XBOX)) 
        Auton.ToggleLockArmed();
        }
        }
        }
       
    Yukon.GYRO.Loop();
}
int ScreenToShow = 0;
unsigned long SecondsPerScreen = 5000;
unsigned long NextScreen = SecondsPerScreen;

void ROBOT::OLEDLoop()
{
    if (Auton.IsArmLocked())
    {
        Yukon.OLED.clear();
        Yukon.OLED.drawString(0, 0, "LOCKED! ");
        Yukon.OLED.drawString(0, 10, Auton.QueuedProgramName());
        Yukon.OLED.display();
    }
    else if (Auton.IsArmed())
    {
        Yukon.OLED.clear();
        Yukon.OLED.drawString(0, 0, "ARMED " + String(LightSensorVal));
        Yukon.OLED.drawString(0, 10, Auton.QueuedProgramName());
        Yukon.OLED.display();
    }
    else if (Auton.QueuedProgramName() != "")
    {
        Yukon.OLED.clear();
        Yukon.OLED.drawString(0, 0, Auton.QueuedProgramName());
        Yukon.OLED.display();
    }
    else
    {
        if (State.AutonLightSensorActive)
        {
            Yukon.OLED.invertDisplay();
        }
        else
        {
            Yukon.OLED.normalDisplay();
        }


        if (ScreenToShow == 0)
        {
            Yukon.OLED.clear();
            Yukon.OLED.setFont(ArialMT_Plain_16);
            Yukon.OLED.drawString(0, 48, "Head: " + String(Yukon.GYRO.Heading()));
            Yukon.OLED.display();

            if (millis() > NextScreen)
            {
                ScreenToShow++;
                NextScreen = millis() + SecondsPerScreen;
            }
        }
        else if (ScreenToShow == 1)
        {

            Yukon.OLED.clear();
            Yukon.OLED.setFont(ArialMT_Plain_16);
            Yukon.OLED.drawString(0, 0, "Ch A: " + String(Yukon.ChAVolts()));
            Yukon.OLED.drawString(0, 16, "Ch B: " + String(Yukon.ChBVolts()));
            Yukon.OLED.drawString(0, 32, "Ch C: " + String(Yukon.ChCVolts()));
            Yukon.OLED.drawString(0, 48, "LS: " + String(State.AutonLightSensorState));
            Yukon.OLED.display();

            if (millis() > NextScreen)
            {
                ScreenToShow = 0;
                NextScreen = millis() + SecondsPerScreen;
            }
        }
    }
}