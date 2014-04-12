
# Put your stlink folder here so make burn will work.
# STLINK=~/stlink.git

# Put your source files here (or *.c, etc)
SRCS = main.c system_stm32f4xx.c
SRCS += system.c
SRCS += leds.c
SRCS += kalman.c

# Drivers
SRCS += stm32f4xx_rcc.c stm32f4xx_exti.c stm32f4xx_gpio.c stm32f4xx_it.c stm32f4xx_usart.c misc.c stm32f4xx_rng.c stm32f4xx_syscfg.c

# ARM math - Matrix functions
SRCS += arm_mat_add_f32.c\
				arm_mat_add_q15.c\
				arm_mat_add_q31.c\
				arm_mat_init_f32.c\
				arm_mat_init_q15.c\
				arm_mat_init_q31.c\
				arm_mat_inverse_f32.c\
				arm_mat_mult_f32.c\
				arm_mat_mult_fast_q15.c\
				arm_mat_mult_fast_q31.c\
				arm_mat_mult_q15.c\
				arm_mat_mult_q31.c\
				arm_mat_scale_f32.c\
				arm_mat_scale_q15.c\
				arm_mat_scale_q31.c\
				arm_mat_sub_f32.c\
				arm_mat_sub_q15.c\
				arm_mat_sub_q31.c\
				arm_mat_trans_f32.c\
				arm_mat_trans_q15.c\
				arm_mat_trans_q31.c

# Binaries will be generated with this name (.elf, .bin, .hex, etc)
PROJ_NAME=drone

# Put your STM32F4 library code directory here
STM_COMMON=../STM32F4-Discovery_FW_V1.1.0

# Normally you shouldn't need to change anything below this line!
#######################################################################################

CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy
SIZE=arm-none-eabi-size

CFLAGS  = -g -O2 -Wall -Tstm32_flash.ld
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS += -I.

CFLAGS += -fno-strict-aliasing
CFLAGS += -DUSE_STDPERIPH_DRIVER
CFLAGS += -DSTM32D4XX
CFLAGS += -DARM_MATH_CM4
CFLAGS += -D__FPU_PRESENT

vpath %.c \
			$(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/src \
			$(STM_COMMON)/Libraries/STM32_USB_OTG_Driver/src \
			$(STM_COMMON)/Libraries/STM32_USB_Device_Library/Core/src \
			$(STM_COMMON)/Libraries/STM32_USB_Device_Library/Class/cdc/src \
			$(STM_COMMON)/Libraries/CMSIS/DSP_Lib/Source/MatrixFunctions

# Include files from STM libraries
CFLAGS += -I$(STM_COMMON)/Utilities/STM32F4-Discovery
CFLAGS += -I$(STM_COMMON)/Libraries/CMSIS/Include -I$(STM_COMMON)/Libraries/CMSIS/ST/STM32F4xx/Include
CFLAGS += -I$(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/inc
CFLAGS += -I$(STM_COMMON)/Libraries/STM32_USB_Device_Library/Class/cdc/inc
CFLAGS += -I$(STM_COMMON)/Libraries/STM32_USB_Device_Library/Core/inc
CFLAGS += -I$(STM_COMMON)/Libraries/STM32_USB_OTG_Driver/inc

# add startup file to build
SRCS += $(STM_COMMON)/Libraries/CMSIS/ST/STM32F4xx/Source/Templates/TrueSTUDIO/startup_stm32f4xx.s

OBJS = $(SRCS:.c=.o)


.PHONY: proj

all: proj
	$(SIZE) $(PROJ_NAME).elf

proj: $(PROJ_NAME).elf

$(PROJ_NAME).elf: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBPATHS) $(LIBS)
	$(OBJCOPY) -O ihex $(PROJ_NAME).elf $(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin

clean:
	find . -name \*.o -type f -delete
	find . -name \*.lst -type f -delete
	rm -f $(PROJ_NAME).elf
	rm -f $(PROJ_NAME).bin
	rm -f $(PROJ_NAME).hex

# Flash the STM32F4
burn: proj
	st-flash write $(PROJ_NAME).bin 0x8000000