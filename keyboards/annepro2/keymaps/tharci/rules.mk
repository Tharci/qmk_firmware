# Other featues
CONSOLE_ENABLE = yes
COMMAND_ENABLE = yes
# DEBUG_EEPROM = yes

ifeq ($(strip $(BOARD)), ANNEPRO2_C18)
ANNEPRO2_EEPROM = yes
endif

ifeq ($(strip $(ANNEPRO2_EEPROM)), yes)
    OPT_DEFS += -DANNEPRO2_EEPROM
    SRC += spi_master.c eeprom_w25x20cl.c
endif


LEADER_ENABLE = yes
# UNICODEMAP_ENABLE = yes
TAP_DANCE_ENABLE = yes
RAW_ENABLE = yes
NKRO_ENABLE = yes

SRC += ble.c
SRC += led.c
SRC += hid_comm.c
SRC += persistence.c
