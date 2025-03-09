#include "zf_common_headfile.h"

int EndRow = 0,EndRow1 = -1,Maxcolumn = COLUMN/2;
int RealEndRow,CorrectedEndRow;
int ControlRow=50;


/**
 * @brief 找截止行，即白点最多的列对应的行
 */
void Find_EndRow(void)
{
  int i,j,num,max = 0;

  int Circle_6_start;

  //环岛第6阶段下寻找EndROw
  if(Circle_flag==6)
  {
    //除R100以外的环岛
    if((int)(r0)<80)
    {
      Circle_6_start = 115;
    }
    //R100的环岛
    else
    {
      Circle_6_start = 40;
    }
    if(Circle_Direction == 1)
    {
        for(j = Circle_6_start;j < COLUMN; j++)
        {
          num = 0;
          for(i = ROW-1;i > 0;i--)
          {
            if(videoData[i][j] == 0)
              break;
            num++;
          }
          if(num >= max)
          {
            EndRow=i;
            max = num;
            Maxcolumn = j;
            if(Maxcolumn >= COLUMN - 3) Maxcolumn = COLUMN - 3;
            if(Maxcolumn <= Circle_6_start+2) Maxcolumn = Circle_6_start+2;
          }  
        }
    }
    else
    {
        for(j = 0;j < COLUMN-Circle_6_start; j++)
        {
          num = 0;
          for(i = ROW-1;i > 0;i--)
          {
            if(videoData[i][j] == 0)
              break;
            num++;
          }
          if(num >= max)
          {
            EndRow=i;
            max = num;
            Maxcolumn = j;
            if(Maxcolumn >= COLUMN - Circle_6_start-2) Maxcolumn = COLUMN - Circle_6_start-2;
            if(Maxcolumn <= 2) Maxcolumn = 2;
          }  
        }
    }
  }  
  //普通赛道下寻找EndRow
  else
  {
    for(j = 0;j < COLUMN; j++)
    {
      num = 0;
      for(i = ROW-1;i > 0;i--)
      {
        if(videoData[i][j] == 0)
          break;
        num++;
      }
      if(num >= max)
      {
        EndRow=i;
        max = num;
        Maxcolumn = j;
        if(Maxcolumn >= COLUMN - 3) Maxcolumn = COLUMN - 3;
        if(Maxcolumn <= 2) Maxcolumn = 2;
      }  
    }
  }
}


 /**
 * @brief 防止截止行过小
 */     
void CorrectEndRow(void)
{
  if(EndRow<2)
  {
    EndRow=2;
    return;
  }
  else if(EndRow>95)
  StopFlag=1;
}
