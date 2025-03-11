#include "zf_common_headfile.h"

int			   SnakePathFlag = 0;
RoadConditions roadCondition = STRANGE;
double		   RealWarp		 = 0;
int			   Temp0, Temp1, Temp2, Temp3, Temp4, Temp5, Temp6, Temp7;
double		   MidLineSlopeVariance;
// Ԫ�ر�־λ
int			   RoadFlag[ROAD_KINDS];
int			   Ba_RealWarp1 = 3152, Ba_RealWarp2 = 3982, Ba_RealWarp3 = 3902;
int			   ValidRow1		  = 0;
int			   My_Round_Open_Flag = 1;

// ��������������ʼ��������������Ϣ��ȡ    ���Թ����ǲο���������
void RawDeal()
{
	// int i=0;
	// ��ʼ��
	//  for(i=0;i<ROAD_KINDS;i++)
	//    RoadFlag[i]=0;
	// ���ֹ��
	Find_EndRow();
	// �����ұ߽�
	// FindBorder1();
	// ��¼��ʵ��ֹ��
	RealEndRow = EndRow;
	// ������ֹ��
	CorrectEndRow();
	// ��ɨ�跨�ұ߽�
	FindBorder();
	// ������
	Find_MidLine();
	// �ҿ�����
	// Find_ControlRow();
	// ��������б��
	// GetSlope();
	// ��ValidRow��һ���жϺ�ֵ��ValidRow1,������Զ��ͼ�����������
	// ValidRow1=ValidRow<=10?10:ValidRow;
	// ��ȫ������б�ʷ���
	// MidLineSlopeVariance=GetVariance(ROW-5,ValidRow1+2);
}

// Ԥ�У���һ��ʶ�𵽵�Ԫ�ؽ��������ж�
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
// ����Ԫ���ж�
RoadConditions Judge_Road_Condition(void)
{
	RawDeal();	  // Ԥ�����ҽ�ֹ�С����ߺ�����

#if 0	 // �Ȳ�����Ԫ��ʶ��

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

// ����Ƕ�
float WarpSet = 0.0;
void  Image_To_Warp(void)
{
	roadCondition = Judge_Road_Condition();
	// ��������������ʵ����
	GetRealMidLine();

	// ʶ���µ��������иĽ����轫�����иĵĺܴ󣬿��Է�ֹ���¶���Ҵ�ǣ�
	if (RoadFlag[RAMP] != 0) {
		ControlRow = 92;	// 94
	}
	if (Circle_flag >= 2 && Circle_flag <= 9) {
		RealWarp = atan(RealMidLine1[ControlRow] / RealMidLine2[ControlRow]);
	}
	// ʶ��·�ϸ�ÿ���׶θ���ƫ�� Һ���ɵ�
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
