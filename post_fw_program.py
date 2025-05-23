import chipwhisperer as cw
import time
import numpy as np
import argparse
import os
import re
import csv

def send_hash_function_name(target, Hash_function_name, Hash_function_variant):
    # Encode the text into a bytearray
    msg = bytearray(Hash_function_name.encode('ascii'))  # Convert the text to ASCII-encoded bytearray

    # If the target expects a fixed size (e.g., 16 bytes), pad or truncate the message
    desired_length = 16
    if len(msg) < desired_length:
        # Pad with zeros if the message is shorter than the required length
        msg.extend([0] * (desired_length - len(msg)))
    elif len(msg) > desired_length:
        # Truncate if the message is longer than the required length
        msg = msg[:desired_length]
    
    # List of LWHF names
    LWHF_names = ["PHOTON", "QUARK", "SPONGENT", "LESAMNTA", "ASCON", "PHOTON_BEETLE", "XOODYAK", "KNOT", "ORANGE", "SHAMAS", 
                  "SIVRIJNDAEL", "SIVTEMPHOTON", "SKINNY", "SNEIK", "TRIAD", "CORAL", "GIMLI", "DRYGASCON", "CLX", "ACE", 
                  "SPARKLE", "SUBTERRAINEAN", "SATURNIN", "ISAP", "GAGE", "BLAKE3", "BLAKE2"]

    # Check which LWHF it is
    if Hash_function_name in LWHF_names:

        if Hash_function_name == "SPONGENT":
            if Hash_function_variant == "088080008" or Hash_function_variant == "088176088":
                hash_variant_byte_size = 11
            elif Hash_function_variant == "128128008" or Hash_function_variant == "128256128":
                hash_variant_byte_size = 16
            elif Hash_function_variant == "160160016" or Hash_function_variant == "160160080" or Hash_function_variant == "160320160":
                hash_variant_byte_size = 20
            elif Hash_function_variant == "224224016" or Hash_function_variant == "224224112" or Hash_function_variant == "224448224":
                hash_variant_byte_size = 28
            elif Hash_function_variant == "256256016" or Hash_function_variant == "256256128" or Hash_function_variant == "256512256":
                hash_variant_byte_size = 32
        else:

            hash_variant_byte_size = int(int(Hash_function_variant)/8)

        # Send the encoded message to the target
        target.simpleserial_write('p', msg)
        time.sleep(10)
        print("Obtaining response from target...")
        response = target.simpleserial_read('r', hash_variant_byte_size, timeout=1000)  # Increase timeout to 1000 ms
        digest = int.from_bytes(response, byteorder='little')  # Interpret as little-endian
        print(f"Digest : {digest}")
        print(f"length of the digest: {len(response)}")

    else:
        print(f"Hash function {Hash_function_name} is not recognized as an LWHF.")


def receive_clock_cycles(target, Hash_function_name):

    msg = bytearray(Hash_function_name.encode('ascii'))  # Convert the text to ASCII-encoded bytearray
    # If the target expects a fixed size (e.g., 16 bytes), pad or truncate the message
    desired_length = 16
    if len(msg) < desired_length:
        # Pad with zeros if the message is shorter than the required length
        msg.extend([0] * (desired_length - len(msg)))
    elif len(msg) > desired_length:
        # Truncate if the message is longer than the required length
        msg = msg[:desired_length]

    # Send the encoded message to the target
    target.simpleserial_write('m', msg)

    time.sleep(5)
    print("Obtaining response from target...........")

    response = target.simpleserial_read('r', 16, timeout=1000)
    digest_size = int.from_bytes(response, byteorder='little')
    print(digest_size)
    print(response)


def get_power_measurement_and_cycles(target, Hash_function_name, Hash_function_variant):
    msg = bytearray(Hash_function_name.encode('ascii'))  # Convert the text to ASCII-encoded bytearray

    # If the target expects a fixed size (e.g., 16 bytes), pad or truncate the message
    desired_length = 16
    if len(msg) < desired_length:
        # Pad with zeros if the message is shorter than the required length
        msg.extend([0] * (desired_length - len(msg)))
    elif len(msg) > desired_length:
        # Truncate if the message is longer than the required length
        msg = msg[:desired_length]

    # List of LWHF names
    LWHF_names = ["PHOTON", "QUARK", "SPONGENT", "LESAMNTA", "ASCON", "PHOTON_BEETLE", "XOODYAK", "KNOT", "ORANGE", "SHAMAS", 
                  "SIVRIJNDAEL", "SIVTEMPHOTON", "SKINNY", "SNEIK", "TRIAD", "CORAL", "GIMLI", "DRYGASCON", "CLX", "ACE", 
                  "SPARKLE", "SUBTERRAINEAN", "SATURNIN", "ISAP", "GAGE", "BLAKE3", "BLAKE2"]

    # Check which LWHF it is
    if Hash_function_name in LWHF_names:

        # if Hash_function_name == "SPONGENT":
        #     if Hash_function_variant == "088080008" or Hash_function_variant == "088176088":
        #         hash_variant_byte_size = 11
        #     elif Hash_function_variant == "128128008" or Hash_function_variant == "128256128":
        #         hash_variant_byte_size = 16
        #     elif Hash_function_variant == "160160016" or Hash_function_variant == "160160080" or Hash_function_variant == "160320160":
        #         hash_variant_byte_size = 20
        #     elif Hash_function_variant == "224224016" or Hash_function_variant == "224224112" or Hash_function_variant == "224448224":
        #         hash_variant_byte_size = 28
        #     elif Hash_function_variant == "256256016" or Hash_function_variant == "256256128" or Hash_function_variant == "256512256":
        #         hash_variant_byte_size = 32
        # else:

        #     hash_variant_byte_size = int(int(Hash_function_variant)/8)

        response_received = False
        while not response_received:
            # Attempt to capture a trace
            # Generate a dummy 80-bit key (10 bytes)

            dummy_key = bytearray([0x00] * 10)  # 80-bit key with all zeros
            trace = cw.capture_trace(scope, target, msg, dummy_key)

            if trace is not None and trace.textout is not None:  # Check if the capture was successful
                # Define constants
                ADC_REF_VOLTAGE = 1 # ADC reference voltage
                AMPLIFIER_GAIN = scope.gain.db  # Amplifier gain in dB (verify scope.gain.actual if available)
                SHUNT_RESISTOR = 49.9  # Shunt resistor value in ohms (50 Ω)
                SUPPLY_VOLTAGE = 3.3  # Supply voltage to the target
                
                # Retrieve the power trace
                raw_adc_values = trace.wave  # Power trace from the capture
                # print(f"Raw ADC values: {raw_adc_values}")
                plaintext_used = trace.textin  # The plaintext sent to the target
                response = trace.textout  # The response (e.g., ciphertext)
                cycles_per_byte = int.from_bytes(response, byteorder='little')

                # Convert raw ADC values to actual voltages
                actual_voltage_trace = raw_adc_values * ADC_REF_VOLTAGE / AMPLIFIER_GAIN
                # print(f"Actual Voltage Trace: {actual_voltage_trace}")

                # Convert to current using the shunt resistor
                current_trace = actual_voltage_trace / SHUNT_RESISTOR
                # print(f"Current Trace: {current_trace}")

                # Calculate instantaneous power (optional for energy calculation)
                power_trace = current_trace * SUPPLY_VOLTAGE
                # print(f"Power Trace: {power_trace}")

                rms_power = np.sqrt(np.mean(power_trace**2))
                # rms_power_mW = rms_power * 1000
                # sampling_period = 1 / scope.clock.adc_freq  # Time between samples
                # duration = len(power_trace) * sampling_period  # Total duration

                execution_time = (cycles_per_byte * 16) / scope.clock.clkgen_freq
                energy = rms_power * execution_time
                rms_power_mW = rms_power * 1000
                energy_nJ = energy * 1000000000

                # Debug printing of values from this function
                print(f"RMS power: {rms_power_mW} mW")
                print(f"Energy from RMS: {energy_nJ} nJ")
                print(f"Cycles per Byte: {cycles_per_byte}")
                print(f"Plaintext Used: {plaintext_used}")


                # Mark the response as received
                response_received = True

                return rms_power_mW, energy_nJ, cycles_per_byte
            else:
                print("Capture failed or no valid response, retrying...")

                time.sleep(5)

    else:
        print(f"Hash function {Hash_function_name} is not recognized as an LWHF.")


def get_ROM(Hash_function_name, Hash_function_variant):
    PLATFORM = 'CWLITEXMEGA'
    map_file_location = '/Users/khannmohsin/Chipwhispere_vscode/chipwhisperer/firmware/mcu/LWHF-SS-template/simpleserial-base-{}.map'.format(PLATFORM)

    with open(map_file_location, "r") as file:
        map_context = file.read()

    # Directory where the .o files are located
    LWHF_directory = f'/Users/khannmohsin/Chipwhispere_vscode/chipwhisperer/firmware/mcu/LWHF-SS-template/objdir-CWLITEXMEGA/LWHF/{Hash_function_name}/'

    # List all files in the directory
    files = os.listdir(LWHF_directory)

    # Filter out the .o files
    o_files = [file for file in files if file.endswith('.o')]

    total_text_size = 0
    total_rodata_size = 0
    total_vectors_size = 0
    total_rom = 0
    o_files_list = []
    for o_file in o_files:
        # Initialize sizes for sections
        text_size = 0
        rodata_size = 0
        vectors_size = 0
        
        # Find all occurrences of the .o file in the map file
        matches = re.finditer(rf'\.(text|rodata|vectors)\s+0x[\da-fA-F]+\s+0x([\da-fA-F]+)\s+.*{re.escape(o_file)}', map_context)
        
        for match in matches:
            section = match.group(1)  # Section name (.text, .rodata, or .vectors)
            size_hex = match.group(2)  # Size in hexadecimal
            
            # Convert size to integer
            size = int(size_hex, 16)
            
            # Add the size to the respective section
            if section == "text":
                text_size += size
            elif section == "rodata":
                rodata_size += size
            elif section == "vectors":
                vectors_size += size

        # Compute total ROM usage for the current .o file
        rom_usage = text_size + rodata_size + vectors_size
        total_text_size += text_size
        total_rodata_size += rodata_size
        total_vectors_size += vectors_size
        total_rom += rom_usage
        o_files_list.append(o_file)
        
        # Print individual section sizes for this .o file
        print(f"ROM usage for {o_file}:")
        print(f"  .text: {text_size} bytes")
        print(f"  .rodata: {rodata_size} bytes")
        print(f"  .vectors: {vectors_size} bytes")
        print(f"  Total: {rom_usage} bytes\n")
    
    print(f"Total ROM usage for {Hash_function_name} ({Hash_function_variant}): {total_rom} bytes")
    return o_files_list, total_text_size, total_rodata_size, total_vectors_size, total_rom



def get_RAM(Hash_function_name, Hash_function_variant):
    PLATFORM = 'CWLITEXMEGA'
    map_file_location = f'/Users/khannmohsin/Chipwhispere_vscode/chipwhisperer/firmware/mcu/LWHF-SS-template/simpleserial-base-{PLATFORM}.map'

    with open(map_file_location, "r") as file:
        map_context = file.read()

    # Directory where the .o and .su files are located
    LWHF_directory = f'/Users/khannmohsin/Chipwhispere_vscode/chipwhisperer/firmware/mcu/LWHF-SS-template/objdir-CWLITEXMEGA/LWHF/{Hash_function_name}/'

    # List all files in the directory
    files = os.listdir(LWHF_directory)

    # Filter out the .o and .su files
    o_files = [file for file in files if file.endswith('.o')]
    su_files = [file for file in files if file.endswith('.su')]

    total_variables_ram = 0
    total_data_size = 0
    total_bss_size = 0
    o_files_list = []

    for o_file in o_files:
        # Initialize sizes for sections
        data_size = 0
        bss_size = 0

        # Find all occurrences of the .o file in the map file
        matches = re.finditer(rf'\.(data|bss)\s+0x[\da-fA-F]+\s+0x([\da-fA-F]+)\s+.*{re.escape(o_file)}', map_context)
        
        for match in matches:
            section = match.group(1)  # Section name (.data or .bss)
            size_hex = match.group(2)  # Size in hexadecimal
            
            # Convert size to integer
            size = int(size_hex, 16)
            
            # Add the size to the respective section
            if section == "data":
                data_size += size
            elif section == "bss":
                bss_size += size

        # Compute total RAM usage for the current .o file
        ram_usage = data_size + bss_size
        total_variables_ram += ram_usage
        total_data_size += data_size
        total_bss_size += bss_size
        o_files_list.append(o_file)

        # Print individual section sizes for this .o file
        print(f"RAM usage for {o_file}:")
        print(f"  .data: {data_size} bytes")
        print(f"  .bss: {bss_size} bytes")
        print(f"  Total: {ram_usage} bytes\n")

    total_static_stack = 0
    total_dynamic_stack = 0
    total_stack = 0 
    su_files_list = []
    # Parse .su files for stack usage
    for su_file in su_files:
        su_file_path = os.path.join(LWHF_directory, su_file)

        with open(su_file_path, "r") as file:
            su_content = file.readlines()

        static_stack = 0
        dynamic_stack = 0

        for line in su_content:
            parts = line.strip().split("\t")
            # print(f"Parsing line: {line.strip()}")  # Debug line
            if len(parts) == 3:  # Ensure proper formatting
                try:
                    usage = int(parts[1])  # Stack usage value

                    stack_type = parts[2].lower()  # Type of stack usage

                    if stack_type == "static":
                        static_stack += usage
                    elif "dynamic" in stack_type:  # Includes "dynamic,bounded"
                        dynamic_stack += usage
                except ValueError:
                    print(f"Could not parse stack usage value: {parts[2]}")  # Debug for value errors
        stack = static_stack + dynamic_stack
        total_stack += stack
        total_static_stack += static_stack
        total_dynamic_stack += dynamic_stack
        su_files_list.append(su_file)

        print(f"Stack usage for {su_file}:")
        print(f"  Max Static: {static_stack} bytes")
        print(f"  Max Dynamic: {dynamic_stack} bytes")
        print(f"  Total Stack: {stack} bytes\n")

    print(f"Total variables RAM usage for {Hash_function_name} ({Hash_function_variant}): {total_variables_ram} bytes")
    print(f"Total Stack usage for {Hash_function_name} ({Hash_function_variant}):")
    print(f"  Max Static: {total_static_stack} bytes")
    print(f"  Max Dynamic: {total_dynamic_stack} bytes")
    print(f"  Total Stack: {total_static_stack + total_dynamic_stack} bytes\n")
    print(f"Overall RAM consumption .data + .bss + stack for is {total_static_stack + total_dynamic_stack + total_variables_ram} bytes")

    return o_files_list, total_data_size, total_bss_size, total_variables_ram, total_static_stack, total_dynamic_stack, total_stack
    
    

def get_message (target):
    # Send the 't' command to trigger text transmission
    print("Requesting text from target...")
    target.write("m\n")

    # Read the response from the target
    time.sleep(2)  # Small delay to ensure data is received
    response = target.read(timeout=60)
    response_ini_removed = response [1:]
    print(f"Raw Response: {response_ini_removed}")

    try :
        mod_response = response_ini_removed.split('z00')[0]  # Keep only the part before "z00"
    except :
        mod_response = response_ini_removed

    print(f"Raw Response: {bytes.fromhex(mod_response).decode('utf-8')}")  # Convert from hexadecimal to ASCII and print
    return mod_response


def update_csv(hash_function_name, hash_variant, csv_file_name, values_dict):
    """
    Updates or creates a CSV file with the specified values in the given columns.
    If the combination of 'Hash Function' and 'Variant' already exists, append the new values to the existing cells,
    ensuring that 'o_file_list' entries are not duplicated.

    Parameters:
    hash_function_name (str): Name of the hash function.
    hash_variant (str): Variant of the hash function (e.g., SHA256, MD5).
    csv_file_name (str): Name of the CSV file to create or update.
    values_dict (dict): Dictionary containing column names as keys and corresponding values to enter.
    """
    # Ensure 'Hash Function' and 'Variant' are always included in the row
    values_dict = {"Hash Function": hash_function_name, "Variant": hash_variant, **values_dict}

    # Check if the file exists
    file_exists = os.path.isfile(csv_file_name)

    # Read existing data if the file exists
    rows = []
    fieldnames = ["Hash Function", "Variant"] + list(values_dict.keys())[2:]  # Ensure proper column order
    if file_exists:
        with open(csv_file_name, mode='r', newline='') as csvfile:
            reader = csv.DictReader(csvfile)
            rows = list(reader)
            fieldnames = reader.fieldnames if reader.fieldnames else fieldnames

    # Check if the row with the same 'Hash Function' and 'Variant' exists
    updated = False
    for row in rows:
        if row['Hash Function'] == hash_function_name and row['Variant'] == hash_variant:
            # Append new values to existing cells for columns other than 'Hash Function' and 'Variant'
            for key, value in values_dict.items():
                if key not in ['Hash Function', 'Variant']:
                    if key == "o_file_list":
                        # Convert existing string to a list, remove duplicates, and join back to a string
                        existing_files = row[key].split(", ") if row[key] else []
                        new_files = value if isinstance(value, list) else [value]
                        combined_files = list(set(existing_files + new_files))  # Ensure uniqueness
                        row[key] = ", ".join(combined_files)
                    else:
                        if key not in row or not row[key]:
                            row[key] = str(value)
                        else:
                            row[key] += f", {value}"
            updated = True
            break

    # If not updated, add a new row
    if not updated:
        if "o_file_list" in values_dict and isinstance(values_dict["o_file_list"], list):
            values_dict["o_file_list"] = ", ".join(values_dict["o_file_list"])  # Convert list to string
        rows.append(values_dict)

    # Write data back to the file
    with open(csv_file_name, mode='w', newline='') as csvfile:
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
        writer.writeheader()
        writer.writerows(rows)

# create entry point of program:
if __name__ == "__main__":

    measurement_path = "/Users/khannmohsin/Chipwhispere_vscode/Measurements"
    cycles_per_byte_file = os.path.join(measurement_path, "cycles_per_byte.csv")
    rom_file = os.path.join(measurement_path, "rom.csv")
    ram_file = os.path.join(measurement_path, "ram.csv")
    power_file =  os.path.join(measurement_path, "power.csv")

    # Parse command-line arguments
    parser = argparse.ArgumentParser(description="Update firmware with specified HASH_FUNCTION and HASH_VARIANT.")
    parser.add_argument("--hash-function", required=True, help="Specify the hash function (e.g., PHOTON).")
    parser.add_argument("--hash-variant", required=True, help="Specify the hash variant (e.g., 80).")
    args = parser.parse_args()

    # Extract arguments
    HASH_FUNC = args.hash_function
    HASH_VAR = args.hash_variant
    # Known values
    SHUNT_RESISTOR = 50  # Ohms
    SUPPLY_VOLTAGE = 3.3  # Volts (adjust based on your setup)

    # Initialize the scope and target
    scope = cw.scope()
    target = cw.target(scope, cw.targets.SimpleSerial)

    target.baud = 38400 #230400 #62524

    # Scope configuration
    SCOPETYPE = 'OPENADC'
    if SCOPETYPE == "OPENADC":
        scope.gain.db = 5
        scope.adc.samples = 5
        scope.adc.offset = 0
        scope.adc.basic_mode = "rising_edge"
        scope.adc.fifo_fill_mode = "normal"
        scope.clock.clkgen_src = 'system' 
        scope.clock.clkgen_freq = 7372800 #12000000
        scope.clock.adc_src = "clkgen_x4"
        # scope.clock.adc_freq = 29500000 #Need to be changed
        scope.trigger.triggers = "tio4"
        scope.io.tio1 = "serial_rx"
        scope.io.tio2 = "serial_tx"     
        scope.io.hs2 = "clkgen"

    print("\n----------------------Performing Post Firmware Update Processing----------------------\n")

    # Example usage of the functions
    # send_hash_function_name(target, HASH_FUNC, HASH_VAR)
    # receive_clock_cycles(target, HASH_FUNC)
    rms_power_mW, energy_nJ, cycles_per_byte = get_power_measurement_and_cycles(target, HASH_FUNC, HASH_VAR) 

    update_csv(HASH_FUNC, HASH_VAR, power_file, values_dict={"Power": rms_power_mW, "Energy" : energy_nJ })

    # update_csv(HASH_FUNC, HASH_VAR, cycles_per_byte_file, values_dict={"Cycles per byte": cycles_per_byte})

    # o_files_list, total_text_size, total_rodata_size, total_vectors_size, total_rom = get_ROM(HASH_FUNC, HASH_VAR)

    # update_csv(HASH_FUNC, HASH_VAR, rom_file, values_dict={"o_file_list": o_files_list, ".text size" : total_text_size, ".rodata size" : total_rodata_size, "vector size" : total_vectors_size, "total ROM" : total_rom })

    # o_files_list, total_data_size, total_bss_size, total_variables_ram, total_static_stack, total_dynamic_stack, total_stack = get_RAM(HASH_FUNC, HASH_VAR)
    # update_csv(HASH_FUNC, HASH_VAR, ram_file, values_dict={"o_file_list": o_files_list, ".data size" : total_data_size, ".bss size" : total_bss_size, "Total Variable Size " : total_variables_ram, "Static Stack Size" : total_static_stack,  "Dynamic Stack Size" : total_dynamic_stack, "Total Stack Size": total_stack, "Overall RAM" : total_static_stack + total_dynamic_stack + total_variables_ram})

    scope.dis()
    target.dis()

