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
����:���л��ͷ����л� һ��������Ϊһ��
**************************************************************************/
#include <memory>
#include "SddItemBase.h"

// �����ַ������л������л�������
#define SDD_CHUNK(pVariate, nLength) jaf::CSddChunkItem::Creation(pVariate, nLength)

namespace jaf
{

	// ������л��ͷ����л���������
	// ĳ���������ݼ��ϵ�һ���γ�һ�����ݣ��������л��ͷ����л�
	class CSddChunkItem :public CSddItemBase
	{
	public:
		// ������л��ͷ����л���������
		// ĳ���������ݼ��ϵ�һ���γ�һ�����ݣ��������л��ͷ����л�
		// pVariate ���ַ
		// nLength ���С
		CSddChunkItem(void* pVariate, size_t nLength);
		~CSddChunkItem();
		// �����ַ��������л��ͷ����л���������
		static std::shared_ptr<CSddInterface> Creation(void* pVariate, size_t nLength);

		// �ӻ������ж�ȡ����
		// rBuffer ������
		// �ɹ�����true,ʧ�ܷ���false
		virtual bool BufferToData(CBuffReaderBase& rBuffReader);
		// ������д�뵽������
		// rBuffer ������
		// �ɹ�����true,ʧ�ܷ���false
		virtual void DataToBuffer(CBufferBase& rBuffer);
		// ��ȡ���л������л�ʹ�õ��ֽڳ���
		virtual size_t GetBufferLength();

	protected:
		size_t m_nLength; // ����
		void* m_pChunk; // ���ַ
	};

} // namespace jaf
