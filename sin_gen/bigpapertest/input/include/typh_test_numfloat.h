typedef float DATATYPE;

//typedef unsigned long _TYPE;   //8 byte
typedef unsigned int _TYPE;  //4 byte

#define _EXP_BITS 8
#define _Fraction_BITS 23

// С���������λ,��������QNaN��SNaN
#define FRACTION_HIGH_BIT		(((_TYPE)1)<<(sizeof(_TYPE)*8-_EXP_BITS-2))
// ��Ч����λ
#define DIGITS_BITS				(sizeof(_TYPE)*8-_EXP_BITS)
// ָ��ƫ��
#define FLOAT_EXP_OFF			( (((int)1)<<(_EXP_BITS-1)) - 1 )

// IEEE�����ʽ
typedef struct
{
	_TYPE m_nFraction : sizeof(_TYPE)*8-_EXP_BITS-1;
	_TYPE m_nExp	  : _EXP_BITS;
	_TYPE m_nSign     : 1;
} _DATA;


//���+0.0��-0.0
DATATYPE Zero( int sign )
{
	DATATYPE rv=0.0;
	_DATA *p = (_DATA *)&rv;
	p->m_nSign	     = sign;
	p->m_nExp      = 0;
	p->m_nFraction = 0;

	return rv;
}


//���+subnormal��-subnormal
DATATYPE SubNormal( int sign )
{
	DATATYPE rv=0.0;
	_DATA *p = (_DATA *)&rv;
	p->m_nSign	     = sign;
	p->m_nExp      = 0;
	p->m_nFraction = 1;

	return rv;
}

//���quiet NaN
DATATYPE QNaN()
{	
	DATATYPE rv=0.0;
	_DATA *p = (_DATA *)&rv;
	p->m_nSign	     = 0;
	p->m_nExp      = -1;
	p->m_nFraction = FRACTION_HIGH_BIT;

	return rv;
}

//���Signal NaN
DATATYPE CQNaN()
{	
	DATATYPE rv=0.0;
	_DATA *p = (_DATA *)&rv;
	p->m_nSign	     = 1;
	p->m_nExp      = -1;
	p->m_nFraction = 1;

	return rv;
}

//�����������
DATATYPE Infinite( int sign )
{
	DATATYPE rv=0.0;
	_DATA *p = (_DATA *)&rv;
	p->m_nSign	     = sign;
	p->m_nExp      = -1;
	p->m_nFraction = 0;

	return rv;
}

//������⸡����
DATATYPE anyf(int nSign,int nExp,long nFraction)
{
	DATATYPE rv=0.0;
	_DATA *p=(_DATA *)&rv;
	p->m_nSign	     = nSign;
	p->m_nExp      = nExp;
	p->m_nFraction = nFraction;

	return rv;
	
}


