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
ʱ��:2020-12-16
����:�ڴ��ȡ��
ͨ��������ܹ��ȽϷ���Ĵ��ڴ��ж�ȡ
**************************************************************************/
#include "BuffReaderBase.h"
#include <assert.h>
#include "SddInclude/SddException.h"

namespace jaf
{
	class CBuffReader :public CBuffReaderBase
	{
	public:
		CBuffReader() {}
		// pBuff Ҫ��ȡ�ڴ�ĵ�ַ
		// nLength Ҫ��ȡ�ڴ�ĳ���
		CBuffReader(const char* pBuff, size_t nLength)
			:m_pBuff(pBuff), m_nLength(nLength)
		{}
		virtual ~CBuffReader() {}

		// ������һ��Ҫ����ȡ���ڴ棬���Ҷ�ȡƫ������Ϊ0
		// pBuff �ڴ��ַ
		// nLength �ڴ泤�� ����С��0
		void Attach(const char* pBuff, size_t nLength)
		{
			assert(pBuff != nullptr);
			m_pBuff = pBuff;
			m_nLength = nLength;
			m_nReadOffset = 0;
		}

		// �Ƴ��������ڴ�
		void Clear()
		{
			m_pBuff = nullptr;
			m_nLength = 0;
			m_nReadOffset = 0;
		}

		// ���ö�ȡƫ��
		// nOffset ���ö�ȡƫ�� ����С��0�����ܴ����ܳ��ȣ������׳��쳣
		void SetReadOffset(size_t nOffset)
		{
			if (nOffset >= m_nLength)
			{
				throw CSddException("ƫ��λ�ô����ڴ��ܳ���.", __FILE__, __LINE__);
			}

			m_nReadOffset = nOffset;
		}
		// ��ȡ��ȡƫ��
		size_t GetReadOffset()
		{
			return m_nReadOffset;
		}

		// ���ڴ��ж�ȡ����
		// pData Ҫ��ȡ���ݵ��Ķ���ĵ�ַ ����Ϊ��
		// nLength Ҫ��ȡ�ĳ���
		// return �ɹ�����true��ʧ�ܷ���false
		// ��ȡ�ɹ��󣬶�ȡƫ��������ȡ�ĳ��ȣ�ʧ�ܲ���
		bool Read(char* pData, size_t nLength)
		{
			if (pData == nullptr)
			{
				return false;
			}
			if (nLength > m_nLength - m_nReadOffset)
			{
				// �ڴ����ݳ��Ȳ���
				return false;
			}

			memcpy_s(pData, nLength, m_pBuff + m_nReadOffset, nLength);
			m_nReadOffset += nLength;
			return true;
		}

		// �������Ҫ��ȡ���ַ�
		// nLength Ҫ�����ĳ���
		// return �ɹ�����true��ʧ�ܷ���false
		// �����ɹ��󣬶�ȡƫ��������ȡ�ĳ��ȣ�ʧ�ܲ���
		bool SkipRead(size_t nLength)
		{
			if (nLength > m_nLength - m_nReadOffset)
			{
				return false;
			}

			m_nReadOffset += nLength;
			return true;
		}

		// �������ڴ�
		// pSeekContent ���������ݵ��׵�ַ
		// nSeekcontentLength ���������ݵĳ���
		// rIndex ���ر����������ݵ������ƫ�ƴ�������
		// �����Ƿ�������
		bool SeekAtOffset(const char* pSeekContent, size_t nSeekContentLength, size_t& rIndex)
		{
			for (size_t i = m_nReadOffset; i < m_nLength; ++i)
			{
				size_t j = 0;
				for (; j < nSeekContentLength; ++j)
				{
					if (m_pBuff[i + j] != pSeekContent[j])
					{
						break;
					}
				}
				if (j >= nSeekContentLength)
				{
					rIndex = i;
					return true;
				}
			}

			return false;
		}

	protected:
		const char* m_pBuff = nullptr; // Ҫ��ȡ���ڴ��ַ
		size_t m_nLength = 0; // Ҫ��ȡ���ڴ��ַ�ĳ���
		size_t m_nReadOffset = 0; // ��ȡ����ƫ�ƣ�ÿ�ζ�ȡ���ǳ�ƫ�ƴ���ȡ
	};

} // namespace jaf

