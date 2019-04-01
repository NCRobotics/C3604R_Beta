
#include "BUDDYBOT.h"
#include "ROBOT.h"

BUDDYBOT::BUDDYBOT(ROBOT &refRobot) : Robot(refRobot)
{
}

void BUDDYBOT::Loop()
{
    //Only Run Command Code When Valid
    if (!CmdTimedOut() && CmdIsRunning())
    {
        if (CmdName() == "ForAsync")
        {
            Robot.State.BuddyBotLiftSpeed = _CmdBuddyBotLiftSpeed;
            while (CmdUpdatePercent(millis()))
            {
                delay(20);
            }
        }
    }
    Robot.State.BuddyBotLiftSpeed = _OIBuddyBotLiftSpeed;

    delay(20);

    long nextLoopTime = millis()+20;
    //Only Run Command Code When Valid
    if (!CmdTimedOut() && CmdIsRunning())
    {
        if (CmdName() == "ForAsync")
        {
            Robot.State.BuddyBotLiftSpeed = _CmdBuddyBotLiftSpeed;
            long nextTime = millis();

            while (CmdUpdatePercent(millis()))
            {
                delay(20);
                nextTime = millis() + 25;

                int16_t tmpBuddyBotLiftSpeed = BurnoutControl(CalcControlLoop(_CmdBuddyBotLiftSpeed), Robot.State.BuddyBotLiftSpeed);


                Robot.State.BuddyBotLiftSpeed = tmpBuddyBotLiftSpeed;

                while (millis() < nextTime)
                {
                    delay(1);
                }
            }
        }
                        _SlowDown = 0;
    }

    int16_t calculatedBuddyBotLiftSpeed = _OIBuddyBotLiftSpeed;
    
    if (BurnoutControlEnabled)
    {
        calculatedBuddyBotLiftSpeed = BurnoutControl(calculatedBuddyBotLiftSpeed, Robot.State.BuddyBotLiftSpeed);
        
    }
    Robot.State.BuddyBotLiftSpeed = calculatedBuddyBotLiftSpeed;

    long untilNextRun = nextLoopTime - millis();
    if(untilNextRun > 0)
        delay(untilNextRun);
}

void BUDDYBOT::OISetSpeed(int16_t BuddyBotLiftSpeed)
{
    _OIBuddyBotLiftSpeed = BuddyBotLiftSpeed;
}

bool BUDDYBOT::ForAsync(long durationMS, int16_t BuddyBotLiftSpeed, float SlowDown, uint8_t HoldUntilPercent)
{
     _SlowDown = SlowDown;

    _CmdBuddyBotLiftSpeed = BuddyBotLiftSpeed;
    
    bool retVal = CmdStart("ForAsync", millis(), millis() + durationMS, durationMS + 500);

    while (CmdPercentComplete() < HoldUntilPercent && retVal)
    {
        delay(20);
    }

    return retVal;
}



