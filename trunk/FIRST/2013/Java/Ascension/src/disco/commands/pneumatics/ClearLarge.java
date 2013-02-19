/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.commands.pneumatics;

import disco.commands.CommandBase;
import edu.wpi.first.wpilibj.command.CommandGroup;
import edu.wpi.first.wpilibj.command.WaitCommand;

public class ClearLarge extends CommandGroup {
    
    public ClearLarge() {
        addSequential(new LargeClearIn());
        addSequential(new WaitCommand(0.2));
        addSequential(new LargeClearOut());
        // Use requires() here to declare subsystem dependencies
        // eg. requires(chassis);
        addSequential(new LargeClearIn());
        addSequential(new WaitCommand(0.2));
        addSequential(new LargeClearOut());
    }

    // Called just before this Command runs the first time
    protected void initialize() {
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return false;
    }

    // Called once after isFinished returns true
    protected void end() {
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
    }
}
