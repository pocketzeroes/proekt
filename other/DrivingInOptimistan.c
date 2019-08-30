#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include <stdlib.h>
// #include "memoization.h"
#ifndef __MEMOIZATION_H__
#define __MEMOIZATION_H__
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
//#include "macro_utilities.h"
#ifndef __MACRO_UTILITIES_H__
#define __MACRO_UTILITIES_H__
#define MAKE_COMMA() MAKE_COMMA1()
#define MAKE_COMMA1() MAKE_COMMA2()
#define MAKE_COMMA2() ,
#define STRINGIZE(arg)  STRINGIZE1(arg)
#define STRINGIZE1(arg) STRINGIZE2(arg)
#define STRINGIZE2(arg) #arg
#define CONCATENATE(arg1, arg2)   CONCATENATE1(arg1, arg2)
#define CONCATENATE1(arg1, arg2)  CONCATENATE2(arg1, arg2)
#define CONCATENATE2(arg1, arg2)  arg1##arg2
#define COUNT_ARGUMENTS(...) PP_NARG_(,##__VA_ARGS__,PP_RSEQ_N())
#define PP_NARG_(...) PP_ARG_N(__VA_ARGS__)
#define PP_ARG_N( \
         _0, _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
         _61,_62,_63,N,...) N
#define PP_RSEQ_N() \
         63,62,61,60,                   \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9,8,7,6,5,4,3,2,1,0
#define FOR_EACH_COMPOSER_0(prefix, postfix, finalPrefix, finalPostfix, ...)
#define FOR_EACH_COMPOSER_1(prefix, postfix, finalPrefix, finalPostfix, x, ...) finalPrefix(x)finalPostfix
#define FOR_EACH_COMPOSER_2(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_1(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_3(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_2(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_4(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_3(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_5(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_4(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_6(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_5(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_7(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_6(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_8(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_7(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_9(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_8(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_10(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_9(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_11(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_10(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_12(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_11(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_13(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_12(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_14(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_13(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_15(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_14(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_16(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_15(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_17(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_16(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_18(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_17(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_19(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_18(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_20(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_19(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_21(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_20(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_22(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_21(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_23(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_22(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_24(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_23(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_25(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_24(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_26(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_25(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_27(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_26(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_28(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_27(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_29(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_28(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_30(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_29(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_31(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_30(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_32(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_31(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_33(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_32(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_34(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_33(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_35(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_34(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_36(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_35(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_37(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_36(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_38(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_37(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_39(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_38(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_40(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_39(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_41(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_40(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_42(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_41(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_43(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_42(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_44(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_43(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_45(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_44(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_46(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_45(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_47(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_46(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_48(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_47(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_49(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_48(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_50(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_49(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_51(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_50(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_52(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_51(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_53(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_52(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_54(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_53(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_55(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_54(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_56(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_55(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_57(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_56(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_58(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_57(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_59(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_58(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_60(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_59(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_61(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_60(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_62(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_61(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_63(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_62(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_64(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_63(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_(N, prefix, postfix, finalPrefix, finalPostfix, ...) CONCATENATE(FOR_EACH_COMPOSER_, N)(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER(prefix, postfix, finalPrefix, finalPostfix, ...) FOR_EACH_COMPOSER_(COUNT_ARGUMENTS(__VA_ARGS__), prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define SIZE_OF_ARGS(...) FOR_EACH_COMPOSER_(COUNT_ARGUMENTS(__VA_ARGS__), sizeof, +, sizeof, +, __VA_ARGS__) 0
#define FOR_EACH_0(what, x, ...)
#define FOR_EACH_1(what, x, ...) what(x)
#define FOR_EACH_2(what, x, ...)\
  what(x);\
  FOR_EACH_1(what,  __VA_ARGS__)
#define FOR_EACH_3(what, x, ...)\
  what(x);\
  FOR_EACH_2(what, __VA_ARGS__);
#define FOR_EACH_4(what, x, ...)\
  what(x);\
  FOR_EACH_3(what,  __VA_ARGS__);
#define FOR_EACH_5(what, x, ...)\
  what(x);\
 FOR_EACH_4(what,  __VA_ARGS__);
#define FOR_EACH_6(what, x, ...)\
  what(x);\
  FOR_EACH_5(what,  __VA_ARGS__);
#define FOR_EACH_7(what, x, ...)\
  what(x);\
  FOR_EACH_6(what,  __VA_ARGS__);
#define FOR_EACH_8(what, x, ...)\
  what(x);\
  FOR_EACH_7(what,  __VA_ARGS__);
#define FOR_EACH_9(what, x, ...)\
  what(x);\
  FOR_EACH_8(what, __VA_ARGS__);
#define FOR_EACH_10(what, x, ...)\
  what(x);\
  FOR_EACH_9(what, __VA_ARGS__);
#define FOR_EACH_11(what, x, ...)\
  what(x);\
  FOR_EACH_10(what, __VA_ARGS__);
#define FOR_EACH_12(what, x, ...)\
  what(x);\
  FOR_EACH_11(what, __VA_ARGS__);
#define FOR_EACH_13(what, x, ...)\
  what(x);\
  FOR_EACH_12(what, __VA_ARGS__);
#define FOR_EACH_14(what, x, ...)\
  what(x);\
  FOR_EACH_13(what, __VA_ARGS__);
#define FOR_EACH_15(what, x, ...)\
  what(x);\
  FOR_EACH_14(what, __VA_ARGS__);
#define FOR_EACH_16(what, x, ...)\
  what(x);\
  FOR_EACH_15(what, __VA_ARGS__);
#define FOR_EACH_17(what, x, ...)\
  what(x);\
  FOR_EACH_16(what, __VA_ARGS__);
#define FOR_EACH_18(what, x, ...)\
  what(x);\
  FOR_EACH_17(what, __VA_ARGS__);
#define FOR_EACH_19(what, x, ...)\
  what(x);\
  FOR_EACH_18(what, __VA_ARGS__);
#define FOR_EACH_20(what, x, ...)\
  what(x);\
  FOR_EACH_19(what, __VA_ARGS__);
#define FOR_EACH_21(what, x, ...)\
  what(x);\
  FOR_EACH_20(what, __VA_ARGS__);
#define FOR_EACH_22(what, x, ...)\
  what(x);\
  FOR_EACH_21(what, __VA_ARGS__);
#define FOR_EACH_23(what, x, ...)\
  what(x);\
  FOR_EACH_22(what, __VA_ARGS__);
#define FOR_EACH_24(what, x, ...)\
  what(x);\
  FOR_EACH_23(what, __VA_ARGS__);
#define FOR_EACH_25(what, x, ...)\
  what(x);\
  FOR_EACH_24(what, __VA_ARGS__);
#define FOR_EACH_26(what, x, ...)\
  what(x);\
  FOR_EACH_25(what, __VA_ARGS__);
#define FOR_EACH_27(what, x, ...)\
  what(x);\
  FOR_EACH_26(what, __VA_ARGS__);
#define FOR_EACH_28(what, x, ...)\
  what(x);\
  FOR_EACH_27(what, __VA_ARGS__);
#define FOR_EACH_29(what, x, ...)\
  what(x);\
  FOR_EACH_28(what, __VA_ARGS__);
#define FOR_EACH_30(what, x, ...)\
  what(x);\
  FOR_EACH_29(what, __VA_ARGS__);
#define FOR_EACH_31(what, x, ...)\
  what(x);\
  FOR_EACH_30(what, __VA_ARGS__);
#define FOR_EACH_32(what, x, ...)\
  what(x);\
  FOR_EACH_31(what, __VA_ARGS__);
#define FOR_EACH_33(what, x, ...)\
  what(x);\
  FOR_EACH_32(what, __VA_ARGS__);
#define FOR_EACH_34(what, x, ...)\
  what(x);\
  FOR_EACH_33(what, __VA_ARGS__);
#define FOR_EACH_35(what, x, ...)\
  what(x);\
  FOR_EACH_34(what, __VA_ARGS__);
#define FOR_EACH_36(what, x, ...)\
  what(x);\
  FOR_EACH_35(what, __VA_ARGS__);
#define FOR_EACH_37(what, x, ...)\
  what(x);\
  FOR_EACH_36(what, __VA_ARGS__);
#define FOR_EACH_38(what, x, ...)\
  what(x);\
  FOR_EACH_37(what, __VA_ARGS__);
#define FOR_EACH_39(what, x, ...)\
  what(x);\
  FOR_EACH_38(what, __VA_ARGS__);
#define FOR_EACH_40(what, x, ...)\
  what(x);\
  FOR_EACH_39(what, __VA_ARGS__);
#define FOR_EACH_41(what, x, ...)\
  what(x);\
  FOR_EACH_40(what, __VA_ARGS__);
#define FOR_EACH_42(what, x, ...)\
  what(x);\
  FOR_EACH_41(what, __VA_ARGS__);
#define FOR_EACH_43(what, x, ...)\
  what(x);\
  FOR_EACH_42(what, __VA_ARGS__);
#define FOR_EACH_44(what, x, ...)\
  what(x);\
  FOR_EACH_43(what, __VA_ARGS__);
#define FOR_EACH_45(what, x, ...)\
  what(x);\
  FOR_EACH_44(what, __VA_ARGS__);
#define FOR_EACH_46(what, x, ...)\
  what(x);\
  FOR_EACH_45(what, __VA_ARGS__);
#define FOR_EACH_47(what, x, ...)\
  what(x);\
  FOR_EACH_46(what, __VA_ARGS__);
#define FOR_EACH_48(what, x, ...)\
  what(x);\
  FOR_EACH_47(what, __VA_ARGS__);
#define FOR_EACH_49(what, x, ...)\
  what(x);\
  FOR_EACH_48(what, __VA_ARGS__);
#define FOR_EACH_50(what, x, ...)\
  what(x);\
  FOR_EACH_49(what, __VA_ARGS__);
#define FOR_EACH_51(what, x, ...)\
  what(x);\
  FOR_EACH_50(what, __VA_ARGS__);
#define FOR_EACH_52(what, x, ...)\
  what(x);\
  FOR_EACH_51(what, __VA_ARGS__);
#define FOR_EACH_53(what, x, ...)\
  what(x);\
  FOR_EACH_52(what, __VA_ARGS__);
#define FOR_EACH_54(what, x, ...)\
  what(x);\
  FOR_EACH_53(what, __VA_ARGS__);
#define FOR_EACH_55(what, x, ...)\
  what(x);\
  FOR_EACH_54(what, __VA_ARGS__);
#define FOR_EACH_56(what, x, ...)\
  what(x);\
  FOR_EACH_55(what, __VA_ARGS__);
#define FOR_EACH_57(what, x, ...)\
  what(x);\
  FOR_EACH_56(what, __VA_ARGS__);
#define FOR_EACH_58(what, x, ...)\
  what(x);\
  FOR_EACH_57(what, __VA_ARGS__);
#define FOR_EACH_59(what, x, ...)\
  what(x);\
  FOR_EACH_58(what, __VA_ARGS__);
#define FOR_EACH_60(what, x, ...)\
  what(x);\
  FOR_EACH_59(what, __VA_ARGS__);
#define FOR_EACH_61(what, x, ...)\
  what(x);\
  FOR_EACH_60(what, __VA_ARGS__);
#define FOR_EACH_62(what, x, ...)\
  what(x);\
  FOR_EACH_61(what, __VA_ARGS__);
#define FOR_EACH_63(what, x, ...)\
  what(x);\
  FOR_EACH_62(what, __VA_ARGS__);
#define FOR_EACH_64(what, x, ...)\
  what(x);\
  FOR_EACH_63(what, __VA_ARGS__);
#define FOR_EACH_(N, what, x, ...) CONCATENATE(FOR_EACH_, N)(what, x, __VA_ARGS__)
#define FOR_EACH(what, x, ...) FOR_EACH_(COUNT_ARGUMENTS(x, __VA_ARGS__), what, x, __VA_ARGS__)
#define STORE_ARGUMENT(memBlock, x, offset) memcpy(memBlock+offset, &x, sizeof(x)); offset += sizeof(x)
#define STORE_ARGUMENTS_0(memBlock, offset, ...)
#define STORE_ARGUMENTS_1(memBlock, offset, x, ...) STORE_ARGUMENT(memBlock, x, offset)
#define STORE_ARGUMENTS_2(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_1(memBlock, offset, __VA_ARGS__)
#define STORE_ARGUMENTS_3(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_2(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_4(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_3(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_5(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_4(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_6(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_5(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_7(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_6(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_8(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_7(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_9(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_8(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_10(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_9(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_11(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_10(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_12(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_11(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_13(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_12(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_14(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_13(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_15(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_14(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_16(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_15(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_17(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_16(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_18(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_17(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_19(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_18(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_20(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_19(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_21(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_20(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_22(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_21(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_23(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_22(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_24(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_23(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_25(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_24(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_26(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_25(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_27(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_26(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_28(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_27(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_29(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_28(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_30(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_29(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_31(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_30(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_32(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_31(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_33(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_32(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_34(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_33(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_35(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_34(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_36(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_35(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_37(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_36(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_38(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_37(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_39(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_38(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_40(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_39(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_41(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_40(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_42(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_41(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_43(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_42(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_44(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_43(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_45(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_44(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_46(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_45(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_47(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_46(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_48(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_47(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_49(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_48(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_50(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_49(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_51(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_50(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_52(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_51(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_53(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_52(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_54(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_53(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_55(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_54(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_56(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_55(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_57(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_56(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_58(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_57(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_59(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_58(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_60(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_59(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_61(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_60(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_62(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_61(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_63(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_62(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_64(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_63(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_(N, memBlock, offset, ...) CONCATENATE(STORE_ARGUMENTS_, N)(memBlock, offset, __VA_ARGS__)
#define STORE_ARGUMENTS(memBlock, offset, ...) STORE_ARGUMENTS_(COUNT_ARGUMENTS(__VA_ARGS__), memBlock, offset, __VA_ARGS__)
#define STORE_N_ARGUMENTS(memBlock, offset, n, ...) STORE_ARGUMENTS_(n, memBlock, offset, __VA_ARGS__)
#define FOR_EACH_SET_2_0(what, sep, ...)
#define FOR_EACH_SET_2_2(what, sep, _1,_2, ...) what(_1,_2)
#define FOR_EACH_SET_2_4(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_2(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_6(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_4(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_8(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_6(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_10(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_8(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_12(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_10(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_14(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_12(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_16(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_14(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_18(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_16(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_20(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_18(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_22(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_20(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_24(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_22(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_26(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_24(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_28(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_26(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_30(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_28(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_32(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_30(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_34(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_32(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_36(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_34(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_38(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_36(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_40(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_38(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_42(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_40(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_44(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_42(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_46(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_44(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_48(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_46(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_50(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_48(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_52(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_50(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_54(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_52(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_56(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_54(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_58(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_56(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_60(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_58(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_62(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_60(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_64(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_62(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_66(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_64(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_68(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_66(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_70(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_68(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_72(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_70(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_74(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_72(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_76(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_74(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_78(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_76(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_80(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_78(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_82(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_80(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_84(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_82(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_86(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_84(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_88(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_86(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_90(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_88(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_92(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_90(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_94(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_92(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_96(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_94(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_98(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_96(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_100(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_98(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_102(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_100(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_104(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_102(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_106(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_104(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_108(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_106(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_110(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_108(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_112(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_110(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_114(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_112(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_116(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_114(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_118(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_116(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_120(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_118(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_122(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_120(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_124(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_122(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_126(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_124(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_128(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_126(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_(N, what, sep, ...) CONCATENATE(FOR_EACH_SET_2_, N)(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2(what, sep, ...) FOR_EACH_SET_2_(COUNT_ARGUMENTS(__VA_ARGS__), what, sep, __VA_ARGS__)
#define MERGE_ARGUMENTS_IN_PAIR(a, b) MERGE_ARGUMENTS_IN_PAIR1(a, b)
#define MERGE_ARGUMENTS_IN_PAIR1(a, b) MERGE_ARGUMENTS_IN_PAIR2(a,b)
#define MERGE_ARGUMENTS_IN_PAIR2(a, b) a b
#define FILTER_FIRST_ARG_IN_PAIR(a, b) FILTER_FIRST_ARG_IN_PAIR1(a,b)
#define FILTER_FIRST_ARG_IN_PAIR1(a, b) FILTER_FIRST_ARG_IN_PAIR2(a,b)
#define FILTER_FIRST_ARG_IN_PAIR2(a, b) b
#define FILTER_SECOND_ARG_IN_PAIR(a, b) FILTER_SECOND_ARG_IN_PAIR1(a, b)
#define FILTER_SECOND_ARG_IN_PAIR1(a, b) FILTER_SECOND_ARG_IN_PAIR2(a, b)
#define FILTER_SECOND_ARG_IN_PAIR2(a, b) a
#define MERGE_ARGUMENTS_PAIRWISE(...) FOR_EACH_SET_2_(COUNT_ARGUMENTS(__VA_ARGS__), MERGE_ARGUMENTS_IN_PAIR, MAKE_COMMA, __VA_ARGS__)
#define FILTER_ODD_ARGUMENTS(...) FOR_EACH_SET_2_(COUNT_ARGUMENTS(__VA_ARGS__), FILTER_FIRST_ARG_IN_PAIR, MAKE_COMMA, __VA_ARGS__)
#define FILTER_EVEN_ARGUMENTS(...) FOR_EACH_SET_2_(COUNT_ARGUMENTS(__VA_ARGS__), FILTER_SECOND_ARG_IN_PAIR, MAKE_COMMA, __VA_ARGS__)
#endif
//#include "khash.h"
#ifndef __AC_KHASH_H
#define __AC_KHASH_H
#define AC_VERSION_KHASH_H "0.2.2"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
typedef uint32_t khint_t;
typedef khint_t khiter_t;
#define __ac_HASH_PRIME_SIZE 32
static const uint32_t __ac_prime_list[__ac_HASH_PRIME_SIZE] =
{
  0ul,          3ul,          11ul,         23ul,         53ul,
  97ul,         193ul,        389ul,        769ul,        1543ul,
  3079ul,       6151ul,       12289ul,      24593ul,      49157ul,
  98317ul,      196613ul,     393241ul,     786433ul,     1572869ul,
  3145739ul,    6291469ul,    12582917ul,   25165843ul,   50331653ul,
  100663319ul,  201326611ul,  402653189ul,  805306457ul,  1610612741ul,
  3221225473ul, 4294967291ul
};
#define __ac_isempty(flag, i) ((flag[i>>4]>>((i&0xfU)<<1))&2)
#define __ac_isdel(flag, i) ((flag[i>>4]>>((i&0xfU)<<1))&1)
#define __ac_iseither(flag, i) ((flag[i>>4]>>((i&0xfU)<<1))&3)
#define __ac_set_isdel_false(flag, i) (flag[i>>4]&=~(1ul<<((i&0xfU)<<1)))
#define __ac_set_isempty_false(flag, i) (flag[i>>4]&=~(2ul<<((i&0xfU)<<1)))
#define __ac_set_isboth_false(flag, i) (flag[i>>4]&=~(3ul<<((i&0xfU)<<1)))
#define __ac_set_isdel_true(flag, i) (flag[i>>4]|=1ul<<((i&0xfU)<<1))
static const double __ac_HASH_UPPER = 0.77;
#define KHASH_INIT(name, khkey_t, khval_t, kh_is_map, __hash_func, __hash_equal) \
  typedef struct {                          \
    khint_t n_buckets, size, n_occupied, upper_bound;       \
    uint32_t *flags;                        \
    khkey_t *keys;                          \
    khval_t *vals;                          \
  } kh_##name##_t;                          \
  static inline kh_##name##_t *kh_init_##name() {           \
    return (kh_##name##_t*)calloc(1, sizeof(kh_##name##_t));    \
  }                                 \
  static inline void kh_destroy_##name(kh_##name##_t *h)        \
  {                                 \
    if (h) {                            \
      free(h->keys); free(h->flags);                \
      free(h->vals);                        \
      free(h);                          \
    }                               \
  }                                 \
  static inline void kh_clear_##name(kh_##name##_t *h)        \
  {                                 \
    if (h && h->flags) { \
      memset(h->flags, 0xaa, ((h->n_buckets>>4) + 1) * sizeof(uint32_t)); \
      h->size = h->n_occupied = 0;                \
    }                               \
  }                                 \
  static inline khint_t kh_get_##name(kh_##name##_t *h, khkey_t key)  \
  {                                 \
    if (h->n_buckets) {                       \
      khint_t inc, k, i, last;                  \
      k = __hash_func(key); i = k % h->n_buckets;         \
      inc = 1 + k % (h->n_buckets - 1); last = i;         \
      while (!__ac_isempty(h->flags, i) && (__ac_isdel(h->flags, i) || !__hash_equal(h->keys[i], key))) { \
        if (i + inc >= h->n_buckets) i = i + inc - h->n_buckets; \
        else i += inc;                      \
        if (i == last) return h->n_buckets;           \
      }                             \
      return __ac_iseither(h->flags, i)? h->n_buckets : i;      \
    } else return 0;                        \
  }                                 \
  static inline void kh_resize_##name(kh_##name##_t *h, khint_t new_n_buckets) \
  {                                 \
    uint32_t *new_flags = 0;                    \
    khint_t j = 1;                          \
    {                               \
      khint_t t = __ac_HASH_PRIME_SIZE - 1;           \
      while (__ac_prime_list[t] > new_n_buckets) --t;       \
      new_n_buckets = __ac_prime_list[t+1];           \
      if (h->size >= (khint_t)(new_n_buckets * __ac_HASH_UPPER + 0.5)) j = 0; \
      else {                            \
        new_flags = (uint32_t*)malloc(((new_n_buckets>>4) + 1) * sizeof(uint32_t)); \
        memset(new_flags, 0xaa, ((new_n_buckets>>4) + 1) * sizeof(uint32_t)); \
        if (h->n_buckets < new_n_buckets) {           \
          h->keys = (khkey_t*)realloc(h->keys, new_n_buckets * sizeof(khkey_t)); \
          if (kh_is_map)                    \
            h->vals = (khval_t*)realloc(h->vals, new_n_buckets * sizeof(khval_t)); \
        }                           \
      }                             \
    }                               \
    if (j) {                            \
      for (j = 0; j != h->n_buckets; ++j) {           \
        if (__ac_iseither(h->flags, j) == 0) {          \
          khkey_t key = h->keys[j];             \
          khval_t val;                    \
          if (kh_is_map) val = h->vals[j];          \
          __ac_set_isdel_true(h->flags, j);         \
          while (1) {                     \
            khint_t inc, k, i;                \
            k = __hash_func(key);             \
            i = k % new_n_buckets;              \
            inc = 1 + k % (new_n_buckets - 1);        \
            while (!__ac_isempty(new_flags, i)) {     \
              if (i + inc >= new_n_buckets) i = i + inc - new_n_buckets; \
              else i += inc;                \
            }                       \
            __ac_set_isempty_false(new_flags, i);     \
            if (i < h->n_buckets && __ac_iseither(h->flags, i) == 0) { \
              { khkey_t tmp = h->keys[i]; h->keys[i] = key; key = tmp; } \
              if (kh_is_map) { khval_t tmp = h->vals[i]; h->vals[i] = val; val = tmp; } \
              __ac_set_isdel_true(h->flags, i);     \
            } else {                    \
              h->keys[i] = key;             \
              if (kh_is_map) h->vals[i] = val;      \
              break;                    \
            }                       \
          }                         \
        }                           \
      }                             \
      if (h->n_buckets > new_n_buckets) {             \
        h->keys = (khkey_t*)realloc(h->keys, new_n_buckets * sizeof(khkey_t)); \
        if (kh_is_map)                      \
          h->vals = (khval_t*)realloc(h->vals, new_n_buckets * sizeof(khval_t)); \
      }                             \
      free(h->flags);                       \
      h->flags = new_flags;                   \
      h->n_buckets = new_n_buckets;               \
      h->n_occupied = h->size;                  \
      h->upper_bound = (khint_t)(h->n_buckets * __ac_HASH_UPPER + 0.5); \
    }                               \
  }                                 \
  static inline khint_t kh_put_##name(kh_##name##_t *h, khkey_t key, int *ret) \
  {                                 \
    khint_t x;                            \
    if (h->n_occupied >= h->upper_bound) {              \
      if (h->n_buckets > (h->size<<1)) kh_resize_##name(h, h->n_buckets - 1); \
      else kh_resize_##name(h, h->n_buckets + 1);         \
    }                               \
    {                               \
      khint_t inc, k, i, site, last;                \
      x = site = h->n_buckets; k = __hash_func(key); i = k % h->n_buckets; \
      if (__ac_isempty(h->flags, i)) x = i;           \
      else {                            \
        inc = 1 + k % (h->n_buckets - 1); last = i;       \
        while (!__ac_isempty(h->flags, i) && (__ac_isdel(h->flags, i) || !__hash_equal(h->keys[i], key))) { \
          if (__ac_isdel(h->flags, i)) site = i;        \
          if (i + inc >= h->n_buckets) i = i + inc - h->n_buckets; \
          else i += inc;                    \
          if (i == last) { x = site; break; }         \
        }                           \
        if (x == h->n_buckets) {                \
          if (__ac_isempty(h->flags, i) && site != h->n_buckets) x = site; \
          else x = i;                     \
        }                           \
      }                             \
    }                               \
    if (__ac_isempty(h->flags, x)) {                \
      h->keys[x] = key;                     \
      __ac_set_isboth_false(h->flags, x);             \
      ++h->size; ++h->n_occupied;                 \
      *ret = 1;                         \
    } else if (__ac_isdel(h->flags, x)) {             \
      h->keys[x] = key;                     \
      __ac_set_isboth_false(h->flags, x);             \
      ++h->size;                          \
      *ret = 2;                         \
    } else *ret = 0;                        \
    return x;                           \
  }                                 \
  static inline void kh_del_##name(kh_##name##_t *h, khint_t x)   \
  {                                 \
    if (x != h->n_buckets && !__ac_iseither(h->flags, x)) {     \
      __ac_set_isdel_true(h->flags, x);             \
      --h->size;                          \
    }                               \
  }
#define kh_int_hash_func(key) (uint32_t)(key)
#define kh_int_hash_equal(a, b) (a == b)
#define kh_int64_hash_func(key) (uint32_t)((key)>>33^(key)^(key)<<11)
#define kh_int64_hash_equal(a, b) (a == b)
static inline khint_t __ac_X31_hash_string(const char *s)
{
  khint_t h = *s;
  if (h) for (++s ; *s; ++s) h = (h << 5) - h + *s;
  return h;
}
#define kh_str_hash_func(key) __ac_X31_hash_string(key)
#define kh_str_hash_equal(a, b) (strcmp(a, b) == 0)
#define khash_t(name) kh_##name##_t
#define kh_init(name) kh_init_##name()
#define kh_destroy(name, h) kh_destroy_##name(h)
#define kh_clear(name, h) kh_clear_##name(h)
#define kh_resize(name, h, s) kh_resize_##name(h, s)
#define kh_put(name, h, k, r) kh_put_##name(h, k, r)
#define kh_get(name, h, k) kh_get_##name(h, k)
#define kh_del(name, h, k) kh_del_##name(h, k)
#define kh_exist(h, x) (!__ac_iseither((h)->flags, (x)))
#define kh_key(h, x) ((h)->keys[x])
#define kh_val(h, x) ((h)->vals[x])
#define kh_value(h, x) ((h)->vals[x])
#define kh_begin(h) (khint_t)(0)
#define kh_end(h) ((h)->n_buckets)
#define kh_size(h) ((h)->size)
#define kh_n_buckets(h) ((h)->n_buckets)
#define KHASH_SET_INIT_INT(name)                    \
  KHASH_INIT(name, uint32_t, char, 0, kh_int_hash_func, kh_int_hash_equal)
#define KHASH_MAP_INIT_INT(name, khval_t)               \
  KHASH_INIT(name, uint32_t, khval_t, 1, kh_int_hash_func, kh_int_hash_equal)
#define KHASH_SET_INIT_INT64(name)                    \
  KHASH_INIT(name, uint64_t, char, 0, kh_int64_hash_func, kh_int64_hash_equal)
#define KHASH_MAP_INIT_INT64(name, khval_t)               \
  KHASH_INIT(name, uint64_t, khval_t, 1, kh_int64_hash_func, kh_int64_hash_equal)
typedef const char *kh_cstr_t;
#define KHASH_SET_INIT_STR(name)                    \
  KHASH_INIT(name, kh_cstr_t, char, 0, kh_str_hash_func, kh_str_hash_equal)
#define KHASH_MAP_INIT_STR(name, khval_t)               \
  KHASH_INIT(name, kh_cstr_t, khval_t, 1, kh_str_hash_func, kh_str_hash_equal)
#endif
#define MEMOIZATION_VERBOSITY 0
#define MAX_NUM_CONTEXTS 8
#define LARGEST_ARGSIZE_EXPECTED 256
#define HASH_ALGORITHM_SEED 0
typedef void (*memoization_function_pointer)(void);
typedef struct S_FUNCTION_MEMOIZATION_SIGNATURE{
  memoization_function_pointer functionPointer;
  unsigned int numArgs;
  unsigned int sizeOfArgs;
  uint32_t key;
  void* argumentKey;
} FUNCTION_MEMOIZATION_SIGNATURE;
static inline unsigned int cmp_memoization_signatures(FUNCTION_MEMOIZATION_SIGNATURE* functSig1, FUNCTION_MEMOIZATION_SIGNATURE* functSig2){
  return ((functSig1->functionPointer == functSig2->functionPointer) &&
      (functSig1->sizeOfArgs == functSig2->sizeOfArgs) &&
      memcmp(functSig1->argumentKey, functSig2->argumentKey, functSig1->sizeOfArgs)==0);
}
static inline uint32_t hash_memoization_signature(FUNCTION_MEMOIZATION_SIGNATURE* functSig){
  return functSig->key;
}
inline uint32_t calc_hash_memoization_signature(memoization_function_pointer functPointer, unsigned int numArgs, unsigned int sizeOfArgs, void* argumentData);
#define kh_memoization_hash_func(key) (hash_memoization_signature(key))
#define kh_memoization_hash_equal(a, b) (cmp_memoization_signatures(a, b))
#define MEMOIZATION_CONTEXT_MAP_INIT(name)                \
  KHASH_INIT(name, FUNCTION_MEMOIZATION_SIGNATURE*, void*, 1, kh_memoization_hash_func, kh_memoization_hash_equal)
MEMOIZATION_CONTEXT_MAP_INIT(MEMO_CACHE)
#define MEMOIZED_FUNCT(CONTEXT_ID, RETURN_TYPE, FUNCT_NAME, ...)                        \
      RETURN_TYPE FUNCT_NAME ## _MEMOIZED_CONTEXT_ ## CONTEXT_ID (MERGE_ARGUMENTS_PAIRWISE(__VA_ARGS__)); \
                                                        \
      RETURN_TYPE FUNCT_NAME (MERGE_ARGUMENTS_PAIRWISE(__VA_ARGS__)){                   \
        if (isGlobalMemoizationContextEnabled((unsigned int)CONTEXT_ID)) {                \
          unsigned int numArgs = COUNT_ARGUMENTS(__VA_ARGS__)/2;                    \
          unsigned long offset = 0;                                 \
          void* argumentKey = NULL;                                   \
          FUNCTION_MEMOIZATION_SIGNATURE* functSig;                         \
          int fetchExitCode, setExitCode;                               \
          RETURN_TYPE returnVal;                                    \
          void* returnValPtr = NULL;                                  \
          argumentKey = malloc(sizeof(numArgs) + SIZE_OF_ARGS(FILTER_ODD_ARGUMENTS(__VA_ARGS__)));  \
          STORE_ARGUMENT(argumentKey, numArgs, offset);                       \
          if (numArgs > 0) {                                      \
            STORE_ARGUMENTS(argumentKey, offset, FILTER_ODD_ARGUMENTS(__VA_ARGS__));        \
          }                                             \
          functSig = makeMemoizationSignature((memoization_function_pointer)FUNCT_NAME,         \
                            numArgs,                        \
                            sizeof(numArgs) + SIZE_OF_ARGS(FILTER_ODD_ARGUMENTS(__VA_ARGS__)),\
                            argumentKey);                     \
          returnValPtr = fetchMemoizationCacheValue(CONTEXT_ID, functSig, &fetchExitCode);      \
          if (fetchExitCode == 0){                                  \
            freeMemoizationSignature(functSig);                           \
            returnVal = *((RETURN_TYPE*)returnValPtr);                        \
            return returnVal;                                   \
          } else {                                          \
            returnVal = FUNCT_NAME ## _MEMOIZED_CONTEXT_ ## CONTEXT_ID (FILTER_ODD_ARGUMENTS(__VA_ARGS__)); \
            returnValPtr = malloc(sizeof(RETURN_TYPE));                       \
            memcpy(returnValPtr, &returnVal, sizeof(RETURN_TYPE));                  \
            setExitCode = setMemoizationCacheValue(CONTEXT_ID, functSig, returnValPtr);       \
            if (setExitCode != 0){                                  \
              free(returnValPtr);                                 \
              freeMemoizationSignature(functSig);                         \
            }                                           \
            return returnVal;                                   \
          }                                             \
        } else {                                            \
          return FUNCT_NAME ## _MEMOIZED_CONTEXT_ ## CONTEXT_ID (FILTER_ODD_ARGUMENTS(__VA_ARGS__));  \
        }                                               \
      }                                                 \
                                                        \
      RETURN_TYPE FUNCT_NAME ## _MEMOIZED_CONTEXT_ ## CONTEXT_ID (MERGE_ARGUMENTS_PAIRWISE(__VA_ARGS__))
typedef struct S_MEMOIZATION_DATA_CONTAINER{
  unsigned int numContexts;
  int* isContextEnabled;
  int* isCacheDirty;
  khash_t(MEMO_CACHE)** contexts;
} MEMOIZATION_DATA_CONTAINER;
void initGlobalMemoizationContexts();
int isGlobalMemoizationContextEnabled(unsigned int contextID);
int isGlobalMemoizationContextDirty(unsigned int contextID);
void enableGlobalMemoizationContext(unsigned int contextID);
void disableGlobalMemoizationContext(unsigned int contextID);
void clearGlobalMemoizationContexts();
void clearGlobalMemoizationContext(unsigned int contextID);
void freeGlobalMemoizationContexts();
MEMOIZATION_DATA_CONTAINER* newMemoizationContainer(unsigned int numContexts);
int isMemoizationContextEnabled(MEMOIZATION_DATA_CONTAINER* container, unsigned int contextID);
int isMemoizationContextDirty(MEMOIZATION_DATA_CONTAINER* container, unsigned int contextID);
void enableMemoizationContext(MEMOIZATION_DATA_CONTAINER* container, unsigned int contextID);
void disableMemoizationContext(MEMOIZATION_DATA_CONTAINER* container, unsigned int contextID);
void clearMemoizationContainer(MEMOIZATION_DATA_CONTAINER* container);
void freeMemoizationContainer(MEMOIZATION_DATA_CONTAINER* container);
void clearMemoizationContext(MEMOIZATION_DATA_CONTAINER* container, unsigned int contextID);
FUNCTION_MEMOIZATION_SIGNATURE* makeMemoizationSignature(memoization_function_pointer functPointer, unsigned int numArgs, unsigned int sizeOfArgs, void* argumentData);
void clearMemoizationSignatureInternalData(FUNCTION_MEMOIZATION_SIGNATURE* functSig);
void freeMemoizationSignature(FUNCTION_MEMOIZATION_SIGNATURE* memoizationSig);
int setMemoizationCacheValue(unsigned int contextID, FUNCTION_MEMOIZATION_SIGNATURE* functSig, void* returnVal);
void* fetchMemoizationCacheValue(unsigned int contextID, FUNCTION_MEMOIZATION_SIGNATURE* functSig,  int* exitCode);
#endif
// #include "murmur_hash3.h"
#ifndef _MURMURHASH3_H_
#define _MURMURHASH3_H_
#if defined(_MSC_VER)
typedef unsigned char uint8_t;
typedef unsigned long uint32_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif
void MurmurHash3_x86_32  ( const void * key, int len, uint32_t seed, void * out );
void MurmurHash3_x86_128 ( const void * key, int len, uint32_t seed, void * out );
void MurmurHash3_x64_128 ( const void * key, int len, uint32_t seed, void * out );
#endif
#if defined(_MSC_VER)
#define FORCE_INLINE	__forceinline
#include <stdlib.h>
#define ROTL32(x,y)	_rotl(x,y)
#define ROTL64(x,y)	_rotl64(x,y)
#define BIG_CONSTANT(x) (x)
#else
#define	FORCE_INLINE __attribute__((always_inline))
inline uint32_t rotl32 ( uint32_t x, int8_t r )
{
  return (x << r) | (x >> (32 - r));
}
#define	ROTL32(x,y)	rotl32(x,y)
#if defined(uint64_t)
inline uint64_t rotl64 ( uint64_t x, int8_t r )
{
  return (x << r) | (x >> (64 - r));
}
#define ROTL64(x,y)	rotl64(x,y)
#endif
#define BIG_CONSTANT(x) (x##LLU)
#endif
FORCE_INLINE uint32_t getblock32 ( const uint32_t * p, int i )
{
  return p[i];
}
#if defined(uint64_t)
FORCE_INLINE uint64_t getblock64 ( const uint64_t * p, int i )
{
  return p[i];
}
#endif
FORCE_INLINE uint32_t fmix32 ( uint32_t h )
{
  h ^= h >> 16;
  h *= 0x85ebca6b;
  h ^= h >> 13;
  h *= 0xc2b2ae35;
  h ^= h >> 16;
  return h;
}
#if defined(uint64_t)
FORCE_INLINE uint64_t fmix64 ( uint64_t k )
{
  k ^= k >> 33;
  k *= BIG_CONSTANT(0xff51afd7ed558ccd);
  k ^= k >> 33;
  k *= BIG_CONSTANT(0xc4ceb9fe1a85ec53);
  k ^= k >> 33;
  return k;
}
#endif
void MurmurHash3_x86_32 ( const void * key, int len, uint32_t seed, void * out )
{
  const uint8_t * data = (const uint8_t*)key;
  const int nblocks = len / 4;
  uint32_t h1 = seed;
  uint32_t c1 = 0xcc9e2d51;
  uint32_t c2 = 0x1b873593;
  const uint32_t * blocks = (const uint32_t *)(data + nblocks*4);
  int i;
  for(i=-nblocks; i; i++)
  {
    uint32_t k1 = getblock32(blocks,i);
    k1 *= c1;
    k1 = ROTL32(k1,15);
    k1 *= c2;
    h1 ^= k1;
    h1 = ROTL32(h1,13);
    h1 = h1*5+0xe6546b64;
  }
  const uint8_t * tail = (const uint8_t*)(data + nblocks*4);
  uint32_t k1 = 0;
  switch(len & 3)
  {
  case 3: k1 ^= tail[2] << 16;
  case 2: k1 ^= tail[1] << 8;
  case 1: k1 ^= tail[0];
          k1 *= c1; k1 = ROTL32(k1,15); k1 *= c2; h1 ^= k1;
  };
  h1 ^= len;
  h1 = fmix32(h1);
  *(uint32_t*)out = h1;
}
void MurmurHash3_x86_128 ( const void * key, const int len, uint32_t seed, void * out ){
  const uint8_t * data = (const uint8_t*)key;
  const int nblocks = len / 16;
  uint32_t h1 = seed;
  uint32_t h2 = seed;
  uint32_t h3 = seed;
  uint32_t h4 = seed;
  uint32_t c1 = 0x239b961b;
  uint32_t c2 = 0xab0e9789;
  uint32_t c3 = 0x38b34ae5;
  uint32_t c4 = 0xa1e38b93;
  const uint32_t * blocks = (const uint32_t *)(data + nblocks*16);
  int i;
  for(i=-nblocks; i; i++)
  {
    uint32_t k1 = getblock32(blocks,i*4+0);
    uint32_t k2 = getblock32(blocks,i*4+1);
    uint32_t k3 = getblock32(blocks,i*4+2);
    uint32_t k4 = getblock32(blocks,i*4+3);
    k1 *= c1; k1  = ROTL32(k1,15); k1 *= c2; h1 ^= k1;
    h1 = ROTL32(h1,19); h1 += h2; h1 = h1*5+0x561ccd1b;
    k2 *= c2; k2  = ROTL32(k2,16); k2 *= c3; h2 ^= k2;
    h2 = ROTL32(h2,17); h2 += h3; h2 = h2*5+0x0bcaa747;
    k3 *= c3; k3  = ROTL32(k3,17); k3 *= c4; h3 ^= k3;
    h3 = ROTL32(h3,15); h3 += h4; h3 = h3*5+0x96cd1c35;
    k4 *= c4; k4  = ROTL32(k4,18); k4 *= c1; h4 ^= k4;
    h4 = ROTL32(h4,13); h4 += h1; h4 = h4*5+0x32ac3b17;
  }
  const uint8_t * tail = (const uint8_t*)(data + nblocks*16);
  uint32_t k1 = 0;
  uint32_t k2 = 0;
  uint32_t k3 = 0;
  uint32_t k4 = 0;
  switch(len & 15)
  {
  case 15: k4 ^= tail[14] << 16;
  case 14: k4 ^= tail[13] << 8;
  case 13: k4 ^= tail[12] << 0;
           k4 *= c4; k4  = ROTL32(k4,18); k4 *= c1; h4 ^= k4;
  case 12: k3 ^= tail[11] << 24;
  case 11: k3 ^= tail[10] << 16;
  case 10: k3 ^= tail[ 9] << 8;
  case  9: k3 ^= tail[ 8] << 0;
           k3 *= c3; k3  = ROTL32(k3,17); k3 *= c4; h3 ^= k3;
  case  8: k2 ^= tail[ 7] << 24;
  case  7: k2 ^= tail[ 6] << 16;
  case  6: k2 ^= tail[ 5] << 8;
  case  5: k2 ^= tail[ 4] << 0;
           k2 *= c2; k2  = ROTL32(k2,16); k2 *= c3; h2 ^= k2;
  case  4: k1 ^= tail[ 3] << 24;
  case  3: k1 ^= tail[ 2] << 16;
  case  2: k1 ^= tail[ 1] << 8;
  case  1: k1 ^= tail[ 0] << 0;
           k1 *= c1; k1  = ROTL32(k1,15); k1 *= c2; h1 ^= k1;
  };
  h1 ^= len; h2 ^= len; h3 ^= len; h4 ^= len;
  h1 += h2; h1 += h3; h1 += h4;
  h2 += h1; h3 += h1; h4 += h1;
  h1 = fmix32(h1);
  h2 = fmix32(h2);
  h3 = fmix32(h3);
  h4 = fmix32(h4);
  h1 += h2; h1 += h3; h1 += h4;
  h2 += h1; h3 += h1; h4 += h1;
  ((uint32_t*)out)[0] = h1;
  ((uint32_t*)out)[1] = h2;
  ((uint32_t*)out)[2] = h3;
  ((uint32_t*)out)[3] = h4;
}
#if defined(uint64_t)
void MurmurHash3_x64_128 ( const void * key, const int len,
                           const uint32_t seed, void * out )
{
  const uint8_t * data = (const uint8_t*)key;
  const int nblocks = len / 16;
  uint64_t h1 = seed;
  uint64_t h2 = seed;
  uint64_t c1 = BIG_CONSTANT(0x87c37b91114253d5);
  uint64_t c2 = BIG_CONSTANT(0x4cf5ad432745937f);
  const uint64_t * blocks = (const uint64_t *)(data);
  int i;
  for(i=0; i < nblocks; i++)
  {
    uint64_t k1 = getblock64(blocks,i*2+0);
    uint64_t k2 = getblock64(blocks,i*2+1);
    k1 *= c1; k1  = ROTL64(k1,31); k1 *= c2; h1 ^= k1;
    h1 = ROTL64(h1,27); h1 += h2; h1 = h1*5+0x52dce729;
    k2 *= c2; k2  = ROTL64(k2,33); k2 *= c1; h2 ^= k2;
    h2 = ROTL64(h2,31); h2 += h1; h2 = h2*5+0x38495ab5;
  }
  const uint8_t * tail = (const uint8_t*)(data + nblocks*16);
  uint64_t k1 = 0;
  uint64_t k2 = 0;
  switch(len & 15)
  {
  case 15: k2 ^= uint64_t(tail[14]) << 48;
  case 14: k2 ^= uint64_t(tail[13]) << 40;
  case 13: k2 ^= uint64_t(tail[12]) << 32;
  case 12: k2 ^= uint64_t(tail[11]) << 24;
  case 11: k2 ^= uint64_t(tail[10]) << 16;
  case 10: k2 ^= uint64_t(tail[ 9]) << 8;
  case  9: k2 ^= uint64_t(tail[ 8]) << 0;
           k2 *= c2; k2  = ROTL64(k2,33); k2 *= c1; h2 ^= k2;
  case  8: k1 ^= uint64_t(tail[ 7]) << 56;
  case  7: k1 ^= uint64_t(tail[ 6]) << 48;
  case  6: k1 ^= uint64_t(tail[ 5]) << 40;
  case  5: k1 ^= uint64_t(tail[ 4]) << 32;
  case  4: k1 ^= uint64_t(tail[ 3]) << 24;
  case  3: k1 ^= uint64_t(tail[ 2]) << 16;
  case  2: k1 ^= uint64_t(tail[ 1]) << 8;
  case  1: k1 ^= uint64_t(tail[ 0]) << 0;
           k1 *= c1; k1  = ROTL64(k1,31); k1 *= c2; h1 ^= k1;
  };
  h1 ^= len; h2 ^= len;
  h1 += h2;
  h2 += h1;
  h1 = fmix64(h1);
  h2 = fmix64(h2);
  h1 += h2;
  h2 += h1;
  ((uint64_t*)out)[0] = h1;
  ((uint64_t*)out)[1] = h2;
}
#endif
/////////////
MEMOIZATION_DATA_CONTAINER* MEMOIZATION_DATA_CACHE = NULL;
void freeMemoizationContext(MEMOIZATION_DATA_CONTAINER* container, unsigned int contextID);
void clearMemoizationContextInternalData(MEMOIZATION_DATA_CONTAINER* container, unsigned int contextID);
MEMOIZATION_DATA_CONTAINER* newMemoizationContainer(unsigned int numContexts){
	unsigned int i;
	MEMOIZATION_DATA_CONTAINER* container = malloc(sizeof(MEMOIZATION_DATA_CONTAINER));
	container->numContexts = numContexts;
	container->contexts = calloc(numContexts, sizeof(khash_t(MEMO_CACHE)*));
	container->isContextEnabled = calloc(numContexts, sizeof(int));
	container->isCacheDirty = calloc(numContexts, sizeof(int));
	for (i=0; i<numContexts; i++){
		container->isContextEnabled[i] = 0;
		container->isCacheDirty[i] = 0;
		container->contexts[i] = kh_init(MEMO_CACHE);
	}
	return container;
}
int isMemoizationContextEnabled(MEMOIZATION_DATA_CONTAINER* container, unsigned int contextID){
	return ((contextID < container->numContexts) && container->isContextEnabled[contextID]);
}
int isMemoizationContextDirty(MEMOIZATION_DATA_CONTAINER* container, unsigned int contextID){
	return ((contextID < container->numContexts) && container->isCacheDirty[contextID]);
}
void enableMemoizationContext(MEMOIZATION_DATA_CONTAINER* container, unsigned int contextID){
	if (contextID < container->numContexts){
		container->isContextEnabled[contextID] = 1;
		container->isCacheDirty[contextID] = 1;
	}
}
void disableMemoizationContext(MEMOIZATION_DATA_CONTAINER* container, unsigned int contextID){
	if (contextID < container->numContexts){
		container->isContextEnabled[contextID] = 0;
	}
}
void setAllMemoizationContextsIsEnabled(MEMOIZATION_DATA_CONTAINER* container, int isEnabled){
	int i;
	if (isEnabled){
		for (i=0; i<container->numContexts; i++){
			enableMemoizationContext(container, i);
		}
	} else {
		for (i=0; i<container->numContexts; i++){
			disableMemoizationContext(container, i);
		}
	}
}
void clearMemoizationContainer(MEMOIZATION_DATA_CONTAINER* container){
	unsigned int i;
	for (i=0; i < container->numContexts; i++){
		clearMemoizationContext(container, i);
	}
}
void freeMemoizationContainer(MEMOIZATION_DATA_CONTAINER* container){
	unsigned int i;
	for (i=0; i < container->numContexts; i++){
		freeMemoizationContext(container, i);
	}
	free(container->isCacheDirty);
	free(container->isContextEnabled);
	free(container->contexts);
	free(container);
}
void clearMemoizationContext(MEMOIZATION_DATA_CONTAINER* container, unsigned int contextID){
	if (contextID < container->numContexts){
		clearMemoizationContextInternalData(container, contextID);
		khash_t(MEMO_CACHE)* context = container->contexts[contextID];
		kh_clear(MEMO_CACHE, context);
		if (!container->isContextEnabled[contextID]){
			container->isCacheDirty[contextID] = 0;
		}
	}
}
void freeMemoizationContext(MEMOIZATION_DATA_CONTAINER* container, unsigned int contextID){
	if (contextID < container->numContexts){
		clearMemoizationContextInternalData(container, contextID);
		khash_t(MEMO_CACHE)* context = container->contexts[contextID];
		kh_destroy(MEMO_CACHE, context);
		container->contexts[contextID] = NULL;
	}
}
void clearMemoizationContextInternalData(MEMOIZATION_DATA_CONTAINER* container, unsigned int contextID){
	if (contextID < container->numContexts){
		int i;
		khash_t(MEMO_CACHE)* context = container->contexts[contextID];
		for (i=kh_begin(context); i < kh_end(context); i++){
			if (kh_exist(context, i)) {
				clearMemoizationSignatureInternalData(kh_key(context, i));
				free(kh_key(context, i));
				free(kh_value(context, i));
			}
		}
	}
}
void initGlobalMemoizationContexts(){
	MEMOIZATION_DATA_CACHE = newMemoizationContainer(MAX_NUM_CONTEXTS);
}
int isGlobalMemoizationContextEnabled(unsigned int contextID){
	return isMemoizationContextEnabled(MEMOIZATION_DATA_CACHE, contextID);
}
int isGlobalMemoizationContextDirty(unsigned int contextID){
	return isMemoizationContextDirty(MEMOIZATION_DATA_CACHE, contextID);
}
void enableGlobalMemoizationContext(unsigned int contextID){
	enableMemoizationContext(MEMOIZATION_DATA_CACHE, contextID);
}
void disableGlobalMemoizationContext(unsigned int contextID){
	disableMemoizationContext(MEMOIZATION_DATA_CACHE, contextID);
}
void clearGlobalMemoizationContexts(){
	clearMemoizationContainer(MEMOIZATION_DATA_CACHE);
}
void clearGlobalMemoizationContext(unsigned int contextID){
	clearMemoizationContext(MEMOIZATION_DATA_CACHE, contextID);
}
void freeGlobalMemoizationContexts(){
	freeMemoizationContainer(MEMOIZATION_DATA_CACHE);
	MEMOIZATION_DATA_CACHE = NULL;
}
inline uint32_t calc_hash_memoization_signature(memoization_function_pointer functPointer, unsigned int numArgs, unsigned int sizeOfArgs, void* argumentData){
	uint32_t hashInputLen = SIZE_OF_ARGS(functPointer, numArgs, sizeOfArgs) + sizeOfArgs;
	void* hashInput = malloc(hashInputLen);
	uint32_t key = 0;
	uint32_t offset = 0;
	hashInput = STORE_ARGUMENTS(hashInput, offset, functPointer, sizeOfArgs);
	memcpy(hashInput+offset, argumentData, sizeOfArgs);
	MurmurHash3_x86_32(hashInput, hashInputLen, HASH_ALGORITHM_SEED, &key);
	free(hashInput);
	return key;
}
FUNCTION_MEMOIZATION_SIGNATURE* makeMemoizationSignature(memoization_function_pointer functPointer, unsigned int numArgs, unsigned int sizeOfArgs, void* argumentData){
	FUNCTION_MEMOIZATION_SIGNATURE* functSig = malloc(sizeof(FUNCTION_MEMOIZATION_SIGNATURE));
	uint32_t key = calc_hash_memoization_signature(functPointer, numArgs, sizeOfArgs, argumentData);
	functSig->functionPointer = functPointer;
	functSig->numArgs = numArgs;
	functSig->sizeOfArgs = sizeOfArgs;
	functSig->key = key;
	functSig->argumentKey = argumentData;
	return functSig;
}
void clearMemoizationSignatureInternalData(FUNCTION_MEMOIZATION_SIGNATURE* functSig){
	free(functSig->argumentKey);
}
void freeMemoizationSignature(FUNCTION_MEMOIZATION_SIGNATURE* functSig){
	clearMemoizationSignatureInternalData(functSig);
	free(functSig);
}
int setMemoizationCacheValue(unsigned int contextID, FUNCTION_MEMOIZATION_SIGNATURE* functSig, void* returnVal){
	int exitCode;
	MEMOIZATION_DATA_CONTAINER* container = MEMOIZATION_DATA_CACHE;
	if (contextID < container->numContexts  && container->contexts[contextID] != NULL){
		int hashExitCode;
		khint_t hashIndex = kh_put(MEMO_CACHE, container->contexts[contextID], functSig, &hashExitCode);
		if (hashExitCode != 0){
			exitCode = 0;
			kh_value(container->contexts[contextID], hashIndex) = returnVal;
		} else {
			exitCode = -1;
		}
	} else {
		exitCode = -1;
	}
	return exitCode;
}
void* fetchMemoizationCacheValue(unsigned int contextID, FUNCTION_MEMOIZATION_SIGNATURE* functSig,  int* exitCode){
	void* returnVal = NULL;
	MEMOIZATION_DATA_CONTAINER* container = MEMOIZATION_DATA_CACHE;
	if ((contextID < container->numContexts) && container->contexts[contextID] != NULL){
		khint_t hashIndex = kh_get(MEMO_CACHE, container->contexts[contextID], functSig);
		if ((hashIndex < kh_n_buckets(container->contexts[contextID])) &&
			(kh_exist(container->contexts[contextID], hashIndex))){
			*exitCode = 0;
			returnVal = kh_value(container->contexts[contextID], hashIndex);
		} else {
			*exitCode=-1;
		}
	} else {
		*exitCode=-1;
	}
	return returnVal;
}
//#include"memoization.h"
#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
int n, d[1200][1200];
vec  adj[1200];
int  par[2000], joins;
int root(int x){
  if(par[x] != x)
     par[x] = root(par[x]);
  return par[x];
}
void join(int a, int b){
  pb(adj[a], b);
  pb(adj[b], a);
  par[root(a)] = b;
  ++joins;
}
bool same(int a, int b){
  return root(a) == root(b);
}
void findjoin(int u) {
  for (int v = 0; v < u; ++v) {
    if (same(u, v))
      continue;
    int x = -1, ok = true;
    for (int k = 0; ok && k < n; ++k) {
      if (u == k || v == k)
        continue;
      int y = (d[u][v]+d[u][k]-d[v][k])/2;
      if (same(u, k))
        ok = y == 0;
      else if (same(v, k))
        ok = y == d[u][v];
      else if (x == -1) x = y;
      else ok = x == y;
    }
    if (ok){
      for (int k = 0; k < n; ++k)
        d[k][n] = d[n][k] = d[u][k] + (same(u, k) ? x : -x);
      join(u, n);
      join(v, n);
      ++n;
    }
  }
}
MEMOIZED_FUNCT(0, int, Size, int, u, int, p){
  int r;
  if (!r && (r = 1)){
    for(int z=0;z<adj[u].sz;z++){int v = adj[u].ptr[z];
      if(v != p)
        r += Size(v, u) + d[u][v]-1;
    }
  }
  return r;
}
MEMOIZED_FUNCT(0, double, DistB, int, u, int, p){
  double r;
  if(r == 0 && (r = 1))
    for(int z=0;z<adj[u].sz;z++){int v = adj[u].ptr[z];
      if (v != p)
        r += d[u][v]*((d[u][v]-1)/2.0 + Size(v, u)) + DistB(v, u);
    }
  return r-1;
}
int main(){
  initGlobalMemoizationContexts(); enableGlobalMemoizationContext(0);
  scanf("%d", &n);
  for(int i = 0; i < n; ++i){
    d[i][i] = 0;
    for(int j = i+1; j < n; ++j)
      scanf("%d", d[i]+j), d[j][i] = d[i][j];
  }
  for(int i = 0; i < 2*n; ++i)
    par[i] = i;
  while(joins < n-1)
    for(int u = 0; u < n; ++u)
      findjoin(u);
  double totd = 0, tots = Size(0, -1);
  for (int u = 0; u < n; ++u){
    totd += DistB(u, -1);
    for(int z=0;z<adj[u].sz;z++){int v = adj[u].ptr[z];
      if (u < v)
        continue;
      totd += ((DistB(u,v) + DistB(v,u))*(d[u][v]-1) +
           1.0*(Size(u,v) + Size(v,u))*d[u][v]*(d[u][v]-1)/2 +
           1.0*d[u][v]*(d[u][v]-1)*(d[u][v]-2)/3);
    }
  }
  printf("%.10lf\n", totd/(tots*(tots-1)));
  disableGlobalMemoizationContext(0); freeGlobalMemoizationContexts();
  return 0;
}