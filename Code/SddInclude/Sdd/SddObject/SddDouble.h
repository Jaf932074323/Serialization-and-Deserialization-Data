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
描述:序列化和反序列化double浮点数项
**************************************************************************/
#include <memory>
#include "SddInclude/Sdd/SddInterface.h"
#include "SddInclude/SddException.h"

// 创建double数据项序列化反序列化对象
#define SDD_DOUBLE(rVariate) jaf::CSddDouble::Creation(rVariate)

namespace jaf
{

	// double的序列化和反序列化对象
	class CSddDouble :public CSddInterface
	{
	public:
		CSddDouble(double& rVariate):m_f(rVariate)
		{
		}

		~CSddDouble()
		{
		}
		// 创建double浮点数的序列化和反序列化对象
		static std::shared_ptr<CSddDouble> Creation(double& rVariate)
		{
			std::shared_ptr<CSddDouble> pItem = std::make_shared<CSddDouble>(rVariate);
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
			return rBuffReader.Read((char*)&m_f, sizeof(double));
		}

		// 将数据写入到缓冲区
		// rBuffer 缓冲区
		// 成功返回true,失败返回false
		virtual void DataToBuffer(CBufferBase& rBuffer)
		{
			rBuffer.Write((char*)&m_f, sizeof(double));
		}

		// 获取序列化或反序列化使用的字节长度
		virtual size_t GetBufferLength()
		{
			return sizeof(double);
		}


	protected:
		double& m_f;
	};


} // namespace jaf

