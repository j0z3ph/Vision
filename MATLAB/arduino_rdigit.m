clc;
clear;
ard = arduino("/dev/cu.usbmodem1101","Uno");
cmd = " ";
while cmd ~= "q"
    button = readDigitalPin(ard, "D10");
    if button == 1
        writeDigitalPin(ard, "D13", 1);
    else
        writeDigitalPin(ard, "D13", 0);
    end
end
clear;