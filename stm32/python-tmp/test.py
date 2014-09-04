
import ctypes
from subprocess import call

# Testing a direct C call to a C++ member function
#
# class Serial {
#    void begin(uint32_t) const;
# };
#
# equals at C level to
#
# __ZNK6Serial5beginEj(class Serial *this, uint32_t);
#
#
# The test case:
#
# class Serial;
#
# extern const class Serial Serial;
#
# #include <Arduino.h>
#
# void dummy() {
#     Serial.begin(57600);
# }
# void setup() {
# }
# void loop() {}
#

emulator = ctypes.CDLL("./libsketch.so")

class SerialClass(ctypes.Structure):
    pass

Serial = ctypes.POINTER(SerialClass).in_dll(emulator, "Serial");

print Serial;

emulator._ZNK6Serial5beginEj(Serial, 57600)
