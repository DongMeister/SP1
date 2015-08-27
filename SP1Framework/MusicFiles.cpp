#include "MusicFiles.h"

std::wstring MusicFiles[] = {L"Music/Clock.wav", L"Music/Puppet.wav", L"Music/Shudder.wav", L"Music/Tension.wav", L"Music/Departure.wav", L"Music/Madness.wav", L"Music/Psychopath.wav", L"Music/Memory.wav", L"Music/OldDoll.wav", L"Music/BattleWin.wav", L"Music/GameOverBitch.wav"};

void MusicWillPlay(int ChooseMusic)
{
	PlaySound(MusicFiles[ChooseMusic].c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}