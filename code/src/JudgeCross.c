#include "zf_common_headfile.h"

//���ڱ������ұ�Զ���˵�
int leftNearFound[1][2],leftRemoteFound[1][2],
    rightNearFound[1][2],rightRemoteFound[1][2];
//���ұ۴��ڱ�־λ
int LeftCrossFlag=0,RightCrossFlag=0;
//Զ���յ�
int InflexionNear = ROW/2,InflexionFar = ROW/2;
int LeftFound = 0,RightFound = 0;

float ArmLength=0;
float myCrossLengthLeft=0,myCrossLengthRight=0;


/**
 * @brief Ѱ��ʮ�ֱ�
 * @param coordinate1 ���ڱ���ʮ�ֱ۵��¶˵�
 * @param coordinate2 ���ڱ���ʮ�ֱ۵��϶˵�
 * @param start_X ����Ѱ��ʮ�ֱ۵���ʼ��
 * @param start_Y ����Ѱ�� ʮ�ֱ۵���ʼ��
 * @param dir 1��ʾѰ����ۣ�2��ʾѰ���ұ�
 * @return int8���ͣ�ָʾ�Ƿ�ʶ��
 */
static int8 FindCrossArm(int coordinate1[1][2],int coordinate2[1][2]
                  ,int start_X,int start_Y,int dir)
{
  int i=0;
  int checkRow=10+RealEndRow;//5
  int near=0,remote=0;
  int start_x=start_X,start_y=start_Y;
  
  int sum=0;
  
  for(i=start_y;i>checkRow;i--)
  {
    sum=0;
    if(videoData[i][start_x]==1
       &&videoData[i-1][start_x]==1
         &&videoData[i-2][start_x]==1)
    {
      near=i;
      for(i=i-3;i>checkRow;i--)
      {
        if(start_x>=LeftLine[i]
           &&start_x<=RightLine[i])
        {
          sum++;
        }
        if(videoData[i][start_x]==0
         &&videoData[i-1][start_x]==0
           &&videoData[i-2][start_x]==0)
        {
          remote=i+1;
          if(dir==1) myCrossLengthLeft = GetLength(start_x,near,start_x,remote);
          else if(dir==2) myCrossLengthRight = GetLength(start_x,near,start_x,remote);
          if(sum>=2&&AssertLength(start_x,near,start_x,remote
                          ,20,65,&ArmLength))
          {
            coordinate1[0][0]=start_x;
            coordinate1[0][1]=near;
            coordinate2[0][0]=start_x;
            coordinate2[0][1]=remote;
            return 1;
          }
          else
          {
            i=i-3;
            break;
          }
        }
      }
    }
  }
  return 0;
}



float  LeftDis=0,RightDis=0;
/**
 * @brief ʶ��ǵ�
 */
void GetCrossInterSectionPoint(void)
{
  int i=0,j=0;
  int CrossCheckRow=10+RealEndRow;//10
  LeftFound=0;
  RightFound=0;
  for(i = ROW-10;i>CrossCheckRow;i--)
  {
    if(Left_Slope[i-2]<0
       &&Left_Slope[i-2]-Left_Slope[i+2]<-0.8
         &&Left_Slope[i-1]-Left_Slope[i+1]<-0.3)
    {
      int  LeftMin=LeftLine[i+2];
      for(j=i;j>i-5;j--)
      {
        if(videoData[j][LeftLine[i]]==0
           &&videoData[j-1][LeftLine[i]]==0)
        {
          break;
        }
      }
      if(j>i-5) continue;
      for(j=i;j>i-8;j--)
      {
        if(LeftLine[j]<LeftMin)
        {
          LeftMin=LeftLine[j];
        }
      }
      if(LeftMin-LeftLine[i+2]>-5) continue;
      LeftFound = i-3;
      for(i=LeftFound;i<ROW-6;i++)
      {
        if(LeftLine[i]>=LeftLine[i+2]
            &&LeftLine[i+2]>=LeftLine[i+4])
        {
          LeftFound=i+2;
          break;
        }
      }
      break;
    }   
  }
  if(i==CrossCheckRow)
  {
    LeftFound=0;
  }
  for(i = ROW-10;i>CrossCheckRow;i--)
  {
    if(Right_Slope[i-2]>0 
       &&Right_Slope[i-2]-Right_Slope[i+2]>0.8
         &&Right_Slope[i-1]-Right_Slope[i+1]>0.3)
    {
      int RightMax=RightLine[i+2];
      for(j=i;j>i-5;j--)
      {
        if(videoData[j][RightLine[i]]==0
           &&videoData[j-1][RightLine[i]]==0)
        {
          break;
        }
      }
      if(j>i-5) continue;
      for(j=i;j>i-8;j--)
      {
        if(RightLine[j]>RightMax)
        {
          RightMax=RightLine[j];
        }
      }
      if(RightMax-RightLine[i+2]<5) continue;
      RightFound = i-3;
      for(i=RightFound;i<ROW-6;i++)
      {
        if(RightLine[i]<=RightLine[i+2]
            &&RightLine[i+2]<=RightLine[i+4])
        {
          RightFound=i+2;
          break;
        }
      }
      break;
    }
  }
  if(i==CrossCheckRow)
  {
    RightFound = 0;
  }
}


/**
 * @brief ��ȡʮ�ֱ�ʶ����ʼ��
 * @param LeftStart ���ڱ������ʮ�ֱ����
 * @param RightStart ���ڱ����Ҳ�ʮ�ֱ����
 * @return ��
 */
void GetCrossStartPoint(int LeftStart[1][2],int RightStart[1][2])
{
  if(LeftFound!=0&&RightFound!=0)
  {
    if(fabs(LeftFound-RightFound)<30)
    {
      LeftStart[0][0]=LeftLine[LeftFound];
      LeftStart[0][1]=LeftFound;
      RightStart[0][0]=RightLine[RightFound];
      RightStart[0][1]=RightFound;
    }
    else if(LeftFound>RightFound)
    {
      LeftStart[0][0]=LeftLine[LeftFound];
      LeftStart[0][1]=LeftFound;
      RightStart[0][0]=RightLine[ROW-1];
      RightStart[0][1]=ROW-1;
    }
    else
    {
      LeftStart[0][0]=LeftLine[ROW-1];
      LeftStart[0][1]=ROW-1;
      RightStart[0][0]=RightLine[RightFound];
      RightStart[0][1]=RightFound;
    }
  }
  else if(LeftFound==0&&RightFound!=0)
  {
    LeftStart[0][0]=LeftLine[(RightFound+ROW-1)/2];
    LeftStart[0][1]=(RightFound+ROW-1)/2;
    RightStart[0][0]=RightLine[RightFound];
    RightStart[0][1]=RightFound;
  }
  else if(LeftFound!=0&&RightFound==0)
  {
    LeftStart[0][0]=LeftLine[LeftFound];
    LeftStart[0][1]=LeftFound;
    RightStart[0][0]=RightLine[(LeftFound+ROW-1)/2];
    RightStart[0][1]=(LeftFound+ROW-1)/2;
  }
  else
  {
    LeftStart[0][0]=LeftLine[ROW-1];
    LeftStart[0][1]=ROW-1;
    RightStart[0][0]=RightLine[ROW-1];
    RightStart[0][1]=ROW-1;
  }
}


int CrossFlag=0;
int CountLeft=0,CountRight=0;
int maybeLeftCrossFlag=0,maybeRightCrossFlag=0;


/**
 * @brief ʮ��ʶ��
 * @return int 1��ʾʶ�𵽣�0��ʾδʶ��
 */
int Judge_Cross(void)
{
  int i=0;
  float CrossWidth=0;  
  int LeftStart[1][2],RightStart[1][2];
  if(RealEndRow>15)   //ͨ����ֹ�н��г����ж�  Ҫ��
  {
    return 0;
  }
  //�ж��Ƿ���ڿ�ȴ���60����
  if(CrossFlag==0)
  {
    for(i=ROW-1;i>EndRow+6;i--)//EndRow
    {
      if(RealWidth1[i]>60)
      {
        break;
      }
    }
    //��������ڣ���Ϊ����ʮ�֣�����0
    if(i<=EndRow+6)//EndRow
    {
      return 0;
    }
  }
  
  GetCrossInterSectionPoint();//�ҽǵ�
  /*if(LeftFound!=0
     &&AssertLength(LeftLine[LeftFound],LeftFound,
                    COLUMN/2,ROW-1,65,200,&LeftDis)) 
  {
    return 0;
  }
  if(RightFound!=0
     &&AssertLength(RightLine[RightFound],RightFound,
                    COLUMN/2,ROW-1,65,200,&RightDis)) 
  {
    return 0;
  }*/
  GetCrossStartPoint(LeftStart,RightStart);//����ʼ��
  LeftCrossFlag=FindCrossArm(leftNearFound,leftRemoteFound
                             ,LeftStart[0][0],LeftStart[0][1],1);//ʶ�����
  RightCrossFlag=FindCrossArm(rightNearFound,rightRemoteFound
                              ,RightStart[0][0],RightStart[0][1],2);//ʶ���ұ�
  //���ұ۾����ҵ����ҵ�Զ���յ������ڲ�����
  if(LeftCrossFlag==1&&RightCrossFlag==1)
  {
    InflexionNear=ROW-3;//�����յ��У�����ʵ�е㣩����ֵ
    InflexionFar=RealEndRow+5;//Զ���յ��У�����ʵ�е㣩����ֵ
    //�ҽ����յ���
    for(i=GetMax(leftNearFound[0][1],rightNearFound[0][1]);i<ROW-2;i++)
    {
      if(AssertLength(LeftLine[i],i,RightLine[i],i
                      ,30,48,&CrossWidth))//�ж���������Ƿ�ӽ��������� 45����Ҫ��
      {
        InflexionNear=i;
        break;
      }
    }
    //��Զ���յ���
    for(i=GetMin(leftRemoteFound[0][1],rightRemoteFound[0][1]);i>RealEndRow+5;i--)
    {
      if(AssertLength(LeftLine[i],i,RightLine[i],i
                      ,30,48,&CrossWidth))//�ж���������Ƿ�ӽ���������
      {
        InflexionFar=i;
        break;
      }
    }
    
    /*********��֮�����ֻ���*********/
    CountLeft=0;
    CountRight=0;
    maybeLeftCrossFlag=0;
    maybeRightCrossFlag=0;
    for(i=leftRemoteFound[0][1]-2;i>RealEndRow;i--)
    {
      if(LeftLine[i]-LeftLine[i-1]>-3) CountLeft++;
      else CountLeft=0;
      if(CountLeft>=5) 
      {
        CountLeft=0;
        maybeLeftCrossFlag=1;
        break;
      }
      if(i<=leftRemoteFound[0][1]-7) 
      {
        CountLeft=0;
        maybeLeftCrossFlag=0;
        CrossFlag=0;
        return 0;
      }
    }
    for(i=rightRemoteFound[0][1]-2;i>RealEndRow;i--)
    {
      if(RightLine[i]-RightLine[i-1]<3) CountRight++;
      else CountRight=0;
      if(CountRight>=5) 
      {
        CountRight=0;
        maybeRightCrossFlag=1;
        break;
      }
      if(i<=rightRemoteFound[0][1]-7) 
      {
        CountRight=0;
        maybeRightCrossFlag=0;
        CrossFlag=0;
        return 0;
      }
    }
    
    if(maybeLeftCrossFlag==1&&maybeRightCrossFlag==1)
    {
      maybeLeftCrossFlag=0;
      maybeRightCrossFlag=0;
      CrossFlag=1;
      return 1;
    }

//    CrossFlag=1;
//    return 1;
  }
  else
  {
    CrossFlag=0;
    return 0;
  }
  return 0;
}


/**
 * @brief ʮ�ִ��������ߣ�����־λ��λ
 * @return ��
 */
void CrossDeal(void)
{
  int i;     
  if(ImageFlag)
  {
    //��Զ���յ���Ϊ�˵㲹������
    for(i = InflexionNear;i >= InflexionFar;i--)
    {
      MidLine[i]=(MidLine[InflexionNear + RowStep]*(i - InflexionFar + RowStep)+MidLine[InflexionFar - RowStep]*(InflexionNear + RowStep - i))/(InflexionNear - InflexionFar + 2*RowStep);
      Error[i] = MidLine[i] - COLUMN/2 ;
    }  
  }
  else if(ControlRow-RowStep<InflexionNear&&ControlRow+RowStep>InflexionFar)
  {
    //���ڿ�����δ��ʮ���ҽ��Կ����н��д�������һ��
    for(i =ControlRow+RowStep;i >= ControlRow-RowStep;i-=RowStep)
    {
      MidLine[i]=(MidLine[InflexionNear + RowStep]*(i - InflexionFar + RowStep)+MidLine[InflexionFar - RowStep]*(InflexionNear + RowStep - i))/(InflexionNear - InflexionFar + 2*RowStep);
      Error[i] = MidLine[i] - COLUMN/2 ;
    }  
  }
  RoadFlag[CROSS]=1;
}



int Curve_Cross_Error = 0;
uint8 Cross_Direction = 0;
int Cross_start,Cross_end,Cross_start1,Cross_end1;
float Curve_ArmWidth = 0;
float temprow1startvariance=0,temprow2endvariance=0;


/**
 * @brief ʶ��бʮ��
 * @return uint8 1��ʾʶ�𵽣�0��ʾδʶ��
 */
uint8 Judge_Curve_Cross(void)
{
  int i=0,j=0;
  int temprow1=0,temprow2=0;
  int endline=0;
  
  int Leftwhite=0,Rightwhite=0;
  
  if(RowSet-20>EndRow+3) endline = RowSet-20;
  else endline = EndRow+3;
  
  for(i = ROW-2;i>40;i-=2)
  {
    if(LeftLine[i]==0) Leftwhite++;
    if(RightLine[i]==151) Rightwhite++;
  }
  
  //����������������а׵��������ֱ��ж�
  if(Leftwhite>Rightwhite)
  {
    //��һ���ж�������б�����䣬ע�����������б��Ϊ0�����
    for(i = ROW-3;i>endline;i--)
    {
      if(i<=2) return 0;//��ֹi-2Խ�絼�³���ס
      if((Right_Slope[i]<0 && Right_Slope[i+1]<0 && Right_Slope[i+2]<0 && Right_Slope[i-1]>0 && Right_Slope[i-2]>0) || (Right_Slope[i] == 0 && Right_Slope[i+1]<=0 && Right_Slope[i-1]>0 && Right_Slope[i-2]>0) || (i<93 && Right_Slope[i] == 0 && Right_Slope[i+1]<=0 && Right_Slope[i+2]<=0 && Right_Slope[i+3]<=0 && Right_Slope[i+4]<=0 && Right_Slope[i+5]<=0 && Right_Slope[i+6]<0 && Right_Slope[i-1]>0 && Right_Slope[i-2]>0))
      {
        Cross_start = i+1;
        Cross_start1 = Cross_start;
        for(j = i;j > EndRow+1; j--)
        {
          if(j<3) return 0;
          if(RightLine[j]-RightLine[j-1]>10&&RightLine[j]-RightLine[j-2]>10&&RightLine[j-2]<RightLine[Cross_start])//Left_Slope[j]<0 && Left_Slope[j+1]<0 && Left_Slope[j-1]>0 && Left_Slope[j-2]>0
          {
            Cross_end = j-1;
            Cross_end1 = Cross_end;
            //�ų������ߺͻᳵ��ͬʱ���ڵĸ���
            if(RightLine[Cross_end+2]-RightLine[Cross_start+1]<15)
            {
              Curve_Cross_Error = 6;
              return 0;
            }
            break;
          }
        }
        if(j == EndRow+1)
        {
          Curve_Cross_Error = 4;
          return 0;
        }
        break;
      }
    }
    if(i <= endline)
    {
      Curve_Cross_Error = 3;
      return 0;
    }
    //�ڶ����ж�����:ʮ�ֱ۵Ŀ��
    if(AssertLength(RightLine[Cross_start],Cross_start,RightLine[Cross_end],Cross_end,33,49,&Curve_ArmWidth))
    {
       if(Cross_start+2+20>ROW-3) temprow1 = ROW-3;
       else temprow1 = Cross_start+2+20;
       if(Cross_end-2-10<EndRow+5) temprow2 =  EndRow+5;
       else temprow2 = Cross_end-2-10;
       
       //�������ж�����:Զ�������ǵ㸽�����е�б�ʷ���
       temprow1startvariance = GetRightVariance(temprow1,Cross_start+2);
       temprow2endvariance = GetRightVariance(Cross_end-2,temprow2);
       
       if(abs_float(temprow1startvariance)<0.1&&abs_float(temprow2endvariance)<0.1)
       {
         Cross_Direction = 1;
         Curve_Cross_Error = 0;
         return 1;
       }
       else 
       {
          Curve_Cross_Error = 7;
          return 0; 
       }
     }
    else
    {
      Curve_Cross_Error = 5;
      return 0;
    }
    
  }
  
  else if(Leftwhite<Rightwhite)
  {
    //��һ���ж�������б������
    for(i = ROW-3;i > endline;i--)
    {
      if(i<=2) return 0;//��ֹi-2Խ�絼�³���ס
      if((Left_Slope[i]>0 && Left_Slope[i+1]>0 && Left_Slope[i+2]>0 && Left_Slope[i-1]<0 && Left_Slope[i-2]<0) || (Left_Slope[i] == 0 && Left_Slope[i+1]>=0 && Left_Slope[i+2]>0 && Left_Slope[i-1]<0 && Left_Slope[i-2]<0) || (i<93 && Left_Slope[i] == 0 && Left_Slope[i+1]>=0 && Left_Slope[i+2]>=0 && Left_Slope[i+3]>=0 && Left_Slope[i+4]>=0 && Left_Slope[i+5]>=0 && Left_Slope[i+6]>0 && Left_Slope[i-1]<0 && Left_Slope[i-2]<0))
      {
        Cross_start = i+1;
        Cross_start1 = Cross_start;
        for(j = i;j > EndRow+1; j--)
        {
          if(j<3) return 0;
          if(LeftLine[j-1]-LeftLine[j]>10&&LeftLine[j-2]-LeftLine[j]>10&&LeftLine[j-2]>LeftLine[Cross_start])//Left_Slope[j]<0 && Left_Slope[j+1]<0 && Left_Slope[j-1]>0 && Left_Slope[j-2]>0
          {
            Cross_end = j-1;
            Cross_end1 = Cross_end;
            //�ų������ߺͻᳵ��ͬʱ���ڵĸ���
            if(LeftLine[Cross_start+1]-LeftLine[Cross_end+2]<15)
            {
              Curve_Cross_Error = 6;
              return 0;
            }
            break;
          }
        }
        if(j == EndRow+1)
        {
          Curve_Cross_Error = 4;
          return 0;
        }
        break;
      }    
    }
    if(i <= endline)
    {
      Curve_Cross_Error = 3;
      return 0;
    }        
    //�ڶ����ж�����:ʮ�ֱ۵Ŀ��
    if(AssertLength(LeftLine[Cross_start],Cross_start,LeftLine[Cross_end],Cross_end,33,49,&Curve_ArmWidth))
    {
       if(Cross_start+2+20>ROW-3) temprow1 = ROW-3;
       else temprow1 = Cross_start+2+20;
       if(Cross_end-2-10<EndRow+5) temprow2 =  EndRow+5;
       else temprow2 = Cross_end-2-10;
       
       //�������ж�����:Զ�������ǵ㸽�����е�б�ʷ���
       temprow1startvariance = GetLeftVariance(temprow1,Cross_start+2);
       temprow2endvariance = GetLeftVariance(Cross_end-2,temprow2);
       
       if(abs_float(temprow1startvariance)<0.1&&abs_float(temprow2endvariance)<0.1)
       {
         Cross_Direction = 2;
         Curve_Cross_Error = 0;
         return 1;
       }
       else 
       {
          Curve_Cross_Error = 7;
          return 0; 
       }
    }
    else
    {
      Curve_Cross_Error = 5;
      return 0;
    }
  }
  
  else 
  {
    Curve_Cross_Error = 2;
    return 0;
  }
}


/**
 * @brief бʮ�ִ��� �ҵ�бʮ�ֵ�Զ�������ǵ�󣬽������������У���RowStep�����ڵ����߽������ӡ�
 * @return ��
 */
void Curve_Cross_Deal(void)
{
  int i=0;
  for(i = Cross_start1;i >= Cross_end1;i--)
  {
    MidLine[i] = MidLine[Cross_end1-RowStep]+(i-Cross_end1+RowStep)*(MidLine[Cross_start1+RowStep]-MidLine[Cross_end1-RowStep])/(Cross_start1-Cross_end1+2*RowStep);
    Error[i] = MidLine[i] - COLUMN/2 ;
  } 
  RoadFlag[CURVECROSS]=1;
}
