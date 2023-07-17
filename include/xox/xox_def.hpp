#ifndef XOX_DEF_HPP
#define XOX_DEF_HPP

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
#endif //XOX_DEF_HPP