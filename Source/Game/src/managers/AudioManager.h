#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include "soloud.h"
#include "../GameApplication.h"

#include <string>

namespace game
{
	class GameApplication;

	class AudioManager
	{
		game::GameApplication* m_gameApplication;

		SoLoud::Soloud m_soLoud;
		SoLoud::Wav m_internalMusicWav;
		SoLoud::Wav m_internalSoundWav;
		SoLoud::handle m_internalHandle;

	public:
		AudioManager(game::GameApplication* gameApplication = nullptr) : m_gameApplication(gameApplication)
		{
			m_soLoud.init();
		}

		~AudioManager()
		{
			m_soLoud.deinit();
		}

		void PlayMusic(const std::string& name);
		void PlaySound(const std::string& name);
		bool IsMusicPlaying();
	};
}

#endif
