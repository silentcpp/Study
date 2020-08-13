#ifndef __STRING_H__
#define __STRING_H__

#ifndef NDEBUG
/*debug版本*/
#define DEBUG 1
#else
/*release版本*/

#ifdef _WIN32
/*消除Windows下提示的多余安全警告*/
#define _CRT_SECURE_NO_WARNINGS
#endif //!_WIN32

#define DEBUG 0
#endif // !NDEBUG

#include <iostream>
#include <cstring>
#include <cstdlib>

/*输入缓存区大小*/
#define BUFFSIZE 4096

class String
{
private:
	/*对象个数*/
	static size_t string_total;
	/*字符串缓存区*/
	mutable char* buffer;
	/*字符串真实长度'\0'包含在内*/
	mutable size_t real_len;
	/*字符串容量*/
	mutable size_t capacity;

	/*自动分配buffer缓存区*/
	char* auto_alloc(const char* str1, const char* str2 = nullptr, bool is_free = true) const;
	char* auto_alloc(const int strlen1, const int strlen2 = 0, bool is_free = true) const;

	/*String减法所调用函数*/
	String& string_subtraction(const char* str);
public:
	/*has-a关系*/
	class iterator {
	public:
		iterator();
		iterator(const iterator& iter);
		iterator(char* pointer);
		iterator(iterator&& right);
		~iterator();
		char& operator*() const;
		iterator& operator=(const iterator& iter);
		bool operator!=(const iterator& iter);
		/*后自增*/
		const iterator operator++(int);
		/*前自增*/
		iterator& operator++();
		const iterator operator--(int);
		iterator& operator--();
		iterator operator+(int i) const;
		iterator operator-(int i) const;
		char* get_pointer() const;
	private:
		char* pointer;
	};
	using const_iterator = const iterator;
	/*has-a关系*/
	class reverse_iterator {
	public:
		reverse_iterator();
		reverse_iterator(const reverse_iterator& riter);
		reverse_iterator(char* pointer);
		reverse_iterator(reverse_iterator&& right);
		~reverse_iterator();
		char& operator*() const;
		reverse_iterator& operator=(const reverse_iterator& iter);
		bool operator!=(const reverse_iterator& iter);
		const reverse_iterator operator++(int);
		reverse_iterator& operator++();
		const reverse_iterator operator--(int);
		reverse_iterator& operator--();
		reverse_iterator operator+(int i) const;
		reverse_iterator operator-(int i) const;
		char* get_pointer() const;
	private:
		char* pointer;
	};
	using const_reverse_iterator = const reverse_iterator;

	constexpr static size_t npos = ~0U;

	String::iterator begin();
	String::iterator end();

	String::reverse_iterator rbegin();
	String::reverse_iterator rend();

	static const size_t get_string_total();

	String();
	~String();
	/*此处记得使用size_t强制类型转换*/
	explicit String(const size_t capacity);
	String(const char ch);
	String(const char* str);
	String(const String& str);
	/*移动构造*/
	String(String&& right);

	String& append(const char* str);
	String& append(const char* str, size_t count);
	String& append(const char ch);
	String& append(size_t count, const char ch);
	String& append(const String& str);
	String& append(const String& str, size_t count);

	String& assign(const char* str);
	String& assign(const size_t count, const char ch);
	String& assign(const char* str, const size_t count);
	String& assign(const String& str, const size_t offset, const size_t count);
	String& assign(const String& str);
	String& assign(const String&& str);

	/*还需要进一步完善*/
	String& replace(const String::iterator first, const String::iterator last, const char* str);
	String& replace(const String::iterator first, const String::iterator last, const char* str, const size_t count);
	String& replace(const String::iterator first, const String::iterator last, size_t count, const char ch);

	int compare(const size_t off, const size_t on, const char* str);
	int compare(const size_t off, const size_t on, const char* str, const size_t count);
	int compare(const char* str) const;
	int compare(const String& str) const;
	int compare(const size_t off, const size_t on, const String& str) const;
	int compare(const size_t off, const size_t on, const String& str, const size_t roff, const size_t ron) const;

	size_t find(const char ch, const size_t start = 0U) const;
	size_t find(const char* str, const size_t start = 0U) const;
	size_t find(const String& str, const size_t start = 0U) const;
	/*string::find 3个参数的没看懂是什么意思，下面的是自己随便写的*/
	size_t find(const char* str, const size_t start, const size_t str_start);

	/*这个太难理解到底是干什么的，没有实现函数体*/
	size_t find_first_not_of(const char ch, const size_t start = 0U) const;
	size_t find_first_not_of(const char* str, const size_t start = 0U) const;
	size_t find_first_not_of(const String& str, const size_t start = 0U) const;
	size_t find_first_not_of(const char* str, const size_t start, const size_t str_start);

	void pop_back();
	void push_back(const char ch);
	const char& at(const size_t size) const;
	String substr(const size_t off = 0U, const size_t count = ~0U);
	char& back();
	char& back() const;
	char& front();
	char& front() const;
	size_t max_size() const;
	void clear();
	void swap(String& str);
	size_t copy(char* buffer, size_t count, size_t off = 0U);

	const char* data() const;
	const char* c_str() const;

	bool empty() const;

	String::iterator erase(String::const_iterator first, String::const_iterator last);

	const size_t get_capacity() const;
	const size_t get_length() const;

	void reserve(size_t new_size = 0U);

	String& operator=(const String& str);
	String& operator=(const char* str);
	String& operator=(const char ch);

	String& operator+=(const String& str);
	String& operator+=(const char* str);
	String& operator+=(const char ch);

	String operator+(const String& str);
	String operator+(const char* str);
	String operator+(const char ch);

	String operator-(const String& str);
	String operator-(const char* str);
	String operator-(const char ch);

	String& operator-=(const String& str);
	String& operator-=(const char* str);
	String& operator-=(const char ch);

	String operator*(const size_t count) const;
	String& operator*=(const size_t count);

	bool operator==(const String& str);
	bool operator==(const char* str);

	bool operator>(const String& str);
	bool operator>(const char* str);
	bool operator<(const char* str);
	bool operator<(const String& str);

	/*explicit关闭隐式转换，可强制类型转换为(wchar_t *)记得自动手动释放内存*/
	explicit operator wchar_t* () const;
	/*返回string长度，同上*/
	explicit operator size_t() const;
	explicit operator int() const;

	char& operator[](const size_t count);
	const char& operator[](const size_t count) const;

	friend std::ostream& operator<<(std::ostream& out, const String& str);
	friend std::istream& operator>>(std::istream& in, String& str);

	friend String operator+(const char* ch, const String& str);
	friend String operator+(const char ch, const String& str);

	friend String operator-(const char* ch, const String& str);
	friend bool operator==(const String& str1, const String& str2);
};
/*直接调用String * size_t */
String operator*(const size_t count, const String& str);

#endif // !__STRING_H__