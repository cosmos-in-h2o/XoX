#include <Cosmos/template/Action.h>
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
	Cosmos::Action<Foo, const char*> a;
	a.addFunc(&Foo::func);
	a.addFunc(&f, &Foo::func2);
	a.addFunc(&func);
	a("aaa");
	system("pause");
	return 0;
}