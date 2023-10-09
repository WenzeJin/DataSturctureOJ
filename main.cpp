#include <iostream>
#include <cassert>

using namespace std;

template<typename T>
class Deque {

    struct Node {
        T val;
        Node *prev;
        Node *next;
    };

    Node *head;
    size_t _size;

public:

    Deque() {
        head = new Node();
        head->prev = head;
        head->next = head;
        _size = 0;
    }

    ~Deque() {
        Node *pt = head->next;
        while(pt != head) {
            pt = pt->next;
            delete pt->prev;
        }
        delete pt;
        head = nullptr;
    }

    void push_front(T& v) {
        Node *temp = new Node();
        temp->val = v;
        temp->prev = head;
        temp->next = head->next;
        head->next = temp;
        temp->next->prev = temp;
        _size++;
    }

    void push_back(T& v) {
        Node *temp = new Node();
        temp->val = v;
        temp->next = head;
        temp->prev = head->prev;
        head->prev = temp;
        temp->prev->next = temp;
        _size++;
    }

    T front() {
        assert(_size > 0);
        return head->next->val;
    }

    T back() {
        assert(_size > 0);
        return head->prev->val;
    }

    void pop_front() {
        assert(_size > 0);
        Node *old = head->next;
        head->next = old->next;
        head->next->prev = head;
        delete old;
        _size--;
    }

    void pop_back() {
        assert(_size > 0);
        Node *old = head->prev;
        head->prev = old->prev;
        head->prev->next = head;
        delete old;
        _size--;
    }

    bool empty() {
        return _size == 0;
    }

    size_t size() {
        return _size;
    }
};

int arr[1000000];
long long pre[1000000];
long long k;

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int cnt;
        cin >> cnt >> k;

        for (int i = 1; i <= cnt; i++){
            cin >> arr[i];
        }

        pre[0] = 0;
        for (int i = 1; i <= cnt; i++) {
            pre[i] = arr[i] + pre[i - 1];
        }

        Deque<int> que;
        int res = cnt + 1;

        for (int i = 0; i <= cnt; i++) {
            int currsum = pre[i];
            while(!que.empty() && currsum - pre[que.front()] >= k) {
                res = min(res, i - que.front());
                que.pop_front();
            }
            while(!que.empty() && pre[que.back()] >= currsum) {
                que.pop_back();
            }
            que.push_back(i);
        }

        if (res == cnt + 1)
        {
            res = -1;
        }
        cout << res << endl;
    }
}