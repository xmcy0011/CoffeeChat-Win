/** @file core_dll.h
  * @brief core_dll
  * @author fei.xu
  * @date 2020/8/26
  */

#ifndef _CORE_DLL_10DCD627_AE3C_4AFA_831B_4C70E61538F4_
#define _CORE_DLL_10DCD627_AE3C_4AFA_831B_4C70E61538F4_

// 定义导出宏

#ifdef CIM_DLL_EXPORTS
#define	CIM_DLL_API __declspec(dllexport)
#else
#define	CIM_DLL_API __declspec(dllimport)
#endif


#endif//_CORE_DLL_10DCD627_AE3C_4AFA_831B_4C70E61538F4_