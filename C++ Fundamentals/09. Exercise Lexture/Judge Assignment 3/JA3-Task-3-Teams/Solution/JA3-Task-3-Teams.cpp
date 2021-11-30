#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <sstream>

using namespace std;

class Player {
    int score;
public:
    const string name;

    Player() {}

    Player(string name) : name(name), score(0) {}

    int getScore() const {
        return this->score;
    }

    void increaseScore() {
        this->score++;
    }
};

int main() {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    map<string, Player> players;
    map<string, vector<string> > teamPlayers;

    int numTeams;
    cin >> numTeams;
    for (int i = 0; i < numTeams; i++) {
        string teamName;
        cin >> teamName;
        int numPlayers;
        cin >> numPlayers;
        vector<string> currTeamPlayers = teamPlayers[teamName];
        for (int teammateInd = 0; teammateInd < numPlayers; teammateInd++) {
            string playerName;
            cin >> playerName;

            auto playerIter = players.find(playerName);
            if (playerIter == players.end()) {
                players.insert({playerName, Player(playerName)});
            }

            currTeamPlayers.push_back(playerName);
        }

        teamPlayers[teamName] = currTeamPlayers;
    }

    int numGames;
    cin >> numGames;
    for (int i = 0; i < numGames; i++) {
        string winningTeam;
        cin >> winningTeam;

        auto winningPlayers = teamPlayers[winningTeam];
        for (string playerName : winningPlayers) {
            players[playerName].increaseScore();
        }
    }

    for (auto entry : players) {
        cout << entry.second.getScore() << " ";
    }

    return 0;
}
