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
时间:2018/11/13 16:21
描述:序列化和反序列化整数项
**************************************************************************/
#include <assert.h>
#include "SddInclude/SddException.h"
#include "SddInclude/Sdd/SddInterface.h"
#include "SddInclude/SddEndian/SddEndianBase.h"

// 创建整数的序列化反序列化的数据项
#define SDD_INTERGER(T,rEndian,rT, ...) jaf::CSddInteger<T>::Creation(rEndian, rT, ## __VA_ARGS__)

namespace jaf
{

	template<typename T>
	// 整数的序列化反序列化通用对象
	// T 整数类型，可以是int/size_t/short int/unsigned short int/long/unsigned long等等
	class CSddInteger :public CSddInterface
	{
	public:
		// 整数的序列化和反序列化的通用对象
		// m_rEndian 端序
		// pT要序列化、反序列化数据的地址
		// nBitLength 要序列化的长度 如果为0，则全部序列化
		CSddInteger(CSddEndianBase& rEndian, T& rT, size_t nLength = 0) :m_rEndian(rEndian), m_rT(rT), m_nLength(nLength)
		{
			if ((0 != m_nLength) && (m_nLength > sizeof(T)))
			{
				throw CSddException("序列化长度太长", __FILE__, __LINE__);
			}
			if (m_nLength < 0)
			{
				throw CSddException("序列化长度传入值为负", __FILE__, __LINE__);
			}

			if (m_nLength == 0)
			{
				m_nLength = sizeof(T);
			}
		}

		~CSddInteger(void)
		{
		}

		// 创建整数的序列化和反序列化对象
		static std::shared_ptr<CSddInteger<T>> Creation(CSddEndianBase& m_rEndian, T& rT, size_t nLength = 0)
		{
			std::shared_ptr<CSddInteger<T>> pItem = std::make_shared<CSddInteger>(m_rEndian, rT, nLength);
			if (pItem == nullptr)
			{
				throw CSddException("创建double数据项失败", __FILE__, __LINE__);
			}
			return pItem;

		}

		// 从缓冲区中读取数据
		// rBuffer 缓冲区
		// 成功返回true,失败返回false
		virtual bool BufferToData(CBuffReaderBase& rBuffReader)
		{
			return m_rEndian.BufferToData(rBuffReader, (char*)&m_rT, sizeof(T), m_nLength);
		}
		// 将数据写入到缓冲区
		// rBuffer 缓冲区
		// 成功返回true,失败返回false
		virtual void DataToBuffer(CBufferBase& rBuffer)
		{
			m_rEndian.DataToBuffer(rBuffer, (const char*)&m_rT, sizeof(T), m_nLength);
		}


		// 获取序列化或反序列化使用的字节长度
		virtual size_t GetBufferLength()
		{
			if (m_nLength == 0)
			{
				return sizeof(T);
			}
			else
			{
				return m_nLength;
			}
		}

	protected:
		size_t m_nLength; // 序列化、反序列化长度 如果为0，则全部序列化
		T& m_rT; // 通用类型数据
		CSddEndianBase& m_rEndian; // 端序
	};

} // namespace jaf
