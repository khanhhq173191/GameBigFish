#include "stdafx.h"
#include "../Utilities/utilities.h"
#include "sound.h"

void Sound::Play(std::string fileName)
{
	soundBuffer.loadFromFile(fileName);
	soundd.push_back(sf::Sound(soundBuffer));
	soundd.back().play();
	for (int i = 0; i < soundd.size(); ++i)
	{
		if (soundd[i].getStatus() == sf::Sound::Stopped)
		{
			soundd.erase(soundd.begin() + i);
			--i;
		}
	}
}

void Music::Play()
{
	if (Singleton<SceneManager>::GetInstance()->GameOver()) {
		musiC.openFromFile("../Resources/Sound/wave2.wav");
	}
	else
	{
		musiC.openFromFile("../Resources/Sound/He.ogg");
	}
	musiC.setLoop(true);// lap lai
	musiC.setVolume(40.f);// am luong bang 50 % am luong goc
	musiC.play();
	std::cin.get();
	cout << 1;
}

void Music::Play2()
{
	musiC.openFromFile("../Resources/Sound/bubbles2.wav");
	musiC.setLoop(true);// lap lai
	musiC.setVolume(100.f);// am luong bang 50 % am luong goc
	musiC.play();
	std::cin.get();
}

void _Thread::soundthread()
{
	while (true)
	{
		if (Singleton<Game>::GetInstance()->Flash)
		{
			sound.Play("../Resources/Sound/bubbleLoop.wav");
			Singleton<Game>::GetInstance()->Flash = false;
		}
		if (Singleton<Game>::GetInstance()->LevelUp)
		{
			sound.Play("../Resources/Sound/freeLife.wav");
			Singleton<Game>::GetInstance()->LevelUp = false;
		}
		if (Singleton<Game>::GetInstance()->Newgm)
		{
			sound.Play("../Resources/Sound/starPickup.wav");
			Singleton<Game>::GetInstance()->Newgm = false;
		}
		Sleep(1000);
	}
}

void _Thread::sound2() {
	while (true)
	{
		if (Singleton<Game>::GetInstance()->Eat)
		{
			sound.Play("../Resources/Sound/bite1.wav");
			Singleton<Game>::GetInstance()->Eat = false;
		}
		if (Singleton<Game>::GetInstance()->Disapear)
		{
			sound.Play("../Resources/Sound/pufferBounce.wav");
			Singleton<Game>::GetInstance()->Disapear = false;
		}
		Sleep(1000);
	}
}