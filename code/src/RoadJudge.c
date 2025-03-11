#include "zf_common_headfile.h"

int			   SnakePathFlag = 0;
RoadConditions roadCondition = STRANGE;
double		   RealWarp		 = 0;
int			   Temp0, Temp1, Temp2, Temp3, Temp4, Temp5, Temp6, Temp7;
double		   MidLineSlopeVariance;
// 元素标志位
int			   RoadFlag[ROAD_KINDS];
int			   Ba_RealWarp1 = 3152, Ba_RealWarp2 = 3982, Ba_RealWarp3 = 3902;
int			   ValidRow1		  = 0;
int			   My_Round_Open_Flag = 1;

// 初步处理，包括初始化，赛道基本信息提取    可以供我们参考控制流程
void RawDeal()
{
	// int i=0;
	// 初始化
	//  for(i=0;i<ROAD_KINDS;i++)
	//    RoadFlag[i]=0;
	// 算截止行
	Find_EndRow();
	// 领域法找边界
	// FindBorder1();
	// 记录真实截止行
	RealEndRow = EndRow;
	// 修正截止行
	CorrectEndRow();
	// 行扫描法找边界
	FindBorder();
	// 算中线
	Find_MidLine();
	// 找控制行
	// Find_ControlRow();
	// 计算赛道斜率
	// GetSlope();
	// 对ValidRow做一个判断后赋值给ValidRow1,可抑制远处图像带来的噪声
	// ValidRow1=ValidRow<=10?10:ValidRow;
	// 算全局中线斜率方差
	// MidLineSlopeVariance=GetVariance(ROW-5,ValidRow1+2);
}

// 预判，上一次识别到的元素进行优先判断
int SuperiorJudge(RoadConditions roadJudge)
{
	switch (roadJudge) {
		case SNAKEBENDING: {
			if (Judge_SnakeBending() == 1) {
				// SnakeBendingDeal();
				return 1;
			}
			break;
		}
		case LOOP: {
			if (Circle_flag != 0) {
				RoadFlag[LOOP] = 1;
				if (JudgeRound_flag == 1)
					Roundabout_Deal();
				return 1;
			}
			break;
		}
		case CROSS: {
			if (Judge_Cross() == 1) {
				CrossDeal();
				return 1;
			}
			break;
		}
		case RAMP: {
			if (Judge_Ramp() == 1) {
				RampDeal();
				return 1;
			}
			break;
		}
		case STARTLINE: {
			if (Judge_StartLine() == 1) {
				StartLineDeal();
				return 1;
			}
			break;
		}

		case CURVECROSS: {
			if (Judge_Curve_Cross()) {
				Curve_Cross_Deal();
				return 1;
			}
			break;
		}

		case NORMAL: {
			break;
		}

		default:
			break;
	}
	return 0;
}

int			   CircleNumber;
// 赛道元素判断
RoadConditions Judge_Road_Condition(void)
{
	RawDeal();	  // 预处理，找截止行、边线和中线

#if 0	 // 先不启用元素识别

  if(EndRowNotFind==1&&Barrier_flag==0)
  {
    return STRANGE;
  }
  else if(SuperiorJudge(roadCondition)==1)
  {
    return roadCondition;
  }
  else if(roadCondition!=STARTLINE&&Judge_StartLine()==1)//roadCondition!=STARTLINE&&Judge_StartLine()==1)
  { 
    StartLineDeal();
    return STARTLINE;
  }    
  else if(roadCondition!=CROSS&&Judge_Cross()==1)
  {
    CrossDeal();
    return CROSS;
  } 
  else if(roadCondition!=RAMP&&Judge_Ramp()==1)
  {
    RampDeal();
    return RAMP;
  }     
  else if(roadCondition!=SNAKEBENDING&&Judge_SnakeBending()==1)
  {
    //SnakeBendingDeal();
    return SNAKEBENDING;
  }
  else if(roadCondition!=LOOP&&Judge_Round1()&&My_Round_Open_Flag == 1)
  {
    Circle_count++;
    if(Circle_count>1)
    {
      JudgeRound_flag = 1;
      Circle_flag = 1;
      Record_Error = 300;
      CircleNumber++;
      Circle_count = 0;      
      LeftFeatureRow1 = 10;
      RightFeatureRow1 = 10;
      RoadFlag[LOOP]=1;
      return LOOP;
    }
    
  }
  else if(roadCondition!=CURVECROSS)
  {
    if(Judge_Curve_Cross())
    {
      Curve_Cross_Deal();
      return CURVECROSS;
    }
  }
  else 
  {    
    RoadFlag[NORMAL]=1;
    return NORMAL;
  }
  return STRANGE;

  if(EndRowNotFind==1&&Barrier_flag==0)

#endif
	return NORMAL;
}

// 计算角度
float WarpSet = 0.0;
void  Image_To_Warp(void)
{
	roadCondition = Judge_Road_Condition();
	// 计算物理世界真实中线
	GetRealMidLine();

	// 识别到坡道将控制行改近（需将控制行改的很大，可以防止上坡舵机乱打角）
	if (RoadFlag[RAMP] != 0) {
		ControlRow = 92;	// 94
	}
	if (Circle_flag >= 2 && Circle_flag <= 9) {
		RealWarp = atan(RealMidLine1[ControlRow] / RealMidLine2[ControlRow]);
	}
	// 识别到路障给每个阶段赋上偏差 液晶可调
	else if (Barrier_flag == 1) {
		if (BarrierDir == 1)
			RealWarp = (-1) * Ba_RealWarp1 / 10000.0;	 //-0.5073
		else
			RealWarp = Ba_RealWarp1 / 10000.0;
	} else {
		RealWarp = (RealMidLine1[ControlRow] * 0.5f + RealMidLine1[ControlRow + RowStep] * 0.15f
					+ RealMidLine1[ControlRow - RowStep] * 0.35f);
		RealWarp = atan(RealWarp / RealMidLine2[ControlRow]);
	}
	CorrectedEndRow = EndRow;
	EndRow			= RealEndRow;
}
