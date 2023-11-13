clc;
clear;
ard = arduino("/dev/cu.usbmodem1101","Uno");
while true
    value = readVoltage(ard,"A0");
    writePWMVoltage(ard,"D11",value);
end
clear;