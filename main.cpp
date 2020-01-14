#include <iostream>
using namespace std;

struct node{
        int data;
        node* left;
        node* right;
        int height;    
};

////Create a class AVL as ADT
class AVLTree{
    private:
        node* root;
    public:
        AVLTree(){ root = 0; }
        void setRoot(node* t);
        node* getRoot();
        void makeEmpty(node* t);
        node* insert(int x, node* t);
        node* singleRightRotate(node* &t);
        node* singleLeftRotate(node* &t);
        node* doubleLeftRotate(node* &t);
        node* doubleRightRotate(node* &t);
        node* findMin(node* t);
        node* findMax(node* t);
        node* remove(int x, node* t);
        int height(node* t);
        int getBalance(node* t);
        void inorder(node* t);
        void display(node *t, int level);
};

void AVLTree::setRoot(node* t){
    root = t;
}

node* AVLTree::getRoot(){
    return root;
}

void AVLTree::makeEmpty(node* t){
    if(t == 0)
        return;
    else{
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
}

node* AVLTree::insert(int x, node* t){
    if(t == 0){
        t = new node;
        t->data = x;
        t->left = t->right = 0;
        return t;
    }
    else if(x < t->data)
        t->left = insert(x, t->left);
    else if(x > t->data)
        t->right = insert(x, t->right);
    
    height(t);
    if(getBalance(t) == 2 && getBalance(t->left) == 1)
        return singleRightRotate(t);
    else if(getBalance(t) == -2 && getBalance(t->right) == -1)
        return singleLeftRotate(t);
    else if(getBalance(t) == -2 && getBalance(t->right) == 1)
        return doubleLeftRotate(t);
    else if(getBalance(t) == 2 && getBalance(t->right) == -1)
        return singleRightRotate(t);
    
    return t;
}

node* AVLTree::singleRightRotate(node* &t){
    node* tl = t->left;
    t->left = tl->right;
    tl->right = t;

    height(t);
    height(tl);
    if(t == root)
        root = tl;
    return tl;
}

// rotate and fix the height 
node* AVLTree::singleLeftRotate(node* &t){
    node* tr = t->right;
    t->right = tr->left;
    tr->left = t;

    height(t);
    height(tr);
    if(t == root)
        root = tr;
    return tr;
}

node* AVLTree::doubleLeftRotate(node* &t){
    node* tr = t->right;
    node* trl = t->right->left;
    t->right = trl->left;
    tr->left = trl->right;
    trl->left = t;
    trl->right = tr;

    height(t);
    height(tr);
    height(trl);
    if(t == root)
        root = trl;
    return trl;
}

node* AVLTree::doubleRightRotate(node* &t){
    node* tl = t->left;
    node* tlr = t->left->right;
    tl->right = tlr->left;
    t->left = tlr->right;
    tlr->left = tl;
    tlr->right = t;

    height(t);
    height(tl);
    height(tlr);
    if(t == root)
        root = tlr;
    return tlr;
}

node* AVLTree::findMin(node* t){
    if(t->left == 0)
        return t;
    else
        return findMin(t->left);
} 

node* AVLTree::findMax(node* t){
    if(t->right == 0)
        return t;
    else
        return findMax(t->right);
}

node* AVLTree::remove(int x, node* t){
    if(t == 0)
        return t;
    if(x < t->data)
        t->left = remove(x, t->left);
    else if(x > t->data)
        t->right = remove(x, t->right);
    else{  
        if((t->left == 0 && t->right == 0)){
            delete t;
            t = 0;
        }
        else if((t->left != 0 && t->right == 0) || (t->right != 0 && t->left == 0)){
            node* temp;
            if(t->left != 0)
                temp = t->left;
            else
                temp = t->right;
            *t = *temp;
            delete temp;
        }
        else{
            node* temp = findMin(t->right);
            t->data = temp->data;
            t->right = remove(temp->data, t->right);
        }
    }
    if(t == 0)
        return t;
    height(t);
    if(getBalance(t)==2 && getBalance(t->left)>=0)
        return singleRightRotate(t);
    else if(getBalance(t)==2 && getBalance(t->left)==-1)
        return doubleRightRotate(t);
    else if(getBalance(t)==-2 && getBalance(t->right)<=0)
        return singleLeftRotate(t);
    else if(getBalance(t)==-2 && getBalance(t->right)==1)
        return doubleLeftRotate(t);
    
    return t;
}

int AVLTree::height(node* t){
    int h = 0, lh = 0, rh = 0;
    if(t != 0){
        if(t->left != 0)
            lh = height(t->left) + 1;
        else if(t->right != 0)
            rh = height(t->right) + 1;

        if(lh == rh || lh > rh){
            h = lh;
            return h;
        }
        else if(lh < rh){
            h = rh;
            return h;
        }
    }
    return h;
}

int AVLTree::getBalance(node* t){
    if(t == 0)
        return 0;
    else
        return height(t->left) - height(t->right);
}

void AVLTree::inorder(node* t){
    if(t){
        inorder(t->left);
        cout << t->data << " ";
        inorder(t->right);
    }
}

void AVLTree::display(node *t, int level){
    int i;
    if (t != 0){
        display(t->right, level + 1);
        cout << "\n";
        if (t == root)
            cout << "Root -> ";
        for (int i = 0; i < level && t != root; i++)
            cout << "       ";
        cout << t->data;
        display(t->left, level + 1);
    }
}

int main()
{
    AVLTree t;
	t.setRoot(t.insert(20, t.getRoot()));
	t.insert(25, t.getRoot());
	t.insert(15, t.getRoot());
	t.insert(10, t.getRoot());
	t.insert(30, t.getRoot());
	t.insert(5, t.getRoot());
	t.insert(35, t.getRoot());
	t.insert(67, t.getRoot());
	t.insert(43, t.getRoot());
    t.insert(21, t.getRoot());
    t.insert(89, t.getRoot());
    t.insert(38, t.getRoot());
    t.insert(69, t.getRoot());

    t.inorder(t.getRoot());
    cout << "\n\n";

    t.display(t.getRoot(),0);
    cout << "\n\n";

    t.remove(5, t.getRoot());
    t.remove(35, t.getRoot());
    t.remove(65, t.getRoot());
    t.remove(89, t.getRoot());
    t.remove(43, t.getRoot());
    t.remove(88, t.getRoot());
    t.remove(20, t.getRoot());
    t.remove(38, t.getRoot());

    t.inorder(t.getRoot());

    //t.display(t.getRoot(),0);
}