################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../code/inc/FindEndrow.c \
../code/inc/FindMidline.c \
../code/inc/Servo.c 

COMPILED_SRCS += \
code/inc/FindEndrow.src \
code/inc/FindMidline.src \
code/inc/Servo.src 

C_DEPS += \
code/inc/FindEndrow.d \
code/inc/FindMidline.d \
code/inc/Servo.d 

OBJS += \
code/inc/FindEndrow.o \
code/inc/FindMidline.o \
code/inc/Servo.o 


# Each subdirectory must supply rules for building sources it contributes
code/inc/FindEndrow.src: ../code/inc/FindEndrow.c code/inc/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc26xb "-fE:/zheshiche/code_new/WhuWheelLeg-main/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
code/inc/FindEndrow.o: code/inc/FindEndrow.src code/inc/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
code/inc/FindMidline.src: ../code/inc/FindMidline.c code/inc/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc26xb "-fE:/zheshiche/code_new/WhuWheelLeg-main/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
code/inc/FindMidline.o: code/inc/FindMidline.src code/inc/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
code/inc/Servo.src: ../code/inc/Servo.c code/inc/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc26xb "-fE:/zheshiche/code_new/WhuWheelLeg-main/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
code/inc/Servo.o: code/inc/Servo.src code/inc/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-code-2f-inc

clean-code-2f-inc:
	-$(RM) code/inc/FindEndrow.d code/inc/FindEndrow.o code/inc/FindEndrow.src code/inc/FindMidline.d code/inc/FindMidline.o code/inc/FindMidline.src code/inc/Servo.d code/inc/Servo.o code/inc/Servo.src

.PHONY: clean-code-2f-inc

