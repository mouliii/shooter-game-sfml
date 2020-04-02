#include "ParticleSystem.h"
#include <iostream>

void ParticleSystem::Draw(sf::RenderTarget& rt)
{
	if (backToFront)
	{
		if (!particles.empty())
		{
			for (size_t i = particles.size() - 1; i > 0; i--)
			{
				if (particles[i].lifeTime >= 0.0f)
				{
					float coefficient = 1.0f - (particles[i].lifeTime / particles[i].fullLife);
					const float size = particles[i].sizeStart - particles[i].sizeStart * coefficient;

					sf::Color color = particles[i].endColor - particles[i].startColor;
					color.a = 255 * coefficient;
					color.r *= coefficient;
					color.g *= coefficient;
					color.b *= coefficient;
					color += particles[i].startColor;

					sf::RectangleShape rect;
					rect.setOrigin(sf::Vector2f(size / 2.f, size / 2.f));
					rect.setPosition(particles[i].pos);
					rect.setSize(sf::Vector2f(size, size));
					rect.setFillColor(color);

					rt.draw(rect);
				}
			}
		}
	}
	else
	{
		for (size_t i = 0; i < particles.size(); i++)
		{
			if (particles[i].lifeTime >= 0.0f)
			{
				float coefficient = 1.0f - (particles[i].lifeTime / particles[i].fullLife);
				const float size = particles[i].sizeStart - particles[i].sizeStart * coefficient;

				sf::Color color = particles[i].endColor - particles[i].startColor;
				color.a = 255 * coefficient;
				color.r *= coefficient;
				color.g *= coefficient;
				color.b *= coefficient;
				color += particles[i].startColor;

				sf::RectangleShape rect;
				rect.setOrigin(sf::Vector2f(size / 2.f, size / 2.f));
				rect.setPosition(particles[i].pos);
				rect.setSize(sf::Vector2f(size, size));
				rect.setFillColor(color);

				rt.draw(rect);
			}
		}
	}
	particles.erase(std::remove_if(particles.begin(), particles.end(),
		[](const Particle& p) {return p.lifeTime <= 0.0f; }),
		particles.end());
}

void ParticleSystem::SpawnParticle(sf::Vector2f pos, const ParticleProperties& pp)
{
	Particle p;
	p.pos = pos;
	p.vel.x = pp.vel.x * Random::GetRandomFloat(-1.0f, 1.0f);
	p.vel.y = pp.vel.y * Random::GetRandomFloat(-1.0f, 1.0f);
	p.sizeStart = pp.sizeStart + pp.sizeVariation * Random::GetRandomFloat(-1.0, 1.0f);
	p.sizeEnd = pp.sizeEnd;
	p.startColor = pp.startColor;
	p.endColor = pp.endColor;
	p.lifeTime = pp.lifeTime;
	p.fullLife = p.lifeTime;

	particles.push_back(p);
}

void ParticleSystem::Update(float dt)
{
	for (auto& p : particles )
	{

		p.pos += p.vel * dt;
		p.lifeTime -= dt;
	}
}
