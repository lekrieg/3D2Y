#include "AudioManager.h"

#include "soloud_wav.h"

void core::AudioManager::PlayMusic(const std::string& name)
{
	// TODO: for now the music should play all the time, so I need to check if it's already playing and dont do anything

	m_internalMusicWav.load(m_gameApplication->GetAssets().GetSound(name).c_str());
	m_internalMusicWav.setLooping(1);

	m_soLoud.stopAll();
	m_internalHandle = m_soLoud.playBackground(m_internalMusicWav);
}

void core::AudioManager::PlaySound(const std::string& name)
{
	m_internalSoundWav.load(m_gameApplication->GetAssets().GetSound(name).c_str());

	m_soLoud.play(m_internalSoundWav);
}

bool core::AudioManager::IsMusicPlaying()
{
	return m_soLoud.isValidVoiceHandle(m_internalHandle);
}
