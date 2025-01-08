#include "zf_common_headfile.h"

void ChangeDataByte(uint8_t* p1, uint8_t* p2)
{
	uint8_t t;
	t	= *p1;
	*p1 = *p2;
	*p2 = t;
}

void buffer_append_int32(uint8_t* buffer, int32_t source, int32_t* index)
{
	buffer[(*index)++] = source >> 24;
	buffer[(*index)++] = source >> 16;
	buffer[(*index)++] = source >> 8;
	buffer[(*index)++] = (unsigned char) source;
}

/**
 * @brief Get the s32 data from four uint8_t buffer object
 * @param  buffer           My Param doc
 * @param  index            My Param doc
 * @return int32_t
 */
int32_t get_s32_from_buffer(const uint8_t* buffer, int32_t* index)
{
	int32_t res = (((uint32_t) buffer[*index]) << 24) | (((uint32_t) buffer[*index + 1]) << 16)
				  | (((uint32_t) buffer[*index + 2]) << 8) | (((uint32_t) buffer[*index + 3]));
	*index += 4;
	return res;
}

/**
 * @brief transfer four int32_t type to float
 * @param  buffer           My Param doc
 * @param  scale            My Param doc
 * @param  index            My Param doc
 * @return float
 */
float buffer_32_to_float(const uint8_t* buffer, float scale, int32_t* index)
{
	return (float) get_s32_from_buffer(buffer, index) / scale;
}

/**
 * @brief Get the s16 data from two uint8_t buffer object
 * @param  buffer           My Param doc
 * @param  index            My Param doc
 * @return int16_t
 */
int16_t get_s16_from_buffer(const uint8_t* buffer, int32_t* index)
{
	int16_t res	 = (((uint32_t) buffer[*index]) << 8) | (((uint32_t) buffer[*index + 1]));
	*index		+= 2;
	return res;
}

/**
 * @brief transfer four int16_t type to float
 * @param  buffer           My Param doc
 * @param  scale            My Param doc
 * @param  index            My Param doc
 * @return float
 */
float buffer_16_to_float(const uint8_t* buffer, float scale, int32_t* index)
{
	return (float) get_s16_from_buffer(buffer, index) / scale;
}

double cvtFloat2Double(float n1, float n2)
{
	struct {
		float n1;
		float n2;
	} s;
	s.n1 = n1;
	s.n2 = n2;
	return *((double*) &s);
}

void Int16ToBytes(s16 data, u8* buff, int index)
{
	buff[index]		= (u8) (data & 0xff);
	buff[index + 1] = (u8) ((data >> 8) & 0xff);
}

void Int32ToBytes(s16 data, u8* buff, int index)
{
	buff[index]		= (u8) (data & 0xff);
	buff[index + 1] = (u8) ((data >> 8) & 0xff);
	buff[index + 2] = (u8) ((data >> 16) & 0xff);
	buff[index + 3] = (u8) ((data >> 24) & 0xff);
}

s16 BytesToInt16(u8* buff, int index)
{
	s16 data = ((uint32_t) buff[index]) | ((uint32_t) buff[index + 1] << 8);
	return data;
}

s32 BytesToInt32(u8* buff, int index)
{
	s32 data = (s32) (((buff[index + 3]) << 24) | ((buff[index + 2]) << 16) | ((buff[index + 1]) << 8) | ((buff[index])));
	return data;
}

/// @brief 线性回归计算中线斜率  y = Ax+B
/// @param Line y值，没有限定范围，注意
/// @param start x左边起点 (含)
/// @param end x右边终点 （含）
/// @param slope 斜率
/// @param intercept 截距
/// @return
bool Regression(int Line[], int start, int end, float* slope, float* intercept)
{
	int i, SumLines;
	// 起点终点无所谓
	SumLines   = ABS(start - end) + 1;	  // 例如1-10是10个数字

	int	  SumX = 0, SumY = 0;
	float SumUp = 0, SumDown = 0, avrX = 0, avrY = 0;

	for (i = start; i <= end; i++) {
		SumX += i;
		SumY += Line[i];	// 假设 Line 存放了 y 值
	}

	avrX = (float) SumX / SumLines;	   // X 的平均值
	avrY = (float) SumY / SumLines;	   // Y 的平均值

	for (i = start; i <= end; i++) {
		SumUp	+= (Line[i] - avrY) * (i - avrX);
		SumDown += (i - avrX) * (i - avrX);
	}

	if (SumDown == 0) {
		// 如果 SumDown 为零，则无法计算斜率
		*slope	   = NAN;
		*intercept = NAN;
		return false;	 // 竖直线
	}

	*slope	   = SumUp / SumDown;			// 斜率 A
	*intercept = avrY - (*slope) * avrX;	// 截距 B
	return true;							// 截距式
}

/// @brief 计算从 Line[start] 到 Line[end] 的方差
/// @param Line  y
/// @param start 开始
/// @param end 结束（可以调换）
/// @return
double CalculateVariance(int Line[], int start, int end)
{
	// 检查输入参数的有效性
	if (start < 0 || start > end) {
		return NAN;
	}

	int	   count	= ABS(end - start) + 1;	   // 计算元素个数
	int	   sum		= 0;
	double mean		= 0.0;
	double variance = 0.0;

	// 计算总和和平均值
	for (int i = start; i <= end; i++) { sum += Line[i]; }
	mean = (double) sum / count;

	// 计算方差
	for (int i = start; i <= end; i++) { variance += pow(Line[i] - mean, 2); }
	variance /= count;	  // 计算总体方差

	return variance;
}

/**
 * @brief    判断 边线是否单调
 * @param    X1 :起始 点
 * @param    X2 :终止 点  二者顺序无所谓
 * @return   0：不单调or错误， 1：单调递增， 2：单调递减
 */
uint8_t LineMono(uint8_t X1, uint8_t X2, int Line[])
{
	int i = 0, num = 0;

	int begin = MIN(X1, X2);
	int end	  = MAX(X1, X2);

	for (i = begin; i < end - 1; i++) {
		if (Line[i] <= Line[i + 1])
			num++;
		else
			num = 0;

		if (num >= (end - begin) * 4 / 5)
			return 1;
	}

	for (i = begin; i < end - 1; i++) {
		if (Line[i] >= Line[i + 1])
			num++;
		else
			num = 0;

		if (num >= (end - begin) * 4 / 5)
			return 2;
	}

	return 0;
}
