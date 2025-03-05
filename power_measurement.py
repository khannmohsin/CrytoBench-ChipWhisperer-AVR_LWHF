import chipwhisperer as cw

# Initialize the scope and target
scope = cw.scope()
target = cw.target(scope, cw.targets.SimpleSerial)

# Set up the scope for power measurement
scope.gain.db = 45  # Adjust gain for the shunt measurement
scope.adc.samples = 5000  # Number of samples to capture
scope.adc.offset = 0  # Offset for ADC capture
scope.clock.clkgen_freq = 7370000  # Set clock frequency (e.g., 7.37 MHz)
scope.trigger.triggers = "tio4"  # Use TIO4 for trigger signal

# Arm the scope for capturing power traces
scope.arm()

# Run a function on the target
target.write("run\n")  # Trigger the target via SimpleSerial

# Wait for the capture to complete
if scope.capture():
    print("Capture failed!")
else:
    trace = scope.get_last_trace()
    print("Power trace captured successfully!")

# Analyze the power consumption
import matplotlib.pyplot as plt
plt.plot(trace)
plt.title("Power Consumption Trace")
plt.xlabel("Samples")
plt.ylabel("Power (relative units)")
plt.show()

# Disconnect
scope.dis()
target.dis()