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
����:���л��ͷ����л�һ������
**************************************************************************/
#include <memory>
#include "SddInclude/Sdd/SddInterface.h"

// ����һ�����ݵ����л������л�����
#define SDD_CHUNK(pVariate, nLength) jaf::CSddChunk::Creation(pVariate, nLength)

namespace jaf
{

	// ������л��ͷ����л�����
	// ĳ���������ݼ��ϵ�һ���γ�һ�����ݣ��������л��ͷ����л�
	class CSddChunk :public CSddInterface
	{
	public:
		// ������л��ͷ����л�����
		// ĳ���������ݼ��ϵ�һ���γ�һ�����ݣ��������л��ͷ����л�
		// pVariate ���ַ
		// nLength ���С
		CSddChunk(void* pVariate, size_t nLength):m_pChunk(pVariate), m_nLength(nLength)
		{
			if (pVariate == nullptr)
			{
				throw CSddException("���л����������ַΪ��", __FILE__, __LINE__);
			}
			if (m_nLength < 0)
			{
				throw CSddException("���л����ȴ���ֵΪ��", __FILE__, __LINE__);
			}
		}

		~CSddChunk()
		{

		}

		// �����ַ��������л��ͷ����л���������
		static std::shared_ptr<CSddChunk> Creation(void* pVariate, size_t nLength)
		{
			std::shared_ptr<CSddChunk> pItem = std::make_shared<CSddChunk>(pVariate, nLength);
			if (pItem == nullptr)
			{
				throw CSddException("������������ʧ��", __FILE__, __LINE__);
			}
			return pItem;
		}


		// �ӻ������ж�ȡ����
		// rBuffer ������
		// �ɹ�����true,ʧ�ܷ���false
		virtual bool BufferToData(CBuffReaderBase& rBuffReader)
		{
			return rBuffReader.Read((char*)m_pChunk, m_nLength);
		}

		// ������д�뵽������
		// rBuffer ������
		// �ɹ�����true,ʧ�ܷ���false
		virtual void DataToBuffer(CBufferBase& rBuffer)
		{
			rBuffer.Write((char*)m_pChunk, m_nLength);
		}

		// ��ȡ���л������л�ʹ�õ��ֽڳ���
		virtual size_t GetBufferLength()
		{
			return m_nLength;
		}

	protected:
		size_t m_nLength; // ����
		void* m_pChunk; // ���ַ
	};

} // namespace jaf
