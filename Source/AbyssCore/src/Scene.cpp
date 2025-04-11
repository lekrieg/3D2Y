#include "Scene.h"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/System/Vector2.hpp"

int abyss::Scene::Width() const
{
	return m_application->GetWindow().getSize().x;
}

int abyss::Scene::Height() const
{
	return m_application->GetWindow().getSize().y;
}

void abyss::Scene::DrawLine(sf::Vector2<float> p1, sf::Vector2f p2)
{
	std::array line =
	{
		sf::Vertex{ p1 },
		sf::Vertex{ p2 }
	};

	m_application->GetWindow().draw(line.data(), line.size(), sf::PrimitiveType::Lines);
}
