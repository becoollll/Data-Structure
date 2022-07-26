#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <ctime>

template <class T>
class Node
{
public:
    Node()
    {
        data = new T;
    }
    Node(T d)
    {
        data = new T;
        (*data) = d;
    }
    Node &operator=(T d)
    {
        (*data) = d;
        return *this;
    }
    friend std::ostream &operator<<(std::ostream &out, Node n)
    {
        out << *(n.data);
        return out;
    }
    friend std::ostream &operator<<(std::ostream &out, Node *n)
    {
        out << *(n->data);
        return out;
    }
    void setData(T d)
    {
        *data = d;
    }
    T &getData() const
    {
        return *data;
    }

protected:
    T *data;
};

template <class T>
class ListNode : public Node<T>
{
public:
    ListNode() : Node<T>()
    {
        prev = NULL;
        next = NULL;
    }
    ListNode(T d) : Node<T>(d)
    {
        prev = NULL;
        next = NULL;
    }
    ListNode(ListNode *p, ListNode *n) : Node<T>()
    {
        prev = p;
        next = n;
    }
    ListNode(T d, ListNode *p, ListNode *n) : Node<T>(d)
    {
        prev = p;
        next = n;
    }
    ListNode *getNext() const
    {
        return next;
    }
    ListNode *getPrev() const
    {
        return prev;
    }
    void setNext(ListNode *n)
    {
        next = n;
    }
    void setPrev(ListNode *p)
    {
        prev = p;
    }
    ListNode &operator=(T d)
    {
        this->setData(d);
        return *this;
    }

private:
    ListNode *prev, *next;
};

template <class T>
class LinkList
{
public:
    LinkList()
    {
        head = NULL;
        tail = NULL;
    }
    void addFromHead(T d)
    {
        ListNode<T> *node = new ListNode<T>(d);
        if (head != NULL)
        {
            head->setPrev(node);
        }
        node->setNext(head);
        head = node;
        if (tail == NULL)
            tail = node;
    }
    void addFromTail(T d)
    {
        ListNode<T> *node = new ListNode<T>(d);
        if (tail != NULL)
        {
            tail->setNext(node);
        }
        node->setPrev(tail);
        tail = node;
        if (head == NULL)
            head = node;
    }
    void addAfter(ListNode<T> *at, T d)
    {
        if (!exist(at))
            return;
        ListNode<T> *node = new ListNode<T>(d);
        if (at->getNext() != NULL)
            at->getNext()->setPrev(node);
        node->setNext(at->getNext());
        at->setNext(node);
        node->setPrev(at);
        if (node->getNext() == NULL)
            tail = node;
    }
    ListNode<T> *removeFromHead()
    {
        ListNode<T> *n = head;
        if (head != NULL)
        {
            head = head->getNext();
            if (head != NULL)
                head->setPrev(NULL);
            else
                tail = NULL;
            n->setNext(NULL);
        }
        return n;
    }
    ListNode<T> *removeFromTail()
    {
        ListNode<T> *n = tail;
        if (tail != NULL)
        {
            tail = tail->getPrev();
            if (tail != NULL)
                tail->setNext(NULL);
            else
                head = NULL;
            n->setPrev(NULL);
        }
        return n;
    }
    ListNode<T> *remove(ListNode<T> *n)
    {
        if (!exist(n))
            return NULL;
        if (n == head)
            return removeFromHead();
        if (n == tail)
            return removeFromTail();
        n->getPrev()->setNext(n->getNext());
        n->getNext()->setPrev(n->getPrev());
        n->setNext(NULL);
        n->setPrev(NULL);
        return n;
    }
    ListNode<T> *exist(T d)
    {
        ListNode<T> *j = head;
        while (j != NULL)
        {
            if (j->getData() == d)
                return j;
            j = j->getNext();
        }
        return NULL;
    }
    bool exist(ListNode<T> *n)
    {
        ListNode<T> *j = head;
        while (j != NULL)
        {
            if (j == n)
                return true;
            j = j->getNext();
        }
        return false;
    }
    ListNode<T> &operator[](int i)
    {
        ListNode<T> *j = head;
        int k;
        for (k = 0; k < i && j != NULL; k++)
            j = j->getNext();
        if (j == NULL)
            throw std::invalid_argument("index does not exist.");
        return *j;
    }
    void print() const
    {
        ListNode<T> *j;
        j = head;
        while (j != NULL)
        {
            std::cout << (*j) << " ";
            j = j->getNext();
        }
        std::cout << std::endl;
    }

protected:
    ListNode<T> *head, *tail;
};

/*
    Please finish the TreeNode class, TreeNode class respresent a node in a general tree.
    A general tree is different from binary tree, every node in binary tree have at most two child node, but a node in general tree may have more than two child node.
*/
template <class T>
class TreeNode : public Node<T>
{
public:
    TreeNode() : Node<T>()
    {
        child = new LinkList<TreeNode<T> *>();
    }
    TreeNode(T d) : Node<T>(d)
    {
        child = new LinkList<TreeNode<T> *>();
    }
    /*
     Add a child to this node.
    */
    void addChild(TreeNode *n)
    {
        child->addFromTail(n);
        child_count += n->getchild_count();
    }
    /*
     Add a child to this node.
    */
    void addChild(T d)
    {
        child->addFromTail(new TreeNode<T>(d));
        child_count++;
    }
    /*
     Return the nth child of the node.
    */
    TreeNode<T> *operator[](int n)
    {
        return (*child)[n].getData();
    }
    int getchild_count()
    {
        return child_count;
    }

private:
    LinkList<TreeNode<T> *> *child;
    int child_count = 0;
};

/*
 Please finish the Tree class. Tree class respresent a general tree, that means node on this tree may have more than two child node.

*/
template <class T>
class Tree
{
public:
    Tree()
    {
        root = NULL;
    }
    /*
     return the nth node on this tree with level order.
    */
    TreeNode<T> *operator[](int n)
    {
        int j, k;
        if (root == NULL)
            return NULL;
        LinkList<TreeNode<T> *> *q = new LinkList<TreeNode<T> *>();
        q->addFromHead(root);
        TreeNode<T> *temp = q->removeFromTail()->getData(); //拿掉root
        for (j = 0; j < n; j++)
        {
            k = 0;
            while (1) //放小孩
            {
                try
                {
                    q->addFromHead((*temp)[k]); // push
                }
                catch (std::invalid_argument e)
                {
                    break;
                }
                k++;
            }
            temp = q->removeFromTail()->getData(); //拿掉 pop
        }
        return temp;
    }
    /*
     return the number of nodes on this tree.
    */
    int count()
    {
        return _count(root);
    }
    /*
     print all the node on this tree with level order.
    */
    void levelOrder()
    {
        int j, k;
        if (root == NULL)
            return;
        ListNode<TreeNode<T> *> *t;
        LinkList<TreeNode<T> *> *q = new LinkList<TreeNode<T> *>();
        q->addFromHead(root);
        TreeNode<T> *temp = q->removeFromTail()->getData();
        for (j = 0;; j++)
        {
            std::cout << temp << " ";
            k = 0;
            while (k < temp->getchild_count()) //放小孩
            {
                q->addFromHead((*temp)[k]);

                k++;
            }
            t = q->removeFromTail();
            if (t == NULL)
                break;
            else
                temp = t->getData();
        }
    }
    /*
     print all the node on this tree with preorder.父 -> 子
    */
    void preorder()
    {
        int j, k;
        if (root == NULL)
            return;
        ListNode<TreeNode<T> *> *t;
        LinkList<TreeNode<T> *> *q = new LinkList<TreeNode<T> *>();
        q->addFromTail(root);
        TreeNode<T> *temp = q->removeFromTail()->getData();
        for (j = 0;; j++)
        {
            std::cout << temp << " ";
            k = temp->getchild_count(); //先放最右邊的
            while (k > 0)
            {
                k--;
                q->addFromTail((*temp)[k]);
            }
            t = q->removeFromTail();
            if (t == NULL)
                break;
            else
                temp = t->getData();
        }
    }
    /*
     print all the node on this tree with postorder. 子 ->父
    */
    void postorder()
    {
        _post(root);
    }
    /*
     set the root of this tree.
    */
    void setRoot(T d)
    {
        root = new TreeNode<T>(d);
    }

private:
    TreeNode<T> *root;
    int _count(TreeNode<T> *r)
    {
        int n = 0;
        int j = 0;
        if (r == NULL)
            return 0;
        while (1)
        {
            try
            {
                n += _count((*r)[j]);
            }
            catch (std::invalid_argument e)
            {
                break;
            }
            j++;
        }
        return n + 1;
    }
    void _post(TreeNode<T> *n) //子 ->父
    {
        if (!n)
            return;
        int k = 0;
        while (k < n->getchild_count())
        {
            _post((*n)[k]);
            k++;
        }
        std::cout << n << " ";
    }
};

template <class T>
class BinaryTreeNode : public Node<T>
{
public:
    BinaryTreeNode() : Node<T>()
    {
        left = NULL;
        right = NULL;
    }
    BinaryTreeNode(T d) : Node<T>(d)
    {
        left = NULL;
        right = NULL;
    }
    BinaryTreeNode(BinaryTreeNode<T> *l, BinaryTreeNode<T> *r) : Node<T>()
    {
        left = l;
        right = r;
    }
    BinaryTreeNode(T d, BinaryTreeNode<T> *l, BinaryTreeNode<T> *r) : Node<T>(d)
    {
        left = l;
        right = r;
    }
    void setLeft(BinaryTreeNode<T> *l)
    {
        left = l;
    }
    void setRight(BinaryTreeNode<T> *r)
    {
        right = r;
    }
    BinaryTreeNode<T> *&getLeft()
    {
        return left;
    }
    BinaryTreeNode<T> *&getRight()
    {
        return right;
    }
    bool operator>(BinaryTreeNode<T> n)
    {
        if (*(this->data) > *(n.data))
            return true;
        return false;
    }
    bool operator==(BinaryTreeNode<T> n)
    {
        if (*(this->data) == *(n.data))
            return true;
        return false;
    }

private:
    BinaryTreeNode<T> *left, *right;
};

template <class T>
class BinaryTree
{
public:
    BinaryTree()
    {
        root = NULL;
        count = 0;
    }
    /*
     Convert a general tree to sibling tree
    */
    static BinaryTree<T> *convertFromGeneralTree(Tree<T> *tree)
    {
        int k;
        BinaryTree<T> *btree = new BinaryTree();
        btree->insert((*tree)[0]->getData()); //把root加進去

        LinkList<TreeNode<T> *> *q = new LinkList<TreeNode<T> *>();              //作用queue
        LinkList<BinaryTreeNode<T> *> *bq = new LinkList<BinaryTreeNode<T> *>(); //作用queue
        ListNode<TreeNode<T> *> *t;
        ListNode<BinaryTreeNode<T> *> *bt;

        TreeNode<T> *temp = (*tree)[0]; // (*tree)[0] 就是 tree 的 root
        BinaryTreeNode<T> *btemp = btree->root;
        for (int j = 0;; j++)
        {
            k = 0;
            while (1) //放小孩
            {
                try
                {
                    if (k) //其他小孩放第一個小孩的右邊
                    {
                        btemp->setRight(new BinaryTreeNode<T>((*temp)[k]->getData()));
                        btemp = btemp->getRight();
                    }
                    else //第一個小孩放左邊
                    {
                        btemp->setLeft(new BinaryTreeNode<T>((*temp)[k]->getData()));
                        btemp = btemp->getLeft();
                    }
                    q->addFromTail((*temp)[k]); // push
                    bq->addFromTail(btemp);
                }
                catch (std::invalid_argument e)
                {
                    break;
                }
                k++;
            }
            t = q->removeFromHead(); // pop
            bt = bq->removeFromHead();
            if (t == NULL && bt == NULL)
                break;
            else
            {
                temp = t->getData();
                btemp = bt->getData();
            }
        }
        return btree;
    }
    virtual BinaryTreeNode<T> *insert(T d)
    {
        BinaryTreeNode<T> *node = new BinaryTreeNode<T>(d);
        if (root == NULL)
        {
            root = node;
        }
        else
        {
            int j = count + 1;
            int k = 1;
            BinaryTreeNode<T> *cur = root;
            while (k <= j)
                k = k << 1;
            k = k >> 2;
            while (k > 1)
            {
                if (k & j)
                    cur = cur->getRight();
                else
                    cur = cur->getLeft();
                k = k >> 1;
            }
            if (k & j)
                cur->setRight(node);
            else
                cur->setLeft(node);
        }
        count++;
    }

    void levelOrder() // use queue
    {
        int j;
        if (root == NULL)
            return;
        ListNode<BinaryTreeNode<T> *> *t;
        LinkList<BinaryTreeNode<T> *> *q = new LinkList<BinaryTreeNode<T> *>();
        q->addFromHead(root);
        BinaryTreeNode<T> *temp = q->removeFromTail()->getData();
        while (1)
        {
            std::cout << temp << " ";

            if (temp->getLeft() != NULL)
            { // 若left有資料,放入queue
                q->addFromHead(temp->getLeft());
            }
            if (temp->getRight() != NULL)
            { // 若right有資料, 放入queue
                q->addFromHead(temp->getRight());
            }

            t = q->removeFromTail();
            if (t == NULL)
                break;
            else
                temp = t->getData();
        }
    }

    BinaryTreeNode<T> *remove(BinaryTreeNode<T> *n)
    {
        if (!exist(n))
            return NULL;
        BinaryTreeNode<T> *last = getLast();
        if (last == root)
        {
            count--;
            root = NULL;
            return n;
        }
        BinaryTreeNode<T> *lastsFather = getFather(last);
        if (lastsFather->getLeft() == last)
            lastsFather->setLeft(NULL);
        else
            lastsFather->setRight(NULL);
        if (last == n)
        {
            count--;
            return n;
        }
        if (n != root)
        {
            BinaryTreeNode<T> *father = getFather(n);
            if (father->getLeft() == n)
                father->setLeft(last);
            else
                father->setRight(last);
        }
        else
        {
            root = last;
        }
        last->setLeft(n->getLeft());
        last->setRight(n->getRight());
        n->setLeft(NULL);
        n->setRight(NULL);
        count--;
        return n;
    }
    BinaryTreeNode<T> *getFather(BinaryTreeNode<T> *n)
    {
        if (n == root || !exist(n))
            return NULL;
        return _getFather(root, n);
    }
    bool exist(BinaryTreeNode<T> *n)
    {
        return _exist(root, n);
    }
    BinaryTreeNode<T> *getRoot()
    {
        return root;
    }
    void print()
    {
        _print(root, 0);
    }
    void swapNode(BinaryTreeNode<T> *node1, BinaryTreeNode<T> *node2)
    {
        if (!exist(node1) || !exist(node2))
            return;
        BinaryTreeNode<T> *father1 = getFather(node1);
        BinaryTreeNode<T> *father2 = getFather(node2);
        if (father1 != NULL)
            if (father1->getLeft() == node1)
                father1->setLeft(node2);
            else
                father1->setRight(node2);
        else
            root = node2;
        if (father2 != NULL)
            if (father2->getLeft() == node2)
                father2->setLeft(node1);
            else
                father2->setRight(node1);
        else
            root = node1;
        BinaryTreeNode<T> *node1L = node1->getLeft();
        BinaryTreeNode<T> *node1R = node1->getRight();
        BinaryTreeNode<T> *node2L = node2->getLeft();
        BinaryTreeNode<T> *node2R = node2->getRight();
        node1->setLeft(node2L);
        node1->setRight(node2R);
        node2->setLeft(node1L);
        node2->setRight(node1R);
    }

protected:
    BinaryTreeNode<T> *root;
    int count;

private:
    BinaryTreeNode<T> *getLast()
    {
        int j = count, k = 1;
        BinaryTreeNode<T> *cur = root;
        while (k <= j)
            k = k << 1;
        k = k >> 2;
        while (k > 0)
        {
            if (k & j)
                cur = cur->getRight();
            else
                cur = cur->getLeft();
            k = k >> 1;
        }
        return cur;
    }
    bool _exist(BinaryTreeNode<T> *r, BinaryTreeNode<T> *n)
    {
        if (n == r)
            return true;
        if (r->getLeft() && _exist(r->getLeft(), n))
            return true;
        if (r->getRight() && _exist(r->getRight(), n))
            return true;
        return false;
    }
    BinaryTreeNode<T> *_getFather(BinaryTreeNode<T> *r, BinaryTreeNode<T> *n)
    {
        if (r == NULL)
            return NULL;
        if (r->getLeft() == n || r->getRight() == n)
            return r;
        BinaryTreeNode<T> *temp;
        temp = _getFather(r->getLeft(), n);
        if (temp != NULL)
            return temp;
        temp = _getFather(r->getRight(), n);
        return temp;
    }
    void _print(BinaryTreeNode<T> *r, int n)
    {
        if (r == NULL)
            return;
        int j;
        _print(r->getRight(), n + 1);
        for (j = 0; j < n; j++)
            std::cout << "    ";
        std::cout << r << std::endl;
        _print(r->getLeft(), n + 1);
    }
};

int main()
{
    Tree<int> *tree = new Tree<int>();
    srand(0);
    int j, k, i;
    for (j = 0; j < 20; j++)
    {
        if (tree->count() == 0)
            tree->setRoot(rand() % 100);
        else
        {
            k = rand() % tree->count();
            (*tree)[k]->addChild(rand() % 100);
        }
    }
    tree->levelOrder();
    std::cout << std::endl;
    tree->preorder();
    std::cout << std::endl;
    tree->postorder();
    std::cout << std::endl;

    BinaryTree<int> *binaryTree = BinaryTree<int>::convertFromGeneralTree(tree);
    binaryTree->print();
}
