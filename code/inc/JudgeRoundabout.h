#ifndef _JUDGEROUNDABOUT_H_
#define _JUDGEROUNDABOUT_H_

#include "zf_common_typedef.h"

extern int	  CircledtR34, CircledtL34, CircledtR5, CircledtL5, CircledtR6, CircledtL6, CircledtR6Final, CircledtR6A, CircledtR6B;
extern int	  R_KgR, R_KgL;
extern int	  ErrorFlag;
extern int	  CircleSpeed_Array[6];
extern float  Circle_Length1;
extern double My_In_R;
extern int	  Cir_Len;
extern int	  JudgeRound_flag;
extern uint8  Circle_Direction;
extern uint8  prerow, down_prerow, down_prerow2;
extern double LeftLineVariance, RightLineVariance;
extern int	  LeftFeatureRow, LeftFeatureRow1;
extern int	  RightFeatureRow, RightFeatureRow1;
extern double Near_Feature_Variance;
extern uint8  outrow;
extern int	  RoundaboutFlag;
extern int	  Circle_EndRow, Circlewidth, Circlewidth1, Circlewidth2, Error_now, LeftLine_record;
extern int	  record_down, record_down1, record_down2, Record_Error, Cal_down_prerow;
extern int	  Circle_ControlRow[6];
extern int	  OutEndRow_Array[6];
extern int	  Circle_flag;
extern int	  OutHopRow, OutHopRow1;
extern int	  Circle_count;
extern int	  LeftFeatureRow, LeftFeatureRow1;
extern int	  RightFeatureRow, RightFeatureRow1;
extern int	  R_Kg, R_Kgin[6];
extern int	  Circle_Fea_Start[6];
extern int	  R0_1, R0_2, R0_3, R0_4;
extern double r0;
extern int	  Circle6FirstFlag1, Circle6FirstFlag, circle6_count_tmp;
int			  Revise_road(int Column_A, int Row_A, int Column_B, int Row_B, int row);
uint8		  Find_outrow(void);
uint8		  Find_prerow(void);
uint8		  Judge_Round1(void);
void		  Roundabout_Deal(void);
uint8		  Find_down_prerow(void);
uint8		  Find_FeatureRow(void);
uint8		  Judge_in_circle1(void);
uint8		  Judge_out_circle(void);
void		  Along_the_other_side(void);
void		  Find_Circleborder(void);
void		  Find_CircleEndRow(void);
uint8		  Find_record_down(void);
uint8		  Find_record_down1(void);
void		  Update_Patch(void);
void		  Update_Patch1(void);
void		  Update_Patch2(void);

void Compute_R(void);
int	 FindOutHopRow(void);

extern int CircleControlRow1, CircleControlRow2, CircleControlRow3, CircleControlRow4, CircleControlRow5;
extern int Iwantknowstartlineiswhat;
#endif