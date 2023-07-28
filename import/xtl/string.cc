
module xox.core.xtl.string;
namespace xox {
	bool select_word(const String& p_s, int p_col, int& r_beg, int& r_end) {
		const String& s = p_s;
		int beg = CLAMP(p_col, 0, s.length());
		int end = beg;

		if (s[beg] > 32 || beg == s.length()) {
			bool symbol = beg < s.length() && is_symbol(s[beg]);

			while (beg > 0 && s[beg - 1] > 32 && (symbol == is_symbol(s[beg - 1]))) {
				beg--;
			}
			while (end < s.length() && s[end + 1] > 32 && (symbol == is_symbol(s[end + 1]))) {
				end++;
			}

			if (end < s.length()) {
				end += 1;
			}

			r_beg = beg;
			r_end = end;

			return true;
		}
		else {
			return false;
		}
	}
}