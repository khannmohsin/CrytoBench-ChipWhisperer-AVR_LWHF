import subprocess
import sys
import os

def main():
    # Get HASH_FUNCTION and HASH_VARIANT as input from the user or command-line arguments
    if len(sys.argv) < 3:
        print("Usage: python main_init.py <HASH_FUNCTION> <HASH_VARIANT>")
        sys.exit(1)

    hash_function = sys.argv[1]
    hash_variant = sys.argv[2]

    # Paths to the other scripts
    firmware_script = "/Users/khannmohsin/Chipwhispere_vscode/firmware_update_xmega.py"
    post_fw_script = "/Users/khannmohsin/Chipwhispere_vscode/post_fw_program.py"

    # Run firmware_update_xmega.py with the provided HASH_FUNCTION and HASH_VARIANT
    print("Running Firmware Update of XMEGA...")
    firmware_process = subprocess.run([
        "python", firmware_script,
        f"--hash-function={hash_function}",
        f"--hash-variant={hash_variant}"
    ])

    if firmware_process.returncode != 0:
        print("Error: Firmware Update to XMEGA failed.")
        sys.exit(1)

    # Run post_fw_program.py
    print("Running post_fw_program.py...")
    post_fw_process = subprocess.run([
        "python", post_fw_script,
        f"--hash-function={hash_function}",
        f"--hash-variant={hash_variant}"
    ])

    if post_fw_process.returncode != 0:
        print("Error: post_fw_program.py failed.")
        sys.exit(1)

    print("Both scripts executed successfully.")

if __name__ == "__main__":
    main()
