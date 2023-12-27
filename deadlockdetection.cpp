#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

class DeadlockDetector {
private:
    int numProcesses;
    vector<unordered_set<int>> allocation;
    vector<unordered_set<int>> request;

public:
    DeadlockDetector(int processes) : numProcesses(processes) {
        allocation.resize(numProcesses);
        request.resize(numProcesses);
    }

    void allocateResource(int process, int resource) {
        allocation[process].insert(resource);
    }

    void requestResource(int process, int resource) {
        request[process].insert(resource);
    }

    bool isDeadlocked() {
        vector<int> inDegrees(numProcesses, 0);

       
        for (int i = 0; i < numProcesses; ++i) {
            for (int r : allocation[i]) {
                if (request[r].count(i) > 0) {
                    inDegrees[i]++;
                }
            }
        }
 
        queue<int> q;
        for (int i = 0; i < numProcesses; ++i) {
            if (inDegrees[i] == 0) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int process = q.front();
            q.pop();

            for (int r : allocation[process]) {
                for (int nextProcess : request[r]) {
                    if (--inDegrees[nextProcess] == 0) {
                        q.push(nextProcess);
                    }
                }
            }
        }

        
        for (int inDegree : inDegrees) {
            if (inDegree > 0) {
                return true;
            }
        }

        return false;
    }
};

int main() {
   
    DeadlockDetector detector(5);

    detector.allocateResource(0, 1);
    detector.allocateResource(1, 2);
    detector.allocateResource(2, 3);

    detector.requestResource(3, 1);
    detector.requestResource(4, 2);

    if (detector.isDeadlocked()) {
        cout << "Deadlock detected!\n";
    } else {
        cout << "No deadlock detected.\n";
    }

    return 0;
}

