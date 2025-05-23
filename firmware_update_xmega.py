import subprocess
import time
import chipwhisperer as cw
import argparse
import os

# Parse command-line arguments
parser = argparse.ArgumentParser(description="Update firmware with specified HASH_FUNCTION and HASH_VARIANT.")
parser.add_argument("--hash-function", required=True, help="Specify the hash function (e.g., PHOTON).")
parser.add_argument("--hash-variant", required=True, help="Specify the hash variant (e.g., 80).")
args = parser.parse_args()

# Extract arguments
HASH_FUNC = args.hash_function
# Hash_function_name = HASH_FUNC  
HASH_VAR = args.hash_variant

SCOPETYPE = 'OPENADC'
PLATFORM = 'CWLITEXMEGA'
CRYTPO_TARGET = 'NONE'

if subprocess.run(["arm-none-eabi-gcc", "--version"]).returncode == 0:
    print("--------------------\nARM GCC is installed\n--------------------\n")
else:
    print("--------------------\nARM GCC is not installed\n--------------------\n")

if subprocess.run(["avr-gcc", "--version"]).returncode == 0:
    print("--------------------\nAVR GCC is installed\n--------------------\n")
else:
    print("--------------------\nAVR GCC is not installed\n--------------------\n")


#Removing the previous build

# Set up path to the firmware
firmware_path = "/Users/khannmohsin/Chipwhispere_vscode/chipwhisperer/firmware/mcu/LWHF-SS-template"
objdir_path = f"{firmware_path}/objdir-{PLATFORM}"
hash_function_path = f"{objdir_path}/LWHF/{HASH_FUNC}"


# Check and remove files in the firmware directory
firmware_files = [f for f in os.listdir(firmware_path) if f.startswith(f"simpleserial-base-{PLATFORM}.")]
if firmware_files:
    print(f"Removing files: {firmware_files}")
    subprocess.run(
        f"rm -rf simpleserial-base-{PLATFORM}.*",
        shell=True,
        cwd=firmware_path
    )
else:
    print(f"No files matching 'simpleserial-base-{PLATFORM}.*' found in {firmware_path}.")

# Check and remove .lst and .o files in the objdir directory
lst_files = [f for f in os.listdir(objdir_path) if f.endswith('.lst')]
o_files = [f for f in os.listdir(objdir_path) if f.endswith('.o')]

if lst_files or o_files:
    print(f"Removing .lst files: {lst_files}")
    print(f"Removing .o files: {o_files}")
    subprocess.run(
        f"rm -rf {objdir_path}/*.lst {objdir_path}/*.o",
        shell=True
    )
else:
    print(f"No .lst or .o files found in {objdir_path}.")

# Check and remove .o files in the hash function directory
hash_function_files = [f for f in os.listdir(hash_function_path) if f.endswith('.o')]
if hash_function_files:
    print(f"Removing .o files: {hash_function_files}")
    subprocess.run(
        f"rm -rf {hash_function_path}/*.o",
        shell=True
    )
else:
    print(f"No .o files found in {hash_function_path}.")



# print("\n----------------------Performing Firmware Update of XMEGA----------------------\n")    
# time.sleep(2)

# Compile the firmware
subprocess.run(["make", f"PLATFORM={PLATFORM}", f"CRYPTO_TARGET={CRYTPO_TARGET}", f"HASH_FUNCTION={HASH_FUNC}", f"HASH_VARIANT={HASH_VAR}"],  cwd=firmware_path)


scope = cw.scope()

target = cw.target(scope, cw.targets.SimpleSerial)

if SCOPETYPE == "OPENADC":
    scope.gain.db = 45
    scope.adc.samples = 3000
    scope.adc.offset = 1250
    scope.adc.basic_mode = "rising_edge"
    scope.clock.clkgen_freq = 7370000
    scope.clock.adc_src = "clkgen_x4"
    # scope.clock.adc_freq = 29500000 #Need to be changed
    scope.trigger.triggers = "tio4"
    scope.io.tio1 = "serial_rx"
    scope.io.tio2 = "serial_tx"
    scope.io.hs2 = "clkgen"
elif SCOPETYPE == "CWNANO":
    scope.io.clkout = 7370000
    scope.adc.clk_freq = 7370000
    scope.io.tio1 = "serial_rx"
    scope.io.tio2 = "serial_tx"
else:
    scope.default_setup()


# 
if "STM" in PLATFORM or PLATFORM == "CWLITEARM" or PLATFORM == "CWNANO":
    prog = cw.programmers.STM32FProgrammer
elif PLATFORM == "CW303" or PLATFORM == "CWLITEXMEGA":
    prog = cw.programmers.XMEGAProgrammer
else:
    prog = None
    
# fw_path = '../hardware/victims/firmware/simpleserial-base-lab1/simpleserial-base-{}.hex'.format(PLATFORM)
fw_path = '/Users/khannmohsin/Chipwhispere_vscode/chipwhisperer/firmware/mcu/LWHF-SS-template/simpleserial-base-{}.hex'.format(PLATFORM)
cw.program_target(scope, prog, fw_path)

# # Turn LED on
# print("Turning LED on...")
# target.write("l01\n")
# response = target.read()
# print(f"Response: {response}")
# time.sleep(10)
# # Turn LED off
# print("Turning LED off...")
# target.write("l00\n")
# response = target.read()
# print(f"Response: {response}")

scope.dis()
target.dis()