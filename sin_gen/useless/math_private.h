#include <stdint.h>

typedef union
{
	double value;
	struct
	{
		uint32_t lsw;
		uint32_t msw;
	} parts;
	uint64_t word;
} ieee_double_shape_type;

/* Get two 32 bit ints from a double.  */
#define EXTRACT_WORDS(ix0,ix1,d)                                \
do {                                                                \
  ieee_double_shape_type ew_u;                                        \
  ew_u.value = (d);                                                \
  (ix0) = ew_u.parts.msw;                                        \
  (ix1) = ew_u.parts.lsw;                                        \
} while (0)

/* Get the more significant 32 bit int from a double.  */
# define GET_HIGH_WORD(i,d)                                        \
do {                                                                \
  ieee_double_shape_type gh_u;                                        \
  gh_u.value = (d);                                                \
  (i) = gh_u.parts.msw;                                                \
} while (0)

/* Get the less significant 32 bit int from a double.  */
# define GET_LOW_WORD(i,d)                                        \
do {                                                                \
  ieee_double_shape_type gl_u;                                        \
  gl_u.value = (d);                                                \
  (i) = gl_u.parts.lsw;                                                \
} while (0)

/* Get all in one, efficient on 64-bit machines.  */
# define EXTRACT_WORDS64(i,d)                                        \
do {                                                                \
  ieee_double_shape_type gh_u;                                        \
  gh_u.value = (d);                                                \
  (i) = gh_u.word;                                                \
} while (0)

/* Set a double from two 32 bit ints.  */
# define INSERT_WORDS(d,ix0,ix1)                                \
do {                                                                \
  ieee_double_shape_type iw_u;                                        \
  iw_u.parts.msw = (ix0);                                        \
  iw_u.parts.lsw = (ix1);                                        \
  (d) = iw_u.value;                                                \
} while (0)

/* Get all in one, efficient on 64-bit machines.  */
# define INSERT_WORDS64(d,i)                                        \
do {                                                                \
  ieee_double_shape_type iw_u;                                        \
  iw_u.word = (i);                                                \
  (d) = iw_u.value;                                                \
} while (0)

/* Set the more significant 32 bits of a double from an int.  */
#define SET_HIGH_WORD(d,v)                                        \
do {                                                                \
  ieee_double_shape_type sh_u;                                        \
  sh_u.value = (d);                                                \
  sh_u.parts.msw = (v);                                                \
  (d) = sh_u.value;                                                \
} while (0)

/* Set the less significant 32 bits of a double from an int.  */
# define SET_LOW_WORD(d,v)                                        \
do {                                                                \
  ieee_double_shape_type sl_u;                                        \
  sl_u.value = (d);                                                \
  sl_u.parts.lsw = (v);                                                \
  (d) = sl_u.value;                                                \
} while (0)

/* A union which permits us to convert between a float and a 32 bit
   int.  */
typedef union
{
	float value;
	uint32_t word;
} ieee_float_shape_type;
/* Get a 32 bit int from a float.  */
# define GET_FLOAT_WORD(i,d)                                        \
do {                                                                \
  ieee_float_shape_type gf_u;                                        \
  gf_u.value = (d);                                                \
  (i) = gf_u.word;                                                \
} while (0)

/* Set a float from a 32 bit int.  */
# define SET_FLOAT_WORD(d,i)                                        \
do {                                                                \
  ieee_float_shape_type sf_u;                                        \
  sf_u.word = (i);                                                \
  (d) = sf_u.value;                                                \
} while (0)
