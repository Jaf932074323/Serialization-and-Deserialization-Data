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
ʱ��:2020/11/22
����:���л��ͷ����л� �û���չ��Ϊ
**************************************************************************/
#include <functional>
#include <memory>
#include <string>
#include "SddInclude/Sdd/SddInterface.h"
#include "SddInclude/SddException.h"

namespace jaf
{
	// ���л��ͷ����л� �û���չ��Ϊ
	class CSddExtendAct:public CSddInterface
	{
	public:
		// ���캯��
		// funBufferToData �û�����ӻ������ж�ȡ������Ϊ
		// funDataToBuffer �û������д�����ݵ���������Ϊ
		CSddExtendAct(std::function<bool(CBuffReaderBase&)> funBufferToData
			, std::function<void(CBufferBase&)> funDataToBuffer)
			:m_funBufferToData(funBufferToData), m_funDataToBuffer(funDataToBuffer)
		{
		}

		CSddExtendAct(std::function<bool(CBuffReaderBase&)> funBufferToData)
			:m_funBufferToData(funBufferToData)
		{
		}

		CSddExtendAct(std::function<void(CBufferBase&)> funDataToBuffer)
			:m_funDataToBuffer(funDataToBuffer)
		{
		}

		~CSddExtendAct()
		{
		}

		// �����ַ��������л��ͷ����л���������
		static std::shared_ptr<CSddExtendAct> Creation(std::function<bool(CBuffReaderBase&)> funBufferToData
			, std::function<void(CBufferBase&)> funDataToBuffer)
		{
			std::shared_ptr<CSddExtendAct> pItem = std::make_shared<CSddExtendAct>(funBufferToData, funDataToBuffer);
			if (pItem == nullptr)
			{
				throw CSddException("�����û���չ��Ϊ����ʧ��", __FILE__, __LINE__);
			}
			return pItem;
		}

		// �����ַ��������л��ͷ����л���������
		static std::shared_ptr<CSddExtendAct> Creation(std::function<bool(CBuffReaderBase&)> funBufferToData)
		{
			std::shared_ptr<CSddExtendAct> pItem = std::make_shared<CSddExtendAct>(funBufferToData);
			if (pItem == nullptr)
			{
				throw CSddException("�����û���չ��Ϊ����ʧ��", __FILE__, __LINE__);
			}
			return pItem;
		}

		// �����ַ��������л��ͷ����л���������
		static std::shared_ptr<CSddExtendAct> Creation(std::function<void(CBufferBase&)> funDataToBuffer)
		{
			std::shared_ptr<CSddExtendAct> pItem = std::make_shared<CSddExtendAct>(funDataToBuffer);
			if (pItem == nullptr)
			{
				throw CSddException("�����û���չ��Ϊ����ʧ��", __FILE__, __LINE__);
			}
			return pItem;
		}

		// �ӻ������ж�ȡ����
		// rBuffer ������
		// �ɹ�����true,ʧ�ܷ���false
		virtual bool BufferToData(CBuffReaderBase& rBuffReader)
		{
			if (m_funBufferToData == nullptr)
			{
				return true;
			}

			return m_funBufferToData(rBuffReader);
		}
		// ������д�뵽������
		// rBuffer ������
		virtual void DataToBuffer(CBufferBase& rBuffer)
		{
			if (m_funDataToBuffer != nullptr)
			{
				m_funDataToBuffer(rBuffer);
			}
		}

		// ��ȡ���л������л�ʹ�õ��ֽڳ���
		virtual size_t GetBufferLength()
		{
			return 0;
		}

	protected:
		std::function<bool(CBuffReaderBase& rBuffReader)> m_funBufferToData = nullptr;
		std::function<void(CBufferBase& rBuffer)> m_funDataToBuffer = nullptr;
	};

}
