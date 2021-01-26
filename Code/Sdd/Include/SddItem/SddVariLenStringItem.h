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
ʱ��:2021/1/26
����:���л��ͷ����л��䳤�ַ�����
**************************************************************************/
#include <string>
#include <memory>
#include "SddItemBase.h"

// �����䳤�ַ������л������л�������
#define SDD_VARI_LEN_STRING(rVariate) jaf::CSddVariLenStringItem::Creation(rVariate)
namespace jaf
{

// �ַ��������л��ͷ����л���������
	class CSddVariLenStringItem :public CSddItemBase
	{
	public:
		CSddVariLenStringItem(std::string& str);
		~CSddVariLenStringItem();

		// �����ַ��������л��ͷ����л���������
		static std::shared_ptr<CSddInterface> Creation(std::string& value);

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
		std::string& m_str; // �ַ�������
	};

} // namespace jaf