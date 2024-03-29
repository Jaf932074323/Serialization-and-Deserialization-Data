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
时间:2020/11/5
描述: 对位序列化和反序列化对象
**************************************************************************/
#include <vector>
#include <list>
#include <memory>
#include "SddInclude/Sdd/SddInterface.h"
#include "SddInclude/Sdd/SddObject/SddBitObject/SddBitInterface.h"

namespace jaf
{
	// 对位序列化和反序列化对象
	class CSddBitItem :public CSddInterface
	{
	public:
		// 对位序列化和反序列化对象
		// nLength 字节长度
		CSddBitItem(size_t nLength) : m_nLength(nLength)
		{
			m_pBuff = new char[nLength];
			m_pBits = new std::list<std::shared_ptr<CSddBitInterface>>;
		}

		~CSddBitItem()
		{
			delete[] m_pBuff;
			delete m_pBits;
		}

		// 从缓冲区中读取数据
		// rBuffer 缓冲区
		// 成功返回true,失败返回false
		virtual bool BufferToData(CBuffReaderBase& rBuffReader)
		{
			rBuffReader.Read(m_pBuff, m_nLength);

			std::list<std::shared_ptr<CSddBitInterface>>* pBits = (std::list<std::shared_ptr<CSddBitInterface>>*)m_pBits;
			for (std::list<std::shared_ptr<CSddBitInterface>>::iterator it = pBits->begin(); it != pBits->end(); ++it)
			{
				if (!(*it)->BufferToData(m_pBuff, m_nLength))
				{
					return false;
				}
			}

			return true;
		}

		// 将数据写入到缓冲区
		// rBuffer 缓冲区
		// 成功返回true,失败返回false
		virtual void DataToBuffer(CBufferBase& rBuffer)
		{
			std::list<std::shared_ptr<CSddBitInterface>>* pBits = (std::list<std::shared_ptr<CSddBitInterface>>*)m_pBits;
			for (std::list<std::shared_ptr<CSddBitInterface>>::iterator it = pBits->begin(); it != pBits->end(); ++it)
			{
				(*it)->DataToBuffer(m_pBuff, m_nLength);
			}

			rBuffer.Write(m_pBuff, m_nLength);
		}

		// 获取序列化或反序列化使用的字节长度
		virtual size_t GetBufferLength()
		{
			return m_nLength;
		}

		// 添加一个子项
		virtual void AddChildBitItem(std::shared_ptr<CSddBitInterface> pChildBitItem)
		{
			std::list<std::shared_ptr<CSddBitInterface>>* pBits = (std::list<std::shared_ptr<CSddBitInterface>>*)m_pBits;
			pBits->push_back(pChildBitItem);
		}

protected:
		size_t m_nLength; // 长度
		char* m_pBuff = nullptr;  // 内部缓存，将各种位数据先缓存到这里，最后一起拷贝到输出缓存中
		void* m_pBits = nullptr;  // 子项列表

	};

} // namespace jaf
