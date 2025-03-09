#include "zf_common_headfile.h"

int MidLine[ROW],Width[ROW],Error[ROW];
int Original_MidLine[ROW],Original_Error[ROW];//根据路况修改Error后，可能还需要原来的Error用于计算或判断
float RealMidLine1[ROW-1],RealMidLine2[ROW-1],RealLeftLine1[ROW-1],RealRightLine1[ROW-1],RealLeftLine2[ROW-1],RealRightLine2[ROW-1];
float RealWidth1[ROW];//每行赛道宽度
int EndRowC = 0;
int AD_Error_Count = 0,BrokenRoad2chooseADFlag = 0;
int MySetBrokenRoad2Dir[15]={0};


/**
 * @brief 找中线
 */
void Find_MidLine(void)
{
    int i;    
    for (i = ROW-1; i > RealEndRow; i--)		//寻找边线，中线
    {    
      Width[i] = RightLine[i] - LeftLine[i];
      MidLine[i] = (RightLine[i] + LeftLine[i])/2;
      Original_MidLine[i] = MidLine[i];
      Error[i] = MidLine[i] - COLUMN/2;
      Original_Error[i] = Error[i];
    }          
}


/**
 * @brief 画中线
 */
void DrawMidLine_Simple(void)
{
  int i;
  for (i = ROW-1; i > 0; i--)
  {
    videoData[i][MidLine[i]]=0;//~videoData[i][MidLine[i]];
    videoData[i][MidLine[i]-1]=0;//~videoData[i][MidLine[i]-1];
//    videoData[i][MidLine[i]+1]=0;//~videoData[i][MidLine[i]+1];
  }
}


/**
 * @brief 画屏幕中线
 */

void DrawScreenMidLine(void)
{
  int i;
  for (i = ROW-1; i > 0; i--)
  {
    videoData[i][76]=~videoData[i][76];
  }
}


/**
 * @brief 校正中线 对环岛的中线进行特殊处理。
 */
void GetRealMidLine(void)
{
  int i=0,temprow=0;
  float RealMid[1][2],RealLeft[1][2],RealRight[1][2];  
  int Cirlce_7_add = 0;//环岛第7阶段中线偏移量
  int Cirlce_6_add = 0;//环岛第6阶段中线偏移量
  
  temprow = ValidRow<EndRow?ValidRow:EndRow;
  for(i=ROW-2;i>temprow;i--)//ROW-1
  {
    Real_Location(MidLine[i],i,RealMid);
    RealMidLine1[i]=RealMid[0][0];
    RealMidLine2[i]=RealMid[0][1];
      
    Real_Location(LeftLine[i],i,RealLeft);
    RealLeftLine1[i]=RealLeft[0][0];
    RealLeftLine2[i]=RealLeft[0][1];
    Real_Location(RightLine[i],i,RealRight);
    RealRightLine1[i]=RealRight[0][0];
    RealRightLine2[i]=RealRight[0][1];
    RealWidth1[i]=RealRightLine1[i]-RealLeftLine1[i];
  }
  //环岛Find_Circleborder还要处理
  if(Circle_flag == 2)
  {
    if(Circle_Direction == 1)
    {RealMidLine1[ControlRow]=RealLeftLine1[ControlRow]+20.0;}
    else if(Circle_Direction == 2)
    {RealMidLine1[ControlRow]=RealRightLine1[ControlRow]-20.0;}
  }
  else if(Circle_flag == 3 || Circle_flag == 4)
  {    
    Update_Patch();
    
    if(R_Kgin[CircleNumber]>10000) R_Kgin[CircleNumber]=-R_Kgin[CircleNumber]+10000;
      
    if(Circle_Direction == 1)
    {RealMidLine1[ControlRow]=RealMidLine1[ControlRow]+R_Kgin[CircleNumber];}
    else if(Circle_Direction == 2)
    {RealMidLine1[ControlRow]=RealMidLine1[ControlRow]-R_Kgin[CircleNumber];}
  }
  else if(Circle_flag == 5)
  {
    Update_Patch1();
  }
  else if(Circle_flag == 6)
  {
    //Cirlce_6_add为环岛第6阶段中线偏移量，用于对环岛第6阶段舵机打角，行驶路径进行调整
    if((int)(r0) == 30)
    {
      Cirlce_6_add = 2;
    }
    else
    {
      Cirlce_6_add = 0;
    }
    
    if(Circle_Direction == 1)
    {      
      RealMidLine1[ControlRow]=RealMidLine1[ControlRow]+CircledtR6+Cirlce_6_add;//0.0            
    }
    else if(Circle_Direction == 2)
    {RealMidLine1[ControlRow]=RealMidLine1[ControlRow]-CircledtL6-Cirlce_6_add;}  //-20.0
  }
  else if(Circle_flag==7)
  {
     Update_Patch2();
     //Cirlce_7_add为环岛第7阶段中线偏移量
     if((int)(r0) == 30)
     {
       Cirlce_7_add = 9;//7
     }
     else if((int)(r0) == 40)
     {
       Cirlce_7_add = 6;
     }
     else if((int)(r0) == 80)
     {
       Cirlce_7_add = -3;
     }
     else
     {
       Cirlce_7_add = 0;
     }
     
     if(Circle_Direction == 1)
    {RealMidLine1[ControlRow]=RealMidLine1[ControlRow]+R_KgR+Cirlce_7_add;}
    else if(Circle_Direction == 2)
    {RealMidLine1[ControlRow]=RealMidLine1[ControlRow]-R_KgL-Cirlce_7_add;}
  }
  else if(Circle_flag == 8 || Circle_flag == 9)
  {
    if(Circle_Direction == 1)
    {RealMidLine1[ControlRow]=RealLeftLine1[ControlRow]+20.0;}
    else if(Circle_Direction == 2)
    {RealMidLine1[ControlRow]=RealRightLine1[ControlRow]-20.0;}
  }
}