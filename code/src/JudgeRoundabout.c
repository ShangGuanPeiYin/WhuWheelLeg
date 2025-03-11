#include "zf_common_headfile.h"

int CircledtR34 = 28,CircledtL34 = 36,CircledtR5 = 9,CircledtL5 = 35,CircledtR6 = 0,CircledtL6 = 0;
int CircledtR6Final = 0;
int CircledtR6A = 0,CircledtR6B = 0;
double My_In_R = 0;
int Cir_Len = 250;
int JudgeRound_flag;
double LeftLineVariance,RightLineVariance;
double CircleTemp7,CircleTemp8;
int LeftFlag = 0,RightFlag = 0;
uint8 Circle_Direction = 0;
//int record_down = 0;
//int record_down1 = 0;
int RightFeatureRow = 0;
int LeftFeatureRow = 0;
int LeftFeatureRow1 = 10;
int RightFeatureRow1 = 10;
int Circle_flag = 0;
uint8 down_prerow = 0;
int Revise_RightLine[ROW],Revise_LeftLine[ROW];
uint8 prerow = 0;
uint8 prerow1 = 10;
int temp1 = 0,temp2 = 0,temp3 = 0,temp4 = 0,temp8 = 0;
uint8 outrow = 0;
int Circle_count = 0;
int Record_Error = 300;//初始化为一个不可能是正常Error的值 ControlRow

int R_Kg = 12;
int R_KgR = 0,R_KgL = 0;
int R_Kgin[6] = {0};
int R0_Array[6] = { 0, 30, 30, 30, 40};
int OutEndRow_Array[6] = {0,50,50,50,50};
int CircleSpeed_Array[6]   = {0, 200, 200, 200, 200 };
int Circle_ControlRow[6] = {0, 62, 62, 62, 62};
int Circle_Fea_Start[6] = {0,30,30,30,30};
int Not_Findprerow_count = 0;
int Near_prerow_flag = 0;
int Left_Border = 0,Right_Border = 0;

int CircleControlRow1 = 0,CircleControlRow2 = 0,CircleControlRow3 = 0,CircleControlRow4 = 0,CircleControlRow5 = 0;

int Circle6FirstFlag1=0,Circle6FirstFlag=0;


/**
 * @brief 给每个环岛分配相应的控制行
 */
void Circle_ControlRow_Set(void)
{
  switch(CircleNumber)
  {
      case 0:Circle_ControlRow[0] = 0;                break;
      case 1:Circle_ControlRow[1] = CircleControlRow1;break;
      case 2:Circle_ControlRow[2] = CircleControlRow2;break;
      case 3:Circle_ControlRow[3] = CircleControlRow3;break;
      case 4:Circle_ControlRow[4] = CircleControlRow4;break;
      default:break;
  }
}
int circle6_count_tmp=0;


/**
 * @brief 环岛处理
 */
void Roundabout_Deal(void)
{
  uint8 i = 0,j = 0;
  static int Find_outrow_flag = 0;
  
  if(Circle_flag == 1)
  {    
    //得到环岛控制行 液晶可调
    Circle_ControlRow_Set();
    ControlRow = Circle_ControlRow[CircleNumber];
    record_down = Find_record_down();
    if(Circle_Direction == 1)
    {
      RightFeatureRow = Find_FeatureRow();
      down_prerow = Find_down_prerow();
      
      if(down_prerow)
      {
        Along_the_other_side();
        if(ImageFlag)
        {
          //显示补线
          for(i = RightFeatureRow;i<=down_prerow;i++)
          {
            Revise_RightLine[i] = Revise_road(RightLine[down_prerow],down_prerow,RightLine[RightFeatureRow],RightFeatureRow,i);
          }
          Draw_a_Line(RightFeatureRow,down_prerow,Revise_RightLine);
        }
        if(RightFeatureRow>=Circle_ControlRow[CircleNumber])
        {
          Circle_flag = 3;
          Near_prerow_flag = 0;
          Not_Findprerow_count = 0;
        }
      }
      else
      {
        Circle_flag = 2;
      }
    }
    else
    {
      LeftFeatureRow = Find_FeatureRow();
      down_prerow = Find_down_prerow();
      
      if(down_prerow)
      {
        Along_the_other_side();
        if(ImageFlag)
        {
          //显示补线
          for(i = LeftFeatureRow;i<=down_prerow;i++)
          {
            Revise_LeftLine[i] = Revise_road(LeftLine[down_prerow],down_prerow,LeftLine[LeftFeatureRow],LeftFeatureRow,i);            
          }
          Draw_a_Line(LeftFeatureRow,down_prerow,Revise_LeftLine);
        }
        if(LeftFeatureRow>=Circle_ControlRow[CircleNumber])
        {
          Circle_flag = 3;
          Near_prerow_flag = 0;
          Not_Findprerow_count = 0;
        }
      }
      else
      {
        Circle_flag = 2;
      }
    }
  }
  if(Circle_flag == 2)
  {
    Circle_ControlRow_Set();
    ControlRow = Circle_ControlRow[CircleNumber];
    record_down = Find_record_down();
    if(Circle_Direction == 1)
    {
      RightFeatureRow = Find_FeatureRow();
      if(RightFeatureRow == 0)
      {
        Temp0 = 2;
      }
      if(RightFeatureRow>=Circle_ControlRow[CircleNumber])
      {
        Circle_flag = 3;
        Near_prerow_flag = 0;
        Not_Findprerow_count = 0;
      }
    }
    else
    {
      LeftFeatureRow = Find_FeatureRow();
      if(LeftFeatureRow>=Circle_ControlRow[CircleNumber])
      {
        Circle_flag = 3;
        Near_prerow_flag = 0;
        Not_Findprerow_count = 0;
      }
    }
  }
  if(Circle_flag == 3)
  {
    //Bee_Set(0);
    Circle_ControlRow_Set();
    ControlRow = Circle_ControlRow[CircleNumber];
    prerow = Find_prerow();
    if(prerow == 0) Temp7 = 1;
    
    if(Not_Findprerow_count == 0)
    {
      
      if(prerow >= ControlRow-6)
      {
        Near_prerow_flag = 1;
      }
      
      if(Circle_Direction == 1)
      {
        if(RightLine[ControlRow] == 151)
        {
          Circle_flag = 4;
        }
        else
        {
          
        }
        
      }
      else
      {
        if(LeftLine[ControlRow] == 0)
        {
          Circle_flag =4;
        }
        else
        {
          
        }
      }
    }
    
    
    if(Near_prerow_flag == 1)
    {
      if(prerow+1 >= ControlRow)
      {
        Circle_flag = 5;
      }
      if(prerow == 0)
      {
        Not_Findprerow_count++;
        if(Not_Findprerow_count>1)
        {
          Circle_flag = 5;
        }
      }
    }
    
  }
  if(Circle_flag == 4)
  {
//    Bee_Set(1);
    Circle_ControlRow_Set();
    ControlRow = Circle_ControlRow[CircleNumber];
    //没有找到prerow的情况还要处理
    prerow = Find_prerow();
    if(prerow == 0) Temp7 =1;
    
    if(prerow+1>= ControlRow)
    {
      Circle_flag = 5;
    }
    else
    {
      
    }
  }
  if(Circle_flag == 5)
  {
    Circle_ControlRow_Set();
    ControlRow = Circle_ControlRow[CircleNumber];
    prerow = Find_prerow();
    Find_CircleEndRow();
    if(ControlRow>Circle_EndRow+4)
    {
      Find_Circleborder();
      if(Circle_Direction == 1)
      {
        Error_now = (RightLine[ControlRow] + LeftLine[ControlRow])/2 - COLUMN/2;
        
      }
      else
      {
        Error_now = (RightLine[ControlRow] + LeftLine[ControlRow])/2 - COLUMN/2;
      }
    }
    else
    {
      ControlRow = Circle_EndRow+4;
      Find_Circleborder();
      if(Circle_Direction == 1)
      {
        Error_now = (RightLine[ControlRow] + LeftLine[ControlRow])/2 - COLUMN/2;
        
      }
      else
      {
        Error_now = (RightLine[ControlRow] + LeftLine[ControlRow])/2 - COLUMN/2;
      }
    }
    if(Judge_in_circle1())
    {
      temp8 = EndRow;
      Circle_flag = 6;
      Find_outrow_flag = 0;
    }
  }
  
  if(Circle_flag == 6)
  {        
    //记录进入第六阶段的次数，用于取消第6阶段前两次的舵机D项输出
    circle6_count_tmp++;    
    //对控制行的限制    
    if(Circle_ControlRow[CircleNumber]<=EndRow+2&&EndRow+2<ROW) 
    { ControlRow = EndRow+2;}
    else if(Circle_ControlRow[CircleNumber]<=EndRow+2&&EndRow+2>ROW-1) 
    { ControlRow = ROW-1;}
    else 
    {ControlRow = Circle_ControlRow[CircleNumber];}
    
    outrow = Find_outrow();
    if(outrow >= ControlRow)
    {
      Circle_flag = 7;
    }
  }
  if(Circle_flag == 7)
  {     
    circle6_count_tmp=0;
    //Circle6FirstFlag1=0;
    //对控制行的限制
    if(Circle_ControlRow[CircleNumber]<=EndRow+2&&EndRow+2<ROW) ControlRow = EndRow+2;
    else if(Circle_ControlRow[CircleNumber]<=EndRow+2&&EndRow+2>ROW-1) ControlRow = ROW-1;
    else {ControlRow = Circle_ControlRow[CircleNumber];}
    //当outrow大于或等于93时不再寻找outrow，避免噪声导致outrow找错
    if(outrow>=93)
    {      
    }
    else
    {
      outrow = Find_outrow();
    }    
      
      
    if(Judge_out_circle() && (outrow>=50||outrow==0))
    {
      Circle_flag = 8;
      //StraightFlag = 1;
    }
    else
    {
        
    }
  }
  if(Circle_flag == 8)
  {    
    //对控制行的限制
    if(Circle_ControlRow[CircleNumber]<=EndRow+5&&EndRow+5<ROW) ControlRow = EndRow+5;
    else if(Circle_ControlRow[CircleNumber]<=EndRow+5&&EndRow+5>ROW-1) ControlRow = ROW-1;
    else {ControlRow = Circle_ControlRow[CircleNumber];}
      
    if(Circle_Direction == 1)
    {                  
      for(j = ROW-5;j>EndRow+5;j++)
      {
        if((RightLine[j+1]-RightLine[j]>4&&RightLine[j+2]-RightLine[j]>4&&RightLine[j+3]-RightLine[j]>4
         &&RightLine[j+1]-RightLine[j-1]>4&&RightLine[j+2]-RightLine[j-1]>4&&RightLine[j+3]-RightLine[j-1]>4
         &&RightLine[j+1]-RightLine[j-2]>4&&RightLine[j+2]-RightLine[j-2]>4&&RightLine[j+3]-RightLine[j-2]>4
         &&RightLine[j+1]==151&&RightLine[j+2]==151&&RightLine[j+3]==151)
         ||
         (RightLine[j+2]-RightLine[j]>4&&RightLine[j+3]-RightLine[j]>4&&RightLine[j+4]-RightLine[j]>4
         &&RightLine[j+1]-RightLine[j-1]>4&&RightLine[j+2]-RightLine[j-1]>4&&RightLine[j+3]-RightLine[j-1]>4
         &&RightLine[j+1]-RightLine[j-2]>4&&RightLine[j+2]-RightLine[j-2]>4&&RightLine[j+3]-RightLine[j-2]>4
         &&RightLine[j+2]==151&&RightLine[j+3]==151&&RightLine[j+4]==151))
        {
          Circle_flag = 9;
          OutHopRow = OutHopRow1 = j-2;
        }
      }
    }
    else
    {                  
      for(j = ROW-5;j>EndRow+5;j--)
      {
        if((LeftLine[j]-LeftLine[j+1]>4&&LeftLine[j]-LeftLine[j+2]>4&&LeftLine[j]-LeftLine[j+3]>4
         &&LeftLine[j-1]-LeftLine[j+1]>4&&LeftLine[j-1]-LeftLine[j+2]>4&&LeftLine[j-1]-LeftLine[j+3]>4
         &&LeftLine[j-2]-LeftLine[j+1]>4&&LeftLine[j-2]-LeftLine[j+2]>4&&LeftLine[j-2]-LeftLine[j+3]>4
         &&LeftLine[j+1]==0&&LeftLine[j+2]==0&&LeftLine[j+3]==0)
         ||
         (LeftLine[j]-LeftLine[j+2]>4&&LeftLine[j]-LeftLine[j+3]>4&&LeftLine[j]-LeftLine[j+4]>4
         &&LeftLine[j-1]-LeftLine[j+1]>4&&LeftLine[j-1]-LeftLine[j+2]>4&&LeftLine[j-1]-LeftLine[j+3]>4
         &&LeftLine[j-2]-LeftLine[j+1]>4&&LeftLine[j-2]-LeftLine[j+2]>4&&LeftLine[j-2]-LeftLine[j+3]>4
         &&LeftLine[j+2]==0&&LeftLine[j+3]==0&&LeftLine[j+4]==0))
        {
          Circle_flag = 9;
          OutHopRow = OutHopRow1 = j-2;
        }
      }      
    }      
  }
  if(Circle_flag == 9)
  {
    OutHopRow = FindOutHopRow();
    if(Circle_Direction == 1)
    {
      if(RowSet<OutHopRow && RightLine[RowSet]!=151&&RightLine[RowSet+1]!=151)
      {
        Circle_flag = 0;
        JudgeRound_flag = 0;
      }
      else
      {
        
      }
    }
    else
    {
      if(RowSet<OutHopRow && LeftLine[RowSet]!=0&&LeftLine[RowSet+1]!=0) 
      {
        Circle_flag = 0;
        JudgeRound_flag = 0;
      }
      else
      {
        
      }
    }
  }
}



int my_test_count = 0;
double Near_Feature_Variance;
int ErrorFlag = 0;
int Cal_down_prerow = 0;
int record_up = 0;
float Circle_Length1 = 0;
int RoundaboutFlag=0;
double Right_record_FeatureVariance = 0,Left_record_FeatureVariance = 0;


/**
 * @brief 环岛识别
 *
 * @return uint8 1为识别到环岛，0未识别到
 */
uint8 Judge_Round1(void)
{
  uint8 i = 0,j = 0,t = 0,p = 0,record_down_start = 0;
  uint8 a = 0;
  //第一个判断条件：一边是直道，另外一边不是，通过斜率方差来判断
  LeftLineVariance = GetLeftVariance(80,10);//10需要再确定  
  RightLineVariance = GetRightVariance(80,10);//10
  CircleTemp7 = LeftLineVariance;
  CircleTemp8 = RightLineVariance;
  if(LeftLineVariance<0.3)//要改
  {
    LeftFlag=1;    
  }
  else
  {
    LeftFlag=0;    
  }
  if(RightLineVariance<0.3)
  {
    RightFlag=1;
  }
  else
  {
    RightFlag=0;
  }
  //右环岛
  if(LeftFlag==1&&RightFlag==0)
  {    
    //判断下角点的存在性,用边界跳变判断
    for(p=ROW-7;p>20;p--)
    {
      if(p<=EndRow) return 0;
      if(((RightLine[p]-RightLine[p-1]<-3 && RightLine[p]-RightLine[p-2]<-9 && RightLine[p]-RightLine[p-3]<-12 && RightLine[p]-RightLine[p-4]<-16)
          ||(p>40 && RightLine[p+1]<145 && RightLine[p]<145 && RightLine[p-1]==151 && RightLine[p-2]==151 && RightLine[p-3]==151)
          ||(p>22 && RightLine[p+1]<145 && RightLine[p]<145 && RightLine[p-1]==151 && RightLine[p-2]==151 && RightLine[p-3]==151 && RightLine[p]>127))
          &&(p<ROW-15 && RightLine[p+5]+1>=RightLine[p+3] && RightLine[p+6]+1>=RightLine[p+3]) && RightLine[p+2]!=151)
      {
        Cal_down_prerow = p+1;
        break;
      }        
    }    
    if(p<=20)
    {
      Cal_down_prerow = 0;
    }
    //根据下角点存在与否，确定找record_down的起始行
    if(Cal_down_prerow)
    {
      record_down_start = Cal_down_prerow - 2;
    }
    else
    {
      record_down_start = ROW-7;
    }
    //第二个判断条件：找record_down
    for(i = record_down_start;i>10;i--)
    {
      if(i<=EndRow) return 0;
      if(RightLine[i] == 151 && RightLine[i+1] == 151 && RightLine[i+2] == 151)
      {
        for(t = i;t>10;t--)
        {
          if(RightLine[t]<151 && RightLine[t-1]<151 && RightLine[t-2]<151)
          {
            if(RightLine[t+1] != 151 || RightLine[t-10]>145 || (RightLine[t]<141 && Cal_down_prerow == 0))//135
            {
              ErrorFlag = 21;
              return 0;
            }
            j = t;
            record_down = t;
            record_down1 = t;
            break; 
          }
        }
        if(t == 10)
        {
          ErrorFlag = 3;
          return 0;
        }
        break;
      }
      else if(Cal_down_prerow)
      {
        if(RightLine[i]-RightLine[i+1]<-25&&RightLine[i]-RightLine[i+2]<-25&&RightLine[i-1]-RightLine[i+1]<-25)
        {
          j = i;
          record_down = i;
          record_down1 = i;
          break;
        }        
      }      
    }
    if(i == 10)
    {
      ErrorFlag = 2;
      return 0;
    }
    
    //第三个判断条件;右环岛内圆的斜率由负变正,根据有没有下角点来分类处理 注意斜率为0的情况
      //若没有下角点对切点附近的斜率的要求放宽
    if(j>ROW-5) j=ROW-5;
    for(;j>ValidRow+3;j--)//ValidRow+3
    {
      if(j<=EndRow+2) return 0;
      if(Cal_down_prerow)
      {
        if(Right_Slope[j+3]<0 && Right_Slope[j+2]<0 && Right_Slope[j+1]<=0 && Right_Slope[j]<=0 && Right_Slope[j-1]>0 && Right_Slope[j-2]>0
           && RightLine[j-2]!=151 && RightLine[j-3]!=151
           && RightLine[j-3] >= RightLine[j] && RightLine[j-4] >= RightLine[j] && RightLine[j+3] >= RightLine[j] && RightLine[j+4] >= RightLine[j]
           && record_down-j < 45)
        {
          RightFeatureRow = j;
          RightFeatureRow1 = RightFeatureRow;
          break;
        }
      }
      else
      {
        //右边界不能太靠左
        if(Right_Slope[j+4]<0&&Right_Slope[j+3]<0&&Right_Slope[j+2]<0&&Right_Slope[j-2]>0&&Right_Slope[j-3]>0&&Right_Slope[j-4]>0
           && RightLine[j-1]>64 && RightLine[j]>64 && RightLine[j+1]>64 && RightLine[j-1]!=151 && RightLine[j-2]!=151 && record_down-j<45)
        {
          //细找FeatureRow
          if(RightLine[j-1]<=RightLine[j])
          {
            if(RightLine[j-1]<=RightLine[j+1]) a = j-1;
            else a = j+1;                         
          }
          else
          {
            if(RightLine[j]<=RightLine[j+1]) a = j;
            else a = j+1;
          }
          RightFeatureRow = a;
          RightFeatureRow1 = RightFeatureRow;
          
          break;
        }
      }
    }
    if(j <= ValidRow+3)//ValidRow+3
    {
      ErrorFlag = 4;
      return 0;
    }
    
    //第四个判断条件：要整合到上面
    if(RightFeatureRow<16 && Cal_down_prerow == 0)//16
    {
      ErrorFlag = 8;
      return 0;
    }
    //以下三段程序（ErrorFlag为101 102 103）用于防止弯入环时将下角点下端识别为record_down,主要针对大环
    if(Cal_down_prerow == 0 && record_down>60 && RightFeatureRow>52 && (record_down-RightFeatureRow)<17 && RightLine[RightFeatureRow]>131)
    {
      ErrorFlag = 101;
      return 0;
    }
    if(Cal_down_prerow == 0 && (record_down-RightFeatureRow)<20 && record_down>40 && RightFeatureRow>30 && RightLine[RightFeatureRow]>133)
    {
      ErrorFlag = 102;
      return 0;
    }
    if(Cal_down_prerow == 0 && (record_down-RightFeatureRow)<27 && record_down>32 && RightFeatureRow>15 && RightLine[RightFeatureRow]>133)
    {
      ErrorFlag = 103;
      return 0;
    }
    //排除某些直角弯
    if(Cal_down_prerow == 0 && record_down-RightFeatureRow>22)
    {
      Right_record_FeatureVariance = GetRightVariance(record_down-1,RightFeatureRow+1);
      if(Right_record_FeatureVariance<0.08)
      {
        ErrorFlag = 100;
        return 0;
      }
    }
//    Right_record_FeatureVariance = GetRightVariance(record_down-1,RightFeatureRow+1);
    //第五个判断条件：RightFeatureRow赛道宽度在40左右,注意前提条件是另一边界没有丢线
    if(LeftLine[RightFeatureRow] != 0 && abs((int)RealWidth1[RightFeatureRow]-40)<8)
    {        
    }
    else
    {
      ErrorFlag = 5;
      return 0;
    }      
    if(record_down>RightFeatureRow)
    {
      //FeatureRow另一边附近斜率方差应该很小
      Near_Feature_Variance = GetLeftVariance(record_down,RightFeatureRow);
            
      if(Near_Feature_Variance>0.2)
      {
        ErrorFlag = 20;
        return 0;
      }
      if(LeftLine[RightFeatureRow+2]==0 || RightLine[RightFeatureRow-2]==0)
      {
        ErrorFlag = 22;
        return 0;
      }
    }
  //排除u型弯
  if(ValidRow>10)//10
  {
    ErrorFlag = 19;
    return 0;
  }
  if(Cal_down_prerow)
  {
    Circle_Length1 = InvSqrt((RealRightLine1[record_up]-RealRightLine1[RightFeatureRow])*(RealRightLine1[record_up]-RealRightLine1[RightFeatureRow]) + (RealRightLine2[record_up]-RealRightLine2[RightFeatureRow])*(RealRightLine2[record_up]-RealRightLine2[RightFeatureRow]) );
    if(Circle_Length1>Cir_Len/1.0)
    {
      ErrorFlag = 15;
      return 0;
    }
  }
   Circle_Direction = 1;
   ErrorFlag=0;
   return 1;
    
    
  }
  //左环岛
  else if(LeftFlag == 0 && RightFlag == 1)
  {
    //判断下角点的存在性,用边界跳变判断
    for(p=ROW-7;p>20;p--)
    {
      if(p<=EndRow) return 0;
      if(((LeftLine[p]-LeftLine[p-1]>3 && LeftLine[p]-LeftLine[p-2]>9 && LeftLine[p]-LeftLine[p-3]>12 && LeftLine[p]-LeftLine[p-3]>16)
         || (p>40 && LeftLine[p+1]>6 && LeftLine[p]>6 && LeftLine[p-1]==0 && LeftLine[p-2]==0 && LeftLine[p-3]==0)
         || (p>22 && LeftLine[p+1]>6 && LeftLine[p]>6 && LeftLine[p-1]==0 && LeftLine[p-2]==0 && LeftLine[p-3]==0 && LeftLine[p]<24))
         &&(LeftLine[p+5]-1<=LeftLine[p+3] && LeftLine[p+6]-1<=LeftLine[p+3]) && LeftLine[p+2] != 0)
      {
        Cal_down_prerow = p+1;
        break;
      }
      
    }
    if(p<=20)
    {
      Cal_down_prerow = 0;
    }
    //根据下角点存在与否，确定找record_down的起始行
    if(Cal_down_prerow)
    {
      record_down_start = Cal_down_prerow - 2;
    }
    else
    {
      record_down_start = ROW-7;
    }
    ////第二个判断条件：找record_down
    for(i = record_down_start;i>10;i--)
    {
      if(i<=EndRow) return 0;
      if(LeftLine[i] == 0 && LeftLine[i+1] == 0 && LeftLine[i+2] == 0)
      {
        for(t = i;t>10;t--)
        {
          if(LeftLine[t]>0 && LeftLine[t-1]>0 && LeftLine[t-2]>0)
          {
            if(LeftLine[t+1] != 0 || LeftLine[t-6]<6 || (LeftLine[t]>10 && Cal_down_prerow == 0))//15
            {
              ErrorFlag = 21;
              return 0;
            }
            j = t;
            record_down = t;
            record_down1 = t;
            break;
          }          
        }
        if(t == 10)
        {
          ErrorFlag = 3;
          return 0;
        }
        break;
      }
      
      else if(Cal_down_prerow)
      {
        if(LeftLine[i]-LeftLine[i+1]>25&&LeftLine[i]-LeftLine[i+2]>25&&LeftLine[i-1]-LeftLine[i+1]>25)
        {
          j = i;
          record_down = i;
          record_down1 = i;
          break;
        }        
      }     
      
    }
    if(i == 10)
    {
      ErrorFlag =2;
      return 0;
    }
    //第三个判断条件;左环岛内圆的斜率由正变负,根据有没有下角点来分类处理 注意斜率为0的情况
    if(j>ROW-5) j = ROW-5;
    for(;j>ValidRow+3;j--)
    {
      if(j<=EndRow+2) return 0;
      if(Cal_down_prerow)
      {
        if(Left_Slope[j+3]>0&&Left_Slope[j+2]>0&&(Left_Slope[j+1]>0||Left_Slope[j+1]==0)&&(Left_Slope[j]>0||Left_Slope[j]==0) &&Left_Slope[j-1]<0&&Left_Slope[j-2]<0
           && LeftLine[j-2]!=0 && LeftLine[j-3]!=0 
           && LeftLine[j-3] <= LeftLine[j] && LeftLine[j-4] <= LeftLine[j] && LeftLine[j+3] <= LeftLine[j] && LeftLine[j+4] <= LeftLine[j] 
           && record_down-j < 45)
        {
          LeftFeatureRow = j;
          LeftFeatureRow1 = LeftFeatureRow;
          break;
        }
      }
      else
      {
        //左边界不能太靠右
        if(Left_Slope[j+4]>0&&Left_Slope[j+3]>0&&Left_Slope[j+2]>0&&Left_Slope[j-2]<0&&Left_Slope[j-3]<0&&Left_Slope[j-4]<0
         && LeftLine[j-1]<88 && LeftLine[j]<88 && LeftLine[j+1]<88 && LeftLine[j-1]!=0 && LeftLine[j-2]!=0 && record_down-j<45)
        {
          //细找FeatureRow
          if(LeftLine[j-1]>=LeftLine[j])
          {
            if(LeftLine[j-1]>=LeftLine[j+1]) a = j-1;
            else a = j+1;
          }
          else
          {
            if(LeftLine[j]>=LeftLine[j+1]) a = j;
            else a = j+1;
          }
          LeftFeatureRow = a;
          LeftFeatureRow1 = LeftFeatureRow;
          break;
        }
      }
    }
    if(j <= ValidRow+3)
    {
      ErrorFlag = 4;
      return 0;
    }
    //第四个判断条件：可以整合到上面
    if(LeftFeatureRow<16 && Cal_down_prerow== 0)//16
    {
      ErrorFlag = 8;
      return 0;
    }
    //以下三段程序（ErrorFlag为101 102 103）用于防止弯入环时将下角点下端识别为record_down,主要针对大环
    if(Cal_down_prerow == 0 && record_down>60 && LeftFeatureRow>52 && (record_down-LeftFeatureRow)<17 && LeftLine[LeftFeatureRow]<20)
    {
      ErrorFlag = 101;
      return 0;
    }
    if(Cal_down_prerow == 0 && (record_down-LeftFeatureRow)<20 && record_down>40 && LeftFeatureRow>30 && LeftLine[LeftFeatureRow]<18)
    {
      ErrorFlag = 102;
      return 0;
    }
    if(Cal_down_prerow == 0 && (record_down-LeftFeatureRow)<27 && record_down>32 && LeftFeatureRow>15 && LeftLine[LeftFeatureRow]<18)
    {
      ErrorFlag = 103;
      return 0;
    }
    //排除某些直角弯
    if(Cal_down_prerow == 0 && record_down-LeftFeatureRow>22)
    {
      Left_record_FeatureVariance = GetLeftVariance(record_down-1,LeftFeatureRow+1);
      if(Left_record_FeatureVariance<0.08)
      {
        ErrorFlag = 100;
        return 0;
      }
    }
    
    //第五个判断条件：RightFeatureRow赛道宽度在40左右,注意前提条件是另一边界没有丢线
    if(RightLine[LeftFeatureRow]!=151 &&abs((int)RealWidth1[LeftFeatureRow]-40)<8)
    {
    }
    else
    {
      ErrorFlag = 5;
      return 0;
    }    
  if(record_down>LeftFeatureRow)
  {
    //FeatureRow另一边附近斜率方差应该很小
    Near_Feature_Variance = GetRightVariance(record_down,LeftFeatureRow);
          
    if(Near_Feature_Variance>0.2)
    {
      ErrorFlag = 20;
      return 0;
    }
    if(RightLine[LeftFeatureRow+2]==151 || RightLine[LeftFeatureRow-2]==151)
    {
      ErrorFlag = 22;
      return 0;
    }
  }
  //排除u型弯
  if(ValidRow>10)//10
  {
    ErrorFlag = 19;
    return 0;
  }
  if(Cal_down_prerow)
  {
    Circle_Length1 = InvSqrt((RealLeftLine1[record_up]-RealLeftLine1[LeftFeatureRow])*(RealLeftLine1[record_up]-RealLeftLine1[LeftFeatureRow]) + (RealLeftLine2[record_up]-RealLeftLine2[LeftFeatureRow])*(RealLeftLine2[record_up]-RealLeftLine2[LeftFeatureRow]) );
    if(Circle_Length1>Cir_Len/1.0)
    {
      ErrorFlag = 15;
      return 0;
    }
  }
   Circle_Direction = 2;
   ErrorFlag=0;
   return 1;
 }
  else
  {
    ErrorFlag = 1;
    return 0;
  }  
}


int Circle_EndRow = 0;
int Circlewidth = 0,Circlewidth1 = 0,Circlewidth2 = 0,Error_now = 0;
double preError = 0;


/**
 * @brief 寻找环岛终点
 */
void Find_CircleEndRow(void)
{
  int i = 0,j = 0;
  
  if(Circle_Direction == 1)
  {
    for(i = ROW-2;i>1;i--)
    {
      //先找到连续的白点，确定在赛道上开始往上找
      if(videoData[i-2][151]==1&&videoData[i-1][151]==1&&videoData[i][151]==1)
      {
        for(j=i-1;j>1;j--)
        {
          if(videoData[j-2][151]==0&&videoData[j-1][151]==0&&videoData[j][151]==0)
          {
            Circle_EndRow = j+1;
            break;
          }
        }
        if(j <= 1) Circle_EndRow = 1;
        break;
      }
    }
    if(i <= 1) Circle_EndRow = 1;
  }
  else
  {
    for(i = ROW-2;i>1;i--)
    {
      if(videoData[i-2][0]==1&&videoData[i-1][0]==1&&videoData[i][0]==1)
      {
        for(j=i-1;j>1;j--)
        {
          if(videoData[j-2][0]==0&&videoData[j-1][0]==0&&videoData[j][0]==0)
          {
            Circle_EndRow = j+1;
            break;
          }
        }
        if(j <= 1) Circle_EndRow = 1;
        break;
      }
    }
    if(i <= 1) Circle_EndRow = 1;
    
  }
}

int Circle_Border = 0;

/**
 * @brief 寻找环岛边界
 */
void Find_Circleborder(void)
{
  int i = 0,j = 0,startcolumn = 0;
  
  //先找到连续多个白点，确定是赛道
  if(Circle_Direction == 1)
  {
    for(i = COLUMN-1;i>5;i--)
    {
      if(videoData[80][i]==1 && videoData[80][i-1]==1 && videoData[80][i-2]==1 && videoData[80][i-3]==1 && videoData[80][i-4]==1 && videoData[80][i-5]==1)
      {
        startcolumn = i-3;
        break;
      }
    }
    if(i == 5)
    {
      startcolumn = 76;
    }
  }
  else
  {
    for(i = 0;i<COLUMN-5;i++)
    {
      if(videoData[80][i]==1 && videoData[80][i+1]==1 && videoData[80][i+2]==1 && videoData[80][i+3]==1 && videoData[80][i+4]==1 && videoData[80][i+5]==1)//ControlRow
      {
        startcolumn = i+3;
        break;
      }
    }
    if(i == COLUMN-5)
    {
      startcolumn = 76;
    }
  }
  
  //先找左边界，满足startcoulmn>2
  for (j = startcolumn; j > 2 ; j--)
  {
    if(videoData[ControlRow][j-2] == 0 && videoData[ControlRow][j-1] == 0 && videoData[ControlRow][j] == 0)
    {
      LeftLine[ControlRow] = j+1;
      break;
    }
  } 
  if(j==2)
  {
    for(;j>-1;j--)
    {
      if(videoData[ControlRow][j]==0)
      {
        LeftLine[ControlRow] = j+1;
        break;
      }
    }
  }
  if(j==-1) LeftLine[ControlRow] = 0;
  
  //找右边界,startcoulmn<COLUMN-2
  for (j = startcolumn; j < COLUMN-2 ; j++)
  {
    if(videoData[ControlRow][j+2] == 0 && videoData[ControlRow][j+1] == 0 && videoData[ControlRow][j] == 0)
    {
      RightLine[ControlRow] = j-1;
      break;
    }
  } 

  if(j==COLUMN-2)
  {
    for(;j<COLUMN;j++)
    {
      if(videoData[ControlRow][j]==0)
      {
        RightLine[ControlRow] = j-1;
        break;
      }
    }
  }
  if(j==COLUMN) RightLine[ControlRow] = COLUMN-1;
  
  
  //Correct Border
  if(prerow)
  {
    if(Circle_Direction == 1)
    {
      if(LeftLine[ControlRow]<Original_RightLine[prerow]+1)//?
      {
        LeftLine[ControlRow] = Original_RightLine[prerow]+1;
      }
    }
    else
    {
      if(RightLine[ControlRow]>Original_LeftLine[prerow]-1)
      {
        RightLine[ControlRow] = Original_LeftLine[prerow]-1;
      }
    }
  }
  
  Left_Border = LeftLine[ControlRow];
  Right_Border = RightLine[ControlRow];
}


/**
 * @brief 补直线
 *
 * @param Column_A 起点列
 * @param Row_A 起点行
 * @param Column_B 终点列
 * @param Row_B 终点行
 * @param row 补线所在行
 *
 * @return int 补线后的行的列值，被限制在0~151之间
 *
 */
int Revise_road(int Column_A,int Row_A,int Column_B,int Row_B,int row)
{
  int md = 0;
  
  md = Column_A - (int)((row-Row_A)*(Column_A-Column_B)/(Row_B-Row_A));
  if(md<0) md = 0;
  if(md>151) md = 151;
  
  return md;
}

int Change_Maxcolumn_flag = 0;
int Temp_Array[10] = {0};

uint8 Find_prerow(void)//可以稳定地找到15~70
{
  uint8 i = 0,endline = 0;//startline = 0;j = 0,
  
//  if(prerow1-5>EndRow+10) startline = prerow1-5;
//  else startline = EndRow+10;//取EndRow后的多少行 十字和下一个同向圆环会干扰prerow
  if(prerow1-10>EndRow+3) endline = prerow1-10;
  else endline = EndRow+3;
  
  if(Circle_Direction==1)//right
  {
     for(i=ROW-4;i>endline;i--)
     {
        if(RightLine[i+1]-RightLine[i]>10 && RightLine[i+2]-RightLine[i]>10 && RightLine[i+3]-RightLine[i] > 10
           && RightLine[i+1]-RightLine[i-1]>10 && RightLine[i+2]-RightLine[i-1]>10 && RightLine[i+3]-RightLine[i-1] > 10
           && RightLine[i+1]-RightLine[i-2]>10 && RightLine[i+2]-RightLine[i-2]>10 && RightLine[i+3]-RightLine[i-2] > 10
           && RightLine[i+1]-RightLine[i-3]>10 && RightLine[i+2]-RightLine[i-3]>10 && RightLine[i+3]-RightLine[i-3] > 10
           && RightLine[i+1]-RightLine[i-4]>10 && RightLine[i+2]-RightLine[i-4]>10 && RightLine[i+3]-RightLine[i-4] > 10  )
        {
             prerow1 = i-1;
             return (i-1);   
        }
     }   
  }
  else if(Circle_Direction==2)
  {
    for(i=ROW-4;i>endline;i--)
    {
      if(LeftLine[i]-LeftLine[i+1] > 10 && LeftLine[i]-LeftLine[i+2]>10 && LeftLine[i]-LeftLine[i+3]>10
         && LeftLine[i-1]-LeftLine[i+1] > 10 && LeftLine[i-1]-LeftLine[i+2]>10 && LeftLine[i-1]-LeftLine[i+3]>10
           && LeftLine[i-2]-LeftLine[i+1] > 10 && LeftLine[i-2]-LeftLine[i+2]>10 && LeftLine[i-2]-LeftLine[i+3]>10
           && LeftLine[i-3]-LeftLine[i+1] > 10 && LeftLine[i-3]-LeftLine[i+2]>10 && LeftLine[i-3]-LeftLine[i+3]>10
          && LeftLine[i-4]-LeftLine[i+1] > 10 && LeftLine[i-4]-LeftLine[i+2]>10 && LeftLine[i-4]-LeftLine[i+3]>10   )
      {
          prerow1 = i-1;
          return (i-1);
      }   
    }
  }
  //下面这句话不能删掉，必须初始化
  prerow1 = 10;
  return 0;    
}


uint8 Find_outrow(void)//可以找到：从角点在视野中出现一直到即将消失，但注意斜率为0的情况
{
  uint8 i = 0,j = 0;
  int Max_Row = 0,Min_Row = 0,Max_Border = 0,Min_Border = 0;
  
  //条件 必须 
  for(i=ROW-5;i>EndRow+6;i--)
  {
    if(Circle_Direction==1)
    { 
      if((Left_Slope[i+2]>=0 && Left_Slope[i+3]>0 && Left_Slope[i+4]>0 && Left_Slope[i-3]<=0 && Left_Slope[i-4]<0 && Left_Slope[i-5]<0)
         || (Left_Slope[i+1]>0 && Left_Slope[i+2]>0 && Left_Slope[i+3]>0 && Left_Slope[i-1]<=0 && Left_Slope[i-2]<=0 && Left_Slope[i-3]<=0 && Left_Slope[i-7]<0)
         || (Left_Slope[i+2]>0 && Left_Slope[i+3]>0 && Left_Slope[i+4]>0 && Left_Slope[i-1]<=0 && Left_Slope[i-2]<=0 && Left_Slope[i-6]<0 && Left_Slope[i-7]<0)) //i,i-1,i-2,i+1
      {
       //细找outrow，右边应为最大边界所在行 
        Max_Row = i-2;
        Max_Border = LeftLine[i-2];
        for(j = i-1;j<=i+1;j++)//?
        {
          if(LeftLine[j]>Max_Border) 
          {
            Max_Border = LeftLine[j];
            Max_Row = j;
          }
        }
        return Max_Row;
      }
    }
    else if(Circle_Direction==2)
    {
      if((Right_Slope[i+2]<=0 && Right_Slope[i+3]<0 && Right_Slope[i+4]<0 && Right_Slope[i-3]>=0 && Right_Slope[i-4]>0 && Right_Slope[i-5]>0)
         || (Right_Slope[i+1]<0 && Right_Slope[i+2]<0 && Right_Slope[i+3]<0 && Right_Slope[i-1]>=0 && Right_Slope[i-2]>=0 && Right_Slope[i-3]>=0 && Right_Slope[i-7]>0)
         || (Right_Slope[i+2]<0 && Right_Slope[i+3]<0 && Right_Slope[i+4]<0 && Right_Slope[i-1]>=0 && Right_Slope[i-2]>=0 && Right_Slope[i-6]>0 && Right_Slope[i-7]>0))
      {
        //细找outrow，左边应为最小边界所在行 
        Min_Row = i-2;
        Min_Border = RightLine[i-2];
        for(j = i-1;j<=i+1;j++)
        {
          if(RightLine[j]<Min_Border) 
          {
            Min_Border = RightLine[j];
            Min_Row = j;
          }
        }
        return Min_Row;
      }
    }
      
  }
  return 0;
}

uint8 Judge_in_circle1(void)
{
  if(Original_Error[ControlRow] == Error_now)
  {
    return 1;
  }
  return 0;
}

double C_variance;
double OutCirRightLineVariance = 0;
double OutCirLeftLineVariance = 0;
/************************************************************************/
/*
*函数名：uint8 Judge_out_circle(void)
*函数功能：环岛由第7阶段进入第8阶段
*形参：无
*返回值：指示是否进入第8阶段
*日期：2019.8.27
*作者：周杏伟
*备注：无
*/
/************************************************************************/
uint8 Judge_out_circle(void)//可用真实赛道斜率
{
  static uint8 count0 = 0;
  int rowup = 0,rowdown = 0;
  //控制出环条件的变量 Circle_R7_outtemp越小出环越早；Circle_L7_outtemp越大出环越早
  int Circle_R7_outtemp = 0,Circle_L7_outtemp = 0;
  if((int)(r0) == 80)
  {
    Circle_R7_outtemp = 20;
    Circle_L7_outtemp = 140;//145
  }
  else if((int)(r0) == 30)
  {
    Circle_R7_outtemp = 45;//57
    Circle_L7_outtemp = 125;
  }
  else
  {
    Circle_R7_outtemp = 40;
    Circle_L7_outtemp = 130;
  }
  
  if(Circle_Direction==1)
  {        
    if(EndRow<=50 && LeftLine[ControlRow+4]>Circle_R7_outtemp && LeftLine[ROW-1]<100 && LeftLine[ROW-2]<100) //80  61  80 (EndRow<=45 && LeftLine[ControlRow+4]>65 && LeftLine[ROW-1]<80 && LeftLine[ROW-2]<85)
    {
      for(int i=ROW-1;i>EndRow;i--)
      {
        if(LeftLine[i]!=0)
        {
          rowdown = i;
          break;
        }
      }
      
      rowup = (ControlRow-20)<(EndRow+2)?(EndRow+2):(ControlRow-20);
      OutCirLeftLineVariance = GetLeftVariance(rowdown,rowup);
      if(OutCirLeftLineVariance<2.0)
      {
        count0++;
      }
      else count0 = 0;      
    }
    else count0 = 0;          
    if(count0>1)
    {
      count0 = 0;
      return 1;
    }
  }
  else
  {    
    if(EndRow<=50 && RightLine[ControlRow+4]<Circle_L7_outtemp && RightLine[ROW-1]>60 && RightLine[ROW-2]>60) //RightLine[ControlRow+4]<120
    {
      for(int i=ROW-1;i>EndRow;i--)
      {
        if(RightLine[i]!=151)
        {
          rowdown = i;
          break;
        }
      }
      
      rowup = (ControlRow-20)<(EndRow+2)?(EndRow+2):(ControlRow-20);
      OutCirRightLineVariance = GetRightVariance(rowdown,rowup);
      if(OutCirRightLineVariance<2.0)
      {
        count0++;
      }
      else count0 = 0;      
    }
    else count0 = 0;          
    if(count0>1)
    {
      count0 = 0;
      return 1;
    }
  }
  return 0;

}

uint8 Find_down_prerow(void)// 直道时，车的最前端在左侧路肩中间，down_prerow = 40             >60跳变值设为10 >80 找不是151的点即可  右边界一定是151
{
  uint8 i = 0,downrow = 0,endline = 0;
  if(EndRow>=3) endline = EndRow + 3;
  else endline = 3;
  
  if(Circle_Direction == 1)
  {
    //******赛道上有噪声（有一点凹产生阴影，或一点点黑）或者阈值没调好，就会有影响，因此必须考虑噪声影响，
    //右边界出现过136 137 93 138 138 而误判，只有一行与其他（多）行比较是不够的，可以的话，必须多行和多行比较，利用尽可能多的信息
    //例如 i和i-1,i-2比较，且i+1和i-1,i-2比较
    if(RightFeatureRow) endline = RightFeatureRow + 2;
    
    //等于151的条件应该放在前面，这样比较快
     for(i=97;i>=endline;i--)
     {
        if((RightLine[i]-RightLine[i-1]<-3 && RightLine[i]-RightLine[i-2]<-9 && RightLine[i+1]-RightLine[i-1]<-3 && RightLine[i+1]-RightLine[i-2]<-9 && RightLine[i]-RightLine[i-3]<-15) 
           || (RightLine[i+1]!=151 && RightLine[i]!=151 && RightLine[i-1]==151 && (i<=38 || (RightLine[i-2]==151 && RightLine[i-3]==151) )))
        {
               // Circle_flag = 1; 
                //Circle_Direction = 2;//left
                downrow = i+1;
                return downrow;
               
         }
            
     }  
     for(i = ROW-2;i > 97;i--)
     {
       if(RightLine[i+1]<151 && RightLine[i]<151 && RightLine[i-1]==151 && RightLine[i-2]==151 && RightLine[i-3]==151)
       {
         downrow = i;
         return downrow;
       }
     }
  }
  else if(Circle_Direction == 2)
  {
    if(LeftFeatureRow) endline = LeftFeatureRow + 2;
    
     for(i=97;i>=endline;i--)
     {
        if((LeftLine[i]-LeftLine[i-1]>3 && LeftLine[i]-LeftLine[i-2]>9 && LeftLine[i+1]-LeftLine[i-1]>3 && LeftLine[i+1]-LeftLine[i-2]>9 && LeftLine[i]-LeftLine[i-3]>15) 
           || (LeftLine[i+1]>4 && LeftLine[i]>4 && LeftLine[i-1]==0 && (i<=38||(LeftLine[i-2]==0 && LeftLine[i-3]==0))))
        {
               // Circle_flag = 1; 
                //Circle_Direction = 2;//left
                downrow = i+1;
                return downrow;
               
         }
            
     }  
     for(i = ROW-2;i > 97;i--)
     {
       if(LeftLine[i+1]>0 && LeftLine[i]>0 && LeftLine[i-1]==0 && LeftLine[i-2]==0 && LeftLine[i-3]==0)
       {
         downrow = i;
         return downrow;
       }
     }
   
  }
  return 0;
}

//下角点存在时的补线
void Along_the_other_side(void)
{
  if(down_prerow && (LeftFeatureRow||RightFeatureRow))
  {
    if(Circle_Direction == 1)
    {
      RightLine[ControlRow-RowStep] = Revise_road(RightLine[down_prerow],down_prerow,RightLine[RightFeatureRow],RightFeatureRow,ControlRow-RowStep);
      RightLine[ControlRow] = Revise_road(RightLine[down_prerow],down_prerow,RightLine[RightFeatureRow],RightFeatureRow,ControlRow);
      RightLine[ControlRow+RowStep] = Revise_road(RightLine[down_prerow],down_prerow,RightLine[RightFeatureRow],RightFeatureRow,ControlRow+RowStep);      
    }
    else
    {
      LeftLine[ControlRow-RowStep] = Revise_road(LeftLine[down_prerow],down_prerow,LeftLine[LeftFeatureRow],LeftFeatureRow,ControlRow-RowStep);
      LeftLine[ControlRow] = Revise_road(LeftLine[down_prerow],down_prerow,LeftLine[LeftFeatureRow],LeftFeatureRow,ControlRow);
      LeftLine[ControlRow+RowStep] = Revise_road(LeftLine[down_prerow],down_prerow,LeftLine[LeftFeatureRow],LeftFeatureRow,ControlRow+RowStep);      
    }
    MidLine[ControlRow-RowStep] = (LeftLine[ControlRow-RowStep]+RightLine[ControlRow-RowStep])/2;
    MidLine[ControlRow] = (LeftLine[ControlRow]+RightLine[ControlRow])/2;
    MidLine[ControlRow+RowStep] = (LeftLine[ControlRow+RowStep]+RightLine[ControlRow+RowStep])/2;
  }
}

uint8 Find_FeatureRow(void)
{
  uint8 i = 0,startline = 0,endline = 0;
  
  //应该增加一个record_down一瞬间找不到的处理，if(record_down==0&&record_down1<90),record_down1<90说明应该是一瞬间找不到
  if(record_down) startline = record_down-1;
  else startline = RowSet+Circle_Fea_Start[CircleNumber];
  
  if(Circle_Direction == 1)
  {
    if(RightFeatureRow1-10>EndRow) endline = RightFeatureRow1-10;
    else endline = EndRow+2;//EndRow
    for(i = startline;i>endline;i--)
    {
      //以record_down为起点，最后判断很多0的条件就不会有Find_FeatureRow2的问题
      if(RightLine[i-2]!=151&&RightLine[i-3]!=151
         &&((Right_Slope[i+1]<0&&(Right_Slope[i]<0||Right_Slope[i]==0)&&Right_Slope[i-1]>0&&Right_Slope[i-2]>0)
         ||(Right_Slope[i+1]<=0&&Right_Slope[i]<=0&&Right_Slope[i-1]>=0&&Right_Slope[i-2]>=0&&Right_Slope[i-3]>=0&&Right_Slope[i-4]>=0&&Right_Slope[i-5]>=0&&Right_Slope[i-6]>=0&&RightLine[i]!=151&&RightLine[i-1]!=151)
         ||(Right_Slope[i+1]<=0&&Right_Slope[i]<=0&&Right_Slope[i-4]>=0&&Right_Slope[i-5]>=0&&Right_Slope[i-6]>=0&&RightLine[i]!=151&&RightLine[i-1]!=151)
         ||(Right_Slope[i+4]<0&&Right_Slope[i+3]<0&&Right_Slope[i+2]<0&&Right_Slope[i-2]>0&&Right_Slope[i-3]>0&&Right_Slope[i-4]>0)
         ||(record_down>45&&Right_Slope[i+4]<0&&Right_Slope[i+3]<0&&Right_Slope[i-3]>0&&Right_Slope[i-4]>0)
         ||((record_down>50||record_down==0)&&Right_Slope[i+3]==0&&Right_Slope[i+2]==0&&Right_Slope[i+1]==0&&Right_Slope[i]==0&&Right_Slope[i-1]==0&&Right_Slope[i-2]==0)))
      {
          //细找FeatureRow,有时可能三个大小相同
          if(RightLine[i-1]==RightLine[i]&&RightLine[i]==RightLine[i+1]) 
          {
            RightFeatureRow1 = i;
            return i;
          }
          if(RightLine[i-1]<=RightLine[i])
          {
            if(RightLine[i-1]<=RightLine[i+1]) 
            {
              RightFeatureRow1 = i-1;
              return (i-1);
            }
            else
            {
              RightFeatureRow1 = i+1;
              return (i+1);
            }
          }
          else
          {
            if(RightLine[i]<=RightLine[i+1]) 
            {
              RightFeatureRow1 = i;
              return i;
            }
            else
            {
              RightFeatureRow1 = i+1;
              return (i+1);
            }
          }
      }
    }
  }
  else if(Circle_Direction == 2)
  {
    if(LeftFeatureRow1-10>EndRow) endline = LeftFeatureRow1-10;
    else endline = EndRow+2;//EndRow
    for(i = startline;i>endline;i--)
    {
      if(LeftLine[i-3]!=0&&LeftLine[i-2]!=0
         &&((Left_Slope[i+1]>0&&(Left_Slope[i]>0||Left_Slope[i]==0)&&Left_Slope[i-1]<0&&Left_Slope[i-2]<0)
         ||(Left_Slope[i+1]>=0&&Left_Slope[i]>=0&&Left_Slope[i-1]<=0&&Left_Slope[i-2]<=0&&Left_Slope[i-3]<=0&&Left_Slope[i-4]<=0&&Left_Slope[i-5]<=0&&Left_Slope[i-6]<=0&&LeftLine[i]!=0&&LeftLine[i-1]!=0)
         ||(Left_Slope[i+1]>=0&&Left_Slope[i]>=0&&Left_Slope[i-4]<=0&&Left_Slope[i-5]<=0&&Left_Slope[i-6]<=0&&LeftLine[i]!=0&&LeftLine[i-1]!=0)
//         ||(Left_Slope[i+1]>0&&Left_Slope[i]>=0&&Left_Slope[i-6]<0&&Left_Slope[i-7]<0)//修改处
//         ||(Left_Slope[i+1]>0&&Left_Slope[i]>=0&&Left_Slope[i-4]<0&&Left_Slope[i-5]<0)
         ||(Left_Slope[i+4]>0&&Left_Slope[i+3]>0&&Left_Slope[i+2]>0&&Left_Slope[i-2]<0&&Left_Slope[i-3]<0&&Left_Slope[i-4]<0)
         ||(record_down>45&&Left_Slope[i+4]>0&&Left_Slope[i+3]>0&&Left_Slope[i-3]<0&&Left_Slope[i-4]<0)
         ||((record_down>50||record_down==0)&&Left_Slope[i+3]==0&&Left_Slope[i+2]==0&&Left_Slope[i+1]==0&&Left_Slope[i]==0&&Left_Slope[i-1]==0&&Left_Slope[i-2]==0)))
      {
          //细找FeatureRow
          if(LeftLine[i]==LeftLine[i-1]&&LeftLine[i]==LeftLine[i+1])
          {
            LeftFeatureRow1 = i;
            return i;
          }
          if(LeftLine[i-1]>=LeftLine[i])
          {
            if(LeftLine[i-1]>=LeftLine[i+1]) 
            {
              LeftFeatureRow1 = i-1;
              return (i-1);
            }
            else 
            {
              LeftFeatureRow1 = i+1;
              return (i+1);
            }
          }
          else
          {
            if(LeftLine[i]>=LeftLine[i+1]) 
            {
              LeftFeatureRow1 = i;
              return i;
            }
            else 
            {
              LeftFeatureRow1 = i+1;
              return (i+1);
            }
          }
      }
    }
  }
  return 0;
}

//要用一个最稳定的量来减小其他量的搜索范围，从而减小误判的可能性
//斜率有噪声时考虑用边界
int Iwantknowstartlineiswhat = 0;
int record_down = 0,record_down1 = 4;
uint8 Find_record_down(void)//注意不要找成上面的,尝试修改成和FeatureRow有关
{
  uint8 i = 0,startline = 0;
  //还是不要和FeatureRow产生关系，因为若FeatureRow一时闪为0的时候，record_down会找错，然后找FeatureRow的起始行出错，FeatureRow也找不到，会有严重的后果
  if(Circle_Direction == 1)
  {
    //避免一瞬间找不到RightFeatureRow或者RightFeatureRow跳变而导致连锁的误判
    //这里的15后期要测试看有没有问题,速度快靠近时可能跳很大
    if(RightFeatureRow&&abs(RightFeatureRow-RightFeatureRow1)<=15)//15
    {
      startline = RightFeatureRow;
    }
    else
    {
      startline = record_down1-8;
    }
//    Iwantknowstartlineiswhat = startline;
//    startline =10;
    for(i = startline;i<ROW-2;i++)
    {
      if((RightLine[i+1]==151 && RightLine[i]==151)
         ||(RightLine[i]>=145 && RightLine[i+1]<128)
         ||(RightLine[i]-RightLine[i+1]<-25 && RightLine[i]-RightLine[i+2]<-25 && RightLine[i]-RightLine[i+3]<-25))
      {
        record_down1 = i;
        return i;
      }
    }
  }
  else
  {
    //避免一瞬间找不到LeftFeatureRow而导致连锁的误判
    if(LeftFeatureRow&&abs(LeftFeatureRow-LeftFeatureRow1)<=15)
    {
      startline = LeftFeatureRow;
    }
    else
    {
      startline = record_down1-8;
    }
    for(i = startline;i<ROW-2;i++)
    {
      if((LeftLine[i+1]==0 && LeftLine[i]==0)
         ||(LeftLine[i]-LeftLine[i+1]>25 && LeftLine[i]-LeftLine[i+2]>25 && LeftLine[i]-LeftLine[i+3]>25))
      {
        record_down1 = i;
        return i;
      }
    }
  }
  return 0;
}

uint8 Find_record_down1(void)
{
  uint8 i = 0,startline = 0;
  startline = ROW-2;
  for(i=startline;i>EndRow+4;i--)
  {
    if(record_down1>90) return 90;
    if(RightLine[i+2] == 151 && RightLine[i+1] == 151 && RightLine[i] != 151 && RightLine[i-1] != 151 && RightLine[i]>RightLine[i-3])
    {
      record_down1 = i;
      return i;
    }
  }
  
  return 0;
}

//第0行到第99行每行校正后的纵坐标
float Y[100] = {221.131230504030,
209.317835549212,	198.629340615141,	188.912374348964,	180.040234667361,	171.907333459065,	164.424974374400,	157.518104841529,	151.122789764440,	145.184226504534,	139.655170506709,	134.494675763944,	129.667079035746,	125.141174505054,	120.889538481810,	116.887973264370,	113.115046329534,	109.551706316872,	106.180961280037,	102.987607735879,	99.9580013946224,	97.0798622775354,	94.3421083515676,	91.7347129285069,	89.2485819603306,	86.8754480656929,	84.6077786851292,	82.4386962151156,	80.3619083370304,	78.3716470543682,	76.4626151942582,	74.6299393283562,	72.8691282320801,	71.1760361366916,	69.5468301412481,	67.9779612452171,	66.4661385409707,	65.0083061711988,	63.6016227117108,	62.2434426869236,	60.9312999650211,	59.6628928135008,	58.4360704245845,	57.2488207445479,	56.0992594620987,	54.9856200290384,	53.9062446020442,	52.8595758078828,	51.8441492460293,	50.8585866527866,	49.9015896597985,	48.9719340875218,	48.0684647209166,	47.1900905204742,	46.3357802268414,	45.5045583218093,	44.6955013124083,	43.9077343083509,	43.1404278661547,	42.3927950760153,	41.6640888699189,	40.9535995316378,	40.2606523911636,	39.5846056878321,	38.9248485879156,	38.2807993438096,	37.6519035831537,	37.0376327173120,	36.4374824596085,	35.8509714445882,	35.2776399403581,	34.7170486467690,	34.1687775728346,	33.6324249873599,	33.1076064372687,	32.5939538285884,	32.0911145654760,	31.5987507430528,	31.1165383901651,	30.6441667585052,	30.1813376548142,	29.7277648131508,	29.2831733044508,	28.8472989808167,	28.4198879521771,	28.0006960931387,	27.5894885780172,	27.1860394421857,	26.7901311680200,	26.4015542938465,	26.0201070444146,	25.6455949815248,	25.2778306735416,	24.9166333826096,	24.5618287684779,	24.2132486079119,	23.8707305287439,	23.5341177576796,	23.2032588810373,	22.8780076176517
};
double r0,roundK;
int R0_1 = 0,R0_2 = 0,R0_3 = 0,R0_4 = 0;
/*计算半径*/
void Compute_R(void)
{
  float Real_1[1][2], Real_2[1][2],Real_3[1][2];
  float x1,y1,x2,y2,x3,y3,d1,d2,d3,r1,dety;
  int row1, row2;
  if(Circle_Direction == 1)
  {
    if(abs(RightFeatureRow-ControlRow)<10)
    {
      for(int i=RightFeatureRow;i<100; i++)
      {
        if(fabs(fabs(Y[i]-Y[RightFeatureRow])-15.0)<1.0)
        {row1=i;}
      }
      for(int i=RightFeatureRow;i>0;i--)
      {
        if(fabs(fabs(Y[RightFeatureRow]-Y[i])-15.0)<1.0)
        {row2=i;}
      }
      Real_Location(RightLine[row1],row1,Real_1);
      Real_Location(RightLine[RightFeatureRow],RightFeatureRow,Real_2);
      Real_Location(RightLine[row2],row2,Real_3);
      x1=Real_1[0][0];
      y1=Real_1[0][1];
      x2=Real_2[0][0];
      y2=Real_2[0][1];
      x3=Real_3[0][0];
      y3=Real_3[0][1];
      d1=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
      d2=sqrt((x2-x3)*(x2-x3)+(y2-y3)*(y2-y3));
      d3=sqrt((x1-x3)*(x1-x3)+(y1-y3)*(y1-y3));
      r0=d1*d2*d3/(2*((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1)));
    }
      r0=fabs(r0);
  }
  else if(Circle_Direction == 2)
  {
    if(abs(LeftFeatureRow-ControlRow)<10)
    {
      for(int i=LeftFeatureRow;i<100; i++)
      {
        if(fabs(fabs(Y[i]-Y[LeftFeatureRow])-15.0)<1.0)
        {row1=i;}
      //break;
      }
      for(int i=LeftFeatureRow;i>0;i--)
      {
        if(fabs(fabs(Y[LeftFeatureRow]-Y[i])-15.0)<1.0)
        {row2=i;}
      //break;
      }
      Real_Location(LeftLine[row1],row1,Real_1);
      Real_Location(LeftLine[LeftFeatureRow],LeftFeatureRow,Real_2);
      Real_Location(LeftLine[row2],row2,Real_3);
      x1=Real_1[0][0];
      y1=Real_1[0][1];
      x2=Real_2[0][0];
      y2=Real_2[0][1];
      x3=Real_3[0][0];
      y3=Real_3[0][1];
      d1=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
      d2=sqrt((x2-x3)*(x2-x3)+(y2-y3)*(y2-y3));
      d3=sqrt((x1-x3)*(x1-x3)+(y1-y3)*(y1-y3));
      r0=d1*d2*d3/(2*((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1)));
    }
      r0=fabs(r0);
  }
  if(r0<30.0)
  {r0=30.0;}
  else if(r0>80.0)
  {r0=80.0;}
      
      r1=r0+40.0;
      My_In_R = r0;
      dety=InvSqrt(r1*r1-r0*r0);
      /*找到伪斜率，根据斜率补直线*/
      roundK=40.0/dety;
      
}
float X0, Y0, X1, Y1;
void Update_Patch(void)
{
  double C1_temp = 0;
  //3,4阶段中线偏移量
  int Cirlce_34_add = 0;  
//  if(r0==0) 
//  {
    float r1,dety;
    switch(CircleNumber)
    {
      case 0:r0 = 0;       break;
      case 1:r0 = R0_1*1.0;break;
      case 2:r0 = R0_2*1.0;break;
      case 3:r0 = R0_3*1.0;break;
      case 4:r0 = R0_4*1.0;break;
//      case 5:Circle_ControlRow[5] = CircleControlRow5;break;
      default:break;
    }
//    r0 = R0_Array[CircleNumber];
    r1=r0+40.0;
    dety=InvSqrt(r1*r1-r0*r0);
    /*找到伪斜率，根据斜率补直线*/
    roundK=40.0/dety;
//  }
  
    if((int)(r0) == 30)
    {
      Cirlce_34_add = -2;
    }
    else if((int)(r0) == 40)
    {
      Cirlce_34_add = 2;
    }
    else
    {
      Cirlce_34_add = 0;
    }
    
  //当控制行打到FeatureRow
  //找上角点dot[1][2]
  float dot[1][2];
  
  if(Circle_Direction == 1)
  {
    if(prerow)
    {
      Real_Location(RightLine[prerow], prerow, dot);
      Y0=dot[0][1];
      X0=dot[0][0];
    }
    else
    {
      X0=30.0;
      Y0=Y[64];
    }
  //由FeatureRow附近的环境计算内环曲率
  //什么时候计算曲率比较靠谱？在控制行打到FeatureRow的时候，在距离FeatureRow上下各15cm左右的位置进行选点计算曲率
  //保存当前曲率避免重复计算
    Y1=Y[ControlRow];
    X1=X0-roundK*fabs(Y1-Y0);
    RealLeftLine1[ControlRow]=X1;
    /*if(Circle_number==3)
    {RealMidLine1[ControlRow]=RealLeftLine1[ControlRow]+30.0;}
    else{*/
    RealMidLine1[ControlRow]=RealLeftLine1[ControlRow]+CircledtR34+Cirlce_34_add;//28.0
    C1_temp=X1+20.0;
  }
  else if(Circle_Direction == 2)
  {
    if(prerow)
    {
      Real_Location(LeftLine[prerow], prerow, dot);
      Y0=dot[0][1];
      X0=dot[0][0];
    }
    else 
    {
      X0=-30.0;
      Y0=Y[64];
    }
  //由FeatureRow附近的环境计算内环曲率
  //什么时候计算曲率比较靠谱？在控制行打到FeatureRow的时候，在距离FeatureRow上下各15cm左右的位置进行选点计算曲率
  //保存当前曲率避免重复计算
  //前提是已知视野中对应的某一行所对应的纵坐标（查表）
  //根据查表所得的结果再次计算横坐标
  //得到控制行对应的控制点的真实坐标
  //已求解得到用来做控制的点
  Y1=Y[ControlRow];
  X1=roundK*fabs(Y1-Y0)+X0;
  RealRightLine1[ControlRow]=X1;
  /*if(Circle_number==3)
  {RealMidLine1[ControlRow]=RealRightLine1[ControlRow]-30.0;}
  else{*/
   RealMidLine1[ControlRow]=RealRightLine1[ControlRow]-CircledtL34-Cirlce_34_add;//26.0
   C1_temp=X1-20.0;
  }
  
  //让打角更加连续的融合策略，利用图像融合的基本原理
  
  
  //注意：在补线的前一点与补线的那一点由于角度突变需要分离微分控制
  
}
void Update_Patch1(void)
{
  //第5阶段中线偏移量
  int Cirlce_5_add = 0;
  if((int)(r0) == 30)
  {
    Cirlce_5_add = 4;
  }
  else
  {
    Cirlce_5_add = 0;
  }
  if(Circle_Direction == 1)
  {
    float RealLeft[1][2];
    Real_Location(LeftLine[ControlRow],ControlRow,RealLeft);
    RealLeftLine1[ControlRow]=RealLeft[0][0];
    RealLeftLine2[ControlRow]=RealLeft[0][1];
    RealMidLine1[ControlRow]=RealLeftLine1[ControlRow]+CircledtR5+Cirlce_5_add; //9.0
    RealMidLine2[ControlRow]=Y[ControlRow];
  }
  else if(Circle_Direction == 2)
  {
    float RealRight[1][2];
    Real_Location(RightLine[ControlRow],ControlRow,RealRight);
    RealRightLine1[ControlRow]=RealRight[0][0];
    RealRightLine2[ControlRow]=RealRight[0][1];
    RealMidLine1[ControlRow]=RealRightLine1[ControlRow]-CircledtL5-Cirlce_5_add; //-35
    RealMidLine2[ControlRow]=Y[ControlRow];
  }
  
}
float C_temp;
void Update_Patch2(void)
{
  if(outrow!=0 && outrow<93)
  {
    float dot[1][2];
  
    if(Circle_Direction == 1)
    {
      Real_Location(LeftLine[outrow], outrow, dot);
      Y0=dot[0][1];
      X0=dot[0][0];
    //由FeatureRow附近的环境计算内环曲率
    //什么时候计算曲率比较靠谱？在控制行打到FeatureRow的时候，在距离FeatureRow上下各15cm左右的位置进行选点计算曲率
    //保存当前曲率避免重复计算
      Y1=Y[ControlRow];
      X1=X0+fabs(Y1-Y0)/roundK;
      RealLeftLine1[ControlRow]=X1;
    
    /*if(Circle_number==3)
    {
      RealMidLine1[ControlRow]=RealLeftLine1[ControlRow]+30.0;
    C_temp=X1+30.0;}
    else {*/
      RealMidLine1[ControlRow]=RealLeftLine1[ControlRow];//?
      C_temp=X1;
    }
    else if(Circle_Direction == 2)
    {
      Real_Location(RightLine[outrow], outrow, dot);
      Y0=dot[0][1];
      X0=dot[0][0];
      //由FeatureRow附近的环境计算内环曲率
      //什么时候计算曲率比较靠谱？在控制行打到FeatureRow的时候，在距离FeatureRow上下各15cm左右的位置进行选点计算曲率
      //保存当前曲率避免重复计算
      //前提是已知视野中对应的某一行所对应的纵坐标（查表）
      //根据查表所得的结果再次计算横坐标
      //得到控制行对应的控制点的真实坐标
      //已求解得到用来做控制的点
      Y1=Y[ControlRow];
      X1=X0-fabs(Y1-Y0)/roundK;
      RealRightLine1[ControlRow]=X1;
  
  /*if(Circle_number==3)
  {
    RealMidLine1[ControlRow]=RealRightLine1[ControlRow]-30.0;
  C_temp=X1-30.0;}
  else {*/
      RealMidLine1[ControlRow]=RealRightLine1[ControlRow];
      C_temp=X1;
    }
  }
  else
    RealMidLine1[ControlRow]=C_temp;
  //让打角更加连续的融合策略，利用图像融合的基本原理
}

int OutHopRow,OutHopRow1;
int FindOutHopRow(void)
{
  int i = 0;
  
  if(Circle_Direction == 1)
  {
      for(i = ROW-5;i>EndRow+5;i--)
      {
        if(RightLine[i+2]==151&&RightLine[i+1]==151&&RightLine[i]!=151&&RightLine[i-1]!=151&&RightLine[i-2]!=151)
        {
          OutHopRow1 = i-2;
          return (i-2);
        }
      }
  }
  else
  {
     for(i = ROW-5;i>EndRow+5;i--)
     {
        if(LeftLine[i+2]==0&&LeftLine[i+1]==0&&LeftLine[i]!=0&&LeftLine[i-1]!=0&&LeftLine[i-2]!=0)
        {
          OutHopRow1 = i-2;
          return (i-2);
        }
     }
  }
  
  return RowSet;
}