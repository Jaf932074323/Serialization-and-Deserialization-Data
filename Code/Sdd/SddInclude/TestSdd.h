#pragma once
//MIT License
//
//Copyright(c) 2021 Jaf932074323 姜安富
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this softwareand associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions :
//
//The above copyright noticeand this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.
/**************************************************************************
作者:姜安富
时间:2020-11-5
描述:序列化和反序列化测试文件
**************************************************************************/
#include "SddHead.h"
#include <iostream>
#include <iomanip>

#ifndef STR
#define STR(R)  #R
#endif // !STR

// 显示变量
#define TEST_COMPARE_SHOW(variableName) \
std::cout << "rTest1." << STR(variableName) << ":" << rTest1.variableName << std::endl; \
std::cout << "rTest2." << STR(variableName) << ":" << rTest2.variableName << std::endl;

// 显示数字的16进制形式
#define TEST_COMPARE_SHOW_HEX(variableName) \
std::cout << std::hex;\
std::cout << "rTest1." << STR(variableName) << ":0x" \
<< std::setfill('0')<< std::setw(2*sizeof(variableName)) << (int)rTest1.variableName << std::endl; \
std::cout << "rTest2." << STR(variableName) << ":0x" \
<< std::setfill('0')<< std::setw(2*sizeof(variableName)) << (int)rTest2.variableName << std::endl; \
std::cout << std::dec; 

// 显示字符的16进制形式
#define TEST_COMPARE_SHOW_CHAR_HEX(variableName) \
std::cout << std::hex;\
std::cout << "rTest1." << STR(variableName) << ":0x" \
<< std::setfill('0')<< std::setw(2*sizeof(variableName)) << (int)*(unsigned char*)&rTest1.variableName << std::endl; \
std::cout << "rTest2." << STR(variableName) << ":0x" \
<< std::setfill('0')<< std::setw(2*sizeof(variableName)) << (int)*(unsigned char*)&rTest2.variableName << std::endl; \
std::cout << std::dec; 

struct SChunk
{
	int m_nNumber = 0;
	double m_f = 0;
};

class CSddTest :public jaf::CSddBase
{
public:
	CSddTest() :CSddBase(jaf::E_ENDIAN::E_ENDIAN_NULL)
	{
		Initialize();
	}

	virtual void Initialize()
	{
		SDD_ADD_ITEM(SDD_STRING(m_strName, 5));
		SDD_ADD_ITEM(SDD_INTERGER(int, m_rEndian, m_nNumber1, 4));
		SDD_ADD_ITEM(SDD_INTERGER(int, m_rEndian, m_nNumber2, 2));
		SDD_ADD_ITEM(SDD_INTERGER(int, m_rEndian, m_nNumber3, 4));
		SDD_ADD_ITEM(SDD_INTERGER(size_t, m_rEndian, m_nUnsignedNumber, 2));
		SDD_ADD_ITEM(SDD_INTERGER(short, m_rEndian, m_nShort, 2));
		SDD_ADD_ITEM(SDD_INTERGER(char, m_rEndian, m_c, 1));
		SDD_ADD_ITEM(SDD_DOUBLE(m_d));
		SDD_ADD_ITEM(SDD_FLOAT(m_f));
		SDD_ADD_ITEM(SDD_CHUNK((void*)&m_chunk, sizeof(SChunk)));
		SDD_ADD_ITEM(SDD_PLACEHOLDER(2, 'a'));

		std::shared_ptr<jaf::CSddBitItem> item = std::make_shared<jaf::CSddBitItem>(4);
		item->AddChildBitItem(std::make_shared<jaf::CSddBoolBit>(m_b1, 0));
		item->AddChildBitItem(std::make_shared<jaf::CSddBoolBit>(m_b2, 1));
		item->AddChildBitItem(std::make_shared<jaf::CSddCharBit>(m_cBit1, 2, 7));
		item->AddChildBitItem(std::make_shared<jaf::CSddCharBit>(m_cBit2, 9, 5));
		item->AddChildBitItem(std::make_shared<jaf::CSddCharBit>(m_cBit3, 16, 8));
		SDD_ADD_ITEM(item);
	}

public:
	// 对比显示两个测试类实例
	static void CompareShow(CSddTest& rTest1, CSddTest& rTest2)
	{
		TEST_COMPARE_SHOW(m_strName);
		TEST_COMPARE_SHOW_HEX(m_nNumber1);
		TEST_COMPARE_SHOW_HEX(m_nNumber2);
		TEST_COMPARE_SHOW(m_nNumber3);
		TEST_COMPARE_SHOW_HEX(m_nUnsignedNumber);
		TEST_COMPARE_SHOW_HEX(m_nShort);
		TEST_COMPARE_SHOW_CHAR_HEX(m_c);
		TEST_COMPARE_SHOW(m_d);
		TEST_COMPARE_SHOW(m_f);
		TEST_COMPARE_SHOW(m_chunk.m_nNumber);
		TEST_COMPARE_SHOW(m_chunk.m_f);
		TEST_COMPARE_SHOW(m_b1);
		TEST_COMPARE_SHOW(m_b2);
		TEST_COMPARE_SHOW_CHAR_HEX(m_cBit1);
		TEST_COMPARE_SHOW_CHAR_HEX(m_cBit2);
		TEST_COMPARE_SHOW_CHAR_HEX(m_cBit3);
	}

	std::string m_strName = "";
	int m_nNumber1 = 0;
	int m_nNumber2 = 0;
	int m_nNumber3 = 0;
	size_t m_nUnsignedNumber = 0;
	short m_nShort = 0;
	char m_c = 0;
	double m_d = 0;
	float m_f = 0;
	SChunk m_chunk;
	bool m_b1 = false;
	bool m_b2 = false;
	char m_cBit1 = 0x00;
	char m_cBit2 = 0x00;
	char m_cBit3 = 0x00;
};

void TestSdd()
{
	std::cout << "开始测试,包的序列化与反序列化" << std::endl;
	jaf::CBuffer buffer;
	jaf::CBuffReader buffReader;

	jaf::CSddEndianManage::SetDefaultEndian(jaf::E_ENDIAN::E_ENDIAN_LITTLE);
	CSddTest test1;
	CSddTest test2;
	test1.m_strName = "123456";
	test1.m_nNumber1 = 0x12345678;
	test1.m_nNumber2 = 0x12345678;
	test1.m_nNumber3 = -100;
	test1.m_nUnsignedNumber = -1000;
	test1.m_nShort = 0x1234;
	test1.m_c = 0x12;
	test1.m_d = 0.25;
	test1.m_f = 0.5;
	test1.m_chunk.m_nNumber = 99;
	test1.m_chunk.m_f = 9.9;
	test1.m_b1 = true;
	test1.m_b2 = true;
	test1.m_cBit1 = (char)0xff;
	test1.m_cBit2 = (char)0xff;
	test1.m_cBit3 = (char)0xff;

	test1.DataToBuffer(buffer);
	buffReader.Attach(buffer.GetBuffer(), buffer.GetWriteLength());
	std::cout << "缓冲区已写入：" << buffer.GetWriteLength() << "已读取:" << buffReader.GetReadOffset() << std::endl;

	if (!test2.BufferToData(buffReader))
	{
		std::cout << "从缓冲区读取数据出错" << std::endl;
		return;
	}
	CSddTest::CompareShow(test1, test2);
	std::cout << "缓冲区已写入：" << buffer.GetWriteLength() << "已读取:" << buffReader.GetReadOffset() << std::endl;

	std::cout << "结束测试,包的序列化与反序列化" << std::endl;
}