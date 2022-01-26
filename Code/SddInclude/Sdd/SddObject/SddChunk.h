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
描述:序列化和反序列化一块数据
**************************************************************************/
#include <memory>
#include "SddInclude/Sdd/SddInterface.h"

// 创建一块数据的序列化反序列化对象
#define SDD_CHUNK(pVariate, nLength) jaf::CSddChunk::Creation(pVariate, nLength)

namespace jaf
{

	// 块的序列化和反序列化对象
	// 某个或多个数据集合到一起形成一块数据，对它序列化和反序列化
	class CSddChunk :public CSddInterface
	{
	public:
		// 块的序列化和反序列化对象
		// 某个或多个数据集合到一起形成一块数据，对它序列化和反序列化
		// pVariate 块地址
		// nLength 块大小
		CSddChunk(void* pVariate, size_t nLength):m_pChunk(pVariate), m_nLength(nLength)
		{
			if (pVariate == nullptr)
			{
				throw CSddException("序列化传入块对象地址为空", __FILE__, __LINE__);
			}
			if (m_nLength < 0)
			{
				throw CSddException("序列化长度传入值为负", __FILE__, __LINE__);
			}
		}

		~CSddChunk()
		{

		}

		// 创建字符串的序列化和反序列化的数据项
		static std::shared_ptr<CSddChunk> Creation(void* pVariate, size_t nLength)
		{
			std::shared_ptr<CSddChunk> pItem = std::make_shared<CSddChunk>(pVariate, nLength);
			if (pItem == nullptr)
			{
				throw CSddException("创建块数据项失败", __FILE__, __LINE__);
			}
			return pItem;
		}


		// 从缓冲区中读取数据
		// rBuffer 缓冲区
		// 成功返回true,失败返回false
		virtual bool BufferToData(CBuffReaderBase& rBuffReader)
		{
			return rBuffReader.Read((char*)m_pChunk, m_nLength);
		}

		// 将数据写入到缓冲区
		// rBuffer 缓冲区
		// 成功返回true,失败返回false
		virtual void DataToBuffer(CBufferBase& rBuffer)
		{
			rBuffer.Write((char*)m_pChunk, m_nLength);
		}

		// 获取序列化或反序列化使用的字节长度
		virtual size_t GetBufferLength()
		{
			return m_nLength;
		}

	protected:
		size_t m_nLength; // 长度
		void* m_pChunk; // 块地址
	};

} // namespace jaf
