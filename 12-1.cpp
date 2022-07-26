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
    }
    /*
     Add a child to this node.
    */
    void addChild(T d)
    {
        child->addFromTail(new TreeNode<T>(d));
    }
    /*
     Return the nth child of the node.
    */
    TreeNode<T> *operator[](int n)
    {
        return (*child)[n].getData();
    }

private:
    LinkList<TreeNode<T> *> *child;
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
            while (1) //放child
            {
                try
                {
                    q->addFromHead((*temp)[k]); // push    (temp is TreeNode)
                }
                catch (std::invalid_argument e) // temp跑到尾
                {
                    break;
                }
                k++;
            }
            temp = q->removeFromTail()->getData(); //拿掉 pop (最後一個)
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
            while (1) // 放child
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
            t = q->removeFromTail();
            if (t == NULL)
                break;
            else
                temp = t->getData();
        }
    }
    /*
     print all the node on this tree with preorder. 父 -> 子
    */
    void preorder() 
    {
        _pre(root);
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
    void _pre(TreeNode<T> *n) //父 -> 子
    {
        if (!n)
            return;
        std::cout << n << " ";
        int k = 0;
        while (1) //放child
        {
            try
            {
                _pre((*n)[k]);
            }
            catch (std::invalid_argument e)
            {
                break;
            }
            k++;
        }
    }
    void _post(TreeNode<T> *n) //子 -> 父
    {
        if (!n)
            return;
        int k = 0;
        while (1) //放child
        {
            try
            {
                _post((*n)[k]);
            }
            catch (std::invalid_argument e)
            {
                break;
            }
            k++;
        }
        std::cout << n << " ";
    }
};

int main()
{
    Tree<int> *tree = new Tree<int>();
    srand(10);
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
    std::cout << tree->count() << std::endl;

    tree->levelOrder();
    std::cout << std::endl;

    tree->preorder();
    std::cout << std::endl;

    tree->postorder();
}