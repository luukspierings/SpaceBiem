
#include "Player.h"

namespace spacebiem
{
    Player & Player::current()
    {
        static Player instance;
        return instance;
    }

    Player::Player()
        : name{playerOneName()}
    {
    }

    Player::Player(const std::string & name)
        : name{ name }
    {
    }

    Player::~Player()
    {
    }

    const std::string & Player::getName() const
    {
        return name;
    }
    void Player::setName(const std::string & pName)
    {
        name = pName;
    }

    std::string Player::saveLocation() const
    {
        return "savegame.csv";
    }

    std::string Player::resourceLocation() const
    {
        return "resources.csv";
    }

	std::string Player::progressLocation() const
	{
        return "progress.csv";
	}

    std::string Player::resolvePath(const std::string & filename)
    {
        return "data/" + name + "/" + filename;
    }
}
