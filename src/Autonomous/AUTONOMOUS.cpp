#include "AUTONOMOUS.h"
#include "ROBOT.h"

AUTONOMOUS::AUTONOMOUS(ROBOT &refRobot) : Robot(refRobot)
{
    _MaxProgramNumber = 6;
}

void AUTONOMOUS::Loop()
{
    if (_AutonARMED)
    {
        if (Robot.State.AutonLightSensorActive)
        {
            Robot.State.AutonLightSensorState = 1;
            LaunchQueued();
        }
    }

    if (_RunningAuton == "Auton1") ExecAuton1();
    else if(_RunningAuton == "Auton2") ExecAuton2();
    else if(_RunningAuton == "Auton3") ExecAuton3();
    else if(_RunningAuton == "Auton4") ExecAuton4();
    else if (_RunningAuton == "Auton5") ExecAuton5();
    else if (_RunningAuton == "Auton6") ExecAuton6();

     _RunningAuton = "";
    delay(20);
}

void AUTONOMOUS::ExecAuton1()
{
    //Hits low flag, high flag, flips a cap, and drives on the platform
    //Red Close Tile
   /* Robot.BallIntake.ForAsync(500, 200, 0);//Moves out of the way
    Robot.Lift.ForAsync(500, 255, 0);//Moves out of the way
    Robot.BallThrower.ForAsync(500, 255, 100);//Shoots ball at flag
    Robot.BallThrower.ForAsync(1000, 125, 0);//Moves back to original position
    Robot.Drive.ForAsync(3000, 100, 114, 100);//Drives forward to hit flag
    Robot.Drive.ForAsync(2000, -100, -100, 100);//Drives backward
    Robot.Drive.ForAsync(1500, 100, -130, 100);//Turns
    Robot.Drive.ForAsync(1000, 100, 100, 0);//Drives at cap
    Robot.Lift.ForAsync(300, 255, 100);//Hits cap
    Robot.Drive.ForAsync(1500, 100, -130, 100);//Turns
    Robot.Drive.ForAsync(2000, 255, 255, 100);//Climbs platform*/
}
void AUTONOMOUS::ExecAuton2()
{
    //Hits low flag, high flag, flips a cap, and drives on the platform
    //Blue Close Tile
    /*Robot.BallIntake.ForAsync(500, 200, 0);//Moves out of the way
    Robot.Lift.ForAsync(500, 255, 0);//Moves out of the way
    Robot.BallThrower.ForAsync(500, 255, 100);//Shoots ball at flag
    Robot.BallThrower.ForAsync(1000, 125, 0);//Moves back to original position
    Robot.Drive.ForAsync(3000, 100, 114, 100);//Drives forward to hit flag
    Robot.Drive.ForAsync(2000, -100, -100, 100);//Drives backward
    Robot.Drive.ForAsync(1500, -130, 100, 100);//Turns
    Robot.Drive.ForAsync(1000, 100, 100, 0);//Drives at cap
    Robot.Lift.ForAsync(300, 255, 100);//Hits cap
    if(Robot.Parking)
    {
    Robot.Drive.ForAsync(1500, -130, 100, 100);//Turns
    Robot.Drive.ForAsync(2000, 255, 255, 100);//Climbs platform
    }*/
}
void AUTONOMOUS::ExecAuton3()
{
    //Shoots flag, Flips cap, drives on platform
    //Red far tile
    /*Robot.BallIntake.ForAsync(500, 200, 0);//Moves out of the way
    Robot.Lift.ForAsync(500, 255, 0);//Moves out of the way
    Robot.BallThrower.ForAsync(500, 255, 100);//Shoots ball at flag
    Robot.Drive.ForAsync(2250, 100, -130, 100);//Turns
    Robot.Drive.ForAsync(1000, 100, 114, 100);//Drives forward
    Robot.Lift.ForAsync(500, 255, 100);//Flips cap
    if(Robot.Parking)
    {
    Robot.Drive.ForAsync(2250, -130, 100, 100);//Turns
    Robot.Drive.ForAsync(1000,255,255,100);//Drives on platform
    }*/
}
void AUTONOMOUS::ExecAuton4()
{
    //Shoots flag, Flips cap, drives on platform
    //Blue far tile
    Robot.BallIntake.ForAsync(500, 200, 0, 0);//Moves out of the way
    Robot.Lift.ForAsync(500, 255, 0, 0);//Moves out of the way
    Robot.BallThrower.ForAsync(500, 255, 0, 100);//Shoots ball at flag
    Robot.Drive.ForAsync(2250, -130, 100, 0, 100);//Turns
    Robot.Drive.ForAsync(1000, 100, 114, 0, 100);//Drives forward
    Robot.Lift.ForAsync(500, 255, 0, 100);//Flips cap
    if(Robot.Parking)
    {
    Robot.Drive.ForAsync(2250, 100, 130, 0, 100);//Turns
    Robot.Drive.ForAsync(1000, 255, 255, 0, 100);//Drives on platform
    }
}

void AUTONOMOUS::ExecAuton5()
{
    //Skills Auton
    /*Robot.BallIntake.ForAsync(500, 200, 0);//Moves out of the way
    Robot.Lift.ForAsync(500, 255, 0);//Moves out of the way
    Robot.BallThrower.ForAsync(500, 255, 100);//Shoots ball at flag
    Robot.Drive.ForAsync(3000, 100, 100, 100);//Drives to hit flags
    Robot.Drive.ForAsync(1500, -100, -100, 100);//Drives to line up with cap
    Robot.Drive.ForAsync(1500, -100, 100, 100);//Turns
    Robot.Drive.ForAsync(1000, 100, 100, 50);//Drives to cap
    Robot.Lift.ForAsync(500, 255, 100);//Flips cap
    Robot.Drive.ForAsync(1500, -100 ,-100, 100);//Drives backward
    Robot.Drive.ForAsync(1500, -100, 100, 100);//Turns
    Robot.Drive.ForAsync(5000, 100, 100, 25);//Drives to BuddyBot
    Robot.BuddyBot.ForAsync(3000, 100, 100);//Puts Down BuddyBot lift
    //DELAY????
    Robot.BuddyBot.ForAsync(1000, 100, 100);//Puts it down more
    Robot.BuddyBot.ForAsync(2500, -100, 100);//Brings it up
    Robot.Drive.ForAsync(1000, -100, -100, 100);//Drives backwards
    Robot.Drive.ForAsync(1500, -100, -100, 100);//Turns
    Robot.Drive.ForAsync(1500, 100, 100, 100);//Drives Forwards
    Robot.Drive.ForAsync(2000, 255, 255, 100);//Parks*/
}

void AUTONOMOUS::ExecAuton6()
{

}