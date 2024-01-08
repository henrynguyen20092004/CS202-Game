#include "HighScore.hpp"

HighScore::HighScore() { loadScores(); }

HighScore::~HighScore() {
    std::ofstream fout("data/HighScore.txt");

    for (int i = 0; i < mHighScores.size(); i++) {
        fout << mHighScores[i] << '\n';
    }

    fout.close();
}

const std::vector<int>& HighScore::getHighScores() { return mHighScores; }

void HighScore::rankScore(int score) {
    for (int i = 0; i < mHighScores.size(); i++) {
        if (score > mHighScores[i]) {
            mHighScores.insert(mHighScores.begin() + i, score);
            mHighScores.pop_back();
            break;
        }
    }
}

void HighScore::loadScores() {
    std::ifstream fin("data/HighScore.txt");
    std::string line;

    while (getline(fin, line)) {
        mHighScores.push_back(std::stoi(line));
    }

    fin.close();
}
