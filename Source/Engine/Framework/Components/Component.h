#pragma once
#include "Framework/Object.h"

namespace kiko
{
	///                    vvvvvv
	class Component : public Object
	{
	public:
		virtual void Update(float dt) = 0;

		friend class Actor;

	///made public
	public:
		class Actor* m_owner = nullptr;
	};
}