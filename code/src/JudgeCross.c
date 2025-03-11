#include "zf_common_headfile.h"

//用于保存左右臂远近端点
int leftNearFound[1][2],leftRemoteFound[1][2],
    rightNearFound[1][2],rightRemoteFound[1][2];
//左右臂存在标志位
int LeftCrossFlag=0,RightCrossFlag=0;
//远近拐点
int InflexionNear = ROW/2,InflexionFar = ROW/2;
int LeftFound = 0,RightFound = 0;

float ArmLength=0;
float myCrossLengthLeft=0,myCrossLengthRight=0;


/**
 * @brief 寻找十字臂
 * @param coordinate1 用于保存十字臂的下端点
 * @param coordinate2 用于保存十字臂的上端点
 * @param start_X 用于寻找十字臂的起始列
 * @param start_Y 用于寻找 十字臂的起始行
 * @param dir 1表示寻找左臂，2表示寻找右臂
 * @return int8类型，指示是否识别到
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
 * @brief 识别角点
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
 * @brief 获取十字臂识别起始点
 * @param LeftStart 用于保存左侧十字臂起点
 * @param RightStart 用于保存右侧十字臂起点
 * @return 无
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
 * @brief 十字识别
 * @return int 1表示识别到，0表示未识别到
 */
int Judge_Cross(void)
{
  int i=0;
  float CrossWidth=0;  
  int LeftStart[1][2],RightStart[1][2];
  if(RealEndRow>15)   //通过截止行进行初步判断  要改
  {
    return 0;
  }
  //判断是否存在宽度大于60的行
  if(CrossFlag==0)
  {
    for(i=ROW-1;i>EndRow+6;i--)//EndRow
    {
      if(RealWidth1[i]>60)
      {
        break;
      }
    }
    //如果不存在，认为不是十字，返回0
    if(i<=EndRow+6)//EndRow
    {
      return 0;
    }
  }
  
  GetCrossInterSectionPoint();//找角点
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
  GetCrossStartPoint(LeftStart,RightStart);//找起始点
  LeftCrossFlag=FindCrossArm(leftNearFound,leftRemoteFound
                             ,LeftStart[0][0],LeftStart[0][1],1);//识别左臂
  RightCrossFlag=FindCrossArm(rightNearFound,rightRemoteFound
                              ,RightStart[0][0],RightStart[0][1],2);//识别右臂
  //左右臂均能找到，找到远近拐点行用于补中线
  if(LeftCrossFlag==1&&RightCrossFlag==1)
  {
    InflexionNear=ROW-3;//近处拐点行（带真实中点）赋初值
    InflexionFar=RealEndRow+5;//远处拐点行（带真实中点）赋初值
    //找近处拐点行
    for(i=GetMax(leftNearFound[0][1],rightNearFound[0][1]);i<ROW-2;i++)
    {
      if(AssertLength(LeftLine[i],i,RightLine[i],i
                      ,30,48,&CrossWidth))//判断赛道宽度是否接近正常赛道 45可能要改
      {
        InflexionNear=i;
        break;
      }
    }
    //找远处拐点行
    for(i=GetMin(leftRemoteFound[0][1],rightRemoteFound[0][1]);i>RealEndRow+5;i--)
    {
      if(AssertLength(LeftLine[i],i,RightLine[i],i
                      ,30,48,&CrossWidth))//判断赛道宽度是否接近正常赛道
      {
        InflexionFar=i;
        break;
      }
    }
    
    /*********用之以区分环岛*********/
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
 * @brief 十字处理（补中线），标志位置位
 * @return 无
 */
void CrossDeal(void)
{
  int i;     
  if(ImageFlag)
  {
    //将远近拐点作为端点补出中线
    for(i = InflexionNear;i >= InflexionFar;i--)
    {
      MidLine[i]=(MidLine[InflexionNear + RowStep]*(i - InflexionFar + RowStep)+MidLine[InflexionFar - RowStep]*(InflexionNear + RowStep - i))/(InflexionNear - InflexionFar + 2*RowStep);
      Error[i] = MidLine[i] - COLUMN/2 ;
    }  
  }
  else if(ControlRow-RowStep<InflexionNear&&ControlRow+RowStep>InflexionFar)
  {
    //仅在控制行未出十字且仅对控制行进行处理，方法一样
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
 * @brief 识别斜十字
 * @return uint8 1表示识别到，0表示未识别到
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
  
  //根据最左和最右两列白点数量来分别判断
  if(Leftwhite>Rightwhite)
  {
    //第一个判断条件：斜率跳变，注意有连续多个斜率为0的情况
    for(i = ROW-3;i>endline;i--)
    {
      if(i<=2) return 0;//防止i-2越界导致程序卡住
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
            //排除斑马线和会车区同时存在的干扰
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
    //第二个判断条件:十字臂的宽度
    if(AssertLength(RightLine[Cross_start],Cross_start,RightLine[Cross_end],Cross_end,33,49,&Curve_ArmWidth))
    {
       if(Cross_start+2+20>ROW-3) temprow1 = ROW-3;
       else temprow1 = Cross_start+2+20;
       if(Cross_end-2-10<EndRow+5) temprow2 =  EndRow+5;
       else temprow2 = Cross_end-2-10;
       
       //第三个判断条件:远近两个角点附近几行的斜率方差
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
    //第一个判断条件：斜率跳变
    for(i = ROW-3;i > endline;i--)
    {
      if(i<=2) return 0;//防止i-2越界导致程序卡住
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
            //排除斑马线和会车区同时存在的干扰
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
    //第二个判断条件:十字臂的宽度
    if(AssertLength(LeftLine[Cross_start],Cross_start,LeftLine[Cross_end],Cross_end,33,49,&Curve_ArmWidth))
    {
       if(Cross_start+2+20>ROW-3) temprow1 = ROW-3;
       else temprow1 = Cross_start+2+20;
       if(Cross_end-2-10<EndRow+5) temprow2 =  EndRow+5;
       else temprow2 = Cross_end-2-10;
       
       //第三个判断条件:远近两个角点附近几行的斜率方差
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
 * @brief 斜十字处理 找到斜十字的远近两个角点后，将这两点所在行（±RowStep）所在的中线进行连接。
 * @return 无
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
