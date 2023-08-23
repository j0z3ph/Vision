clc;
clear;
ard = arduino("/dev/cu.usbmodem101","Uno");
for k = 1:30
    writeDigitalPin(ard, "D13", 0);
    pause(1);
    writeDigitalPin(ard, "D13", 1);
    pause(1);
end
clear;