import subprocess
import os
import time

# List of hash functions and their variants
hash_functions = {
    "PHOTON": ["80", "128", "256"],
    # "QUARK": ["UQUARK", "CQUARK", "SQUARK"],
    # "SPONGENT": ["088080008", "088176088", "128128008", "128256128", "160160016", "160160080", "224224016", "224224112", "256256016", "256256128"],
    "LESAMNTA": ["256"],
    "ASCON": ["256"],
    "PHOTON_BEETLE": ["256"],
    "XOODYAK": ["256"], 
    "KNOT": ["256"],
    "ORANGE": ["256"], 
    "SHAMAS": ["256"], 
    "SIVRIJNDAEL": ["256"], 
    "SIVTEMPHOTON": ["256"], 
    "SKINNY": ["256"], 
    "SNEIK": ["256"], 
    "TRIAD": ["256"], 
    "CORAL": ["256"], 
    "GIMLI": ["256"],
    "DRYGASCON": ["128", "256"],
    "CLX": ["256"], 
    "ACE": ["256"], 
    "SPARKLE": ["256"], 
    "SUBTERRAINEAN": ["256"], 
    "SATURNIN": ["256"], 
    "ISAP": ["256"], 
    "GAGE": ["256"], 
    "BLAKE3": ["256"], 
    "BLAKE2": ["256"],
}

# Path to your main_init.py script
main_script = "/Users/khannmohsin/Chipwhispere_vscode/main_init.py"

# Log file to record test results
log_file = "test_results.log"

# Function to run the test
def run_test(hash_function, variant):
    try:
        print(f"Testing {hash_function} with variant {variant}...")
        
        # Run the main script with the hash function and variant
        result = subprocess.run(
            [
                "python", main_script,
                hash_function, variant
            ],
            capture_output=True,
            text=True,
        )

        # Check the result and log it
        if result.returncode == 0:
            print(f"PASS: {hash_function} {variant}")
            log_message = f"PASS: {hash_function} {variant}\n"
        else:
            print(f"FAIL: {hash_function} {variant}")
            log_message = f"FAIL: {hash_function} {variant}\nOutput:\n{result.stderr}\n"

        # Write to the log file
        with open(log_file, "a") as log:
            log.write(log_message)

    except Exception as e:
        print(f"ERROR: {hash_function} {variant}")
        with open(log_file, "a") as log:
            log.write(f"ERROR: {hash_function} {variant} - {str(e)}\n")

# Main testing loop
def main():
    # Clear the log file at the start
    if os.path.exists(log_file):
        os.remove(log_file)

    # Iterate through all hash functions and variants
    for hash_function, variants in hash_functions.items():
        for variant in variants:
            for _ in range(10):
                run_test(hash_function, variant)
            time.sleep(1)  # Small delay between tests

    print("Testing complete. Check test_results.log for details.")

if __name__ == "__main__":
    main()