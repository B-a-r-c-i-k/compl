//
// Created by kir10 on 21.10.2023.
//

#include "solution.h"

set<int> setM;
vector<set<int>> setsS;
map<int, vector<int>> positionElementInSets;
set<pair<int, int>> countNotVisitedElementsInSAndS;

int countElementsInM, countSubsetsS;
int answer;
vector<int> subsetAnswer;

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

int main() {
    cin >> countElementsInM;
    for (int i = 0; i < countElementsInM; ++i) {
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
    while(!IsEnd()) {
        FindBestSubset();
    }
    cout << answer << endl;
    sort(subsetAnswer.begin(), subsetAnswer.end());
    for (auto subsetNumber : subsetAnswer) {
        cout << subsetNumber << " ";
    }
}