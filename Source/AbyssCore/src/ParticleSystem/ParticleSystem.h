//
// Created by lekrieg on 19/11/2025.
//

#ifndef SUNRISE_PARTICLE_SYSTEM_H
#define SUNRISE_PARTICLE_SYSTEM_H

#include <vector>

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/System/Vector2.hpp"

class ParticleSystem
{
    struct Particle
    {
        sf::Vector2f velocity;
        int lifetime = 0;
    };

    std::vector<Particle> m_particles;
    sf::VertexArray m_vertices;
    float m_size = 8;

    // if I want a bunch of places I cound add an index to particle and make the emitter an array
    // this I could make a bunch of torches or something similar
    sf::Vector2f m_emitter;

    void ResetParticles(size_t count = 1024, float size = 8)
    {
        m_particles = std::vector<Particle>(count);
        m_vertices = sf::VertexArray(sf::PrimitiveType::Triangles, count * 3);
        m_size = size;

        for (size_t p = 0; p < m_particles.size(); p++)
        {
            ResetParticle(p, true);
        }
    }

    void ResetParticle(size_t index, bool first = false)
    {
        float x = m_emitter.x / 2;
        float y = m_emitter.y / 2;

        m_vertices[index * 3 + 0].position = sf::Vector2f(x, y);
        m_vertices[index * 3 + 1].position = sf::Vector2f(x + m_size, y);
        m_vertices[index * 3 + 2].position = sf::Vector2f(x, y + m_size);

        sf::Color color(128 + rand() % 128, 55, 55, rand() % 255);

        if (first)
        {
            color.a = 0;
        }

        m_vertices[index * 3 + 0].color = color;
        m_vertices[index * 3 + 1].color = color;
        m_vertices[index * 3 + 2].color = color;

        // TODO: update this to cpp 11 way
        float rx = ((float)rand() / RAND_MAX) * 3;
        float ry = ((float)rand() / RAND_MAX) * 3;
        m_particles[index].velocity = sf::Vector2f(rx, ry);

        m_particles[index].lifetime = 30 + rand() % 60;
    }

public:

    ParticleSystem() = default;

    void Init(const sf::Vector2f emitter)
    {
        m_emitter = emitter;
        ResetParticles();
    }

    void Update()
    {
        for (size_t i = 0; i < m_particles.size(); ++i)
        {
            if (m_particles[i].lifetime == 0)
            {
                ResetParticle(i);
            }

            m_vertices[i * 3 + 0].position += m_particles[i].velocity;
            m_vertices[i * 3 + 1].position += m_particles[i].velocity;
            m_vertices[i * 3 + 2].position += m_particles[i].velocity;

            m_particles[i].lifetime--;
        }
    }

    void Draw(sf::RenderWindow& window) const
    {
        window.draw(m_vertices);
    }
};

#endif //SUNRISE_PARTICLE_SYSTEM_H