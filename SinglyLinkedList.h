
#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <exception>
#include <memory>

template <typename T>
class SLNode {
public:
  SLNode(const T& x, std::shared_ptr<SLNode> next)
  : element_(x), next_(next) {}

  const T& Element() const { return element_; }
  void SetElement(T x) { element_ = x; }
  std::shared_ptr<SLNode> Next() { return next_; }
  void SetNext(std::shared_ptr<SLNode> next) { next_ = next; }

private:
  T element_;
  std::shared_ptr<SLNode> next_;
};

template <typename T>
class SLList {
public:
  SLList()
  : head_(nullptr), tail_(nullptr), size_(0) {}

  SLList(const SLList& other) { CopyFrom(other); }

  SLList& operator=(const SLList& other) { CopyFrom(other); }

  ~SLList() { Clear(); }

  void Clear() {
    while (size_ > 0) {
      RemoveFront();
    }
  }

  int Size() { return size_; }

  const T& Front() const {
    if (size_ == 0) {
      throw std::underflow_error("list is empty");
    }
    return head_->Element();
  }

  const T& Back() const {
    if (size_ == 0) {
      throw std::underflow_error("list is empty");
    }
    return tail_->Element();
  }

  void AddFront(T x) {
    std::shared_ptr<SLNode<T>> new_node
     = std::make_shared<SLNode<T>>(x, head_);
    head_ = new_node;
    if (size_ == 0) {
      tail_ = new_node;
    }
    size_++;
  }

  void AddBack(T x) {
    std::shared_ptr<SLNode<T>> new_node
     = std::make_shared<SLNode<T>>(x, nullptr);
    if (size_ > 0) {
      tail_->SetNext(new_node);
    } else {
      head_ = new_node;
    }
    tail_ = new_node;
    size_++;
  }

  void RemoveFront() {
    if (size_ == 0) {
      throw std::underflow_error("list is empty");
    }
    head_ = head_->Next();
    // old head is automatically deleted by shared_ptr
    size_--;
  }

  const T& Get(int i) const {
    if ((i < 0) || (i >= size_)) {
      throw std::out_of_range("i");
    }
    return Skip(i)->Element();
  }

  void Set(int i, const T& x) {
    if ((i < 0) || (i >= size_)) {
      throw std::out_of_range("i");
    }
    Skip(i)->SetElement(x);
  }

  void Add(int i, const T& x) {
    if ((i < 0) || (i > size_)) {
      throw std::out_of_range("i");
    } else if (i == 0) {
      AddFront(x);
    } else if (i == size_) {
      AddBack(x);
    } else {
      std::shared_ptr<SLNode<T>> before = Skip(i - 1),
        new_node = std::make_shared<SLNode<T>>(x, before->Next());
      before->SetNext(new_node);
      size_++;
    }
  }

  void Remove(int i) {
    if ((i < 0) || (i >= size_)) {
      throw std::out_of_range("i");
    } else if (i == 0) {
      RemoveFront();
    } else {
      std::shared_ptr<SLNode<T>> before = Skip(i - 1),
        after = before->Next()->Next();
      before->SetNext(after);
      // after->Next() is automatically deleted
      if (i == (size_ - 1)) {
        tail_ = before;
      }
      size_--;
    }
  }

  void RemoveBack() {
    if (size_ == 0) {
      throw std::underflow_error("list is empty");
    }
    Remove(size_ - 1);
  }

  // Returns the count of positive numbers in the list.
  int CountPositive() {
    return CountPositiveRec(head_);
  }

private:

  std::shared_ptr<SLNode<T>> head_, tail_;
  int size_;

  int CountPositiveRec(std::shared_ptr<SLNode<T>> where) {
    if (where == nullptr) {
      return 0;
    }
    int positives_in_rest = CountPositiveRec(where->Next());
    if (where->Element() > 0) {
      return 1 + positives_in_rest;
    } else {
      return positives_in_rest;
    }
  }

  std::shared_ptr<SLNode<T>> Skip(int i) const {
    std::shared_ptr<SLNode<T>> where = head_;
    for (int j = 0; j < i; j++) {
      where = where->Next();
    }
    return where;
  }

  void CopyFrom(const SLList& other) {
    for (std::shared_ptr<SLNode<T>> where = other.head_;
         where != nullptr;
         where = where->Next()) {
      AddBack(where->Element());
    }
  }

};

#endif
