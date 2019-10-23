typedef double DATATYPE;

typedef unsigned long _TYPE;   //8 byte

#define _EXP_BITS 11
#define _Fraction_BITS 52

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
void Zero_( int *sign,DATATYPE *ret )
{
	DATATYPE rv=0.0;
	_DATA *p = (_DATA *)&rv;
	p->m_nSign	     =*sign;
	p->m_nExp      = 0;
	p->m_nFraction = 0;

	*ret=rv;
}


//���+subnormal��-subnormal
void SubNormal_( int *sign,DATATYPE *ret )
{
	DATATYPE rv=0.0;
	_DATA *p = (_DATA *)&rv;
	p->m_nSign	     = *sign;
	p->m_nExp      = 0;
	p->m_nFraction = 1;
	*ret=rv;
}

//���quiet NaN
void  QNaN_(DATATYPE *ret)
{	
	DATATYPE rv=0.0;
	_DATA *p = (_DATA *)&rv;
	p->m_nSign	     = 0;
	p->m_nExp      = -1;
	p->m_nFraction = FRACTION_HIGH_BIT;
	*ret=rv;
}

//���Signal NaN
void CQNaN_(DATATYPE *ret)
{	
	DATATYPE rv=0.0;
	_DATA *p = (_DATA *)&rv;
	p->m_nSign	     = 1;
	p->m_nExp      = -1;
	p->m_nFraction = 1;
	*ret=rv;
}

//�����������
void Infinite_( int *sign,DATATYPE *ret )
{
	DATATYPE rv=0.0;
	_DATA *p = (_DATA *)&rv;
	p->m_nSign	     = *sign;
	p->m_nExp      = -1;
	p->m_nFraction = 0;

	*ret=rv;
}

//������⸡����
void anyf_(int *nSign,int *nExp,long *nFraction,DATATYPE *ret)
{
	DATATYPE rv=0.0;
	_DATA *p=(_DATA *)&rv;
	p->m_nSign	     = *nSign;
	p->m_nExp      = *nExp;
	p->m_nFraction = *nFraction;
	
	*ret=rv;
	
}


