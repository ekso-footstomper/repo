/**
 *  EKSO BIONICS
 *
 *  Copyright 2016, Ekso Bionics, as an unpublished work.
 *  All rights reserved.  This computer software is
 *  PROPRIETARY INFORMATION of Ekso Bionics
 *  and shall not be reproduced, disclosed or used without written
 *  permission of Ekso Bionics.  Multiple Patents Pending.
 *
 */
/**
 *  @file main.h
 *  @brief Main module to control foot test stand and allow for user control through command line input
 *
 *
 *  $Revision: $1.0
 *  $Date: $04/11/2016
 *
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "./BBBIOlib/BBBio_lib/BBBiolib.h"



/**Define all  pin numbers for  Foot Test Stand*/
#define HEADER_P8 8
#define HEADER_P9 9
#define LOAD_CELL_1  0  //AIN_0
#define LOAD_CELL_2  1  //AIN_1
#define SOL_VALVE_1 11  //GPIO 11, P8
#define SOL_VALVE_2 12  //GPIO 12, P8
#define SOL_VALVE_3 15 //GPIO 15, P8
#define PRS_REG_1    0  //PWMSS_0A P9 22
#define PRS_REG_2    1  //PWMSS_0B P9 21
#define RTC_SLC     19  //Real time clock SLC pin
#define RTC_SDA     20  // Real time clock SDA pin
#define HEEL_1_ADC   2  //AIN_2
#define TOE_1_ADC    3  //AIN_3
#define HEEL_2_ADC   4  //AIN_4
#define TOE_2_ADC    5  //AIN_5

/**define Buffer size for ADC*/
#define BUFFER_SIZE 100
#define SAMPLE_SIZE 1

/**PWM defines*/
#define PWM_HZ 500

/**--data logging--*/
#define LOGNAME_SIZE 255
#define LOG_TIMER_MS 12 //[msec]
#define LOGNAME_FORMAT_SAMPLE_A  "../log/FTS_SAMPLE_A_%Y-%m-%d_%H%M%S.log"
#define LOGNAME_FORMAT_SAMPLE_B  "../log/FTS_SAMPLE_B_%Y-%m-%d_%H%M%S.log"

/**Set default settings*/
#define DEFAULT_DES_FORCE 40 //psi
#define DEFAULT_UP_STEP 500 //ms
#define DEFAULT_DOWN_STEP 500 //ms
#define DEFAULT_DES_STEPS 2 //cycles
#define DEFAULT_TURN_PLATES true //default don't turn plates
#define DEFAULT_NUM_SAMPLES 1 //default number of samples

/**Set constants*/
#define LOAD_CELL_CONST 0.0030019 // V/V/#
#define ADC_MAX_V 1.8 //Volts
#define GAIN_LOADCELL 1.757 //gain of op amp
#define V_OUT_MAX 3.3 //volts
#define MAX_PSI 120.0 //PSI
#define MIN_PSI 3.0 //PSI
#define PWM_GAIN 3 //(1 + R2/R1)
#define MAX_V_INPUT_PRESSREG 10 //volts
#define RESOLUTION_ADC 4096 //the counts in 12 bit ADC 0 - 4095
#define X_INTERCEPT 0.029755 //computed from testing load cell and graphing in excel lbs vs output voltage mV
#define Y_INTERCEPT 0.03996 //computed from testing load cell and graphing in excel lbs vs output voltage mV
#define AREA_FOOT_SENSOR 42.09
#define GAIN_TOE_HEEL 2
#define FIVE_V_INPUT 5
#define R2_TOE 322
#define R2_HEEL 2298
#define FOOT_SENSOR_INTERNAL_RES 470
#define MAX_SAMPLE 2 //max number of samples

typedef struct data_t{
	uint16_t sampleNum, currentSubState, nextSubState;
	uint32_t dataCount, lotNum, serialNum;
	float desiredForce, measuredForce, heelVal, toeVal, baseForce;
	bool bLogCreated, bCurrentSensorContact, bNextSensorContact;
	int8_t fileName[LOGNAME_SIZE];
}data_t;

typedef struct test_param_t{
	uint16_t numSAMPLE, command;
	int16_t currentState, nextState, FORCE_PROF;
	uint32_t upStepTime_ms, downStepTime_ms, count, cycle;
	uint64_t stepTime_ms, elapsedTime_ms, currentTime_ms, logTime_ms;
	float desiredForce;
	bool bUpFlag, bDownFlag, bTurnFlag, bCommandFlag, bLogTrue, bCleanTest;
}test_param_t;

typedef struct SPid{
  float dState;		// Last position input
  float pastDTerm;	//last Dterm
  float iState;		// Integrator state
  float iMax, iMin; // Maximum and minimum allowable integrator state
  float	iGain,    	// integral gain
  	  	pGain,    	// proportional gain
        dGain;     	// derivative gain
} SPid;

typedef enum {
	toe,
	heel
}toeHeelID;

typedef enum {
	verticalValve,
	turnValve_A,
	turnValve_B
}valveDefine;

typedef enum {
	sample_A,
	sample_B
}sampleNumber;

typedef enum {
	init,
	downStep,
	upStep,
	hold,
	quit,
	reset
}state;

typedef enum {
	sensorContact,
	noSensorContact
}subState;

void initTest();
void cleanTest();
void initValve();
void openValve(int16_t valveDefine);
void closeValve(int16_t valveDefine);
float getLoadCell(int16_t sampleNum);
void enableLoadCellADC();
void enableFootADC();
void setDesForce(float force);
void turnOffPressureReg();
void initADC();
uint64_t getTimestamp_ms();
void initCLI();
uint64_t elapsedStepTime(test_param_t *pParam);
void logData();
const char * getStateEnum(int16_t state);
float getFootVal(int16_t sampleNum, int toeHeel);


#endif
