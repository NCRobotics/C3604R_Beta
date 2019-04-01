
#include "BALLTHROWER.h"
#include "ROBOT.h"

BALLTHROWER::BALLTHROWER(ROBOT &refRobot) : Robot(refRobot)
{
}

void BALLTHROWER::Loop()
{
    //Only Run Command Code When Valid
    if (!CmdTimedOut() && CmdIsRunning())
    {
        if (CmdName() == "ForAsync")
        {
            Robot.State.BallThrowerMotorSpeed = _CmdBallThrowerMotorSpeed;
            while (CmdUpdatePercent(millis()))
            {
                delay(20);
            }
        }
    }
    Robot.State.BallThrowerMotorSpeed = _OIBallThrowerMotorSpeed;

    delay(20);

    long nextLoopTime = millis()+20;
    //Only Run Command Code When Valid
    if (!CmdTimedOut() && CmdIsRunning())
    {
        if (CmdName() == "ForAsync")
        {
            Robot.State.BallThrowerMotorSpeed = _CmdBallThrowerMotorSpeed;
            long nextTime = millis();

            while (CmdUpdatePercent(millis()))
            {
                delay(20);
                nextTime = millis() + 25;

                int16_t tmpBallThrowerMotorSpeed = BurnoutControl(CalcControlLoop(_CmdBallThrowerMotorSpeed), Robot.State.BallThrowerMotorSpeed);


                Robot.State.BallThrowerMotorSpeed = tmpBallThrowerMotorSpeed;

                while (millis() < nextTime)
                {
                    delay(1);
                }
            }
        }
                        _SlowDown = 0;
    }

    int16_t calculatedBallThrowerMotorSpeed = _OIBallThrowerMotorSpeed;
    
    if (BurnoutControlEnabled)
    {
        calculatedBallThrowerMotorSpeed = BurnoutControl(calculatedBallThrowerMotorSpeed, Robot.State.BallThrowerMotorSpeed);
        
    }
    Robot.State.BallThrowerMotorSpeed = calculatedBallThrowerMotorSpeed;

    long untilNextRun = nextLoopTime - millis();
    if(untilNextRun > 0)
        delay(untilNextRun);
}

void BALLTHROWER::OISetSpeed(int16_t BallThrowerMotorSpeed)
{
    _OIBallThrowerMotorSpeed = BallThrowerMotorSpeed;
}

bool BALLTHROWER::ForAsync(long durationMS, int16_t BallThrowerMotorSpeed, float SlowDown, uint8_t HoldUntilPercent)
{
     _SlowDown = SlowDown;

    _CmdBallThrowerMotorSpeed = BallThrowerMotorSpeed;
    
    bool retVal = CmdStart("ForAsync", millis(), millis() + durationMS, durationMS + 500);

    while (CmdPercentComplete() < HoldUntilPercent && retVal)
    {
        delay(20);
    }

    return retVal;
}



