################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
ESP_8266_client_MQTT.lss \

FLASH_IMAGE += \
ESP_8266_client_MQTT.hex \

EEPROM_IMAGE += \
ESP_8266_client_MQTT.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: ESP_8266_client_MQTT.elf secondary-outputs

# Tool invocations
ESP_8266_client_MQTT.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,ESP_8266_client_MQTT.map -mmcu=atmega32 -o "ESP_8266_client_MQTT.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ESP_8266_client_MQTT.lss: ESP_8266_client_MQTT.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S ESP_8266_client_MQTT.elf  >"ESP_8266_client_MQTT.lss"
	@echo 'Finished building: $@'
	@echo ' '

ESP_8266_client_MQTT.hex: ESP_8266_client_MQTT.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex ESP_8266_client_MQTT.elf  "ESP_8266_client_MQTT.hex"
	@echo 'Finished building: $@'
	@echo ' '

ESP_8266_client_MQTT.eep: ESP_8266_client_MQTT.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex ESP_8266_client_MQTT.elf  "ESP_8266_client_MQTT.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: ESP_8266_client_MQTT.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 ESP_8266_client_MQTT.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) ESP_8266_client_MQTT.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
