
#include "BALLINTAKE.h"
#include "ROBOT.h"

BALLINTAKE::BALLINTAKE(ROBOT &refRobot) : Robot(refRobot)
{
}

void BALLINTAKE::Loop()
{
    //Only Run Command Code When Valid
    if (!CmdTimedOut() && CmdIsRunning())
    {
        if (CmdName() == "ForAsync")
        {
            Robot.State.BallIntakeMotorSpeed = _CmdBallIntakeMotorSpeed;
            while (CmdUpdatePercent(millis()))
            {
                delay(20);
            }
        }
    }
    Robot.State.BallIntakeMotorSpeed = _OIBallIntakeMotorSpeed;

    delay(20);

    long nextLoopTime = millis()+20;
    //Only Run Command Code When Valid
    if (!CmdTimedOut() && CmdIsRunning())
    {
        if (CmdName() == "ForAsync")
        {
            Robot.State.BallIntakeMotorSpeed = _CmdBallIntakeMotorSpeed;
            long nextTime = millis();

            while (CmdUpdatePercent(millis()))
            {
                delay(20);
                nextTime = millis() + 25;

                int16_t tmpBallIntakeMotorSpeed = BurnoutControl(CalcControlLoop(_CmdBallIntakeMotorSpeed), Robot.State.BallIntakeMotorSpeed);


                Robot.State.BallIntakeMotorSpeed = tmpBallIntakeMotorSpeed;

                while (millis() < nextTime)
                {
                    delay(1);
                }
            }
        }
                        _SlowDown = 0;
    }

    int16_t calculatedBallIntakeMotorSpeed = _OIBallIntakeMotorSpeed;
    
    if (BurnoutControlEnabled)
    {
        calculatedBallIntakeMotorSpeed = BurnoutControl(calculatedBallIntakeMotorSpeed, Robot.State.BallIntakeMotorSpeed);
        
    }
    Robot.State.BallIntakeMotorSpeed = calculatedBallIntakeMotorSpeed;

    long untilNextRun = nextLoopTime - millis();
    if(untilNextRun > 0)
        delay(untilNextRun);
}

void BALLINTAKE::OISetSpeed(int16_t BallIntakeMotorSpeed)
{
    _OIBallIntakeMotorSpeed = BallIntakeMotorSpeed;
}

bool BALLINTAKE::ForAsync(long durationMS, int16_t BallIntakeMotorSpeed, float SlowDown, uint8_t HoldUntilPercent)
{
     _SlowDown = SlowDown;

    _CmdBallIntakeMotorSpeed = BallIntakeMotorSpeed;
    
    bool retVal = CmdStart("ForAsync", millis(), millis() + durationMS, durationMS + 500);

    while (CmdPercentComplete() < HoldUntilPercent && retVal)
    {
        delay(20);
    }

    return retVal;
}



