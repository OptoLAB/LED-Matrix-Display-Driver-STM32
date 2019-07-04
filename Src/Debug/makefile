################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include displayDriver/subdir.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
-include Middlewares/Third_Party/FatFs/src/option/subdir.mk
-include Middlewares/Third_Party/FatFs/src/subdir.mk
-include Examples/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
LED_MATRIX_DISPLAY_STM32.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
LED_MATRIX_DISPLAY_STM32.list \

OBJCOPY_HEX += \
LED_MATRIX_DISPLAY_STM32.hex \

OBJCOPY_BIN += \
LED_MATRIX_DISPLAY_STM32.bin \


# All Target
all: LED_MATRIX_DISPLAY_STM32.elf secondary-outputs

# Tool invocations
LED_MATRIX_DISPLAY_STM32.elf: $(OBJS) $(USER_OBJS) C:\Users\Jovan\Desktop\LED_MATRIX_DISPLAY_STM32\STM32F415RGTX_FLASH.ld
	arm-none-eabi-gcc -o "LED_MATRIX_DISPLAY_STM32.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\Jovan\Desktop\LED_MATRIX_DISPLAY_STM32\STM32F415RGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="LED_MATRIX_DISPLAY_STM32.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

LED_MATRIX_DISPLAY_STM32.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "LED_MATRIX_DISPLAY_STM32.list"
	@echo 'Finished building: $@'
	@echo ' '

LED_MATRIX_DISPLAY_STM32.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "LED_MATRIX_DISPLAY_STM32.hex"
	@echo 'Finished building: $@'
	@echo ' '

LED_MATRIX_DISPLAY_STM32.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "LED_MATRIX_DISPLAY_STM32.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
