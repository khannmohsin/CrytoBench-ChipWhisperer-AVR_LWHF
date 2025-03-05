import chipwhisperer as cw

scope = cw.scope()
prog = cw.programmers.XMEGAProgrammer
cw.program_target(scope, prog, "main_target.hex")

# Initialize scope


# # Initialize programmer
# programmer = cw.programmers.XMEGAProgrammer()


# # Set the scope for the programmer
# programmer.scope = scope

# # Flash the firmware
# firmware_path = "main_target.hex"
# programmer.program(firmware_path, memtype="flash")
# print("Programming complete!")

# # Disconnect scope
# scope.dis()