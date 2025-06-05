SHELL = /bin/sh -x

# Hey Emacs, this is a -*- makefile -*-
#----------------------------------------------------------------------------
#
# Makefile for ChipWhisperer SimpleSerial-AES Program
#
#----------------------------------------------------------------------------
# On command line:
#
# make all = Make software.
#
# make clean = Clean out built project files.
#
# make coff = Convert ELF to AVR COFF.
#
# make extcoff = Convert ELF to AVR Extended COFF.
#
# make program = Download the hex file to the device, using avrdude.
#                Please customize the avrdude settings below first!
#
# make debug = Start either simulavr or avarice as specified for debugging,
#              with avr-gdb or avr-insight as the front end for debugging.
#
# make filename.s = Just compile filename.c into the assembler code only.
#
# make filename.i = Create a preprocessed source file for use in submitting
#                   bug reports to the GCC project.
#
# To rebuild project do "make clean" then "make all".
#----------------------------------------------------------------------------

# Target file name (without extension).
# This is the name of the compiled .hex file.
TARGET = simpleserial-base

# List C source files here.
# Header files (.h) are automatically pulled in.

# Add source file for the specified hash function
ifeq ($(HASH_FUNCTION), PHOTON)
    SRC += LWHF/PHOTON/photon.c
    CFLAGS += -Iobjdir-CWLITEXMEGA/LWHF/PHOTON/
    CFLAGS += -D_PHOTON$(HASH_VARIANT)_
	CFLAGS += -D_HASH_FUNCTION_PHOTON_
	CFLAGS += -mmcu=atxmega128d3
	CFLAGS += -fstack-usage

else ifeq ($(HASH_FUNCTION), QUARK)
    SRC += LWHF/QUARK/quark.c
	CFLAGS += -Iobjdir-CWLITEXMEGA/LWHF/QUARK/
    CFLAGS += -D$(HASH_VARIANT)
	CFLAGS += -D_HASH_FUNCTION_QUARK_
	CFLAGS += -mmcu=atxmega128d3
	CFLAGS += -fstack-usage

else ifeq ($(HASH_FUNCTION), SPONGENT)
	SRC += LWHF/SPONGENT/spongent.c
	CFLAGS += -Iobjdir-CWLITEXMEGA/LWHF/SPONGENT/
	CFLAGS += -D_SPONGENT$(HASH_VARIANT)_
	CFLAGS += -D_HASH_FUNCTION_SPONGENT_
	CFLAGS += -mmcu=atxmega128d3
	CFLAGS += -fstack-usage

else ifeq ($(HASH_FUNCTION), LESAMNTA)
	SRC += LWHF/LESAMNTA/lesamnta-LW.c
	CFLAGS += -Iobjdir-CWLITEXMEGA/LWHF/LESAMNTA/
	# CFLAGS += -D_LESAMNTA$(HASH_VARIANT)_
	CFLAGS += -D_HASH_FUNCTION_LESAMNTA_
	CFLAGS += -mmcu=atxmega128d3
	CFLAGS += -fstack-usage

else ifeq ($(HASH_FUNCTION), ASCON)
	SRC += LWHF/ASCON/hash.c LWHF/ASCON/printstate.c
	CFLAGS += -Iobjdir-CWLITEXMEGA/LWHF/ASCON/
	# CFLAGS += -D_ASCON$(HASH_VARIANT)_
	CFLAGS += -D_HASH_FUNCTION_ASCON_
	CFLAGS += -mmcu=atxmega128d3
	CFLAGS += -fstack-usage

else ifeq ($(HASH_FUNCTION), PHOTON_BEETLE)
	SRC += LWHF/PHOTON_BEETLE/hash.c LWHF/PHOTON_BEETLE/photon.c
	CFLAGS += -Iobjdir-CWLITEXMEGA/LWHF/PHOTON_BEETLE/
	# CFLAGS += -D_PHOTON_BEETLE$(HASH_VARIANT)_
	CFLAGS += -D_HASH_FUNCTION_PHOTON_BEETLE_
	CFLAGS += -mmcu=atxmega128d3
	CFLAGS += -fstack-usage

else ifeq ($(HASH_FUNCTION), XOODYAK)
	SRC += LWHF/XOODYAK/Xoodyak.c LWHF/XOODYAK/Xoodoo-reference.c
	CFLAGS += -Iobjdir-CWLITEXMEGA/LWHF/XOODYAK/
	# CFLAGS += -D_XOODYAK$(HASH_VARIANT)_
	CFLAGS += -D_HASH_FUNCTION_XOODYAK_
	CFLAGS += -mmcu=atxmega128d3
	CFLAGS += -fstack-usage

else ifeq ($(HASH_FUNCTION), KNOT)
	SRC += LWHF/KNOT/hash.c
	CFLAGS += -Iobjdir-CWLITEXMEGA/LWHF/KNOT/
	# CFLAGS += -D_KNOT$(HASH_VARIANT)_
	CFLAGS += -D_HASH_FUNCTION_KNOT_
	CFLAGS += -mmcu=atxmega128d3
	CFLAGS += -fstack-usage

else ifeq ($(HASH_FUNCTION), ORANGE)
	SRC += LWHF/ORANGE/hash.c
	CFLAGS += -Iobjdir-CWLITEXMEGA/LWHF/ORANGE/
	# CFLAGS += -D_ORANGE$(HASH_VARIANT)_
	CFLAGS += -D_HASH_FUNCTION_ORANGE_
	CFLAGS += -mmcu=atxmega128d3
	CFLAGS += -fstack-usage

else ifeq ($(HASH_FUNCTION), SHAMAS)
	SRC += LWHF/SHAMAS/hash.c
	CFLAGS += -Iobjdir-CWLITEXMEGA/LWHF/SHAMAS/
	# CFLAGS += -D_SHAMAS$(HASH_VARIANT)_
	CFLAGS += -D_HASH_FUNCTION_SHAMAS_
	CFLAGS += -mmcu=atxmega128d3
	CFLAGS += -fstack-usage

else ifeq ($(HASH_FUNCTION), SIVRIJNDAEL)
	SRC += LWHF/SIVRIJNDAEL/hash.c LWHF/SIVRIJNDAEL/rijndael-alg-ref.c LWHF/SIVRIJNDAEL/rijndael256.c
	CFLAGS += -Iobjdir-CWLITEXMEGA/LWHF/SIVRIJNDAEL/
	# CFLAGS += -D_SIVRIJNDAEL$(HASH_VARIANT)_
	CFLAGS += -D_HASH_FUNCTION_SIVRIJNDAEL_
	CFLAGS += -mmcu=atxmega128d3
	CFLAGS += -fstack-usage

else ifeq ($(HASH_FUNCTION), SIVTEMPHOTON)
	SRC += LWHF/SIVTEMPHOTON/hash.c LWHF/SIVTEMPHOTON/photon.c
	CFLAGS += -Iobjdir-CWLITEXMEGA/LWHF/SIVTEMPHOTON/
	# CFLAGS += -D_SIVTEMPHOTON$(HASH_VARIANT)_
	CFLAGS += -D_HASH_FUNCTION_SIVTEMPHOTON_
	CFLAGS += -mmcu=atxmega128d3
	CFLAGS += -fstack-usage

else ifeq ($(HASH_FUNCTION), SKINNY)
	SRC += LWHF/SKINNY/hash.c LWHF/SKINNY/skinny_reference.c LWHF/SKINNY/skinny_hash.c
	CFLAGS += -Iobjdir-CWLITEXMEGA/LWHF/SKINNY/
	# CFLAGS += -D_SKINNY$(HASH_VARIANT)_
	CFLAGS += -D_HASH_FUNCTION_SKINNY_
	CFLAGS += -mmcu=atxmega128d3
	CFLAGS += -fstack-usage

else ifeq ($(HASH_FUNCTION), SNEIK)
	SRC += LWHF/SNEIK/hash.c LWHF/SNEIK/blnk.c LWHF/SNEIK/sneik_f512_c99.c 
	CFLAGS += -Iobjdir-CWLITEXMEGA/LWHF/SNEIK/
	# CFLAGS += -D_SNEIK$(HASH_VARIANT)_
	CFLAGS += -D_HASH_FUNCTION_SNEIK_
	CFLAGS += -mmcu=atxmega128d3
	CFLAGS += -fstack-usage

else ifeq ($(HASH_FUNCTION), TRIAD)
	SRC += LWHF/TRIAD/hash.c 
	CFLAGS += -Iobjdir-CWLITEXMEGA/LWHF/TRIAD/
	# CFLAGS += -D_TRIAD$(HASH_VARIANT)_
	CFLAGS += -D_HASH_FUNCTION_TRIAD_
	CFLAGS += -mmcu=atxmega128d3
	CFLAGS += -fstack-usage

else ifeq ($(HASH_FUNCTION), CORAL)
	SRC += LWHF/CORAL/hash.c 
	CFLAGS += -Iobjdir-CWLITEXMEGA/LWHF/CORAL/
	# CFLAGS += -D_CORAL$(HASH_VARIANT)_
	CFLAGS += -D_HASH_FUNCTION_CORAL_
	CFLAGS += -mmcu=atxmega128d3
	CFLAGS += -fstack-usage

else ifeq ($(HASH_FUNCTION), GIMLI)
	SRC += LWHF/GIMLI/gimli_hash.c 
	CFLAGS += -Iobjdir-CWLITEXMEGA/LWHF/GIMLI/
	# CFLAGS += -D_GIMLI$(HASH_VARIANT)_
	CFLAGS += -D_HASH_FUNCTION_GIMLI_
	CFLAGS += -mmcu=atxmega128d3
	CFLAGS += -fstack-usage

else ifeq ($(HASH_FUNCTION), DRYGASCON)

	ifeq ($(HASH_VARIANT), 128)
		SRC += LWHF/DRYGASCON/drygascon_128/hash.c
		CFLAGS += -Iobjdir-CWLITEXMEGA/LWHF/DRYGASCON/drygascon_128/
		# CFLAGS += -D_DRYGASCON$(HASH_VARIANT)_
		CFLAGS += -D_HASH_FUNCTION_DRYGASCON_128_
		CFLAGS += -mmcu=atxmega128d3
		CFLAGS += -fstack-usage

	else ifeq ($(HASH_VARIANT), 256)
		SRC += LWHF/DRYGASCON/drygascon_256/hash.c
		CFLAGS += -Iobjdir-CWLITEXMEGA/LWHF/DRYGASCON/drygascon_256/
		# CFLAGS += -D_DRYGASCON$(HASH_VARIANT)_
		CFLAGS += -D_HASH_FUNCTION_DRYGASCON_256_
		CFLAGS += -mmcu=atxmega128d3
		CFLAGS += -fstack-usage
    else
        $(error Unsupported HASH_VARIANT: $(HASH_VARIANT))
	endif

else ifeq ($(HASH_FUNCTION), CLX)
	SRC += LWHF/CLX/hash.c
	CFLAGS += -Iobjdir-CWLITEXMEGA/LWHF/CLX/
	# CFLAGS += -D_CLX$(HASH_VARIANT)_
	CFLAGS += -D_HASH_FUNCTION_CLX_
	CFLAGS += -mmcu=atxmega128d3
	CFLAGS += -fstack-usage

else ifeq ($(HASH_FUNCTION), ACE)
	SRC += LWHF/ACE/hash.c LWHF/ACE/ace.c
	CFLAGS += -Iobjdir-CWLITEXMEGA/LWHF/ACE/
	# CFLAGS += -D_ACE$(HASH_VARIANT)_
	CFLAGS += -D_HASH_FUNCTION_ACE_
	CFLAGS += -mmcu=atxmega128d3
	CFLAGS += -fstack-usage

else ifeq ($(HASH_FUNCTION), SPARKLE)
	SRC += LWHF/SPARKLE/hash.c LWHF/SPARKLE/sparkle_ref.c
	CFLAGS += -Iobjdir-CWLITEXMEGA/LWHF/SPARKLE/
	# CFLAGS += -D_SPARKLE$(HASH_VARIANT)_
	CFLAGS += -D_HASH_FUNCTION_SPARKLE_
	CFLAGS += -mmcu=atxmega128d3
	CFLAGS += -fstack-usage

else ifeq ($(HASH_FUNCTION), SUBTERRAINEAN)
	SRC += LWHF/SUBTERRAINEAN/subterranean_ref.c LWHF/SUBTERRAINEAN/crypto_hash.c
	CFLAGS += -Iobjdir-CWLITEXMEGA/LWHF/SUBTERRAINEAN/
	# CFLAGS += -D_SUBTERRAINEAN$(HASH_VARIANT)_
	CFLAGS += -D_HASH_FUNCTION_SUBTERRAINEAN_
	CFLAGS += -mmcu=atxmega128d3
	CFLAGS += -fstack-usage

else ifeq ($(HASH_FUNCTION), SATURNIN)
	SRC += LWHF/SATURNIN/hash.c LWHF/SATURNIN/saturnin.c
	CFLAGS += -Iobjdir-CWLITEXMEGA/LWHF/SATURNIN/
	# CFLAGS += -D_SATURNIN$(HASH_VARIANT)_
	CFLAGS += -D_HASH_FUNCTION_SATURNIN_
	CFLAGS += -mmcu=atxmega128d3
	CFLAGS += -fstack-usage

else ifeq ($(HASH_FUNCTION), ISAP)
	SRC += LWHF/ISAP/hash.c  LWHF/ISAP/Ascon-reference.c
	CFLAGS += -Iobjdir-CWLITEXMEGA/LWHF/ISAP/
	# CFLAGS += -D_ISAP$(HASH_VARIANT)_
	CFLAGS += -D_HASH_FUNCTION_ISAP_
	CFLAGS += -mmcu=atxmega128d3
	CFLAGS += -fstack-usage

else ifeq ($(HASH_FUNCTION), GAGE)
	SRC += LWHF/GAGE/hash.c LWHF/GAGE/constants.c
	CFLAGS += -Iobjdir-CWLITEXMEGA/LWHF/GAGE/
	# CFLAGS += -D_GAGE$(HASH_VARIANT)_
	CFLAGS += -D_HASH_FUNCTION_GAGE_
	CFLAGS += -mmcu=atxmega128d3
	CFLAGS += -fstack-usage

else ifeq ($(HASH_FUNCTION), BLAKE3)
	SRC += LWHF/BLAKE3/blake3.c LWHF/BLAKE3/blake3_dispatch.c LWHF/BLAKE3/blake3_portable.c 
	CFLAGS += -Iobjdir-CWLITEXMEGA/LWHF/BLAKE3/
	# CFLAGS += -D_BLAKE3$(HASH_VARIANT)_
	CFLAGS += -D_HASH_FUNCTION_BLAKE3_
	CFLAGS += -mmcu=atxmega128d3
	CFLAGS += -fstack-usage

else ifeq ($(HASH_FUNCTION), BLAKE2)
	SRC += LWHF/BLAKE2/blake2s-ref.c
	CFLAGS += -Iobjdir-CWLITEXMEGA/LWHF/BLAKE2/
	# CFLAGS += -D_BLAKE2s$(HASH_VARIANT)_
	CFLAGS += -D_HASH_FUNCTION_BLAKE2s_
	CFLAGS += -mmcu=atxmega128d3
	CFLAGS += -fstack-usage


else
    $(error Unsupported HASH_FUNCTION: $(HASH_FUNCTION))
endif




# SRC += LWHF/3_PHOTON/photon.c

# CFLAGS += -Iobjdir-CWLITEXMEGA/LWHF/3_PHOTON/

# CFLAGS += -D_PHOTON80_ 

SRC += simpleserial-base-clock_power.c 


# ----------Added by me 		---------------------------------------------

# CFLAGS += -D_PHOTON80_

# -------------------------------------------------------------------------



# -----------------------------------------------------------------------------

ifeq ($(CRYPTO_OPTIONS),)
CRYPTO_OPTIONS = AES128C
endif

#Add simpleserial project to build
include ../simpleserial/Makefile.simpleserial

FIRMWAREPATH = ../.
include $(FIRMWAREPATH)/Makefile.inc