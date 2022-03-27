#pragma once

#include "../Helpers.h"


enum ParticleType : uint8_t
{
	Null, Gas, Liquid, SolidMovable, SolidImmovable
};


// Contains properties that are common to all cells that contain this particle
struct Particle
{
public:
	Vector4<uint8_t> color;
	uint8_t id;
	ParticleType type;
};
