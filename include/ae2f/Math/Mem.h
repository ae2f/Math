#ifndef ae2f_iMathMem
/** 
 * @brief 
 * Byte vector type: as an input buffer. \n
 * Designed to be a read-only memory.
 * */
#define ae2f_iMathMem const unsigned char*
#endif

#ifndef ae2f_oMathMem
/** 
 * @brief 
 * Byte vector type: as an output buffer. 
 * */
#define ae2f_oMathMem unsigned char*
#endif

#ifndef ae2f_bMathMem
/** 
 * @brief 
 * Byte vector type: as temporary buffer. 
 * */
#define ae2f_bMathMem unsigned char*
#endif

#ifndef ae2f_MathMemOutErr
/** @brief Error pointer type */
#define ae2f_MathMemOutErr ae2f_err_t*
#endif
