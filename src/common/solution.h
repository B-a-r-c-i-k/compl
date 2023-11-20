#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

class TSetCoverage {
public:
    int sizeM;
    int countSubsetsS;
    int answer = 0;
    vector<int> subsetAnswer;

    set<int> setM;
    vector<set<int>> setsS;
    map<int, vector<int>> positionElementInSets;
    set<pair<int, int>> countNotVisitedElementsInSAndS;


    bool IsEnd() {
        return setM.empty();
    }

    void FindBestSubset() {
        pair<int, int> bestSubset = *(--countNotVisitedElementsInSAndS.end());
        ++answer;
        subsetAnswer.push_back(bestSubset.second + 1);
        countNotVisitedElementsInSAndS.erase(bestSubset);
        for (auto element : setsS[bestSubset.second]) {
            if (setM.find(element) != setM.end()) {
                setM.erase(element);
            }
            for (auto subsetsNumber : positionElementInSets[element]) {
                if (subsetsNumber == bestSubset.second) {
                    continue;
                }
                pair<int, int> countAndSubset = {setsS[subsetsNumber].size(), subsetsNumber};
                setsS[subsetsNumber].erase(element);
                countNotVisitedElementsInSAndS.erase(countAndSubset);
                --countAndSubset.first;
                if (countAndSubset.first != 0) {
                    countNotVisitedElementsInSAndS.insert(countAndSubset);
                }
            }
            positionElementInSets.erase(element);
        }
        setsS[bestSubset.second].clear();
    }

public:

    TSetCoverage(int _sizeM, vector <int> _M, int _countSubsetsS,
                 vector<set<int>> _setsS) :
                 sizeM(_sizeM), countSubsetsS(_countSubsetsS), setsS(_setsS) {
        for (auto element : _M) {
            setM.insert(element);
        }
        for (int i = 0; i < setsS.size(); ++i) {
            for (auto element : setsS[i]) {
                positionElementInSets[element].push_back(i);
            }
            countNotVisitedElementsInSAndS.insert({setsS[i].size(), i});
        }
    }

    void Read() {
        cin >> sizeM;
        for (int i = 0; i < sizeM; ++i) {
            int element;
            cin >> element;
            setM.insert(element);
        }
        cin >> countSubsetsS;
        setsS.resize(countSubsetsS);
        for (int i = 0; i < countSubsetsS; ++i) {
            int countElementsInS;
            cin >> countElementsInS;
            for (int j = 0; j < countElementsInS; ++j) {
                int element;
                cin >> element;
                positionElementInSets[element].push_back(i);
                setsS[i].insert(element);
            }
            countNotVisitedElementsInSAndS.insert({setsS[i].size(), i});
        }
    }

    void FindSetCoverage() {
        while(!IsEnd()) {
            FindBestSubset();
        }
    }

    void PrintAnswer() {
        cout << answer << endl;
        sort(subsetAnswer.begin(), subsetAnswer.end());
        for (auto subsetNumber : subsetAnswer) {
            cout << subsetNumber << " ";
        }
    }

    int GetCountCoverage() {
        return answer;
    }
};

