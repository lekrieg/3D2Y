#ifndef YAML_H
#define YAML_H

#include "SFML/System/Vector2.hpp"
#include "yaml-cpp/yaml.h"

namespace YAML
{
	template <> struct convert<sf::Vector2f>
	{
			inline static Node encode(const sf::Vector2f &rhs)
			{
				Node node;
				node.push_back(rhs.x);
				node.push_back(rhs.y);
				node.SetStyle(EmitterStyle::Flow);
				return node;
			}

			inline static bool decode(const Node &node, sf::Vector2f &rhs)
			{
				if (!node.IsSequence() || node.size() != 2)
				{
					return false;
				}
				rhs.x = node[0].as<float>();
				rhs.y = node[1].as<float>();
				return true;
			}
	};

	// stream operator
	inline Emitter &operator<<(Emitter &emitter, const sf::Vector2f &v)
	{
		emitter << Flow;
		emitter << BeginSeq << v.x << v.y << EndSeq;
		return emitter;
	}
}

#endif
