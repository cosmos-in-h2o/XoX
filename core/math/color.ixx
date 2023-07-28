module;
#include <algorithm>
export module xox.core.math.color;
namespace xox{
	export using ColorValue=unsigned short;
	export struct Color{
		union{
			struct {
				ColorValue r;
				ColorValue g;
				ColorValue b;
				ColorValue a;
			};
			ColorValue value[4] = { 0, 0, 0, 0xff };
		};
		Color()=default;
		Color(const Color&)=default;
		Color(ColorValue r,ColorValue g,ColorValue b):r(r),g(g),b(b),a(0xff){}
		Color(ColorValue r,ColorValue g,ColorValue b,ColorValue a):r(r),g(g),b(b),a(a){}
		~Color()=default;
		Color& operator=(const Color&)=default;
		ColorValue& operator[](size_t index) {
			return this->value[index];
		}
		Color operator+(const Color& color){
			auto alpha=this->a+color.a;
			if(alpha>255) alpha=255;
			return Color(this->r+color.r,this->g+color.g,this->b+color.b,alpha);
		}
	};
}