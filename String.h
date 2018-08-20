#pragma once

#define NULL 0
#include <string.h>
#include <malloc.h>

class String
{
public:
	String::String(const char *cstr) {
		init();
		if (cstr)
			copy(cstr, strlen(cstr));
	}

  String::String()
  {
    init();
  }

	String & String::copy(const char *cstr, unsigned int length) {
		if (!reserve(length)) {
			invalidate();
			return *this;
		}
		len = length;
		strcpy(buffer, cstr);
		return *this;
	}

#if test
	String & String::copy(const __FlashStringHelper *pstr, unsigned int length) {
		if (!reserve(length)) {
			invalidate();
			return *this;
		}
		len = length;
		strcpy_P(buffer, (PGM_P)pstr);
		return *this;
	}
#endif

	const char* c_str() const { return buffer; }

	int String::compareTo(const String &s) const {
		if (!buffer || !s.buffer) {
			if (s.buffer && s.len > 0)
				return 0 - *(unsigned char *)s.buffer;
			if (buffer && len > 0)
				return *(unsigned char *)buffer;
			return 0;
		}
		return strcmp(buffer, s.buffer);
	}

  bool String::startsWith(const String &s) const
  {
    return strncmp(buffer, s.buffer, s.len) == 0;
  }

  int length() const
  {
    return len;
  }

  void toCharArray(char* pBuffer, int bufferSize) const
  {
    strncpy(pBuffer, buffer, bufferSize);
  }

  unsigned char String::concat(const char *cstr, unsigned int length) {
    unsigned int newlen = len + length;
    if (!cstr)
      return 0;
    if (length == 0)
      return 1;
    if (!reserve(newlen))
      return 0;
    strcpy(buffer + len, cstr);
    len = newlen;
    return 1;
  }

  unsigned char String::concat(const char *cstr) {
    if (!cstr)
      return 0;
    return concat(cstr, strlen(cstr));
  }

  unsigned char String::concat(const String &rhs)
  {
    return concat(rhs.c_str());
  }

  char String::charAt(unsigned int loc) const {
    return buffer[loc];
  }

  void String::setCharAt(unsigned int loc, char c) {
    if (loc < len)
      buffer[loc] = c;
  }

  String String::substring(unsigned int left, unsigned int right) const {
    if (left > right) {
      unsigned int temp = right;
      right = left;
      left = temp;
    }
    String out;
    if (left >= len)
      return out;
    if (right > len)
      right = len;
    char temp = buffer[right];  // save the replaced character
    buffer[right] = '\0';
    out = buffer + left;  // pointer arithmetic
    buffer[right] = temp;  //restore character
    return out;
  }

  int String::indexOf(char c) const {
    return indexOf(c, 0);
  }

  int String::indexOf(char ch, unsigned int fromIndex) const {
    if (fromIndex >= len)
      return -1;
    const char* temp = strchr(buffer + fromIndex, ch);
    if (temp == NULL)
      return -1;
    return temp - buffer;
  }

  long String::toInt(void) const {
    if (buffer)
      return atol(buffer);
    return 0;
  }

	unsigned char operator ==(const char *cstr) const {
		return equals(cstr);
	}
	unsigned char operator ==(const String &rhs) const {
		return equals(rhs);
	}
	unsigned char String::equals(const String &s2) const {
		return (len == s2.len && compareTo(s2) == 0);
	}
  unsigned char operator !=(const String &rhs) const {
    return !equals(rhs);
  }
	unsigned char String::equals(const char *cstr) const {
		if (len == 0)
			return (cstr == NULL || *cstr == 0);
		if (cstr == NULL)
			return buffer[0] == 0;
		return strcmp(buffer, cstr) == 0;
	}

	unsigned char String::operator<(const String &rhs) const {
		return compareTo(rhs) < 0;
	}

	unsigned char String::operator>(const String &rhs) const {
		return compareTo(rhs) > 0;
	}

	unsigned char String::operator<=(const String &rhs) const {
		return compareTo(rhs) <= 0;
	}

	unsigned char String::operator>=(const String &rhs) const {
		return compareTo(rhs) >= 0;
	}

	friend std::ostream& operator<<(std::ostream &os, const String &rhs) {
		return os << rhs.buffer;
	}


protected:
	char *buffer;	        // the actual char array
	unsigned int capacity;  // the array length minus one (for the '\0')
	unsigned int len;       // the String length (not counting the '\0')

	inline void String::init(void) {
		buffer = NULL;
		capacity = 0;
		len = 0;
	}

	void String::invalidate(void) {
		if (buffer)
			free(buffer);
		init();
	}

	unsigned char String::reserve(unsigned int size) {
		if (buffer && capacity >= size)
			return 1;
		if (changeBuffer(size)) {
			if (len == 0)
				buffer[0] = 0;
			return 1;
		}
		return 0;
	}

	unsigned char String::changeBuffer(unsigned int maxStrLen) {
		size_t newSize = (maxStrLen + 16) & (~0xf);
		char *newbuffer = (char *)realloc(buffer, newSize);
		if (newbuffer) {
			size_t oldSize = capacity + 1; // include NULL.
			if (newSize > oldSize)
			{
				memset(newbuffer + oldSize, 0, newSize - oldSize);
			}
			capacity = newSize - 1;
			buffer = newbuffer;
			return 1;
		}
		return 0;
	}
};
