#include <iostream>
#include <string>
using namespace std;

struct TreeNode {
    string name;
    int studentID;
    string department;
    double GPA;
    TreeNode* left;
    TreeNode* right;
    int height; // For AVL tree

    TreeNode(const string& name, int id, const string& department, double gpa)
        : name(name), studentID(id), department(department), GPA(gpa), left(nullptr), right(nullptr), height(1) {}
};

class StudentInformationSystem {
public:
    // Constructor
    StudentInformationSystem() {
        root = nullptr;
    }

    // Destructor
    ~StudentInformationSystem() {
        destroyTree(root);
    }

    // Function to add a new student record to the system
    void addStudent(const std::string& name, int id, const std::string& department, double gpa) {
        root = insertNode(root, name, id, department, gpa);
    }

    // Function to remove a student record from the system
    void removeStudent(int id) {
        root = removeNode(root, id);
    }

    // Function to search for a student by their ID and retrieve their information
    string searchStudent(int id) {
        TreeNode* FoundNode = searchNode(root, id);
        if (FoundNode != nullptr) {
            return "Name: " + FoundNode->name + "\nStudent ID: " + to_string(FoundNode->studentID) + "\nDepartment: " + FoundNode->department + "\nGPA: " + to_string(FoundNode->GPA) + "\n";
        }
        else {
            return "Student with ID " + std::to_string(id) + " not found.";
        }
    }

    // Function to display all student records in the system
    void displayAllStudents() {
        displayAllStudentsHelper(root);
    }

    // Function to calculate the average GPA of all students in the system
    double calculateAverageGPA() {
        int count = 0;
        double sum = 0.0;
        calculateAverageGPAHelper(root, sum, count);
        if (count == 0) {
            return 0.0;
        }
        return sum / count;
    }

    // Function to update the GPA of a student
    void updateGPA(int id, double newGPA) {
        updateGPAHelper(root, id, newGPA);
    }

private:
    TreeNode* root; // Root node of the AVL tree

    // AVL Tree Insertion with Balancing
    TreeNode* insertNode(TreeNode* node, const std::string& name, int id, const std::string& department, double gpa) {
        if (node == nullptr) {
            return new TreeNode(name, id, department, gpa);
        }

        if (id < node->studentID) {
            node->left = insertNode(node->left, name, id, department, gpa);
        }
        else if (id > node->studentID) {
            node->right = insertNode(node->right, name, id, department, gpa);
        }
        else {
            // Duplicate IDs are not allowed
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        return balanceNode(node);
    }

    // AVL Tree Deletion with Balancing
    TreeNode* removeNode(TreeNode* node, int id) {
        if (node == nullptr) {
            return node;
        }

        if (id < node->studentID) {
            node->left = removeNode(node->left, id);
        }
        else if (id > node->studentID) {
            node->right = removeNode(node->right, id);
        }
        else {
            if ((node->left == nullptr) || (node->right == nullptr)) {
                TreeNode* temp = node->left ? node->left : node->right;

                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                }
                else {
                    *node = *temp;
                }
                delete temp;
            }
            else {
                TreeNode* temp = findMinNode(node->right);
                node->name = temp->name;
                node->studentID = temp->studentID;
                node->department = temp->department;
                node->GPA = temp->GPA;
                node->right = removeNode(node->right, temp->studentID);
            }
        }

        if (node == nullptr) {
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        return balanceNode(node);
    }

    TreeNode* searchNode(TreeNode* node, int id) {
        if (node == nullptr || node->studentID == id) {
            return node;
        }
        else if (id < node->studentID) {
            return searchNode(node->left, id);
        }
        else {
            return searchNode(node->right, id);
        }
    }

    TreeNode* findMinNode(TreeNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    void displayAllStudentsHelper(TreeNode* node) {
        if (node != nullptr) {
            displayAllStudentsHelper(node->left);
            cout << "Name: " << node->name << endl;
            cout << "Student ID: " << node->studentID << endl;
            cout << "Department: " << node->department << endl;
            cout << "GPA: " << node->GPA << endl;
            displayAllStudentsHelper(node->right);
        }
    }

    void calculateAverageGPAHelper(TreeNode* node, double& sum, int& count) {
        if (node == nullptr) {
            return;
        }
        calculateAverageGPAHelper(node->left, sum, count);
        sum += node->GPA;
        count++;
        calculateAverageGPAHelper(node->right, sum, count);
    }

    void updateGPAHelper(TreeNode* node, int id, double newGPA) {
        TreeNode* student = searchNode(node, id);
        if (student != nullptr) {
            student->GPA = newGPA;
        }
    }

    void destroyTree(TreeNode* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    int getHeight(TreeNode* node) {
        return node ? node->height : 0;
    }

    int getBalanceFactor(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    TreeNode* rotateRight(TreeNode* y) {
        TreeNode* x = y->left;
        TreeNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    TreeNode* rotateLeft(TreeNode* x) {
        TreeNode* y = x->right;
        TreeNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    TreeNode* balanceNode(TreeNode* node) {
        int balance = getBalanceFactor(node);

        // Left Left Case
        if (balance > 1 && getBalanceFactor(node->left) >= 0) {
            return rotateRight(node);
        }

        // Left Right Case
        if (balance > 1 && getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Right Case
        if (balance < -1 && getBalanceFactor(node->right) <= 0) {
            return rotateLeft(node);
        }

        // Right Left Case
        if (balance < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }
};

int main() {
    StudentInformationSystem system;

    system.addStudent("Alice", 101, "CS", 3.8);
    system.addStudent("Bob", 102, "Math", 3.5);
    system.addStudent("Sam", 123, "Biology", 3.7);
    system.addStudent("Jacob", 455, "Physics", 3.8);
    system.addStudent("Kwame", 200, "CS", 3.4);

    system.displayAllStudents();

    cout << "Average GPA: " << system.calculateAverageGPA() << endl;

    system.removeStudent(101);

    cout << system.searchStudent(102) << endl;

    system.updateGPA(102, 3.9);
    cout << system.searchStudent(102) << endl;

    return 0;
}
