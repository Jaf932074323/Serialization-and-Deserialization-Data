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
时间:2021/11/21
描述:vector的序列化和反序列化对象
**************************************************************************/
#include <vector>
#include <memory>
#include <functional>
#include "SddInclude/Sdd/SddInterface.h"
#include "SddInclude/SddEndian/SddEndianBase.h"

// 创建double数据项序列化反序列化对象
#define SDD_VECTOR(rLen, rVector, rSddElement, rElement) jaf::CSddVector::Creation(rLen,rVector,rSddElement,rElement)
namespace jaf
{
	template<typename ElementType, typename SddElementType>
	// vector的序列化和反序列化对象
	// ElementType 元素类型
	// SddElementType 序列化或反序列化元素的对象
	class CSddVector :public CSddInterface
	{
	public:
		// vector的序列化和反序列化对象的构造函数
		// rVector 被序列化的vector
		// pSddElement 序列化元素的对象
		// rElement 序列化每一项时，被序列化的元素
		// 注：对容器类别的序列化和反序列化，一直没想好合适实现方式，这样实现相对比较复杂，有更好的方式时再修改
		CSddVector(std::vector<ElementType>& rVector, std::shared_ptr<SddElementType> pSddElement, ElementType& rElement)
			:m_rVector(rVector)
			, m_pSddElement(pSddElement)
			, m_rElement(rElement)
		{
		}

		~CSddVector()
		{

		}

		// 创建vector的序列化和反序列化对象
		// rVector 被序列化的vector
		// pSddElement 序列化元素的对象
		// rElement 序列化每一项时，被序列化的元素
		static std::shared_ptr< CSddVector< ElementType, SddElementType>> Creation(std::vector<ElementType>& rVector, std::shared_ptr<SddElementType> pSddElement, ElementType& rElement)
		{
			std::shared_ptr<CSddVector< ElementType, SddElementType>> pItem = std::make_shared<CSddVector< ElementType, SddElementType>>(rVector, pSddElement, rElement);
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
			if (m_nLen < 0)
			{
				return false;
			}

			m_rVector.resize(m_nLen);
			for (size_t i = 0; i < m_nLen; ++i)
			{
				if (!m_pSddElement->BufferToData(rBuffReader))
				{
					return false;
				}
				m_rVector[i] = m_rElement;
			}

			return true;
		}

		// 将数据写入到缓冲区
		// rBuffer 缓冲区
		// 成功返回true,失败返回false
		virtual void DataToBuffer(CBufferBase& rBuffer)
		{
			m_nLen = m_rVector.size();

			for (size_t i = 0; i < m_nLen; ++i)
			{
				m_rElement = m_rVector[i];
				m_pSddElement->DataToBuffer(rBuffer);
			}
		}

		// 获取序列化或反序列化使用的字节序列长度
		virtual size_t GetBufferLength()
		{
			m_nLen = m_rVector.size();

			size_t nLen = m_pSddElement->GetBufferLength() * m_nLen;
			return nLen;
		}

		// 设置vector的长度，在反序列化时，获取反序列化到的荣
		void SetLen(size_t nLen)
		{
			m_nLen = nLen;
			m_rVector.resize(nLen);
		}

	public:
		size_t m_nLen = 0; // 记录长度的对象
		std::vector<ElementType>& m_rVector; // 被序列化的vector
		std::shared_ptr<SddElementType> m_pSddElement; // 序列化元素的对象
		ElementType& m_rElement; // 序列化每一项时，被序列化的元素
	};
}
