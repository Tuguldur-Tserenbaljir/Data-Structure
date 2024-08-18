/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <string.h>
using namespace std;
struct Node {
    char data; // Clubs=C, Diamonds=D, Heart=H, Spade=S
    int points; // points of the card
    Node* leftChild; // left child node
    Node* rightChild; // right child node
    Node(char data) : data(data), leftChild(nullptr), rightChild(nullptr),points(0) {}
};

class Yugi {
public:
    Yugi() : root(new Node('t')), leftChild(nullptr), rightChild(nullptr), points(0) {}
    void summon(char card_v) {
        //cout<<"Error"<<endl;
        if(card_v == 'C'){
            if (root->leftChild == nullptr) {
                root->leftChild = new Node(card_v);
                root->leftChild->points = 1;
                //cout<<"Left child is: "<< root->leftChild->data<<endl;
            } else if (root->rightChild == nullptr){
                root->rightChild = new Node(card_v);
                root->rightChild->points = 1;
                //cout<<"Right child is: "<< root->leftChild->data<<endl;
            }
        }
        
        else if(card_v == 'D'){
            //half full,  right is null
            if(root->leftChild != nullptr && root->rightChild == nullptr){
                Node *new_node = new Node(card_v);
                new_node->points = 3;
                new_node->leftChild = root->leftChild;
                new_node->rightChild = nullptr;
                root->leftChild = new_node;
                
            }//not full , left is null
            else if(root->leftChild == nullptr && root->rightChild != nullptr){
                Node *new_node = new Node(card_v);
                new_node->points = 3;
                new_node->rightChild = root->rightChild;
                new_node->leftChild = nullptr;
                root->rightChild = new_node;
            }
            //full, leftside has more value, sac right
            else if(root->leftChild->points > root->rightChild->points){
                Node *new_node = new Node(card_v);
                new_node->points = 3;
                new_node->rightChild = root->rightChild;
                new_node->leftChild = nullptr;
                root->rightChild = new_node;
            }
            //rightside has more value
            else if(root->leftChild->points < root->rightChild->points){
                Node *new_node = new Node(card_v);
                new_node->points = 3;
                new_node->leftChild = root->leftChild;
                new_node->rightChild = nullptr;
                root->leftChild = new_node;
            }
            //full, equal
            else if(root->leftChild->points == root->rightChild->points){
                Node *new_node = new Node(card_v);
                new_node->points = 3;
                new_node->leftChild = root->leftChild;
                new_node->rightChild = nullptr;
                root->leftChild = new_node;
                //cout<<"Left child is: "<< root->rightChild->data<<endl;
            }
        }
        else if(card_v == 'H'){
            if(root->rightChild != nullptr && root->leftChild != nullptr){
                Node *new_node = new Node(card_v);
                new_node->leftChild = root->leftChild;
                new_node->rightChild = root->rightChild;
                root->leftChild = new_node;
                root->rightChild = nullptr;
                new_node->points = calculate_points(new_node);
            }
        }
    }
    int calculate_points(Node* node) {
        if (node == nullptr) {
                return 0;
            }
        int left_count = 0;
        int right_count = 0;
        int return_count = 0;
        left_count += calculate_points(node->leftChild);
        right_count -= calculate_points(node->rightChild);
        return_count = left_count + right_count + node->points;
        return return_count;
}

void print_result() {
    int total_heart_points = sum_heart_points(root);
    cout <<total_heart_points << endl;
}

int sum_heart_points(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    int points = 0;
    if (node->data == 'H') {
        points += node->points;
    }
    points += sum_heart_points(node->leftChild);
    points += sum_heart_points(node->rightChild);
    return points;
}

private:
    Node* leftChild;
    Node* rightChild;
    Node* root;
    int points;
};



int main()
{
    
    string input;
    Yugi yugi;
    Node test('t');
    
    while (getline(cin, input)) {
        if (input == "Clubs") {
            //cout<<"The card is Clubs"<<endl;
            yugi.summon('C');
        } else if (input == "Diamonds") {
            //cout<<"The card is Diamons"<<endl;
            yugi.summon('D');
        } else if (input == "Heart") {
            //cout<<"The card is Heart"<<endl;
            yugi.summon('H');
        }
        else if (input == "Spade") {
            //cout<<"Ending"<<endl;
            yugi.print_result();
            break;
        }
    }
    return 0;
}