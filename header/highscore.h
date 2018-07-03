#ifndef HIGHSCORE_H
#define HIGHSCORE_H

using namespace std;

class highscore{
public:
    highscore(string name, uint score);
    string name;
    uint score;
};

highscore::highscore(string name, uint score){
    this->score = score;
    this->name = name;
}

inline bool operator< (const highscore& lhs, const highscore& rhs){ return lhs.score < rhs.score; }
inline bool operator> (const highscore& lhs, const highscore& rhs){ return lhs.score > rhs.score; }

std::ostream& operator<<(std::ostream& out, const highscore& hs){
   return out << hs.name << " SCORED: " << hs.score;
}

#endif
