package discobot;

import Utils.*;
import edu.wpi.first.wpilibj.*;

/**
 *
 * @author Nelson Chen
 */
public class Teleop {

    static boolean sonarControlEnabled = false;
    static boolean fieldCentricEnabled = true;
    static final double k_armDownSpeed = 0.7;
    static final double k_armUpSpeed = -0.7;
    static final double k_collectorOutSpeed = 0.5;
    static final double k_collectorInSpeed = -0.5;
    static double currentX = 0.0;
    static double currentY = 0.0;
    static double currentTime;
    static boolean[] leftButtons = new boolean[12];
    static boolean[] rightButtons = new boolean[12];
    static boolean[] liftButtons = new boolean[12];
    //static double[] lastPressed = new double[12];
    static int i = 0;
    static double rotation;
    static final double k_driveRotationThreshold = 0.5;
    static final double k_gyroRotationThreshold = 1.0;
    static double oldAngle = 0.0;
    static double delayLift7;
    static double delayLift6;

    //static double[] encoder = new double[4];
    public static void periodic() {
        /*encoder[0] = HW.encoderFrontLeft.getDistance();
        encoder[1] = HW.encoderFrontRight.getDistance();
        encoder[2] = HW.encoderRearRight.getDistance();
        encoder[3] = HW.encoderRearLeft.getDistance();
        DataLogger.dataLogger.setEntryValue(encoder);*/
        updateButtons();

        //Turn Controller Reset and Orientation
        if (leftButtons[11]) {
            HW.turnController.reset(0);
        } else if (leftButtons[10]) {
            HW.turnController.reset(90);
        } else if (leftButtons[7]) {
            HW.turnController.reset(180);
        } else if (leftButtons[6]) {
            HW.turnController.reset(270);
        } else if (rightButtons[3]) {
            HW.turnController.turnToOrientation(0);
        } else if (rightButtons[5]) {
            HW.turnController.turnToOrientation(90);
        } else if (rightButtons[2]) {
            HW.turnController.turnToOrientation(180);
        } else if (rightButtons[4]) {
            HW.turnController.turnToOrientation(270);
        } else {
            HW.turnController.incrementSetpoint(HW.driveStickRight.getX());
        }

        //Drive Code


        //FC halo control
        rotation = HW.turnController.getRotation();
        double out[] = rotateVector(HW.driveStickLeft.getX(), HW.driveStickLeft.getY(), -1 * HW.gyro.getAngle());
        if (leftButtons[5]) {
           HW.sonarControllerFrontLeft.enable();
           currentY = HW.sonarControllerFrontLeft.getSpeed();
           if (HW.sonarFrontLeft.getRangeInches() < 70) {
               HW.sonarControllerLeft.enable();
               currentX = HW.sonarControllerLeft.getSpeed();
           } else {
               currentX = 0;
           }
           HW.drive.HolonomicDrive(currentX, currentY, rotation);
           DiscoUtils.debugPrintln("Sonar Mode");
           
        } else {
            HW.drive.HolonomicDrive(out[0], out[1], rotation);
        }


        if (liftButtons[6]) { //arm up
            HW.armMotor.set(k_armUpSpeed);
        } else if (liftButtons[7]) { // arm down
            HW.armMotor.set(k_armDownSpeed);
        } else {
            HW.armMotor.set(0.0);
        }

        HW.lift.set(-HW.liftHandle.getY() * 0.75);

        if (liftButtons[3]) { //out
            HW.collectorMotor.set(k_collectorOutSpeed);
        } else if (liftButtons[2]) { //in
            HW.collectorMotor.set(k_collectorInSpeed);
        } else {
            HW.collectorMotor.set(0.0);
        }

        //HW.collector.periodic(liftHandleButtons);
        //HW.arm.periodic(liftHandleButtons);
        if (i > 30) {
            //DiscoUtils.debugPrintln("Gyro: " + HW.gyro.getAngle());
            //DiscoUtils.debugPrintln("L  sonar: " + HW.sonarLeft.getRangeCM());
            //DiscoUtils.debugPrintln("FL sonar: " + HW.sonarFrontLeft.getRangeInches());
            //DiscoUtils.debugPrintln("FR sonar: " + HW.sonarFrontRight.getRangeInches());
            DiscoUtils.debugPrintln("Sonar L: " + HW.sonarLeft.getRangeInches());
            DiscoUtils.debugPrintln("Sonar FL: " + HW.sonarFrontLeft.getRangeInches());
            DiscoUtils.debugPrintln("Sonar FR: " + HW.sonarFrontRight.getVoltage());
            DiscoUtils.debugPrintln("Sonar R: " + HW.sonarRight.getRangeInches());

            i = 0;
        } else {
            i++;
        }
        //verifyGyro(HW.gyro.getAngle());
        /*if (leftButtons[9]) {
        fieldCentricEnabled = true;
        DiscoUtils.debugPrintln("Field Centric Enabled");
        HW.lcd.println(DriverStationLCD.Line.kMain6, 0, "Field-Centric Enabled");
        HW.lcd.updateLCD();
        } else if (leftButtons[8]) {
        fieldCentricEnabled = false;
        DiscoUtils.debugPrintln("Field Centric Disabled");
        HW.lcd.println(DriverStationLCD.Line.kMain6, 0, "Field-Centric Disabled");
        HW.lcd.updateLCD();
        }*/
    }

    public static void continuous() {
    }

    /**
     * Rotate a vector in Cartesian space.
     */
    protected static double[] rotateVector(double x, double y, double angle) {
        double cosA = Math.cos(angle * (3.14159 / 180.0));
        double sinA = Math.sin(angle * (3.14159 / 180.0));
        double out[] = new double[2];
        out[0] = x * cosA - y * sinA;
        out[1] = x * sinA + y * cosA;
        return out;
    }

    private static void updateButtons() {
        for (int b = 1; b
                < 12; b++) {
            leftButtons[b] = HW.driveStickLeft.getRawButton(b);
            rightButtons[b] = HW.driveStickRight.getRawButton(b);
            liftButtons[b] = HW.liftHandle.getRawButton(b);
        }
        currentTime = Timer.getFPGATimestamp();
    }

    public static void verifyGyro(double currentAngle) {
        double angleChange = currentAngle - oldAngle;
        if (Math.abs(rotation) > k_driveRotationThreshold
                && Math.abs(angleChange) < k_gyroRotationThreshold) {
            fieldCentricEnabled = false;
        } else {
            fieldCentricEnabled = true;
        }
        oldAngle = currentAngle;
    }
}
