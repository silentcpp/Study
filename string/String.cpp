#include "String.h"

/*初始化静态成员，统计对象的个数*/
size_t String::string_total = 0;

char* String::auto_alloc(const char* str1, const char* str2, bool is_free) const
{
	char* buffer = nullptr;
	do
	{
		if (!this->buffer && str1 && !str2)
		{
			this->real_len = strlen(str1) + 1;
			buffer = new(std::nothrow) char[this->real_len];
			if (!buffer)
			{
				break;
			}
			strcpy(buffer, str1);
		}
		else if (this->buffer && str1 && !str2)
		{
			this->real_len = strlen(str1) + 1;
			buffer = new(std::nothrow) char[this->real_len];
			if (!buffer)
			{
				break;
			}
			strcpy(buffer, str1);
			if (is_free)
			{
				delete[] this->buffer;
			}
		}
		else if (!this->buffer && !str1 && str2)
		{
			this->real_len = strlen(str2) + 1;
			buffer = new(std::nothrow) char[this->real_len];
			if (!buffer)
			{
				break;
			}
			strcpy(buffer, str2);
		}
		else if (this->buffer && !str1 && str2)
		{
			this->real_len = strlen(str2) + 1;
			buffer = new(std::nothrow) char[this->real_len];
			if (!buffer)
			{
				break;
			}
			strcpy(buffer, str2);
			if (is_free)
			{
				delete[] this->buffer;
			}
		}
		else if (this->buffer && str1 && str2)
		{
			this->real_len = strlen(str1) + strlen(str2) + 1;
			buffer = new(std::nothrow) char[this->real_len];
			if (!buffer)
			{
				break;
			}
			strcpy(buffer, str1);
			strcat(buffer, str2);
			if (is_free)
			{
				delete[] this->buffer;
			}
		}
		else
		{
			std::cout << "Found the condition isn't satisfied" << std::endl;
			std::cout << "this->buffer:" << this->buffer << std::endl;
			std::cout << "str1:" << str1 << std::endl;
			std::cout << "str2:" << str2 << std::endl;
		}
	} while (false);
	this->capacity = this->real_len;
	return buffer;
}

char* String::auto_alloc(const int str1, const int str2, bool is_free) const
{
	char* buffer = nullptr;
	do
	{
		if (!this->buffer && str1 && !str2)
		{
			this->real_len = str1 + 1;
			buffer = new(std::nothrow) char[this->real_len];
			if (!buffer)
			{
				break;
			}
		}
		else if (this->buffer && str1 && !str2)
		{
			this->real_len = str1 + 1;
			buffer = new(std::nothrow) char[this->real_len];
			if (!buffer)
			{
				break;
			}
			if (is_free)
			{
				delete[] this->buffer;
			}

		}
		else if (!this->buffer && !str1 && str2)
		{
			this->real_len = str2 + 1;
			buffer = new(std::nothrow) char[this->real_len];
			if (!buffer)
			{
				break;
			}
		}
		else if (this->buffer && !str1 && str2)
		{
			this->real_len = str2 + 1;
			buffer = new(std::nothrow) char[this->real_len];
			if (!buffer)
			{
				break;
			}
			if (is_free)
			{
				delete[] this->buffer;
			}
		}
		else if (this->buffer && str1 && str2)
		{
			this->real_len = str1 + str2 + 1;
			buffer = new(std::nothrow) char[this->real_len];
			if (!buffer)
			{
				break;
			}
			if (is_free)
			{
				delete[] this->buffer;
			}
		}
		else
		{
			std::cout << "Found the condition isn't satisfied" << std::endl;
			std::cout << "this->buffer:" << this->buffer << std::endl;
			std::cout << "str1:" << str1 << std::endl;
			std::cout << "str2:" << str2 << std::endl;
		}
	} while (false);
	this->capacity = this->real_len;
	return buffer;
}

String& String::string_subtraction(const char* str)
{
	size_t pos = 0, len = strlen(str);
	for (char* ptr = this->buffer; *ptr != '\0'; ptr++, pos++)
		if (!strncmp(ptr, str, len))
			for (size_t i = pos; i < this->get_length() - 1; i++)
				if (i + len > this->get_length())
					this->buffer[i] = '\0';
				else
					this->buffer[i] = this->buffer[i + len];
	return *this;
}

String::iterator String::begin()
{
	return String::iterator(this->buffer);
}

String::iterator String::end()
{
	return String::iterator(this->buffer + this->get_length());
}

String::reverse_iterator String::rbegin()
{
	/*忽略'\0'减1*/
	return String::reverse_iterator(this->buffer + this->get_length() - 1);
}

String::reverse_iterator String::rend()
{
	return String::reverse_iterator(this->buffer - 1);
}

const size_t String::get_string_total()
{
	return string_total;
}

String::String() :buffer(nullptr), real_len(0)
{
	string_total++;
#if DEBUG
	std::cout << "String::String()" << std::endl;
#endif
}

String::String(const char ch) :buffer(nullptr), real_len(0)
{
#if DEBUG
	std::cout << "String::String(const char ch)" << std::endl;
#endif
	string_total++;
	char temp[2];
	temp[0] = ch;
	temp[1] = '\0';
	this->buffer = auto_alloc(temp);
}

String::String(const char* buffer) :buffer(nullptr), real_len(0)
{
	string_total++;
#if DEBUG
	std::cout << "String::String(const char *buffer)" << std::endl;
#endif
	this->buffer = auto_alloc(buffer);
}

String::String(const String& str) :buffer(nullptr), real_len(0)
{
	string_total++;
#if DEBUG
	std::cout << "String::String(const String & str)" << std::endl;
#endif
	this->buffer = auto_alloc(str.buffer);
}

String::String(String&& right)
{
#if DEBUG
	std::cout << "String::String(String && right)" << std::endl;
#endif
	this->buffer = right.buffer;
	this->real_len = right.real_len;
	this->capacity = right.capacity;
	right.buffer = nullptr;
	right.real_len = 0;
	right.capacity = 0;
}

String::~String()
{
	string_total--;
#if DEBUG
	std::cout << "String::~String()" << std::endl;
#endif
	if (buffer)
	{
		delete[] buffer;
		buffer = nullptr;
		real_len = 0;
	}
}

String::String(const size_t capacity) :buffer(nullptr), real_len(0)
{
#if DEBUG
	std::cout << "String::String(const size_t capacity)" << std::endl;
#endif
	if (capacity > 0)
	{
		this->buffer = this->auto_alloc(capacity);
		memset(this->buffer, 0x0, capacity);
	}
}

String& String::append(const char* str)
{
	this->buffer = auto_alloc(this->buffer, str);
	return *this;
}

String& String::append(const char* str, size_t count)
{
	char* temp = new(std::nothrow) char[strlen(str) + 1];
	memset(temp, 0x0, strlen(str) + 1);
	strncpy(temp, str, count);
	this->buffer = auto_alloc(this->buffer, temp);
	delete[] temp;
	return *this;
}

String& String::append(const char ch)
{
	char temp[2];
	temp[0] = ch;
	temp[1] = '\0';
	this->buffer = auto_alloc(this->buffer, temp);
	return *this;
}

String& String::append(size_t count, const char ch)
{
	char* temp = new(std::nothrow) char[count + 1];
	size_t i;
	for (i = 0; i < count; i++)
		temp[i] = ch;
	temp[i] = '\0';
	this->buffer = auto_alloc(this->buffer, temp);
	delete[] temp;
	return *this;
}

String& String::append(const String& str)
{
	this->buffer = auto_alloc(this->buffer, str.buffer);
	return *this;
}

String& String::append(const String& str, size_t count)
{
	for (size_t i = 0; i < count; i++)
	{
		this->buffer = auto_alloc(this->buffer, str.buffer);
	}
	return *this;
}

String& String::assign(const char* str)
{
	this->buffer = auto_alloc(str);
	return *this;
}

String& String::assign(const size_t count, const char ch)
{
	this->buffer = auto_alloc(count + 1);
	memset(this->buffer, 0x0, count + 1);
	for (size_t i = 0; i < count; i++)
	{
		this->buffer[i] = ch;
	}
	return *this;
}

String& String::assign(const char* str, const size_t count)
{
	size_t size = strlen(str) * count + 1;
	this->buffer = auto_alloc(size);
	memset(this->buffer, 0x0, size);
	for (size_t i = 0; i < count; i++)
	{
		strcat(this->buffer, str);
	}
	return *this;
}

String& String::assign(const String& str, const size_t offset, const size_t count)
{
	char* str_start = str.buffer + offset;
	this->buffer = auto_alloc(count - offset + 1);
	memset(this->buffer, 0x0, count - offset + 1);
	strncpy(this->buffer, str_start, count);
	return *this;
}

String& String::assign(const String& str)
{
	if (this == &str)
		return *this;
	this->buffer = auto_alloc(str.buffer);
	return *this;
}

String& String::assign(const String&& str)
{
	this->buffer = auto_alloc(str.buffer);
	return *this;
}

String& String::replace(const String::iterator first, const String::iterator last, const char* str)
{
	size_t pos = 0, len = strlen(str);

	for (String::iterator si = first; si != last; si++)
		if (*str)
			*si = *(str++);
		else
			pos++;

	size_t i = 0;
	for (char* pointer = this->buffer + len; *pointer; pointer++)
	{
		pointer[i] = pointer[i + pos];
	}
	return *this;
}

String& String::replace(const String::iterator first, const String::iterator last, const char* str, const size_t count)
{
	char* temp = new(std::nothrow) char[count + 1];
	strcpy(temp, str);

	int start_offset = (int)first.get_pointer() - (int)this->buffer;
	size_t i = 0;
	for (char* start = this->buffer + start_offset; (int)start != (int)last.get_pointer(); start++, i++)
	{
		(this->buffer + start_offset)[i] = temp[i];
	}
	delete[] temp;
	return *this;
}

String& String::replace(const String::iterator first, const String::iterator last, size_t count, const char ch)
{
	size_t pos = 0;
	for (String::iterator si = first; si != last; ++si, pos++)
		if (pos < count)
			*si = ch;

	size_t i = 0;
	for (char* pointer = this->buffer + count; *pointer; pointer++)
		pointer[i] = pointer[i + pos - count];

	return *this;
}

void String::pop_back()
{
	this->buffer[this->get_length() - 1] = '\0';
	this->real_len -= 1;
}

void String::push_back(const char ch)
{
	this->operator+=(ch);
}

const char& String::at(const size_t size) const
{
	return this->buffer[size];
}

String String::substr(const size_t off, const size_t count)
{
	char* temp = new(std::nothrow)char[count - off + 2];
	memset(temp, 0x0, count - off + 2);
	strncpy(temp, this->buffer + off, count);
	String str(temp);
	delete[] temp;
	return str;
}

char& String::back()
{
	return this->buffer[this->get_length() - 1];
}

char& String::back() const
{
	return this->buffer[this->get_length() - 1];
}

char& String::front()
{
	return *this->buffer;
}

char& String::front() const
{
	return *this->buffer;
}

size_t String::max_size() const
{
	return (~0) & 0x7fffffff;
}

void String::clear()
{
	memset(this->buffer, 0x0, this->real_len);
	this->real_len = 0;
}

void String::swap(String& str)
{
	String temp = *this;
	*this = str;
	str = temp;
}

size_t String::copy(char* buffer, size_t count, size_t off)
{
	if (!buffer)
		return 0;

	if (count > get_length())
		count = get_length();

	if (off > get_length())
		off = get_length();

	bool flag = true;
	size_t i = 0;
	for (; i < count; i++)
	{
		if (flag)
			buffer[i] = this->at(off++);
		if (this->at(off) == '\0')
			flag = false;
	}
	return i;
}

const char* String::data() const
{
	return this->buffer;
}

bool String::empty() const
{
	return !this->real_len || !this->get_length();
}

int String::compare(const size_t off, const size_t on, const char* str)
{
	char* start = this->buffer + off;
	char* temp = new(std::nothrow) char[on - off + 1];
	memset(temp, 0x0, on - off + 1);
	strncpy(temp, start, on - off);
	int result = strcmp(temp, str);
	delete[] temp;
	return result;
}

int String::compare(const size_t off, const size_t on, const char* str, const size_t count)
{
	char* start = this->buffer + off;
	char* temp = new(std::nothrow) char[on - off + 1];
	memset(temp, 0x0, on - off + 1);
	strncpy(temp, start, on - off);
	int result = strncmp(temp, str, count);
	delete[] temp;
	return result;
}

int String::compare(const char* str) const
{
	return strcmp(this->buffer, str);
}

int String::compare(const String& str) const
{
	return strcmp(this->buffer, str.buffer);
}

int String::compare(const size_t off, const size_t on, const String& str) const
{
	char* start = this->buffer + off;
	char* temp = new(std::nothrow) char[on - off + 1];
	memset(temp, 0x0, on - off + 1);
	strncpy(temp, start, on - off);
	int result = strcmp(temp, str.buffer);
	delete[] temp;
	return result;
}

int String::compare(const size_t off, const size_t on, const String& str, const size_t roff, const size_t ron) const
{
	char* this_start = this->buffer + off;
	char* temp = new(std::nothrow) char[on - off + 1];
	memset(temp, 0x0, on - off + 1);
	strncpy(temp, this_start, on - off);
	char* str_start = str.buffer + roff;
	int result = strncmp(temp, str_start, ron);
	delete[] temp;
	return result;
}

size_t String::find(const char ch, const size_t start) const
{
	size_t pos = 0;
	char* p = nullptr;
	for (p = this->buffer + start; *p; p++, pos++)
	{
		if (*p == ch)
			break;
	}
	return !*p ? ~0U : pos;
}

size_t String::find(const char* str, const size_t start) const
{
	size_t pos = 0, n = strlen(str);
	char* p = nullptr;
	for (p = this->buffer; *p; p++, pos++)
	{
		if (!strncmp(p, str, n))
			break;
	}
	return !*p ? ~0U : pos;
}

size_t String::find(const String& str, const size_t start) const
{
	return String::find(str.buffer, start);
}

size_t String::find(const char* str, const size_t start, const size_t str_start)
{
	return String::find(str + str_start, start);
}

size_t String::find_first_not_of(const char ch, const size_t start) const
{
	return *(this->buffer + start) == ch ? true : false;
}

size_t String::find_first_not_of(const char* str, const size_t start) const
{
	return size_t();
}

size_t String::find_first_not_of(const String& str, const size_t start) const
{
	return size_t();
}

size_t String::find_first_not_of(const char* str, const size_t start, const size_t str_start)
{
	return size_t();
}

String::iterator String::erase(String::const_iterator first, String::const_iterator last)
{
	//"hello world,i am superman,i love chinaA"
	/*得到指针偏移量
	*此处不使用(int *)last.get_pointer() - (int *)first.get_pointer()
	*假如last.get_pointer()地址为：0x00C0A3AF，first.get_pointer()地址为：0X00C0A388
	*0x00C0A3AF - 0X00C0A388 = 0X27;
	*换算成10进制：39
	*int *地址相减还会再/4（因为int *的步长为4字节），就相当于39/4，int除法运算只保留整数，所以就是9。
	*所以此处使用int强制转换来得到指针偏移量
	*/
	/*得到偏移地址总数*/
	int last_first_offset = (int)last.get_pointer() - (int)first.get_pointer();
	//std::cout << "offset:" << last_first_offset << std::endl;
	/*找到开始地址*/
	int start_offset = (int)first.get_pointer() - (int)this->buffer;
	size_t i = 0;
	for (char* p_offset = this->buffer + start_offset; *p_offset; p_offset++, i++)
	{
		(this->buffer + start_offset)[i] = (this->buffer + start_offset)[i + last_first_offset];
	}
	this->real_len -= last_first_offset;
	return String::iterator(last.get_pointer() - last_first_offset);
}

const size_t String::get_capacity() const
{
	return this->capacity;
}

const char* String::c_str() const
{
	return !this->buffer ? "" : this->buffer;
}

String& String::operator=(const String& str)
{
#if DEBUG
	std::cout << "String & String::operator=(const String & str)" << std::endl;
#endif
	if (this == &str)
		return *this;
	this->buffer = auto_alloc(str.buffer);
	return *this;
}

String& String::operator=(const char* str)
{
#if DEBUG
	std::cout << "String & String::operator=(const char * str)" << std::endl;
#endif
	this->buffer = auto_alloc(str);
	return *this;
}

String& String::operator=(const char ch)
{
	char buffer[2];
	buffer[0] = ch;
	buffer[1] = '\0';
	this->buffer = auto_alloc(buffer);
	return *this;
}

String& String::operator+=(const String& str)
{
	this->buffer = auto_alloc(this->buffer, str.buffer);
	return *this;
}

String& String::operator+=(const char* str)
{
	this->buffer = auto_alloc(this->buffer, str);
	return *this;
}

String& String::operator+=(const char ch)
{
	char buffer[2];
	buffer[0] = ch;
	buffer[1] = '\0';
	this->buffer = auto_alloc(this->buffer, buffer);
	return *this;
}

String String::operator+(const String& str)
{
	return String(auto_alloc(this->buffer, str.buffer, false));
}

String String::operator+(const char* str)
{
	return String(auto_alloc(this->buffer, str, false));
}

String String::operator+(const char ch)
{
	char str[2];
	str[0] = ch;
	str[1] = '\0';
	return String(auto_alloc(this->buffer, str, false));
}

String operator+(const char* ch, const String& str)
{
	return String(str.auto_alloc(ch, str.buffer, false));
}

String operator+(const char ch, const String& str)
{
	char buffer[2];
	buffer[0] = ch;
	buffer[1] = '\0';
	return String(str.auto_alloc(buffer, str.buffer, false));
}

bool operator==(const String& str1, const String& str2)
{
	return !strcmp(str1.buffer, str2.buffer);
}

String operator-(const char* ch, const String& str)
{
	String s(ch);
	s.string_subtraction(str.c_str());
	return s;
}
String String::operator-(const String& str)
{
	String s(this->buffer);
	s.string_subtraction(str.c_str());
	return s;
}

String String::operator-(const char* str)
{
	String s(this->buffer);
	s.string_subtraction(str);
	return s;
}

String String::operator-(const char ch)
{
	String s(this->buffer);
	size_t pos = 0;
	for (char* pointer = s.buffer; *pointer != '\0'; pointer++, pos++)
	{
		if (*pointer == ch)
		{
			for (size_t i = pos; i < s.get_length(); i++)
			{
				s.buffer[i] = s.buffer[i + 1];
			}
		}
	}
	return s;
}

String& String::operator-=(const String& str)
{
	this->string_subtraction(str.c_str());
	return *this;
}

String& String::operator-=(const char* str)
{
	this->string_subtraction(str);
	return *this;
}

String& String::operator-=(const char ch)
{
	size_t pos = 0;
	for (char* pointer = this->buffer; *pointer != '\0'; pointer++, pos++)
	{
		if (*pointer == ch)
		{
			for (size_t i = pos; i < get_length(); i++)
			{
				this->buffer[i] = this->buffer[i + 1];
			}
		}
	}
	return *this;
}

String String::operator*(const size_t count) const
{
	String str(this->real_len * count);
	for (size_t i = 0, pos = 0; i < count; i++)
	{
		for (size_t j = 0; j < this->real_len - 1; j++)
		{
			str.buffer[pos++] = this->buffer[j];
		}
	}
	return str;
}

String& String::operator*=(const size_t count)
{
	do
	{
		if (!this->real_len || !this->buffer || !count)
		{
			break;
		}

		size_t real_length = this->real_len;
		char* buffer = new(std::nothrow) char[real_length];
		if (!buffer)
		{
			break;
		}
		strcpy(buffer, this->buffer);
		delete[] this->buffer;
		this->real_len = this->get_length() * count + 1;
		this->buffer = new(std::nothrow) char[this->real_len];
		/*如果内存分配失败，还原this->buffer,this->real_len*/
		if (!buffer)
		{
			this->real_len = real_length;
			this->buffer = new(std::nothrow) char[this->real_len];
			strcpy(this->buffer, buffer);
			delete[] buffer;
			break;
		}
		memset(this->buffer, 0x0, this->real_len);
		for (size_t i = 0, j = 0; i < this->get_length(); i++, j++)
		{
			if (j == real_length - 1)
				j = 0;
			this->buffer[i] = buffer[j];
		}
		delete[] buffer;
	} while (false);
	return *this;
}

String operator*(const size_t count, const String& str)
{
	/*调用String operator*(const size_t count) const;*/
	return str * count;
}

bool String::operator==(const String& str)
{
	return !strcmp(this->buffer, str.buffer);
}

bool String::operator==(const char* str)
{
	return !strcmp(this->buffer, str);
}

bool String::operator>(const String& str)
{
	return (strcmp(this->buffer, str.buffer) > 0);
}

bool String::operator>(const char* str)
{
	return (strcmp(this->buffer, str) > 0);
}

bool String::operator<(const char* str)
{
	return (strcmp(this->buffer, str) < 0);
}

bool String::operator<(const String& str)
{
	return (strcmp(this->buffer, str.buffer) < 0);
}

String::operator size_t() const
{
	return this->get_length();
}

String::operator int() const
{
	return (int)this->get_length();
}

String::operator wchar_t* () const
{
	wchar_t* _buffer = new(std::nothrow) wchar_t[this->real_len];
	if (!_buffer)
	{
		return _buffer;
	}
	size_t size = mbstowcs(_buffer, this->buffer, this->get_length());
	if (size != this->get_length())
	{
		delete[] _buffer;
		_buffer = nullptr;
	}
	return _buffer;
}

char& String::operator[](const size_t count)
{
	return this->buffer[count];
}

const char& String::operator[](const size_t count) const
{
	return this->buffer[count];
}

const size_t String::get_length() const
{
	return this->real_len == 0 ? 0 : this->real_len - 1;
}

void String::reserve(size_t new_size)
{
	this->capacity = new_size;
}

std::ostream& operator<<(std::ostream& out, const String& str)
{
	if (!str.buffer)
		out << "";
	else
		out << str.buffer;
	return out;
}

std::istream& operator>>(std::istream& in, String& str)
{
	char buf[BUFFSIZE] = {};
	in.getline(buf, BUFFSIZE);
	str.buffer = str.auto_alloc(buf);
	strcpy(str.buffer, buf);
	return in;
}

String::iterator::iterator() :pointer(nullptr)
{
#if DEBUG
	std::cout << "String::iterator::iterator()" << std::endl;
#endif
}

String::iterator::iterator(const iterator& iter) : pointer(nullptr)
{
#if DEBUG
	std::cout << "String::iterator::iterator(const iterator &iter)" << std::endl;
#endif
	this->pointer = iter.pointer;
}

String::iterator::iterator(char* pointer)
{
#if DEBUG
	std::cout << "String::iterator::iterator(char * pointer)" << std::endl;
#endif
	this->pointer = pointer;
}

String::iterator::iterator(iterator&& right)
{
#if DEBUG
	std::cout << "String::iterator::iterator(iterator && right)" << std::endl;
#endif
	this->pointer = right.pointer;
	right.pointer = nullptr;
}

String::iterator::~iterator()
{
#if DEBUG
	std::cout << "String::iterator::~iterator()" << std::endl;
#endif
	this->pointer = nullptr;
}

char& String::iterator::operator*() const
{
	return *this->pointer;
}

String::iterator& String::iterator::operator=(const iterator& iter)
{
	this->pointer = iter.pointer;
	return *this;
}

bool String::iterator::operator!=(const iterator& iter)
{
	return (int*)this->pointer != (int*)iter.pointer;
}

const String::iterator String::iterator::operator++(int)
{
	String::iterator iter = *this;
	++this->pointer;
	return iter;
}

String::iterator& String::iterator::operator++()
{
	this->pointer = this->pointer + 1;
	return *this;
}

const String::iterator String::iterator::operator--(int)
{
	String::iterator iter = *this;
	--this->pointer;
	return iter;
}

String::iterator& String::iterator::operator--()
{
	this->pointer = this->pointer - 1;
	return *this;
}

String::iterator String::iterator::operator+(int i) const
{
	String::iterator si = *this;
	si.pointer += i;
	return si;
}

String::iterator String::iterator::operator-(int i) const
{
	String::iterator si = *this;
	si.pointer -= i;
	return si;
}

char* String::iterator::get_pointer() const
{
	return this->pointer;
}

String::reverse_iterator::reverse_iterator() :pointer(nullptr)
{
#if DEBUG
	std::cout << "String::reverse_iterator::reverse_iterator()" << std::endl;
#endif
}

String::reverse_iterator::reverse_iterator(const reverse_iterator& riter) : pointer(riter.pointer)
{
#if DEBUG
	std::cout << "String::reverse_iterator::reverse_iterator(const reverse_iterator &riter)" << std::endl;
#endif
}

String::reverse_iterator::reverse_iterator(char* pointer) :pointer(pointer)
{
#if DEBUG
	std::cout << "String::reverse_iterator::reverse_iterator(char * pointer,size_t length)" << std::endl;
#endif
}

String::reverse_iterator::reverse_iterator(reverse_iterator&& right)
{
#if DEBUG
	std::cout << "String::reverse_iterator::reverse_iterator(reverse_iterator && right)" << std::endl;
#endif
	this->pointer = right.pointer;
	right.pointer = nullptr;
}

String::reverse_iterator& String::reverse_iterator::operator=(const reverse_iterator& riter)
{
	this->pointer = riter.pointer;
	return *this;
}

String::reverse_iterator::~reverse_iterator()
{
#if DEBUG
	std::cout << "String::reverse_iterator::~reverse_iterator()" << std::endl;
#endif
	this->pointer = nullptr;
}

char& String::reverse_iterator::operator*() const
{
	return *this->pointer;
}

bool String::reverse_iterator::operator!=(const reverse_iterator& iter)
{
	return (int*)this->pointer != (int*)iter.pointer;
}

const String::reverse_iterator String::reverse_iterator::operator++(int)
{
	String::reverse_iterator riter = *this;
	--this->pointer;
	return riter;
}

String::reverse_iterator& String::reverse_iterator::operator++()
{
	this->pointer -= 1;
	return *this;
}

const String::reverse_iterator String::reverse_iterator::operator--(int)
{
	String::reverse_iterator riter = *this;
	++this->pointer;
	return riter;
}

String::reverse_iterator& String::reverse_iterator::operator--()
{
	this->pointer += 1;
	return *this;
}

String::reverse_iterator String::reverse_iterator::operator+(int i) const
{
	String::reverse_iterator s = *this;
	s.pointer -= i;
	return s;
}

String::reverse_iterator String::reverse_iterator::operator-(int i) const
{
	String::reverse_iterator s = *this;
	s.pointer += i;
	return s;
}

char* String::reverse_iterator::get_pointer() const
{
	return this->pointer;
}
