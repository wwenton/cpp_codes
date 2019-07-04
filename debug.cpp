
template <class c> auto try_out(c x) -> decltype(cerr << x, 0);
char try_out(...);

template <class c> struct range { c b, e; };
template <class c> range<c> mrange(c i, c j) { return range<c>{i, j}; }

struct err {

	template <class c, class d> err& operator << (pair<c,d> x) {
		return *this << "(" << x.first << ", " << x.second << ")";
	}
	
	template <class c> typename enable_if<sizeof(try_out(declval<c>())) != 1, err&>::type operator << (c x) {
		cerr << boolalpha << x;
		return *this;
	}
	
	template <class c> typename enable_if<sizeof(try_out(declval<c>())) == 1, err&>::type operator << (c x) {
		return *this << mrange(begin(x), end(x));
	}

	template <class c> err& operator << (range<c> x) {
		*this << "{";
		for (auto it = x.b; it != x.e; it++)
			*this << ", " + 2 * (it == x.b) << *it;
		return *this << "}";
	}

};

#define aty(...) "[ " << #__VA_ARGS__ << " : " << __VA_ARGS__ << " ]"


