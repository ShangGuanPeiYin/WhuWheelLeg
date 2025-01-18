################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../user/cpu0_main.c" \
"../user/cpu1_main.c" \
"../user/isr.c" \
"../user/user.c" 

COMPILED_SRCS += \
"user/cpu0_main.src" \
"user/cpu1_main.src" \
"user/isr.src" \
"user/user.src" 

C_DEPS += \
"./user/cpu0_main.d" \
"./user/cpu1_main.d" \
"./user/isr.d" \
"./user/user.d" 

OBJS += \
"user/cpu0_main.o" \
"user/cpu1_main.o" \
"user/isr.o" \
"user/user.o" 


# Each subdirectory must supply rules for building sources it contributes
"user/cpu0_main.src":"../user/cpu0_main.c" "user/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"user/cpu0_main.o":"user/cpu0_main.src" "user/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"user/cpu1_main.src":"../user/cpu1_main.c" "user/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"user/cpu1_main.o":"user/cpu1_main.src" "user/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"user/isr.src":"../user/isr.c" "user/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"user/isr.o":"user/isr.src" "user/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"user/user.src":"../user/user.c" "user/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"user/user.o":"user/user.src" "user/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-user

clean-user:
	-$(RM) ./user/cpu0_main.d ./user/cpu0_main.o ./user/cpu0_main.src ./user/cpu1_main.d ./user/cpu1_main.o ./user/cpu1_main.src ./user/isr.d ./user/isr.o ./user/isr.src ./user/user.d ./user/user.o ./user/user.src

.PHONY: clean-user

