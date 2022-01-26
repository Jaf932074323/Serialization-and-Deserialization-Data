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
时间:2018/10/25
描述:序列化和反序列化数据对象 Serialization and Deserialization Data 简称为SDD
这个类及其子类作用是方便的将特定的数据集序列化成字节序列(缓冲区对象)，
以及从字节数组(缓冲区对象)中反序列化出特定的数据对象
**************************************************************************/
#include <list>
#include <memory>
#include "SddInclude/Sdd/SddInterface.h"
#include "SddInclude/SddEndian/SddEndianBase.h"
#include "SddInclude/SddEndian/SddEndianBase.h"
#include "SddInclude/SddEndian/SddEndianNo.h"
#include "SddInclude/SddEndian/SddEndianLittle.h"
#include "SddInclude/SddEndian/SddEndianBig.h"
#include "SddInclude/SddEndian/SddEndianManage.h"

#define SDD_ADD_ITEM(CreationItemFun) AddChildItem(CreationItemFun);
namespace jaf
{
	class CSddBase :public CSddInterface
	{
	public:
		CSddBase() :m_rEndian(CSddEndianManage::GetDefaultEndian())
		{
			m_pItems = new std::list<std::shared_ptr<CSddInterface>>();
		}
		CSddBase(E_ENDIAN eEndian) : m_rEndian(CSddEndianManage::GetEndian(eEndian))
		{
			m_pItems = new std::list<std::shared_ptr<CSddInterface>>();
		}
		~CSddBase(void)
		{
			delete (std::list<std::shared_ptr<CSddInterface>>*)m_pItems;
		}

		// 从缓冲区中读取数据
		// rBuffer 缓冲区
		// 成功返回true,失败返回false
		virtual bool BufferToData(CBuffReaderBase& rBuffReader)
		{
			std::list<std::shared_ptr<CSddInterface>>* pItems = (std::list<std::shared_ptr<CSddInterface>>*)m_pItems;
			for (std::list<std::shared_ptr<CSddInterface>>::iterator it = pItems->begin(); it != pItems->end(); ++it)
			{
				if (!(*it)->BufferToData(rBuffReader))
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
			std::list<std::shared_ptr<CSddInterface>>* pItems = (std::list<std::shared_ptr<CSddInterface>>*)m_pItems;
			for (std::list<std::shared_ptr<CSddInterface>>::iterator it = pItems->begin(); it != pItems->end(); ++it)
			{
				(*it)->DataToBuffer(rBuffer);
			}
		}

		// 获取序列化或反序列化使用的字节序列长度
		virtual size_t GetBufferLength()
		{
			size_t nLength = 0;
			std::list<std::shared_ptr<CSddInterface>>* pItems = (std::list<std::shared_ptr<CSddInterface>>*)m_pItems;
			for (std::list<std::shared_ptr<CSddInterface>>::iterator it = pItems->begin(); it != pItems->end(); ++it)
			{
				nLength += (*it)->GetBufferLength();
			}
			return nLength;
		}

	protected:
		// 添加子项
		void AddChildItem(std::shared_ptr<CSddInterface> pChildItem)
		{
			std::list<std::shared_ptr<CSddInterface>>* pItems = (std::list<std::shared_ptr<CSddInterface>>*)m_pItems;
			pItems->push_back(pChildItem);
		}

	protected:
		CSddEndianBase& m_rEndian; // 端序

		void* m_pItems = nullptr;
		//std::list<std::shared_ptr<CSddInterface>> m_childItems; // 子项列表
	};

} // namespace jaf

