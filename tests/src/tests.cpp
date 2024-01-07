#include <gtest/gtest.h>
#include <cmath>
#include "solution.h"

vector<int> GenerateM(int minSizeM = 5, int maxSizeM = 8) {
    int sizeM = minSizeM + rand() % (maxSizeM - minSizeM + 1);
    vector<int> M;
    for (int i = 0; i < sizeM; ++i) {
        M.push_back(i + 1);
    }
    return M;
}

TSetCoverage GenerateTestsSuite1() {
    vector<int> M = GenerateM();
    int minCountSubsetsS = 5;
    int maxCountSubsetsS = 20;
    int countSubsetsS = minCountSubsetsS + rand() % (maxCountSubsetsS - minCountSubsetsS + 1);
    vector<set<int>> subsetsS(countSubsetsS);
    for (int i = 0; i < M.size(); ++i) {
        bool isInserted = false;
        for (int j = 0; j < countSubsetsS; ++j) {
            bool needInsert = rand() % 2;
            if (needInsert) {
                subsetsS[j].insert(M[i]);
                isInserted = true;
            }
        }
        if (!isInserted) {
            --i;
        }
    }
    TSetCoverage tSetCoverage(M.size(), M, countSubsetsS, subsetsS);
    return tSetCoverage;
}

TSetCoverage GenerateTestsSuite2(int limit = 3) {
    vector<int> M = GenerateM();
    int minCountSubsetsS = 5;
    int maxCountSubsetsS = 20;
    int countSubsetsS = minCountSubsetsS + rand() % (maxCountSubsetsS - minCountSubsetsS + 1);
    vector<set<int>> subsetsS(countSubsetsS);
    for (int i = 0; i < M.size(); ++i) {
        bool isInserted = false;
        for (int j = 0; j < countSubsetsS; ++j) {
            bool needInsert = rand() % 2;
            if (needInsert && subsetsS[j].size() < limit) {
                subsetsS[j].insert(M[i]);
                isInserted = true;
            }
        }
        if (!isInserted) {
            --i;
        }
    }
    TSetCoverage tSetCoverage(M.size(), M, countSubsetsS, subsetsS);
    return tSetCoverage;
}

TSetCoverage GenerateTestsSuite3(int minSizeSubset = 4) {
    vector<int> M = GenerateM();
    int minCountSubsetsS = 5;
    int maxCountSubsetsS = 20;
    int countSubsetsS = minCountSubsetsS + rand() % (maxCountSubsetsS - minCountSubsetsS + 1);
    vector<set<int>> subsetsS(countSubsetsS);
    for (int i = 0; i < M.size(); ++i) {
        bool isInserted = false;
        for (int j = 0; j < countSubsetsS; ++j) {
            bool needInsert = rand() % 2;
            if (needInsert) {
                subsetsS[j].insert(M[i]);
                isInserted = true;
            }
        }
        if (!isInserted) {
            --i;
        }
    }
    for (int i = 0; i < countSubsetsS; ++i) {
        int j = 0;
        while(subsetsS[i].size() < minSizeSubset) {
            bool needInsert = rand() % 2;
            if (needInsert) {
                subsetsS[i].insert(M[j]);
            }
            j = (j + 1) % (int)(M.size());
        }
    }
    TSetCoverage tSetCoverage(M.size(), M, countSubsetsS, subsetsS);
    return tSetCoverage;
}


int DFS(vector<int> currentChoiceSubsets, int currentSubset, TSetCoverage tSetCoverage) {
    if (currentSubset == tSetCoverage.countSubsetsS) {
        set<int> visited;
        for (int i = 0; i < currentChoiceSubsets.size(); ++i) {
            int subset = currentChoiceSubsets[i];
            for (auto element : tSetCoverage.setsS[subset]) {
                visited.insert(element);
            }
        }
        if (visited.size() == tSetCoverage.sizeM) {
            return currentChoiceSubsets.size();
        } else {
            return 1e9;
        }
    }
    int answer1 = DFS(currentChoiceSubsets, currentSubset + 1, tSetCoverage);
    currentChoiceSubsets.push_back(currentSubset);
    int answer2 = DFS(currentChoiceSubsets, currentSubset + 1, tSetCoverage);
    return min(answer1, answer2);
}

int SampleSolution(TSetCoverage tSetCoverage) {
    return DFS({}, 0, tSetCoverage);
}

//----------------------------------------------------------

TEST(TEST_common, filling_subsets) {
    int TEST_COUNT = 10;
    for (int i = 0; i < TEST_COUNT; ++i) {
        TSetCoverage tSetCoverage = GenerateTestsSuite1();
        int correctAnswer = SampleSolution(tSetCoverage);
        tSetCoverage.FindSetCoverage();
        int answer = tSetCoverage.GetCountCoverage();
        EXPECT_LE(correctAnswer, int(answer * std::log(tSetCoverage.sizeM)));
    }
}

TEST(TEST_common, small_subsets) {
    int TEST_COUNT = 10;
    for (int i = 0; i < TEST_COUNT; ++i) {
        TSetCoverage tSetCoverage = GenerateTestsSuite2();
        int correctAnswer = SampleSolution(tSetCoverage);
        tSetCoverage.FindSetCoverage();
        int answer = tSetCoverage.GetCountCoverage();
        EXPECT_LE(correctAnswer, int(answer * std::log(tSetCoverage.sizeM)));
    }
}

TEST(TEST_common, large_subsets) {
    int TEST_COUNT = 10;
    for (int i = 0; i < TEST_COUNT; ++i) {
        TSetCoverage tSetCoverage = GenerateTestsSuite3();
        int correctAnswer = SampleSolution(tSetCoverage);
        tSetCoverage.FindSetCoverage();
        int answer = tSetCoverage.GetCountCoverage();
        EXPECT_LE(correctAnswer, int(answer * std::log(tSetCoverage.sizeM)));
    }
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
