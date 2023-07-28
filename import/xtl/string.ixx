module;
#include <EASTL/string.h>
#include <xox/xox_def.hpp>
export module xox.core.xtl.string;
export import xox.core.memory.malloc;
import xox.core.xtl.vector;
namespace xox {
	export using String = eastl::string;
	bool operator==(const char* p_chr, const String& p_str);
	bool operator==(const wchar_t* p_chr, const String& p_str);
	bool operator!=(const char* p_chr, const String& p_str);
	bool operator!=(const wchar_t* p_chr, const String& p_str);

	String operator+(const char* p_chr, const String& p_str);
	String operator+(const wchar_t* p_chr, const String& p_str);
	String operator+(char32_t p_chr, const String& p_str);

	String itos(int64_t p_val);
	String uitos(uint64_t p_val);
	String rtos(double p_val);
	String rtoss(double p_val); //scientific version

	template <typename L, typename R>
	_FORCE_INLINE_ bool is_str_less(const L* l_ptr, const R* r_ptr) {
		while (true) {
			const char32_t l = *l_ptr;
			const char32_t r = *r_ptr;

			if (l == 0 && r == 0) {
				return false;
			}
			else if (l == 0) {
				return true;
			}
			else if (r == 0) {
				return false;
			}
			else if (l < r) {
				return true;
			}
			else if (l > r) {
				return false;
			}

			l_ptr++;
			r_ptr++;
		}
	}


	String RTR(const String& p_text, const String& p_context = "");
	String RTRN(const String& p_text, const String& p_text_plural, int p_n, const String& p_context = "");

	bool select_word(const String& p_s, int p_col, int& r_beg, int& r_end);

	_FORCE_INLINE_ void sarray_add_str(Vector<String>& arr) {
	}

	_FORCE_INLINE_ void sarray_add_str(Vector<String>& arr, const String& p_str) {
		arr.push_back(p_str);
	}

	template <class... P>
	_FORCE_INLINE_ void sarray_add_str(Vector<String>& arr, const String& p_str, P... p_args) {
		arr.push_back(p_str);
		sarray_add_str(arr, p_args...);
	}

	template <class... P>
	_FORCE_INLINE_ Vector<String> sarray(P... p_args) {
		Vector<String> arr;
		sarray_add_str(arr, p_args...);
		return arr;
	}

} 