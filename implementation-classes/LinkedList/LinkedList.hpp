#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <utility>

// динамический список (обращение к элементу за O(n), нет свободного доступа к элементу)
template <class T>
class LinkedList {
private:
  struct Node {
    T value;
    Node* next;
    Node(const T& v, Node* n = nullptr) : value(v), next(n) {}
    Node(T&& v, Node* n = nullptr) : value(std::move(v)), next(n) {}
  };

  Node* head_ = nullptr;
  Node* tail_ = nullptr;

public:
  LinkedList() = default;

  // запретим копирование (иначе нужен Rule of 5)
  LinkedList(const LinkedList&) = delete;
  LinkedList& operator=(const LinkedList&) = delete;

  ~LinkedList() {
    while (head_) {
      Node* next = head_->next;
      delete head_;
      head_ = next;
    }
    tail_ = nullptr;
  }

  // добавить в конец O(1)
  push_back(const T& val) {
    Node* new_node = new Node(val);
    if (!head_) {
      head_ = tail_ = new_node;
      return;
    }
    tail_->next = new_node;
    tail_ = new_node;
  }

  // удалить с конца O(n)
  pop_back() {
    if (!head_) {
      return;
    }

    if (head_ == tail_) {
      delete head_;
      head_ = tail_ = nullptr;
      return;
    }

    Node* runner = head_;
    while (runner->next != tail_) {
      runner = runner->next;
    }
    delete tail_;
    tail_ = runner;
    tail_->next = nullptr;
  }

  // добавить в начало O(1)
  push_front(const T& val) {
    Node* new_node = new Node(val, head_);
    head_ = new_node;
    if (!tail_) {
      tail_ = head_;
    }
  }

  // удалить с начала O(1)
  pop_front() {
    if (!head_) {
      return;
    }

    Node* new_head = head_->next;
    delete head_;
    head_ = new_head;
    if (!head_) {
      tail_ = nullptr;
    }
  }
};

#endif  // LINKEDLIST_HPP
