typedef int RANK;

template<typename T> struct ListNode{
    T data; ListNode<T> *pred, *succ;
    ListNode(){}//针对header和tailer的构造
    ListNode(T const& e, ListNode<T>* pred=NULL, ListNode<T>* succ=NULL)
        :data(e), pred(pred), succ(succ){}
    ListNode<T>* insertAsPred(T const& e){
        ListNode<T>* newNode = ListNode(e, pred, succ);
        pred->succ = newNode;
        pred = newNode;
        return newNode;
    }
}

template<typename T> class List{
private:
    RANK _size; ListNode<T> *header, *tailer;

public:

    RANK find(T e, RANK n, ListNode<T>* p){
        while(p!=header && p->pred->data!=e) p=p->pred;
        return  (p==header)? NULL: p;
    }
}