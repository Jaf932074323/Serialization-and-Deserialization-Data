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
ʱ��:2020/11/5
����:���л��ͷ����л� ռλ����
**************************************************************************/
#include <memory>
#include "SddInclude/Sdd/SddInterface.h"
#include "SddInclude/SddException.h"

// ����ռλ������л������л�����
#define SDD_PLACEHOLDER(nLength, ...) jaf::CSddPlaceholder::Creation(nLength, ## __VA_ARGS__)

namespace jaf
{

	// ���л��ͷ����л� ռλ����
	class CSddPlaceholder :public CSddInterface
	{
	public:
		// nLength ռλ����
		// c ռλ����
		CSddPlaceholder(size_t nLength, char c) :m_nLength(nLength), m_c(c)
		{
		}

		~CSddPlaceholder()
		{
		}
		// ����dռλ��������л��ͷ����л�����
		static std::shared_ptr<CSddPlaceholder> Creation(size_t nLength, char c = 0x00)
		{
			std::shared_ptr<CSddPlaceholder> pItem = std::make_shared<CSddPlaceholder>(nLength, c);
			if (pItem == nullptr)
			{
				throw CSddException("����ռλ��������ʧ��", __FILE__, __LINE__);
			}
			return pItem;
		}

		// �ӻ������ж�ȡ����
		// rBuffer ������
		// �ɹ�����true,ʧ�ܷ���false
		virtual bool BufferToData(CBuffReaderBase& rBuffReader)
		{
			return rBuffReader.SkipRead(m_nLength);
		}
		// ������д�뵽������
		// rBuffer ������
		// �ɹ�����true,ʧ�ܷ���false
		virtual void DataToBuffer(CBufferBase& rBuffer)
		{
			rBuffer.WriteChar(m_c, m_nLength);
		}
		// ��ȡ���л������л�ʹ�õ��ֽڳ���
		virtual size_t GetBufferLength()
		{
			return m_nLength;
		}


	protected:
		size_t m_nLength; // ����
		char m_c = 0x00; // ռλ����
	};

} // namespace jaf


