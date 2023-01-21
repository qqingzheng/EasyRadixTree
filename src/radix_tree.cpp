#include "radix_tree.h"


RadixTree::RadixTree(){
    // view();
}


void RadixTree::insert(const string&& key, const string&& value){
    int key_ptr = 0;
    Node* current = &root;
    while(current){
        int child_idx;
        if((child_idx = findroute(current, key, key_ptr)) != -1){
            // Found a child whose first character match to the target. 
            // And `child_idx` is the ID of the matched child.
            const string& label = current->children[child_idx]->label;  // label of the matched child
            int num_match = 0;
            for(int i = 0; i < label.size(); ++ i)
                if(key[key_ptr] == label[i]){
                    ++ key_ptr;
                    ++ num_match;
                }
            if(num_match != label.size()) // if pass this node
                splitnode(current, child_idx, num_match);
            current = current->children[child_idx];
        }else{
            if(current->children.size() == 0){ // no children
                current->has_value = false;
                addnode(current, "", current->content);
                current->content = "";
            }
            addnode(current, key.substr(key_ptr, key.size() - key_ptr), value);
            break;
        }
    }
}


string RadixTree::get(const string&& key){
    Node* current = &root;
    int match_ptr = 0;
    while(current->children.size()){
        current = childrenwalk(current, key, match_ptr);
        // cout << current->label << endl;
        if(current == nullptr)
            return "";
    }
    if(current->has_value)
        return current->content;
    return "";
}


Node* RadixTree::childrenwalk(const Node* current, const string& key, int& target){
    for(auto child : current->children){
        if(child->label == "" && key.size() == target){
            return child;
        }
        for(int i = 0; i < child->label.size(); ++ i){   
            if(child->label[i] != key[target]) break;
            ++target;
            if(i == child->label.size() - 1){
                return child;
            }
            
        }
    }
    return nullptr;
}


void RadixTree::splitnode(Node* parent, int& target, int& split_size){
    Node* upper_node = new Node;
    upper_node->label = parent->children[target]->label.substr(0, split_size);
    upper_node->has_value = false;
    Node* lower_node = new Node;
    lower_node->has_value = true;
    lower_node->label = parent->children[target]->label.substr(split_size, parent->children[target]->label.size());
    
    upper_node->children.push_back(lower_node);
    lower_node->children = std::move(parent->children[target]->children);
    lower_node->content = std::move(parent->children[target]->content);

    delete parent->children[target];
    parent->children[target] = upper_node;

}


void RadixTree::_view(const Node& node, int depth){
    for(int i = depth; i != 0; --i){
        cout << ("  ");
    }
    cout << "➡️ " << node.label << "  " << node.content << endl;
    for(auto child : node.children){
        _view(*child, depth + 1);
    }
}

void RadixTree::view(){
    for(auto child : root.children){
        _view(*child, 1);
    }
}

inline bool RadixTree::checknode(const Node* node, const string& key, int start, int end){
    if(key.substr(start, end) == node->label)
        return true;
    return false;
}

inline int RadixTree::findroute(const Node* node, const string& key, int target){
    for(int i = 0; i < node->children.size(); ++ i){
        if(key[target] == node->children[i]->label[0])
            return i;
    }
    return -1;
}

inline void RadixTree::addnode(Node* parent, const string& key, const string& value){
    Node* node = new Node;
    node->has_value = true;
    node->label = key;
    node->content = value;
    parent->children.push_back(node);
}

