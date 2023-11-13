clc;
clear;
ard = arduino("/dev/cu.usbmodem1101","Uno");
cmd = " ";
while cmd ~= "q"
    cmd = input("Comando [ON/OFF/q]: ","s");
    if cmd == "on" || cmd == "ON"
        writeDigitalPin(ard, "D13", 1);
    elseif cmd == "off" || cmd == "OFF"
        writeDigitalPin(ard, "D13", 0);
    end
end
clear;