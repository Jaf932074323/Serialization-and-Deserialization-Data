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
#include <vector>
#include <list>
#include <memory>
#include "SddItem/SddItemBase.h"
#include "SddItem/SddBitItem/SddBitInterface.h"

namespace jaf
{
	// ���л��ͷ����л�λ��������
	class CSddBitItem :public CSddItemBase
	{
	public:
		// �ַ��������л��ͷ����л���λ������
		// nLength �ֽڳ���
		CSddBitItem(size_t nLength);
		~CSddBitItem();

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

		// ���һ������
		virtual void AddChildBitItem(std::shared_ptr<CSddBitInterface> pChildBitItem);

	protected:
		size_t m_nLength; // ����
		std::vector<char> m_vectorBuff;  // �ڲ����棬������λ�����Ȼ��浽������һ�𿽱������������
		std::list<std::shared_ptr<CSddBitInterface>> m_listBit; // �����б�

	};

} // namespace jaf
