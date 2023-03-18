#ifndef ACTION_H
#define ACTION_H
#include <Cosmos/classes/Atom.h>
#include <list>
namespace Cosmos {
	///----------------------------------------------------------------------------------------------------
	/// Action
	///----------------------------------------------------------------------------------------------------
	/// 简介：void返回类型委托
	/// 实现：使用函数指针实现，不能包装带捕获类型的lambda表达式
	/// 说明：MT为成员类型，用于调用成员函数
	///----------------------------------------------------------------------------------------------------
	
	template<typename MT,typename ... Args>
	class Action:public Atom
	{
	private:
		//函数指针的声明
		typedef void(*common_fun)(Args...);
		typedef void(MT::*member_fun)(Args...);

		//列表
		std::list<common_fun> cfun_list;//普通函数列表
		std::list<member_fun> mfun_list;//成员函数列表
		std::list<int> mfun_add;//成员函数位置
		std::list<MT*> member;//类对象，与成员函数列表对应
	public:
		//构造与析构
		Action<MT, Args...>(){}
		Action<MT, Args...>(common_fun& fun){
			this->cfun_list.push_back(fun);
		}
		Action<MT, Args...>(MT* member, member_fun& fun) {
			this->mfun_add.push_back(this->cfun_list.size() + this->mfun_list.size());
			this->member.push_back(member);
			this->mfun_list.push_back(fun);
		}
		~Action<MT, Args...>() {}
		//添加函数
		inline void addFunc(const common_fun& fun) {
			this->cfun_list.push_back(fun);
		}

		inline void addFunc(MT* member, const member_fun& fun) {
			this->mfun_add.push_back(this->cfun_list.size() + this->mfun_list.size());
			this->member.push_back(member);
			this->mfun_list.push_back(fun);
			////调试
			//printf("%d\n", this->cfun_list.size() + this->mfun_list.size());
		}

		//执行函数
		void invoke(Args... args) {
			if (this->cfun_list.empty() && this->mfun_list.empty()) {
				return;
			}
			typename std::list<common_fun>::iterator cfun_list_iter = this->cfun_list.begin();
			typename std::list<member_fun>::iterator mfun_list_iter = this->mfun_list.begin();
			typename std::list<MT*>::iterator member_iter = this->member.begin();
			typename std::list<int>::iterator mfun_add_iter = this->mfun_add.begin();
			//当普通函数列表为空
			if (this->cfun_list.empty()) {
				for (; mfun_list_iter!=this->mfun_list.end();) {
					(*member_iter->*(*mfun_list_iter))(args...);
					mfun_list_iter++;
					member_iter++;
				}
				return;
			}
			if (this->mfun_list.empty())
			{
				for (; cfun_list_iter != this->cfun_list.end();) {
					(*cfun_list_iter)(args...);
					cfun_list_iter++;
				}
				return;
			}
			
			//都不为空就一起执行
			for (int index = 0;;) {
				////调试
				//printf("%d",index);
				if (cfun_list_iter == this->cfun_list.end() && mfun_list_iter == this->mfun_list.end()) {
					return;
				}
				//判断是否为成员函数
				if (mfun_add_iter!=this->mfun_add.end() && *mfun_add_iter == index) {
					(*member_iter->*(*mfun_list_iter))(args...);
					mfun_list_iter++;
					member_iter++;
					mfun_add_iter++;
				}
				else if (cfun_list_iter != this->cfun_list.end()) {
					(*cfun_list_iter)(args...);
					cfun_list_iter++;
				}
				index++;
			}
		}

		inline void invokeOnce(Args... args){
			this->invoke(args...);
			this->clear();
		}

		//清空函数列表
		inline void clear() {
			this->cfun_list.clear();
			this->mfun_list.clear();
			this->member.clear();
			this->mfun_add.clear();
		}

		//运算符重载
		inline void operator+=(const common_fun& fun) {
			this->cfun_list.push_back(fun);
		}

		inline void operator()(Args... args) {
			this->invoke(args...);
		}

		inline void operator=(const common_fun& fun) {
			this->clear();
			this->cfun_list.push_back(fun);
		}

		//其他
		bool isEmpty() {
			if (this->cfun_list.empty()) {
				return true;
			}
			if (this->mfun_list.empty()) {
				return true;
			}
			return false;
		}
	};
};

#endif