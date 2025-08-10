#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "Yaml.h"
#include "../Application.h"

#include <memory>

class Serializer
{
private:

	Application* m_app = nullptr;

public:

	explicit Serializer(Application* app) : m_app(app)
	{
	}

	void Serialize(YAML::Emitter &em);

	void Deserialize(const YAML::Node& nodes);

	void SerializeSprite(YAML::Emitter &em, const std::shared_ptr<SpriteAsset>& s);
	void DeserializeSprite(const YAML::Node& node, std::vector<std::shared_ptr<SpriteAsset>>& sprites);

	void SerializeAudio(YAML::Emitter &em, const std::shared_ptr<AudioAsset>& a);
	void DeserializeAudio(const YAML::Node& node, std::vector<std::shared_ptr<AudioAsset>>& audios);

	void SerializeFont(YAML::Emitter &em, const std::shared_ptr<FontAsset>& f);
	void DeserializeFont(const YAML::Node& node, std::vector<std::shared_ptr<FontAsset>>& fonts);
};

#endif
