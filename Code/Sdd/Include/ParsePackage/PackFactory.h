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
ʱ��:2020-12-09
����:�����л����ݰ������ӿ�
**************************************************************************/
#include <map>
#include <string>
#include <assert.h>
#include "PackFactBase.h"

namespace jaf
{
	// ���л����Ĺ���
	class CPackFactory :public CPackFactBase
	{
	public:
		CPackFactory() {}; // ���ع��캯��
		~CPackFactory() {};
	public:
		// ע�ᴴ�����ĺ���
		// nPackageType ������
		// createFun �������ĺ���
		virtual void RegisterCreateFun(unsigned int nPackageType, CreatePackageFun createFun)
		{
			std::map<unsigned int, CreatePackageFun>::iterator it = m_mapCreateFun.find(nPackageType);
			if (it != m_mapCreateFun.end()) // û�ж�Ӧ���͵İ��Ĵ�������
			{
				throw "����" + std::to_string(nPackageType) + "�İ��Ѿ���ע��";
			}
			if (!createFun)
			{
				throw "Ҫע��Ĵ������ĺ���Ϊ��";
			}

			m_mapCreateFun.insert(std::pair<unsigned int, CreatePackageFun>(nPackageType, createFun));
		}

		// �ð����ͺ��ֽ����鴴����
		// nPackageType ������
		// pData ���ڴ�����������
		// nLen pData���ݵĳ���
		virtual std::shared_ptr<CPackBase> Create(unsigned int nPackageType, char* pData, size_t nLen)
		{
			std::map<unsigned int, CreatePackageFun>::iterator it = m_mapCreateFun.find(nPackageType);
			if (it == m_mapCreateFun.end()) // û�ж�Ӧ���͵İ��Ĵ�������
			{
				return std::shared_ptr<CPackBase>(); // ����һ����ָ��
			}

			assert(it->second);

			std::shared_ptr<CPackBase> p;
			p = (it->second)(pData, nLen);
			return p;
		}

	protected:
		std::map<unsigned int, CreatePackageFun> m_mapCreateFun; // ���ڱ���ÿ�ְ����������䴴������
	};

} // namespace jaf

