#pragma once
class str
{
private:
	char* buff;
	unsigned int size_buff;
public:
	str(const char* s)
	{
		size_buff = strlen(s);
		buff = new char[size_buff + 1];
		memcpy(buff, s, size_buff);
		buff[size_buff] = 0;
	}
	str(const str& other)
		: size_buff(other.size_buff + 1)
	{
		buff = new char[size_buff];
		memcpy(buff, other.buff, size_buff + 1);

	}
	~str()
	{
		delete[] buff;
	}
	friend ostream& operator<<(ostream& stream, const str& string);
};

ostream& operator<<(ostream& stream, const str& string)
{
	stream << string.buff;
	return stream;
}
