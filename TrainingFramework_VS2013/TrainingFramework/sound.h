#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h"
#include <iostream>
#include "../Include/SFML/Audio.hpp"
#include <string.h>
#include <deque>
#include "Game.h"
#include <Windows.h>
class Sound
{
private:
	sf::SoundBuffer soundBuffer;
	std::deque<sf::Sound> soundd;
public:
	void Play(std::string FileName);
};

class Music
{
private:
	sf::Music musiC;
public:
	void Play();
	void Play2();
};

class _Thread
{
public:
	void soundthread();
	void sound2();

private:
	Sound sound;
};