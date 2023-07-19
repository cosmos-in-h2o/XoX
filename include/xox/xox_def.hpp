#ifndef XOX_DEF_HPP
#define XOX_DEF_HPP

//获取字符串
#ifndef _STR
#define _STR(X) #X
#define _MKSTR(X) _STR(X)
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

//typedef
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

//需要引入safe_refcount模块才能使用
#define SAFE_NUMERIC_TYPE_PUN_GUARANTEES(TYPE)                    \
	static_assert(sizeof(SafeNumeric<TYPE>) == sizeof(TYPE));   \
	static_assert(alignof(SafeNumeric<TYPE>) == alignof(TYPE)); \
	static_assert(std::is_trivially_destructible<std::atomic<TYPE>>::value);
//需要引入safe_refcount模块才能使用
#define SAFE_FLAG_TYPE_PUN_GUARANTEES                \
	static_assert(sizeof(SafeFlag) == sizeof(bool)); \
	static_assert(alignof(SafeFlag) == alignof(bool));

//连接所有内置电子到编辑器，需要引入模块xox.world
#define CONNECT_ALL_ELE

//快捷连接电子与编辑器
#define XOXELECTRON(CLASS) \
private: \
	static String _get_class_name(){return STR(CLASS);}
#define EXPORT_VAR()
#define EXPORT_FUNC()
#endif //XOX_DEF_HPP