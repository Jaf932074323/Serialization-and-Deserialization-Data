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
ʱ��:2020-12-013
����:�̶���ͷ��β�İ��Ľ�����
**************************************************************************/
#include <string>
#include "Buffer/Buffer.h"
#include "Buffer/BuffReader.h"
#include "ParsePackage/ParsePackBase.h"
#include "ParsePackage/SpecialPack/PackHeadBase.h"
#include "ParsePackage/SpecialPack/PackTailBase.h"
#include "ParsePackage/PackFactBase.h"
#include "ParsePackage/DealPackInterface.h"

namespace jaf
{
	// �̶���ͷ��β�İ��Ľ�����
	class CParsePackHeadTail :public CParsePackBase
	{
	public:
		// �̶���ͷ��β�İ��Ľ�����Ĺ��캯��
		// pHead ��ͷ
		// pTail ��β
		// rPackFactory ������
		// rDealPack ���������
		CParsePackHeadTail(CPackHeadBase& rHead, CPackTailBase& rTail
			, CPackFactBase& rPackFactory)
			:m_rHead(rHead), m_rTail(rTail), m_rPackFactory(rPackFactory)
		{
		}

		virtual ~CParsePackHeadTail()
		{}

		// ���µ�����
		virtual void NewData(const char* pData, size_t nLength)
		{
			m_dataBuffer.Write(pData, nLength);
			Parse();
		}

	protected:

		void Parse()
		{
			while (ParseOne())
			{
			}
		}

		// ����һ������
		// �����Ƿ���Ҫ���������������������п��ܻ��ܽ�������ʱ����true�������ܽ�����ʱ����false
		bool ParseOne()
		{
			if (m_dataBuffer.GetWriteLength() <= 0)
			{
				return false;
			}

			// ����ͷ
			size_t nHeadIndex;
			if (!m_rHead.SeekHead(m_dataBuffer.GetBuffer(), m_dataBuffer.GetWriteLength(), nHeadIndex))
			{
				// ���û���ҵ�ͷ����nHeadIndexǰ������ݶ�����Ч��
				m_dataBuffer.PopFront(nHeadIndex);
				return false;
			}
			// ����ҵ��ˣ�ҲҪ�Ƴ�nHeadIndexǰ�������
			m_dataBuffer.PopFront(nHeadIndex);

			CBuffReader buffReader;
			buffReader.Attach(m_dataBuffer.GetBuffer(), m_dataBuffer.GetWriteLength());

			// ��ȡͷ
			m_rHead.BufferToData(buffReader);
			if (!m_rHead.Check())
			{
				m_dataBuffer.PopFront(1);
				return true;
			}

			size_t nContentLen = m_rHead.GetContentLen();

			size_t nTotalLen = m_rHead.GetBufferLength() + m_rTail.GetBufferLength() + nContentLen; // �ܳ���
			if (nContentLen > m_dataBuffer.GetWriteLength()) // ���Ȳ���
			{
				return false;
			}

			// ��ȡ����
			std::vector<char> vectorContent(nContentLen);
			buffReader.Read(vectorContent.data(), nContentLen);

			// ��ȡβ
			m_rTail.BufferToData(buffReader);
			if (!m_rTail.Check(m_dataBuffer.GetBuffer(), nContentLen))
			{
				m_dataBuffer.PopFront(1);
				return true;
			}

			std::shared_ptr<CPackBase> pPack = m_rPackFactory.Create(m_rHead.GetType(), vectorContent.data(), nContentLen);
			if (pPack != nullptr)
			{
				m_pDealPack->Deal(m_rHead.GetType(), pPack);
			}
			m_dataBuffer.PopFront(nTotalLen);

			return true;
		}

	protected:
		CPackHeadBase& m_rHead; // ��ͷ
		CPackTailBase& m_rTail; // ��β
		CPackFactBase& m_rPackFactory; // ������

		CBuffer m_dataBuffer; // ���յ������ݻ�����
	};


} // namespace jaf
