#ifndef _MATHFUNC_H
#define _MATHFUNC_H

#include "zf_common_typedef.h"

/*-----------------�����궨��----------------------------*/

#ifndef PI
#define PI 3.1415926535897
#endif

#define DEG2RAD (PI / 180)
#define RAD2DEG (180 / PI)

#define ABS(x)	  ((x) > 0 ? (x) : (-(x)))	   // ȡ����ֵ
#define SIG(x)	  (((x) < 0) ? (-1) : (1))	   // ȡ����
#define MIN(x, y) (((x) > (y)) ? (y) : (x))	   // ȡ��С
#define MAX(x, y) (((x) > (y)) ? (x) : (y))	   // ȡ���

// ����
#define SWAP(x, y, _type) \
	{                     \
		_type z;          \
		z = x;            \
		x = y;            \
		y = z;            \
	}	 // ָ�����ͽ�������

// ���Ʒ�ֵ
#define PEAK(A, B)              \
	{                           \
		if (ABS(A) > ABS(B))    \
			(A) = SIG(A) * (B); \
	}

// �޷�
#define Limit(A, min, max) \
	{                      \
		if (A > max)       \
			A = max;       \
		if (A < min)       \
			A = min;       \
	}

// STM32��׼��
/*!< STM32F10x Standard Peripheral Library old types (maintained for legacy purpose) */

typedef int32_t s32;
typedef int16_t s16;
typedef int8_t	s8;

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t	 u8;

/*
typedef const int32_t sc32; !< Read Only
typedef const int16_t sc16; !< Read Only
typedef const int8_t  sc8;	!< Read Only

typedef __IO int32_t vs32;
typedef __IO int16_t vs16;
typedef __IO int8_t	 vs8;

typedef __I int32_t vsc32;	  //!< Read Only
typedef __I int16_t vsc16;	  //!< Read Only
typedef __I int8_t	vsc8;	  //!< Read Only

typedef const uint32_t uc32; !< Read Only
typedef const uint16_t uc16; !< Read Only
typedef const uint8_t  uc8;	 !< Read Only

typedef __IO uint32_t vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef __I uint32_t vuc32;	   // !< Read Only
typedef __I uint16_t vuc16;	   // !< Read Only
typedef __I uint8_t	 vuc8;	   // !< Read Only
*/

/*�������������������������������������������������������� ����ͽ��� ����������������������������������������������������*/
// Encode�����뵽buff��  Decode����buff�����
#define EncodeS32Data(f, buff) \
	{                          \
		*(s32*) buff = *f;     \
	}
#define DecodeS32Data(f, buff) \
	{                          \
		*f = *(s32*) buff;     \
	}
#define EncodeS16Data(f, buff) \
	{                          \
		*(s16*) buff = *f;     \
	}
#define DecodeS16Data(f, buff) \
	{                          \
		*f = *(s16*) buff;     \
	}
#define EncodeU16Data(f, buff) \
	{                          \
		*(u16*) buff = *f;     \
	}
#define DecodeU16Data(f, buff) \
	{                          \
		*f = *(u16*) buff;     \
	}
#define EncodeU32Data(f, buff) \
	{                          \
		*(u32*) buff = *f;     \
	}
#define DecodeU32Data(f, buff) \
	{                          \
		*f = *(u32*) buff;     \
	}

/**
 * @brief  ���Բ�ֵ ��������
 *
 * @param start
 * @param end
 * @param t
 * @return float
 */
static inline float Lerp(float start, float end, float t)
{
	Limit(t, 0, 1);
	return (end - start) * t + start;
}

// ����ת��
void	ChangeDataByte(uint8_t* p1, uint8_t* p2);
void	buffer_append_int32(uint8_t* buffer, int32_t source, int32_t* index);
int32_t get_s32_from_buffer(const uint8_t* buffer, int32_t* index);
int16_t get_s16_from_buffer(const uint8_t* buffer, int32_t* index);
double	cvtFloat2Double(float n1, float n2);
float	buffer_32_to_float(const uint8_t* buffer, float scale, int32_t* index);
float	buffer_16_to_float(const uint8_t* buffer, float scale, int32_t* index);
void	Int16ToBytes(s16 data, u8* buff, int index);
void	Int32ToBytes(s16 data, u8* buff, int index);
s16		BytesToInt16(u8* buff, int index);
s32		BytesToInt32(u8* buff, int index);

// ��ѧ����
int	Regression(int Line[], int start, int end, float* slope, float* intercept);	   // �ع�
double	CalculateVariance(int Line[], int start, int end);						   // ����
uint8_t LineMono(uint8_t X1, uint8_t X2, int Line[]);							   // �ж��Ƿ񵥵�
float LimitBoth_float(float a, float min, float max);							   // �޷�

#endif
