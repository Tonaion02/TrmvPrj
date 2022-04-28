#pragma once

#include <array>

#include "ECS/Entity.h"
#include "ECS/Signature.h"





class SignatureManager
{
public:
	inline static SignatureManager& get()
	{
		static SignatureManager instance = SignatureManager();
		return instance;
	}

	inline bool isThereTypeCmp(Entity e, int type) { return (bool)signatures[e][type]; }
	inline void registerTypeCmp(Entity e, int type) { signatures[e][type] = 1; }
	inline void unRegisterTypeCmp(Entity e, int type) { signatures[e][type] = 0; }

protected:
	SignatureManager();

protected:
	std::array<Signature, MAX_ENTITIES> signatures;
};