#include <iostream>

struct ListNode {
  int val;
  ListNode* next;

  ListNode(int v) : val(v), next(nullptr) {};
  ListNode(int v, ListNode* n) : val(v), next(n) {};
};

class LinkedList {
  private:
    ListNode* head;
    int length;

  public:
    LinkedList() : head(nullptr), length(0) {};
    ~LinkedList() { deleteList(head ); };
    int getLength() {
      return length;
    }
    void print() {
      if (length < 1) return;
      ListNode* cur = head;
      std::cout << cur->val;
      cur = cur->next;
      while(cur) {
        std::cout << " " << cur->val;
        cur = cur->next;
      }
      std::cout << std::endl;
    }
    bool search(int key) {
      ListNode* cur = head;
      while (cur) {
        if (key == cur->val) return true;
        cur = cur->next;
      }
      return false;
    }
    void insert(int key) {
      head = new ListNode(key, head);
      length++;
    }
    bool insertAt(int key, int index) {
      if (index == 0) {
        head = new ListNode(key, head);
        length++;
        return true;
      }
      if (index > length || index < 0) return false;
      ListNode* cur = head;
      while (--index > 1) {
        cur = cur->next;
      }
      cur->next = new ListNode(key, cur->next);
      length++;
      return true;
    }
    bool deleteKey(int key) {
      if (length == 0) return false;
      if (head->val == key) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
        length--;
        return true;
      }
      ListNode* cur = head;
      ListNode* dummy;
      while (cur) {
        if (cur->val == key) {
          dummy->next = cur->next;
          delete cur;
          length--;
          return true;
        }
        dummy = cur;
        cur = cur->next;
      }
      return false;
    }
    bool deleteAt(int index) {
      if (length == 0 || index > length || index < 0) return false;
      if (index == 0) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
        length--;
        return true;
      }
      ListNode* cur = head;
      ListNode* dummy;
      while (index--) {
        dummy = cur;
        cur = cur->next;
      }
      dummy->next = cur->next;
      delete cur;
      length--;
      return true;
    }
    void deleteList(ListNode* cur) {
      if (!cur) return;
      deleteList(cur->next);
      delete cur;
    }
    ListNode* fromStart(int index) { /* 0 indexed */
      if (index == 0) return head;
      if (index >= length) return nullptr;
      ListNode* cur = head;
      while (index--) {
        cur = cur->next;
      }
      return cur;
    }
    ListNode* fromEnd(int index) {
      ListNode* ahead = fromStart(index);
      if (!ahead) return nullptr;
      ListNode* cur = head;
      while (ahead->next) {
        ahead = ahead->next;
        cur = cur->next;
      }
      return cur;
    }
};