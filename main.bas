DIM motorONOFF AS BYTE  '存储电机状态
DIM pose AS BYTE
DIM grip_pose AS BYTE

DIM i AS BYTE
DIM j AS BYTE

DIM A AS BYTE
DIM A_old AS BYTE
DIM B AS BYTE

' 倾斜检测用
CONST FB_tilt_AD_port = 2
CONST LR_tilt_AD_port = 3
CONST tilt_time_check = 5
CONST MIN = 61
CONST MAX = 107
CONST COUNT_MAX = 10

' 打开电机控制
PTP SETON
PTP ALLON

' 设置电机方向
' G6B, G6C 为手臂，G6A, G6D 为腿
DIR G6A, 1, 0, 0, 1, 0, 0   'motor # 0~5
DIR G6B, 1, 1, 1, 1, 1, 1   'motor # 6~11
DIR G6C, 0, 0, 0, 0, 0, 0   'motor # 12~17
DIR G6D, 0, 1, 1, 0, 1, 0   'motor # 18~23

' 初始化机器人
GOSUB MOTOR_ON
SPEED 5
GOSUB POWER_FIRST_POSE
GOSUB STAND_POSE

GOTO MAIN

'**********FUNCTION**********

' 设置可用电机
MOTOR_ON:
    GOSUB MOTOR_GET

    MOTOR G6B
    DELAY 50
    MOTOR G6C
    DELAY 50
    MOTOR G6A
    DELAY 50
    MOTOR G6D

    motorONOFF = 0

    RETURN

' 读取电机状态
MOTOR_GET:
    GETMOTORSET G6A, 1, 1, 1, 1, 1, 0
    GETMOTORSET G6B, 1, 1, 1, 0, 0, 0
    GETMOTORSET G6C, 1, 1, 1, 0, 0, 0
    GETMOTORSET G6D, 1, 1, 1, 1, 1, 0

    RETURN

' 设置机器人上电后的姿势
POWER_FIRST_POSE:
    MOVE G6A, 95, 76, 145, 93, 105, 100
    MOVE G6D, 95, 76, 145, 93, 105, 100
    MOVE G6B, 100, 45, 90, 100, 100, 100
    MOVE G6C, 100, 45, 90, 100, 100, 100
    WAIT

    pose = 0

    RETURN

' 站立姿势
STAND_POSE:
    MOVE G6A, 100, 76, 145, 93, 100, 100
    MOVE G6D, 100, 76, 145, 93, 100, 100
    MOVE G6B, 100, 30, 80, 100, 100, 100
    MOVE G6C, 100, 30, 80, 100, 100, 100
    WAIT

    pose = 0
    grip_pose = 0

    RETURN

' 标准站立姿势
STANDARD_POSE:
    MOVE G6A, 100, 76, 145, 93, 100, 100
    MOVE G6D, 100, 76, 145, 93, 100, 100
    MOVE G6B, 100, 30, 80, 100, 100, 100
    MOVE G6C, 100, 30, 80, 100, 100, 100
    WAIT

    RETURN

' 前后倾斜检查
FB_TILT_CHECK:
    FOR i = 0 TO COUNT_MAX
        A = AD(FB_tilt_AD_port)
        IF A > 250 OR A < 5 THEN RETURN
        IF A > MIN AND A < MAX THEN RETURN
        DELAY tilt_time_check
    NEXT i

    IF A < MIN THEN GOSUB TILT_FRONT
    IF A > MAX THEN GOSUB TILT_BACK

    GOSUB GOSUB_RX_EXIT

    RETURN

' 左右倾斜检查
LR_TILT_CHECK:
    FOR i = 0 TO COUNT_MAX
        B = AD(LR_tilt_AD_port)
        IF B > 250 OR B < 5 THEN RETURN
        IF B > MIN AND B < MAX THEN RETURN
        DELAY tilt_time_check
    NEXT i

    IF B < MIN OR B > MAX THEN
        SPEED 8
        MOVE G6B, 140, 40, 80
        MOVE G6C, 140, 40, 80
        WAIT
        GOSUB STANDARD_POSE
        RETURN

' 前倾处理
TILT_FRONT:
    A = AD(FB_tilt_AD_port)
    IF A < MIN THEN GOSUB BACK_STANDUP
    RETURN

' 后倾处理
TILT_BACK:
    A = AD(FB_tilt_AD_port)
    IF A > MAX THEN GOSUB FRONT_STANDUP
    RETURN

' 后倒自动站立
BACK_STANDUP:
    GOSUB ARM_MOTOR_MODE1
    GOSUB LEG_MOTOR_MODE1

    SPEED 15
    MOVE G6A, 100, 150, 170, 40, 100
    MOVE G6D, 100, 150, 170, 40, 100
    MOVE G6B, 150, 150, 45
    MOVE G6C, 150, 150, 45
    WAIT

    SPEED 15
    MOVE G6A, 100, 155, 110, 120, 100
    MOVE G6D, 100, 155, 110, 120, 100
    MOVE G6B, 190, 80, 15
    MOVE G6C, 190, 80, 15
    WAIT

    GOSUB LEG_MOTOR_MODE2

    SPEED 15
    MOVE G6A, 100, 165, 27, 162, 100
    MOVE G6D, 100, 165, 27, 162, 100
    MOVE G6B, 155, 15, 90
    MOVE G6C, 155, 15, 90
    WAIT

    SPEED 10
    MOVE G6A, 100, 150, 27, 162, 100
    MOVE G6D, 100, 150, 27, 162, 100
    MOVE G6B, 140, 15, 90
    MOVE G6C, 140, 15, 90
    WAIT

    SPEED 6
    MOVE G6A, 100, 138, 27, 155, 100
    MOVE G6D, 100, 138, 27, 155, 100
    MOVE G6B, 113, 30, 80
    MOVE G6C, 113, 30, 80
    WAIT

    DELAY 100
    SPEED 10
    GOSUB STAND_POSE
    GOSUB LEG_MOTOR_MODE1

    RETURN

' 前倒自动站立
FRONT_STANDUP:
    GOSUB ARM_MOTOR_MODE1
    GOSUB LEG_MOTOR_MODE1

    SPEED 15
    MOVE G6A, 100, 15, 70, 140, 100
    MOVE G6D, 100, 15, 70, 140, 100
    MOVE G6B, 20, 140, 15
    MOVE G6C, 20, 140, 15
    WAIT

    SPEED 12
    MOVE G6A, 100, 136, 35, 80, 100
    MOVE G6D, 100, 136, 35, 80, 100
    MOVE G6B, 20, 30, 80
    MOVE G6C, 20, 30, 80
    WAIT

    SPEED 12
    MOVE G6A, 100, 165, 70, 30, 100
    MOVE G6D, 100, 165, 70, 30, 100
    MOVE G6B, 30, 20, 95
    MOVE G6C, 30, 20, 95
    WAIT

    SPEED 10
    MOVE G6A, 100, 167, 45, 90, 100
    MOVE G6D, 100, 167, 45, 90, 100
    MOVE G6B, 130, 50, 60
    MOVE G6C, 130, 50, 60
    WAIT

    SPEED 10
    GOSUB STAND_POSE

    RETURN

' 设置手臂电机为模式 1
ARM_MOTOR_MODE1:
    MOTORMODE G6B, 1, 1, 1
    MOTORMODE G6C, 1, 1, 1
    RETURN

' 设置腿电机为模式 1
LEG_MOTOR_MODE1:
    MOTORMODE G6A, 1, 1, 1, 1, 1
    MOTORMODE G6D, 1, 1, 1, 1, 1
    RETURN

' 设置腿电机为模式 2
LEG_MOTOR_MODE2:
    MOTORMODE G6A, 2, 2, 2, 2, 2
    MOTORMODE G6D, 2, 2, 2, 2, 2
    RETURN

' 串口接收
RX_EXIT:
    ERX 4800, A, MAIN
    GOTO RX_EXIT

GOSUB_RX_EXIT:
    ERX 4800, A, GOSUB_RX_EXIT2
    RETURN

GOSUB_RX_EXIT2:
    RETURN

'**********MAIN**********
MAIN:
    ' 倾斜检测
    GOSUB FB_TILT_CHECK
    GOSUB LR_TILT_CHECK

    ' 接收蓝牙模块数据
    ERX 4800, A, MAIN

    A_old = A

    ' A 值为 0, 1, ... 时跳转到 MAIN, KEY1, ...
    ON A GOTO MAIN, KEY1, KEY2

KEY1:
    GOTO RX_EXIT

KEY2:
    GOTO RX_EXIT
