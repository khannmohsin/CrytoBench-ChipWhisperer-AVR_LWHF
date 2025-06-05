def calculate_erank(cpb, ram, rom, energy_nj):
    """
    Calculate the E-RANK of a lightweight hash function.

    Parameters:
    - cpb: Cycles per Byte (int or float)
    - ram: RAM usage in bytes (int)
    - rom: ROM usage in bytes (int)
    - energy_nj: Energy consumption in nanojoules (float)

    Returns:
    - e_rank: The calculated E-RANK (float)
    """
    denominator = (rom + 2 * ram) * energy_nj
    e_rank = (1e9 / cpb) / denominator
    return e_rank


# Input values
cpb = float(input("Enter Cycles per Byte (CpB): "))
ram = int(input("Enter RAM (in bytes): "))
rom = int(input("Enter ROM (in bytes): "))
energy_nj = float(input("Enter Energy (in nJ): "))

# Call the function
e_rank = calculate_erank(cpb, ram, rom, energy_nj)

# Print result
print("E-RANK:", e_rank)