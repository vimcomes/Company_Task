#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

class CEO {
    int mainTask=0;
    std::string leadName;
public:
    void setLeadName(const std::string& name) {
        leadName = name;
    }
    std::string getLeadName() {
        return leadName;
    }
    int getMainTask() const {
        return mainTask;
    }
    void setMainTask (int number) {
        mainTask = number;
    }
};

class Manager {
    int serial_number=0;
    int totalNumberTask=0;
    int countFreeWorkers=0;
    std::vector<std::string> names;
    std::vector<char> task;

public:
    Manager() = default;
    Manager (int& inSerialNumber, int& inWorkersCount, std::vector<std::string>& inWorkersNames)
            : serial_number(inSerialNumber), countFreeWorkers(inWorkersCount), names(inWorkersNames) {}
    static void fillManagersName(int count, std::vector<std::string> vec) {
        for (int  i = 0; i < count; ++i) {
            std::cout << "Enter manager name per " << i + 1 << " command: ";
            std::string manager_name;
            std::cin >> manager_name;
            vec.push_back(manager_name);
        }
    }
    static void fillWorkersName(std::vector<std::string> vec, int count) {
        for (int j = 0; j < count; ++j) {
            std::cout << "Enter the name of " << j + 1 << " worker: ";
            std::string worker_name;
            std::cin >> worker_name;
            vec.push_back(worker_name);
        }
    }
    int getTotalNumberTask() const {
        return totalNumberTask;
    }
    void setTotalNumberTask(CEO* director) {
        std::srand(serial_number + director->getMainTask());
        totalNumberTask = 1 + std::rand() % countFreeWorkers;
    }
    int getFreeWorkers() const {
        return countFreeWorkers;
    }
    void setFreeWorkers(int inFreeWorkers) {
        countFreeWorkers = inFreeWorkers;
        if (countFreeWorkers < 0)  countFreeWorkers = 0;
    }
    std::vector<char> getVectorTask() {
        return task;
    }
    void setVectorTask (char a) {
        task.push_back(a);
    }
};

int main() {
    CEO director;

    std::cout << "Hello, Boss, Say me your name, please: " << std::endl;
    std::string bossName;
    std::cin >> bossName;
    director.setLeadName(bossName);

    std::vector<Manager> vec_teams;

    int count_teams;
    std::cout << "Enter the number of teams: " <<std:: endl;
    std::cin >> count_teams;

    std::vector<std::string> manager_names_vec;

    // initialization of manager names per command
    auto manager = new Manager();
    Manager::fillManagersName(count_teams, manager_names_vec);
    delete manager;

    int totalWorkers = 0;
    std::vector<std::string> worker_names_vec;
    for (int i = 0; i < count_teams; ++i) {
        std::cout << "Enter the count of people for " << i + 1 << " team: ";
        int count_workers;
        std::cin >> count_workers;
        totalWorkers += count_workers;
        Manager new_team(i, count_workers, worker_names_vec);
        Manager::fillWorkersName(worker_names_vec, count_workers);
        vec_teams.push_back(new_team);
    }
    while (totalWorkers != 0) {

        std::cout << "Alright, " << director.getLeadName() << ", enter your num: " << std::endl;
        int num;
        std::cin >> num;

        director.setMainTask(num);

        for (int i = 0; i < vec_teams.size(); i++) {
            if (vec_teams[i].getFreeWorkers() == 0) {
                std::cout << "In " << i + 1 << " group all the workers are busy" << std::endl;
                continue;
            }
            vec_teams[i].setTotalNumberTask(&director);
            for (int j = 0; j < vec_teams[i].getTotalNumberTask(); j++) {
                int random = 1 + std::rand() % 3;
                switch (random) {
                    case 1:
                        vec_teams[i].setVectorTask('A');
                        break;
                    case 2:
                        vec_teams[i].setVectorTask('B');
                        break;
                    case 3:
                        vec_teams[i].setVectorTask('C');
                        break;
                }
            }
            totalWorkers -= vec_teams[i].getTotalNumberTask();
            std::cout << "In team " << i + 1 << " has " << vec_teams[i].getTotalNumberTask()
                      << " employees out of "<< vec_teams[i].getFreeWorkers() << std::endl << "Task: ";
            for (int k = 0; k < vec_teams[i].getVectorTask().size(); k++) {
                std::cout << vec_teams[i].getVectorTask()[k] << " ";
            }
            std::cout << std::endl;
            vec_teams[i].setFreeWorkers(vec_teams[i].getFreeWorkers()
                                        - vec_teams[i].getTotalNumberTask());
        }
    }
    std::cout << "All the workers are busy!" << std::endl;
    return 0;
  }
