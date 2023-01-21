#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct Node{
    bool has_value;
    string label;
    string content;    // Content of this node
    vector<Node*> children; 
};


class RadixTree{
private:
    struct Node root;                     // which `from` is set to nullptr
    Node* childrenwalk(const Node* current, const string& key, int& target);
    void splitnode(Node* parent, int& target, int& split_size);
    void _view(const Node& node, int depth);
    inline void addnode(Node* node, const string& key, const string& value);
    inline int findroute(const Node* node, const string& key, int target);
    inline bool checknode(const Node* node, const string& key, int start, int end);
public:
    explicit RadixTree();
    RadixTree& operator=(const RadixTree&) = delete;
    void insert(const string&& key, const string&& value);  // use universal reference to ensure that this function can input rvalue
    string get(const string&& key);
    void view();
};