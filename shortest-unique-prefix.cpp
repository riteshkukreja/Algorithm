/* Shortest Unique Prefix
 * Problem URL: https://www.interviewbit.com/problems/shortest-unique-prefix/
 *
 * Find shortest unique prefix to represent each word in the list.
 * Input: [zebra, dog, duck, dove]
 * Output: {z, dog, du, dov}
 * where we can see that
 * zebra = z
 * dog = dog
 * duck = du
 * dove = dov
 */
 
// Prefix Tree Node Element
class Node {
    public:
        string val;
        vector<Node*> child;
    
        // constructor
        Node(string name) {
            val = name;
        }
        
        // Insert a node as child
        void insert(Node* T) {
            child.push_back(T);
        }
        
        // Insert the child to the current node
        // handle the prfix conditions
        void insertChild(string name) {
            for(int i = 0; i < child.size(); i++) {
                int j = 0;
                int len = min((child[i]->val).length(), name.length());
                
                while(j < len && (child[i]->val)[j] == name[j]) j++;
                
                if(j > 0) {
                    // last of previous element
                    string o_suffix = (child[i]->val).substr(j, (child[i]->val).length() - j);
                    
                    // last of new element
                    string n_suffix = name.substr(j, name.length() - j);
                    
                    // common prefix of both element
                    string prefix = name.substr(0, j);
                    
                    //cout << "Collision: " << prefix << " " << o_suffix << " " << n_suffix << "; ";
                    
                    if(o_suffix.length() > 0) {
                        // update prefix
                        child[i]->val = prefix;
                        
                        // copy all the children of this node
                        vector<Node*> copychild = child[i]->child;
                        
                        // clear all the children of this node
                        child[i]->child.clear();
                        
                        // insert suffix as children of this node
                        // this is always unique
                        Node *T = new Node(o_suffix);
                        T->child = copychild;
                        child[i]->insert(T);
                    }
                    
                    // insert the new suffix child    
                    if(n_suffix.length() > 0)
                        child[i]->insertChild(n_suffix);
                    
                    return;
                }
            }
            
            Node *T = new Node(name);
            insert(T);
        }
    
        // boolean result if the node has children
        bool empty() {
            return child.size() == 0;
        }
};

// hashmap to store prefixes for ordered results
unordered_map<string, string> res;

void traverse(Node* T, string ss) {
    if(T == NULL) return;
    
    // Current node has child nodes
    if(!T->empty()) {
        
        // special case if only one child
        if((T->child).size() == 1 && (T->child[0])->empty()) {
            // insert into vector
            string parent = ss + (T->child[0])->val;
            res[parent] = ss;
            return;
        }
        
        // to handle special case of root node
        if(T->val != "*")
            ss += T->val;
        
        // traverse the child nodes
        for(int i = 0; i < (T->child).size(); i++) {
            traverse(T->child[i], ss);
        }
        
    } else {
        string parent = ss + T->val;
        
        // leaf node
        if(T->val != "*")
            ss += T->val[0];
        
        // insert into vector
        res[parent] = ss;
        return;
    }
}

/* 
 * Main method to call the prefix generation
 * @Params A - Vector of strings
 */
vector<string> Solution::prefix(vector<string> &A) {
    // create a empty vector for results
    vector<string> result;
    
    // clear the global hashmap
    res.clear();
    
    // return empty vector in case A is empty
    if(A.size() == 0) return result;
    
    // Generate the prefix tree
    Node* Tree = new Node("*");
    for(int i = 0; i < A.size(); i++) {
        Tree->insertChild(A[i]);
    }
    
    // Traverse the tree to generate hashmap
    // Not needed if the order of prefix isn't important
    traverse(Tree, "");
    
    // generate ordered result from hashmap
    for(int i = 0; i < A.size(); i++) {
        result.push_back(res[A[i]]);
    }
    
    return result;
}

