#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "HashTable.h"
#include "RenderDefines.h"

#include <assert.h>
#include <vector>
#include <string>

namespace abyss
{
	namespace utils
	{
		template <typename TAG>
		class Handle
		{
			int m_index;

		public:
			Handle() { m_index = -1; }

			void Initialize(int index) { m_index = index; }
			void Nullify() { m_index = -1; }
			int GetIndex() { return m_index; }
			bool IsNull() { return (m_index <= -1); }

			bool operator==(Handle<TAG> handle)
			{
				return m_index == handle.GetIndex();
			}
		};

		class ResourceName
		{
			std::string m_name;
			int m_index;

		public:
			ResourceName()
			{
				m_index = -1;
			}

			std::string GetName() { return m_name; }
			int GetIndex() { return m_index; }

			void SetName(std::string name) { m_name = name; }
			void SetIndex(int index) { m_index = index; }

			bool operator==(ResourceName resName)
			{
				return (m_name == resName.GetName() && m_index == resName.GetIndex());
			}
		};

		template <typename A, typename HANDLE>
		class ResourceManager
		{
			std::vector<A*> m_objects;
			HashTable<ResourceName> *m_resourceHash;

		public:
			ResourceManager(int hashSize = 0)
			{
				m_resourceHash = nullptr;

				if (hashSize > 0)
				{
					m_resourceHash = new HashTable<ResourceName>(hashSize);
				}
			}

			~ResourceManager()
			{
				DeleteAllMemory();
			}

			bool Create(A* res, char* name, HANDLE* handle);
			void Release(HANDLE handle);

			int GetRegisteredIndex(char *name);

			A* GetResource(HANDLE handle)
			{
				int index = handle.GetIndex();

				if (index >= GetSize() || index <= -1)
				{
					return nullptr;
				}

				return m_objects[handle.GetIndex()];
			}

			int GetSize()
			{
				return static_cast<int>(m_objects.size());
			}

			std::vector<A*>* GetObjects()
			{
				return &m_objects;
			}

		private:
			void SetRegisteredName(char* name, int index);

			void DeleteAllMemory()
			{
				for (int i = 0; i < GetSize(); i++)
				{
					if (m_objects[i])
					{
						delete m_objects[i];
					}

					m_objects[i] = nullptr;
				}

				if (m_resourceHash != nullptr)
				{
					delete m_resourceHash;
				}

				m_resourceHash = nullptr;
			}
		};

		template <typename A, typename HANDLE>
		bool ResourceManager<A, HANDLE>::Create(A* res, char* name, HANDLE* handle)
		{
			int index = -1;

			if (res == nullptr)
			{
				return false;
			}

			if (handle)
			{
				handle->Nullify();
			}

			index = GetRegisteredIndex(name);

			if (index == -1)
			{
				m_objects.push_back(res);

				index = static_cast<int>(m_objects.size()) - 1;

				if (index < 0)
				{
					return false;
				}

				SetRegisteredName(name, index);
			}

			if (handle)
			{
				handle->Initialize(index);
			}

			return true;
		}

		template <typename A, typename HANDLE>
		void ResourceManager<A, HANDLE>::Release(HANDLE handle)
		{
			int index = handle.GetIndex();

			if (handle.IsNull())
			{
				return;
			}

			handle.Nullify();
		}

		template <typename A, typename HANDLE>
		int ResourceManager<A, HANDLE>::GetRegisteredIndex(char* name)
		{
			HashItem<ResourceName> tempHashItem;
			ResourceName tempRes;
			int key = -1;

			if (name == nullptr)
			{
				return -1;
			}

			std::string str(name);

			if (m_resourceHash != nullptr)
			{
				key = m_resourceHash->HashFunction(str);
				tempHashItem = m_resourceHash->Find(key);

				if (tempHashItem.GetKey() != -1 && tempHashItem.GetObject().GetName() == str)
				{
					return tempHashItem.GetObject().GetIndex();
				}
			}

			return -1;
		}

		template <typename A, typename HANDLE>
		void ResourceManager<A, HANDLE>::SetRegisteredName(char* name, int index)
		{
			if (name == nullptr || m_resourceHash == nullptr || index < 0)
			{
				return;
			}

			HashItem<ResourceName> hashItem;
			std::string str(name);

			ResourceName resName;
			resName.SetName(name);
			resName.SetIndex(index);

			hashItem.SetKey(m_resourceHash->HashFunction(str));
			hashItem.SetObj(resName);

			m_resourceHash->Insert(hashItem);
		}
	}
}

#endif