import xox.Template.Delegata;
#include <cstdio>
#include <cstdlib>
class Foo {
public:
	int aa;
	static void func(const char* c) {
		printf("Foo::func\n");
	}
	void func2(const char* c) {
		printf("Foo::func2\n");
	}
};

void func(const char* c) {
	printf("func\n");
}

int main() {
	typedef void(*common_fun)();
	Foo f;
	xox::Action<Foo, const char*> a;
	a.addFunc(&Foo::func);
	a.addFunc(&f, &Foo::func2);
	a.addFunc(&f, &Foo::func2);
	a.addFunc(&f, &Foo::func2);
	a.addFunc(&f, &Foo::func2);
	a.addFunc([](const char*) {printf("lambda\n"); });
	a("aaa");
	system("pause");
	return 0;
}