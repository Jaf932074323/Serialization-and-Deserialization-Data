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
时间:2020-12/20
描述:组包与解包测试
**************************************************************************/
#include "SddHead.h"
#include <string>

const std::string g_strHead = "Head"; // 用"Head"4个字节表示包头
const std::string g_strTail = "Tail"; // 用"Tail"4个字节表示包尾,用于比较是否是Tail开头

// 包头
class CPackHead :public jaf::CPackHeadBase
{
public:
	CPackHead()
	{
		// 定义包头序列化方式
		SDD_ADD_ITEM(SDD_STRING(m_strHead, 4)); // 序列化用"Head"4个字节表示的包头
		SDD_ADD_ITEM(SDD_INTERGER(unsigned int, m_rEndian, m_nType, 4)); // 序列化包类型
		SDD_ADD_ITEM(SDD_INTERGER(size_t, m_rEndian, m_nContentLength, 4)); // 序列化包内容长度
	};
	virtual ~CPackHead() {};

	// 查找头所在位置
	// pData 要查找头的数据
	// rIndex 用于返回索引。如果找到则返回头第一个字节的位置索引；如果没有找，则这个索引之前的所有数据都是无效的
	// 返回头是否找到索引
	virtual bool SeekHead(const char* pData, size_t nLength, size_t& rIndex)
	{
		jaf::CBuffer buff;
		buff.Write(pData, nLength);
		return buff.SeekFront(g_strHead.c_str(), 4, rIndex);
	}

	// 获取包内容的长度
	virtual size_t GetContentLen()
	{
		return m_nContentLength;
	}
	// 获取包类型
	virtual unsigned int GetType()
	{
		return m_nType;
	}
	// 检查包头是否正确
	virtual bool Check()
	{
		return true;
	}

public:
	std::string m_strHead = g_strHead; // 包头
	unsigned int m_nType = 0; // 包类型
	size_t m_nContentLength = 0; // 包内容长度
};

class CPackTail :public jaf::CPackTailBase
{
public:
	CPackTail()
	{
		// 定义包尾序列化方式
		SDD_ADD_ITEM(SDD_STRING(m_strTail, 4)); // 序列化用"Head"4个字节表示的包头
	};
	virtual ~CPackTail() {};

	// 检查包尾是否正确
	// pPackBuffer 整个包缓存的首地址，包括头、尾和中间内容
	// nTotalLength 整个包缓存的长度，包括头、尾和中间内容
	virtual bool Check(const char* pPackBuffer, size_t nTotalLength)
	{
		return m_strTail == g_strTail;
	}

protected:
	std::string m_strTail = g_strTail; // 用4个字节表示包尾
};

// 定义包A
class CPackA :public jaf::CPackBase
{
public:
	CPackA() 
	{
		// 定义A包序列化方式
		SDD_ADD_ITEM(SDD_STRING(m_str, 10)); // 包A要序列化一个10字节长度的字符串
		SDD_ADD_ITEM(SDD_INTERGER(char, m_rEndian, m_char, 1)); // 还要序列化1个字符
	};
	~CPackA() {};

	// 创建A包的函数
	static std::shared_ptr<CPackBase> Create(char* pData, size_t nLen)
	{
		std::shared_ptr<CPackA> pPack = std::make_shared<CPackA>();
		jaf::CBuffReader reader(pData, nLen);
		pPack->BufferToData(reader);
		return pPack;
	}

	static unsigned int GetType()
	{
		return 1; // 包A的类型
	}
public:
	std::string m_str;
	char m_char = 0;
};


// 定义包B
class CPackB :virtual public jaf::CPackBase
{
public:
	CPackB() 
	{
		// 定义B包序列化方式
		SDD_ADD_ITEM(SDD_INTERGER(short int, m_rEndian, m_number, 2)); // 包B要序列化一个短整形数字
	};
	~CPackB() {};

	// 创建B包的函数
	static std::shared_ptr<jaf::CPackBase> Create(char* pData, size_t nLen)
	{
		std::shared_ptr<CPackB> pPack = std::make_shared<CPackB>();
		jaf::CBuffReader reader(pData, nLen);
		pPack->BufferToData(reader);
		return pPack;
	}

	static unsigned int GetType()
	{
		return 2; // 包B的类型
	}

public:
	short int m_number = 0;
};

// 包处理
class CDealPack :public jaf::CDealPackInterface
{
public:
	// 处理包
	// nPackType 包类型
	// rPackage 包对象
	virtual void Deal(size_t nPackType, std::shared_ptr<jaf::CPackBase>& rPackage)
	{
		switch (nPackType)
		{
		case 1:
		{
			std::shared_ptr<CPackA> p = std::dynamic_pointer_cast<CPackA>(rPackage);
			std::cout << "解析出了A包,类型为:" << nPackType << ",值:" << p->m_str << ',' << p->m_char << std::endl;
		}
		break;
		case 2:
		{
			std::shared_ptr<CPackB> p = std::dynamic_pointer_cast<CPackB>(rPackage);
			std::cout << "解析出了B包,类型为:" << nPackType << ",值:" << p->m_number << std::endl;
		}
		break;
		default:
			std::cout << "解析出了未知的包，类型为:" << nPackType << std::endl;
			break;
		}
	}

};

void TestPackAndUnpack()
{
	std::cout << "开始测试,组包与解包" << std::endl;

	CPackHead head; // 头
	CPackTail tail; // 尾
	CDealPack dealPack; // 处理包的对象
	jaf::CPackFactory packFactory; // 定义一个创建包的工厂
	// 注册包A和包B，注册后就可以创建包A和包B了
	packFactory.RegisterCreateFun(CPackA::GetType(), CPackA::Create);
	packFactory.RegisterCreateFun(CPackB::GetType(), CPackB::Create);
	jaf::CParsePackHeadTail parsePack(head, tail, packFactory); // 用于解析数据包
	parsePack.SetDealPack(&dealPack);

	// 实例化一个A包和B包
	CPackA a;
	a.m_str = "CPackA";
	a.m_char = 'A';
	CPackB b;
	b.m_number = 2;


	jaf::CBuffer buff; // 实例化一个缓冲区

	std::string strDestroy = "Destroy"; // 破坏包序列化的字符串

	// 加入干扰
	std::string strInterference1 = "Interference factor1";
	buff.Write(strInterference1.c_str(), strInterference1.size());

	// 将A包序列化，存储在buff中
	head.m_nType = CPackA::GetType();
	head.m_nContentLength = a.GetBufferLength();
	head.DataToBuffer(buff);
	a.DataToBuffer(buff);
	//buff.Write(strDestroy.c_str(), strDestroy.size()); // 破坏A包的序列化
	tail.DataToBuffer(buff);

	// 加入干扰
	std::string strInterference2 = "Interference factor2";
	buff.Write(strInterference2.c_str(), strInterference2.size());

	// 将B包序列化
	head.m_nType = CPackB::GetType();
	head.m_nContentLength = b.GetBufferLength();
	head.DataToBuffer(buff);
	//buff.Write(strDestroy.c_str(), strDestroy.size()); // 破坏B包的序列化
	b.DataToBuffer(buff);
	tail.DataToBuffer(buff);

	// 加入干扰
	std::string strInterference3 = "Interference factor1";
	buff.Write(strInterference3.c_str(), strInterference3.size());


	// 解包
	jaf::CBuffReader reader;
	parsePack.NewData(buff.GetBuffer(), buff.GetWriteLength());

	std::cout << "结束测试,组包与解包" << std::endl;
}