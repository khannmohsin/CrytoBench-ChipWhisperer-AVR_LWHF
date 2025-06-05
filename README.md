# CrytoBench-ChipWhisperer-AVR_LWHF: Benchmarking Lightweight Hash Functions on AVR using ChipWhisperer

This project implements a full-stack benchmarking suite for **Lightweight Hash Functions (LWHFs)** on resource-constrained microcontrollers using the **ChipWhisperer cryptanalysis platform**. It integrates firmware-level instrumentation, host-side automation, and power profiling into a cohesive framework for analyzing cryptographic primitives.

---

## Overview

This project supports benchmarking of 22 LWHFs (NIST submissions, ISO standards, and SHA-3 variants) and evaluates them on the following metrics:

- **Execution time**: Cycles per Byte (CPB)
- **Energy consumption**: Estimated from voltage traces
- **Memory usage**: RAM and ROM footprint from `.map` and `.su` files
- **E-RANK**: Composite performance-cost metric

It includes modular firmware templates for the **ATxmega128D4** and integrates seamlessly with ChipWhisperer for side-channel-resilient measurements.

---

## Directory Structure

```
CW_project/
├── *.py                          # Python automation scripts
│   ├── main_init.py              # Initialize ChipWhisperer & flash target
│   ├── post_fw_program.py        # Collect benchmarks (CPB, power, memory)
│   ├── power_measurement.py      # Energy profiling logic
│   ├── E_rank.py                 # Computes E-RANK metric
│   ├── heatmap.py                # Visualization
│   └── test_cases_LWHF.py        # Runs and validates hash outputs
├── *.c / *.h                     # C source for firmware on target MCU
│   ├── main_target.c             # Entry point
│   ├── simpleserial.c/.h         # Serial comm via ChipWhisperer
│   └── hal.h                     # MCU abstraction layer
├── chipwhisperer_mod/            # Modified ChipWhisperer clone (submodule)
│   └── firmware
│       └── mcu
|           ├── LWHF-SS-template/        # Custom firmware template for ChipWhisperer
│           ├── simpleserial-base*.c     # Base and clock/power variants
│           ├── makefile                 # Makefile for XMEGA
│           └── LWHF/                    # Subfolders for LWHF variants 
└── Manuscript/LightSec.pdf     # Full academic writeup
```

---

## Setup Instructions

### Prerequisites

- Python 3.8+
- AVR-GCC toolchain (`avr-gcc`, `avr-objcopy`, `avr-size`)
- [ChipWhisperer](https://newae.com/tools/chipwhisperer/) hardware and Python API
- Git (for submodules)

To better understand the system's architecture, refer to the following diagram:

![ChipWhisperer Architecture](Manuscripts/Arch_Chipwhisperer.png)

### Python Dependencies

```bash
pip install chipwhisperer matplotlib numpy pandas
```

---

## Running Benchmarks

### 1. Flash Firmware to Target

Choose the LWHF in `main_target.c` or `LWHF-SS-template/`, then:

```bash
python3 main_init.py
```

Or use the Makefile directly:

```bash
cd LWHF-SS-template
make PLATFORM=CWLITEXMEGA FIRMWARE=simpleserial-base-clock_power
```

### Flashing Firmware with `firmware_update_xmega.py`

For modular and automated firmware flashing based on a specific hash function and variant, use:

```bash
python3 firmware_update_xmega.py --hash-function PHOTON --hash-variant 256
```

This script performs the following:
- Removes old compiled firmware artifacts
- Rebuilds the firmware with `make`, passing in the selected LWHF and variant
- Initializes the ChipWhisperer scope
- Programs the ATxmega128D4 device using the generated `.hex` file

The script relies on these parameters:
- `--hash-function`: Folder name in `LWHF/` (e.g., `PHOTON`, `SNEIK`)
- `--hash-variant`: Variant identifier (e.g., `80`, `256`, or custom)

Ensure paths inside the script match your local installation.
"""

### 2. Trigger Benchmark Execution

```bash
python3 post_fw_program.py --hash-function PHOTON --hash-variant 256
```

This script includes:
- Sending test vectors over UART to the flashed firmware
- Receiving and parsing the cycle count (CPB)
- Capturing ADC traces and calculating energy using RMS power
- Profiling ROM and RAM using `.map` and `.su` files
- Exporting measurements to structured CSV logs (e.g., `power.csv`, `rom.csv`, `ram.csv`)

### 3. Compute E-RANK

```bash
python3 E_rank.py
```

### 4. Visualize Results

```bash
python3 heatmap.py
```

---

## Adding a New Hash Function

You can test new LWHFs in isolation before firmware integration. Example:

###  Compile and Run: Lesamnta-LW
```bash
gcc -o lesamnta_hash lesamnta_hash.c lesamnta-LW.c -O3
./lesamnta_hash
```

### Compile and Run: PHOTON-256
```bash
gcc -D_PHOTON256_ -o Photon_hash Photon_hash.c photon.c -O3
./Photon_hash
```

Then to integrate:

1. Create a subfolder in `LWHF-SS-template/LWHF/`
2. Add your implementation (`e.g., sneik_hash.c`, `blnk.h`)
3. Modify `simpleserial-base.c` to add a handler function (e.g., under `case 'p':`)
4. Compile with:
```bash
make PLATFORM=CWLITEXMEGA FIRMWARE=simpleserial-base
```
5. Flash and profile using `main_init.py` and `post_fw_program.py`

---

## Benchmarking Details

### Memory Profiling

- `.map` files parsed for `.data`, `.bss`, `.text`, `.rodata`
- `.su` files parsed for stack usage

### Energy Profiling

- Power calculated from ADC voltage traces using Ohm’s law
- RMS energy computed and normalized

### E-RANK Formula

```text
E-RANK = (10^9 / CPB) / [(ROM + 2×RAM) × Energy]
```

---

## Reference

**Paper**: *Software Benchmarking and Comparative Performance Analysis of NIST Submitted and ISO Standardized LWHFs*  
**Authors**: [Author Names]  
**Platform**: AVR ATXMega128D4 + ChipWhisperer  
**Year**: 2025

---

## Citation

```bibtex
@inproceedings{lightsec2025,
  title={Software Benchmarking and Comparative Performance Analysis of NIST Submitted and ISO Standardized Lightweight Hash Functions},
  author={[Author Names]},
  booktitle={LightSec Conference},
  year={2025}
}
```

---

## License

This project includes custom code and adaptations of ChipWhisperer (© NewAE Technology). Custom LWHF instrumentation developed by [Your Name or Institution].
"""

