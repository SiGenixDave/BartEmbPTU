/*******************************************************************************
** .b
**  Copyright (c) 1990-1995,1999,2000,2001,2002 
**                Bombardier Transportation (Holdings) Inc.
********************************************************************************
**  Project    : DFW Propulsion
**  File Name  : ptudfqa.c
**  Subsystem  : PTU
**  Procedures :
**               SetupStreamDump
**               LoadFaultHeaderWithoutTime
**               LoadFaultHeader
**               StartScheduling
**               StopScheduling
**               ChangeChartVariable
**                               printf
**               Start_self_test_task_req
**               Self_test_cmd_req
**               Get_self_test_packet_req
**               Exit_self_test_task_req
**               GetCarID
**               SetCarID
**               SerialInterruptHandler
**               SendEndOfInterrupt
**               start_cbram_write
**               end_cbram_write
**               InitializeChartRecorder
**               InitialiseSerialPortPointers
**               InitialiseSCC
**               GetSwVersion
**               GetVersionString
**
**  Abstract   : This file contains the job specific PTU functions.
**  Compiler   : iC-86
**
**  EPROM Drawing:
** .b
********************************************************************************
** History:
**
** 25 Apr 95 Ajay Mishra
**    Created source file
**
** Revision :
** 17 Nov 1999 S.Taher @ ADtranz
**    Made the following modifications which moving the fault and data logs to
**    BBRAM :
**    1. Made modification to SetCarID and GetCarId. See function header for
**       details.
**    2. Deleted the external declarations for cc_faultlog, cc_datalog and
**       bat_ram_area.
**    3. Changed the pointers of the fault log and the data log in the
**       InitialiseFaultPointers to point to the BBRAM.
**    4. Moved the Chart_Rec_Service routine to ptuchart.c
** 27 Jan 2000  Sajan Joseph @ ADtranz Pittsburgh.
**    Added include of macros.h. Updated the following functions: 
**    Start_self_test_task_req(), Exit_self_test_task_req(),
**    Self_test_cmd_req(), and Get_self_test_packet_req().
** 02 Feb 2000 S.Taher @ ADtranz
**    Made changes to LoadFaultHeader. See function header for details.
** 07 Jun 2000 D.schnewlin @ Adtranz
**    Added new function LoadFaultHeaderWithoutTime.
**  08 Aug 2001 Becki Cirinelli @ Bombardier Transportation
**	   Removed job specific information from LoadFaultHeaderWithoutTime.
**	   Pittsburgh information will have to be added 
**  30 Jan 2002 Becki Cirinelli @ Bombardier Transportation
**     Modified Read_clock function to pass PTU_TIME parameter
**     in the GetTimeDate() function and LoadFaultHeader() function
**  4 April 2002 R.Cirinelli @ Bombardier 
**    Added Scale_Fixed_Channel_Chart_Rec() function to scale outputs
**    Added Zero_Fixed_Channel_Chart_Rec() function to zero outputs
**    Added Ramp_Fixed_Channel_Chart_Rec() function to ramp outputs 
**    Added Full_Fixed_Channel_Chart_Rec() function to set outputs to 4095 
**  08 Oct 2002 Sarfaraz Taher
**    Created for DFW TCC SW from Pittsburgh LRV.Commented the self-test
**    related functionaliyty. Will be enabled when the self-test functionality
**    is integrated. 
**  12 Nov 2002 Sarfaraz Taher
**    Added the GetSwVersion routine in other that the version.h file could 
**    be located along with the project specific files. PTU version.h filename
**    conflicts with the CSS version.h filename and hence requires this change.
**  14 April 2003 Rebecca Cirinelli
**    Added the setnvCarId, setnvFlag, and getnvCarId to interface with the 
**    cpp code generated by Rhapsody to retreive information from BBRAM
**  20 March 2008 Erik Holm
**    Removed #define __INCvxTypesh to permit compilation with
**    CSS API NVRAM functions.
*******************************************************************************/
/*  Grab all of the compiler #pragma's.                                     */
#ifdef __cplusplus
extern "C" {
#endif


/* Project specific information */
#ifndef TEST_ON_PC
#include "rts_api.h"
#endif

#include "ptuprj.h"

#include "fltinfo.h"
#include "ptu.h"
#include "batram.h"

#include "version.h"

#ifndef TEST_ON_PC
#include "io_def.h"
#include "ioclock.h"
#include "st_def.h"
#include "st_var.h"
#endif

/* externs */
extern void setnvCarId(INT_8 *pCar);
extern void setnvFlag(INT_8 aFlag);
extern void getnvCarId(INT_8 *pCar);
extern UINT_16 getTachZeroSpeed();

/* None */

const UINT_16 ChartRecorderVar[MAX_CR_TBL_ENTRIES] =
{
	0,0,0,0,0,0,0,0
};

/************************************************************************
*
* .b
*
*   Procedure Name : SetupStreamDump
*
*   Abstract :
*
*   Inputs :
*       Global :    None
*
*       Constants :
*               TRUE
*
*       Parameters :
*               passedqueue struct faultlogqueue_t *
*                       pointer to the fault log
*                       structure to be initialized
*
*   Outputs :
*       Global :    None
*
*       Parameters :
*
*       Returned :  None
*
*   Functional Description :
*
* .b
*
*   History :       04/05/95    D. Pradhan  Creation
*   Revised :
*
*************************************************************************/
UINT_8 SetupStreamDump(struct faultlogqueue_t   *passedqueue)
{
	UINT_8 ReturnValue = FALSE;

	/* LOOP ONCE ... EXIT ON ERROR */
	do
	{
	  /* set up any data log triggers */

	} while(FALSE);

	return ReturnValue;
}


/************************************************************************
*
* .b
*
*   Procedure Name : LoadFaultHeaderWithoutTime
*
*   Abstract :
*
*   Inputs :
*       Global :
*
*       Constants :
*               SELFTESTFAULT
*
*       Parameters :
*               passedfault struct minfaultpacket_t *
*                       pointer to the fault that is to
*                       be logged
*
*   Outputs :
*       Global :    None
*
*       Parameters :
*               passedfault has updated header info
*
*       Returned :  None
*
*   Functional Description :
*     Set up global fault info but not the date time stamp.
*
*
* .b
*
*   History :   04/05/95    D. Pradhan  Creation
*   Revised :
*	 02 Feb 2000 S.Taher @ ADtranz
*      Made WMATA specific fault header changes.
*    07 Jun 2000 D.schnewlin @ Adtranz
*      Derived from function LoadFaultHeader.
*	 08 Aug 2001 Becki Cirinelli @ Bombardier Transportation
*	   Removed job specific information from file.  Pittsburgh
*	   information will have to be added 
*************************************************************************/
void LoadFaultHeaderWithoutTime(struct minfaultpacket_t *passedfault)
{
#if 0
  /* Store the odometer value */
  passedfault->odometer= bat_ram_area->non_constant_area.odometer_mileage;

  /* Store the master controller mode request during the fault */
  passedfault->operator_request = 0;

  /* Store the car speed during the fault */
  passedfault->vehicle_speed    = 0;
#endif
}


/************************************************************************
*
* .b
*
*   Procedure Name : LoadFaultHeader
*
*   Abstract :
*
*   Inputs :
*       Global :
*
*       Constants :
*               SELFTESTFAULT
*
*       Parameters :
*               passedfault struct minfaultpacket_t *
*                       pointer to the fault that is to
*                       be logged
*
*   Outputs :
*       Global :    None
*
*       Parameters :
*               passedfault has updated header info
*
*       Returned :  None
*
*   Functional Description :
*     Set up the date time stamp and other global fault info.
*
*
* .b
*
*   History :   04/05/95    D. Pradhan  Creation
*   Revised :
*	 02 Feb 2000 S.Taher @ ADtranz
*      Made WMATA specific fault header changes.
*    07 Jun 2000 D.schnewlin @ Adtranz
*      Other global fault info are now set by new function
*      LoadFaultHeaderWithoutTime.
*************************************************************************/
void LoadFaultHeader(struct minfaultpacket_t *passedfault)
{
#ifndef TEST_ON_PC
  /* Store the time of the fault */
  Read_clock((struct date_time_type *)(&passedfault->TimeStamp), PTU_TIME);
#endif
  /* Store the odometer value */
  LoadFaultHeaderWithoutTime(passedfault);
}


/************************************************************************
*
* .b
*
*   Procedure Name : StartScheduling
*
*   Abstract :
*
*   Inputs :
*       Global :        None
*
*       Constants :     None
*
*       Parameters :    None
*
*   Outputs :
*       Global :        None
*
*       Parameters :    None
*
*       Returned :      None
*
*   Functional Description :
*
* .b
*
*   History :       04/11/95    D. Pradhan  Creation
*   Revised :
*
*************************************************************************/
void StartScheduling(void)
{
 /*
  * Put start scheduling here
  */

}


/************************************************************************
*
* .b
*
*   Procedure Name : StopScheduling
*
*   Abstract :
*
*   Inputs :
*       Global :        None
*
*       Constants :     None
*
*       Parameters :    None
*
*   Outputs :
*       Global :        None
*
*       Parameters :    None
*
*       Returned :      None
*
*   Functional Description :
*
* .b
*
*   History :       04/11/95    D. Pradhan  Creation
*   Revised :
*
*************************************************************************/
void StopScheduling(void)
{
 /*
  * Put start scheduling here
  */
}


/************************************************************************
*
* .b
*
*   Procedure Name : ChangeChartVariable
*
*   Abstract :
*
*   Inputs :
*       Global :        None
*
*       Constants :     None
*
*       Parameters :    None
*
*   Outputs :
*       Global :        None
*
*       Parameters :    None
*
*       Returned :      None
*
*   Functional Description :
*
* .b
*
*   History :       04/11/95    D. Pradhan  Creation
*   Revised :
*
*************************************************************************/
void ChangeChartVariable(UINT_16 ChartIndex, UINT_16 VariableIndex)
{
	GlobalPTUData.ChartRecorderElement[ChartIndex] = VariableIndex;
}


/****************************************************************************
*
* .b
*   Procedure Name: Start_self_test_task_req
*
*   Abstract:
*
*   INPUTS:
*
*       Globals:
*           None
*
*       Constants:
*           None
*
*       Procedure Parameters:
*
*   OUTPUTS
*
*       Globals:
*           None
*
*       Returned Values:
*
*   Functional Description:
* .b
*
*   History:        
*   05/04/95    Creation of Version 1.0             ddp
*
*   Revisions: 
*   07/12/2001  2.0   S.Taher - Created for Pittsburgh
* 
*****************************************************************************/
void Start_self_test_task_req(void)
{   
#ifndef TEST_ON_PC
  // Commented out to wait for integration with self-test
   struct st_cmd_str SelfTestCommand;
   struct st_resp_str init_response;
 
   if ( getTachZeroSpeed() != TRUE)
   {
 	/* Speed or Power Request is present */
 	init_response.msg_mode = ST_MSG_MODE_SPECIAL;
 	init_response.test_id = ST_SPECIAL_NO_ENTER;
 	init_response.result.type1.test_case = 1;
 	init_response.result.type1.num_of_vars = 0;
 	init_response.flags = 0;
 	init_response.set_info = 0;
 	init_response.result.type1.version = 0;
    Write_st_resp_buf((UINT_8 *) &init_response);
   }
   else
   {
	/* Send a message to the PTU accepting the request */
  	SelfTestCommand.id       = ST_CMD_ENTER_ST;
  	SelfTestCommand.xy_info = 0;
  	SelfTestCommand.data     = 0;

  	Write_st_cmd_buf((UINT_8 *) &SelfTestCommand, (UINT_16) sizeof(SelfTestCommand));
   }
#endif
}   /* end func Start_self_test_task_req */

/****************************************************************************
*
* .b
*   Procedure Name: Exit_self_test_task_req
*
*   Abstract:
*
*   INPUTS:
*
*       Globals:
*           None
*
*       Constants:
*           None
*
*       Procedure Parameters:
*
*   OUTPUTS
*
*       Globals:
*           None
*
*       Returned Values:
*
*   Functional Description:
* .b
*
*   History:        05/04/95    Creation of Version 2.0             ddp
*   Revision:
*   27 Jan 2000  Sajan Joseph @ ADtranz Pittsburgh.
*     Removed #if's.
*   07/12/2001  2.0   S.Taher - Created for Pittsburgh
*
*****************************************************************************/
void Exit_self_test_task_req(void)
{ 
#ifndef TEST_ON_PC
  // Commented out - Waiting for self-test integration.
  struct st_cmd_str SelfTestCommand;

  SelfTestCommand.id       = ST_CMD_EXIT_ST;
  SelfTestCommand.xy_info = 0;
  SelfTestCommand.data     = 0;
  Write_st_cmd_buf((UINT_8 *) &SelfTestCommand, (UINT_16) sizeof(SelfTestCommand));
#endif
}   /* end func Exit_self_test_task_req */



/****************************************************************************
*
* .b
*   Procedure Name: Self_test_cmd_req
*
*   Abstract:
*
*   INPUTS:
*
*       Globals:
*           None
*
*       Constants:
*           None
*
*       Procedure Parameters:
*
*   OUTPUTS
*
*       Globals:
*           None
*
*       Returned Values:
*
*   Functional Description:
* .b
*
*   History:        05/04/95    Creation of Version 2.0             ddp
*   Revision:
*   27 Jan 2000  Sajan Joseph @ ADtranz Pittsburgh.
*     Removed #if's.
*   07/12/2001  2.0   S.Taher - Created for Pittsburgh
*****************************************************************************/
void Self_test_cmd_req(Header_t *PassedRequest)
{
#ifndef TEST_ON_PC
  // Commented out to wait for integration with self-test
  UINT_16 length;

  length = PassedRequest->PacketLength - sizeof(Header_t);
  Write_st_cmd_buf(
    (UINT_8 *) &(((SelfTestCommandReq_t *) PassedRequest)->id), length);
#endif
}   /* end func Self_test_cmd_req */


/****************************************************************************
*
* .b
*   Procedure Name: Get_self_test_packet_req
*
*   Abstract:
*
*   INPUTS:
*
*       Globals:
*           None
*
*       Constants:
*           None
*
*       Procedure Parameters:
*
*   OUTPUTS
*
*       Globals:
*           None
*
*       Returned Values:
*
*   Functional Description:
* .b
*
*   History:        05/04/95    Creation of Version 2.0             ddp
*   Revision:
*   27 Jan 2000  Sajan Joseph @ ADtranz Pittsburgh.
*     Removed #if's.
*   07/12/2001  2.0   S.Taher - Created for Pittsburgh
*****************************************************************************/
void Get_self_test_packet_req(MaxResponse_t DATAFARTYPE *Response)
{
#ifndef TEST_ON_PC
  // Commented out - waiting to add the self test functionality
  UINT_16 MessageLength;
  UINT_16 MsgAvailable;

  MsgAvailable = Read_st_resp_buf((UINT_8 *)
                     &((GetSelfTestPacketRes_t *)Response)->Valid,
                     &MessageLength);
  if (MsgAvailable == TRUE)
  { /* there is a message present : send it to the PTU */
    ((GetSelfTestPacketRes_t *)Response)->Valid = TRUE;
    TransmitMessage( (Header_t *)Response,
	     (UINT_16)(MessageLength + sizeof(Header_t)) );
  }
  else
  {
    ((GetSelfTestPacketRes_t *)Response)->Valid = FALSE;
    TransmitMessage( (Header_t *)Response,
	     (UINT_16)(2 + sizeof(Header_t)) );
  }
#endif
}   /* end func Get_self_test_packet_req */


/****************************************************************************
*
* .b
*   Procedure Name: GetCarID
*
*   Abstract:
*
*   INPUTS:
*
*       Globals:
*           None
*
*       Constants:
*           None
*
*       Procedure Parameters:
*
*   OUTPUTS
*
*       Globals:
*           None
*
*       Returned Values:
*
*   Functional Description:
* .b
*
*   History:        05/04/95    Creation of Version 2.0             ddp
*
*   Revised:        01/03/2000  S.Taher @ ADtranz
*                   Changed the battery RAM variable to a pointer variable.
*					04/14/2003  R.Cirinelli @ Bombardier Transportation
*                   Change function so that information for CarId is 
*                   obtained by calling a cpp interface function.  This is 
*                   necessary because constant bbram has been movied to
*                   rhapsody.
*
*****************************************************************************/
void GetCarID(char *CarID)
{
#ifndef TEST_ON_PC
	getnvCarId((INT_8 *)CarID);
#endif
}

/****************************************************************************
*
* .b
*   Procedure Name: SetCarID
*
*   Abstract:
*
*   INPUTS:
*
*       Globals:
*           None
*
*       Constants:
*           None
*
*       Procedure Parameters:
*
*   OUTPUTS
*
*       Globals:
*           None
*
*       Returned Values:
*
*   Functional Description:
* .b
*
*   History:        05/04/95    Creation of Version 2.0             ddp
*
*   Revised:        01/03/2000  S.Taher @ ADtranz
*                   Changed code to set the car-id to the PTU copy of the
*                   constant battery RAM area and then change the state of the
*                   constant battery RAM update state machine.
*                   04/15/2003 R.Cirinelli @ Bombardier Transportation
*					Change function so that information for CarId is 
*                   sent to a cpp interface function.  This is 
*                   necessary because constant bbram has been moved to
*                   rhapsody.
*******************************************************************************/
void SetCarID( char *CarID )
{
#ifndef TEST_ON_PC
	if ( getTachZeroSpeed() == TRUE)
	{
 		/* Speed or Power Request is not present */
		setnvCarId((INT_8 *)CarID);
		setnvFlag(1);
	}
#endif
}




/****************************************************************************
*
* .b
*   Procedure Name:   SendEndOfInterrupt
*
*   Abstract:
*
*   INPUTS:
*
*       Globals:
*
*       Constants:
*
*       Procedure Parameters:
*
*   OUTPUTS
*
*       Globals:
*
*       Returned Values:
*
*   Functional Description:
*
* .b
*
*   History:    05/10/95 ddp @ ATSI -   Created
*
*****************************************************************************/
void SendEndOfInterrupt(void)
{
/*  Re-enable interrupt on the SCC.                   tbd .. JVL 10/24/95   */
}

/****************************************************************************
*
* .b
*   Procedure Name: start_cbram_write
*
*   Abstract:
*
*   INPUTS:
*
*       Globals:
*
*       Constants:
*
*       Procedure Parameters:
*
*   OUTPUTS
*
*       Globals:
*
*       Returned Values:
*
*   Functional Description:
*
* .b
*
*   History:    05/10/95 ddp @ ATSI -   Created
*
*****************************************************************************/
void start_cbram_write(void)
{
}


/****************************************************************************
*
* .b
*   Procedure Name: end_cbram_write
*
*   Abstract:
*
*   INPUTS:
*
*       Globals:
*
*       Constants:
*
*       Procedure Parameters:
*
*   OUTPUTS
*
*       Globals:
*
*       Returned Values:
*
*   Functional Description:
*
* .b
*
*   History:    05/10/95 ddp @ ATSI -   Created
*
*****************************************************************************/
void end_cbram_write(void)
{
}



/****************************************************************************
*
* .b
*   Procedure Name:   InitializeChartRecorder
*
*   Abstract:
*       Initializes which Variables get sent to the Chart Recorder.
*
*   INPUTS:
*
*       Globals:
*
*       Constants:
*
*       Procedure Parameters:
*
*   OUTPUTS
*
*       Globals:
*               GlobalPTUData
*
*       Returned Values: None
*
*   Functional Description:
*
* .b
*
*   History:    07/10/95 ddp @ ATSI -   Created
*
*****************************************************************************/
void InitializeChartRecorder(void)
{
/*  Declare all local variables.                                            */
	INT_16  Index;

/*  Initialize the Watch Window and Chart Recorder table.                   */
	for (Index = 0; Index < MAX_CR_TBL_ENTRIES; Index++)
	{
/*  Set the Chart Recorder Channel.                                         */
		GlobalPTUData.ChartRecorderElement[Index] = ChartRecorderVar[Index];
	}

}


/****************************************************************************
*
* .b
*   Procedure Name:   InitialiseSerialPortPointers
*
*   Abstract:
*       Initializes an array of pointers to the Serial Channel Port.
*
*   INPUTS:
*
*       Globals:
*
*       Constants:
*
*       Procedure Parameters:
*
*   OUTPUTS
*
*       Globals:
*
*       Returned Values: None
*
*   Functional Description:
*
* .b
*
*   History:    10/24/95 ddp @ ATSI -   Created
*
*****************************************************************************/
void InitialiseSerialPortPointers(void)
{

}


/****************************************************************************
*
* .b
*   Procedure Name:   InitialiseSCC
*
*   Abstract:
*       Initializes the Serial for Interrupts.
*
*   INPUTS:
*
*       Globals:
*
*       Constants:
*
*       Procedure Parameters:
*
*   OUTPUTS
*
*       Globals:
*
*       Returned Values: None
*
*   Functional Description:
*
* .b
*
*   History:    10/24/95 ddp @ ATSI -   Created
*
*****************************************************************************/
void InitialiseSCC(void)
{

}


/*
 * This function should be replaced by verify_bat_ram_area()
 */

void  InitializeBatRAMArea(void)
{

  //bat_ram_area->constant_area =  default_const_bat_ram_area;
}



void GetTimeDate(MaxResponse_t DATAFARTYPE *Response)
{

#ifndef TEST_ON_PC
	struct date_time_type   TimeStruct;

	Read_clock(&TimeStruct, PTU_TIME);

	((GetTimeDateRes_t *)Response)->Hour   = TimeStruct.hr;
	((GetTimeDateRes_t *)Response)->Minute = TimeStruct.min;
	((GetTimeDateRes_t *)Response)->Second = TimeStruct.sec;
	((GetTimeDateRes_t *)Response)->Year   = TimeStruct.year;
	((GetTimeDateRes_t *)Response)->Month  = TimeStruct.month;
	((GetTimeDateRes_t *)Response)->Day    = TimeStruct.day;
#endif

}

void SetTimeDate(MaxRequest_t DATAFARTYPE *PassedRequest)
{

#ifndef TEST_ON_PC
	struct date_time_type   TimeStruct;

	TimeStruct.hr       = ((SetTimeDateReq_t *)PassedRequest)->Hour;
	TimeStruct.min      = ((SetTimeDateReq_t *)PassedRequest)->Minute;
	TimeStruct.sec      = ((SetTimeDateReq_t *)PassedRequest)->Second;
	TimeStruct.year     = ((SetTimeDateReq_t *)PassedRequest)->Year;
	TimeStruct.month    = ((SetTimeDateReq_t *)PassedRequest)->Month;
	TimeStruct.day      = ((SetTimeDateReq_t *)PassedRequest)->Day;
	Set_clock(&TimeStruct);
#endif
}

void StartRTC()
{
}

void StopRTC()
{
/***** TEMPFIX *****
* Function body removed to compile the system
*/
#if 0
	Stop_clock();
#endif
}


/************************************************************************
*
* .b
*
*   Procedure Name :    InitialiseFaultPointers
*
*   Abstract :
*               Initializes all Globals Event and Data Structure Pointers
*
*   Inputs :
*       Global :    None
*
*       Constants : None
*
*       Parameters : None
*
*   Outputs :
*       Global :
*                   CurrentEventLog
*                   GlobalFaultLog
*                   GlobalDataLog
*
*       Parameters : None
*
*       Returned :  None
*
*   Functional Description :
*
* .b
*
*   History :   08/29/96    D. Pradhan Creation
*   Revised :
*               11/19/1999  S.Taher @ ADtranz
*                           Changed the initialization of the GlobalFaultLog
*                           and GlobalDataLog to point to the BBRAM area.
*
*************************************************************************/
void InitialiseFaultPointers()
{
	CurrentEventLog = 0;
	GlobalFaultLog  = &(bat_ram_area->non_constant_area.cc_faultlog[0]);
	GlobalDataLog   = &(bat_ram_area->non_constant_area.cc_datalog[0]);
}

/******************************************************************************
*
* .b
*
*
*Procedure Name:Scale_Fixed_Channel_Chart_Rec
*
*
*Abstract:      
*This function scales the 8 constant chart recorder outputs to 12 LSBs
*
*
*INPUTS:
*
*Globals:
*
*
*Procedure Parameters:
*None
*
*
*OUTPUTS:
*
*Globals:   
*io_var.fixed_chart_recorder_channels[0..8]       
*
*
*Return Value:
*None
*
*
*Functional Description:
*This function scales the global variables from either 16 or 32 to 12 bits and 
*makes it an unsigned variable.
*This is accomplished by reading each global variable and plugging it into
*a formula that reduces the resolution and shifts the scale so that the zero 
*value would be at 0x7FF or 2048 if it is signed. If the variable is unsigned, 
*the full scale is used with the zero value starting at 0. 
*The formulas are as follows:
*
* Car Speed:    ((car_speed + CAR_SPEED_OFFSET) * MAX_CHART_BITS) / 
*                             CAR_SPEED_SCALE / SPEED_SCALE_FACTOR
* 
* Rate Request: ((rate_request + RATE_REQUEST_OFFSET) * 
*                    MAX_CHART_BITS) / RATE_REQUEST_SCALE
*                             / RATE_REQUEST_SCALE_FACTOR   
* 
* Tractive Effort: ((tractive_effort_rqstd + TE_RQSTD_OFFSET) * 
*                             MAX_CHART_BITS) / TE_RQSTD_SCALE
* 
* Inv TE Delivered: ((inv_te_dlvrd + TE_DLVRD_OFFSET) * MAX_CHART_BITS) / 
*                             TE_DLVRD_SCALE
*
* Line Voltage:     ((vline + VLINE_OFFSET) * MAX_CHART_BITS) /
*                             VLINE_SCALE / VOLT_SCALE_FACTOR
* 
*   Line Current:     ((iline + ILINE_OFFSET) * MAX_CHART_BITS) /
*                             ILINE_SCALE 
*
* Link Voltage:     ((vlink + VLINK_OFFSET) * MAX_CHART_BITS) /
*                             VLINK_SCALE / VOLT_SCALE_FACTOR
*
*   ICI: Inverter Status:  ((inverter_status + INV_STATUS_OFFSET) * 
*                             MAX_CHART_BITS) / INV_STATUS_SCALE
*
* .b
* History:
* 19 March 2002 RAC
*   Created.              
* Revised:
******************************************************************************/         
void Scale_Fixed_Channel_Chart_Rec(void)
{
#if 0
  /*reads car speed, adds offset to adjust for positive scale, then multiply 
    by the max no. of chart bits.  This value is divided by the speed scale
    to allow the car speed of 0 to 60mph  to span from 0 to 4096 bits.
    This number is also divided by the scale factor to convert the speed 
    from the raw value*/
  io_var.fixed_chart_recorder_channels[FIX_CH1] = 
     ((READ_VEHICLE_SPEED() + CAR_SPEED_OFFSET) * DACSIZE) 
     / CAR_SPEED_SCALE / SPEED_SCALE_FACTOR;    

  /*reads the rate request, adds offset to adjust for positive scale, then 
    multiply by the max no. of chart bits, This value is divided by the rate
    scale to allow the rate request of 0 to 5mph/s to span from 0 to 4096 
    bits.*/
  io_var.fixed_chart_recorder_channels[FIX_CH2] = 
     ((READ_RATE_REQST() + RATE_REQUEST_OFFSET) * DACSIZE) /
     RATE_REQUEST_SCALE / RATE_REQUEST_SCALE_FACTOR;

  /*reads the TE request, adds offset to adjust for positive scale, then 
    multiply by the max no. of chart bits, This value is divided by the TE
    request scale to allow the TE request of -10000 to 10000lbs to span 
    from 0 to 4096 bits.*/
  io_var.fixed_chart_recorder_channels[FIX_CH3] = 
     ((READ_TE_REQUEST(TRK_X) + TE_RQSTD_OFFSET) * DACSIZE) /
     TE_RQSTD_SCALE;

  /*reads the TE delivered, adds offset to adjust for positive scale, then 
    multiply by the max no. of chart bits, This value is divided by the TE
    delivered scale to allow the TE delivered of -10000 to 10000lbs to span 
    from 0 to 4096 bits.*/
  io_var.fixed_chart_recorder_channels[FIX_CH4] = 
     ((READ_TE_DELIVERED_LB() + TE_DLVRD_OFFSET) * DACSIZE) / 
     TE_DLVRD_SCALE;

  /*reads the line voltage, adds offset to adjust for positive scale, then 
    multiply by the max no. of chart bits, This value is divided by the line
    voltage scale to allow line voltage of 0 to 1000v to span 
    from 0 to 4096 bits.  The value is also divided by the volt scale factor
    to convert from the raw value*/
  io_var.fixed_chart_recorder_channels[FIX_CH5] = 
     ((READ_LINE_VOLTAGE() + VLINE_OFFSET) * DACSIZE) /
     VLINE_SCALE; 

  /*reads the line current, adds offset to adjust for positive scale, then 
    multiply by the max no. of chart bits, This value is divided by the line
    current scale to allow line current of -1500 to 1500A to span 
    from 0 to 4096 bits.*/
 io_var.fixed_chart_recorder_channels[FIX_CH6] = 
    ((READ_LINE_CURRENT() + ILINE_OFFSET) * DACSIZE) /
    ILINE_SCALE; 

  /*reads the link voltage, adds offset to adjust for positive scale, then 
    multiply by the max no. of chart bits, This value is divided by the link
    voltage scale to allow link voltage of 0 to 1000v to span 
    from 0 to 4096 bits.  The value is also divided by the volt scale factor
    to convert from the raw value*/
  io_var.fixed_chart_recorder_channels[FIX_CH7] = 
     ((READ_LINK_VOLTAGE() + VLINK_OFFSET) * DACSIZE) /
     VLINK_SCALE / VOLT_SCALE_FACTOR;

  /*reads the inverter status, adds offset to adjust for positive scale, then 
    multiply by the max no. of chart bits, This value is divided by the inv
    status scale to allow an inverter status of 0 to 50 to span 
    from 0 to 4096 bits.*/
  io_var.fixed_chart_recorder_channels[FIX_CH8] = 
   ((READ_INV_STATUS(TRK_X) + INV_STATUS_OFFSET) * DACSIZE) /
   INV_STATUS_SCALE;
#endif
}  
/******************************************************************************
*
* .b
*
*
*Procedure Name:Zero_Fixed_Channel_Chart_Rec
*
*
*Abstract:      
*This function zeros the 8 constant chart recorder outputs 
*
*
*INPUTS:
*
*Globals:
*
*
*Procedure Parameters:
*None
*
*
*OUTPUTS:
*
*Globals:   
*io_var.fixed_chart_recorder_channels[0..8]       
*
*
*Return Value:
*None
*
*
*Functional Description:  see abstract
*
* .b
* History:
* 19 March 2002 RAC
*   Created.              
* Revised:
******************************************************************************/         
void Zero_Fixed_Channel_Chart_Rec(void)
{        
#if 0 
  // Commented out - waiting for functionality to be added
  UINT_16        Index;

  for (Index = 0; Index < NUM_OF_FIXED_CR_CHANNELS; Index++)
  {
    io_var.fixed_chart_recorder_channels[Index] = 0;
  }  
#endif
}
/******************************************************************************
*
* .b
*
*
*Procedure Name:Ramp_Fixed_Channel_Chart_Rec
*
*
*Abstract:      
*This function ramps the 8 constant chart recorder outputs from 0 to 4095 
*
*
*INPUTS:
*
*Globals:
*
*
*Procedure Parameters:
*None
*
*
*OUTPUTS:
*
*Globals:   
*io_var.fixed_chart_recorder_channels[0..8]       
*
*
*Return Value:
*None
*
*
*Functional Description:  see abstract
*
* .b
* History:
* 19 March 2002 RAC
*   Created.              
* Revised:
******************************************************************************/         
void Ramp_Fixed_Channel_Chart_Rec(void)
{ 
#if 0
  // Commented out - waiting for functionality to be added
  UINT_16        Index;
  static UINT_16 RampIndex;

  RampIndex += 5;
  
  for (Index = 0; Index < NUM_OF_FIXED_CR_CHANNELS; Index++)
  {
    io_var.fixed_chart_recorder_channels[Index] = RampIndex;
  }  

  if (RampIndex == 4095)
  {
    RampIndex = 0;
  }
#endif
}
/******************************************************************************
*
* .b
*
*
*Procedure Name:Full_Fixed_Channel_Chart_Rec
*
*
*Abstract:      
*This function sets the 8 constant chart recorder outputs to 4095
*
*
*INPUTS:
*
*Globals:
*
*
*Procedure Parameters:
*None
*
*
*OUTPUTS:
*
*Globals:   
*io_var.fixed_chart_recorder_channels[0..8]       
*
*
*Return Value:
*None
*
*
*Functional Description:  see abstract
*
* .b
* History:
* 19 March 2002 RAC
*   Created.              
* Revised:
******************************************************************************/         
void Full_Fixed_Channel_Chart_Rec(void)
{   
#if 0
  // Commented out - waiting for functionality to be added
  UINT_16        Index;
  
  for (Index = 0; Index < NUM_OF_FIXED_CR_CHANNELS; Index++)
  {
    io_var.fixed_chart_recorder_channels[Index] = 0xfff;
  }  
#endif
}

/******************************************************************************
*
* .b
*
*
*Procedure Name:GetSwVersion
*
*
*Abstract:      
*This function returns the Software Version.
*
*
*INPUTS:
*
*Globals:
*
*
*Procedure Parameters:
*None
*
*
*OUTPUTS:
*
*Globals:   
*None       
*
*
*Return Value:
*UINT_32 (software version)
*
*
*Functional Description:  see abstract
*
* .b
* History:
* 12 Nov 2002 S.Taher.
*   Created.              
* Revised:
******************************************************************************/         
UINT_32 GetSwVersion(void)
{   
	UINT_32 temp_version = SW_VERSION;

	return ( temp_version );
//	return ( SW_VERSION );
}

/******************************************************************************
*
* .b
*
*
*Procedure Name:GetVersionString
*
*
*Abstract:      
*This function returns the pointer to the version string.
*
*
*INPUTS:
*
*Globals:
*
*
*Procedure Parameters:
*None
*
*
*OUTPUTS:
*
*Globals:   
*None       
*
*
*Return Value:
*UINT_32 (software version)
*
*
*Functional Description:  see abstract
*
* .b
* History:
* 12 Nov 2002 S.Taher.
*   Created.              
* Revised:
******************************************************************************/         
UINT_8 sw_versionstring[40]= SW_VERSIONSTRING;

UINT_8* GetVersionString(void)
{ 
  return ( sw_versionstring );
}

#ifdef __cplusplus
}
#endif
