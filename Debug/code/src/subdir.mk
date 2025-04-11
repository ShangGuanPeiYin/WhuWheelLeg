################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../code/src/BLDC.c" \
"../code/src/Camera.c" \
"../code/src/CommonFunction.c" \
"../code/src/Correct.c" \
"../code/src/Filter.c" \
"../code/src/FindBorder.c" \
"../code/src/FindControlRow.c" \
"../code/src/FindEndrow.c" \
"../code/src/FindMidLine.c" \
"../code/src/GetDistance.c" \
"../code/src/GetSlope.c" \
"../code/src/GetVariance.c" \
"../code/src/JudgeCross.c" \
"../code/src/JudgeRamp.c" \
"../code/src/JudgeRoadBarrier.c" \
"../code/src/JudgeRoundabout.c" \
"../code/src/JudgeSnakeBending.c" \
"../code/src/JudgeStartLine.c" \
"../code/src/MasterCtrl.c" \
"../code/src/MathLib.c" \
"../code/src/Pid.c" \
"../code/src/RoadJudge.c" \
"../code/src/SeekFree.c" \
"../code/src/Servo.c" \
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
"code/src/CommonFunction.src" \
"code/src/Correct.src" \
"code/src/Filter.src" \
"code/src/FindBorder.src" \
"code/src/FindControlRow.src" \
"code/src/FindEndrow.src" \
"code/src/FindMidLine.src" \
"code/src/GetDistance.src" \
"code/src/GetSlope.src" \
"code/src/GetVariance.src" \
"code/src/JudgeCross.src" \
"code/src/JudgeRamp.src" \
"code/src/JudgeRoadBarrier.src" \
"code/src/JudgeRoundabout.src" \
"code/src/JudgeSnakeBending.src" \
"code/src/JudgeStartLine.src" \
"code/src/MasterCtrl.src" \
"code/src/MathLib.src" \
"code/src/Pid.src" \
"code/src/RoadJudge.src" \
"code/src/SeekFree.src" \
"code/src/Servo.src" \
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
"./code/src/CommonFunction.d" \
"./code/src/Correct.d" \
"./code/src/Filter.d" \
"./code/src/FindBorder.d" \
"./code/src/FindControlRow.d" \
"./code/src/FindEndrow.d" \
"./code/src/FindMidLine.d" \
"./code/src/GetDistance.d" \
"./code/src/GetSlope.d" \
"./code/src/GetVariance.d" \
"./code/src/JudgeCross.d" \
"./code/src/JudgeRamp.d" \
"./code/src/JudgeRoadBarrier.d" \
"./code/src/JudgeRoundabout.d" \
"./code/src/JudgeSnakeBending.d" \
"./code/src/JudgeStartLine.d" \
"./code/src/MasterCtrl.d" \
"./code/src/MathLib.d" \
"./code/src/Pid.d" \
"./code/src/RoadJudge.d" \
"./code/src/SeekFree.d" \
"./code/src/Servo.d" \
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
"code/src/CommonFunction.o" \
"code/src/Correct.o" \
"code/src/Filter.o" \
"code/src/FindBorder.o" \
"code/src/FindControlRow.o" \
"code/src/FindEndrow.o" \
"code/src/FindMidLine.o" \
"code/src/GetDistance.o" \
"code/src/GetSlope.o" \
"code/src/GetVariance.o" \
"code/src/JudgeCross.o" \
"code/src/JudgeRamp.o" \
"code/src/JudgeRoadBarrier.o" \
"code/src/JudgeRoundabout.o" \
"code/src/JudgeSnakeBending.o" \
"code/src/JudgeStartLine.o" \
"code/src/MasterCtrl.o" \
"code/src/MathLib.o" \
"code/src/Pid.o" \
"code/src/RoadJudge.o" \
"code/src/SeekFree.o" \
"code/src/Servo.o" \
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
"code/src/CommonFunction.src":"../code/src/CommonFunction.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/CommonFunction.o":"code/src/CommonFunction.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/src/Correct.src":"../code/src/Correct.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/Correct.o":"code/src/Correct.src" "code/src/subdir.mk"
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
"code/src/FindMidLine.src":"../code/src/FindMidLine.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/FindMidLine.o":"code/src/FindMidLine.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/src/GetDistance.src":"../code/src/GetDistance.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/GetDistance.o":"code/src/GetDistance.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/src/GetSlope.src":"../code/src/GetSlope.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/GetSlope.o":"code/src/GetSlope.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/src/GetVariance.src":"../code/src/GetVariance.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/GetVariance.o":"code/src/GetVariance.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/src/JudgeCross.src":"../code/src/JudgeCross.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/JudgeCross.o":"code/src/JudgeCross.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/src/JudgeRamp.src":"../code/src/JudgeRamp.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/JudgeRamp.o":"code/src/JudgeRamp.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/src/JudgeRoadBarrier.src":"../code/src/JudgeRoadBarrier.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/JudgeRoadBarrier.o":"code/src/JudgeRoadBarrier.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/src/JudgeRoundabout.src":"../code/src/JudgeRoundabout.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/JudgeRoundabout.o":"code/src/JudgeRoundabout.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/src/JudgeSnakeBending.src":"../code/src/JudgeSnakeBending.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/JudgeSnakeBending.o":"code/src/JudgeSnakeBending.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/src/JudgeStartLine.src":"../code/src/JudgeStartLine.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/JudgeStartLine.o":"code/src/JudgeStartLine.src" "code/src/subdir.mk"
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
"code/src/RoadJudge.src":"../code/src/RoadJudge.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/RoadJudge.o":"code/src/RoadJudge.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/src/SeekFree.src":"../code/src/SeekFree.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/SeekFree.o":"code/src/SeekFree.src" "code/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/src/Servo.src":"../code/src/Servo.c" "code/src/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/files/Desktop/Car/ADS_Workspace/WheelLeg/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/src/Servo.o":"code/src/Servo.src" "code/src/subdir.mk"
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
	-$(RM) ./code/src/BLDC.d ./code/src/BLDC.o ./code/src/BLDC.src ./code/src/Camera.d ./code/src/Camera.o ./code/src/Camera.src ./code/src/CommonFunction.d ./code/src/CommonFunction.o ./code/src/CommonFunction.src ./code/src/Correct.d ./code/src/Correct.o ./code/src/Correct.src ./code/src/Filter.d ./code/src/Filter.o ./code/src/Filter.src ./code/src/FindBorder.d ./code/src/FindBorder.o ./code/src/FindBorder.src ./code/src/FindControlRow.d ./code/src/FindControlRow.o ./code/src/FindControlRow.src ./code/src/FindEndrow.d ./code/src/FindEndrow.o ./code/src/FindEndrow.src ./code/src/FindMidLine.d ./code/src/FindMidLine.o ./code/src/FindMidLine.src ./code/src/GetDistance.d ./code/src/GetDistance.o ./code/src/GetDistance.src ./code/src/GetSlope.d ./code/src/GetSlope.o ./code/src/GetSlope.src ./code/src/GetVariance.d ./code/src/GetVariance.o ./code/src/GetVariance.src ./code/src/JudgeCross.d ./code/src/JudgeCross.o ./code/src/JudgeCross.src ./code/src/JudgeRamp.d ./code/src/JudgeRamp.o ./code/src/JudgeRamp.src ./code/src/JudgeRoadBarrier.d ./code/src/JudgeRoadBarrier.o ./code/src/JudgeRoadBarrier.src ./code/src/JudgeRoundabout.d ./code/src/JudgeRoundabout.o ./code/src/JudgeRoundabout.src ./code/src/JudgeSnakeBending.d ./code/src/JudgeSnakeBending.o ./code/src/JudgeSnakeBending.src ./code/src/JudgeStartLine.d ./code/src/JudgeStartLine.o ./code/src/JudgeStartLine.src ./code/src/MasterCtrl.d ./code/src/MasterCtrl.o ./code/src/MasterCtrl.src ./code/src/MathLib.d ./code/src/MathLib.o ./code/src/MathLib.src ./code/src/Pid.d ./code/src/Pid.o ./code/src/Pid.src ./code/src/RoadJudge.d ./code/src/RoadJudge.o ./code/src/RoadJudge.src ./code/src/SeekFree.d ./code/src/SeekFree.o ./code/src/SeekFree.src ./code/src/Servo.d ./code/src/Servo.o ./code/src/Servo.src ./code/src/dataProcess.d ./code/src/dataProcess.o ./code/src/dataProcess.src ./code/src/imu.d ./code/src/imu.o ./code/src/imu.src ./code/src/key.d ./code/src/key.o ./code/src/key.src ./code/src/leg.d ./code/src/leg.o ./code/src/leg.src ./code/src/oledDebug.d ./code/src/oledDebug.o ./code/src/oledDebug.src ./code/src/queue.d ./code/src/queue.o ./code/src/queue.src ./code/src/robot.d ./code/src/robot.o ./code/src/robot.src ./code/src/vector.d ./code/src/vector.o ./code/src/vector.src ./code/src/vofa.d ./code/src/vofa.o ./code/src/vofa.src

.PHONY: clean-code-2f-src

