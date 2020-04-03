#include "ParticleSystem.h"
#include <iostream>

ParticleSystem::ParticleSystem()
{
	particles.resize(index + 1);
}

void ParticleSystem::Draw(sf::RenderTarget& rt)
{
	for (size_t i = particles.size() - 1; i > 0; i--)
	{
		if (particles[i].active)
		{
			float coefficient = 1.0f - (particles[i].lifeTime / particles[i].fullLife);
			const float size = particles[i].sizeStart - particles[i].sizeStart * coefficient;

			sf::Color color = particles[i].endColor - particles[i].startColor;
			color.a = 255.f * coefficient;
			color.r *= coefficient;
			color.g *= coefficient;
			color.b *= coefficient;
			color += particles[i].startColor;

			sf::RectangleShape rect;
			rect.setOrigin(sf::Vector2f(size / 2.f, size / 2.f));
			rect.setPosition(particles[i].pos);
			rect.setSize(sf::Vector2f(size, size));
			rect.setRotation(particles[i].rotation);
			rect.setFillColor(color);

			rt.draw(rect);
		}
	}
	/*	// ei kuulu tähä systeemiin. vanha juttu
	particles.erase(std::remove_if(particles.begin(), particles.end(),
		[](const Particle& p) {return p.lifeTime <= 0.0f; }),
		particles.end());
		*/
}

void ParticleSystem::SpawnParticle(sf::Vector2f pos, const ParticleProperties& pp)
{
	if (spawn)
	{
		spawn = false;
		Particle& p = particles[index];
		p.active = true;
		p.pos = pos;
		p.vel.x = pp.vel.x * Random::GetRandomFloat(-1.0f, 1.0f);
		p.vel.y = pp.vel.y * Random::GetRandomFloat(-1.0f, 1.0f);
		p.sizeStart = pp.sizeStart + pp.sizeVariation * Random::GetRandomFloat(-1.0, 1.0f);
		p.sizeEnd = pp.sizeEnd;
		p.startColor = pp.startColor;
		p.endColor = pp.endColor;
		p.rotation = Random::GetRandomInt(0, 360);
		p.lifeTime = pp.lifeTime + Random::GetRandomFloat(-0.5f, 0.5f);
		p.fullLife = p.lifeTime;
		//++ drawaa vanhat päällimmäisiksi ja -- drawaa vanhat päällimmäisiksi
		index = ++index % particles.size();
	}
	
}

void ParticleSystem::Update(float dt)
{
	for (auto& p : particles )
	{
		if (!p.active)
		{
			continue;
		}
		if (p.lifeTime <= 0.0f)
		{
			p.active = false;
			continue;
		}
		p.pos += p.vel * dt;
		p.rotation += 50.0f * dt;
		p.lifeTime -= dt;
	}
	curTime -= dt;
	if (curTime <= 0.0f)
	{
		spawn = true;
		curTime = time;
	}
}
