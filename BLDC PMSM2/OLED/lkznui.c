#include "oled.h"
#include "lkznui.h"
#include "stm32f10x_MClib.h"
#include "MC_Globals.h"
extern u8 key_con(void);
u8 keytemp;
u8 screen[3]={0};
u16 speednum=1000,changescrenntime=500,flag3=0;
s16 speedref[2]={1000,0};
//u8 strings[2]={0};
u16  pid[3][3]={0};
u8  pidstat[3]={0};
extern u16 time,time1;
extern u16 h_ADCrEFvolt; 
u8 i,k,j=0,flag,flag1=0,flag2=0;

/*******************************************************************************
* Function Name  : key_con
* Description    : Configures the Motor operation mode
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
u8 key_con(void)
{
	 static u8 key;
	key=0;
	 if(!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0))
	 {
		 key=2;
		 
	 }
	  if(!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13))
	 {
		 key=1;
		 
	 }
	  if(!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_14))
	 {
		 key=3;
		 
	 }
	  if(!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_15))
	 {
		 key=4;
		 
	 }
	  if(!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0))
	 {
		// key=5;
		 
	 }
	 return key;
}
void welcoms(void)
{
	  j=36;
		    k=0;
			 for(i=0;i<=11;i=i+1)
			     {
						  	OLED_ShowCHinese(j,k,i,1);//联 
						    if(j<90)
						      j=j+18;
						   else
							  j=36;  
						     if(i==3|| i==4 || i==5|| i==6 )
							  k= 2;
						 else if(i==7|| i==8 || i==9|| i==10 )
							  k= 4;
						 else
							  k=0;   
					 }
	 speednum =1000; 
					 
					 flag1=1;
}
void lkznui(void)
{
	u16 speedtemp;
  keytemp=key_con();
		if(keytemp==1)
		{
			   OLED_Clear(); 
			    OLED_ShowCHinese(36,0,0,1);
		    	OLED_ShowCHinese(54,0,1,1);
			    OLED_ShowCHinese(72,0,2,1);
		    	OLED_ShowCHinese(90,0,3,1);
			    OLED_ShowCHinese(0,2,18,1);
		    	OLED_ShowCHinese(16,2,19,1);
			    OLED_ShowCHinese(54,2,22,1);
		    	OLED_ShowCHinese(70,2,23,1); 
			    OLED_ShowCHinese(0,4,24,1);
		    	OLED_ShowCHinese(16,4,25,1);
			    OLED_ShowCHinese(54,4,26,1);
		    	OLED_ShowCHinese(70,4,27,1); 
			while(1)
			{
				 switch (State)
    {
      case IDLE:    // Idle state   
      break;
      
      case INIT:
        MCL_Init();
        TB_Set_StartUp_Timeout(3000);//延时1.5S吗
        State = START; 
      break;
        
      case START:  
      //passage to state RUN is performed by startup functions; 
      break;
          
      case RUN:   // motor running       
#ifdef ENCODER
        if(ENC_ErrorOnFeedback() == TRUE)
        {
        MCL_SetFault(SPEED_FEEDBACK);
        }
#elif defined HALL_SENSORS        
        if(HALL_IsTimedOut())
        {
          MCL_SetFault(SPEED_FEEDBACK);
        } 
	//	te=	HALL_GetSpeed();/te/
        if ( HALL_GetSpeed()== HALL_MAX_SPEED)
        {
          MCL_SetFault(SPEED_FEEDBACK);
        } 
#elif defined NO_SPEED_SENSORS
      
#endif     
      break;  
      
      case STOP:    // motor stopped
          // shutdown power         
          /* Main PWM Output Disable */
          TIM_CtrlPWMOutputs(TIM1, DISABLE);
          
          State = WAIT;
          
#ifdef THREE_SHUNT          
          SVPWM_3ShuntAdvCurrentReading(DISABLE);
#endif   
#ifdef SINGLE_SHUNT          
          SVPWM_1ShuntAdvCurrentReading(DISABLE);
#endif
          Stat_Volt_alfa_beta.qV_Component1 = Stat_Volt_alfa_beta.qV_Component2 = 0;
          
#ifdef ICS_SENSORS
          SVPWM_IcsCalcDutyCycles(Stat_Volt_alfa_beta);
#elif defined THREE_SHUNT
          SVPWM_3ShuntCalcDutyCycles(Stat_Volt_alfa_beta);
#endif                                                
          TB_Set_Delay_500us(2000); // 1 sec delay
      break;
      
      case WAIT:    // wait state
          if (TB_Delay_IsElapsed() == TRUE) 
          {
#ifdef ENCODER            
            if(ENC_Get_Mechanical_Speed() ==0)             
            {              
              State = IDLE;              
            }
#elif defined HALL_SENSORS      
            if (HALL_IsTimedOut())
            {               
              State=IDLE;
            } 
#elif defined NO_SPEED_SENSORS
            STO_InitSpeedBuffer();
            State=IDLE; 
#endif            
          }
        break;
    			 
      case FAULT:                   
          if (MCL_ClearFault() == TRUE)
          {
            if((wGlobal_Flags & SPEED_CONTROL) == SPEED_CONTROL)
            {
              bMenu_index = CONTROL_MODE_MENU_1;
            }
            else
            {
              bMenu_index = CONTROL_MODE_MENU_6;
            }       
#if defined NO_SPEED_SENSORS
            STO_InitSpeedBuffer();
#endif            
          State = IDLE;
		     //  State = INIT; 
            wGlobal_Flags |= FIRST_START;
						if(screen[0]==0 && screen[1]==1)
						{
								OLED_ShowCHinese(90,6,28,1);
		    	  OLED_ShowCHinese(106,6,29,1); 
						}
					 
						flag1=1;
          }
		  
        break;
    
      default:        
        break;
    }
				 keytemp=key_con();
				if(time >changescrenntime || keytemp ==0)
				             {
					           flag=0;
										 time=0;
				             }
					OLED_ShowCHinese(36,0,0,1);
		    	OLED_ShowCHinese(54,0,1,1);
			    OLED_ShowCHinese(72,0,2,1);
		    	OLED_ShowCHinese(90,0,3,1);	
				switch(screen[1])
				{
			
					case 0://第一界面
						
					if(keytemp==0)
				    {
					    flag=0;
				    }
		         if(keytemp ==1 && screen[0]<=2 && flag==0)
					{
						 screen[0]++; 
						 flag=1;
					}
						
					else if(keytemp ==2 && screen[0]>=1 && flag==0)
					{
						  screen[0]--;
						  flag=1;
					}
						 switch(screen[0])
					    {
					 case 0:
						 OLED_ShowCHinese(0,2,18,0);
		    	   OLED_ShowCHinese(16,2,19,0); 
					    OLED_ShowCHinese(54,2,22,1);
		    	OLED_ShowCHinese(70,2,23,1); 
			    OLED_ShowCHinese(0,4,24,1);
		    	OLED_ShowCHinese(16,4,25,1);
			    OLED_ShowCHinese(54,4,26,1);
		    	OLED_ShowCHinese(70,4,27,1); 
						 break;
					 case 1:
						 OLED_ShowCHinese(0,2,18,1);
		    	   OLED_ShowCHinese(16,2,19,1); 
					    OLED_ShowCHinese(54,2,22,0);
		    	OLED_ShowCHinese(70,2,23,0); 
			    OLED_ShowCHinese(0,4,24,1);
		    	OLED_ShowCHinese(16,4,25,1);
			    OLED_ShowCHinese(54,4,26,1);
		    	OLED_ShowCHinese(70,4,27,1); 
						 break;
					 case 2:
						 OLED_ShowCHinese(0,2,18,1);
		    	   OLED_ShowCHinese(16,2,19,1); 
					    OLED_ShowCHinese(54,2,22,1);
		    	OLED_ShowCHinese(70,2,23,1); 
			    OLED_ShowCHinese(0,4,24,0);
		    	OLED_ShowCHinese(16,4,25,0);
			    OLED_ShowCHinese(54,4,26,1);
		    	OLED_ShowCHinese(70,4,27,1); 
						 break;
					 case 3:
						 OLED_ShowCHinese(0,2,18,1);
		    	   OLED_ShowCHinese(16,2,19,1); 
					    OLED_ShowCHinese(54,2,22,1);
		    	OLED_ShowCHinese(70,2,23,1); 
			    OLED_ShowCHinese(0,4,24,1);
		    	OLED_ShowCHinese(16,4,25,1);
			    OLED_ShowCHinese(54,4,26,0);
		    	OLED_ShowCHinese(70,4,27,0); 
						 break; 
				     }
							if(keytemp==3)
				         {
					         screen[1] =1;
                   flag=1;									 
									  OLED_Clear(); 
									 time=0;
									 screen[2]=0;
									 changescrenntime=1000;
									
				         }		
						break;
					case 1:           //第二界面
						    switch(screen[0])
								{
									
									case 0://第一子界面
										
											if(time >changescrenntime || keytemp ==0)
				             {
					           flag=0;
										 time=0;
										//	 changescrenntime=300;
											
				             }
									
					if(flag2==0)
						{
						  if(keytemp ==1 &&  flag==0)
					             {
					            	speedref[0]+=10; 
						              flag=1;
												 
												 
					             }
						
					    else if(keytemp ==2 &&  flag==0)
					            {
						          	speedref[0]-=10; 
						            flag=1;
					            }
						OLED_ShowCHinese(0,2,12,1);
		    	                 OLED_ShowCHinese(16,2,13,1); 
											     OLED_ShowCHinese(32,2,14,1);
		    	                 OLED_ShowCHinese(48,2,15,1); 
											  if(speedref[0]<0)
												{
													OLED_ShowString(80,2,"-",1); 
													speedtemp=-speedref[0];
												  OLED_ShowNum(90,2,speedtemp,4,16);//显示ASCII字符	
												}
												else
												{
													 	OLED_ShowString(80,2," ",1); 
													  OLED_ShowNum(90,2,speedref[0],4,16);//显示ASCII字符	
												}
											 
												hSpeed_Reference=speedref[0]/6;   
						}
					else 
						{
							 h_ADCrEFvolt=h_ADCrEFvolt>>3;
						   speedref[1]=h_ADCrEFvolt-1000;
							if(speedref[1] >4100) speedref[1]=4100;
							if(speedref[1] <900) speedref[1]=900;
						   OLED_ShowCHinese(0,2,12,1);
		    	           OLED_ShowCHinese(16,2,13,1); 
						OLED_ShowCHinese(32,2,32,1);
		    	        OLED_ShowCHinese(48,2,33,1); 
							hSpeed_Reference=speedref[1]/6;   
							speedref[0]=1000;
							  OLED_ShowNum(90,2,speedref[1],4,16);//显示ASCII字符	
						}
		               
									 if(keytemp ==3 &&  flag==0)
									 {
										   
										   flag=1;
										 if(flag1)
										 {
											    
											  	 flag1=0;
											     
											   
                           State = INIT;
											 wGlobal_Flags |= SPEED_CONTROL;
										 }
										 else
										 {
											 flag1=1;
									     State = STOP;
										  
										 }
									
										
									 }
									 if(keytemp!=0)
									 {
										  flag3++;
										  if(flag3>800)
											{
												 changescrenntime=50;
												flag3=0;
											}
									 }
									 else
									 {
										  changescrenntime=500;
									 }
									 if(flag1==0)
									 {
										       OLED_ShowCHinese(90,6,18,1);
		    	                 OLED_ShowCHinese(106,6,19,1); 
									 }
									 else
									 {
										 	 OLED_ShowCHinese(90,6,28,1);
		    	             OLED_ShowCHinese(106,6,29,1);
									 }
									        
									         OLED_ShowCHinese(0,4,16,1);   
		    	                 OLED_ShowCHinese(16,4,17,1); 
											     OLED_ShowCHinese(32,4,14,1);
		    	                 OLED_ShowCHinese(48,4,15,1); 
											     OLED_ShowCHinese(0,6,18,1);
		    	                 OLED_ShowCHinese(16,6,19,1); 
											     OLED_ShowCHinese(32,6,20,1);
		    	                 OLED_ShowCHinese(48,6,21,1); 
									      	
											   
										       if(time1>200)
														 {
															 time1=0;
															 if(speedref[0]<0)
												        {
													        OLED_ShowString(80,4,"-",1);
																	speedtemp=-ENC_Get_Mechanical_Speed()*6;
																	 OLED_ShowNum(90,4,(u32)speedtemp,4,16);//显示ASCII字符		
																}
																else{
																	OLED_ShowNum(90,4,(u32)ENC_Get_Mechanical_Speed()*6,4,16);//显示ASCII字符	
																	OLED_ShowString(80,4," ",1);
																}
                                   	
                               GPIO_ResetBits(GPIOD,GPIO_Pin_1);															 
													    }														 
									             GPIO_SetBits(GPIOD,GPIO_Pin_1);	
										break;
									case 1://第二子界面

										if(time >changescrenntime || keytemp ==0)
				                             {
					                           flag=0;
										       time=0;
				                             }

										 if(keytemp ==1 && screen[2]<1 && flag==0)
					                      {
					            	        screen[2]++; 
						                    flag=1;
					                      }
						
					                    else if(keytemp ==2 && screen[2]>=1 && flag==0)
					                      {
						                	 screen[2]--; 
						                    flag=1;
					                      }
										switch(screen[2])
										{
											case 0:
												 OLED_ShowCHinese(0,2,30,0);
		    	                       OLED_ShowCHinese(16,2,31,0); 
					                   OLED_ShowCHinese(54,2,32,1);
		    	                       OLED_ShowCHinese(70,2,33,1); 
									   flag2=0;
												break;
											case 1:
												 OLED_ShowCHinese(0,2,30,1);
		    	                       OLED_ShowCHinese(16,2,31,1); 
					                   OLED_ShowCHinese(54,2,32,0);
		    	                       OLED_ShowCHinese(70,2,33,0); 
									   flag2=1;
												break;
											case 2:
												break;
											default:
												  OLED_Clear(); 
										    OLED_ShowChar(0,0, 2);
												break;
										}
										break;
									case 2://第三子界面
										if(time >changescrenntime || keytemp ==0)
				                             {
					                           flag=0;
										       time=0;
				                             }

										 if(keytemp ==1 && screen[2]<2 && flag==0)
					                      {
					            	        screen[2]++; 
						                    flag=1;
					                      }
						
					                    else if(keytemp ==2 && screen[2]>=1 && flag==0)
					                      {
						                	 screen[2]--; 
						                    flag=1;
					                      }
										 switch(screen[2])
										{
											case 0:
												 OLED_ShowCHinese(0,2,14,0);
		    	               OLED_ShowCHinese(16,2,15,0); 
												 OLED_ShowCHinese(36,2,34,1);
		    	               OLED_ShowCHinese(52,2,35,1); 
												 OLED_ShowCHinese(72,2,36,1);
		    	               OLED_ShowCHinese(88,2,37,1); 
												break;
											case 1:
												 	 OLED_ShowCHinese(0,2,14,1);
		    	               OLED_ShowCHinese(16,2,15,1); 
												 OLED_ShowCHinese(36,2,34,0);
		    	               OLED_ShowCHinese(52,2,35,0); 
												 OLED_ShowCHinese(72,2,36,1);
		    	               OLED_ShowCHinese(88,2,37,1); 
												break;
											case 2:
													 OLED_ShowCHinese(0,2,14,1);
		    	               OLED_ShowCHinese(16,2,15,1); 
												 OLED_ShowCHinese(36,2,34,1);
		    	               OLED_ShowCHinese(52,2,35,1); 
												 OLED_ShowCHinese(72,2,36,0);
		    	               OLED_ShowCHinese(88,2,37,0); 
												break;
											case 3:
												break;	
											default:
												  OLED_Clear(); 
										    OLED_ShowChar(0,0, 3);
												break;
										}
										 if(keytemp ==3 &&  flag==0 && screen[0]==2)
										 	{
										 	  screen[0]=4; 
											  OLED_Clear(); 
												 flag=1;
										 	}
										break;
									case 3:
									
			    OLED_ShowCHinese(36,0,0,1);
		    	OLED_ShowCHinese(54,0,1,1);
			    OLED_ShowCHinese(72,0,2,1);
		    	OLED_ShowCHinese(90,0,3,1);
			
			    OLED_ShowCHinese(36,2,8,1);
		    	OLED_ShowCHinese(54,2,9,1);
			    OLED_ShowCHinese(72,2,10,1);
		    	OLED_ShowCHinese(90,2,11,1); 		
					OLED_ShowCHinese(36,4,38,1);
		    	OLED_ShowCHinese(54,4,38,1);
			    OLED_ShowCHinese(72,4,39,1);
		    	OLED_ShowCHinese(90,4,40,1); 
     				if(keytemp==4 && flag==0)
								       {
									      screen[1]=0; 
												 flag=1;
									     OLED_Clear(); 
								      }	
									    break;
							
								   case 4:
									
                    switch(screen[2])
										{
											case 0:
											pid[0][0]=PID_Speed_InitStructure.hKp_Gain;
											pid[0][1]=PID_Speed_InitStructure.hKi_Gain;
										  pid[0][2]=PID_Speed_InitStructure.hKd_Gain;
													if(time >changescrenntime || keytemp ==0)
				                             {
					                           flag=0;
										       time=0;
														changescrenntime=300;					 
				                             }

										 if(keytemp ==1 && flag==0)
					                      {
					            	       if(pid[0][pidstat[0]]<5000)
															   	pid[0][pidstat[0]]+= 10;
						                    flag=1;
					                      }
						
					                    else if(keytemp ==2 && flag==0)
					                      {
						                  if(pid[0][pidstat[0]]>0)
															   	pid[0][pidstat[0]]-=10;
						                    flag=1;
					                      }
													 if(keytemp ==3 && flag==0)
													 {
														  
														   if(pidstat[0]<=1)
															 {
																   pidstat[0]++;
															 }
															 else
															 {
																 pidstat[0]=0; 
															 }
															 flag=1;
													 }
												
                           														 
													 switch(pidstat[0])
													 {
														 
														 case 0:
														  													 
									
									    	PID_Speed_InitStructure.hKp_Gain=pid[0][0];
											 	 OLED_ShowString(32,2,"P :",0);
														 OLED_ShowString(32,4,"I :",1);
										  
														 OLED_ShowString(32,6,"D :",1);
															 break;
														 case 1:
														  
										
										PID_Speed_InitStructure.hKi_Gain=pid[0][1];
									 	 OLED_ShowString(32,2,"P :",1);
														 OLED_ShowString(32,4,"I :",0);
										  
														 OLED_ShowString(32,6,"D :",1);
															 break;
														 case 2:
											
										PID_Speed_InitStructure.hKd_Gain=pid[0][2];
											 	 OLED_ShowString(32,2,"P :",1);
														 OLED_ShowString(32,4,"I :",1);
										  
														 OLED_ShowString(32,6,"D :",0);
															 break;
													 }
													 OLED_ShowCHinese(0,2,14,1);
												   OLED_ShowCHinese(0,4,15,1);
													  OLED_ShowNum(60,2,	pid[0][0],4,16);//显示ASCII字符
                               OLED_ShowNum(60,4,	pid[0][1],4,16);//显示ASCII字符		
                               OLED_ShowNum(60,6,	pid[0][2],4,16);//显示ASCII字符		

												break;
											case 1:
										
											pid[1][0]=PID_Torque_InitStructure.hKp_Gain;
											pid[1][1]=PID_Torque_InitStructure.hKi_Gain;
										  pid[1][2]=PID_Torque_InitStructure.hKd_Gain;
													if(time >changescrenntime || keytemp ==0)
				                             {
					                           flag=0;
										       time=0;
														changescrenntime=300;					 
				                             }

										 if(keytemp ==1 && flag==0)
					                      {
					            	       if(pid[1][pidstat[1]]<5000)
															   	pid[1][pidstat[1]]+=10;
						                    flag=1;
					                      }
						
					                    else if(keytemp ==2 && flag==0)
					                      {
						                  if(pid[1][pidstat[1]]>0)
															   	pid[1][pidstat[1]]-=10;
						                    flag=1;
					                      }
													 if(keytemp ==3 && flag==0)
													 {
														  
														   if(pidstat[1]<=1)
															 {
																   pidstat[1]++;
															 }
															 else
															 {
																 pidstat[1]=0; 
															 }
															 flag=1;
													 }
													
                           														 
													 switch(pidstat[1])
													 {
														 
														 case 0:
									 
										PID_Torque_InitStructure.hKp_Gain=pid[1][0];
											  	 OLED_ShowString(32,2,"P :",0);
														 OLED_ShowString(32,4,"I :",1);
										  
														 OLED_ShowString(32,6,"D :",1);
															 break;
														 case 1:
														  
											 
										PID_Torque_InitStructure.hKi_Gain=pid[1][1];
											   	 OLED_ShowString(32,2,"P :",1);
														 OLED_ShowString(32,4,"I :",0);
										  
														 OLED_ShowString(32,6,"D :",1);
															 break;
														 case 2:
															   
											 
										PID_Torque_InitStructure.hKd_Gain=pid[1][2];
											    	 OLED_ShowString(32,2,"P :",1);
														 OLED_ShowString(32,4,"I :",1);
										  
														 OLED_ShowString(32,6,"D :",0);
															 break;
													 }
												   OLED_ShowCHinese(0,2,34,1);
												   OLED_ShowCHinese(0,4,35,1);
													  OLED_ShowNum(60,2,	pid[1][0],4,16);//显示ASCII字符
                               OLED_ShowNum(60,4,	pid[1][1],4,16);//显示ASCII字符		
                               OLED_ShowNum(60,6,	pid[1][2],4,16);//显示ASCII字符		
												break;
											case 2:
											pid[2][0]=PID_Flux_InitStructure.hKp_Gain;
											pid[2][1]=PID_Flux_InitStructure.hKi_Gain;
										  pid[2][2]=PID_Flux_InitStructure.hKd_Gain;
													if(time >changescrenntime || keytemp ==0)
				                             {
					                           flag=0;
										       time=0;
														changescrenntime=300;					 
				                             }

										 if(keytemp ==1 && flag==0)
					                      {
					            	       if(pid[2][pidstat[2]]<5000)
															   	pid[2][pidstat[2]]+=10;
						                    flag=1;
					                      }
						
					                    else if(keytemp ==2 && flag==0)
					                      {
						                  if(pid[2][pidstat[2]]>0)
															   	pid[2][pidstat[2]]-=10;
						                    flag=1;
					                      }
													 if(keytemp ==3 && flag==0)
													 {
														   if(pidstat[2]<=1)
															 {
																   pidstat[2]++;
															 }
															 else
															 {
																 pidstat[2]=0; 
															 }
															 flag=1;
													 }
													
                           														 
													 switch(pidstat[2])
													 {
														 
														 case 0:
														  													 
											 
													
											PID_Flux_InitStructure.hKp_Gain=pid[2][0];
											 	 OLED_ShowString(32,2,"P :",0);
														 OLED_ShowString(32,4,"I :",1);
										  
														 OLED_ShowString(32,6,"D :",1);
															 break;
														 case 1:
														  
											 
										PID_Flux_InitStructure.hKi_Gain=pid[2][1];
											  OLED_ShowString(32,2,"P :",1);
														 OLED_ShowString(32,4,"I :",0);
										  
														 OLED_ShowString(32,6,"D :",1);
															 break;
														 case 2:
															   
											 
											PID_Flux_InitStructure.hKd_Gain=pid[2][2];
											  OLED_ShowString(32,2,"P :",1);
														 OLED_ShowString(32,4,"I :",1);
										  
														 OLED_ShowString(32,6,"D :",0);
															 break;
													 }
												   OLED_ShowCHinese(0,2,36,1);
												   OLED_ShowCHinese(0,4,37,1);
												 	  OLED_ShowNum(60,2,	pid[2][0],4,16);//显示ASCII字符
                                OLED_ShowNum(60,4,	pid[2][1],4,16);//显示ASCII字符		
                                OLED_ShowNum(60,6,	pid[2][2],4,16);//显示ASCII字符		
												break;
											default:
												
												break;
										}
											if(keytemp==4 && flag==0)
								       {
									      screen[0]=2; 
												 flag=1;
									     OLED_Clear(); 
								      }	
									    break;
						
								}
								if( keytemp==4 && flag==0)
								{
									 screen[1]=0; 
									 flag=1;
									 OLED_Clear(); 
								}
						break;
							
				}
         
        			
			}
		}
}



