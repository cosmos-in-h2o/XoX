#ifndef XOX_DEF_HPP
#define XOX_DEF_HPP
//编译器为MSVC(或者windows上的clang)或者是否为mingw
#if defined (_MSC_VER)||defined (__MINGW32__)||defined (__MINGW64__)
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
//对齐大小
#define XOX_ALIGNMENT sizeof(void*)

//连接所有内置电子到编辑器，需要引入模块xox.world
#define CONNECT_ALL_ELE

//快捷连接电子与编辑器
#define XOXELECTRON(CLASS) \
private: \
	static String _get_class_name(){return STR(CLASS);}
#define EXPORT_VAR()
#define EXPORT_FUNC()
#endif //XOX_DEF_HPP
