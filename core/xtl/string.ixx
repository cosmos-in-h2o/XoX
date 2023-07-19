module;
#include <xox/xox_def.hpp>
export module xox.core.xtl.string;
import xox.core.memory.malloc;
import xox.core.error.error_list;

namespace xox {
	template<typename T> class CowData {};

	export template<typename CT_, typename Allocator=DefaultAllocator> 
	class BasicString {
		CowData<CT_> _cowdata;
		static const char32_t _null;
		static const char32_t _replacement_char;

		void copy_from(const char* p_cstr);
		void copy_from(const char* p_cstr, const int p_clip_to);
		void copy_from(const wchar_t* p_cstr);
		void copy_from(const wchar_t* p_cstr, const int p_clip_to);
		void copy_from(const char32_t* p_cstr);
		void copy_from(const char32_t* p_cstr, const int p_clip_to);

		void copy_from(const char32_t& p_char);

		void copy_from_unchecked(const char32_t* p_char, const int p_length);

		bool _base_is_subsequence_of(const BasicString& p_string, bool case_insensitive) const;
		int _count(const BasicString& p_string, int p_from, int p_to, bool p_case_insensitive) const;
		BasicString _camelcase_to_underscore() const;

		public:
			enum {
				npos = -1 ///<for "some" compatibility with std::string (npos is a huge value in std::string)
			};

			_FORCE_INLINE_ CT_* data() { return _cowdata.ptrw(); }
			_FORCE_INLINE_ const CT_* c_str() const { return _cowdata.ptr(); }

			void remove_at(int p_index) { _cowdata.remove_at(p_index); }

			_FORCE_INLINE_ void clear() { resize(0); }

			_FORCE_INLINE_ CT_ get(int p_index) const { return _cowdata.get(p_index); }
			_FORCE_INLINE_ void set(int p_index, const char32_t& p_elem) { _cowdata.set(p_index, p_elem); }
			_FORCE_INLINE_ int size() const { return _cowdata.size(); }
			Error resize(int p_size) { return _cowdata.resize(p_size); }

			_FORCE_INLINE_ const CT_& operator[](int p_index) const {
				if (unlikely(p_index == _cowdata.size())) {
					return _null;
				}

				return _cowdata.get(p_index);
			}
			_FORCE_INLINE_ CharProxy<CT_> operator[](int p_index) { return CharProxy<CT_>(p_index, _cowdata); }

			bool operator==(const BasicString& p_str) const;
			bool operator!=(const BasicString& p_str) const;
			BasicString operator+(const BasicString& p_str) const;
			BasicString operator+(CT_ p_char) const;

			BasicString& operator+=(const BasicString&);
			BasicString& operator+=(char32_t p_char);
			BasicString& operator+=(const char* p_str);
			BasicString& operator+=(const wchar_t* p_str);
			BasicString& operator+=(const char32_t* p_str);

			/* Compatibility Operators */

			void operator=(const char* p_str);
			void operator=(const wchar_t* p_str);
			void operator=(const char32_t* p_str);

			bool operator==(const char* p_str) const;
			bool operator==(const wchar_t* p_str) const;
			bool operator==(const char32_t* p_str) const;
			bool operator==(const StrRange& p_str_range) const;

			bool operator!=(const char* p_str) const;
			bool operator!=(const wchar_t* p_str) const;
			bool operator!=(const char32_t* p_str) const;

			bool operator<(const char32_t* p_str) const;
			bool operator<(const char* p_str) const;
			bool operator<(const wchar_t* p_str) const;

			bool operator<(const BasicString& p_str) const;
			bool operator<=(const BasicString& p_str) const;
			bool operator>(const BasicString& p_str) const;
			bool operator>=(const BasicString& p_str) const;

			signed char casecmp_to(const BasicString& p_str) const;
			signed char nocasecmp_to(const BasicString& p_str) const;
			signed char naturalcasecmp_to(const BasicString& p_str) const;
			signed char naturalnocasecmp_to(const BasicString& p_str) const;

			const char32_t* get_data() const;
			/* standard size stuff */

			_FORCE_INLINE_ int length() const {
				int s = size();
				return s ? (s - 1) : 0; // length does not include zero
			}

			bool is_valid_string() const;

			/* debug, error messages */
			void print_unicode_error(const BasicString& p_message, bool p_critical = false) const;

			/* complex helpers */
			BasicString substr(int p_from, int p_chars = -1) const;
			int find(const BasicString& p_str, int p_from = 0) const; ///< return <0 if failed
			int find(const char* p_str, int p_from = 0) const; ///< return <0 if failed
			int find_char(const char32_t& p_char, int p_from = 0) const; ///< return <0 if failed
			int findn(const BasicString& p_str, int p_from = 0) const; ///< return <0 if failed, case insensitive
			int rfind(const BasicString& p_str, int p_from = -1) const; ///< return <0 if failed
			int rfindn(const BasicString& p_str, int p_from = -1) const; ///< return <0 if failed, case insensitive
			int findmk(const Vector<BasicString>& p_keys, int p_from = 0, int* r_key = nullptr) const; ///< return <0 if failed
			bool match(const BasicString& p_wildcard) const;
			bool matchn(const BasicString& p_wildcard) const;
			bool begins_with(const BasicString& p_string) const;
			bool begins_with(const char* p_string) const;
			bool ends_with(const BasicString& p_string) const;
			bool is_enclosed_in(const BasicString& p_string) const;
			bool is_subsequence_of(const BasicString& p_string) const;
			bool is_subsequence_ofn(const BasicString& p_string) const;
			bool is_quoted() const;
			Vector<BasicString> bigrams() const;
			float similarity(const BasicString& p_string) const;
			BasicString format(const Variant& values, BasicString placeholder = "{_}") const;
			BasicString replace_first(const BasicString& p_key, const BasicString& p_with) const;
			BasicString replace(const BasicString& p_key, const BasicString& p_with) const;
			BasicString replace(const char* p_key, const char* p_with) const;
			BasicString replacen(const BasicString& p_key, const BasicString& p_with) const;
			BasicString repeat(int p_count) const;
			BasicString insert(int p_at_pos, const BasicString& p_string) const;
			BasicString erase(int p_pos, int p_chars = 1) const;
			BasicString pad_decimals(int p_digits) const;
			BasicString pad_zeros(int p_digits) const;
			BasicString trim_prefix(const BasicString& p_prefix) const;
			BasicString trim_suffix(const BasicString& p_suffix) const;
			BasicString lpad(int min_length, const BasicString& character = " ") const;
			BasicString rpad(int min_length, const BasicString& character = " ") const;
			BasicString sprintf(const Array& values, bool* error) const;
			BasicString quote(BasicString quotechar = "\"") const;
			BasicString unquote() const;
			static BasicString num(double p_num, int p_decimals = -1);
			static BasicString num_scientific(double p_num);
			static BasicString num_real(double p_num, bool p_trailing = true);
			static BasicString num_int64(int64_t p_num, int base = 10, bool capitalize_hex = false);
			static BasicString num_uint64(uint64_t p_num, int base = 10, bool capitalize_hex = false);
			static BasicString chr(CT_ p_char);
			static BasicString md5(const uint8_t* p_md5);
			static BasicString hex_encode_buffer(const uint8_t* p_buffer, int p_len);
			Vector<uint8_t> hex_decode() const;

			bool is_numeric() const;

			double to_float() const;
			int64_t hex_to_int() const;
			int64_t bin_to_int() const;
			int64_t to_int() const;

			static int64_t to_int(const char* p_str, int p_len = -1);
			static int64_t to_int(const wchar_t* p_str, int p_len = -1);
			static int64_t to_int(const char32_t* p_str, int p_len = -1, bool p_clamp = false);

			static double to_float(const char* p_str);
			static double to_float(const wchar_t* p_str, const wchar_t** r_end = nullptr);
			static double to_float(const char32_t* p_str, const char32_t** r_end = nullptr);
			static uint32_t num_characters(int64_t p_int);

			BasicString capitalize() const;
			BasicString to_camel_case() const;
			BasicString to_pascal_case() const;
			BasicString to_snake_case() const;

			BasicString get_with_code_lines() const;
			int get_slice_count(BasicString p_splitter) const;
			BasicString get_slice(BasicString p_splitter, int p_slice) const;
			BasicString get_slicec(CT_ p_splitter, int p_slice) const;

			Vector<BasicString> split(const BasicString& p_splitter = "", bool p_allow_empty = true, int p_maxsplit = 0) const;
			Vector<BasicString> rsplit(const BasicString& p_splitter = "", bool p_allow_empty = true, int p_maxsplit = 0) const;
			Vector<BasicString> split_spaces() const;
			Vector<double> split_floats(const BasicString& p_splitter, bool p_allow_empty = true) const;
			Vector<float> split_floats_mk(const Vector<BasicString>& p_splitters, bool p_allow_empty = true) const;
			Vector<int> split_ints(const BasicString& p_splitter, bool p_allow_empty = true) const;
			Vector<int> split_ints_mk(const Vector<BasicString>& p_splitters, bool p_allow_empty = true) const;

			BasicString join(Vector<BasicString> parts) const;

			static CT_ char_uppercase(CT_ p_char);
			static CT_ char_lowercase(CT_ p_char);
			BasicString to_upper() const;
			BasicString to_lower() const;

			int count(const BasicString& p_string, int p_from = 0, int p_to = 0) const;
			int countn(const BasicString& p_string, int p_from = 0, int p_to = 0) const;

			BasicString left(int p_len) const;
			BasicString right(int p_len) const;
			BasicString indent(const BasicString& p_prefix) const;
			BasicString dedent() const;
			BasicString strip_edges(bool left = true, bool right = true) const;
			BasicString strip_escapes() const;
			BasicString lstrip(const BasicString& p_chars) const;
			BasicString rstrip(const BasicString& p_chars) const;
			BasicString get_extension() const;
			BasicString get_basename() const;
			BasicString path_join(const BasicString& p_file) const;
			char32_t unicode_at(int p_idx) const;

			CharString ascii(bool p_allow_extended = false) const;
			CharString utf8() const;
			Error parse_utf8(const char* p_utf8, int p_len = -1, bool p_skip_cr = false);
			static BasicString utf8(const char* p_utf8, int p_len = -1);

			Char16String utf16() const;
			Error parse_utf16(const char16_t* p_utf16, int p_len = -1);
			static BasicString utf16(const char16_t* p_utf16, int p_len = -1);

			static uint32_t hash(const char32_t* p_cstr, int p_len); /* hash the string */
			static uint32_t hash(const char32_t* p_cstr); /* hash the string */
			static uint32_t hash(const wchar_t* p_cstr, int p_len); /* hash the string */
			static uint32_t hash(const wchar_t* p_cstr); /* hash the string */
			static uint32_t hash(const char* p_cstr, int p_len); /* hash the string */
			static uint32_t hash(const char* p_cstr); /* hash the string */
			uint32_t hash() const; /* hash the string */
			uint64_t hash64() const; /* hash the string */
			BasicString md5_text() const;
			BasicString sha1_text() const;
			BasicString sha256_text() const;
			Vector<uint8_t> md5_buffer() const;
			Vector<uint8_t> sha1_buffer() const;
			Vector<uint8_t> sha256_buffer() const;

			_FORCE_INLINE_ bool is_empty() const { return length() == 0; }
			_FORCE_INLINE_ bool contains(const char* p_str) const { return find(p_str) != -1; }
			_FORCE_INLINE_ bool contains(const BasicString& p_str) const { return find(p_str) != -1; }

			// path functions
			bool is_absolute_path() const;
			bool is_relative_path() const;
			bool is_resource_file() const;
			BasicString path_to(const BasicString& p_path) const;
			BasicString path_to_file(const BasicString& p_path) const;
			BasicString get_base_dir() const;
			BasicString get_file() const;
			static BasicString humanize_size(uint64_t p_size);
			BasicString simplify_path() const;
			bool is_network_share_path() const;

			BasicString xml_escape(bool p_escape_quotes = false) const;
			BasicString xml_unescape() const;
			BasicString uri_encode() const;
			BasicString uri_decode() const;
			BasicString c_escape() const;
			BasicString c_escape_multiline() const;
			BasicString c_unescape() const;
			BasicString json_escape() const;
			Error parse_url(BasicString& r_scheme, BasicString& r_host, int& r_port, BasicString& r_path) const;

			BasicString property_name_encode() const;

			// node functions
			static BasicString get_invalid_node_name_characters();
			BasicString validate_node_name() const;
			BasicString validate_identifier() const;
			BasicString validate_filename() const;

			bool is_valid_identifier() const;
			bool is_valid_int() const;
			bool is_valid_float() const;
			bool is_valid_hex_number(bool p_with_prefix) const;
			bool is_valid_html_color() const;
			bool is_valid_ip_address() const;
			bool is_valid_filename() const;

			/**
			 * The constructors must not depend on other overloads
			 */

			_FORCE_INLINE_ BasicString() {}
			_FORCE_INLINE_ BasicString(const BasicString& p_str) { _cowdata._ref(p_str._cowdata); }
			_FORCE_INLINE_ void operator=(const BasicString& p_str) { _cowdata._ref(p_str._cowdata); }

			Vector<uint8_t> to_ascii_buffer() const;
			Vector<uint8_t> to_utf8_buffer() const;
			Vector<uint8_t> to_utf16_buffer() const;
			Vector<uint8_t> to_utf32_buffer() const;
			Vector<uint8_t> to_wchar_buffer() const;

			BasicString(const char* p_str);
			BasicString(const wchar_t* p_str);
			BasicString(const char32_t* p_str);
			BasicString(const char* p_str, int p_clip_to_len);
			BasicString(const wchar_t* p_str, int p_clip_to_len);
			BasicString(const char32_t* p_str, int p_clip_to_len);
			BasicString(const StrRange& p_range);
	};


	export using String = BasicString<char32_t>;
}