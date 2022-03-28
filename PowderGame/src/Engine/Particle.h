#pragma once

#include <vector>

#include "../Helpers.h"


enum ParticleType : uint8_t
{
	NullParticle, Gas, Liquid, SolidMovable, SolidImmovable
};


// Contains properties that are common to all cells that contain this particle
struct Particle
{
public:
	char name[5];

	// blue-green-red-alpha format because of the way the pixel buffer accepts input 
	// (it's easy to treat it like an int like this)
	Vector4<uint8_t> color; 
	ParticleType type;
};


static std::vector<Particle> particleArr
{
	// 0
	{"NULL",
	0, 0, 0, 255,
	ParticleType::NullParticle },

	// 1
	{"SAND",
	128, 178, 194, 255,
	ParticleType::SolidMovable },

	// 2
	{"STNE",
	133, 142, 145, 255,
	ParticleType::SolidMovable },

	// 3
	{"SNOW",
	250, 224, 192, 255,
	ParticleType::SolidMovable },

	// 4
	{"SALT",
	253, 250, 243, 255,
	ParticleType::SolidMovable },

	// 5
	{"PLUT",
	36, 166, 88, 255,
	ParticleType::SolidMovable },
};

