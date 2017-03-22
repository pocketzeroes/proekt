class Iterator {
    struct Data;
	Data* data;
  public:
	Iterator(const vector<int>& nums);
	Iterator(const Iterator& iter);
	virtual ~Iterator();
	int next();
	bool hasNext() const;
};
class PeekingIterator : public Iterator {
  public:
    PeekingIterator(const vector<int>& nums) : Iterator(nums), has_next_(Iterator::hasNext()) {
      ;;
    }
    int peek() {
        if (!has_peeked_) {
            has_peeked_ = true;
            val_        = Iterator::next();
        }
        return val_;
    }
    int next() {
        val_        = peek();
        has_peeked_ = false;
        has_next_   = Iterator::hasNext();
        return val_;
    }
    bool hasNext() const {
        return has_next_;
    }
  private:
    int  val_;
    bool has_next_;
    bool has_peeked_ = false;
};
