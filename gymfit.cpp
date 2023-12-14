#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
using namespace std;

class GymPlan {
public:
    string planName;
    int durationInMonths;
    double cost;

    GymPlan(string name, int duration, double cost)
        : planName(name), durationInMonths(duration), cost(cost) {}
};

class Member {
public:
    int memberId;
    string memberName;
    GymPlan memberPlan;

    Member(int id, string name, GymPlan plan)
        : memberId(id), memberName(name), memberPlan(plan) {}
};

class GymManager {
private:
    vector<Member> members;
    vector<GymPlan> availablePlans;
    bool isAdminLoggedIn;

public:
    GymManager() : isAdminLoggedIn(false) {
        // Pre-defined gym plans
        availablePlans.push_back(GymPlan("Basic", 6, 50.0));
        availablePlans.push_back(GymPlan("Standard", 12, 80.0));
        availablePlans.push_back(GymPlan("Premium", 24, 120.0));
    }

    void displayMenu() {
        cout << "\nGym Management Menu:\n";
        cout << "1. Login as Admin\n";
        cout << "2. View Plans\n";
        cout << "3. Exit\n";
        if (isAdminLoggedIn) {
            cout << "4. Add Member\n";
            cout << "5. Remove Member\n";
            cout << "6. Display Members\n";
        }
        cout << "Enter your choice: ";
    }

    bool adminLogin() {
        string password;
        cout << "Enter Admin Password: ";
        cin >> password;
        // You can replace this basic check with a more secure authentication mechanism.
        return (password == "admin123");
    }

    void addMember() {
        if (!isAdminLoggedIn) {
            cout << "Admin login required to add a member.\n";
            return;
        }

        int memberId;
        string memberName;
        int planChoice;

        cout << "Enter Member ID: ";
        cin >> memberId;
        cout << "Enter Member Name: ";
        cin.ignore(); // Ignore newline character in the buffer
        getline(cin, memberName);

        cout << "Choose Gym Plan:\n";
        displayPlans();

        cout << "Enter Plan Choice (1-" << availablePlans.size() << "): ";
        cin >> planChoice;

        if (planChoice >= 1 && planChoice <= availablePlans.size()) {
            GymPlan selectedPlan = availablePlans[planChoice - 1];
            Member member(memberId, memberName, selectedPlan);
            members.push_back(member);

            cout << "Member added successfully!\n";
        } else {
            cout << "Invalid plan choice. Member not added.\n";
        }
    }

    void removeMember() {
        if (!isAdminLoggedIn) {
            cout << "Admin login required to remove a member.\n";
            return;
        }

        int memberId;
        cout << "Enter Member ID to remove: ";
        cin >> memberId;

        auto it = find_if(members.begin(), members.end(), [memberId](const Member& member) {
            return member.memberId == memberId;
        });

        if (it != members.end()) {
            members.erase(it);
            cout << "Member removed successfully!\n";
        } else {
            cout << "Member not found.\n";
        }
    }

    void displayMembers() {
        if (!isAdminLoggedIn) {
            cout << "Admin login required to view members.\n";
            return;
        }

        cout << "\nMembers:\n";
        for (const auto& member : members) {
            cout << "ID: " << member.memberId << ", Name: " << member.memberName
                 << ", Plan: " << member.memberPlan.planName << ", Duration: " << member.memberPlan.durationInMonths
                 << " months, Cost: $" << member.memberPlan.cost << endl;
        }
    }

    void displayPlans() {
        cout << "\nAvailable Gym Plans:\n";
        for (size_t i = 0; i < availablePlans.size(); ++i) {
            cout << i + 1 << ". Plan: " << availablePlans[i].planName << ", Duration: " << availablePlans[i].durationInMonths
                 << " months, Cost: $" << availablePlans[i].cost << endl;
        }
    }

    void run() {
        int choice;

        do {
            displayMenu();
            cin >> choice;

            switch (choice) {
                case 1:
                    isAdminLoggedIn = adminLogin();
                    if (isAdminLoggedIn) {
                        cout << "Admin login successful!\n";
                    } else {
                        cout << "Admin login failed.\n";
                    }
                    break;
                case 2:
                    displayPlans();
                    break;
                case 3:
                    cout << "Exiting Gym Management. Goodbye!\n";
                    break;
                case 4:
                    addMember();
                    break;
                case 5:
                    removeMember();
                    break;
                case 6:
                    displayMembers();
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 3);
    }
};

int main() {
    GymManager gymManager;
    gymManager.run();

    return 0;
}
