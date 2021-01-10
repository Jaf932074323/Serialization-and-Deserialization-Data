#pragma once
//MIT License
//
//Copyright(c) 2021 Jaf932074323 ������
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
����:������
ʱ��:2020-12/20
����:�����������
**************************************************************************/
#include "SddHead.h"
#include <string>

const std::string g_strHead = "Head"; // ��"Head"4���ֽڱ�ʾ��ͷ
const std::string g_strTail = "Tail"; // ��"Tail"4���ֽڱ�ʾ��β,���ڱȽ��Ƿ���Tail��ͷ

// ��ͷ
class CPackHead :public jaf::CPackHeadBase
{
public:
	CPackHead()
	{
		// �����ͷ���л���ʽ
		SDD_ADD_ITEM(SDD_STRING(m_strHead, 4)); // ���л���"Head"4���ֽڱ�ʾ�İ�ͷ
		SDD_ADD_ITEM(SDD_INTERGER(unsigned int, m_rEndian, m_nType, 4)); // ���л�������
		SDD_ADD_ITEM(SDD_INTERGER(size_t, m_rEndian, m_nContentLength, 4)); // ���л������ݳ���
	};
	virtual ~CPackHead() {};

	// ����ͷ����λ��
	// pData Ҫ����ͷ������
	// rIndex ���ڷ�������������ҵ��򷵻�ͷ��һ���ֽڵ�λ�����������û���ң����������֮ǰ���������ݶ�����Ч��
	// ����ͷ�Ƿ��ҵ�����
	virtual bool SeekHead(const char* pData, size_t nLength, size_t& rIndex)
	{
		jaf::CBuffer buff;
		buff.Write(pData, nLength);
		return buff.SeekFront(g_strHead.c_str(), 4, rIndex);
	}

	// ��ȡ�����ݵĳ���
	virtual size_t GetContentLen()
	{
		return m_nContentLength;
	}
	// ��ȡ������
	virtual unsigned int GetType()
	{
		return m_nType;
	}
	// ����ͷ�Ƿ���ȷ
	virtual bool Check()
	{
		return true;
	}

public:
	std::string m_strHead = g_strHead; // ��ͷ
	unsigned int m_nType = 0; // ������
	size_t m_nContentLength = 0; // �����ݳ���
};

class CPackTail :public jaf::CPackTailBase
{
public:
	CPackTail()
	{
		// �����β���л���ʽ
		SDD_ADD_ITEM(SDD_STRING(m_strTail, 4)); // ���л���"Head"4���ֽڱ�ʾ�İ�ͷ
	};
	virtual ~CPackTail() {};

	// ����β�Ƿ���ȷ
	// pPackBuffer ������������׵�ַ������ͷ��β���м�����
	// nTotalLength ����������ĳ��ȣ�����ͷ��β���м�����
	virtual bool Check(const char* pPackBuffer, size_t nTotalLength)
	{
		return m_strTail == g_strTail;
	}

protected:
	std::string m_strTail = g_strTail; // ��4���ֽڱ�ʾ��β
};

// �����A
class CPackA :public jaf::CPackBase
{
public:
	CPackA() 
	{
		// ����A�����л���ʽ
		SDD_ADD_ITEM(SDD_STRING(m_str, 10)); // ��AҪ���л�һ��10�ֽڳ��ȵ��ַ���
		SDD_ADD_ITEM(SDD_INTERGER(char, m_rEndian, m_char, 1)); // ��Ҫ���л�1���ַ�
	};
	~CPackA() {};

	// ����A���ĺ���
	static std::shared_ptr<CPackBase> Create(char* pData, size_t nLen)
	{
		std::shared_ptr<CPackA> pPack = std::make_shared<CPackA>();
		jaf::CBuffReader reader(pData, nLen);
		pPack->BufferToData(reader);
		return pPack;
	}

	static unsigned int GetType()
	{
		return 1; // ��A������
	}
public:
	std::string m_str;
	char m_char = 0;
};


// �����B
class CPackB :virtual public jaf::CPackBase
{
public:
	CPackB() 
	{
		// ����B�����л���ʽ
		SDD_ADD_ITEM(SDD_INTERGER(short int, m_rEndian, m_number, 2)); // ��BҪ���л�һ������������
	};
	~CPackB() {};

	// ����B���ĺ���
	static std::shared_ptr<jaf::CPackBase> Create(char* pData, size_t nLen)
	{
		std::shared_ptr<CPackB> pPack = std::make_shared<CPackB>();
		jaf::CBuffReader reader(pData, nLen);
		pPack->BufferToData(reader);
		return pPack;
	}

	static unsigned int GetType()
	{
		return 2; // ��B������
	}

public:
	short int m_number = 0;
};

// ������
class CDealPack :public jaf::CDealPackInterface
{
public:
	// �����
	// nPackType ������
	// rPackage ������
	virtual void Deal(size_t nPackType, std::shared_ptr<jaf::CPackBase>& rPackage)
	{
		switch (nPackType)
		{
		case 1:
		{
			std::shared_ptr<CPackA> p = std::dynamic_pointer_cast<CPackA>(rPackage);
			std::cout << "��������A��,����Ϊ:" << nPackType << ",ֵ:" << p->m_str << ',' << p->m_char << std::endl;
		}
		break;
		case 2:
		{
			std::shared_ptr<CPackB> p = std::dynamic_pointer_cast<CPackB>(rPackage);
			std::cout << "��������B��,����Ϊ:" << nPackType << ",ֵ:" << p->m_number << std::endl;
		}
		break;
		default:
			std::cout << "��������δ֪�İ�������Ϊ:" << nPackType << std::endl;
			break;
		}
	}

};

void TestPackAndUnpack()
{
	std::cout << "��ʼ����,�������" << std::endl;

	CPackHead head; // ͷ
	CPackTail tail; // β
	CDealPack dealPack; // ������Ķ���
	jaf::CPackFactory packFactory; // ����һ���������Ĺ���
	// ע���A�Ͱ�B��ע���Ϳ��Դ�����A�Ͱ�B��
	packFactory.RegisterCreateFun(CPackA::GetType(), CPackA::Create);
	packFactory.RegisterCreateFun(CPackB::GetType(), CPackB::Create);
	jaf::CParsePackHeadTail parsePack(head, tail, packFactory); // ���ڽ������ݰ�
	parsePack.SetDealPack(&dealPack);

	// ʵ����һ��A����B��
	CPackA a;
	a.m_str = "CPackA";
	a.m_char = 'A';
	CPackB b;
	b.m_number = 2;


	jaf::CBuffer buff; // ʵ����һ��������

	std::string strDestroy = "Destroy"; // �ƻ������л����ַ���

	// �������
	std::string strInterference1 = "Interference factor1";
	buff.Write(strInterference1.c_str(), strInterference1.size());

	// ��A�����л����洢��buff��
	head.m_nType = CPackA::GetType();
	head.m_nContentLength = a.GetBufferLength();
	head.DataToBuffer(buff);
	a.DataToBuffer(buff);
	//buff.Write(strDestroy.c_str(), strDestroy.size()); // �ƻ�A�������л�
	tail.DataToBuffer(buff);

	// �������
	std::string strInterference2 = "Interference factor2";
	buff.Write(strInterference2.c_str(), strInterference2.size());

	// ��B�����л�
	head.m_nType = CPackB::GetType();
	head.m_nContentLength = b.GetBufferLength();
	head.DataToBuffer(buff);
	//buff.Write(strDestroy.c_str(), strDestroy.size()); // �ƻ�B�������л�
	b.DataToBuffer(buff);
	tail.DataToBuffer(buff);

	// �������
	std::string strInterference3 = "Interference factor1";
	buff.Write(strInterference3.c_str(), strInterference3.size());


	// ���
	jaf::CBuffReader reader;
	parsePack.NewData(buff.GetBuffer(), buff.GetWriteLength());

	std::cout << "��������,�������" << std::endl;
}