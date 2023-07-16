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
#define CLASS_GET_1(CLASS,VAR1) \
	inline const decltype(CLASS::VAR1)& CLASS::get_##VAR1()const{return this->VAR1;}
#define CLASS_SET_1(CLASS,VAR1) \
	inline void CLASS::set_##VAR1(const decltype(CLASS::VAR1)& _##VAR1 ){this->VAR1=_##VAR1;}

#define CLASS_GET_2(CLASS,VAR1,VAR2) \
	inline const decltype(CLASS::VAR1)& CLASS::get_##VAR1()const{return this->VAR1;} \
	inline const decltype(CLASS::VAR2)& CLASS::get_##VAR2()const{return this->VAR2;}
#define CLASS_SET_2(CLASS,VAR1,VAR2) \
	inline void CLASS::set_##VAR1(const decltype(CLASS::VAR1)& _##VAR1 ){this->VAR1=_##VAR1;} \
	inline void CLASS::set_##VAR2(const decltype(CLASS::VAR2)& _##VAR2 ){this->VAR2=_##VAR2;}

#define CLASS_GET_3(CLASS,VAR1,VAR2,VAR3) \
	inline const decltype(CLASS::VAR1)& CLASS::get_##VAR1()const{return this->VAR1;} \
	inline const decltype(CLASS::VAR2)& CLASS::get_##VAR2()const{return this->VAR2;} \
	inline const decltype(CLASS::VAR3)& CLASS::get_##VAR3()const{return this->VAR3;}
#define CLASS_SET_3(CLASS,VAR1,VAR2,VAR3) \
	inline void CLASS::set_##VAR1(const decltype(CLASS::VAR1)& _##VAR1 ){this->VAR1=_##VAR1;} \
	inline void CLASS::set_##VAR2(const decltype(CLASS::VAR2)& _##VAR2 ){this->VAR2=_##VAR2;} \
	inline void CLASS::set_##VAR3(const decltype(CLASS::VAR3)& _##VAR3 ){this->VAR3=_##VAR3;}

#define CLASS_GET_4(CLASS,VAR1,VAR2,VAR3,VAR4) \
	inline const decltype(CLASS::VAR1)& CLASS::get_##VAR1()const{return this->VAR1;} \
	inline const decltype(CLASS::VAR2)& CLASS::get_##VAR2()const{return this->VAR2;} \
	inline const decltype(CLASS::VAR3)& CLASS::get_##VAR3()const{return this->VAR3;} \
	inline const decltype(CLASS::VAR4)& CLASS::get_##VAR4()const{return this->VAR4;}
#define CLASS_SET_4(CLASS,VAR1,VAR2,VAR3,VAR4) \
	inline void CLASS::set_##VAR1(const decltype(CLASS::VAR1)& _##VAR1 ){this->VAR1=_##VAR1;} \
	inline void CLASS::set_##VAR2(const decltype(CLASS::VAR2)& _##VAR2 ){this->VAR2=_##VAR2;} \
	inline void CLASS::set_##VAR3(const decltype(CLASS::VAR3)& _##VAR3 ){this->VAR3=_##VAR3;} \
	inline void CLASS::set_##VAR4(const decltype(CLASS::VAR4)& _##VAR4 ){this->VAR4=_##VAR4;}

#define CLASS_GET_5(CLASS,VAR1,VAR2,VAR3,VAR4,VAR5) \
	inline const decltype(CLASS::VAR1)& CLASS::get_##VAR1()const{return this->VAR1;} \
	inline const decltype(CLASS::VAR2)& CLASS::get_##VAR2()const{return this->VAR2;} \
	inline const decltype(CLASS::VAR3)& CLASS::get_##VAR3()const{return this->VAR3;} \
	inline const decltype(CLASS::VAR4)& CLASS::get_##VAR4()const{return this->VAR4;} \
	inline const decltype(CLASS::VAR5)& CLASS::get_##VAR5()const{return this->VAR5;}
#define CLASS_SET_5(CLASS,VAR1,VAR2,VAR3,VAR4,VAR5) \
	inline void CLASS::set_##VAR1(const decltype(CLASS::VAR1)& _##VAR1 ){this->VAR1=_##VAR1;} \
	inline void CLASS::set_##VAR2(const decltype(CLASS::VAR2)& _##VAR2 ){this->VAR2=_##VAR2;} \
	inline void CLASS::set_##VAR3(const decltype(CLASS::VAR3)& _##VAR3 ){this->VAR3=_##VAR3;} \
	inline void CLASS::set_##VAR4(const decltype(CLASS::VAR4)& _##VAR4 ){this->VAR4=_##VAR4;} \
	inline void CLASS::set_##VAR5(const decltype(CLASS::VAR5)& _##VAR5 ){this->VAR5=_##VAR5;}

#define CLASS_GET_6(CLASS,VAR1,VAR2,VAR3,VAR4,VAR5,VAR6) \
	inline const decltype(CLASS::VAR1)& CLASS::get_##VAR1()const{return this->VAR1;} \
	inline const decltype(CLASS::VAR2)& CLASS::get_##VAR2()const{return this->VAR2;} \
	inline const decltype(CLASS::VAR3)& CLASS::get_##VAR3()const{return this->VAR3;} \
	inline const decltype(CLASS::VAR4)& CLASS::get_##VAR4()const{return this->VAR4;} \
	inline const decltype(CLASS::VAR5)& CLASS::get_##VAR5()const{return this->VAR5;} \
	inline const decltype(CLASS::VAR6)& CLASS::get_##VAR6()const{return this->VAR6;}
#define CLASS_SET_6(CLASS,VAR1,VAR2,VAR3,VAR4,VAR5,VAR6) \
	inline void CLASS::set_##VAR1(const decltype(CLASS::VAR1)& _##VAR1 ){this->VAR1=_##VAR1;} \
	inline void CLASS::set_##VAR2(const decltype(CLASS::VAR2)& _##VAR2 ){this->VAR2=_##VAR2;} \
	inline void CLASS::set_##VAR3(const decltype(CLASS::VAR3)& _##VAR3 ){this->VAR3=_##VAR3;} \
	inline void CLASS::set_##VAR4(const decltype(CLASS::VAR4)& _##VAR4 ){this->VAR4=_##VAR4;} \
	inline void CLASS::set_##VAR5(const decltype(CLASS::VAR5)& _##VAR5 ){this->VAR5=_##VAR5;} \
	inline void CLASS::set_##VAR6(const decltype(CLASS::VAR6)& _##VAR6 ){this->VAR6=_##VAR6;}

#endif //XOX_DEF_HPP