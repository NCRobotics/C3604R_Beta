
#pragma once

#include <Arduino.h>
#include <YUKON_COMMAND.h>

class ROBOT;

class BALLTHROWER : public YUKON_COMMAND
{

    public:
        BALLTHROWER(ROBOT &refRobot);
        ROBOT &Robot;

        void Loop();

        void OISetSpeed(int16_t BallThrowerMotorSpeed);

        bool ForAsync(long durationMS, int16_t BallThrowerMotorSpeed, float SlowDown, uint8_t HoldPercent);

        //Each Sensor
        


    private:
        int16_t _CmdBallThrowerMotorSpeed = 0;
        int16_t _OIBallThrowerMotorSpeed = 0;


};
