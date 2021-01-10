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

#include "Buffer/Buffer.h"
#include <assert.h>
#include "SddException.h"

namespace jaf
{
	CBuffer::CBuffer(void) :
		m_eStoreSite(E_STORE_SITE::E_STORE_SITE_STACK)
		, m_nCapacity(g_nDefaultStackLen)
		, m_pBuffer(m_arrBufferStack)
		, m_nWriteByteLen(0)
	{
		memset(m_arrBufferStack, 0, g_nDefaultStackLen);
	}


	CBuffer::~CBuffer(void)
	{
		Clear();
	}

	// ��� �ͷŶ����ڴ桢����Ѷ���д�ֽڵ�
	void CBuffer::Clear()
	{
		ReleaseAllotMemory();
		m_eStoreSite = E_STORE_SITE::E_STORE_SITE_STACK;
		m_pBuffer = m_arrBufferStack;
		m_nCapacity = g_nDefaultStackLen;

		m_nWriteByteLen = 0;
	}

	// ԤԼnSize�ռ�,����д���ֽ� �û������ܹ���д��nSize���ֽ�
	// ������������ʱ�����·��������ڴ�ռ䣬���ܹ���ȡnSize���ֽ�
	// ��ʹ�ô洢���û��ṩ���ڴ�ʱ��������������������false
	// nSize ҪԤԼ�ռ�Ĵ�С
	// return �ɹ�����true��ʧ�ܷ���false
	void CBuffer::Reserve(size_t nSize)
	{
		// ����ռ��Ѿ��㹻����ֱ�ӷ���true
		ExtendCapacity(m_nWriteByteLen + nSize);
	}

	// ��չ�������ռ䣬��ԭ����д��ĳ����£�
	// ��չ����������nCapacity���ֽڴ�С��������������ʱ�����·��������ڴ�ռ䣬���ܹ��ٴ�ȡnSize���ֽ�
	// ��ʹ�ô洢���û��ṩ���ڴ�ʱ��������������������false
	// nCapacity Ҫ��չ��Ŀ���С
	// return �ɹ�����true��ʧ�ܷ���false
	void CBuffer::ExtendCapacity(size_t nCapacity)
	{
		// ����ռ��Ѿ��㹻����ֱ�ӷ���
		if (nCapacity <= m_nCapacity)
		{
			return;
		}

		// ����Ҫ����ռ��С������ռ�ʱҪ��kAllotMemoryUnit�ı������з���
		size_t nTotalCapacity = (nCapacity / g_nAllotMemoryUnit + 1) * g_nAllotMemoryUnit;
		nTotalCapacity *= 2; // ÿ�ζ����һ�������������ظ�����

		char* pBuff = nullptr;
		try
		{
			pBuff = new char[nTotalCapacity]; // ���붯̬�ڴ� todo: ��Ҫ��try
		}
		catch (const std::bad_alloc& e)
		{
			std::string str = e.what();
		}

		memcpy(pBuff, m_pBuffer, m_nWriteByteLen); // ���Ѿ�д��Ĳ��ֿ�������
		ReleaseAllotMemory(); // ��ԭ��������ڴ�ռ��ͷŵ�
		m_pBuffer = pBuff; // ������ָ��ָ���·�����ڴ�ռ�
		m_nCapacity = nTotalCapacity;

		return;
	}

	// ��ȡ��д���ֽ���
	size_t CBuffer::GetWriteLength() const
	{
		return m_nWriteByteLen;
	}

	// ��ȡ��������ַ
	const char* CBuffer::GetBuffer() const
	{
		return m_pBuffer;
	}

	// д�����ݵ�������
	// pData Ҫд�����ĵ�ַ ����Ϊ��
	// nLength Ҫд��ĳ���
	// return �ɹ�����true��ʧ�ܷ���false
	void CBuffer::Write(const char* pData, size_t nLength)
	{
		if (nullptr == pData)
		{
			throw CSddException(("д����ڴ��ַΪ��."), __FILE__, __LINE__);
		}

		Reserve(nLength);

		memcpy(m_pBuffer + m_nWriteByteLen, pData, nLength);
		m_nWriteByteLen += nLength;
	}

	void CBuffer::WriteChar(char c, size_t nLength)
	{
		Reserve(nLength);

		memset(m_pBuffer + m_nWriteByteLen, c, nLength);
		m_nWriteByteLen += nLength;
	}

	void CBuffer::PopFront(size_t nLength)
	{
		if (nLength >= m_nWriteByteLen)
		{
			m_nWriteByteLen = 0;
			return;
		}

		if (nLength == 0)
		{
			return;
		}

		m_nWriteByteLen = m_nWriteByteLen - nLength;
		for (size_t i = 0; i < m_nWriteByteLen; ++i)
		{
			m_pBuffer[i] = m_pBuffer[i + nLength];
		}
	}

	void CBuffer::PopBack(size_t nLength)
	{
		if (nLength >= m_nWriteByteLen)
		{
			m_nWriteByteLen = 0;
		}

		m_nWriteByteLen = m_nWriteByteLen - nLength;
	}

	// �������ڴ�
	// pSeekContent ���������ݵ��׵�ַ
	// nSeekcontentLength ���������ݵĳ���
	// rIndex ���ر����������ݵ�����
	// �����Ƿ�������
	bool CBuffer::SeekFront(const char* pSeekContent, size_t nSeekContentLength, size_t& rIndex)
	{
		for (size_t i = 0; i < m_nWriteByteLen; ++i)
		{
			size_t j = 0;
			for (; j < nSeekContentLength; ++j)
			{
				if (m_pBuffer[i + j] != pSeekContent[j])
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

	// �ͷŶ�̬������ڴ�ռ� ������������ͷ����ڴ棬�������ֵ����������д�ֽڡ��Ѷ��ֽڵȶ�û�������������������������
	void CBuffer::ReleaseAllotMemory()
	{
		// ����洢�ڶ�̬�����ڴ��У���Ҫ�ͷŷ�����ڴ�
		if (E_STORE_SITE::E_STORE_SITE_DYNAMIC == m_eStoreSite)
		{
			delete[] m_pBuffer;
			m_pBuffer = m_arrBufferStack;
		}
	}

} // namespace jaf

