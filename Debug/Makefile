################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../Visual\ Micro/


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../adc.c \
../board.c \
../pwm.c \
../shell.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
adc.o \
board.o \
pwm.o \
shell.o


OBJS_AS_ARGS +=  \
adc.o \
board.o \
pwm.o \
shell.o


C_DEPS +=  \
adc.d \
board.d \
pwm.d \
shell.d


C_DEPS_AS_ARGS +=  \
adc.d \
board.d \
pwm.d \
shell.d


OUTPUT_FILE_PATH +=Peltier_FW_Arduino.elf

OUTPUT_FILE_PATH_AS_ARGS +=Peltier_FW_Arduino.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

# AVR32/GNU C Compiler









./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C++ Compiler : 
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.876\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -funsigned-char -funsigned-bitfields -D__AVR_ATmega32U4__ -DARDUINO=105 -DF_CPU=16000000L -D__AVR__  -I"C:\Program Files (x86)\Arduino\hardware\arduino\cores\arduino" -I"C:\Program Files (x86)\Arduino\hardware\arduino\variants\micro" -I"C:\Program Files (x86)\Arduino\libraries\EEPROM" -I"C:\Program Files (x86)\Arduino\libraries\EEPROM\utility" -I"C:\Program Files (x86)\Arduino\libraries\Esplora" -I"C:\Program Files (x86)\Arduino\libraries\Esplora\utility" -I"C:\Program Files (x86)\Arduino\libraries\Ethernet" -I"C:\Program Files (x86)\Arduino\libraries\Ethernet\utility" -I"C:\Program Files (x86)\Arduino\libraries\Firmata" -I"C:\Program Files (x86)\Arduino\libraries\Firmata\utility" -I"C:\Program Files (x86)\Arduino\libraries\GSM" -I"C:\Program Files (x86)\Arduino\libraries\GSM\utility" -I"C:\Program Files (x86)\Arduino\libraries\LiquidCrystal" -I"C:\Program Files (x86)\Arduino\libraries\LiquidCrystal\utility" -I"C:\Program Files (x86)\Arduino\libraries\NIL_OS" -I"C:\Program Files (x86)\Arduino\libraries\NIL_OS\utility" -I"C:\Program Files (x86)\Arduino\libraries\Robot_Control" -I"C:\Program Files (x86)\Arduino\libraries\Robot_Control\utility" -I"C:\Program Files (x86)\Arduino\libraries\Robot_Motor" -I"C:\Program Files (x86)\Arduino\libraries\Robot_Motor\utility" -I"C:\Program Files (x86)\Arduino\libraries\SD" -I"C:\Program Files (x86)\Arduino\libraries\SD\utility" -I"C:\Program Files (x86)\Arduino\libraries\Servo" -I"C:\Program Files (x86)\Arduino\libraries\Servo\utility" -I"C:\Program Files (x86)\Arduino\libraries\SoftwareSerial" -I"C:\Program Files (x86)\Arduino\libraries\SoftwareSerial\utility" -I"C:\Program Files (x86)\Arduino\libraries\SPI" -I"C:\Program Files (x86)\Arduino\libraries\SPI\utility" -I"C:\Program Files (x86)\Arduino\libraries\Stepper" -I"C:\Program Files (x86)\Arduino\libraries\Stepper\utility" -I"C:\Program Files (x86)\Arduino\libraries\TFT" -I"C:\Program Files (x86)\Arduino\libraries\TFT\utility" -I"C:\Program Files (x86)\Arduino\libraries\WiFi" -I"C:\Program Files (x86)\Arduino\libraries\WiFi\utility" -I"C:\Program Files (x86)\Arduino\libraries\Wire" -I"C:\Program Files (x86)\Arduino\libraries\Wire\utility" -I"c:\program files (x86)\arduino\hardware\tools\avr\avr\include" -I"c:\program files (x86)\arduino\hardware\tools\avr\avr\include\avr" -I"c:\program files (x86)\arduino\hardware\tools\avr\avr" -I"c:\program files (x86)\arduino\hardware\tools\avr\lib\gcc\avr\4.3.2\include"  -O1 -ffunction-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega32u4 -c -std=gnu99 -include=arduino.h -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o"$@" "$<" 
	@echo Finished building: $<



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP)
	@echo Building target: $@
	@echo Invoking: AVR8/GNU Linker : 
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.876\avr8-gnu-toolchain\bin\avr-g++.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="Peltier_FW_Arduino.map" -Wl,--start-group  -Wl,--end-group -Wl,--gc-sections -mmcu=atmega32u4 
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.876\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "Peltier_FW_Arduino.elf" "Peltier_FW_Arduino.hex"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.876\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "Peltier_FW_Arduino.elf" "Peltier_FW_Arduino.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.876\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "Peltier_FW_Arduino.elf" > "Peltier_FW_Arduino.lss"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.876\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature  "Peltier_FW_Arduino.elf" "Peltier_FW_Arduino.srec"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.876\avr8-gnu-toolchain\bin\avr-size.exe" "Peltier_FW_Arduino.elf"
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS)$(C_DEPS_AS_ARGS) $(EXECUTABLES) 
	rm -rf "Peltier_FW_Arduino.elf" "Peltier_FW_Arduino.a" "Peltier_FW_Arduino.hex" "Peltier_FW_Arduino.lss" "Peltier_FW_Arduino.eep" "Peltier_FW_Arduino.map" "Peltier_FW_Arduino.srec"
	