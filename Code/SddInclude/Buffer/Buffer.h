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
时间:2018-10-31 16:57
描述:缓冲区，存储字节
提供了一个默认栈，字节优先存储在默认栈中。
在使用者不指定存储方式时，当要存储的字节串长度小于默认栈长度，默认存储在这个栈中。
当超过默认栈长度时，存储在动态分配内存中。
**************************************************************************/
#include <memory.h>
#include "SddInclude/Buffer/BufferBase.h"
#include "SddInclude/SddException.h"

namespace jaf
{
	const size_t g_nAllotMemoryUnit = 32; // 分配空间时，以这个值的倍数分配
	const size_t g_nDefaultStackLen = 32; // 默认栈长度

	// 缓冲区
	class CBuffer :public CBufferBase
	{
	protected:
		// 字节存储位置
		enum class E_STORE_SITE
		{
			E_STORE_SITE_STACK = 0, // 存储在默认栈中
			E_STORE_SITE_DYNAMIC = 1 // 存储在动态内存中
		};
	public:
		CBuffer(void) :
			m_eStoreSite(E_STORE_SITE::E_STORE_SITE_STACK)
			, m_nCapacity(g_nDefaultStackLen)
			, m_pBuffer(m_arrBufferStack)
			, m_nWriteByteLen(0)
		{
			memset(m_arrBufferStack, 0, g_nDefaultStackLen);
		}

		~CBuffer(void)
		{
			Clear();
		}

		// 清空 释放冬天内存、清空已读已写字节等
		void Clear()
		{
			ReleaseAllotMemory();
			m_eStoreSite = E_STORE_SITE::E_STORE_SITE_STACK;
			m_pBuffer = m_arrBufferStack;
			m_nCapacity = g_nDefaultStackLen;

			m_nWriteByteLen = 0;
		}

		// 预约nSize空间,用于写入字节 让缓存区能够再写入nSize个字节
		// 在总容量不够时，重新分配更大的内存空间，以能够存取nSize个字节
		// 当使用存储在用户提供的内存时，若总容量不够，返回false
		// nSize 要预约空间的大小
		// return 成功返回true，失败返回false
		void Reserve(size_t nSize)
		{
			// 如果空间已经足够，则直接返回true
			ExtendCapacity(m_nWriteByteLen + nSize);
		}

		// 扩展缓冲区空间，在原来已写入的长度下，
		// 扩展容量到至少nCapacity个字节大小，在总容量不够时，重新分配更大的内存空间，以能够再存取nSize个字节
		// 当使用存储在用户提供的内存时，若总容量不够，返回false
		// nCapacity 要扩展的目标大小
		// return 成功返回true，失败返回false
		void ExtendCapacity(size_t nCapacity)
		{
			// 如果空间已经足够，则直接返回
			if (nCapacity <= m_nCapacity)
			{
				return;
			}

			// 总需要分配空间大小，分配空间时要以kAllotMemoryUnit的倍数进行分配
			size_t nTotalCapacity = (nCapacity / g_nAllotMemoryUnit + 1) * g_nAllotMemoryUnit;
			nTotalCapacity *= 2; // 每次多分配一倍，以免过多的重复分配

			char* pBuff = nullptr;
			try
			{
				pBuff = new char[nTotalCapacity]; // 申请动态内存
			}
			catch (const std::bad_alloc& e)
			{
				std::string str = e.what();
			}

			memcpy(pBuff, m_pBuffer, m_nWriteByteLen); // 将已经写入的部分拷贝过来
			ReleaseAllotMemory(); // 将原来分配的内存空间释放掉
			m_pBuffer = pBuff; // 缓冲区指针指向新分配的内存空间
			m_nCapacity = nTotalCapacity;
			m_eStoreSite = E_STORE_SITE::E_STORE_SITE_DYNAMIC;

			return;
		}

		// 获取已写入字节数
		size_t GetWriteLength() const
		{
			return m_nWriteByteLen;
		}

		// 获取缓冲区地址
		const char* GetBuffer() const
		{
			return m_pBuffer;
		}

	public:
		// 写入数据到缓存中
		// pData 要写入对象的地址 不能为空
		// nLength 要写入的长度
		// return 成功返回true，失败返回false
		void Write(const char* pData, size_t nLength)
		{
			if (nullptr == pData)
			{
				throw CSddException(("写入的内存地址为空."), __FILE__, __LINE__);
			}

			Reserve(nLength);

			memcpy(m_pBuffer + m_nWriteByteLen, pData, nLength);
			m_nWriteByteLen += nLength;
		}

		// 重复写入同一个字符到缓冲区中
		// c 要写入的字符
		// nLength 要写入字符的个数
		// return 成功返回true，失败返回false
		void WriteChar(char c, size_t nLength)
		{
			Reserve(nLength);

			memset(m_pBuffer + m_nWriteByteLen, c, nLength);
			m_nWriteByteLen += nLength;
		}

	public:
		// 删除前指定长度
		// nLength 要删除的长度,如果长度不够则全部删除
		virtual void PopFront(size_t nLength)
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
		// 删除后指定长度
		// nLength 要删除的长度,如果长度不够则全部删除
		virtual void PopBack(size_t nLength)
		{
			if (nLength >= m_nWriteByteLen)
			{
				m_nWriteByteLen = 0;
			}

			m_nWriteByteLen = m_nWriteByteLen - nLength;
		}


		// 搜索子内存
		// pSeekContent 被搜索内容的首地址
		// nSeekcontentLength 被搜索内容的长度
		// rIndex 返回被搜索到内容的索引
		// 返回是否搜索到
		virtual bool SeekFront(const char* pSeekContent, size_t nSeekContentLength, size_t& rIndex)
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
	private:
		// 释放动态分配的内存空间 这个函数仅仅释放了内存，其它相关值如容量、已写字节等等都没处理，调用需谨慎，否则有隐患
		void ReleaseAllotMemory()
		{
			// 如果存储在动态分配内存中，需要释放分配的内存
			if (E_STORE_SITE::E_STORE_SITE_DYNAMIC == m_eStoreSite)
			{
				delete[] m_pBuffer;
				m_pBuffer = m_arrBufferStack;
			}
		}

	protected:
		// 缓冲区指针,指向存储字节的首地址
		// 当使用默认栈时，它指向默认栈首地址
		// 当使用动态内存空间时，指向动态内存首地址
		char* m_pBuffer = nullptr;
		char m_arrBufferStack[g_nDefaultStackLen]; // 默认栈
		E_STORE_SITE m_eStoreSite = E_STORE_SITE::E_STORE_SITE_STACK; // 字节存储位置

		size_t m_nCapacity = g_nDefaultStackLen; // 总容量
		size_t m_nWriteByteLen = 0; // 已经写入字节的长度
	};

} // namespace jaf
