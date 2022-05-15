#pragma once

#include <array>

#include "SDL_Enviroment.h"

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

	inline bool isThereTypeCmp(Entity e, unsigned int type) { return (bool)signatures[e][type]; }
	inline void registerTypeCmp(Entity e, unsigned int type) { signatures[e][type] = 1; }
	inline void unRegisterTypeCmp(Entity e, unsigned int type) { signatures[e][type] = 0; }
	void printSignatureEntity(Entity e) 
	{
		SDL_Log("%s", signatures[e].to_string().c_str());
	}

protected:
	SignatureManager();

protected:
	std::array<Signature, MAX_ENTITIES> signatures;
};