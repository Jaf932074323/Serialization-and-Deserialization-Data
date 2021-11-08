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
#include <vector>
#include <memory>
#include "SddItemBase.h"
#include "SddException.h"

// �����䳤�ַ������л������л�������
#define SDD_VARI_LEN_STRING(rVariate) jaf::CSddVariLenStringItem::Creation(rVariate)
namespace jaf
{

// �ַ��������л��ͷ����л���������
	class CSddVariLenStringItem :public CSddItemBase
	{
	public:
		CSddVariLenStringItem(std::string& str) :m_str(str)
		{
		}
		~CSddVariLenStringItem(){}

		// �����ַ��������л��ͷ����л���������
		static std::shared_ptr<CSddInterface> Creation(std::string& value)
		{
			std::shared_ptr<CSddInterface> pItem = std::make_shared<CSddVariLenStringItem>(value);
			if (pItem == nullptr)
			{
				throw CSddException("�����ַ���������ʧ��", __FILE__, __LINE__);
			}
			return pItem;
		}

		// �ӻ������ж�ȡ����
		// rBuffer ������
		// �ɹ�����true,ʧ�ܷ���false
		virtual bool BufferToData(CBuffReaderBase& rBuffReader)
		{
			// �����ַ�������
			size_t nPos = 0;
			if (!rBuffReader.SeekAtOffset("\0", 1, nPos))
			{
				return false;
			}

			std::vector<char> vector;
			vector.resize(nPos);
			vector[nPos] = 0;

			if (!rBuffReader.Read(vector.data(), nPos))
			{
				return false;
			}
			m_str = vector.data();
			return true;
		}

		// ������д�뵽������
		// rBuffer ������
		// �ɹ�����true,ʧ�ܷ���false
		virtual void DataToBuffer(CBufferBase& rBuffer)
		{
			std::vector<char> vector;
			size_t nLen = m_str.size() + 1;
			vector.resize(nLen);
			vector[nLen - 1] = 0;

			memcpy_s(vector.data(), nLen, m_str.data(), nLen);
			rBuffer.Write(vector.data(), nLen);
		}

		// ��ȡ���л������л�ʹ�õ��ֽڳ���
		virtual size_t GetBufferLength()
		{
			return m_str.size() + 1;
		}

	protected:
		std::string& m_str; // �ַ�������
	};

} // namespace jaf
