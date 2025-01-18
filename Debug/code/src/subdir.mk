################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../code/src/Camera.c" \
"../code/src/Filter.c" \
"../code/src/MasterCtrl.c" \
"../code/src/MathLib.c" \
"../code/src/Pid.c" \
"../code/src/ServoMotor.c" \
"../code/src/bldc.c" \
"../code/src/dataProcess.c" \
"../code/src/imu.c" \
"../code/src/key.c" \
"../code/src/leg.c" \
"../code/src/oledDebug.c" \
"../code/src/queue.c" \
"../code/src/robot.c" \
"../code/src/vector.c" 

COMPILED_SRCS += \
"code/src/Camera.src" \
"code/src/Filter.src" \
"code/src/MasterCtrl.src" \
"code/src/MathLib.src" \
"code/src/Pid.src" \
"code/src/ServoMotor.src" \
"code/src/bldc.src" \
"code/src/dataProcess.src" \
"code/src/imu.src" \
"code/src/key.src" \
"code/src/leg.src" \
"code/src/oledDebug.src" \
"code/src/queue.src" \
"code/src/robot.src" \
"code/src/vector.src" 

C_DEPS += \
"./code/src/Camera.d" \
"./code/src/Filter.d" \
"./code/src/MasterCtrl.d" \
"./code/src/MathLib.d" \
"./code/src/Pid.d" \
"./code/src/ServoMotor.d" \
"./code/src/bldc.d" \
"./code/src/dataProcess.d" \
"./code/src/imu.d" \
"./code/src/key.d" \
"./code/src/leg.d" \
"./code/src/oledDebug.d" \
"./code/src/queue.d" \
"./code/src/robot.d" \
"./code/src/vector.d" 

OBJS += \
"code/src/Camera.o" \
"code/src/Filter.o" \
"code/src/MasterCtrl.o" \
"code/src/MathLib.o" \
"code/src/Pid.o" \
"code/src/ServoMotor.o" \
"code/src/bldc.o" \
"code/src/dataProcess.o" \
"code/src/imu.o" \
"code/src/key.o" \
"code/src/leg.o" \
"code/src/oledDebug.o" \
"code/src/queue.o" \
"code/src/robot.o" \
"code/src/vector.o" 


# Each subdirectory must supply rules for building sources it contributes
"code/src/Camera.src":"../code/src/Camera.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/Camera.o":"code/src/Camera.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/src/Filter.src":"../code/src/Filter.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/Filter.o":"code/src/Filter.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/src/MasterCtrl.src":"../code/src/MasterCtrl.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/MasterCtrl.o":"code/src/MasterCtrl.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/src/MathLib.src":"../code/src/MathLib.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/MathLib.o":"code/src/MathLib.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/src/Pid.src":"../code/src/Pid.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/Pid.o":"code/src/Pid.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/src/ServoMotor.src":"../code/src/ServoMotor.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/ServoMotor.o":"code/src/ServoMotor.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/src/bldc.src":"../code/src/bldc.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/bldc.o":"code/src/bldc.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/src/dataProcess.src":"../code/src/dataProcess.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/dataProcess.o":"code/src/dataProcess.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/src/imu.src":"../code/src/imu.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/imu.o":"code/src/imu.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/src/key.src":"../code/src/key.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/key.o":"code/src/key.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/src/leg.src":"../code/src/leg.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/leg.o":"code/src/leg.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/src/oledDebug.src":"../code/src/oledDebug.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/oledDebug.o":"code/src/oledDebug.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/src/queue.src":"../code/src/queue.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/queue.o":"code/src/queue.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/src/robot.src":"../code/src/robot.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/robot.o":"code/src/robot.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/src/vector.src":"../code/src/vector.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/vector.o":"code/src/vector.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-code-2f-src

clean-code-2f-src:
	-$(RM) ./code/src/Camera.d ./code/src/Camera.o ./code/src/Camera.src ./code/src/Filter.d ./code/src/Filter.o ./code/src/Filter.src ./code/src/MasterCtrl.d ./code/src/MasterCtrl.o ./code/src/MasterCtrl.src ./code/src/MathLib.d ./code/src/MathLib.o ./code/src/MathLib.src ./code/src/Pid.d ./code/src/Pid.o ./code/src/Pid.src ./code/src/ServoMotor.d ./code/src/ServoMotor.o ./code/src/ServoMotor.src ./code/src/bldc.d ./code/src/bldc.o ./code/src/bldc.src ./code/src/dataProcess.d ./code/src/dataProcess.o ./code/src/dataProcess.src ./code/src/imu.d ./code/src/imu.o ./code/src/imu.src ./code/src/key.d ./code/src/key.o ./code/src/key.src ./code/src/leg.d ./code/src/leg.o ./code/src/leg.src ./code/src/oledDebug.d ./code/src/oledDebug.o ./code/src/oledDebug.src ./code/src/queue.d ./code/src/queue.o ./code/src/queue.src ./code/src/robot.d ./code/src/robot.o ./code/src/robot.src ./code/src/vector.d ./code/src/vector.o ./code/src/vector.src

.PHONY: clean-code-2f-src

