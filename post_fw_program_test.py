import chipwhisperer as cw
import time

# Initialize ChipWhisperer scope and target
scope = cw.scope()
target = cw.target(scope, cw.targets.SimpleSerial)
target.baud = 230400

# Scope configuration
scope.gain.db = 45
scope.adc.samples = 1000
scope.adc.offset = 1250
scope.adc.basic_mode = "rising_edge"
scope.clock.clkgen_src = 'system' 
scope.clock.clkgen_freq = 7372800    #12000000  # 12 MHz clock
scope.clock.adc_src = "clkgen_x4"
scope.trigger.triggers = "tio4"
scope.io.tio1 = "serial_rx"
scope.io.tio2 = "serial_tx"
scope.io.hs2 = "clkgen"


msg = bytearray([0]*16) #simpleserial uses bytearrays
target.simpleserial_write('p', msg)

# Send the 't' command to trigger text transmission
print(target.simpleserial_read('r', 16, timeout=1000))  # Increase timeout to 1000 ms

