#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <iomanip>

using namespace std;

// Job Role Data Structure
struct JobRole {
    string title;
    vector<string> requiredSkills;
};

// String ko lowercase karne ka helper function
string toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// Vector Dot Product Calculation
double dotProduct(const vector<double>& A, const vector<double>& B) {
    double sum = 0.0;
    for (size_t i = 0; i < A.size(); ++i) {
        sum += A[i] * B[i];
    }
    return sum;
}

// Vector Magnitude (Length) Calculation
double vectorMagnitude(const vector<double>& A) {
    double sum = 0.0;
    for (double val : A) {
        sum += val * val;
    }
    return sqrt(sum);
}

// Cosine Similarity Formula: (A . B) / (||A|| * ||B||)
double calculateCosineSimilarity(const vector<double>& userVec, const vector<double>& jobVec) {
    double dot = dotProduct(userVec, jobVec);
    double magUser = vectorMagnitude(userVec);
    double magJob = vectorMagnitude(jobVec);

    if (magUser == 0.0 || magJob == 0.0) return 0.0; // Avoid Division by Zero

    return dot / (magUser * magJob);
}

int main() {
    cout << "========================================================\n";
    cout << "  DecodeLabs Project 3: AI Tech Stack Recommender (C++) \n";
    cout << "========================================================\n\n";

    // 1. Dataset: Job Roles and associated Skill Features
    vector<JobRole> dataset = {
        {"Data Scientist", {"python", "sql", "machine learning", "data analysis", "statistics"}},
        {"DevOps Engineer", {"aws", "docker", "kubernetes", "cicd", "linux", "cloud"}},
        {"Backend Developer", {"java", "python", "sql", "apis", "cpp", "databases"}},
        {"Frontend Developer", {"javascript", "html", "css", "react", "web design"}},
        {"AI / ML Engineer", {"python", "cplusplus", "machine learning", "tensorflow", "algorithms"}}
    };

    // Vocabulary space create karna (Unique skills across dataset)
    set<string> vocabSet;
    for (const auto& job : dataset) {
        for (const auto& skill : job.requiredSkills) {
            vocabSet.insert(toLower(skill));
        }
    }
    vector<string> vocabulary(vocabSet.begin(), vocabSet.end());

    // 2. User State Ingestion (Minimum 3 Inputs)
    cout << "Enter at least 3 skills/interests (separated by Enter or comma):\n";
    vector<string> userInputs;
    for (int i = 1; i <= 3; ++i) {
        string inputSkill;
        cout << "Skill " << i << ": ";
        getline(cin, inputSkill);
        if (!inputSkill.empty()) {
            userInputs.push_back(toLower(inputSkill));
        }
    }

    // 3. Vector Mapping (Binary Vector Space mapping)
    vector<double> userVector(vocabulary.size(), 0.0);
    for (size_t i = 0; i < vocabulary.size(); ++i) {
        for (const auto& input : userInputs) {
            if (vocabulary[i] == input || vocabulary[i].find(input) != string::npos) {
                userVector[i] = 1.0; // Active dimension
            }
        }
    }

    // 4. Scoring: Calculate Cosine Similarity for each Job Role
    vector<pair<double, string>> scoredRoles;

    for (const auto& job : dataset) {
        vector<double> jobVector(vocabulary.size(), 0.0);
        for (size_t i = 0; i < vocabulary.size(); ++i) {
            for (const auto& skill : job.requiredSkills) {
                if (vocabulary[i] == skill) {
                    jobVector[i] = 1.0;
                }
            }
        }

        double similarityScore = calculateCosineSimilarity(userVector, jobVector);
        scoredRoles.push_back({similarityScore, job.title});
    }

    // 5. Sorting: High score to low score
    sort(scoredRoles.rbegin(), scoredRoles.rend());

    // 6. Filtering & Output: Display Top-3 Recommendations
    cout << "\n--------------------------------------------------------\n";
    cout << "            TOP-3 RECOMMENDED CAREER PATHS              \n";
    cout << "--------------------------------------------------------\n";

    int topN = min(3, (int)scoredRoles.size());
    for (int i = 0; i < topN; ++i) {
        double matchPercentage = scoredRoles[i].first * 100.0;
        cout << i + 1 << ". " << left << setw(20) << scoredRoles[i].second 
             << " -> Match Score: " << fixed << setprecision(2) << matchPercentage << "%\n";
    }

    cout << "========================================================\n";

    return 0;
}