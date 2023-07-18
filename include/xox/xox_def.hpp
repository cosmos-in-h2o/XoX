#ifndef XOX_DEF_HPP
#define XOX_DEF_HPP

#ifndef _STR
#define _STR(m_x) #m_x
#define _MKSTR(m_x) _STR(m_x)
#endif

//编译器为MSVC
#ifdef _MSC_VER
	//导出时
	#ifdef XOX_EXPORT
		#define XOX_API __declspec(dllexport)
	#else
		#define XOX_API __declspec(dllimport)
	#endif
#else
	#define XOX_API
#endif

//一些宏函数
//用于快速写类的get与set的函数
#define CLASS_GET(CLASS,VAR) \
	inline const decltype(CLASS::VAR)& CLASS::get_##VAR()const{return this->VAR;}
#define CLASS_SET(CLASS,VAR) \
	inline void CLASS::set_##VAR(const decltype(CLASS::VAR)& _##VAR ){this->VAR=_##VAR;}
#include <cstdint>


// 无论如何都应该inline
#ifndef _ALWAYS_INLINE_
#if defined(__GNUC__)
#define _ALWAYS_INLINE_ __attribute__((always_inline)) inline
#elif defined(_MSC_VER)
#define _ALWAYS_INLINE_ __forceinline
#else
#define _ALWAYS_INLINE_ inline
#endif
#endif

//除了在dev构建都应该inline，因为它几乎不产生debugging
#ifndef _FORCE_INLINE_
#ifdef DEV_ENABLED
#define _FORCE_INLINE_ inline
#else
#define _FORCE_INLINE_ _ALWAYS_INLINE_
#endif
#endif

#endif //XOX_DEF_HPP