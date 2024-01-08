#ifndef HIGH_SCORE_HPP
#define HIGH_SCORE_HPP

#include "../TextNode/TextNode.hpp"

class HighScore {
   public:
    HighScore();
    ~HighScore();

    const std::vector<int>& getHighScores();

    void rankScore(int score);

   private:
    std::vector<int> mHighScores;

    void loadScores();
};

#endif
