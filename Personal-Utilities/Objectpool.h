#pragma once

#include "typedefs.h"

namespace Leon::Utils
{
	template <typename T>
	class Objectpool
	{
		struct Freeobj
		{
			T* newobj;
			Freeobj* next = nullptr;
		public:
			Freeobj(T* t, Freeobj* f)
				: newobj(t), next(f)
			{
			}
		};
	private:
		Freeobj* free = nullptr;
	public:
		Objectpool()
		{
		}
		~Objectpool()
		{
			Freeobj* temp;
			while (free)
			{
				temp = free;
				free = free->next;
				delete (temp->newobj);
				delete temp;
			}
		}
	private: void CreateNew()
	{
		if (free)
		{
			free = new Freeobj(new T(), free);
		}
		else
		{
			free = new Freeobj(new T(), nullptr);
		}
	}
	public:
		void Allocate(uint16 times = 1)
		{
			for (int i = 0; i < times; i++)
			{
				CreateNew();
			}
		}

		T* GetNew()
		{
			if (free)
			{
				Freeobj* temp = free;
				T* ret = temp->newobj;
				free = free->next;
				delete temp;
				return ret;
			}
			else
			{
				return new T();
			}
		}
		void Release(T* t)
		{
			if (free)
			{
				free = new Freeobj(t, free);
			}
			else
			{
				free = new Freeobj(t, nullptr);
			}
		}
		inline void Delete(T* t)
		{
			delete t;
		}
	};
}