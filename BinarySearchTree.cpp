//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Benjamin Leanna
// Version     : 1.0
// Description : Binary Search Tree
//============================================================================

#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

// Internal structure for tree node
struct Node {
    Bid bid;
    Node *left;
    Node *right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a bid
    Node(Bid aBid) :
            Node() {
        bid = aBid;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);
    void preOrder(Node* node);
    void postOrder(Node* node);
    Node* removeNode(Node* node, string bidId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Bid bid);
    void PostOrder();
    void PreOrder();
    void Remove(string bidId);
    Bid Search(string bidId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    root = nullptr;//root is equal to nullptr
    }

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
    // I looked at geeksforgeeks site on Inorder Tree Traversal without Recursion on using
    // A stack for this but the code itself on that site is wrong (or doesn't work)
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    inOrder(root);// call inOrder fuction and pass root
    }

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    postOrder(root);// postOrder root
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    preOrder(root);// preOrder root
}

/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
    if (root == nullptr) {// if root equarl to null ptr
        root = new Node(bid);// root is equal to new node bid
    }
    else {
        this->addNode(root, bid);// add Node root and bid
    }

}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
    this->removeNode(root, bidId);// remove node root bidID
}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
    Node* cur = root;// set current node equal to root
    while (cur != nullptr) {// keep looping downwards until bottom reached or matching bidId found
        if (cur->bid.bidId.compare(bidId) == 0) {// if match found
            return cur->bid;//return current bid
        }
        else if (bidId.compare(cur->bid.bidId) < 0) {// if bid is smaller than current node
            cur = cur->left;//Traverse left
        }
        else {
            cur = cur->right;//else traverse right
        }
    }
    Bid bid;
    return bid;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {
    if (node != nullptr && node->bid.bidId.compare(bid.bidId)>0) {// if node is larger then add to left
        if (node->left == nullptr) { // if no left node
            node->left = new Node(bid);// this node becomes left
            return;
        }
        else {
            this->addNode(node->left, bid);// else recurse down the left node
        }
    }
    else if (node != nullptr && node->bid.bidId.compare(bid.bidId) < 0) {
        if (node->right == nullptr) { // if no right node
            node->right = new Node(bid); //this node becomes the right
            return;
        }
        else {
            this->addNode(node-> right, bid); //otherwise returse downt he left node
        }
    }
}

//indorder left, cur, right
void BinarySearchTree::inOrder(Node* node) {
    if (node != nullptr) {//if node is not equal to null ptr
        inOrder(node->left);//InOrder the left
        cout << node->bid.bidId << " : " << node->bid.title << " | " << node->bid.amount << " | " << node->bid.fund << endl;//output bidID, title, amount, fund
        inOrder(node->right);//InOder the right
    }
}

//postorder right, cur, left
void BinarySearchTree::postOrder(Node* node) {
    if (node != nullptr) {//if node is not equal to null ptr
        postOrder(node->right);//postOrder the right
        cout << node->bid.bidId << " : " << node->bid.title << " | " << node->bid.amount << " | " << node->bid.fund << endl;//output bidID, title, amount, fund
        postOrder(node->left);//postOrder the left
    }
}

//preorder cur, left, right
void BinarySearchTree::preOrder(Node* node) {
    if (node != nullptr) {//if node is not equal to null ptr
        cout << node->bid.bidId << " : " << node->bid.title << " | " << node->bid.amount << " | " << node->bid.fund << endl;//output bidID, title, amount, fund
        preOrder(node->left);//postOrder the left
        preOrder(node->right);//postOrder the right
    }
}

Node* BinarySearchTree::removeNode(Node* node, string bidId) {
    if (node == nullptr) { //if nothing there, return the node
        return node;
    }
    else if (bidId.compare(node->bid.bidId) < 0) { //else if the node to the left equals the bid
        node->left = removeNode(node->left, bidId); // remove the left node
    }
    else if (bidId.compare(node->bid.bidId) > 0) { // else if the node tot he right equals the bid
        node->right = removeNode(node->right, bidId); // remove the right node
    }
    else {
        if (node->left == nullptr && node->right == nullptr) { // if no children
            delete node; //delete node
            node = nullptr; //node is now null
        }
        else if (node->left != nullptr && node->right == nullptr) { // if only right has children
            Node* tmp = node; // make temp node to hold
            node = node->left; // make the node now the left
            delete tmp; // delete the temp node
            tmp = nullptr; // temp node is now null
        }
        else if (node->right != nullptr && node->left == nullptr) { // if only left has children
            Node* tmp = node; // make temp node to hold
            node = node->right; // make the node now the right
            delete tmp; // delete the temp node
            tmp = nullptr; // temp node is now null
        }
        else { // had children on both sides
            // find the minimum of the right subtree node for bst
            Node* tmp = node->right; // create temp node
            while (tmp->left != nullptr) { //while the left is not null
                tmp = tmp->left; //temp node is now the left side
            }
            node->bid = tmp->bid; // bid is now tmp bid
            node->right = removeNode(node->right, tmp->bid.bidId); //right node is now removed and replaced witht he left tmp node
        }
    }
    return node;
}
//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bst->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98109";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

            //cout << bst->Size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            ticks = clock();

            bid = bst->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
            bst->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

	return 0;
}
