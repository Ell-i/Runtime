
import ctypes
from subprocess import call

# Testing a direct C call to a C++ member function
#
# class SerialClass {
#    void begin(uint32_t) const;
# };
#
# equals at C level to
#
# __ZNK6SerialClass5beginEj(class SerialClass *this, uint32_t);
#
#
# The test case:
#
# class SerialClass;
#
# extern const class SerialClass Serial;
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

emulator._ZNK6SerialClass5beginEj(Serial, 57600)
