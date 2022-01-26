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
ʱ��:2020/11/12
����:�Բ���λ������л��ͷ����л�
**************************************************************************/
#include "SddInclude/Sdd/SddObject/SddBitObject/SddBitInterface.h"
#include <assert.h>

namespace jaf
{
	class CSddBoolBit :public CSddBitInterface
	{
	public:
		CSddBoolBit(bool& rBool, size_t nBitIndex) :m_rBool(rBool), m_nBitIndex(nBitIndex)
		{
		}

		~CSddBoolBit()
		{
		}

		// �ӻ������ж�ȡλ����
		// pBuff ������
		// nLength �������ܳ���
		// �ɹ�����true,ʧ�ܷ���false
		virtual bool BufferToData(const char* pBuff, size_t nLength)
		{
			assert(nLength * 8 > m_nBitIndex); // ����������Ҫס����
			const char* p = pBuff + m_nBitIndex / 8; // �ҵ�Ҫ�����л����ַ���ַ
			size_t nIndex = m_nBitIndex % 8; // �ҵ������л���λ����

			char c = 0x01 << nIndex;
			c &= *p;
			m_rBool = (bool)c;

			return true;
		}

		// ��λ����д�뵽������
		// pBuff ������
		// nLength �������ܳ���
		// �ɹ�����true,ʧ�ܷ���false
		virtual bool DataToBuffer(char* pBuff, size_t nLength)
		{
			assert(nLength * 8 > m_nBitIndex); // ����������Ҫס����
			char* p = pBuff + m_nBitIndex / 8; // �ҵ�Ҫ���л����ַ���ַ
			size_t nIndex = m_nBitIndex % 8; // �ҵ����л���λ����

			char c = (char)m_rBool;
			c <<= nIndex;
			*p |= c;

			return true;
		}

	protected:
		bool& m_rBool; // Ҫ���л��Ĳ���ֵ������
		size_t m_nBitIndex; // ���л�����λ����
	};

} // namespace jaf

