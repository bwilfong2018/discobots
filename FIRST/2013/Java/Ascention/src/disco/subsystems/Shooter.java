/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.subsystems;

import disco.HW;
import edu.wpi.first.wpilibj.Victor;
import edu.wpi.first.wpilibj.command.PIDSubsystem;
import disco.utils.DiscoCounterEncoder;

//This is what we have now. This will eventually become a PIDSubsystem (maybe)
public class Shooter extends PIDSubsystem {
    // Put methods for controlling this subsystem
    // here. Call these from Commands.
    private Victor shooter1;
    private Victor shooter2;
    private static double kP=0, kI=0, kD=0;
    private DiscoCounterEncoder encoder;

    public Shooter(){
	super("shooter", kP, kI, kD);
	shooter1=new Victor(HW.Shooter1Slot,HW.Shooter1Channel);
	shooter2=new Victor(HW.Shooter2Slot,HW.Shooter2Channel);
        encoder=new DiscoCounterEncoder(HW.DiscoEncoderSlot, HW.DiscoEncoderChannel, 1);
    }

    public void initDefaultCommand() {
        // Set the default command for a subsystem here.
        //setDefaultCommand(new MySpecialCommand());
    }

    public void setPower(double power){
	setPower1(power);
	setPower2(power);
    }

    public void setPower1(double power){
	shooter1.set(power);
    }

    public void setPower2(double power){
	shooter2.set(power);
    }

    public double getPower1(){
	return shooter1.get();
    }

    public double getPower2(){
	return shooter2.get();
    }

    protected double returnPIDInput() {
        return encoder.getRPM();
    }

    protected void usePIDOutput(double output) {
        setPower(output);
    }
}