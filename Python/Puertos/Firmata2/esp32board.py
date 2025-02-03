esp32 = {
    "digital": tuple(x for x in range(40)),
    "analog": tuple(x for x in range(40)),
    "pwm": (2, 4, 5, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33),
    "use_ports": True,
    "disabled": (1, 3, 6, 7, 8, 9, 10, 11),
}

def esp32_analog_message(self, pin_nr, lsb, msb):
    value = round(float((msb << 7) + lsb) / 4095, 4)
    # Only set the value if we are actually reporting
    try:
        if self.analog[pin_nr].reporting:
            self.analog[pin_nr].value = value
            if not self.analog[pin_nr].callback is None:
                self.analog[pin_nr].callback(value)
    except IndexError:
        raise ValueError