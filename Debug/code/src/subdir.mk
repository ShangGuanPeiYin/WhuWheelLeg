################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../code/src/BLDC.c" \
"../code/src/Camera.c" \
"../code/src/Filter.c" \
"../code/src/FindBorder.c" \
"../code/src/FindControlRow.c" \
"../code/src/FindEndrow.c" \
"../code/src/FindMidline.c" \
"../code/src/MasterCtrl.c" \
"../code/src/MathLib.c" \
"../code/src/Pid.c" \
"../code/src/Servo.c" \
"../code/src/beiyoucontrol.c" \
"../code/src/beiyoupid.c" \
"../code/src/dataProcess.c" \
"../code/src/imu.c" \
"../code/src/key.c" \
"../code/src/leg.c" \
"../code/src/oledDebug.c" \
"../code/src/queue.c" \
"../code/src/robot.c" \
"../code/src/vector.c" \
"../code/src/vofa.c" 

COMPILED_SRCS += \
"code/src/BLDC.src" \
"code/src/Camera.src" \
"code/src/Filter.src" \
"code/src/FindBorder.src" \
"code/src/FindControlRow.src" \
"code/src/FindEndrow.src" \
"code/src/FindMidline.src" \
"code/src/MasterCtrl.src" \
"code/src/MathLib.src" \
"code/src/Pid.src" \
"code/src/Servo.src" \
"code/src/beiyoucontrol.src" \
"code/src/beiyoupid.src" \
"code/src/dataProcess.src" \
"code/src/imu.src" \
"code/src/key.src" \
"code/src/leg.src" \
"code/src/oledDebug.src" \
"code/src/queue.src" \
"code/src/robot.src" \
"code/src/vector.src" \
"code/src/vofa.src" 

C_DEPS += \
"./code/src/BLDC.d" \
"./code/src/Camera.d" \
"./code/src/Filter.d" \
"./code/src/FindBorder.d" \
"./code/src/FindControlRow.d" \
"./code/src/FindEndrow.d" \
"./code/src/FindMidline.d" \
"./code/src/MasterCtrl.d" \
"./code/src/MathLib.d" \
"./code/src/Pid.d" \
"./code/src/Servo.d" \
"./code/src/beiyoucontrol.d" \
"./code/src/beiyoupid.d" \
"./code/src/dataProcess.d" \
"./code/src/imu.d" \
"./code/src/key.d" \
"./code/src/leg.d" \
"./code/src/oledDebug.d" \
"./code/src/queue.d" \
"./code/src/robot.d" \
"./code/src/vector.d" \
"./code/src/vofa.d" 

OBJS += \
"code/src/BLDC.o" \
"code/src/Camera.o" \
"code/src/Filter.o" \
"code/src/FindBorder.o" \
"code/src/FindControlRow.o" \
"code/src/FindEndrow.o" \
"code/src/FindMidline.o" \
"code/src/MasterCtrl.o" \
"code/src/MathLib.o" \
"code/src/Pid.o" \
"code/src/Servo.o" \
"code/src/beiyoucontrol.o" \
"code/src/beiyoupid.o" \
"code/src/dataProcess.o" \
"code/src/imu.o" \
"code/src/key.o" \
"code/src/leg.o" \
"code/src/oledDebug.o" \
"code/src/queue.o" \
"code/src/robot.o" \
"code/src/vector.o" \
"code/src/vofa.o" 


# Each subdirectory must supply rules for building sources it contributes
"code/src/BLDC.src":"../code/src/BLDC.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/BLDC.o":"code/src/BLDC.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/src/Camera.src":"../code/src/Camera.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/Camera.o":"code/src/Camera.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/src/Filter.src":"../code/src/Filter.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/Filter.o":"code/src/Filter.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/src/FindBorder.src":"../code/src/FindBorder.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/FindBorder.o":"code/src/FindBorder.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/src/FindControlRow.src":"../code/src/FindControlRow.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/FindControlRow.o":"code/src/FindControlRow.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/src/FindEndrow.src":"../code/src/FindEndrow.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/FindEndrow.o":"code/src/FindEndrow.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/src/FindMidline.src":"../code/src/FindMidline.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/FindMidline.o":"code/src/FindMidline.src" "code/src/subdir.mk"
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
"code/src/Servo.src":"../code/src/Servo.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/Servo.o":"code/src/Servo.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/src/beiyoucontrol.src":"../code/src/beiyoucontrol.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/beiyoucontrol.o":"code/src/beiyoucontrol.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/src/beiyoupid.src":"../code/src/beiyoupid.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/beiyoupid.o":"code/src/beiyoupid.src" "code/src/subdir.mk"
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
"code/src/vofa.src":"../code/src/vofa.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/vofa.o":"code/src/vofa.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-code-2f-src

clean-code-2f-src:
	-$(RM) ./code/src/BLDC.d ./code/src/BLDC.o ./code/src/BLDC.src ./code/src/Camera.d ./code/src/Camera.o ./code/src/Camera.src ./code/src/Filter.d ./code/src/Filter.o ./code/src/Filter.src ./code/src/FindBorder.d ./code/src/FindBorder.o ./code/src/FindBorder.src ./code/src/FindControlRow.d ./code/src/FindControlRow.o ./code/src/FindControlRow.src ./code/src/FindEndrow.d ./code/src/FindEndrow.o ./code/src/FindEndrow.src ./code/src/FindMidline.d ./code/src/FindMidline.o ./code/src/FindMidline.src ./code/src/MasterCtrl.d ./code/src/MasterCtrl.o ./code/src/MasterCtrl.src ./code/src/MathLib.d ./code/src/MathLib.o ./code/src/MathLib.src ./code/src/Pid.d ./code/src/Pid.o ./code/src/Pid.src ./code/src/Servo.d ./code/src/Servo.o ./code/src/Servo.src ./code/src/beiyoucontrol.d ./code/src/beiyoucontrol.o ./code/src/beiyoucontrol.src ./code/src/beiyoupid.d ./code/src/beiyoupid.o ./code/src/beiyoupid.src ./code/src/dataProcess.d ./code/src/dataProcess.o ./code/src/dataProcess.src ./code/src/imu.d ./code/src/imu.o ./code/src/imu.src ./code/src/key.d ./code/src/key.o ./code/src/key.src ./code/src/leg.d ./code/src/leg.o ./code/src/leg.src ./code/src/oledDebug.d ./code/src/oledDebug.o ./code/src/oledDebug.src ./code/src/queue.d ./code/src/queue.o ./code/src/queue.src ./code/src/robot.d ./code/src/robot.o ./code/src/robot.src ./code/src/vector.d ./code/src/vector.o ./code/src/vector.src ./code/src/vofa.d ./code/src/vofa.o ./code/src/vofa.src

.PHONY: clean-code-2f-src

