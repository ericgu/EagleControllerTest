#pragma once

class EEPROMClass
{
public:
	EEPROMClass()
	{
		_storedSize = -1;
		_committed = 0;
	}

	void begin(int size) {
		_storedSize = size;
	}

	void commit() 
	{
		_committed = true;
	}

	void write(int offset, char data) 
	{
		_data[offset] = data;
	}

	char read(int offset) {
		return _data[offset];
	}

	int _storedSize;
	int _committed;

	char _data[4096];
};

EEPROMClass EEPROM;	


