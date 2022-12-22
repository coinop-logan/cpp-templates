#include <math.h>
#include <chrono>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string.hpp>
#include <vector>

using namespace std;

class SensitiveEnemy
{
public:
    int health;
    bool dead;
    SensitiveEnemy(int health)
        : health(health), dead(false)
        {}

    void deductHealthMaybeDie(int amount)
    {
        health -= amount;
        if (health <= 0)
        {
            dead = true;
        }
    }
    virtual string announceSelf() {}
    virtual void hearInsult(string insult) {}
};

class Rylan : public SensitiveEnemy
{
public:
    int estimatedPopularity;
    Rylan()
        : SensitiveEnemy(30), estimatedPopularity(50)
    {}
    string announceSelf()
    {
        if (estimatedPopularity > 0)
            return "*minecraft villager dying noises*";
        else
            return "*hides his tears*";
    }
    void hearInsult(string insult)
    {
        if (boost::algorithm::contains(insult, "weak"))
        {
            deductHealthMaybeDie(10);
        }
        if (boost::algorithm::contains(insult, "nonpog"))
        {
            estimatedPopularity -= 1000;
        }
    }
};

class Ozzy : public SensitiveEnemy
{
public:
    Ozzy()
        : SensitiveEnemy(50)
    {}
    string announceSelf()
    {
        return "*ignores you*";
    }
    void hearInsult(string insult)
    {
        if (boost::algorithm::contains(insult, "short"))
        {
            deductHealthMaybeDie(10);
        }
    }
};

vector<boost::shared_ptr<SensitiveEnemy>> enemies;

void makeSomeEnemies()
{
    enemies.push_back(boost::shared_ptr<Ozzy>(new Ozzy()));
    enemies.push_back(boost::shared_ptr<Ozzy>(new Ozzy()));
    enemies.push_back(boost::shared_ptr<Rylan>(new Rylan()));
}

int main (int argc, char **argv)
{
    makeSomeEnemies();

    for (int i=0; i<enemies.size(); i++)
    {
        cout << "enemy " << i << ": " << enemies[i]->announceSelf() << endl;
    }

    cout << "type enemy number followed by insult" << endl << endl;

    while (true)
    {
        string command;

        cout << ">> ";
        getline (cin, command);
        
        vector<string> words;
        boost::split(words, command, boost::is_any_of(" "));
        int enemyNum = stoi(words[0]);

        words.erase(words.begin());

        if (enemyNum < enemies.size())
        {
            if (auto enemy = enemies[enemyNum])
            {
                if (auto rylan = boost::dynamic_pointer_cast<Rylan, SensitiveEnemy>(enemy))
                {
                    cout << "it looks kinda like a Rylan, and " <<
                        (rylan->estimatedPopularity > 0 ? "it looks confident" : "it looks ashamed") << endl;
                }
                enemy->hearInsult(boost::join(words, " "));
                cout << "enemy: " << enemy->announceSelf() << endl;
            }
        }

        for (int i=0; i<enemies.size(); i++)
        {
            if (enemies[i]->dead)
            {
                cout << "enemy " << i << " has fallen over dead!" << endl;
                enemies.erase(enemies.begin() + i);
                i --;
            }
        }
    }
    
    return 0;
}