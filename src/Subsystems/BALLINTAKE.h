
#pragma once

#include <Arduino.h>
#include <YUKON_COMMAND.h>

class ROBOT;

class BALLINTAKE : public YUKON_COMMAND
{

    public:
        BALLINTAKE(ROBOT &refRobot);
        ROBOT &Robot;

        void Loop();

        void OISetSpeed(int16_t BallIntakeMotorSpeed);

        bool ForAsync(long durationMS, int16_t BallIntakeMotorSpeed, float SlowDown, uint8_t HoldPercent);

        //Each Sensor
        


    private:
        int16_t _CmdBallIntakeMotorSpeed = 0;
        int16_t _OIBallIntakeMotorSpeed = 0;


};
