#ifndef __ROBOT_PROTOCOL_H__
#define __ROBOT_PROTOCOL_H__

#define _PRINT_MSG_  
                    
/*
    robot command code define
*/
#define BOW			1   
#define SIT_DOWN		26  
#define RIGHT_SHOOTING    	2   
#define LEFT_SHOOTING     	6   
#define FWD_SHORT_STEP		11  
#define BWD_SHORT_STEP		12  
#define FWD_RUN           	5   
#define BWD_RUN           	10  
#define LEFT_TURN         	7   
#define RIGHT_TURN		9   
#define GO_LEFT		        14  
#define GO_RIGHT	        13  
#define LEFT_FRONT_SIDE_ATTACK	17  
#define RIGHT_FRONT_SIDE_ATTACK	27  
#define LOSER1	          	3   
#define LOSER2	          	4   
#define LEFT_SIDE_ATTACK	18
#define RIGHT_SIDE_ATTACK	23
#define HEAD_LEFT	        15
#define HEAD_RIGHT	        20  
#define FLAPPING_AND_STANDUP	28  
#define MARK_TIME	        30
#define BACK_LIFT_ATTACK	31
#define ATTENTION_1	        29
#define TUMBLING_FORWARD	25
#define TUMBLING_BACKWARD       19  
#define LEFT_BACK_ATTACK	22
#define RIGHT_BACK_ATTACK	24
#define FRONT_BOTH_SIDE_PUNCH	32
#define MOTION_CAPTURE	        16 
#define CEREMONY	        8 
#define FRONT_LIFT_ATTACK	21
#define FWD_1STEP 		53 
#define BWD_1STEP	 	54
#define SIT_DOWN_1 		55 

/*append option*/
#define HEAD_DORIDORI 47  
#define CTRL_MOTOR  52    // Motor ID + angle(10~190) control

// walking partial posture 
#define WALKING_01  33
#define WALKING_02  34
#define WALKING_03  35
#define WALKING_04  36
#define WALKING_05  37
#define WALKING_06  38
#define WALKING_07  39
#define WALKING_08  40
#define WALKING_09  41
#define WALKING_10  42
#define WALKING_11  43
#define WALKING_12  44
#define WALKING_13  45
#define WALKING_14  46

#define ATTENTION  48     
#define DANCE      49         

#define RIGHT_KICK  50    
#define LEFT_KICK   51     

#define MOTOR0_ANGLE 56
#define MOTOR1_ANGLE 57
#define MOTOR2_ANGLE 58
#define MOTOR3_ANGLE 59
#define MOTOR4_ANGLE 61
#define MOTOR6_ANGLE 62
#define MOTOR7_ANGLE 63
#define MOTOR8_ANGLE 64
#define MOTOR11_ANGLE 65
#define MOTOR12_ANGLE 66
#define MOTOR13_ANGLE 67
#define MOTOR14_ANGLE 68
#define MOTOR18_ANGLE 69
#define MOTOR19_ANGLE 70
#define MOTOR20_ANGLE 71
#define MOTOR21_ANGLE 72
#define MOTOR22_ANGLE 73

void Send_Command(unsigned char command);
int Receive_Command(unsigned char* buff);
unsigned char Receive_Angle(unsigned char command);
unsigned char Receive_All_Angle();


#endif

